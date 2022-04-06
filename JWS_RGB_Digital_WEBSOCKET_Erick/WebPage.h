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
      <p class="state">Date : <span id="tgl">00-00-00</span></p>
      <p class="state">Time : <span id="waktu">00-00-00</span></p>
      <input type="DATE" id="date"/><input type="TIME" id="time"/><br>
      <p><button id="button" class="button">Simpan</button></p>
      <p><button id="selaras" class="button">Selaraskan</button></p>
    </div>
  </div>
  <div class="content">
    <div class="card">
        <h2>Setel Info</h2>
        <label for="angka">Info ke-:</label>
        <select id="angka">
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
            <option value="4">4</option>
            <option value="5">5</option>
            <option value="6">6</option>
            <option value="7">7</option>
            <option value="8">8</option>
            <option value="9">9</option>
            <option value="10">10</option>
          </select>
      <label for="teks">Teks Info :</label>
      <input type="text" id="teks" placeholder="Input Teks">
      <br><br>
      <p><button id="tekss" class="button">Kirim</button></p>
    </div>
  </div>

  <div class="content">
    <div class="card">
        <h2>Setting</h2>
  <table width='100%'>
    <tr>
        <td>
        <label for="latitude">Latitude</label><br>
        <input id="latitude" size="9"/>
        </td>
        <td>
        <label for="longitude">Longitude</label><br>
        <input id="longitude" size="9"/>
        </td>    
    </tr>
    <tr>
        <td>
        <label for="zonawaktu">Zona Waktu</label><br>
        <input id="zonawaktu" size="3"/>
        </td>
        <td>
        <label for="hilal">Hilal</label><br>
        <input id="hilal" maxlength="2" size="3"/>
        </td>
    </tr>
    <tr>
        <td>
        <label for="ssid">SSID</label><br>
        <input id="ssid" type="text"/>
        </td>
        <td>
        <label for="p_ssid">Password</label><br>
        <input id="p_ssid" type="text"/>
        </td>
    </tr>
    <tr>
        <td>
        <label for="ap">Access Point Mode</label><br>
        <input id="ap" type="text"/>
        </td>
        <td>
        <label for="p_ap">Password Access Point Mode</label><br>
        <input id="p_ap" type="text"/>
        </td>
    </tr>
    <tr>
        <td colspan="3">
        <label for="batastombol">Batas Tombol</label><br>
        <input id="batastombol" maxlength="3"/>
        </td>
    </tr>
</table>

<br>
<p><button id="set" class="button">Simpan</button></p>
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
    let data=event.data;
    let a = data.substring(0,1);
    let b = data.substring(1);
    console.log(data);
    switch(parseInt(a)){
        case 0:
            proseswaktu(b);
            break;
        case 1:
            prosesdata(b);
            break;
        default:
            break;
    }
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
// =================================TERIMA========================================
  function proseswaktu(x){
    let convert = x.split(";");
    document.getElementById("tgl").innerHTML=convert[0];
    document.getElementById("waktu").innerHTML=convert[1];
    console.log(convert[0]);
    console.log(convert[1]);
  }
  function prosesdata(x){
    let myObj = JSON.parse(x);
    document.getElementById('latitude').value=myObj.lat;
    document.getElementById('longitude').value=myObj.lon;
    document.getElementById('zonawaktu').value=myObj.z_w;
    document.getElementById('hilal').value=myObj.hilal;
    document.getElementById('ssid').value=myObj.ssid;
    document.getElementById('p_ssid').value=myObj.p_ssid;
    document.getElementById('ap').value=myObj.ap;
    document.getElementById('p_ap').value=myObj.p_ap;
    document.getElementById('batastombol').value=myObj.batastombol;
  }

//   ================================KIRIM=========================================
  function kirim(x, y){
    let data = "#"+ y + "," + x + ";";
    console.log(data);
    websocket.send(data);
  }
  function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
    document.getElementById('selaras').addEventListener('click', selaraskan);
    document.getElementById('tekss').addEventListener('click', teks);
    document.getElementById('set').addEventListener('click', set);
  }
  function toggle(){
    let a = document.getElementById("time").value;
    let b = document.getElementById("date").value;
    let data = String(b)+","+String(a)+":0";
    kirim(data, "0");
  }
  function selaraskan(){
    var now = new Date();
    let tgl = now.getDate();
    let bulan = now.getMonth();
    let tahun = now.getFullYear();
    let jam = now.getHours();
    let menit = now.getMinutes();
    let detik = now.getSeconds();
    let data = String(tahun)+"-"+String(bulan)+"-"+String(tgl)+","+String(jam)+":"+String(menit)+":"+String(detik);
    kirim(data, "0");
  }
  function teks(){
    let a = document.getElementById("teks").value;
    let b = document.getElementById("angka").value;
    let c =parseInt(b)-1;
    data = String(c)+String(a);
    kirim(data, "1");
  }
  function set(){
    let latitude = document.getElementById("latitude").value;
    let longitude = document.getElementById("longitude").value;
    let zonawaktu = document.getElementById("zonawaktu").value;
    let hilal = document.getElementById("hilal").value;
    let ssid = document.getElementById("ssid").value;
    let p_ssid = document.getElementById("p_ssid").value;
    let ap = document.getElementById("ap").value;
    let p_ap = document.getElementById("p_ap").value;
    let batastombol = document.getElementById("batastombol").value;
    let dataadmin = {
        lat:latitude, 
        lon:longitude, 
        z_w:zonawaktu, 
        hilal:hilal, 
        ssid:ssid, 
        p_ssid:p_ssid,
        ap:ap, 
        p_ap:p_ap, 
        batastombol:batastombol};
    let data = JSON.stringify(dataadmin);
    kirim(data, "2");
}
</script>
</body>
</html>
)rawliteral";
