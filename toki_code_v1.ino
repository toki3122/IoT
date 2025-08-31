#include <QTRSensors.h>

// Constants
const int baseSpeed = 100;  // Base speed for N20 motors
const int maxSpeed = 255;   // Maximum PWM value
const int integralLimit = 1000; // Limit for PID integral term

// Motor control pins (L298D)
#define left_motor_speed     10  // ENA
#define right_motor_speed    5   // ENB
#define right_motor_forward  8   // IN1
#define right_motor_backward 9   // IN2
#define left_motor_forward   6   // IN3
#define left_motor_backward  7   // IN4

// Button and LED pins
#define button_calibration 2
#define led_green 12
#define led_red 13

// PID constants (tuned for better line following)
// - Kp: Increase (e.g., 0.3) if robot doesn't turn enough; decrease (e.g., 0.1) if it oscillates.
// - Ki: Increase (e.g., 0.002) if robot drifts slightly off-center; keep low to avoid overshoot.
// - Kd: Increase (e.g., 0.5) if robot oscillates; decrease (e.g., 0.2) if sluggish.
float Kp = 0.1;    // Stronger correction for deviations
float Ki = 0;  // Slight integral for steady-state errors
float Kd = 0.5;    // Reduced to allow faster response
int lastError = 0;
int I = 0;

// QTR sensor setup
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

// Button state and debounce
bool calibrated = false;
bool running = false;
unsigned long lastCalibPress = 0;
unsigned long lastStartPress = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(9600);
  Serial.println("Robot initializing...");

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A6, A7}, SensorCount);

  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(button_calibration, INPUT_PULLUP);

  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  Serial.println("Testing motors...");
  motor(100,100);
  delay(1000);
  motor(-100,-100);
  Serial.println("Motor test complete");
}

void loop() {
  static bool lastCalibButton = HIGH;
  static bool lastStartButton = HIGH;

  bool currCalibButton = digitalRead(button_calibration);
  bool currStartButton = digitalRead(button_start);
  unsigned long currentTime = millis();

  // Calibration
  if (lastCalibButton == HIGH && currCalibButton == LOW &&
      (currentTime - lastCalibPress > debounceDelay) && !calibrated) {
    lastCalibPress = currentTime;
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, LOW);
    Serial.println("Calibrating... Move robot over line and background.");
    for (uint16_t i = 0; i < 400; i++) {
      qtr.calibrate();
      delay(5);
    }
    calibrated = true;
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, HIGH);
    Serial.println("Calibration complete");
    for (uint8_t i = 0; i < SensorCount; i++) {
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": Min=");
      Serial.print(qtr.calibrationOn.minimum[i]);
      Serial.print(", Max=");
      Serial.println(qtr.calibrationOn.maximum[i]);
    }
  }

  // Start/Stop
  if (lastStartButton == HIGH && currStartButton == LOW &&
      (currentTime - lastStartPress > debounceDelay) && calibrated) {
    lastStartPress = currentTime;
    running = !running;
    if (running) {
      Serial.println("Robot started");
    } else {
      motor(0, 0);
      Serial.println("Robot stopped");
    }
  }

  lastCalibButton = currCalibButton;
  lastStartButton = currStartButton;

  // Main control
  if (running && calibrated) {
    // Read sensors and get line position
    uint16_t positionLine = qtr.readLineWhite(sensorValues);
    // Debug sensor values
    Serial.print("Sensors: ");
    for (int i = 0; i < SensorCount; i++) {
      Serial.print(sensorValues[i]);
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("Line position: ");
    Serial.println(positionLine);

    // Line detection: check if any sensor is on the line
    bool lineDetected = false;
    for (int i = 0; i < SensorCount; i++) {
      int threshold = (qtr.calibrationOn.minimum[i] + qtr.calibrationOn.maximum[i]) / 2;
      if (sensorValues[i] < threshold) { // for white line, lower values
        lineDetected = true;
        break;
      }
    }

    if (!lineDetected) {
      motor(0,0);
      Serial.println("No line detected");
    } else {
      if (abs(lastError) < 300 && is_junction()) {
        handle_t_junction();
      } else {
        PID_control(positionLine);
      }
    }
  }
}

bool is_junction() {
  static int junctionCount = 0;
  int activeSensors = 0;
  for (int i = 0; i < SensorCount; i++) {
    int threshold = (qtr.calibrationOn.minimum[i] + qtr.calibrationOn.maximum[i]) / 2;
    if (sensorValues[i] > threshold) {
      activeSensors++;
    }
  }
  if (activeSensors >= 4) {
    junctionCount++;
    if (junctionCount >= 2) {
      junctionCount = 0;
      Serial.println("Junction detected");
      return true;
    }
  } else {
    junctionCount = 0;
  }
  return false;
}

void PID_control(uint16_t positionLine) {
  int error = positionLine - 2500; // Corrected error calculation
  if (abs(error) < 50) I = 0; // Reset integral near center
  int P = error;
  I += error;
  I = constrain(I, -integralLimit, integralLimit);
  int D = error - lastError;
  lastError = error;

  int adj = P * Kp + I * Ki + D * Kd;
  int motorSpeedA = baseSpeed + adj;
  int motorSpeedB = baseSpeed - adj;

  motorSpeedA = constrain(motorSpeedA, -maxSpeed, maxSpeed);
  motorSpeedB = constrain(motorSpeedB, -maxSpeed, maxSpeed);
  motor(motorSpeedA, motorSpeedB);

  // Debug PID output
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print(", Adj: ");
  Serial.print(adj);
  Serial.print(", LeftSpeed: ");
  Serial.print(motorSpeedA);
  Serial.print(", RightSpeed: ");
  Serial.println(motorSpeedB);
}

void handle_t_junction() {
  delay(200);
  qtr.read(sensorValues);

  int left = sensorValues[0] + sensorValues[1];
  int center = sensorValues[2] + sensorValues[3];
  int right = sensorValues[4] + sensorValues[5];

  if (left > right && left > center) {
    Serial.println("Turning left");
    motor(-100, 100);
    while (abs(qtr.readLineWhite(sensorValues) - 2500) > 500) {
      // Continue reading sensors
    }
  } else if (right > left && right > center) {
    Serial.println("Turning right");
    motor(100, -100);
    while (abs(qtr.readLineWhite(sensorValues) - 2500) > 500) {
      // Continue reading sensors
    }
  } else {
    Serial.println("Going straight");
    motor(baseSpeed, baseSpeed);
    delay(250);
  }
}

void motor(int a, int b) {
  if (a >= 0) {
    digitalWrite(left_motor_forward, HIGH);
    digitalWrite(left_motor_backward, LOW);
  } else {
    a = -a;
    digitalWrite(left_motor_forward, LOW);
    digitalWrite(left_motor_backward, HIGH);
  }

  if (b >= 0) {
    digitalWrite(right_motor_forward, HIGH);
    digitalWrite(right_motor_backward, LOW);
  } else {
    b = -b;
    digitalWrite(right_motor_forward, LOW);
    digitalWrite(right_motor_backward, HIGH);
  }

  analogWrite(left_motor_speed, a);
  analogWrite(right_motor_speed, b);
}