#include "Define.h"
#include "Encoder.h"

Encoder * Encoder::m_instance = NULL;

Encoder * Encoder::GetInstance()
{
  if (m_instance == NULL)
      m_instance = new Encoder();
  return m_instance;
}

void Encoder::Release()
{
  delete m_instance;
  m_instance = NULL;
}

void Encoder::Setup()
{
  pinMode(ENCODER_LEFT, INPUT);
  pinMode(ENCODER_RIGHT, INPUT);
  m_pinInterruptL = digitalPinToInterrupt(ENCODER_LEFT);
  m_pinInterruptR = digitalPinToInterrupt(ENCODER_RIGHT);
  m_pulsesDetectL = 0;
  m_pulsesDetectR = 0;
}

void Encoder::Reset(Wheel type)
{
  if (type == Wheel::RIGHT)
    detachInterrupt(m_pinInterruptR);
  
  if (type == Wheel::LEFT)
    detachInterrupt(m_pinInterruptL);
}

void Encoder::ResetPulsesDetect(Wheel type)
{
  if (type == Wheel::RIGHT)
     m_pulsesDetectR = 0;
  
  if (type == Wheel::LEFT)
     m_pulsesDetectL = 0;
}

void Encoder::Set(Wheel type)
{
  if (type == Wheel::LEFT)
    attachInterrupt(m_pinInterruptL, InterruptCounterLeft, FALLING);

  if (type == Wheel::RIGHT)
    attachInterrupt(m_pinInterruptR, InterruptCounterRight, FALLING);
}

void Encoder::Wait(unsigned long numPulses, Wheel type)
{
  if (type == Wheel::LEFT)
  {
    while(m_pulsesDetectL < numPulses)
    {
      // Do nothing;
    }
  }

  if (type == Wheel::RIGHT)
  {
    while(m_pulsesDetectR < numPulses)
    {
      // Do nothing;
    }
  }
}

unsigned long Encoder::GetPulsesDetect(Wheel type)
{
  if (type == Wheel::RIGHT)
    return m_pulsesDetectR;

  if (type == Wheel::LEFT)
    return m_pulsesDetectL;
}

void Encoder::IncreasePulsesDetect(Wheel type)
{
  if (type == Wheel::RIGHT)
    m_pulsesDetectR++;

  if (type == Wheel::LEFT)
    m_pulsesDetectL++;
}

void InterruptCounterLeft()
{
  Encoder::GetInstance()->IncreasePulsesDetect(Wheel::LEFT);
}

void InterruptCounterRight()
{
  Encoder::GetInstance()->IncreasePulsesDetect(Wheel::RIGHT);
}

Encoder::Encoder()
{
}

Encoder::~Encoder()
{
}
