const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>JWS Digital</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
</head>
<body>
  <div class="topnav">
    <h1>JWS Digital</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Setel Waktu</h2>
      <p class="state">Waktu : <span id="state">00-00-00</span></p>
      <input type="TIME" id="time"/><br>
      <p><button id="button" class="button">Simpan</button></p>
      <p><button id="selaras" class="button">Selaraskan</button></p>
    </div>
  </div>
  <div class="content">
    <div class="card">
      <label for="teks">Teks :</label>
      <input type="text" id="teks" name="teks"><br><br>
      <p><button id="tekss" class="button">Kirim</button></p>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    let state=event.data;
    document.getElementById('state').innerHTML = state;
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function kirim(x, y){
    let data = y+ "," + x + ";";
    console.log(data);
    websocket.send(data);
  }
  function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
    document.getElementById('selaras').addEventListener('click', selaraskan);
    document.getElementById('tekss').addEventListener('click', teks);
  }
  function toggle(){
    let a = document.getElementById("time").value;
    let data = a+":0";
    kirim(data, "0");
  }
  function selaraskan(){
    var now = new Date();
    let jam = now.getHours();
    let menit = now.getMinutes();
    let detik = now.getSeconds();
    let data = String(jam)+":"+String(menit)+":"+String(detik);
    kirim(data, "0");
  }
  function teks(){
    let data = document.getElementById("teks").value;
    kirim(data, "1");
  }
</script>
</body>
</html>
)rawliteral";
