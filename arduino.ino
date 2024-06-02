#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "S";
const char* password = "Lolidkwtstpa5";

// Create a web server object
WebServer server(80);

String directionString = "";

// IR sensor pins
const int irSensor1Pin = 14; // Left IR sensor
const int irSensor2Pin = 13; // Middle IR sensor
const int irSensor3Pin = 12; // Right IR sensor

// Motor driver pins (assuming L298N)
const int in1 = 5;
const int in2 = 18;
const int in3 = 19;
const int in4 = 21;

// Function to handle incoming direction commands
void handleDirection() {
  if (server.hasArg("dir")) {
    String direction = server.arg("dir");
    if (direction == "F" && !directionString.endsWith("F")) {
      directionString += "F";
    } else if (direction != "F") {
      directionString += direction;
    }
    Serial.println("Direction received: " + directionString);
  }
  server.send(200, "text/plain", "Direction received");
}

// Function to initialize the motor driver pins
void setupMotors() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to move the robot backward
void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500); // Adjust this delay to complete the turn
  stopMotors();
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(500); // Adjust this delay to complete the turn
  stopMotors();
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Function to set up the Wi-Fi connection and web server
void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");

  // Set up routes
  server.on("/direction", HTTP_POST, handleDirection);

  // Start server
  server.begin();
  Serial.println("HTTP server started");

  // Initialize motor driver
  setupMotors();

  // Initialize IR sensor pins
  pinMode(irSensor1Pin, INPUT);
  pinMode(irSensor2Pin, INPUT);
  pinMode(irSensor3Pin, INPUT);
}

// Function to control the robot's movement based on the directionString and IR sensor input
void loop() {
  server.handleClient();

  // Read IR sensor input
  int irSensor1Value = digitalRead(irSensor1Pin);
  int irSensor2Value = digitalRead(irSensor2Pin);
  int irSensor3Value = digitalRead(irSensor3Pin);

  // If middle sensor detects black tape, read the next direction
  if (irSensor2Value == HIGH && directionString.length() > 0) {
    char direction = directionString.charAt(0);
    directionString.remove(0, 1); // Remove the first character

    switch (direction) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
    }
  }

  // If the left or right sensor detects black tape, adjust the robot to keep the black tape under the middle sensor
  if (irSensor1Value == HIGH) {
    // Adjust robot to the right
    turnRight();
    delay(200); // Adjust this delay as needed to align the robot
    moveForward();
  } else if (irSensor3Value == HIGH) {
    // Adjust robot to the left
    turnLeft();
    delay(200); // Adjust this delay as needed to align the robot
    moveForward();
  } else {
    // Continue moving forward if no adjustment is needed
    moveForward();
  }

  delay(100); // Adjust this delay for the main loop
}

