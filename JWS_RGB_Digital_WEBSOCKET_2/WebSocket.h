bool tndaBuzzer = false;
bool batas=false;

void notifyClients(String x, String y) {
  if(!batas){
    String pesan = y + x;
    ws.textAll(pesan);
  }
}

void sendJWS() {
  String pesan;
  char out[20];
  String hari = String(namaHari[rHar]);
  String bulan = String(namaBulan[rBul]);
  sprintf(out, "%s,%02d %s %d", hari, rTgl, bulan, rTah);
  pesan = String(out);
  for (int i = 0; i <= 7; i++) {
    sprintf(out, ";%02d:%02d:%02d", stimeInt[i][0], stimeInt[i][1], stimeInt[i][2]);
    pesan += String(out);
  }
  //  Serial.println(pesan);
  notifyClients(pesan, "2");
}

void kirimdata(fs::FS &fs, const char * path, String x) {
  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //      Serial.println("- failed to open file for reading");
    return;
  }
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);
  String pesan = String(buf.get());
  pesan = pesan.substring(0, pesan.indexOf("}") + 1);
  //  Serial.println(buf.get());
  //  Serial.println(pesan);
  notifyClients(pesan, x);
}

int keInt(String x, String y) {
  x = x.substring(0, x.indexOf(y));
  int z = x.toInt();
  return z;
}
void handleWaktu(String x) {
  uint16_t tahun = keInt(x, "-");
  x = x.substring(x.indexOf("-") + 1);
  uint8_t bulan = keInt(x, "-");
  x = x.substring(x.indexOf("-") + 1);
  uint8_t tgl = keInt(x, ",");
  x = x.substring(x.indexOf(",") + 1);
  uint8_t jam = keInt(x, ":");
  x = x.substring(x.indexOf(":") + 1);
  uint8_t menit = keInt(x, ":");
  x = x.substring(x.indexOf(":") + 1);
  uint8_t detik = x.toInt();
  Rtc.SetDateTime(RtcDateTime(tahun, bulan, tgl, jam, menit, detik));
  BacaRTC();
  updateJWS();
}

void handleText(String x) {
  gantiInfo(LITTLEFS, fileInfo, x);
    textJln=x.substring(1);
    pTeks = textJln.length();
}

void handleAtur(String x, bool y) {
  File file = LITTLEFS.open(fileAtur);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, buf.get());
  if(y){
    doc["cerah"] = x;
    dma_display->setBrightness8(x.toInt());
  }else{
    doc["volume"] = x;
    myDFPlayer.volume(x.toInt());
  }
  String pesan;
  serializeJson(doc, pesan);
  file.close();
  deleteFile(LITTLEFS, fileAtur);
  writeFile(LITTLEFS, fileAtur, pesan.c_str());
  readFileInfo(LITTLEFS, fileAtur);
}

void handleJWS(String x) {
  deleteFile(LITTLEFS, filejws);
  writeFile(LITTLEFS, filejws, x.c_str());
  readFileJWS(LITTLEFS, filejws);
}

void handleAdmin(String x) {
  deleteFile(LITTLEFS, fileAdmin);
  writeFile(LITTLEFS, fileAdmin, x.c_str());
  readFileAdmin(LITTLEFS, fileAdmin);
  updateJWS();
}

void handleWebSocketMessage(void *arg, unsigned char *data, size_t len) {
  batas=true;
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    //    Serial.print(data);
    char in[512];
    sprintf(in, "%s", data);
    if (String(in).substring(0, 1) == "#") {
      String a = String(in).substring(1, 2);
      String b = String(in).substring(3);
      b = b.substring(0, b.indexOf(";"));
      //      Serial.println(String(in));
      //      Serial.println(a);
      //      Serial.println(b);
      switch (a.toInt()) {
        case 0:
          handleAdmin(b);
          break;
        case 1:
          handleWaktu(b);
          sendJWS();
          break;
        case 2:
          handleText(b);
          break;
        case 3:
          handleJWS(b);
          break;
          break;
        case 4:
          handleAtur(b, true);
          break;
          break;
        case 5:
          handleAtur(b, false);
          break;
        default:
          break;
      }
      tndaBuzzer = true;
      time2 = millis();
    }
  }
  batas=false;
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, unsigned char *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      //      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      kirimdata(LITTLEFS, filejws, "3");
      sendJWS();
      kirimdata(LITTLEFS, fileAdmin, "0");
      break;
    case WS_EVT_DISCONNECT:
      //      Serial.printf("WebSocket client #%u disconnected\n", client->id());
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
  return String();
}

void setup_websocket() {
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    //    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  //  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/admin", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", admin_html, processor);
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}
