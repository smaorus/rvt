var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');
var uuid = require('node-uuid');
var mkdirp = require('mkdirp');
var rimraf = require('rimraf');
var path = require('path');
// app.use(express.static(__dirname + '/frontend'));
// app.get('/', (req, res) => res.sendFile(__dirname + '/frontend/index.html'));

var SAMPLE_FOLDER = "samples"
var SAMPLE_PROGRAM1_FILE_NAME = "p1.txt";
var SAMPLE_PROGRAM2_FILE_NAME = "p2.txt";
var SAMPLE_PARAMETERS_FILE_NAME = "prms.txt";
var RV_PATH = path.resolve(path.join('..', 'Debug', 'rv.exe'));
var RESULT_FILE = 'rv_out.gv';
var FUF_FILE = 'rv_pe.fuf';
var FUF_COMMAND = '-fuf ' + FUF_FILE;
var LISTENING_PORT = 3017;
var MUTUAL_TERMINATION_PARAM = '-mt';


io.on('connection', function(socket){
  console.log('a user connected');
  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
   socket.on('message', function(msg){
   		errFunc = err => {
						    if(err) {
						        return console.log(err);
						    }
						 };
		console.log('Request received');
		checkEquivalence(msg, socket);
	}); 

   socket.on('init_samples', function(sample_name){
   		var sample_dirs = getDirectories('samples');
   		var sample = readSample('Basecase not in sync')
   		sample.additional_samples = sample_dirs;
   		socket.emit('init_samples_response', sample);
   });

   socket.on('sample_request', function(sample_name){
   		console.log(sample_name);

   		var sample = readSample(sample_name)
   		socket.emit('sample_response', sample);
  	});
});

http.listen(LISTENING_PORT, () => console.log('listening on *:' + LISTENING_PORT));

function deleteFolder(folderName){
	rimraf(folderName, function(err){
		if (err) throw err;
		console.log('Deleted temporary folder');
	});
}

function runRVT(socket, p1, p2, folderName, params){
	var errText = '';
	
	const exec = require('child_process').exec;
	if (params.indexOf(MUTUAL_TERMINATION_PARAM) > -1){
		
		var moddedParams = params.replace('-mt', '');
		// running rvt without mt to create rv_pe.fuf file
		var rvtMtCommand = RV_PATH + ' ' + moddedParams + ' ' + p1 + ' ' + p2;

		console.log('Running mt RVT: ' + rvtMtCommand);
		
		var cmd = exec(rvtMtCommand , {cwd: folderName},
					(err, stdout, stderr) => {
						  if (err) {
						  	console.log(errText);
						    socket.emit('wait', errText);
						    deleteFolder(folderName);
						    return;
						  }
							
						var rvtCommand = RV_PATH + ' ' + FUF_COMMAND + ' ' + params + ' ' + p1 + ' ' + p2;

						console.log('RVT pe is done, continue with mt proof: ' + rvtCommand);
						var cmd = exec(rvtCommand , {cwd: folderName},
								(err, stdout, stderr) => {
									  if (err) {
									  	console.log(errText);
									    socket.emit('wait', errText);
									    deleteFolder(folderName);
									    return;
									  }
								
								console.log('RVT mt is done, sending results');
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
		console.log('Running RVT');
		var rvtCommand = RV_PATH + ' ' + params + ' ' + p1 + ' ' + p2;
		var cmd = exec(rvtCommand , {cwd: folderName},
					(err, stdout, stderr) => {
						  if (err) {
						  	console.log(errText);
						    socket.emit('wait', errText);
						    deleteFolder(folderName);
						    return;
						  }
						  console.log('RVT is done, sending result');
						
						  fs.readFile(path.join(folderName, RESULT_FILE), 'utf8', 
						  	function(err, data) {
							  	if (err) throw err;
							  	socket.emit('message', data);
								deleteFolder(folderName);
							});
						  });
	      cmd.stderr.on('data', function(data) {
	      errText += data.toString();
	    });
	  }
}


function checkEquivalence(msg, socket) {
    var uid = uuid.v1();
    var folderName = path.resolve(path.join('.', uid));
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

