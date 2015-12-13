#ifndef __EYE_H__
#define __EYE_H__
#include <Servo.h>

class Eye
{
  public:
    void Setup();
    bool HaveObstacle();
    bool CanGo(long distance);
    bool HaveObstacle_NonIR();
    void Turn(Direct dir);
    static Eye * GetInstance();
    static void Release();
    float GetDistance();
    
  private:
    static Eye * m_instance;
    Servo m_servo;
    Eye();
    ~Eye();
};
#endif 
