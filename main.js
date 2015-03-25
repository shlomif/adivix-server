var express = require('express');
var app = require('express-ws')(express()).app;
var util = require('util');
var multer = require('multer');
var schedule = require('node-schedule');
var events = require('events');
var uuid = require('uuid');
var path = require('path');

var contentBlocks = new events.EventEmitter();
var players = new events.EventEmitter();
var connectedPlayers = [];

app.use(express.static(path.join(__dirname, 'contentBlocks/files')));

app.ws('/player', function(ws, req) {
	console.log("connected player");
	var id = uuid.v4();

	players.emit('connected', id);

	contentBlocks.on("sendBlock", function(manifest) {
		var message = {type: "manifest", manifest: manifest};

		ws.send(message);
	});

	ws.on("close", function() {
		console.log("closed player");
		players.emit('disconnected', id);
	});
});

players.on('connected', function(client) {
	connectedPlayers.push(client);
});

players.on('disconnected', function(client) {
	for (var i = 0; i < connectedPlayers.length; i++) {
		if (connectedPlayers[i] === client) {
			connectedPlayers.splice(i, 1);
			break;
		}
	}
});

app.ws('/panel/players', function(ws, req) {
	// Player uptime tracker
	console.log("connected panel");

	connectedPlayers.forEach(function(client) {
		var message = {type: "connected", id: client};

		ws.send(JSON.stringify(message));
	});

	players.on('connected', function(client) {
		var message = {type: "connected", id: client};

		ws.send(JSON.stringify(message));
	});

	players.on('disconnected', function(client) {
		var message = {type: "disconnected", id: client};

		ws.send(JSON.stringify(message));
	});

	ws.on("close", function() {
		console.log("closed panel");
	});
});

app.post('/panel/manifest', multer({inMemory: true}), function (req, res) {
	var manifest = req.files.manifest.buffer;
	var time = JSON.parse(manifest).time;
	var scheduleTime = new Date(time - 1 * 24 * 60 * 60 * 1000); // Schedule to send a day before the content block should be shown

	var scheduledJob = schedule.scheduleJob(scheduleTime, function() {
		contentBlocks.emit('sendBlock', manifest);
	});
});

app.post('/panel/asset', multer({dest: "./contentBlocks/files/"}), function (req, res) {
	if(typeof req.files !== "undefined" && typeof req.files.file !== "undefined") {
		var message = {type: "upload", filename: req.files.file.name};
		res.send(message);
	} else {
		var message = {type: "error", error: "Missing file or invalid form field name"};
		res.status(422).send(message);
	}
});

var server = app.listen(3000, function () {
	var host = server.address().address;
	var port = server.address().port;

	console.log('Example app listening at http://%s:%s', host, port);
});
