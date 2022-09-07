void buzzer(int val){
  if(val == 1){
    digitalWrite(buzzer1,HIGH);
  }
  if(val == 0){
    digitalWrite(buzzer1,LOW);
  }
}
