int Vin = 5;     // напряжение на выводе 5V arduino
float Vout = 0;  // напряжение на выводе A0 arduino
float R1 = 0.99;  // значение известного сопротивления
float R2 = 0;    // значение неизвестного сопротивления
float buffer;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int a2d_data = analogRead(A0);
  buffer = a2d_data * Vin;
  Vout = (buffer) / 1024.0;
  buffer = Vout / (Vin - Vout);
  R2 = R1 * buffer;
  //Serial.print(Vout);
  //Serial.print(" ");

  //Serial.print("\t R: ");
  if (R2 > 20) {
    Serial.println("inf");
  } else {
    Serial.println(R2);
  }
  //delay(1000);
}
