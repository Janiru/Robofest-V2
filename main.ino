#include <QTRSensors.h>
QTRSensors qtr;

#define SETPOINT    3500  // The goal for readLine (center)
#define KP          0.06   // The P value in PID
#define KD          0.6     // The D value in PID
#define L_MOTOR     8     // Left motor pin
#define R_MOTOR     3    // Right motor pin
#define MAX_SPEED   200   // The max speed to set motors to
#define SET_SPEED   200   // The goal speed to set motors to
#define MIN_SPEED   0     // The min speed to set motors to
#define NUM_SENSORS 8     // The number of QTR sensors
#define TIMEOUT     2500  // Timeout for the QTR sensors to go low
#define EMITTER_PIN 2     // Emitter pin for QTR sensor emitters

int LmF = 6;
int LmB = 7;
int LmS = 8;

int RmF = 4;
int RmB = 5;
int RmS = 3;

// PID **************************************
int lastError = 0;  // For storing PID error


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
  Serial.begin(9600);
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
  mpower(150 - adjust, 150 + adjust);

  if(sensorValues[7] > 920 || sensorValues[6] > 920){
    if(sensorValues[3] > 920 || sensorValues[4]> 920){
      mpower(200,-200);
      delay(260);
    }
  }


}

void mpower(int lm, int rm) {

  if (lm > 255) {
    lm = 255;
  }
  if (lm == 0) {
    digitalWrite(LmS, LOW);
  }

  if (lm > 0 && lm <= 255) {
    digitalWrite(LmF, HIGH);
    digitalWrite(LmB, LOW);
    analogWrite(LmS, lm);
  }

  else if (lm < 0) {
    digitalWrite(LmB, HIGH);
    digitalWrite(LmF, LOW);
    analogWrite(LmS, lm * -1);
  }

  if (rm > 255) {
    rm = 255;
  }

  if (rm == 0) {
    digitalWrite(RmS, LOW);
  }

  if (rm > 0 && rm <= 255) {
    digitalWrite(RmF, HIGH);
    digitalWrite(RmB, LOW);
    analogWrite(RmS, rm);
  }
  else if (rm < 0) {
    digitalWrite(RmB, HIGH);
    digitalWrite(RmF, LOW);
    analogWrite(RmS, rm * -1);
  }

}
