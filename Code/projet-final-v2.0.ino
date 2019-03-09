#include<Servo.h>
#define S0 4   //s0 est branché sur PD4
#define S1 5   //s1 est branché sur PD5
#define S2 6   //s2 est branché sur PD6
#define S3 7   //s3 est branché sur PD7
#define sensorOut 8  //OUT est branché sur PD8
Servo servo1;
Servo servo2;
int frequency = 0;
int color;
int S;
int T;
int H;
int i;
int j;
int v;

void setup() {
  servo1.attach(2);
  servo2.attach(3);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);    // on configure l'Output frequency scaling à 20%
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}

void loop() {
  for (int i=10; i<=47; i++){                           //on place le bonbon sous le capteur 
      servo1.write(i);
      Serial.print("A");
      Serial.println(i);
      delay(50);}
  delay(400);
  color = readColor();                                  //le capteur analyse le bonbon et va renvoyer un entier selon la couleur perçue
  Serial.print(color);
  delay(500);
  switch (color){
    case 0:
    for (int i=0; i<=1; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    case 1:
    for (int i=0; i<=45; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    case 2:
    for (int i=0; i<=80; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    /*case 3:
    for (int i=0; i<=100; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    case 4:
    for (int i=0; i<=125; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    case 5:
    for (int i=10; i<=25; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;   */
  }

  delay(300);
  for (int i=50; i<=90; i++){                           //on emmene le bonbon au tobogan
      servo1.write(i);
      Serial.print("B");
      Serial.println(i);
      delay(25);}
  delay(1000);
  for (int i=90; i>=15; i--){                           //on tourne le moteur pour aller chercher le bonbon
      servo1.write(i);
      Serial.print("C");
      Serial.println(i);
      delay(10);}
  color=0;
  delay(1000);
}

int readColor(){
  var();
  Serial.print("R : ");
  int m=ReadRed();
  affichage(ReadRed());
  Serial.print("G : ");
  int n=ReadGreen();
  affichage(ReadGreen());
  Serial.print("B : ");
  int p=ReadBlue();
  affichage(ReadBlue());
  Serial.println(" ");
  var();
  delay(200);

  if ((n-m)>=17) {
    Serial.println("ROUGE");
    return 0;
  }
  if (n<p) {
    Serial.println("VERT");
    return 1;
  }
  if (p<n) {
    Serial.println("BLEU");
    return 2;
  }
  else {
    Serial.println("INCONNU");
    return 5;
  }
}

int ReadRed() {        // On lit la composante rouge de la source lumineuse

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  while(i<5) {
   int b = pulseIn(sensorOut, LOW);
   S+=b;
   i=i+1;
   delay(100);
  
  }
  return(S/5); // on retourne la composante rouge moyenne de la souce lumineuse
}

int ReadGreen() {   // On lit la composante verte de la source lumineuse

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  while(j<5) {
    int b =  pulseIn(sensorOut, LOW);
    T+=b;
    j=j+1;
    delay(100);
  }
  return(T/5);
}

int ReadBlue() {       // On lit la composante bleue de la source lumineuse

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  while(v<5) {
    int b = pulseIn(sensorOut, LOW);
    H+=b;
    v=v+1;
    delay(100);
  }
  return(H/5);
}

String affichage(int k) {
  Serial.print(k);
  Serial.print(" ");
}

int var() {
  i=0;
  j=0;
  v=0;
  S=0;
  T=0;
  H=0;
}

/*void Servo1Turn(int n){
  int angle=servo1.read();
  Serial.print("AngleServo1Avant: ");
  Serial.println(angle);                                    
  if (angle<n){                                             
    for (int i=angle; i<=n; i++){                           
      servo1.write(i);
      delay(100);
    }
   Serial.print("AngleServo1Apres: ");
   Serial.println(servo1.read());      
  }
  if (angle>n){
    for (int i=angle; n<=i; i--){
      servo1.write(i);
      delay(100);
    }
    Serial.print("AngleServo1Apres: ");
    Serial.println(servo1.read());
  }  
}
void Servo2Turn(int n){                                     
  int angle=servo2.read();
  Serial.print("AngleServo2Avant: ");
  Serial.println(angle);
  if (angle<n){
    for (int i=angle; i<=n; i++){
      servo2.write(i);
      delay(100);
    }
    Serial.print("AngleServo2Apres: ");
    Serial.println(servo2.read());
  }  
  if (angle>n){
    for (int i=angle; n<=i; i--){
      servo2.write(i);
      delay(100);
    }
    Serial.print("AngleServo2Apres: ");
    Serial.println(servo2.read());
  } 
}*/
