#ifndef __REGULATOR_H__
#define __REGULATOR_H__

class Driver;
class Encoder;
class Regulator
{
  public:
    void StartBalance(unsigned long numPulses);
    void StopBalance();
    bool IsActive();
    void ResetWasWriteToEEPROM();
    void WritePWMToEEPROM();
    static Regulator * GetInstance();
    static void Release();
    
  private:
    static Regulator * m_instance;
    bool    m_isActive;
    bool    m_wasWriteToEEPROM;
    Regulator();
    ~Regulator();
};

#endif
