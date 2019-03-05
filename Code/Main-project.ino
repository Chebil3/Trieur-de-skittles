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
int S;    //Création de variable utlisées par les fonctions de couleurs
int T;
int H;
int i;
int j;
int v;

void setup() {
  servo1.attach(2);         //Connection du servo moteur 1 au entrée numérique 2
  servo2.attach(3);         ////Connection du servo moteur 2 à l'entrée numérique 3
  pinMode(S0, OUTPUT);      //Configuration des entrées S0 à S3 et sensorOut en mode sortie
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);    // on configure l'Output frequency scaling à 20%
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  Servo1Turn(65);  //Rotation de 65°C du servo 1 pour emmener le skittle sous le capteur
  delay(500);
  color = readColor();   //Analyse de la couleur du skittle
  delay(100);
  switch (color){   //Fonction permettant d'ordonner une rotation d'un certain angle en fonction de la valeur de color ( 5 différentes rotations possibles car 5 types de couleurs )
    case 0:
    Servo2Turn(25);
    break;

    case 1:
    Servo2Turn(50);
    break;

    case 2:
    Servo2Turn(75);
    break;

    case 3:
    Servo2Turn(100);

    case 4:
    Servo2Turn(125);
  }
  delay(300);
  Servo1Turn(90);  // Rotation du servo 1 permettant de faire tomber le skittle dans le toboggan
  delay(200);
  Servo1Turn(0);  // Rotation du servo 1 afin de se remettre à sa position initiale ( plaque fixée sur le servo 1 en dessous de l'entonnoir à skittles
  color=0;        
  
}

int readColor(){
  var();                //Appel de fonction permettant d'initialiser à 0 les variables de chaques fonctions de couleurs
  Serial.print("R : ");
  int m=ReadRed();   //Affectation du résultat entre 0 et 255 de la composante Rouge en RGB
  affichage(ReadRed());
  Serial.print("G : ");
  int n=ReadGreen();   //Affectation du résultat entre 0 et 255 de la composante Verte en RGB
  affichage(ReadGreen());
  Serial.print("B : ");
  int p=ReadBlue();   //Affectation du résultat entre 0 et 255 de la composante Bleue en RGB
  affichage(ReadBlue());
  Serial.println(" ");
  var();               //Appel de fonction permettant de réinitialiser à 0 les variables de chaques fonctions de couleurs
  delay(200);

  if (m<150 and 90<m and 50<p and p<150) {   //Enchainement de 5 boucles if déterminants, en fonction des valeurs m,p et n données, la couleur correspondante, et retournant un entier caractérisant une couleur
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
    int b = map(frequency, 25, 190, 255, 0);  // on calibre la valeur obtenue par pulseIn dans une échelle de valeur entre 0 et 255 (plus la valeur est haute plus la composante rouge est importante)
    T+=b;
    j=j+1;
    delay(100);
  }
  return(T/5);    // on retourne la composante verte moyenne de la souce lumineuse
}

int ReadBlue() {       // On lit la composante bleue de la source lumineuse

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  while(v<5) {
    frequency = pulseIn(sensorOut, LOW);
    int b = map(frequency, 25, 160, 255, 0);  // on calibre la valeur obtenue par pulseIn dans une échelle de valeur entre 0 et 255 (plus la valeur est haute plus la composante rouge est importante)
    H+=b;
    v=v+1;
    delay(100);
  }
  return(H/5);  // on retourne la composante bleue moyenne de la souce lumineuse

String affichage(int k) {   //fonction permettant l'affichage sur le moniteur série de la valeur d'une composante RGB
  Serial.print(k);
  Serial.print(" ");
}

int var() {   //Fonction permettant d'initialiser à 0 les variables de toutes les fonctions de couleurs
  i=0;
  j=0;
  v=0;
  S=0;
  T=0;
  H=0;
}

void Servo1Turn(int n){     //Fonction permettant d'effectuer au servo moteur 1 de faire des rotations dans le sens trigonométrique et dans le sens contraire
  int angle=servo1.read();       //lecture de l'angle au début
  Serial.print("AngleServo1Avant: ");
  Serial.println(angle);                                    
  if (angle<n){                         //chaque 0.1 secondes le servo moteur fait une rotation d'un degré dans le sens horaire jusqu'à arriver à l'angle désiré                    
    for (int i=angle; i<=n; i++){                           
      servo1.write(i);
      delay(100);
    }
   Serial.print("AngleServo1Apres: ");
   Serial.println(servo1.read());      //affichage de l'angle à la fin
  }
  if (angle>n){            //chaque 0.1 secondes le servo moteur fait une rotation d'un degré dans le sens anti-horaire jusqu'à arriver à l'angle désiré
    for (int i=angle; n<=i; i--){
      servo1.write(i);
      delay(100);
    }
    Serial.print("AngleServo1Apres: ");
    Serial.println(servo1.read());   //affichage de l'angle à la fin 
  }  
}

void Servo2Turn(int n){            //Fonction permettant d'effectuer au servo moteur 2 de faire des rotations dans le sens trigonométrique et dans le sens contraire               
  int angle=servo2.read();   //lecture de l'angle au début
  Serial.print("AngleServo2Avant: ");
  Serial.println(angle);
  if (angle<n){   //chaque 0.1 secondes le servo moteur fait une rotation d'un degré dans le sens horaire jusqu'à arriver à l'angle désiré
    for (int i=angle; i<=n; i++){
      servo2.write(i);
      delay(100);
    }
    Serial.print("AngleServo2Apres: ");
    Serial.println(servo2.read());    //affichage de l'angle à la fin
  }  
  if (angle>n){       //chaque 0.1 secondes le servo moteur fait une rotation d'un degré dans le sens anti-horaire jusqu'à arriver à l'angle désiré
    for (int i=angle; n<=i; i--){
      servo2.write(i);
      delay(100);
    }
    Serial.print("AngleServo2Apres: ");
    Serial.println(servo2.read());      //affichage de l'angle à la fin
  } 
}
