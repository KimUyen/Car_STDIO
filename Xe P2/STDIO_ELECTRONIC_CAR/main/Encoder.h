#ifndef __ENCODER_H__
#define __ENCODER_H__

void InterruptCounterLeft();
void InterruptCounterRight();
    
class Encoder
{
  public:
    void Setup();
    void Reset(Wheel type);
    void ResetPulsesDetect(Wheel type);
    void IncreasePulsesDetect(Wheel type);
    void Set(Wheel type);
    void Wait(unsigned long numPulses, Wheel type);
    unsigned long GetPulsesDetect(Wheel type);
    static Encoder * GetInstance();
    static void Release();
    
  private:
    static Encoder * m_instance;
    
    uint8_t m_pinInterruptL;
    uint8_t m_pinInterruptR;
    volatile unsigned long m_pulsesDetectL;
    volatile unsigned long m_pulsesDetectR;

    Encoder();
    ~Encoder();
};
#endif
