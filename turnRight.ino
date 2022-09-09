bool conditionRight = true;

void turnRight() {
  if (LeftOrRight == true) {
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
      delay(5);
    }
  }
  else if (LeftOrRight == false) {
    mpower(-190, -190);
    delay(30);
    mpower(0, 0);

    qtr.readLineBlack(sensorValues);
    if (sensorValues[0] < 300 && sensorValues[1] < 300 && sensorValues[2] < 300 &&
        sensorValues[3] < 300 && sensorValues[4] < 300 && sensorValues[5] < 300 &&
        sensorValues[6] < 300 && sensorValues[7] < 300) {
      mpower(200, -200);
      delay(300);
    } else {
      mpower(200, 200);
      delay(100);
    }
  }


}
