const si = require('systeminformation');
const delaySeconds = 0.5;
const SerialPort = require('serialport');
const port = new SerialPort('COM14', { baudRate: 9600 });
let message = '';

port.on("open", () => {
  console.log('COM14 open');
});

function loop() {

  si.currentLoad().then(data => 
    message = (`CPU    | ${Math.round(data.currentLoad * 100) / 100} %   ;`));

  si.mem().then(bytes => {
    const k = 1000;
    const dm = 0 + 1 || 3;
    const sizes = ['Bytes', 'KB', 'MB', 'GB', 'TB', 'PB', 'EB', 'ZB', 'YB'];
    const i = Math.floor(Math.log(bytes.used) / Math.log(k));
    message += (`MEMORY | ${parseFloat((bytes.used / k ** i).toFixed(dm))} ${sizes[i]}   `)});
    port.write(message.toString());
    setTimeout(loop, delaySeconds * 2000);
}

loop();