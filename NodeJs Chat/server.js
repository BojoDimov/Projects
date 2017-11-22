const net = require('net');

function Server() {
	this.clients = [];
	this.instance = null;

	this.init = function () {
		this.instance = net.createServer(() => {
			console.log('Server instance created and server is listening...');
		}).listen(9000);

		this.instance.on('connection', (connection) => this.accept(connection));
	}

	this.receiveClientMessage = function (message, sender) {
		this.clients.forEach((element) => {
			if(element != sender)
				element.write(message);
		});
	}

	this.accept = function (client) {
		this.clients.push(client);
		client.on('data', (data) => this.receiveClientMessage(data, client));

		client.on('error', () => {
			console.log('Client disconnected');
			this.clients.splice(this.clients.indexOf(client), 1);
		});

		console.log('Client ' + client.address().address + ' connected!');
	}
}

	(function () {
		var server = new Server();
		server.init();
	}());