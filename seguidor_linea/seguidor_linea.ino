const int velA = 6;
const int velB = 11;
const int Ain2 = 7;
const int Ain1 = 8;
const int stby = 12;
const int Bin1 = 9;
const int Bin2 = 10;

void setup() {
  pinMode(velA, OUTPUT);
  pinMode(velB, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  analogWrite(velA, 255);
  analogWrite(velB, 255);
  digitalWrite(stby, HIGH);
}

void loop() {
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