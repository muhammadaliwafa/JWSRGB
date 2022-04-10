bool tarhim = true;

void runtarhim(int x) {
  if (tarhim) {
    if(x!=0 and x!=2 and x!=3){
      myDFPlayer.playMp3Folder(1);
    }
    tarhim = false;
//    digitalWrite(buzzer, HIGH);
  }
}

void setDF(){
  while (!myDFPlayer.begin(Serial)) {
  }
  delay(200);
  myDFPlayer.reset();
  delay(500);
  myDFPlayer.volume((p_atur.volume)-'0');
  delay(10);
//  myDFPlayer.playMp3Folder(1);
}
