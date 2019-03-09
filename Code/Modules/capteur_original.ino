#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequency = 0;
int S;
int T;
int H;
int i;
int j;
int v;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {

  var();
  Serial.print("R : ");
  int m=val1();
  affichage(val1());
  Serial.print("G : ");
  int n=val2();
  affichage(val2());
  Serial.print("B : ");
  int p=val3();
  affichage(val3());
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

int val1() {

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  while(i<5) {
    int b = pulseIn(sensorOut, LOW);
    S+=b;
    i=i+1;
    delay(100);
  }
  return(S/5);
}

int val2() {

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

int val3() {

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
