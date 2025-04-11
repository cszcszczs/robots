// pines para los sensores infrarojos
const int sensorDer = A0;
const int sensorIzq = A1;
const int sensorAtras = A2;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin:
  int sensorValueDer = analogRead(sensorDer);
  // print out the value you read:
  Serial.print(sensorValueDer);
  Serial.print(" ");

  int sensorValueIzq = analogRead(sensorIzq);
  Serial.print(sensorValueIzq);
  Serial.print(" ");

  int sensorValueAtras = analogRead(sensorValueAtras);
  Serial.print(sensorValueAtras);
  Serial.println(" ");
}
