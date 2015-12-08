#include "Define.h"
#include "Encoder.h"
#include "Driver.h"

Driver * Driver::m_instance = NULL;

Driver * Driver::GetInstance()
{
  if (m_instance == NULL)
      m_instance = new Driver();
  return m_instance;
}

void Driver::Release()
{
  delete m_instance;
  m_instance = NULL;
}


bool Driver::IsStop()
{
  return m_isStop;
}

void Driver::Setup()
{
  // Setup for motor right.
  pinMode(EN_RIGHT, OUTPUT);
  pinMode(IN1_RIGHT, OUTPUT);
  pinMode(IN2_RIGHT, OUTPUT); 

  // Setup for motor left.
  pinMode(EN_LEFT, OUTPUT);
  pinMode(IN1_LEFT, OUTPUT);
  pinMode(IN2_LEFT, OUTPUT);
}

void Driver::GoHead()
{
  m_isStop = false;
  //Running motor Right 
  digitalWrite(IN1_RIGHT, HIGH);
  digitalWrite(IN2_RIGHT, LOW);
  
  //Running motor left
  digitalWrite(IN1_LEFT, HIGH);
  digitalWrite(IN2_LEFT, LOW);
}

void Driver::GoBack()
{
  m_isStop = false;
  //Running motor Right 
  digitalWrite(IN1_RIGHT, LOW);
  digitalWrite(IN2_RIGHT, HIGH);
  
  //Running motor left
  digitalWrite(IN1_LEFT, LOW);
  digitalWrite(IN2_LEFT, HIGH);
}

void Driver::TurnLeft()
{
  m_isStop = false;
  //Running motor A 
  digitalWrite(IN1_RIGHT, HIGH);
  digitalWrite(IN2_RIGHT, LOW); 
  
  //Running motor B
  digitalWrite(IN1_LEFT, LOW);
  digitalWrite(IN2_LEFT, HIGH);
  analogWrite(EN_RIGHT, m_pwmRight);
   analogWrite(EN_LEFT, m_pwmLeft);

  // Wait encoder
  Encoder::GetInstance()->Set(Wheel::RIGHT);
  Encoder::GetInstance()->Wait(HOLES_FOR_TURN, Wheel::RIGHT);
  Encoder::GetInstance()->Reset(Wheel::RIGHT);
}

void Driver::TurnRight()
{
  m_isStop = false;
  //Running motor A 
  digitalWrite(IN1_RIGHT, LOW);
  digitalWrite(IN2_RIGHT, HIGH); 
  
  //Running motor B
  digitalWrite(IN1_LEFT, HIGH);
  digitalWrite(IN2_LEFT, LOW);
  analogWrite(EN_RIGHT, m_pwmRight);
   analogWrite(EN_LEFT, m_pwmLeft);
  
  // Wait encoder
  Encoder::GetInstance()->Set(Wheel::LEFT);
  Encoder::GetInstance()->Wait(HOLES_FOR_TURN, Wheel::LEFT);
  Encoder::GetInstance()->Reset(Wheel::LEFT);
}

void Driver::Stop()
{
  m_isStop = true;
  digitalWrite(IN1_RIGHT, LOW);
  digitalWrite(IN2_RIGHT, LOW); 
  
  digitalWrite(IN1_LEFT, LOW);
  digitalWrite(IN2_LEFT, LOW);
}

void Driver::Start()
{
   m_isStop = false;
   analogWrite(EN_RIGHT, m_pwmRight);
   analogWrite(EN_LEFT, m_pwmLeft);
   GoHead(); 
}

void Driver::SetPWMLeft(uint8_t pwm)
{
  m_pwmLeft = pwm;
}

void Driver::SetPWMRight(uint8_t pwm)
{
  m_pwmRight = pwm;
}

uint8_t Driver::GetPWMLeft()
{
  return m_pwmLeft;
}

uint8_t Driver::GetPWMRight()
{
  return m_pwmRight;
}

Driver::Driver()
{
  m_pwmRight = PWM;
  
  int iTemp = EEPROM.read(gAddressEEPROM);
  if (iTemp < PWM - 55 || iTemp > PWM + 55)
    m_pwmLeft = PWM;
  else
    m_pwmLeft = iTemp;
    
  m_isStop = true;
}

Driver::~Driver()
{
  
}
