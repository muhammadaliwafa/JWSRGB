bool tarhim = false;

void runtarhim() {
  if (!tarhim) {
    Serial.println("********** TARHIM **********");
    myDFPlayer.playMp3Folder(1);
    tarhim = true;

  }
}

void setDF(){
  while (!myDFPlayer.begin(Serial)) {
  }
  delay(200);
  myDFPlayer.reset();
  delay(500);
  myDFPlayer.volume(p_atur[1]);
  delay(200);
  myDFPlayer.playMp3Folder(2);
}
