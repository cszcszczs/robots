const int velA = 6;
const int velB = 11;
const int Ain2 = 7;
const int Ain1 = 8;
const int stby = 12;
const int Bin1 = 9;
const int Bin2 = 10;

// sensores
const int sensorA0 = A0;

// valores sensores
int valorSensorA0;

// Definir variables para encontrar el promedio linea negra
const int numLecturas = 10; // Número de lecturas para calcular el promedio
float lineaNegra;

void setup() {
  // motores
  pinMode(velA, OUTPUT);
  pinMode(velB, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  // sensores
  pinMode(sensorA0, INPUT);

  analogWrite(velA, 255);
  analogWrite(velB, 255);
  digitalWrite(stby, HIGH);

  // encontrar el promedio de la linea negra
  lineaNegra = promedioLinea();
}

void loop() {
  // leer los valores de los sensores
  valorSensorA0 = analogRead(sensorA0);
  // Adelante
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, HIGH);

  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);

  delay(2000);

  //Atras
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);

  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  
  delay(2000);
  
}

// Funcion para encontrar la media de la linea negra
float promedioLinea() {
  int suma = 0;
  for(int i = 0; i < numLecturas; i++) {
    int lectura = analogRead(sensorA0);
    suma += lectura;
    delay(100);
  }

  return suma / numLecturas;
}