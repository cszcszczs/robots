#include "HardwareSerial.h"
#include <Arduino.h>
#include "motors.h"

Motors::Motors(uint8_t PWA, uint8_t PWB, uint8_t AIN1, uint8_t AIN2, uint8_t BIN1, uint8_t BIN2) {
  pwa = PWA;
  pwb = PWB;
  ain1 = AIN1;
  ain2 = AIN2;
  bin1 = BIN1;
  bin2 = BIN2;
}

void Motors::init() {
  pinMode(pwa, OUTPUT);
  pinMode(pwb, OUTPUT);

  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);

  Serial.println("[M] Configured motor pins.");
}

void Motors::config_direction(uint8_t A, uint8_t B) {
  if (A) {
    A_direction[0] = ain2;
    A_direction[1] = ain1;
  }
  else {
    A_direction[0] = ain1;
    A_direction[1] = ain2;
  }

  if (B) {
    B_direction[0] = bin2;
    B_direction[1] = bin1;
  }
  else {
    B_direction[0] = bin1;
    B_direction[1] = bin2;
  }
}

void Motors::set_pwa(uint16_t vel) {
  analogWrite(pwa, vel);
}

void Motors::set_pwb(uint16_t vel) {
  analogWrite(pwb, vel);
}

void Motors::forward() {
  A_forward();
  B_forward();
}

void Motors::backward() {
  A_backward();
  B_backward();
}

void Motors::A_forward() {
  digitalWrite(A_direction[0], HIGH);
  digitalWrite(A_direction[1], LOW);
}

void Motors::B_forward() {
  digitalWrite(B_direction[0], HIGH);
  digitalWrite(B_direction[1], LOW);
}

void Motors::A_backward() {
  digitalWrite(A_direction[0], LOW);
  digitalWrite(A_direction[1], HIGH);
}

void Motors::B_backward() {
  digitalWrite(B_direction[0], LOW);
  digitalWrite(B_direction[1], HIGH);
}

void Motors::A_stop() {
  digitalWrite(A_direction[0], LOW);
  digitalWrite(A_direction[1], LOW);
}

void Motors::B_stop() {
  digitalWrite(B_direction[0], LOW);
  digitalWrite(B_direction[1], LOW);
}

void Motors::stop() {
  A_stop();
  B_stop();
}
