#include "Define.h"
#include "Driver.h"
#include "Encoder.h"
#include "Regulator.h"

Regulator * Regulator::m_instance = NULL;

Regulator * Regulator::GetInstance()
{
  if (m_instance == NULL)
      m_instance = new Regulator();
  return m_instance;
}

void Regulator::Release()
{
  delete m_instance;
  m_instance = NULL;
}

void Regulator::StartBalance(unsigned long pulsesNumRight)
{
  m_isActive = true;
  if (Driver::GetInstance()->IsStop())
  {
    return;
  }
  
  Encoder::GetInstance()->Set(Wheel::LEFT);
  Encoder::GetInstance()->Set(Wheel::RIGHT);
}

void Regulator::StopBalance()
{
  if (m_wasWriteToEEPROM)
    return;
    
  Encoder::GetInstance()->Reset(Wheel::LEFT);
  Encoder::GetInstance()->Reset(Wheel::RIGHT);

  unsigned long pulsesL = Encoder::GetInstance()->GetPulsesDetect(Wheel::LEFT);
  unsigned long pulsesR = Encoder::GetInstance()->GetPulsesDetect(Wheel::RIGHT);
  
  // calculate
  if (pulsesL != 0 && pulsesR != 0)
      Driver::GetInstance()->SetPWMLeft(pulsesL * Driver::GetInstance()->GetPWMRight() / pulsesR);  
  
  Encoder::GetInstance()->ResetPulsesDetect(Wheel::LEFT);
  Encoder::GetInstance()->ResetPulsesDetect(Wheel::RIGHT);
  m_wasWriteToEEPROM = true;
}

bool Regulator::IsActive()
{
  return m_isActive;
}

Regulator::Regulator()
{
  m_isActive = false;
  m_wasWriteToEEPROM = false;
}
    
Regulator::~Regulator()
{
  
}

void Regulator::ResetWasWriteToEEPROM()
{
  if (m_wasWriteToEEPROM)
      m_wasWriteToEEPROM = false;
}

void Regulator::WritePWMToEEPROM()
{
  if (!m_wasWriteToEEPROM)
      EEPROM.write(gAddressEEPROM, Driver::GetInstance()->GetPWMLeft());
}
