const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>

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

        h2 {
            font-size: 1.5rem;
            font-weight: bold;
            color: #00FF00;
        }

        .topnav {
            overflow: hidden;
            background-color: #000000;
        }

        body {
            margin: 0;
            background-color: #151519;
            color: #fff;
        }

        .content {
            display: none;
            padding: 5px;
            max-width: 600px;
            margin: 0 auto;
            background-color: #00FF00;
            -webkit-animation: fadeEffect 1s;
            animation: fadeEffect 1s;
        }

        @-webkit-keyframes fadeEffect {
            from {
                opacity: 0;
            }

            to {
                opacity: 1;
            }
        }

        @keyframes fadeEffect {
            from {
                opacity: 0;
            }

            to {
                opacity: 1;
            }
        }

        .card {
            background-color: #151519;
            ;
            box-shadow: 2px 2px 12px 1px rgba(0, 255, 0, 1);
            padding-top: 10px;
            padding-bottom: 20px;
        }

        .button {
            padding: 10px 50px;
            font-size: 24px;
            text-align: center;
            outline: none;
            color: #fff;
            background: none;
            border: 3px solid #00ff00;
            border-radius: 5px;
            -webkit-touch-callout: none;
            -webkit-user-select: none;
            -khtml-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
            user-select: none;
            -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
        }

        .button:hover {
            background-color: #00ff00;
            color: #000;
        }

        .button:active {
            background-color: #ffffff;
            box-shadow: 2 2px #00ff00;
            transform: translateY(2px);
            color: #000;
        }

        .state {
            font-size: 1.5rem;
            color: #8c8c8c;
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
            border: #ccc;
        }

        .ws td,
        th {
            border: 1px solid #ccc;
            text-align: left;
            padding: 8px;
            background-color: #66bb66;
            /* background-color: rgb(97, 219, 107); */
            color: #000;
        }
        .islide {
            opacity: 0.7;
            width: 100%;
            accent-color: #00ff00;
            height: 4px;
        }

        .form-switch {
            display: inline-block;
            cursor: pointer;
            -webkit-tap-highlight-color: transparent;
        }

        .form-switch i {
            position: relative;
            display: inline-block;
            margin-right: .5rem;
            width: 46px;
            height: 26px;
            background-color: #e6e6e6;
            border-radius: 23px;
            vertical-align: text-bottom;
            transition: all 0.3s linear;
        }

        .form-switch i::before {
            content: "";
            position: absolute;
            left: 0;
            width: 42px;
            height: 22px;
            background-color: #fff;
            border-radius: 11px;
            transform: translate3d(2px, 2px, 0) scale3d(1, 1, 1);
            transition: all 0.25s linear;
        }

        .form-switch i::after {
            content: "";
            position: absolute;
            left: 0;
            width: 22px;
            height: 22px;
            background-color: #fff;
            border-radius: 11px;
            box-shadow: 0 2px 2px rgba(0, 0, 0, 0.24);
            transform: translate3d(2px, 2px, 0);
            transition: all 0.2s ease-in-out;
        }

        .form-switch:active i::after {
            width: 28px;
            transform: translate3d(2px, 2px, 0);
        }

        .form-switch:active input:checked+i::after {
            transform: translate3d(16px, 2px, 0);
        }

        .form-switch input {
            display: none;
        }

        .form-switch input:checked+i {
            background-color: #4BD763;
        }

        .form-switch input:checked+i::before {
            transform: translate3d(18px, 2px, 0) scale3d(0, 0, 0);
        }

        .form-switch input:checked+i::after {
            transform: translate3d(22px, 2px, 0);
        }

        .slider-square {
            -webkit-appearance: none;
            width: 100%;
            height: 24px;
            background: grey;
            outline: none;
            opacity: 0.7;
            -webkit-transition: opacity .15s ease-in-out;
            transition: opacity .15s ease-in-out;
        }

        .slider-square:hover {
            opacity: 1;
        }

        .slider-square::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 24px;
            height: 24px;
            background: #00ff00;
            cursor: pointer;
        }

        .slider-square::-moz-range-thumb {
            width: 24px;
            height: 24px;
            border: 0;
            background: #00ff00;
            cursor: pointer;
        }

        
    </style>
