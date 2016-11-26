var five = require("johnny-five"),
    board = new five.Board(),
    net = require('net');
net.createServer(function (socket) {
    socket.on('data', function (data) {
        console.log(data.toString());
        socket.disconnect();
    });
}).listen(5000);

board.on("ready", function () {
    // Creates a piezo object and defines the pin to be used for the signal
    //var piezo = new five.Piezo(4);
    var led = new five.Led(3);

    var proximity = new five.Proximity({
        controller: "HCSR04",
        pin: 8
    });

    var repl = this.repl;

    var status = false;

    proximity.on("data", function () {
        if (this.cm <= 50 && status == false) {
            status = true;
            console.log("ON: ", this.cm);
            led.on();
        } else if (this.cm > 50 && status == true) {
            status = false;
            console.log("OFF: ", this.cm);
            led.off();
        }

    });

    /*
     board.repl.inject({
     piezo: piezo
     });
     */
    /*
     setInterval(function() {
     piezo.play({
     // song is composed by a string of notes
     // a default beat is set, and the default octave is used
     // any invalid note is read as "no note"
     song: "G C G C - E - -",
     beats: 1 / 4,
     tempo: 30
     });
     }, 1000);
     */

});