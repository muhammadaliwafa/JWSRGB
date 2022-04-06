void handleWaktu(String x){
  int a = x.length();
  char in[a];
  x.toCharArray(in,a);
  uint8_t jam;
  uint8_t menit;
  uint8_t detik;
  int n = sscanf(in, "%d:%d:%d", &jam, &menit, &detik);
  RtcDateTime now = Rtc.GetDateTime();
  uint16_t year = now.Year();
  uint8_t month = now.Month();
  uint8_t day = now.Day();
  Rtc.SetDateTime(RtcDateTime(year, month, day, jam, menit, detik));
  BacaRTC();
}

void handleText(String x){
  textJln=x;
  pTeks = textJln.length();
}

void notifyClients(String x) {
  ws.textAll(x);
}

void handleWebSocketMessage(void *arg, unsigned char *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//    Serial.print(data);
    char in[512];
    sprintf(in, "%s", data);
    String a=String(in).substring(0,1);
    String b=String(in).substring(2);
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
      default:
        break;
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, unsigned char *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
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
