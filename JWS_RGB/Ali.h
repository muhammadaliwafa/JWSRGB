bool kdp;

void kedip() {
  static uint32_t   timerSave, lastSecond;
  uint32_t          nowmilis = millis();
  if (lastSecond != rDet) {
    lastSecond = rDet;
    kdp = true;
    timerSave = nowmilis;
  }
  if ((nowmilis - timerSave) > 500) {
    kdp = false;
  }
}
