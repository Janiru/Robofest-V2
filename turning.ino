void turning(String dir) {
  if (dir == "right") {
    bool condition = true;
    mpower(190, -190);
    delay(100);
    while (condition == true) {
      mpower(190, -190);
      qtr.readLineBlack(sensorValues);
      if ((sensorValues[3] > 920 || sensorValues[4] > 920) && (sensorValues[0] < 300 && sensorValues [1] < 300) && (sensorValues[6] < 300 && sensorValues [7] < 300)) {
        condition = false;
      }
    }
  }
  else if (dir == "left") {
    bool condition = true;
    mpower(-190, 190);
    delay(100);
    while (condition == true) {
      mpower(-190, 190);
      qtr.readLineBlack(sensorValues);
      if ((sensorValues[3] > 920 || sensorValues[4] > 920) && (sensorValues[0] < 300 && sensorValues [1] < 300) && (sensorValues[6] < 300 && sensorValues [7] < 300)) {
        condition = false;

      }
    }
  }
}
