
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

  if (m<180 and 90<m and 50<p and p<150) {
    Serial.println("ROUGE");
  }
  if (110<p and p<125 and 40<n and n<60) {
    Serial.println("BLEU");
  }
  if (80<n and n<120 and 60<p and p<100) {
    Serial.println("VERT");
  }
  if (110<m and m<200 and 50<p and p<80 and 50<n and n<80) {
    Serial.println("ORANGE");
  }
  if (35<m and m<50 and 60<p and p<80 and 20<n and n<40) {
    Serial.println("MARRON");
  }
}

int val1() {

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  while(i<5) {
    frequency = pulseIn(sensorOut, LOW);
    int b = map(frequency, 25, 200, 255, 0);
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
    frequency = pulseIn(sensorOut, LOW);
    int b = map(frequency, 25, 190, 255, 0);
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
