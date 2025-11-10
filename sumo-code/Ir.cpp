#include <Arduino.h>
#include "Ir.h"

IR::IR(const uint8_t p) {
  pin = p;
}

bool IR::value() {
  //delay(10);
  return analogRead(pin) > white;
} 

uint16_t IR::get_white() {
  return white;
}

void IR::set_white(int valor)
{
  white = valor;
}

int IR::calibrar_color(uint16_t pin_led)
{
  const int numLecturas = 150;
  long sumaLecturas = 0;
  int lecturaPromedio = 0;
  digitalWrite(pin_led, HIGH);

  for (int i = 0; i < numLecturas; i++)
  {
    sumaLecturas += analogRead(pin);
    delay(10);
  }

  lecturaPromedio = sumaLecturas / numLecturas;
  digitalWrite(pin_led, LOW);
  return lecturaPromedio;
}