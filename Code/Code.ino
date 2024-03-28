#include<Servo.h>

Servo servo;

#define Right1 12
#define Right2 11
#define Left1 10
#define Left2 9

#define ServoPin 8

#define SensorTrig 3
#define SensorEco 2

int Minimumdist = 5; // 5cm from object will detect
int turningdelay = 1000; //1 second

long time;
int distance;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(Right1,OUTPUT);
    pinMode(Right2,OUTPUT);
    pinMode(Left1,OUTPUT);
    pinMode(Left2,OUTPUT);

    pinMode(SensorTrig,OUTPUT);
    pinMode(SensorEco,INPUT);

    servo.attach(ServoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDistance();
  if(distance < Minimumdist){
      STOP();
      servo.write(0);//Trun sensor Right
      updateDistance();

      if(distance > Minimumdist){
      Right();
      }
      else{
          servo.write(180);//Turn sensor Left 
          updateDistance();
          if(distance > Minimumdist){
              Left();
          }
          else{
              Right();//U Turn
              Right();
          }
      }
  }
  else{
      servo.write(90);//Turn sensor front
      Front();
  }
}


void updateDistance(){
    digitalWrite(SensorTrig, LOW); //Trigger servo
    delayMicroseconds(2);
    digitalWrite(SensorTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(SensorTrig, LOW);

    time = pulseIn(SensorEco, HIGH); // Read Pulse
    
    distance = time * 0.034 / 2; //Calculate distance
    
    Serial.print("Distance: ");
    Serial.println(distance);
}

void Front(){
    digitalWrite(Right1,HIGH);//FWD
    digitalWrite(Right2,LOW);
    digitalWrite(Left1,HIGH);//FWD
    digitalWrite(Left2,LOW);

}

void Right(){
    digitalWrite(Right1,HIGH);//FWD
    digitalWrite(Right2,LOW);
    digitalWrite(Left1,LOW);//REV
    digitalWrite(Left2,HIGH);
    delay(1000);
    STOP();
}

void Left(){
    digitalWrite(Right2,HIGH);//REV
    digitalWrite(Right1,LOW);
    digitalWrite(Left2,LOW);//FWD
    digitalWrite(Left1,HIGH);
    delay(1000);
    STOP();
}

void STOP(){
    digitalWrite(Right1,LOW);//STP
    digitalWrite(Right2,LOW);
    digitalWrite(Left1,LOW);//STP
    digitalWrite(Left2,LOW);

}

