
#include <QTRSensors.h>
QTRSensors qtr;

#define SETPOINT    3500
#define KP          0.0675
#define KD         1.8
#define NUM_SENSORS 8
#define TIMEOUT     2500
int LmF = 6;
int LmB = 7;
int LmS = 8;

int RmF = 4;
int RmB = 5;
int RmS = 3;

int buzzer = 11;

int baseSpeed = 190;
int maxSpeed = 230;
int minVals[] = {412, 464, 464 , 420, 420, 560, 560, 652};

// PID **************************************
int lastError = 0;  // For storing PID error

/*Junction turn, decision taking variables*/

const bool LeftOrRight = false;
// True means Right is prioritized, False means Left is prioratized

unsigned int sensorValues[NUM_SENSORS];   // For sensor values of readLine()
void setup() {
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) {
    A7, A6, A5, A4, A3, A2, A1, A0
  }, NUM_SENSORS);
  qtr.setEmitterPin(2);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);


  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 200; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
  // Initialize Pins
  pinMode(LmF, OUTPUT);
  pinMode(LmB, OUTPUT);
  pinMode(LmS, OUTPUT);

  pinMode(RmF, OUTPUT);
  pinMode(RmB, OUTPUT);
  pinMode(RmS, OUTPUT);

  pinMode(buzzer, HIGH);

  Serial.begin(9600);

  /****** Hard coded calibrations ******/

  //  for (uint8_t i = 0; i < 8; i++)
  //  {
  //    qtr.calibrationOn.minimum[i] = minVals[i];
  //    qtr.calibrationOn.maximum[i] = 2500;
  //  }
  /****** Hard coded calibrations ******/

}

void loop() {
  // Take a reading
  unsigned int linePos = qtr.readLineBlack(sensorValues);

  // Compute the error
  int error = SETPOINT - linePos;

  // Compute the motor adjustment
  int adjust = error * KP + KD * (error - lastError);

  // Record the current error for the next iteration
  lastError = error;
  mpower(baseSpeed - adjust, baseSpeed + adjust);

  /******************** Increasing Speed when line is centered********************/

  if (linePos > 3000 && linePos < 4000) {
    baseSpeed = maxSpeed;
  }
  else {
    baseSpeed = 190;
  }



  /******************** Dead End ********************/

  if (sensorValues[0] < 300 && sensorValues[1] < 300 && sensorValues[2] < 300 &&
      sensorValues[3] < 300 && sensorValues[4] < 300 && sensorValues[5] < 300 &&
      sensorValues[6] < 300 && sensorValues[7] < 300) {
    mpower(230, -230);
    delay(10);
  }

  /******************** Right Turn  ********************/

  if (sensorValues[6] > 920 || sensorValues[7] > 920) {
    if (sensorValues[0] < 300 || sensorValues[1] < 300) {
      if ( sensorValues[3] > 920 || sensorValues[4] > 920) {
        turnRight();
      }
    }
  }

  /******************** Left Turn if front is null  ********************/

  if (sensorValues[0] > 920 || sensorValues[1] > 920) {
    if (sensorValues[6] < 300 || sensorValues[7] < 300) {
      if ( sensorValues[3] > 920 || sensorValues[4] > 920) {
        turnLeft();
      }
    }
  }
  /******************** T junction ********************/

  if (sensorValues[0] >920 && sensorValues[1] >920 && sensorValues[2] >920 &&
      sensorValues[3] >920 && sensorValues[4] >920 && sensorValues[5] >920 &&
      sensorValues[6] >920 && sensorValues[7] >920) {
    tJunction();
  }

}
