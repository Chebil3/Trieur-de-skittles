#include<Servo.h>
#include<SoftwareSerial.h>
#define RX 12
#define TX 11
SoftwareSerial BlueT(RX,TX);
#define S0 4   //s0 est branché sur PD4
#define S1 5   //s1 est branché sur PD5
#define S2 6   //s2 est branché sur PD6
#define S3 7   //s3 est branché sur PD7
#define sensorOut 8  //OUT est branché sur PD8
Servo servo1;
Servo servo2;
char Data;
int frequency = 0;
int color;
int S;        //Création de variable utlisées par les fonctions de couleurs
int T;
int H;
int i;
int j;
int v;
int r=0;
int g=0;
int l=0;

void setup() {
  Serial.begin(9600);
  BlueT.begin(9600);   //Initialisation du module bluetooth
  servo1.attach(2);   //Connection du servo moteur 1 au entrée numérique 2
  servo2.attach(3);   //Connection du servo moteur 1 au entrée numérique 3
  pinMode(S0, OUTPUT);    //Configuration des entrées S0 à S3 et sensorOut en mode sortie
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);    // on configure l'Output frequency scaling à 20%
  digitalWrite(S1,LOW);
  lcd.begin(16,2);
}

void loop() {
  
  if (BlueT.available()) {    //Si le module bluetooth est disponible à la connexion
      Data=BlueT.read();      //Lecture du caractère envoyé par le téléphone
      if (Data=='M') {        //Si on demande à mettre en marche la machine
        for (int i=15; i<=47; i++){            //on place le bonbon sous le capteur 
            servo1.write(i);
            Serial.print("A");
            Serial.println(i);
            delay(50);}
        delay(400);
        color = readColor();           //le capteur analyse le bonbon et va renvoyer un entier selon la couleur perçue
        Serial.print(color);
        delay(500);
        switch (color){
          case 0:
          for (int i=0; i<=1; i++){              //on tourne le tobogan jusqu'à l'angle voulu si c'est rouge
            servo2.write(i);
            Serial.print("D");
            Serial.println(i);
            delay(10);}
          break;
      
          case 1:
          for (int i=0; i<=45; i++){            //on tourne le tobogan jusqu'à l'angle voulu si c'est vert
            servo2.write(i);
            Serial.print("D");
            Serial.println(i);
            delay(10);}
          break;
      
          case 2:
          for (int i=0; i<=80; i++){           //on tourne le tobogan jusqu'à l'angle voulu si c'est bleu
            servo2.write(i);
            Serial.print("D");
            Serial.println(i);
            delay(10);}
          break;
    }
  
        delay(300);
        for (int i=50; i<=90; i++){             //on emmene le bonbon au tobogan
            servo1.write(i);
            Serial.print("B");
            Serial.println(i);
            delay(25);}
        delay(1000);
        for (int i=90; i>=15; i--){        //on tourne le moteur pour aller chercher le bonbon
            servo1.write(i);
            Serial.print("C");
            Serial.println(i);
            delay(10);}
        color=0;
        delay(1000);
        Data='M';
        
        }

        if(Data=='A') {     //Si le téléphone demande à la machine de s'arreter
          Serial.println("La machine est désactivé!");
        }
 }
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

  if ((n-m)>5) {
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
