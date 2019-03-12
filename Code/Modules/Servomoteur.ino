#include<Servo.h>
Servo servo1;              //Declaration des deux objets servo
Servo servo2;

void PositiveTurn(int beginning,int last,int speedd, Servo moteur){
   for (int i=beginning; i<=last; i++){                                 //cette rotation concerne une augmentation d'angle
      moteur.write(i);
      Serial.print("A");
      Serial.println(i);
      delay(speedd);}                                                   //ici on définit la vitesse angulaire du moteur
}
void NegativeTurn(int beginning,int last,int speedd, Servo moteur){
   for (int i=beginning; i>=last; i--){                                 //cette rotation concerne une diminution d'angle                  
      moteur.write(i);
      Serial.print("B");
      Serial.println(i);
      delay(speedd);}
}
