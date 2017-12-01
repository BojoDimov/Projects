var request = require("request");

request("http://localhost:12909", function (error, response, body) {
	console.log(body);
});