#include<Servo.h>
Servo servo1;
Servo servo2;

void PositiveTurn(int beginning,int last,int speedd, Servo moteur){
   for (int i=beginning; i<=last; i++){                           
      moteur.write(i);
      Serial.print("A");
      Serial.println(i);
      delay(speedd);}
}
void NegativeTurn(int beginning,int last,int speedd, Servo moteur){
   for (int i=beginning; i>=last; i--){                           
      moteur.write(i);
      Serial.print("B");
      Serial.println(i);
      delay(speedd);}
}
