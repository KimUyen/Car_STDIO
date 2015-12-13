#ifndef __DRIVER_H__
#define __DRIVER_H__

class Encoder;
class Eye;
class Driver
{
  public:
      void Setup();
      void Start();
      void GoHead();
      void GoBack();
      bool CanTurnLeft();
      bool CanTurnRight();
      void TurnLeft();
      void TurnRight();
      void Stop();
      bool IsStop();
      bool IsGoBack();
      void SetPWMLeft(uint8_t pwm);
      void SetPWMRight(uint8_t pwm);
      uint8_t GetPWMLeft();
      uint8_t GetPWMRight();
      static Driver * GetInstance();
      static void Release();
      
  private:
      static Driver * m_instance;
      Driver();
      ~Driver();
      volatile uint8_t m_pwmLeft;
      volatile uint8_t m_pwmRight;
      bool m_isStop;
      bool m_isGoBack;
};

#endif
