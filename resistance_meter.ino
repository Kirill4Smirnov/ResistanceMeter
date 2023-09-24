#include "GyverFilters.h"
// параметры: разброс измерения, разброс оценки, скорость изменения значений
// разброс измерения: шум измерений
// разброс оценки: подстраивается сам, можно поставить таким же как разброс измерения
// скорость изменения значений: 0.001-1, варьировать самому
GKalman testFilter(50, 40, 0.03);
// также может быть объявлен как (разброс измерения, скорость изменения значений)
// GKalman testFilter(40, 0.5);

int Vin = 5;     // напряжение на выводе 5V arduino
float Vout = 0;  // напряжение на выводе A0 arduino
float R1 = 0.99;  // значение известного сопротивления
float R2 = 0;    // значение неизвестного сопротивления
float buffer;
int a2d_data = 0;


void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);

    for (int i = 0; i < 100; i++){
    a2d_data = analogRead(A0);
    a2d_data = testFilter.filtered(a2d_data);
  }
}

void loop() {

  a2d_data = analogRead(A0);
  a2d_data = testFilter.filtered(a2d_data);
  buffer = a2d_data * Vin;
  Vout = (buffer) / 1024.0;
  buffer = Vout / (Vin - Vout);
  R2 = R1 * buffer;
  //Serial.print(Vout);
  //Serial.print(" ");

  //Serial.print("\t R: ");
  if (R2 > 40) {
    Serial.println("inf");
  } else {
    Serial.println(R2);
  }
  //delay(1000);
/* //this is for filter adjustment
  Serial.print(a2d_data);
  Serial.print(" ");
  a2d_data = testFilter.filtered(a2d_data);
  Serial.println(a2d_data);
  */
}
