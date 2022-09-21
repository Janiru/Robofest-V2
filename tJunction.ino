void tJunction() {
  mpower(-190, -190);
  delay(60);
  mpower(0, 0);
  delay(50);
  qtr.readLineBlack(sensorValues);
  if (sensorValues[0] > 920 || sensorValues[1] > 920) {
    if (sensorValues[6] > 920 || sensorValues[7] > 920) {
      if (sensorValues[3] > 920 || sensorValues[4] > 920) {
        Serial.println("Box");
        mpower(0, 0);
        delay(6000);
      }
    }
  }
  else {
    Serial.println("T junc");
    if (LeftOrRight == true) {
      mpower(190, -190);
      delay(250);
    }
    else {
      mpower(-190, 190);
      delay(250);
    }
  }
}
