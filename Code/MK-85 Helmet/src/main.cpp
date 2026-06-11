#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <DFRobot_DF2301Q.h>

#define WOKWI_SIMULATION true

static const uint8_t BUTTON_PIN = 2;
static const uint8_t LEFT_LED_PIN = 3;
static const uint8_t RIGHT_LED_PIN = 6;
static const uint8_t LEFT_SERVO_PIN = 9;
static const uint8_t RIGHT_SERVO_PIN = 10;

static const uint8_t OPEN_COMMAND_ID = 5;
static const uint8_t CLOSE_COMMAND_ID = 6;

static const int LEFT_OPEN_ANGLE = 18;
static const int LEFT_CLOSED_ANGLE = 92;
static const int RIGHT_OPEN_ANGLE = 162;
static const int RIGHT_CLOSED_ANGLE = 88;
static const uint8_t STEP_DELAY_MS = 12;
static const uint8_t STEP_SIZE = 1;

DFRobot_DF2301Q_I2C voiceModule(&Wire);
Servo leftServo;
Servo rightServo;

bool helmetIsOpen = false;
unsigned long lastButtonPress = 0;

void moveServoPair(int leftTarget, int rightTarget) {
  int leftCurrent = leftServo.read();
  int rightCurrent = rightServo.read();

  while (leftCurrent != leftTarget || rightCurrent != rightTarget) {
    if (leftCurrent < leftTarget) {
      leftCurrent = min(leftCurrent + STEP_SIZE, leftTarget);
    } else if (leftCurrent > leftTarget) {
      leftCurrent = max(leftCurrent - STEP_SIZE, leftTarget);
    }

    if (rightCurrent < rightTarget) {
      rightCurrent = min(rightCurrent + STEP_SIZE, rightTarget);
    } else if (rightCurrent > rightTarget) {
      rightCurrent = max(rightCurrent - STEP_SIZE, rightTarget);
    }

    leftServo.write(leftCurrent);
    rightServo.write(rightCurrent);
    delay(STEP_DELAY_MS);
  }
}

void openHelmet() {
  if (helmetIsOpen) {
    return;
  }
  
  digitalWrite(LEFT_LED_PIN, LOW);
  digitalWrite(RIGHT_LED_PIN, LOW);

  moveServoPair(LEFT_OPEN_ANGLE, RIGHT_OPEN_ANGLE);
  helmetIsOpen = true;
}

void closeHelmet() {
  if (!helmetIsOpen) {
    return;
  }

  moveServoPair(LEFT_CLOSED_ANGLE, RIGHT_CLOSED_ANGLE);
  
  digitalWrite(LEFT_LED_PIN, HIGH);
  digitalWrite(RIGHT_LED_PIN, HIGH);
  
  helmetIsOpen = false;
}

void handleVoiceCommand(uint8_t commandId) {
  switch (commandId) {
    case OPEN_COMMAND_ID:
      Serial.println(F("Voice command: open helmet"));
      openHelmet();
      break;
    case CLOSE_COMMAND_ID:
      Serial.println(F("Voice command: close helmet"));
      closeHelmet();
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);

  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  
  leftServo.write(LEFT_CLOSED_ANGLE);
  rightServo.write(RIGHT_CLOSED_ANGLE);
  digitalWrite(LEFT_LED_PIN, HIGH);
  digitalWrite(RIGHT_LED_PIN, HIGH);
  helmetIsOpen = false;

  Serial.println(F("Starting voice module..."));

  #if WOKWI_SIMULATION
    Serial.println(F("Use the green button to open/close the helmet."));
    Serial.println(F("Or, click the Terminal and type '5' (To Open) or '6' (TO Close)."));
  #else
    while (!voiceModule.begin()) {
      Serial.println(F("Voice module not found. Check I2C wiring or power."));
      delay(2000);
    }

    voiceModule.setVolume(5);
    voiceModule.setMuteMode(0);
    voiceModule.setWakeTime(20);

    Serial.println(F("Controller ready."));
    Serial.println(F("Say command ID 5 to open helmet and 6 to close."));
  #endif
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (millis() - lastButtonPress > 350) { 
      lastButtonPress = millis();
      Serial.println(F("DEBUG: Button pressed"));
      if (helmetIsOpen) {
        closeHelmet();
      } else {
        openHelmet();
      }
    }
  }

  uint8_t commandId = 0;

  #if WOKWI_SIMULATION
    if (Serial.available() > 0) {
      char incoming = Serial.read();
      if (incoming == '5') commandId = OPEN_COMMAND_ID;
      if (incoming == '6') commandId = CLOSE_COMMAND_ID;
    }
  #else
    commandId = voiceModule.getCMDID();
  #endif

  if (commandId != 0) {
    Serial.print(F("Recognized command ID: "));
    Serial.println(commandId);
    handleVoiceCommand(commandId);
  }
  
  delay(10);
}