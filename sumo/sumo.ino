// pines para los sensores infrarojos
const int sensor1 = 2;
const int sensor2 = 3;

// pines sensor ultrasonico
const int triggerPin = 4;
const int echoPin = 5;

// pines de los motores
const int velA = 6;
const int velB = 11;
const int Ain2 = 7;
const int Ain1 = 8;
const int stby = 12;
const int Bin1 = 9;
const int Bin2 = 10;

// velocidad maxima de los motores
const int velocidadMaxima = 150;

// Definir variables para los valores de los sensores (para saber cuando esta apunto de salirse el robot)
int valorSensor1;
int valorSensor2;

// Definir variable para la distancia detectada para el sensor ultrasonico
float distancia;

void setup() {
  // Inicializar los pines de los sensores infrarojos como entradas
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);

  // Inicializar los pines del sensor ultrasonico como entrada y salida
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializar pines de los motores
  pinMode(velA, OUTPUT);
  pinMode(velB, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  digitalWrite(stby, HIGH);
}

void loop() {
  // leer los valores de los sensores
  valorSensor1 = digitalRead(sensor1);
  valorSensor2 = digitalRead(sensor2);

  // leer la distancia detectada por el sensor
  distancia = medirDistancia();

  // si la distancia es menor a 40 cm, avanzar hacia el objeto detectado
  if (distancia < 40) {
    avanzarRecto();
  } else if (valorSensor1 == HIGH && valorSensor2 == HIGH) {
    // si ambos sensores detectan el borde blanco, detener los motores
    detenerMotores();
  } else if (valorSensor1 == LOW) {
    // si el sensor izquierdo detecta el dojo negro, girar hacia la derecha
    girarDerecha();
  } else if (valorSensor2 == LOW) {
    // si el sensor derecho detecta el dojo negro, girar hacia la izquierda
    girarIzquierda();
  } else {
    // si ninguno de los sensores detecta el borde blanco ni el dojo negro, ni hay objetos cercanos, avanzar recto
    avanzarRecto();
  }
}

// Funcion para detener los motores
void detenerMotores() {
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
}

// Funcion para avanzar recto
void avanzarRecto() {
  analogWrite(velA, velocidadMaxima);
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, HIGH);
  analogWrite(velB, velocidadMaxima);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
}

// Funcion para retroceder
void retroceder() {
  analogWrite(velA, velocidadMaxima);
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(velB, velocidadMaxima);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);  
}

// Funcion para girar hacia la izquierda
void girarIzquierda() {
  analogWrite(velA, velocidadMaxima);
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  analogWrite(velB, velocidadMaxima);
}

// Funcion para girar hacia la derecha
void girarDerecha() {
  analogWrite(velB, velocidadMaxima);
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(velA, velocidadMaxima);
}

// Funcion para medir la distancia con el sensor
float medirDistancia() {
  // Enviar un pulso de 10 microsegundos al pin de disparo
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // calcular la duracion del eco
  float duracion = pulseIn(echoPin, HIGH);

  // calcular la distancia en centimetros
  float distancia = duracion / 58.2;

  //retornar la distancia
  return distancia;
}
