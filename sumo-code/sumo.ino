/*
  SENSOR IR
  negro - HIGH
  blanco - LOW
*/
#include "motors.h"
#include "Ir.h"

#define IR_A 11
#define IR_B 4
#define TRIG_PIN 2
#define ECHO_PIN 3

Motors motors = Motors(11, 6, 9, 10, 7, 8);
//Motors motors = Motors(11, 6, 9, 10, 7, 8);
IR sensores[8] = { IR(A0), IR(A1), IR(A2), IR(A3), IR(A4), IR(A5), IR(A6), IR(A7) };
unsigned int distance;

bool back = false;
bool search = false;
bool attack = false;
bool last_turn = false;
bool sum = false;
short count_turn = 0;

bool state = false;
bool pressed = false;

const int BTN_PIN = 4;

template <size_t N>
void calibrar_sensores(IR (&sensores)[N], uint16_t pin, uint8_t n) {
  for (size_t i = 0; i < n; i++) {
    int blanco = sensores[i].calibrar_color(pin);
    delay(1500);
    int negro = sensores[i].calibrar_color(pin);

    if (blanco < negro) {
      sensores[i].set_white(blanco);
      Serial.println(blanco);
    } else {
      sensores[i].set_white(negro);
      Serial.println(negro);
    }
  }
}


void setup() {
  Serial.begin(9600);

  /*pinMode(IR_A, INPUT);
  pinMode(IR_B, INPUT);*/
  pinMode(BTN_PIN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(12, HIGH);

  motors.init();
  motors.config_direction(1, 0);
  digitalWrite(12, HIGH);
  
  motors.set_pwa(130);
  motors.set_pwb(90);

  calibrar_sensores(sensores, 13, 2);
  for (int i = 0; i < 2; i++)
  {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensores[i].get_white());
  }

    // SON 5
  delay(1000);
}

void loop() {
  else {
    // go to backward
    if (!sensores[0].value() && !sensores[1].value()) {
      backward();
      attack = false;
      sum = 0;
    }
    // turn right
    else if (!sensores[0].value() && sensores[1].value()) {
      turn_right();
      attack = false;
      last_turn = true;
      sum++;
    }
    // turn left
    else if (sensores[0].value() && !sensores[1].value()) {
      turn_left();
      attack = false;
      last_turn = false;
      sum++;
    }
    // go to forward  
    else {
      ult_sensor();

      if (attack) {
        motors.set_pwa(255);
        motors.set_pwb(235);
        motors.forward();
        count_turn = 0;

        if (distance > 30) {
          attack = false;
        }
      }
      else if (enemy_in_distance()) {
        before_attack();
      }
      else {
        if (count_turn >= 3) {
          bool next = false;
          count_turn = 0;
          motors.set_pwa(150);
          motors.set_pwb(150);
          
          if (last_turn) {
            motors.A_forward();
            motors.B_backward();
            delay(100);
          }
          else {
            motors.B_forward();
            motors.A_backward();
            delay(100);
          }
        }
        else {
          motors.set_pwa(50); //100
          motors.set_pwb(60); // 90
          motors.forward();
        }
      }
    }
  }
}

void backward() {
  back = true;
  motors.set_pwa(140);
  motors.set_pwb(140);
  motors.backward();

  if (sensores[0].value() || sensores[1].value()) {
    motors.set_pwa(100);
    motors.set_pwb(100);
    if (sensores[0].value() && sensores[1].value()) {
      back = false;
    }
    else if (sensores[0].value()) {
      motors.A_backward();
      motors.B_forward();
      delay(100);
    }
    else {
      motors.A_forward();
      motors.B_backward();
      delay(100);
    }
  }
}

void turn_right() {
  motors.set_pwa(200);
  motors.set_pwb(200);
  motors.A_backward();
  motors.B_forward();
  delay(100);
}

void turn_left() {
  motors.set_pwa(200);
  motors.set_pwb(200);
  motors.B_backward();
  motors.A_forward();
  delay(100);
}

void ult_sensor() {
  delay(10);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  distance = pulseIn(ECHO_PIN, HIGH) * 0.034/2;
}

bool enemy_in_distance() {
  ult_sensor();
  return distance <= 20;
}

void before_attack() {
  motors.stop();
  uint16_t p = distance;
  delay(20);
  ult_sensor();

  if (p <= distance) attack = true;
  else search = true;
}