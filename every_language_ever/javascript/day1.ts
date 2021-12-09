let message: string = 'Hello, World!';
console.log(message);

let prev = null;
let increases = 0;

var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('input.txt')
});

lineReader.on('line', function (line) {
    let cur = parseInt(line);
    if (prev != null && cur > prev) {
          increases++;
          console.log(increases);
    }
    // console.log('Line from file:', cur);
    prev = cur;
});
