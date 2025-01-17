git 
#include <QTRSensors.h>
#include <Servo.h>

QTRSensors qtr;

#define SETPOINT    3500
#define KP          0.0675
#define KD         2
#define NUM_SENSORS 8
#define TIMEOUT     2500
int LmF = 6;
int LmB = 7;
int LmS = 8;

int RmF = 4;
int RmB = 5;
int RmS = 3;



int baseSpeed = 190;
int maxSpeed = 210;
int minVals[] = {412, 464, 464 , 420, 420, 560, 560, 652};

// PID **************************************
int lastError = 0;  // For storing PID error

/*Junction turn, decision taking variables*/

const bool LeftOrRight = true;
// True means Right is prioritized, False means Left is prioratized

unsigned int sensorValues[NUM_SENSORS];   // For sensor values of readLine()
bool first = true;

//servo positions

int servoRight = 0;
int servoLeft = 180;
int servoUp = 7;
int servoDown = 89;
bool boxPicked = false;
Servo bottomServo, topServo;
void setup() {

  topServo.attach(12);
  bottomServo.attach(11);

  topServo.write(servoUp);
  bottomServo.write(servoRight);
  delay(1000);
  servoDetach();
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
  Serial.begin(9600);

}

void loop() {

  unsigned int linePos = qtr.readLineBlack(sensorValues);
  while (first == true && sensorValues[0] > 920 && sensorValues[1] > 920 && sensorValues[2] > 920 &&
         sensorValues[3] > 920 && sensorValues[4] > 920 && sensorValues[5] > 920 && sensorValues[6] > 920 && sensorValues[7] > 920) {
    qtr.readLineBlack(sensorValues);
    mpower(240, 240);
    delay(80);
  } first = false;
  int error = SETPOINT - linePos;
  int adjust = error * KP + KD * (error - lastError);
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
    Serial.println("dead end");
    mpower(210, -210);
    delay(5);
  }
  /******************** Right Turn  ********************/

  if (sensorValues[6] > 920 || sensorValues[7] > 920) {
    if (sensorValues[0] < 300 && sensorValues[1] < 300) {
      if ( sensorValues[3] > 920 || sensorValues[4] > 920) {
        turnRight();
      }
    }
  }

  /******************** Left Turn if front is null  ********************/

  if (sensorValues[0] > 920 || sensorValues[1] > 920) {
    if (sensorValues[5] < 300 && sensorValues[6] < 300) {
      if ( sensorValues[3] > 920 || sensorValues[4] > 920) {
        turnLeft();
      }
    }
  }
  /******************** T junction ********************/

  if ((sensorValues[3] > 920 || sensorValues[4] > 920) && (sensorValues[0] > 920 || sensorValues[1] > 920 || sensorValues[2] > 920) && (sensorValues[5] > 920 || sensorValues[6] > 920 || sensorValues[7] > 920)) {
    tJunction();
  }

  /*************** The END ******************/

  if (sensorValues[0] > 920 && sensorValues[7] > 920) {
    if (sensorValues[1] > 920 && sensorValues[6] > 920) {
      if (sensorValues[3] < 300 || sensorValues[4] < 300) {
        theEnd();
      }
    }
  }

}
