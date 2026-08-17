// ── Pin definitions ──────────────────────────────────────
const int RPWM  = 5;   // Forward PWM
const int LPWM  = 6;   // Reverse PWM
const int R_EN  = 7;   // Forward enable
const int L_EN  = 8;   // Reverse enable
const int SW_L  = 2;   // Limit switch left  (NO, INPUT_PULLUP)
const int SW_R  = 3;   // Limit switch right (NO, INPUT_PULLUP)
const int POT   = A0;  // Potentiometer wiper

// ── Settings ─────────────────────────────────────────────
const int END_PAUSE_MS  = 2000; // Pause at end stop (ms)
const int MIN_PWM       = 40;   // Minimum PWM to keep motor moving
const int DEAD_ZONE_BOT = 100;  // Pot values 0–100 = full stop
const int IGNORE_MS     = 5000; // Ignore switches after trigger (ms)

// ── State ────────────────────────────────────────────────
int direction = 1; // 1 = forward, -1 = reverse

// ── Helpers ──────────────────────────────────────────────
void motorForward(int speed) {
  analogWrite(RPWM, speed);
  analogWrite(LPWM, 0);
}

void motorReverse(int speed) {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, speed);
}

void motorStop() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
}

void runMotor(int speed) {
  if (direction == 1) motorForward(speed);
  else                motorReverse(speed);
}

int readSpeed() {
  int potVal = analogRead(POT);
  if (potVal < DEAD_ZONE_BOT) return 0;
  int speed = map(potVal, DEAD_ZONE_BOT, 1023, MIN_PWM, 255);
  return constrain(speed, MIN_PWM, 255);
}

// ── Setup ────────────────────────────────────────────────
void setup() {
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(SW_L, INPUT_PULLUP);
  pinMode(SW_R, INPUT_PULLUP);

  digitalWrite(R_EN, HIGH); // Enable forward channel
  digitalWrite(L_EN, HIGH); // Enable reverse channel
}

// ── Loop ─────────────────────────────────────────────────
void loop() {

  int speed = readSpeed();

  // Stop if pot is in dead zone
  if (speed == 0) {
    motorStop();
    return;
  }

  // Check limit switches (HIGH = triggered, NO wiring)
  bool hitLeft  = (digitalRead(SW_L) == HIGH);
  bool hitRight = (digitalRead(SW_R) == HIGH);

  if (hitLeft || hitRight) {
    motorStop();
    delay(END_PAUSE_MS);    // Pause at end
    direction = -direction; // Flip direction once

    // Run for IGNORE_MS ignoring switches so carriage clears the striker
    unsigned long ignoreUntil = millis() + IGNORE_MS;
    while (millis() < ignoreUntil) {
      int s = readSpeed();
      if (s == 0) motorStop();
      else        runMotor(s);
    }
    return;
  }

  // Run motor in current direction at pot speed
  runMotor(speed);
}
