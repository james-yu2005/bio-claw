

Servo myservo1; // Position servo on pin 11
Servo myservo2; // Continuous rotation servo on pin 9

void setup() {
  Serial.begin(9600);
  myservo1.attach(11);
  myservo2.attach(9);
  Serial.println("Ready. Enter values in Serial Monitor:");
  Serial.println("- For position servo: Enter angle (0-180)");
  Serial.println("- For rotation servo: Enter speed (-100 to 100)");
}

void posServo() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt();
    while(Serial.available() > 0) Serial.read();
    angle = constrain(angle, 0, 180);
    Serial.print("Moving position servo to angle: ");
    Serial.println(angle);
    myservo1.write(angle);
  }
}

void rotServo() {
  if (Serial.available() > 0) {
    int speedPercent = Serial.parseInt();
    int speedPWM;
    while(Serial.available() > 0) Serial.read();
    speedPWM = constrain(speedPercent, -100, 100);

    Serial.print("Setting rotation servo speed to: ");
    Serial.print(speedPWM);
    Serial.println("%");

    // Use your predefined servo values for specific speed ranges
    int servoVal;

    if (speedPercent == 0) {
      servoVal = 93; // stopped
    }
    else if (speedPercent > 0) {
      if (speedPercent > 50) {
        servoVal = 180; // fast forward
      } else {
        servoVal = 100; // slow forward
      }
    }
    else { // speedPercent < 0
      if (speedPercent < -50) {
        servoVal = 0; // fast reverse
      } else {
        servoVal = 80; // slow reverse
      }
    }

    Serial.print("Servo write value: ");
    Serial.println(servoVal);
    myservo2.write(servoVal);
  }
}
// new commit
void loop() {
  // For testing rotation servo, comment posServo and uncomment rotServo
  // posServo();
  rotServo();
  // delay(50);
}
