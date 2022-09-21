bool conditionLeft = true;

void turnLeft() {
  if (LeftOrRight == true) {
    mpower(-190, -190);
    delay(40);
    mpower(0, 0);

    qtr.readLineBlack(sensorValues);
    if (sensorValues[0] < 300 && sensorValues[1] < 300 && sensorValues[2] < 300 &&
        sensorValues[3] < 300 && sensorValues[4] < 300 && sensorValues[5] < 300 &&
        sensorValues[6] < 300 && sensorValues[7] < 300) {

      mpower(-200, 200);
      delay(250);
    } else {
      mpower(200, 200);
      delay(100);
    }
  }
  else if (LeftOrRight == false) {
    mpower(-190, -190);
    delay(40);
    mpower(-200, 200);
    delay(250);
  }
}
