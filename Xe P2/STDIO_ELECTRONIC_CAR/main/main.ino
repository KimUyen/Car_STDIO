#include "Define.h"
#include "Driver.h"
#include "Encoder.h"
#include "Eye.h"
#include "Regulator.h"

unsigned long gTimeToUpdatePWM = 200; // milisecond
unsigned long gTimeOld = 0;           // get time when start push button
float gDistanceR, gDistanceL;
int i = 0;
bool gIsGoBack = false;

void BalanceIFButtonPUSH()
{
  // Balance if button is pushed
  // If button is pushed -> check Time To update pwm. Else -> Write to EEPROM if have no write yet.
  
  if (Regulator::GetInstance()->IsActive())
  {
    Regulator::GetInstance()->ResetWasWriteToEEPROM();
    // Stop interrupt and update pwmLeft
    if (millis() - gTimeOld > gTimeToUpdatePWM)
    {
      Regulator::GetInstance()->StopBalance();
      Regulator::GetInstance()->StartBalance(HOLES_FOR_TURN);
    }
  }
  else // write when button didn't pushed.
  {
    Regulator::GetInstance()->StopBalance();
    Regulator::GetInstance()->WritePWMToEEPROM();
  }
}

void ObstacleAvoidance()
{
  // Go Head until detect obstacle.
  Eye::GetInstance()->Turn(Direct::CENTER);
  Driver::GetInstance()->GoHead();
  
  while (!Eye::GetInstance()->HaveObstacle() && gIsGoBack == false)
  {
    // Do nothing.
  }
  
  // Detect obstacle and controler direction
  // If in front of car have obstacle -> Check right or left obstacle -> Di chuyen den noi khong vat can, uu tien huong co khoang cach den vat can nho hon.
  
  // Stop motor.
  Driver::GetInstance()->Stop();

  /////////////////////////////////////////////////////////////
  // Get distance to Direct Left
  Eye::GetInstance()->Turn(Direct::L);
  gDistanceL = Eye::GetInstance()->GetDistance();
  delay(100);
    
  // Nếu bên trái khoảng cách đến vật cản có thể chấp nhận thì đi theo hướng này
  ////////////////////////////////////////////////////////////
  if (!Eye::GetInstance()->CheckObstacle(gDistanceL))
  {
    Driver::GetInstance()->TurnLeft();
    gIsGoBack = false;
  }
  else
  {
    /////////////////////////////////////////////////////////
    Eye::GetInstance()->Turn(Direct::R);
    gDistanceR = Eye::GetInstance()->GetDistance();
    delay(100);

    // Nếu bên phải khoảng cách đến vật cản có thể chấp nhận thì đi theo hướng này
    ////////////////////////////////////////////////////////
    if (!Eye::GetInstance()->CheckObstacle(gDistanceR))
    {
      Driver::GetInstance()->TurnRight();
      gIsGoBack = false;
    }
    else
    {
      // Nếu không, đi lùi
      //////////////////////////////////////////////////////
      gIsGoBack = true;
      Eye::GetInstance()->Turn(Direct::CENTER);
      Driver::GetInstance()->GoBack();
      delay(100);
    }
  }
}

void setup() {
  Eye::GetInstance()->Setup();
  Driver::GetInstance()->Setup();
  Encoder::GetInstance()->Setup();

  // Start driver and run
  Driver::GetInstance()->Start();
}

void loop() {
  Driver::GetInstance()->TurnLeft();
  Driver::GetInstance()->Stop();
  delay(1);
  //BalanceIFButtonPUSH();
  //ObstacleAvoidance();
}
