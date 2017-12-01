var http = require("http");
var url = require('url');
var fs = require('fs');
var ytdl = require('ytdl-core');


var server = http.createServer(function (request, response) {
	response.writeHead(200, { "Content-Type": "arrayBuffer", "Access-Control-Allow-Origin": "*" });

	if (request.method == 'GET') {
		//get params as object
		var queryData = url.parse(request.url, true).query;
		console.log('Requested resource: ' + queryData.viewKey);
		console.log('Requested from: ' + request.connection.remoteAddress)
		var stream = ytdl(queryData.viewKey, { filter: "audioonly" });
			
		stream.on('progress', function (obj,obj1,obj2) {
			// console.log("Chunk size is: " + obj);
			// console.log("Total downloaded is: " + obj1);
			// console.log("Total size is: " + obj2);
		})

		stream.on('finish', function(){
			console.log("Finsh!");
			response.end();
		})

		stream.pipe(response);
	}
	// else if (request.method == 'POST') {
	// 	response.write("I anwser a POST reuqest.");
	// 	response.write("With body: \n");
	// 	//read post body
	// 	var body = '';
	// 	request.on('data', function (data) {
	// 		body += data.toString();
	// 	});
	// 	request.on('end', function () {
	// 		var POST = JSON.parse(body);
	// 		console.log(POST);
	// 		response.write(body);
	// 	});
	//}
});

server.listen(12909);
console.log("Server is listening");