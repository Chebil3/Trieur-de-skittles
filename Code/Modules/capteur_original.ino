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

  if (m<180 and 100<m and 0<p and p<40 and 0<n and n<40 ) {
    Serial.println("ROUGE");
  }
  if (70<p and p<140 and 0<n and n<90 and 35<m<120) {
    Serial.println("BLEU");
  }
  if (60<n and n<140 and 40<m and m<140 and 0<p and p<60) {
    Serial.println("VERT");
  }
  if (110<m and m<150 and 30<p and p<60 and 30<n and n<60) {
    Serial.println("ORANGE");
  }
  if (60<m and m<90 and 10<p and p<50 and 10<n and n<50) {
    Serial.println("MARRON");
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
