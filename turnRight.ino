bool conditionRight = true;

void turnRight() {
  mpower(-190, -190);
  delay(60);
  mpower(160, -160);
  delay(120);
  while (conditionRight == true) {
    qtr.readLineBlack(sensorValues);
    if (sensorValues[0] < 300 && sensorValues[7] < 300) {
      if (sensorValues[3] > 920 || sensorValues[4] > 920) {
        conditionRight = false;
      }
    }
    mpower(200, -200);
    delay(10);
  }
}
