/**
   NoU3_servo_test
   by joshua-8, MIT License
   This program can be used to control servos connected to an Alfredo Systems NoU3
   This example is based on the Alfredo NoU3 MotorParty example
   The NoU3 documentation and tutorials can be found at https://alfredo-nou3.readthedocs.io/

    User Manual:
        select which servo to control using a, s, d, or f
        enter angles between 0 and 100 degrees
        make sure your serial monitor is set to add newlines to each sent message, and is 115200 baud

*/

#include <Alfredo_NoU3.h>

const byte NUM_SERVOS = 4;

int servoVal[NUM_SERVOS];

String inString = "";

int whichServoIsSelected = 0;

//NoU_Motor motor1(1);
//NoU_Motor motor2(2);
//NoU_Motor motor3(3);
//NoU_Motor motor4(4);
//NoU_Motor motor5(5);
//NoU_Motor motor6(6);
//NoU_Motor motor7(7);
//NoU_Motor motor8(8);

NoU_Servo servo1(1);
NoU_Servo servo2(2);
NoU_Servo servo3(3);
NoU_Servo servo4(4);

bool writeServoNumber(int servoNumber, int servoAngle) {
  switch (servoNumber) {
    case 1:
      servo1.write(servoAngle);
      break;
    case 2:
      servo2.write(servoAngle);
      break;
    case 3:
      servo3.write(servoAngle);
      break;
    case 4:
      servo4.write(servoAngle);
      break;
  default: // not a valid servo
      return false;
  }
  return true;
}

void setup() {
  NoU3.begin();
  Serial.begin(115200);

  // initialize values
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoVal[i] = 90;
  }

  delay(5000);
  Serial.println("Welcome to the nou3 servo tester https://github.com/joshua-8/NoU3_servo_test");
  Serial.println("select which servo to control using a, s, d, or f");
  Serial.println("enter angles between 0 and 100 degrees");
  Serial.println("send a newline to make the servo move");

}

void loop() {

  NoU3.setServiceLight(LIGHT_ENABLED);

  while (Serial.available() > 0) {
    int inChar = Serial.read();

    bool anythingSelected = false;
    if (inChar == 'a') {
      whichServoIsSelected = 1;
      anythingSelected = true;
    }
    if (inChar == 's') {
      whichServoIsSelected = 2;
      anythingSelected = true;
    }
    if (inChar == 'd') {
      whichServoIsSelected = 3;
      anythingSelected = true;
    }
    if (inChar == 'f') {
      whichServoIsSelected = 4;
      anythingSelected = true;
    }
    if (anythingSelected) {
      Serial.print("servo ");
      Serial.print(whichServoIsSelected);
      Serial.println(" selected");
      break;
    }

    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar == '\n') {
      int inputValue = inString.toInt();
      if (inputValue >= 0 && inputValue <= 180) {
        if (writeServoNumber(whichServoIsSelected, inputValue)) {
          Serial.print("setting servo ");
          Serial.print(whichServoIsSelected);
          Serial.print(" to ");
          Serial.print(inputValue);
          Serial.println(" degrees");
        } else {
          Serial.print("servo ");
          Serial.print(whichServoIsSelected);
          Serial.println(" is not a valid servo");
        }
      }
      inString = "";
    }
  }

  delay(1);
}
