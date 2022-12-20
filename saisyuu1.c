#include <Servo.h>

// 変数定義
//1:つかみ:持ち上げ
Servo myservo1;
unsigned long time;
const int servo1=5;
const int AIN1 = 7;
const int AIN2 = 8;
const int PWMA = 9;
const int BIN1 = 11;
const int BIN2 = 12;
const int PWMB = 10;
const int light = A0;
double cona = 1;
double conb = 0.8;
double conaa = 1;
double conbb=1;
int speed_cmd;
int map_speedA;
int map_speedB;
int speed_cmda;
int speed_cmdb;
int delta = 100;
bool driving = true;
int starting;
bool turn = true;
double timing = 1;
int lighting;
bool truee = true;
double Distance = 0;
double degre = 0;
double degree = 0;
bool black;
bool drtn = false;
bool tatn = false;
#define TringPin 4
#define EchoPin 3





void setup() {
  // put your setup code here, to run once:
pinMode(AIN1,OUTPUT);
pinMode(AIN2, OUTPUT);
pinMode(PWMA,OUTPUT);
pinMode(BIN1,OUTPUT);
pinMode(BIN2, OUTPUT);
pinMode(PWMB,OUTPUT);
pinMode(servo1,OUTPUT);
pinMode(A2,INPUT);
pinMode( TringPin, OUTPUT);
pinMode( EchoPin, INPUT);
pinMode(A4, INPUT);
pinMode(light, INPUT);
pinMode(13,OUTPUT);
pinMode(2,INPUT_PULLUP);
Serial.begin( 9600 );
}

// プロトタイプ宣言
void drive(void);//実行時走行

void breaki();//減速

void go(void);//目の前の物体に近づく

void stopp(void);//停止

void turning(int deg, bool isright);//指定した角度、方向に回転

double measure(void);//目の前の距離を測定

void hold(void);//目の前のものを掴む

void putt(void);//置く

bool isblack(void);//地面やドリンクが白か黒かの判定

bool istouch(void);//壁やテーブルと接触したらtrue

void searchandgo(void);//10度ずつ回転して目の前に物体があるかどうかの確認

void searchandgoandstop(void);//10度ずつ回転して目の前に物体があるかどうかの確認,目の前にあったらストップ

void gyakugorugo(bool isright);//黒検知後回転

void vertical();//壁に対して垂直に

void curve(bool isright);//緩やかにカーブ

bool tatouch(void);//多分使わない



// メインコード
void loop() {
  // put your main code here, to run repeatedly:
cona = analogRead(A2);
double aaa = analogRead(A4);
timing = double(aaa/1023);
vertical();
stopp();
delay(100);
while(isblack()==false){
  drive();
}

if(isblack()==true){
int ii=0;
    while(ii<100){
      ii=ii+1;
      delay(2);
    if(istouch()==true){
    stopp();
  if (drtn==tatn){
  digitalWrite(13,HIGH);
  delay(100000);
  }else{
    delay(100000);
  }
  }
 }

stopp();
turning(90,true);
while(istouch()==false){
    drive();
  }
  stopp();
  if (drtn==tatn){
  digitalWrite(13,HIGH);
  delay(100000);
  }else{
    delay(100000);
  }

  }


}


// 関数定義
void drive(void){
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2, LOW);
  map_speedA = 255*cona/1023/3*2;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2, LOW);
  map_speedB = 255*conb/3*2;
  analogWrite(PWMB, map_speedB);
}

void breaki(){
  Distance=measure();
  if (Distance>40){
    drive();
  }else{
    digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2, LOW);
  map_speedA = 255*cona/1023/60*(20+Distance/2);
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2, LOW);
  map_speedB = 255*conb/60*(20+Distance/2);
  analogWrite(PWMB, map_speedB);
  }
}

void go(void){
  Distance=measure();
  if (Distance>6){
    breaki();
  }else{
    stopp();
  }
}

void stopp(void){
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

}

void turning(int deg, bool isright){
  if (isright){
    digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2, LOW);
  map_speedA = 255*cona/1023;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2, HIGH);
  map_speedB = 255*conb;
  analogWrite(PWMB, map_speedB);
  delay(int(2000*timing*deg/90));
  }else{
    digitalWrite(AIN1,LOW);
  digitalWrite(AIN2, HIGH);
  map_speedA = 255*cona/1023;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2, LOW);
  map_speedB = 255*conb;
  analogWrite(PWMB, map_speedB);
  delay(int(2000*timing*deg/90));
  }
  stopp();
}

double measure(void){
  digitalWrite(TringPin,HIGH);
  delayMicroseconds(10);
  digitalWrite( TringPin, LOW);
  double ProDelay1 = pulseIn(EchoPin,HIGH);
  double Distance1 = 340*ProDelay1/20000;

  digitalWrite(TringPin,HIGH);
  delayMicroseconds(10);
  digitalWrite( TringPin, LOW);
  double ProDelay2 = pulseIn(EchoPin,HIGH);
  double Distance2 = 340*ProDelay2/20000;

  digitalWrite(TringPin,HIGH);
  delayMicroseconds(10);
  digitalWrite( TringPin, LOW);
  double ProDelay3 = pulseIn(EchoPin,HIGH);
  double Distance3 = 340*ProDelay3/20000;

  if (Distance1<Distance2){
    if(Distance1<Distance3){
      return Distance1;
    }else{
      return Distance3;
    }
  }else{
    if (Distance2<Distance3){
      return Distance2;
    }else{
      return Distance3;
    }
  }
}

void hold(void){
  myservo1.write(90);
  delay(100);

}

void putt(void){
  myservo1.write(30);
  delay(100);
}

bool isblack(void){
  if(analogRead(A0)<500){
    return false;
  }else{
    return true;
  }
}

bool istouch(void){
  if(digitalRead(2)){
    return false;
  }else{
    return true;
  }
}

void searchandgo(void){
  Distance=measure();
  if (Distance<50){
    go();
  }else{
    delay(100);
    turning(10,true);
  delay(100);
  }
}

void searchandgoandstop(void){
  Serial.println(digitalRead(2));
  if (digitalRead(2) == 1){
    searchandgo();
  }else{
    stopp();
    digitalWrite(13,HIGH);
    delay(10000);

  }
}

void gyakugorugo(bool isright){
  Distance=measure();

  while(Distance<50){
    delay(100);
    turning(10,true);
  delay(100);
    Distance=measure();
  }
//  turning(30,true);

  while(istouch()==false){
    curve(true);
  }
  stopp();
  if (drtn==tatn){
  digitalWrite(13,HIGH);
  delay(100000);
  }else{
    delay(100000);
  }

}

void vertical(){
  int nowDistance=measure();
  int preDistance = 1000;
  while (nowDistance<preDistance || nowDistance>80){


    turning(10,true);
    delay(100);
    preDistance = nowDistance;
    nowDistance=measure();
  }
  turning(30,true);
}

void curve(bool isright){
  double d=0.1;
  if (isright==true){
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2, LOW);
  map_speedA = 255;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2, LOW);
  map_speedB = d*255;
  analogWrite(PWMB, map_speedB);
  }else{
    digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2, LOW);
  map_speedA = d*255;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2, LOW);
  map_speedB = 255;
  analogWrite(PWMB, map_speedB);
  }

}

bool tatouch(void){
  if (analogRead(A0)>800 && analogRead(A0)<200){
    return true;
  }else{
    return false;
  }
}
