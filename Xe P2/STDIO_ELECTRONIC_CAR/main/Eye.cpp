#include "Define.h"
#include "Eye.h"

Eye * Eye::m_instance = NULL;

Eye * Eye::GetInstance()
{
  if (m_instance == NULL)
      m_instance = new Eye();
  return m_instance;
}

Eye::Eye()
{
  
}

Eye::~Eye()
{
  
}
void Eye::Release()
{
  delete m_instance;
  m_instance = NULL;
}

void Eye::Setup()
{
  // Servo pin
  m_servo.attach(SERVO_PIN); 

  // SRF pin
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // IR pin
  pinMode(PHOTODIOT_IR, INPUT_PULLUP);
}

bool Eye::HaveObstacle()
{
  long distance = GetDistance();
  if ((distance < DISTANCE_HAVE_OBSTACLE && distance > 0) || digitalRead(PHOTODIOT_IR) == 0)
      return true;
  return false;
}

bool Eye::CheckObstacle(long distance)
{
  if ((distance < DISTANCE_HAVE_OBSTACLE && distance > 0))
      return true;
  return false;
}

bool Eye::CanGo(long distance)
{
  if (distance > DISTANCE_CAN_GO)
    return true;
  return false;
}

void Eye::Turn(Direct dir)
{
  switch (dir)
  {
    case Direct::L:
      m_servo.write (ANGLE_180);
      break;
    
    case Direct::R:
      m_servo.write (ANGLE_0);
      break;
      
    case Direct::CENTER:
      m_servo.write (ANGLE_90);
      break;
    }
}

float Eye::GetDistance()
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