</head>

<body>
    <div class="topnav">
        <h1>JWS Digital</h1>
    </div>

    <div class="tab">
        <button class="tablinks" id="defaultOpen" onclick="openCity(event, 'tglw')">Tanggal&Waktu</button>
        <button class="tablinks" onclick="openCity(event, 'jadwal')">Jadwal Sholat</button>
        <button class="tablinks" onclick="openCity(event, 'info')">Info</button>
        <button class="tablinks" onclick="openCity(event, 'setting')">Setting JWS</button>
        <button class="tablinks" onclick="openCity(event, 'cv')"> Kecerahan & Volume</button>
    </div>

    <div class="content" id='tglw'>
        <div class="card">
            <h2>Tanggal&Waktu</h2>
            <p class="state">Date : <span id="tgl">00-00-00</span></p>
            <p class="state">Time : <span id="waktu">00-00-00</span></p>
            <label for="date">Tanggal : </label><input type="DATE" id="date" /><br>
            <label for="time">Waktu : </label><input type="TIME" id="time" /><br>
            <p><button onclick="waktu()" class="button">Kirim</button></p>
            <p><button onclick="selaraskan()" class="button">Selaraskan</button></p>
        </div>
    </div>

    <div class="content" id='jadwal'>
        <div class="card" align="center">
            <h2>Jadwal Sholat</h2>
            <table style="border: 1px solid" class="ws">
                <tr>
                    <th>Sholat</th>
                    <th>Waktu</th>
                </tr>
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
            <p><button onclick="teks()" class="button">Kirim</button></p>
        </div>
    </div>

    <div class="content" id='setting'>
        <div class="card">
            <h2>Setting JWS</h2>
            <table width='100%'>
                <tr>
                    <td>
                        <label for="is">Iqomah Subuh</label><br>
                        <input id="is" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="id">Iqomah Dzuhur</label><br>
                        <input id="id" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="ia">Iqomah Ashar</label><br>
                        <input id="ia" maxlength="2" size="3" />
                    </td>
                </tr>
                <tr>
                    <td>
                        <label for="im">Iqomah Maghrib</label><br>
                        <input id="im" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="ii">Iqomah Isya</label><br>
                        <input id="ii" maxlength="2" size="3" />
                    </td>
                    <td>
                        <label for="durasiAdzan">Durasi Adzan</label><br>
                        <input id="durasiAdzan" maxlength="2" size="3" />
                    </td>
                </tr>
            </table>
            <table width='100%'>
                <tr>
                    <td>
                        <label for="f_ws">Faktor Waktu Sholat</label><br>
                        <input id="f_ws" size="3" />
                    </td>
                    <td>
                        <label for="durasikutbah">Durasi Kutbah</label><br>
                        <input id="durasikutbah" size="3" />
                    </td>
                    <td>
                        <label for="f_hjr">Koreksi Hijriah</label><br>
                        <input type="number" id="f_hjr" size="3" />
                    </td>
                </tr>
                <tr>
                    <td colspan="3">
                        <label class="form-switch"><input type="checkbox" name="dispiqmh" id="dispiqmh"><i></i> Display
                            Iqomah </label><br><br>
                        <label class="form-switch"><input type="checkbox" name="dispimsyak" id="dispimsyak"><i></i>
                            Display Imsyak </label><br><br>
                        <label class="form-switch"><input type="checkbox" name="ringimsyak" id="ringimsyak"><i></i>
                            Alarm Imsyak </label><br><br>
                        <label class="form-switch"><input type="checkbox" name="disppuasa" id="disppuasa"><i></i>
                            Display puasa </label><br><br>
                        <label class="form-switch"><input type="checkbox" name="dispdhuha" id="dispdhuha"><i></i>
                            Display Dhuha </label><br><br>
                        <label class="form-switch"><input type="checkbox" name="dispdhuha" id="dispterbit"><i></i>
                            Display Terbit </label><br><br>
                        <label class="form-switch"><input type="checkbox" name="dispsplash" id="dispsplash"><i></i>
                            Tampilan Awal </label><br><br>
                    </td>
                </tr>
            </table>
            <br><br>
            <p><button onclick="setting()" class="button">Kirim</button></p>
        </div>
    </div>

    <div class="content" id='cv'>
        <div class="card">
            <table width='100%'>
                <tr>
                    <td>
                        <h2>Kecerahan</h2><br>
                        <input type="range" min="0" max="255" class="islide" id="cerah" onchange="setBr()">
                    </td>
                </tr>
                <tr>
                    <td>
                        <h2>Volume</h2><br>
                        <input type="range" min="0" max="30" class="islide" id="volum" onchange="setVol()">
                    </td>
                </tr>
            </table>
        </div>
    </div>

    <script>
        var batas = false;
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
        document.getElementById("defaultOpen").click();

        var gateway = `ws://${window.location.hostname}/ws`;
        var websocket;
        window.addEventListener('load', onLoad);
        function initWebSocket() {
            console.log('Trying to open a WebSocket connection...');
            websocket = new WebSocket(gateway);
            websocket.onopen = onOpen;
            websocket.onclose = onClose;
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
            batas = true;
            let data = event.data;
            let a = data.substring(0, 1);
            let b = data.substring(1);
            console.log(data);
            switch (parseInt(a)) {
                case 1:
                    proseswaktu(b);
                    break;
                case 2:
                    jadwalSholat(b);
                    break;
                case 3:
                    prosesJWS(b);
                    break;
                default:
                    break;
            }
            batas = false;
        }
        function onLoad(event) {
            initWebSocket();
        }
        // =================================TERIMA========================================
        function proseswaktu(x) {
            document.getElementById("waktu").innerHTML = x;
        }
        function jadwalSholat(x) {
            let convert = x.split(";");
            document.getElementById("tgl").innerHTML = convert[0];
            document.getElementById("wsim").innerHTML = convert[1];
            document.getElementById("wssh").innerHTML = convert[2];
            document.getElementById("wstr").innerHTML = convert[3];
            document.getElementById("wsdh").innerHTML = convert[4];
            document.getElementById("wsdz").innerHTML = convert[5];
            document.getElementById("wsas").innerHTML = convert[6];
            document.getElementById("wsma").innerHTML = convert[7];
            document.getElementById("wsis").innerHTML = convert[8];
        }
        function prosesJWS(x) {
            var myObj = JSON.parse(x);
            document.getElementById('is').value = myObj.is;
            document.getElementById('id').value = myObj.id;
            document.getElementById('ia').value = myObj.ia;
            document.getElementById('im').value = myObj.im;
            document.getElementById('ii').value = myObj.ii;
            document.getElementById('durasiAdzan').value = myObj.durasiAdzan;
            document.getElementById('f_ws').value = myObj.f_ws;
            document.getElementById('durasikutbah').value = myObj.durasikutbah;
            document.getElementById('f_hjr').value = myObj.f_hjr;
            document.getElementById('dispiqmh').checked = !!myObj.dispiqmh;
            document.getElementById('dispimsyak').checked = !!myObj.dispimsyak;
            document.getElementById('ringimsyak').checked = !!myObj.ringimsyak;
            document.getElementById('disppuasa').checked = !!myObj.disppuasa;
            document.getElementById('dispdhuha').checked = !!myObj.dispdhuha;
            document.getElementById('dispterbit').checked = !!myObj.dispterbit;
            document.getElementById('dispsplash').checked = !!myObj.dispsplash;
        }
        //   ================================KIRIM=========================================
        function kirim(x, y) {
            if (!batas) {
                let data = "#" + y + "," + x + ";";
                console.log(data);
                websocket.send(data);
            }
        }
        function waktu() {
            let a = document.getElementById("time").value;
            let b = document.getElementById("date").value;
            let data = String(b) + ",";
            data += String(a) + ":0";
            kirim(data, "1");
        }
        function selaraskan() {
            var now = new Date();
            let tgl = now.getDate();
            let bulan = now.getMonth();
            bulan = bulan + 1;
            let tahun = now.getFullYear();
            let jam = now.getHours();
            let menit = now.getMinutes();
            let detik = now.getSeconds();
            let data = String(tahun) + "-"
            data += String(bulan) + "-";
            data += String(tgl) + ",";
            data += +String(jam) + ":";
            data += String(menit) + ":";
            data += String(detik);
            kirim(data, "1");
        }
        function teks() {
            let a = document.getElementById("teks").value;
            let b = document.getElementById("angka").value;
            let c = parseInt(b) - 1;
            data = String(c) + String(a);
            kirim(data, "2");
        }

        function setting() {
            let is = document.getElementById("is").value;
            let id = document.getElementById("id").value;
            let ia = document.getElementById("ia").value;
            let im = document.getElementById("im").value;
            let ii = document.getElementById("ii").value;
            let durasiAdzan = document.getElementById("durasiAdzan").value;
            let f_ws = document.getElementById("f_ws").value;
            let durasikutbah = document.getElementById("durasikutbah").value;
            let f_hjr = document.getElementById("f_hjr").value;
            let dispiqmh = document.getElementById("dispiqmh").checked;
            let dispimsyak = document.getElementById("dispimsyak").checked;
            let ringimsyak = document.getElementById("ringimsyak").checked;
            let disppuasa = document.getElementById("disppuasa").checked;
            let dispdhuha = document.getElementById("dispdhuha").checked;
            let dispterbit = document.getElementById("dispterbit").checked;
            let dispsplash = document.getElementById("dispsplash").checked;
            let datajws = {
                is: is,
                id: id,
                ia: ia,
                im: im,
                ii: ii,
                durasiAdzan: durasiAdzan,
                f_ws: f_ws,
                durasikutbah: durasikutbah,
                f_hjr: f_hjr,
                dispiqmh: dispiqmh,
                dispimsyak: dispimsyak,
                ringimsyak: ringimsyak,
                disppuasa: disppuasa,
                dispdhuha: dispdhuha,
                dispterbit: dispterbit,
                dispsplash: dispsplash
            };
            let data = JSON.stringify(datajws);
            kirim(data, "3");
        }

        function setBr() {
            let data = document.getElementById('cerah').value;
            kirim(data, "4")
        }

        function setVol() {
            let data = document.getElementById('volum').value;
            kirim(data, "5")
        }
    </script>
