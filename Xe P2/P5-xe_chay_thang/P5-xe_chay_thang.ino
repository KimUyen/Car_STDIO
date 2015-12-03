#include <EEPROM.h>
int cambien = 4;
int led = 1;
bool stop;

//Motor A
int enA = 13;
int in1 = 6;
int in2 = 11;

//Motor B
int enB = 7;
int in3 = 5;
int in4 = 10;

//PushButton
int button = 13;

// Encoder
#define PULSESPERTURN 15
#define ENCODER_LEFT  2
#define ENCODER_RIGHT  3
#define PWM 200

typedef enum 
{
LEFT = 0,
RIGHT = 1,
CENTER
}Direct;

volatile unsigned int pulses[2] = {0, 0};  // number of pulses
volatile unsigned int pwm2 = 200;

unsigned long pushButton;
int pushButton2;

void counter_left()
{
  //Update count
  pulses[LEFT]++;     
}

void counter_right()
{
  //Update count
  pulses[RIGHT]++;      
}    

void balanceSpeed(long pulsesNumeLeft)
{
  if (stop)
  return;
  
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), counter_left, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), counter_right, FALLING);
  
  while (pulses[RIGHT] < pulsesNumeLeft)
  {
  }
  
  detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
  detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
  
  
  // calculate
  if (pulses[LEFT] != 0 && pulses[RIGHT] != 0)
  pwm2 = pulses[LEFT] * PWM / pulses[RIGHT];  
  Serial.println(pulses[LEFT]);
  Serial.println(pulses[RIGHT]);
  pulses[LEFT] = 0;
  pulses[RIGHT] = 0;
}
void setup()
{
  Serial.begin(9600);
  //khai bao cam bien hong ngoai
  pinMode(led,OUTPUT);
  pinMode(cambien, INPUT_PULLUP);
  
  //dong co A-B
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT); 
  
  pinMode(enB,OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT); 
  
  
  pinMode(ENCODER_LEFT, INPUT);
  pinMode(ENCODER_RIGHT, INPUT);
  
  pinMode (button, OUTPUT);
  
  MotorRunningGo(PWM, pwm2);
  pushButton = 0;
  stop = false;
  
  pwm2 = EEPROM.read(0);
  if (pwm2 < 180 || pwm2 > 220)
  {
    pwm2 = PWM;
  }  
}

void MotorRunningGo(int pwm1, int pwm2)
{   
  //Running motor A 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  analogWrite(enA, pwm1); //Speed PWM: 0~255 
  
  //Running motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, pwm2); //Speed PWM: 0~255   
}
void GoBack()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void StopMotor()
{  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void loop()
{
  Tumlum();
}
void Tumlum()
{
  while (pushButton < 100)
  {
    if(digitalRead(cambien) == 0)
    {         
    StopMotor();
    delay(100);
    stop = true;       
  }   
     
  balanceSpeed(50);
  MotorRunningGo(PWM, pwm2);
  stop = false;    
  pushButton++;
  
  Serial.print("pwm2 = ");
  Serial.println(pwm2,DEC);
  }
  
  pushButton = 0;
  EEPROM.write (0, pwm2);
  delay (1000);
}

