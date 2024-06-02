const int irSensor1Pin = 14; // Left IR sensor
const int irSensor2Pin = 13; // Middle IR sensor
const int irSensor3Pin = 12; // Right IR sensor
/*
5-R
18-P
19-B
21-Y

IN1 - P
IN2 - R
IN3 - Y
IN4 - B

5 - IN2
18 - IN1
19 - IN4
21 - IN3
*/
const int in1 = 5;  // Motor A (Left motor) direction control
const int in2 = 18; // Motor A (Left motor) direction control
const int in3 = 19; // Motor B (Right motor) direction control
const int in4 = 21; // Motor B (Right motor) direction control

//String directionString = "FFRFFLFF"; // Example constant direction string
String directionString = "FRF"; // Example constant direction string

void setupMotors() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void moveForward() {
  digitalWrite(in2, LOW);
  speedControl(in1, in3);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  speedControl(in2, in4);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  speedControl(in2, in3);
  digitalWrite(in4, LOW);
  //delay(100); // Adjust this delay to make the turn less abrupt
  //moveForward(); // Move forward slightly to align with the tape
  //delay(100);
  //stopMotors();
}

void turnRight() {
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  speedControl(in1, in4);
  //delay(100); // Adjust this delay to make the turn less abrupt
  //moveForward(); // Move forward slightly to align with the tape
  //delay(100);
  //stopMotors();
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void speedControl(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
}

void setup() {
  Serial.begin(115200);
  
  // Initialize motor driver
  setupMotors();
  pinMode(26, OUTPUT);
  pinMode(33,OUTPUT);

  // Initialize IR sensor pins
  pinMode(irSensor1Pin, INPUT);
  pinMode(irSensor2Pin, INPUT);
  pinMode(irSensor3Pin, INPUT);
}

void loop() {
  static int directionIndex = 0;
  analogWrite(26, 140);
  analogWrite(33, 140);

  bool sensor1 = digitalRead(irSensor1Pin) == LOW;
  bool sensor2 = digitalRead(irSensor2Pin) == LOW;
  bool sensor3 = digitalRead(irSensor3Pin) == LOW;
  // Stop the robot if all directions have been processed
  if (directionIndex >= directionString.length()) {
    stopMotors();
    return;
  }
  int check = 4*sensor1 + 2*sensor2 + sensor3;
  switch(check){
    case 0b111:
     stopMotors();
    break;
    case 0b110:
      turnRight();
    break;
    case 0b011:
      turnLeft();
    break;
    case 0b101:
      moveForward();
    break;
    default:
      moveForward();
    break;
  }
  delay(16);
  stopMotors();
  /*
  if (!irSensor1White || !irSensor3White) {
    if (directionIndex < directionString.length()) {
      char direction = directionString.charAt(directionIndex);
      directionIndex++;

      if ((direction == 'L' && !irSensor3White) || (direction == 'R' && !irSensor1White)) {
        // If the direction matches the IR sensor detection, turn
        if (direction == 'L') {
          turnLeft();
        } else if (direction == 'R') {
          turnRight();
        }
        // Ensure the middle IR sensor is back on the black tape after turning
        while (irSensor2White) {
          moveForward();
          delay(100);
        }
        stopMotors();
      } else {
        // Otherwise, continue straight
        moveForward();
      }
    }

*/ 

   // Adjust this delay for the main loop
}
