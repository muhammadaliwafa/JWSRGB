void notifyClients(String x, String y) {
  String pesan = y+x;
  ws.textAll(pesan);
}

void kirimdata(fs::FS &fs, const char * path){
  File file = fs.open(path);
  if(!file || file.isDirectory()){
      Serial.println("- failed to open file for reading");
      return;
  }
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);
  String pesan = String(buf.get());
  pesan = pesan.substring(0,pesan.indexOf("}")+1);
  Serial.println(buf.get());
  Serial.println(pesan);
  notifyClients(pesan, "1");
}

void handleWaktu(String x){
  int a = x.length();
  char in[a];
  x.toCharArray(in,a);
  uint8_t tahun;
  uint8_t bulan;
  uint8_t tgl;
  uint8_t jam;
  uint8_t menit;
  uint8_t detik;
  int n = sscanf(in, "%d-%d-%d,%d:%d:%d", &tahun, &bulan, &tgl, &jam, &menit, &detik);
  Rtc.SetDateTime(RtcDateTime(tahun, bulan, tgl, jam, menit, detik));
  BacaRTC();
}

void handleText(String x){
  gantiInfo(LITTLEFS, fileInfo, x);
//  textJln=x.substring(1);
  pTeks = textJln.length();
}

void handleSetting(String x){
  deleteFile(LITTLEFS, fileAdmin);
  writeFile(LITTLEFS, fileAdmin,x.c_str());
  readFileAdmin(LITTLEFS, fileAdmin);
}

void handleWebSocketMessage(void *arg, unsigned char *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//    Serial.print(data);
    char in[512];
    sprintf(in, "%s", data);
    if(String(in).substring(0,1)=="#"){
      String a=String(in).substring(1,2);
      String b=String(in).substring(3);
      b = b.substring(0, b.indexOf(";"));
      Serial.println(String(in));
      Serial.println(a);
      Serial.println(b);
      switch(a.toInt()){
        case 0:
          handleWaktu(b);
          break;
        case 1:
          handleText(b);
          break;
        case 2:
          handleSetting(b);
          break;
        default:
          break;
      }
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, unsigned char *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      kirimdata(LITTLEFS, fileAdmin);
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var) {
  //  Serial.println(var);
  //  if(var == "STATE"){
  //    if (ledState){
  //      return "ON";
  //    }
  //    else{
  //      return "OFF";
  //    }
  //  }
  return String();
}

void setup_websocket() {
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}
