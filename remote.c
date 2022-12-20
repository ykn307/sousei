#include <Servo.h>

// 変数定義
//1:つかみ:持ち上げ
Servo myservo1;
unsigned char command;
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
pinMode(A4, INPUT);
pinMode(light, INPUT);
pinMode(13,OUTPUT);
myservo1.attach(5);
Serial.begin(57600);
}

// プロトタイプ宣言
void drive(void);//実行時走行

void back(void);//バック

void stopp(void);//停止

void turning(int deg, bool isright);//指定した角度、方向に回転

void hold(void);//目の前のものを掴む

void putt(void);//置く


void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0){
  command = Serial.read();
  switch(command){
    case 0:
      stopp();
      digitalWrite(13,HIGH);
      break;
    case 1:
      drive();
      digitalWrite(13,LOW);
      break;
    case 2:
      right();
      break;
    case 3:
      left();
      break;
    case 4:
      back();
      break;
    case 5:
      hold();
      break;
    case 6:
      putt();
      break;
  }
  Serial.flush();
  delay(100);
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

void back(void){
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2, HIGH);
  map_speedA = 255*cona/1023/3*2;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2, HIGH);
  map_speedB = 255*conb/3*2;
  analogWrite(PWMB, map_speedB);
}

void stopp(void){
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

}

void right(){
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2, LOW);
  map_speedA = 255*cona/1023/3*2;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2, HIGH);
  map_speedB = 255*conb/3*2;
  analogWrite(PWMB, map_speedB);
}

void left(){
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2, HIGH);
  map_speedA = 255*cona/1023/3*2;
  analogWrite(PWMA, map_speedA);

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2, LOW);
  map_speedB = 255*conb/3*2;
  analogWrite(PWMB, map_speedB);
}


void hold(void){
  myservo1.write(160);
  delay(100);

}

void putt(void){
  myservo1.write(20);
  delay(100);
}

void lit(){
  if (command==0){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}
