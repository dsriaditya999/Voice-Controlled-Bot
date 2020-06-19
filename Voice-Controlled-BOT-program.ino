
#include<string.h>
char *p;
int dist;
String command;
int ENA = 11;
int in1 =10;
int in2 =9;
int in3 = 8;
int in4 = 7;
int ENB = 6;
const byte sensor = 3;
String voice;
const float step_count = 20;
const float wheel_diameter = 60;


volatile int count = 0;

void ISR_count(){
  count++;
}

int CM_to_steps(float cm){
  int result;
  float circumference = (3.14*wheel_diameter)/10;
  float cm_per_step = (circumference/step_count);
  float f_result = (cm/cm_per_step);
  result = (int) (f_result);
  return result;
  }


void MoveForward(int steps)
{
  count = 0;
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

  while(steps>count){
    delay(200);
    analogWrite(ENA,150);
    analogWrite(ENB,150);
    delay(200);
    }
    analogWrite(ENA,0);
    analogWrite(ENB,0);

  }
  
void MoveReverse(int steps )
{
  count = 0;
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

  while(steps>count){
    delay(200);
    analogWrite(ENA,150);
    analogWrite(ENB,150);
    delay(200);
    }
    analogWrite(ENA,0);
    analogWrite(ENB,0);

  }
void MoveLeft(int steps)
{
  count = 0;
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(200);
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  delay(600);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
  while(steps>count){
    delay(100);
    analogWrite(ENA,150);
    analogWrite(ENB,150);
    delay(200);
    }
    analogWrite(ENA,0);
    analogWrite(ENB,0);

  }

void MoveRight(int steps)
{
  count = 0;
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(200);
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  delay(600);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
  while(steps>count){
    delay(100);
    analogWrite(ENA,150);
    analogWrite(ENB,150);
    delay(200);
    }
    analogWrite(ENA,0);
    analogWrite(ENB,0);

  }

void setup() {
  // put your setup code here, to run once:
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENB,OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensor),ISR_count,RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){


    delay(10);
    char c = Serial.read();
    if(c=='#'){
      break;
      }

      voice += c;
  }
      if(voice.length() > 0){

        Serial.println(voice);
        

        p = strtok(voice.c_str()," ");
        command = p;
        p = strtok(NULL," ");
        dist = String(p).toInt();
        
        if(command == "*forward"){
          
          MoveForward(CM_to_steps(dist));
          Serial.println(dist);
          }

         else if(command == "*reverse"){
          
          MoveReverse(CM_to_steps(dist));
 
        }
        else if(command == "*left"){
          
          MoveLeft(CM_to_steps(dist));
 
        }
        else if(command == "*right" || command == "*write"){
          
          MoveRight(CM_to_steps(dist));
 
        }
    }
    voice ="";
    

}
