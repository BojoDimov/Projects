const net = require('net');
const readline = require('readline');

const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});


function Client(username) {
	var address = '';
	var port = '';

	this.username = username;
	this.socket = null;

	this.send = function (message) {
		this.socket.write(username + ': ' + message);
	}

	this.receive = function (message) {
		console.log(new Date().toLocaleTimeString() + '  ' + message.toLocaleString());
	}

	this.init = function (server) {
		this.socket = net.connect({ port: server.port, host: server.host }, () => {
			console.log('Successfully connected to ' + server.host + ' at port ' + this.socket.localPort);
		});

		this.socket.on('data', this.receive);
	}
}


const NETWORK_CREDENTIALS = {
	host: '151.251.11.225',
	port: 9000
};

(function () {
	var client = null;
	rl.question('username: ', (answer) => {
		client = new Client(answer);
		client.init(NETWORK_CREDENTIALS);
	});

	rl.setPrompt('>');
	rl.on('line', (line) => {
		client.send(line);
		rl.prompt();
	});
}());