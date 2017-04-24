var winston = require('winston');
winston.add(winston.transports.File, { filename: 'rvt.log' });
winston.remove(winston.transports.Console);
winston.add(winston.transports.Console, {'timestamp':true});var express = require('express');

var app = express();
var http = require('https').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');
var uuid = require('node-uuid');
var mkdirp = require('mkdirp');
var rimraf = require('rimraf');
var path = require('path');
// app.use(express.static(__dirname + '/frontend'));
// app.get('/', (req, res) => res.sendFile(__dirname + '/frontend/index.html'));

var HOME_FOLDER = "C:\\gitrvt\\rvtweb";
var SAMPLE_FOLDER = path.join(HOME_FOLDER, "samples");
var SAMPLE_PROGRAM1_FILE_NAME = "p1.txt";
var SAMPLE_PROGRAM2_FILE_NAME = "p2.txt";
var SAMPLE_PARAMETERS_FILE_NAME = "prms.txt";
var RV_PATH = 'C:\\gitrvt\\Release\\rv.exe';
var RESULT_FILE = 'rv_out.gv';
var FUF_FILE = 'rv_pe.fuf';
var FUF_COMMAND = '-fuf ' + FUF_FILE;
var LISTENING_PORT = 3017;
var MUTUAL_TERMINATION_PARAM = '-mt';


io.on('connection', function(socket){
  winston.info('a user connected');
  socket.on('disconnect', function(){
    winston.info('user disconnected');
  });
   socket.on('message', function(msg){
   		errFunc = err => {
						    if(err) {
						        return console.log(err);
						    }
						 };
		winston.info('request received');
  		checkEquivalence(msg, socket);
	}); 

   socket.on('init_samples', function(sample_name){
   		var sample_dirs = getDirectories(SAMPLE_FOLDER);
   		var sample = readSample('Basecase not in sync')
   		sample.additional_samples = sample_dirs;
   		socket.emit('init_samples_response', sample);
   });

   socket.on('sample_request', function(sample_name){
   		winston.info('sample requested: ' + sample_name);
  
   		var sample = readSample(sample_name)
   		socket.emit('sample_response', sample);
  	});
});

http.listen(LISTENING_PORT, () => winston.info('listening on: ' + LISTENING_PORT));

function deleteFolder(folderName){
	rimraf(folderName, function(err){
		if (err) throw err;
		winston.info('deleted temporary folder');
  
	});
}

function runRVT(socket, p1, p2, folderName, params){
	var errText = '';
	
	const exec = require('child_process').exec;
	if (params.indexOf(MUTUAL_TERMINATION_PARAM) > -1){
		
		var moddedParams = params.replace('-mt', '');
		// running rvt without mt to create rv_pe.fuf file
		var rvtMtCommand = RV_PATH + ' ' + moddedParams + ' ' + p1 + ' ' + p2;

		winston.info('Running mt RVT: ' + rvtMtCommand);
		
		var cmd = exec(rvtMtCommand , {cwd: folderName},
					(err, stdout, stderr) => {
						  if (err) {
						  	winston.info(errText);
						    socket.emit('wait', errText);
						    deleteFolder(folderName);
						    return;
						  }
							
						var rvtCommand = RV_PATH + ' ' + FUF_COMMAND + ' ' + params + ' ' + p1 + ' ' + p2;

						winston.info('RVT pe is done, continue with mt proof: ' + rvtCommand);
						var cmd = exec(rvtCommand , {cwd: folderName},
								(err, stdout, stderr) => {
									  if (err) {
									  	winston.info(errText);
									    socket.emit('wait', errText);
									    deleteFolder(folderName);
									    return;
									  }
								
								winston.info('RVT mt is done, sending results');
								fs.readFile(path.join(folderName, RESULT_FILE), 'utf8', 
						  		function(err, data) {
								  	if (err) throw err;
								  	socket.emit('message', data);
									deleteFolder(folderName);
								});
						  });	  

						});
						  
						  
	      cmd.stderr.on('data', function(data) {
	      errText += data.toString();
	    });

	}
	else{
		winston.info('Running RVT');
		var rvtCommand = RV_PATH + ' ' + params + ' ' + p1 + ' ' + p2;
		var cmd = exec(rvtCommand , {cwd: folderName},
					(err, stdout, stderr) => {
						  if (err) {
						  	winston.info(errText);
						    socket.emit('wait', errText);
						    deleteFolder(folderName);
						    return;
						  }
						  winston.info('RVT is done, sending result');
						
						  fs.readFile(path.join(folderName, RESULT_FILE), 'utf8', 
						  	function(err, data) {
							  	if (err) throw err;
							  	socket.emit('message', data);
								deleteFolder(folderName);
							});
						  });
	      cmd.stderr.on('data', function(data) {
	      		errText += data.toString();
	      		winston.info(errText);
	    });
	  }
}


function checkEquivalence(msg, socket) {
    var uid = uuid.v1();
    var folderName = path.resolve(path.join(HOME_FOLDER, uid));
	mkdirp(folderName, function(err) { 
		if (err) {
			socket.emit('wait', 'Error creating dedicated folder');
			throw err;
		}
		var p1Path = path.join(folderName, 'p1.c');
		var p2Path = path.join(folderName, 'p2.c');
		fs.writeFile(p1Path, msg.p1, errFunc);
	    fs.writeFile(p2Path, msg.p2, errFunc);

	    runRVT(socket, p1Path, p2Path, folderName, msg.prms);

    });

}

function getDirectories(srcpath) {
  return fs.readdirSync(srcpath).filter(function(file) {
    return fs.statSync(path.join(srcpath, file)).isDirectory();
  });
}

function readSample(sample_name){
	var file1 = path.join('.', SAMPLE_FOLDER, sample_name, SAMPLE_PROGRAM1_FILE_NAME);
   	var file2 = path.join('.', SAMPLE_FOLDER, sample_name, SAMPLE_PROGRAM2_FILE_NAME);
   	var fileprm = path.join('.', SAMPLE_FOLDER, sample_name, SAMPLE_PARAMETERS_FILE_NAME);

   	var program1 = fs.readFileSync(file1).toString();
   	var program2 = fs.readFileSync(file2).toString();
	var prms = fs.readFileSync(fileprm).toString();
   		
	return {p1: program1, p2: program2, parameters: prms};

}