</body>

</html>
)rawliteral";

const char admin_html[] PROGMEM = R"rawliteral(
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
            color: #00FF00;
        }
        .topnav {
            overflow: hidden;
            background-color: #000000;
        }
        body {
            margin: 0;
            background-color: #151519;
            color: #fff;
        }
        .content {overflow: hidden;
            padding: 5px;
            max-width: 600px;
            margin: 0 auto;
            background-color: #00FF00;
        }
        .card {
            background-color: #151519;;
            box-shadow: 2px 2px 12px 1px rgba(0,255,0,1);
            padding-top:10px;
            padding-bottom:20px;
        }
        .button {
            padding: 10px 50px;
            font-size: 24px;
            text-align: center;
            outline: none;
            color: #fff;
            background: none;
            border: 3px solid #00ff00;
            border-radius: 5px;
            -webkit-touch-callout: none;
            -webkit-user-select: none;
            -khtml-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
            user-select: none;
            -webkit-tap-highlight-color: rgba(0,0,0,0);
        }
        .button:hover {
            background-color: #00ff00;
            color: #000;
        }
        .button:active {
            background-color: #ffffff;
            box-shadow: 2 2px #00ff00;
            transform: translateY(2px);
            color: #000;
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
            function initButton() {
                document.getElementById('set').addEventListener('click', set);
            }
            // =================================TERIMA========================================
            function prosesdata(x){
                var myObj = JSON.parse(x);
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
                kirim(data, "0");
            }
        </script>
    </body>
</html>
)rawliteral";
