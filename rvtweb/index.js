var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');
var uuid = require('node-uuid');
var mkdirp = require('mkdirp');
var rimraf = require('rimraf');
// app.use(express.static(__dirname + '/frontend'));
// app.get('/', (req, res) => res.sendFile(__dirname + '/frontend/index.html'));

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

   socket.on('sample_request', function(sample_name){
   		console.log(sample_name);
   		var file1 = '.\\samples\\' + sample_name + '_1.txt';
   		var file2 = '.\\samples\\' + sample_name + '_2.txt';
   		var fileprms = '.\\samples\\' + sample_name + '_prms.txt';
   		fs.readFile(file1, 'utf8', 
		  	function(err, data1) {
			  	if (err) throw err;
			  	var side1 = data1;

			  	fs.readFile(file2, 'utf8', 
		  			function(err, data2) {
		  				if (err) throw err;
			  			var side2 = data2;

			  			fs.readFile(fileprms, 'utf8', 
				  			function(err, data3) {
				  				if (err) throw err;
					  			var prms = data3;
					  			console.log('sending response');
					  			socket.emit('sample_response',  {p1: side1,
					  											p2: side2,
					  											parameters: prms});
				  			});
		  			});


			});
		});
  });


http.listen(3000, () => console.log('listening on *:3000'));

function deleteFolder(folderName){
	rimraf(folderName, function(err){
		if (err) throw err;
		console.log('Deleted temporary folder');
	});
}

function runRVT(socket, p1, p2, folderName, params){
	var errText = '';
	
	var rvtCommand = 'C:\\NewRVT\\Debug\\rv.exe ' + params + ' ' + p1 + ' ' + p2;
	const exec = require('child_process').exec;
	
	console.log('Running RVT');
	var cmd = exec(rvtCommand , {cwd: folderName},
				(err, stdout, stderr) => {
					  if (err) {
					  	console.log(errText);
					    socket.emit('wait', errText);
					    deleteFolder(folderName);
					    return;
					  }
					  console.log('RVT is done, sending result');
					
					  fs.readFile(folderName + '\\rv_out.gv', 'utf8', 
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


function checkEquivalence(msg, socket) {
    var uid = uuid.v1();
    var folderName = 'C:\\NewRVT\\rvtweb\\' + uid
	mkdirp(folderName, function(err) { 
		if (err) {
			socket.emit('wait', 'Error creating dedicated folder');
			throw err;
		}
		var p1Path = folderName + '\\p1.c';
		var p2Path = folderName + '\\p2.c';
		fs.writeFile(p1Path, msg.p1, errFunc);
	    fs.writeFile(p2Path, msg.p2, errFunc);

	    runRVT(socket, p1Path, p2Path, folderName, msg.prms);

    });

}

