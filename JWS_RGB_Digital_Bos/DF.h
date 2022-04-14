bool tarhim = true;

void runtarhim(int x) {
  if (tarhim) {
    //    Serial.println(x);
    if ((x != 0) && (x != 2) && (x != 3)) {
      //      Serial.println("DF...DF");
      myDFPlayer.playMp3Folder(1);
    }
    tarhim = false;
    digitalWrite(buzzer, HIGH);
  }
}

void setDF() {
  while (!myDFPlayer.begin(Serial)) {
  }
  delay(10);
  myDFPlayer.volume(30);
  delay(10);
  myDFPlayer.playMp3Folder(2);
}
