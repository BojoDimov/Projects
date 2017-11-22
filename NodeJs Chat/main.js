const child_factory = require('child_process');

function main() {

}

function doCalculation(data, func){
	for(var i = 0 ; i < data.length; i++){
		data[i] = func(data[i])
	}
}

main();

//192.168.10.104