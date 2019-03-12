#define S0 4   //s0 est branché sur PD4
#define S1 5   //s1 est branché sur PD5
#define S2 6   //s2 est branché sur PD6
#define S3 7   //s3 est branché sur PD7
#define sensorOut 8   //OUT est branché sur PD8
int frequency = 0;
int S;
int T;
int H;
int i;
int j;
int v;

void setup() {
  pinMode(S0, OUTPUT);    //Configuration des entrées S0 à S3 et sensorOut en mode sortie
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);  // on configure l'Output frequency scaling à 20%
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {

  var();
  Serial.print("R : ");
  int m=ReadRouge();  //Affectation du résultat entre 0 et 255 de la composante Rouge en RGB
  affichage(val1());
  Serial.print("G : ");
  int n=ReadGreen();      //Affectation du résultat entre 0 et 255 de la composante Verte en RGB
  affichage(val2());
  Serial.print("B : ");
  int p=ReadBlue();     //Affectation du résultat entre 0 et 255 de la composante Bleue en RGB
  affichage(val3());
  Serial.println(" ");
  var();
  delay(200);

  if ((n-m)>=17) {      //Enchainement de 4 boucles if déterminants, en fonction des valeurs m,p et n données, la couleur correspondante, et retournant un entier caractérisant une couleur
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

int ReadRed() {     // On lit la composante rouge de la source lumineuse

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  while(i<5) {
    int b = pulseIn(sensorOut, LOW);    //lecture de la fréquence de la composante rouge
    S+=b;
    i=i+1;
    delay(100);
  }
  return(S/5);      // on retourne la composante rouge moyenne de la souce lumineuse
}

int ReadGreen() {     // On lit la composante verte de la source lumineuse

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  while(j<5) {
    int b =  pulseIn(sensorOut, LOW);     // On lit la composante verte de la source lumineuse
    T+=b;
    j=j+1;
    delay(100);
  }
  return(T/5);      // on retourne la composante verte moyenne de la souce lumineuse
}

int ReadBlue() {      // On lit la composante bleue de la source lumineuse

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  while(v<5) {
    int b = pulseIn(sensorOut, LOW);      // On lit la composante bleue de la source lumineuse
    H+=b;
    v=v+1;
    delay(100);
  }
  return(H/5);      // on retourne la composante bleue moyenne de la souce lumineuse
}

String affichage(int k) {     //fonction permettant l'affichage sur le moniteur série de la valeur d'une composante RGB
  Serial.print(k);
  Serial.print(" ");
} 

int var() {     //Fonction permettant d'initialiser à 0 les variables de toutes les fonctions de couleurs
  i=0;
  j=0;
  v=0;
  S=0;
  T=0;
  H=0;
}
