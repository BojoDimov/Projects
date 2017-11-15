var http = require("http");
const websocket = require('websocket').server;
var ytdl = require('ytdl-core');

const videoKey = "WSeNSzJ2-Jw";
const port = 12909;
const httpServer = http.createServer();
const wsServer = new websocket({ httpServer: httpServer});
httpServer.listen(port, () => console.log((new Date()) + " Server is listening on port " + port));

wsServer.on('request', req => {
	console.log((new Date()) + ' Connection from origin ' + request.origin + '.');
	let conn = req.accept();
	conn.on('message', handleConnectionMessage);
})

function handleConnectionMessage(message){
	console.log(message);
}

function streamSong(videoKey, connection){
	let finished = false;
	ytdl(videoKey, { filter: 'audioonly' }).on('data', connection.sendBytes);
}

function streamChunk(videoKey, connection, offset, size){
	ytdl(videoKey, { range: { start: offset, end: offset + size}}).on('data', connection.sendBytes);
}


// if song chunk is missing and we are requesting song portion, which that chunk contains
// request the chung with request event "request_chunk"
//Q: how to tell if chunk is missing?
//:- seek song -> offset song by time offset -> tell if song buffer is long enough 
// Nah: better is to divide the song in array of SongChunkObject { offset: time_t} and check if the speciffic chunk is availiable
static class WsEvents {
	static RequestChunk = 'request_chunk';
	static RequestSong = 'request_song';
}

/**
 * Audio songs flow for the chunked implementation:
 * 1. Request viewKey info
 * 2. Receive viewKey info request
 * 3. Get audio info with getInfo()
 * 4. Send back audio info
 * 5. Request Audio source using info object? or using the viewKey at speciffic byte offset e.g. start of song is [0, byteSizeFor10SecAudio]
 * 6. Receive request
 * 7. Request the  speciffic chunk using range(start = offset, end = offset + byteSizeFor10SecAudio)
 * 8. Send the chunk to the UI
 * 9. Handle chunk insertion into the song chunk array
 */

 /**
	* Audio song flow for the initial implementation downloading the whole song at once:
	* 1. Request song source by viewKey
	* 2. Get song
	* 3. Add song to queue
	*/