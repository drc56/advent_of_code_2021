var message = 'Hello, World!';
console.log(message);
var prev = null;
var increases = 0;
var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('input.txt')
});
lineReader.on('line', function (line) {
    var cur = parseInt(line);
    if (prev != null && cur > prev) {
        increases++;
        console.log(increases);
    }
    // console.log('Line from file:', cur);
    prev = cur;
});
console.log(increases);
