#include<Servo.h>
Servo servo1;
Servo servo2;
void setup() {
  servo1.attach(2);
  servo2.attach(3);
  Serial.begin(9600);
}

void loop(){
  Servo1Turn(90);
  Servo1Turn(0);
  Servo2Turn(90);
  Servo2Turn(0);
}

void Servo1Turn(int n){
  int angle=servo1.read();
  Serial.println("AngleServo1avant: "+servo1.read());       //Je lis l'angle courant
  if (angle<n){                                             //Si l'angle courant est inférieur à l'angle auquel on veut aller
    for (int i=angle; i<=n; i++){                           //on tourne jusqu'à l'angle voulu
      servo1.write(i);
      delay(10);
    }
   Serial.println("AngleServo1apres: "+servo1.read());      //Je lis l'angle atteint
  }
  if (angle>n){
    for (int i=angle; n<=i; i--){
      servo1.write(i);
      delay(10);
    }
    Serial.println("AngleServo1apres: "+servo1.read());
  }  
}

void Servo2Turn(int n){                                     //Cette fonction est la même que au-dessus sauf qu'il s'agit du servomoteur 2
  int angle=servo2.read();
  Serial.println("AngleServo2avant: "+servo2.read());
  if (angle<n){
    for (int i=angle; i<=n; i++){
      servo2.write(i);
      delay(10);
    }
    Serial.println("AngleServo2apres: "+servo2.read());
  }
  
  if (angle>n){
    for (int i=angle; n<=i; i--){
      servo2.write(i);
      delay(10);
    }
    Serial.println("AngleServo2apres: "+servo2.read());
  } 
}
