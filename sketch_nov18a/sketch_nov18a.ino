#include <Servo.h>

//Servo
Servo gServo;
#define SERVO_PIN 9
#define TRIG_PIN 8
#define ECHO_PIN 12

//IRIGHT1_PIN,IN2 = RIGHT
#define RIGHT1_PIN 6
#define RIGHT2_PIN 11

/*IN3,ILEFT2_PIN = LEFT*/
#define LEFT1_PIN 5
#define LEFT2_PIN 10

// default value
#define NUMPULSE_90 8
#define PULSESPERTURN 15
#define ANGLE_0 0
#define ANGLE_90 90
#define ANGLE_180 180
#define DISTANCE_STUFF 35

// Encoder
#define ENCODER_LEFT  2
#define ENCODER_RIGHT  3


// value global 
volatile unsigned int pulses_control_wheel[2] = {0};
volatile unsigned int pulses[2] = {0};  // number of pulses
bool can_goHead;

typedef enum 
{
  LEFT = 0,
  RIGHT = 1,
  CENTER
}Direct;

void turnEye(Direct dir)
{
  switch (dir)
  {
    case LEFT:
      gServo.write (ANGLE_180);
      break;
    
    case RIGHT:
      gServo.write (ANGLE_0);
      break;
      
    case CENTER:
      gServo.write (ANGLE_90);
      break;
    }
    delay (200);
}

float GetDistance()
{
  unsigned long duration, distanceCm;   
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
 
  // convert to distance
  distanceCm = duration / 29.1 / 2;
  
  return distanceCm;
}

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
void turnRight()
{
    turnEye(CENTER);

    analogWrite(RIGHT1_PIN, 0);
    analogWrite(RIGHT2_PIN, 180);
    
    analogWrite(LEFT1_PIN, 200);
    analogWrite(LEFT2_PIN, 0);

    runEncoder (NUMPULSE_90);
}

void turnLeft ()
{
    turnEye(CENTER);


    analogWrite(LEFT1_PIN, 0);
    analogWrite(LEFT2_PIN, 200);
    analogWrite(RIGHT1_PIN, 180);
    analogWrite(RIGHT2_PIN, 0);
   
    runEncoder (NUMPULSE_90);
}

void runEncoder (int numPulse)
{
    attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), counter_left, FALLING);
    attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), counter_right, FALLING);
    
    while (pulses[LEFT] < NUMPULSE_90 && pulses[RIGHT] < NUMPULSE_90)
    {
      // Do nothing
    }
    
    detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
    detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
    pulses[LEFT] = 0;
    pulses[RIGHT] = 0;
}


void STOP ()
{
    analogWrite(RIGHT2_PIN, 0);
    analogWrite(RIGHT1_PIN, 0);
    analogWrite(LEFT2_PIN, 0);
    analogWrite(LEFT1_PIN, 0);
   
}
void goHead ()
{
    turnEye (CENTER);
    analogWrite(RIGHT2_PIN, 0);
    analogWrite(RIGHT1_PIN, 180);
    analogWrite(LEFT2_PIN, 0);
    analogWrite(LEFT1_PIN, 200);
}

void goBack ()
{
    turnEye (CENTER);
    analogWrite(RIGHT1_PIN, 0);
    analogWrite(RIGHT2_PIN, 180);
    analogWrite(LEFT1_PIN, 0);
    analogWrite(LEFT2_PIN, 200);
} 
void setup()
{  
  // servo
    Serial.begin(9600);
    gServo.attach(SERVO_PIN); 
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

   // wheel
    pinMode(RIGHT1_PIN, OUTPUT);
    pinMode(RIGHT2_PIN, OUTPUT);
    pinMode(LEFT1_PIN, OUTPUT);
    pinMode(LEFT2_PIN, OUTPUT);

    // encoder
    pinMode(ENCODER_LEFT, INPUT);
    pinMode(ENCODER_RIGHT, INPUT);

    can_goHead = true;
}

bool haveStuff()
{
    long distance = GetDistance();
    if (distance < DISTANCE_STUFF && distance > 0)
      return true;
    return false;
}
     
void loop()
{
  goHead ();
  
  while (!haveStuff () && can_goHead)
  {
     // Do nothing
  }

  STOP ();
  
  turnEye (LEFT);
  if (haveStuff ())
  {
      turnEye (RIGHT);
      if (haveStuff ())
        {
          can_goHead = false;
          goBack ();
          delay (300);
        }
        else
        {
          can_goHead = true;
          turnRight ();
        }
  }
  else
  {
    can_goHead = true;
    turnLeft ();
  }
}
