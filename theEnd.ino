void theEnd(){
  buzzer(1);
  mpower(200,200);
  delay(120);
  buzzer(0);
  mpower(-190,-190);
  delay(40);
  buzzer(1);
  delay(120);
  buzzer(0);
  while(true){
    mpower(0,0);
  }
}
