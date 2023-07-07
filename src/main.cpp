#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  pinMode(32, OUTPUT);
  Serial.begin(9600);
  Serial.println("Started.")
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(32, HIGH);
  delay(1000);
  digitalWrite(32, LOW);
  delay(500);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }