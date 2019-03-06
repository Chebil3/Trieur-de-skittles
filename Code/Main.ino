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
  for (int i=15; i<=52; i++){                           //on place le bonbon sous le capteur 
      servo1.write(i);
      Serial.print("A");
      Serial.println(i);
      delay(50);}
  delay(3000);
  color = readColor();                                  //le capteur analyse le bonbon et va renvoyer un entier selon la couleur perçue
  Serial.print(color);
  delay(1000);
  switch (color){
    case 0:
    for (int i=0; i<=25; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    case 1:
    for (int i=0; i<=50; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    case 2:
    for (int i=0; i<=75; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;

    case 3:
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
    for (int i=0; i<=150; i++){                           //on tourne le tobogan jusqu'à l'angle voulu 
      servo2.write(i);
      Serial.print("D");
      Serial.println(i);
      delay(10);}
    break;   
  }

  delay(300);
  for (int i=50; i<=90; i++){                           //on emmene le bonbon au tobogan
      servo1.write(i);
      Serial.print("B");
      Serial.println(i);
      delay(50);}
  delay(200);
  for (int i=90; i>=15; i--){                           //on tourne le moteur pour aller chercher le bonbon
      servo1.write(i);
      Serial.print("C");
      Serial.println(i);
      delay(10);}
  color=0;
  delay(2000);
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

  if (m<150 and 90<m and 50<p and p<150) {
    Serial.println("ROUGE");
    return 0;
  }
  if (110<p and p<125 and 40<n and n<60) {
    Serial.println("BLEU");
    return 1;
  }
  if (80<n and n<120 and 60<p and p<100) {
    Serial.println("VERT");
    return 2;
  }
  if (110<m and m<200 and 50<p and p<80 and 50<n and n<80) {
    Serial.println("ORANGE");
    return 3;
  }
  if (35<m and m<50 and 60<p and p<80 and 20<n and n<40) {
    Serial.println("MARRON");
    return 4;
  }
  else {
    return 5;
  }
}

int ReadRed() {        // On lit la composante rouge de la source lumineuse

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  while(i<5) {    //boucle qui sert à faire une moyenne afin d'être plus précis 
    frequency = pulseIn(sensorOut, LOW);
    int b = map(frequency, 25, 200, 255, 0);  // on calibre la valeur obtenue par pulseIn dans une échelle de valeur entre 0 et 255 (plus la valeur est haute plus la composante rouge est importante)
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
    frequency = pulseIn(sensorOut, LOW);
    int b = map(frequency, 25, 190, 255, 0);
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
    frequency = pulseIn(sensorOut, LOW);
    int b = map(frequency, 25, 160, 255, 0);
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
