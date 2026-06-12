#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <DFRobot_DF2301Q.h>

// change this to false when running on real hardware
#define SIM_MODE true

// -- pin defs --
#define BTN    2
#define LED_L  3
#define LED_R  6
#define SRV_L  9
#define SRV_R  10

// voice cmd IDs (from DF2301Q command table)
#define VC_OPEN  5
#define VC_CLOSE 6

// these angles took forever to dial in, don't change without re-testing
#define L_OPN  18
#define L_CLZ  92
#define R_OPN  162
#define R_CLZ  88

// too fast and the helmet jams, 12ms felt right after testing
#define SERVO_DLY 12

Servo sL, sR;
DFRobot_DF2301Q_I2C mic(&Wire);

bool hlmtOpen = false;
unsigned long btnDebounce = 0;

// sweeps both servos 1 deg at a time so it doesnt snap
// could probably speed this up but 12ms works fine
void runServos(int targL, int targR) {
  int cL = sL.read();
  int cR = sR.read();

  while (cL != targL || cR != targR) {
    if (cL < targL) cL++;
    else if (cL > targL) cL--;

    if (cR < targR) cR++;
    else if (cR > targR) cR--;

    sL.write(cL);
    sR.write(cR);
    delay(SERVO_DLY);
  }
}

void doOpen() {
  if (hlmtOpen) return;
  digitalWrite(LED_L, LOW);
  digitalWrite(LED_R, LOW);
  runServos(L_OPN, R_OPN);
  hlmtOpen = true;
}

void doClose() {
  if (!hlmtOpen) return;
  runServos(L_CLZ, R_CLZ);
  // LEDs back on once closed
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_R, HIGH);
  hlmtOpen = false;
}

// called from both button and voice paths
void execCmd(uint8_t id) {
  if (id == VC_OPEN) {
    Serial.println("cmd: open");
    doOpen();
  } else if (id == VC_CLOSE) {
    Serial.println("cmd: close");
    doClose();
  }
  // anything else just gets ignored
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED_L, OUTPUT);
  pinMode(LED_R, OUTPUT);

  sL.attach(SRV_L);
  sR.attach(SRV_R);

  // boot into closed state
  sL.write(L_CLZ);
  sR.write(R_CLZ);
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_R, HIGH);
  hlmtOpen = false;

#if SIM_MODE
  Serial.println("wokwi sim - btn or type 5/6 in terminal");
#else
  Serial.println("init mic...");
  int tries = 0;
  while (!mic.begin()) {
    tries++;
    Serial.print("mic not found, attempt ");
    Serial.println(tries);
    delay(2000);
    if (tries > 5) {
      Serial.println("giving up on mic, continuing without voice");
      break;
    }
  }
  mic.setVolume(5);
  mic.setMuteMode(0);
  mic.setWakeTime(20);
  Serial.println("ready");
#endif
}

void loop() {
  bool btnHeld = digitalRead(BTN) == LOW;
  if (btnHeld && millis() - btnDebounce > 350) {
    btnDebounce = millis();
    hlmtOpen ? doClose() : doOpen();
  }

  uint8_t incoming = 0;

#if SIM_MODE
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == '5') incoming = VC_OPEN;
    else if (ch == '6') incoming = VC_CLOSE;
  }
#else
  incoming = mic.getCMDID();
#endif

  if (incoming) execCmd(incoming);

  delay(10);
}