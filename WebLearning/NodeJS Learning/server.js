var http = require('http');
var fs = require('fs');

http.createServer(function(req, res) {
    fs.readFile('index.html', function(err, data) {
        if (err) {
            res.writeHead(404);
            res.write('File not found! :(');
        }
        else {
            res.writeHead(200, {'Content-Type': 'text/html'});
            res.write(data);
        }
    fs.writeFile('myFile.txt', 'My Text UwU', function(err) {
        if (err) throw err;
        console.log('Created new file');
    });

        res.end();
    })

}).listen(8080);
