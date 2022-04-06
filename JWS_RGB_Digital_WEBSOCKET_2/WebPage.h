const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
    <head>
    <title>JWS Digital</title>
    <meta charset="UTF-8">
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
                display: none;
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

            .tab {
            overflow: hidden;
            border: 1px solid #ccc;
            background-color: #f1f1f1;
            }

            /* Style the buttons inside the tab */
            .tab button {
            background-color: inherit;
            float: left;
            border: none;
            outline: none;
            cursor: pointer;
            padding: 14px 16px;
            transition: 0.3s;
            font-size: 17px;
            }

            /* Change background color of buttons on hover */
            .tab button:hover {
            background-color: #ddd;
            }

            /* Create an active/current tablink class */
            .tab button.active {
            background-color: #ccc;
            }
            .ws table {
            font-family: arial, sans-serif;
            border-collapse: collapse;
            width: 100%;
            }

            .ws td, th {
            border: 1px solid #dddddd;
            text-align: left;
            padding: 8px;
            }
        </style>
    </head>
    <body>
        <div class="topnav">
            <h1>JWS Digital</h1>
            </div>

            <div class="tab">
                <button class="tablinks" onclick="openCity(event, 'tglw')">Tanggal&Waktu</button>
                <button class="tablinks" onclick="openCity(event, 'jadwal')">Jadwal Sholat</button>
                <button class="tablinks" onclick="openCity(event, 'info')">Info</button>
                <button class="tablinks" onclick="openCity(event, 'setting')">Setting</button>
            </div>

            <div class="content" id='tglw'>
                <div class="card">
                    <h2>Tanggal&Waktu</h2>
                    <p class="state">Date : <span id="tgl">00-00-00</span></p>
                    <p class="state">Time : <span id="waktu">00-00-00</span></p>
                    <input type="DATE" id="date"/><input type="TIME" id="time"/><br>
                    <p><button id="button" class="button">Simpan</button></p>
                    <p><button id="selaras" class="button">Selaraskan</button></p>
                </div>
            </div>

            <div class="content" id='jadwal'>
                <div class="card" align="center" > 
                    <h2>Jadwal Sholat</h2>
                        <table style="border: 1px solid" class="ws">
                            <tr>
                                <td>Imsyak</td>
                                <td id="wsim">0:0:0</td>
                            </tr>
                            <tr>
                                <td>Shubuh</td>
                                <td id="wssh">0:0:0</td>
                            </tr>
                            <tr>
                                <td>Terbit</td>
                                <td id="wstr">0:0:0</td>
                            </tr>
                            <tr>
                                <td>Dhuha</td>
                                <td id="wsdh">0:0:0</td>
                            </tr>
                            <tr>
                                <td>Dzuhur</td>
                                <td id="wsdz">0:0:0</td>
                            </tr>
                            <tr>
                                <td>Ashar</td>
                                <td id="wsas">0:0:0</td>
                            </tr>
                            <tr>
                                <td>Maghrib</td>
                                <td id="wsma">0:0:0</td>
                            </tr>
                            <tr>
                                <td>Isya</td>
                                <td id="wsis">0:0:0</td>
                            </tr>
                        </table>
                </div>
            </div>

            <div class="content" id='info'>
                <div class="card">
                    <h2>Info</h2>
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

            <div class="content" id='setting'>
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
                            <input id="hilal" size="3"/>
                            </td>
                        </tr>
                        <tr>
                            <td>
                            <label for="ssid">SSID</label><br>
                            <input id="ssid" type="text" size="9"/>
                            </td>
                            <td>
                            <label for="p_ssid">Password</label><br>
                            <input id="p_ssid" type="text" size="9"/>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <label for="ap">Access Point Mode</label><br>
                                <input id="ap" type="text" size="9"/>
                            </td>
                            <td>
                                <label for="p_ap">Password Access Point Mode</label><br>
                                <input id="p_ap" type="text" size="9"/>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2">
                                <label for="batastombol">Batas Tombol</label><br>
                                <input id="batastombol"/>
                            </td>
                        </tr>
                    </table>
                <br>
                <p><button id="set" class="button">Simpan</button></p>
            </div>
        </div>
        <script>

            function openCity(evt, cityName) {
                let i, content, tablinks;
                content = document.getElementsByClassName("content");
                for (i = 0; i < content.length; i++) {
                content[i].style.display = "none";
                }
                tablinks = document.getElementsByClassName("tablinks");
                for (i = 0; i < tablinks.length; i++) {
                tablinks[i].className = tablinks[i].className.replace(" active", "");
                }
                document.getElementById(cityName).style.display = "block";
                evt.currentTarget.className += " active";
            }

            var gateway = `ws://${window.location.hostname}/ws`;
            var websocket;
            window.addEventListener('load', onLoad);
            function initWebSocket() {
                console.log('Trying to open a WebSocket connection...');
                websocket = new WebSocket(gateway);
                websocket.onopen    = onOpen;
                websocket.onclose   = onClose;
                websocket.onmessage = onMessage;
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
                    case 3:
                        jadwalSholat(b);
                        break;
                    default:
                        break;
                }
            }
            function onLoad(event) {
                initWebSocket();
                initButton();
            }
            function initButton() {
                document.getElementById('button').addEventListener('click', waktu);
                document.getElementById('selaras').addEventListener('click', selaraskan);
                document.getElementById('tekss').addEventListener('click', teks);
                document.getElementById('set').addEventListener('click', set);
            }
            // =================================TERIMA========================================
            function proseswaktu(x){
                document.getElementById("waktu").innerHTML=x;
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

            function jadwalSholat(x){
                let convert = x.split(";");
                document.getElementById("tgl").innerHTML=convert[0];
                document.getElementById("wsim").innerHTML=convert[1];
                document.getElementById("wssh").innerHTML=convert[2];
                document.getElementById("wstr").innerHTML=convert[3];
                document.getElementById("wsdh").innerHTML=convert[4];
                document.getElementById("wsdz").innerHTML=convert[5];
                document.getElementById("wsas").innerHTML=convert[6];
                document.getElementById("wsma").innerHTML=convert[7];
                document.getElementById("wsis").innerHTML=convert[8];
            }
            //   ================================KIRIM=========================================
            function kirim(x, y){
                let data = "#"+ y + "," + x + ";";
                console.log(data);
                websocket.send(data);
            }
            function waktu(){
                let a = document.getElementById("time").value;
                let b = document.getElementById("date").value;
                let data = String(b)+",";
                data += String(a)+":0";
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
                let data = String(tahun)+"-"
                data += String(bulan)+"-";
                data += String(tgl)+",";
                data += +String(jam)+":";
                data += String(menit)+":";
                data += String(detik);
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
                    batastombol:batastombol
                };
                let data = JSON.stringify(dataadmin);
                kirim(data, "2");
            }
        </script>
    </body>
</html>
)rawliteral";
