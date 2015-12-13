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
  Driver::GetInstance()->GoHead();
  
  while (!Eye::GetInstance()->HaveObstacle() && !Driver::GetInstance()->IsGoBack())
  {
    Serial.println("IN WHILE");
    // Do nothing.
  }
  
  // Stop motor.
  Driver::GetInstance()->Stop();
  ///////////////////////////////////////////////////////////////
  // TURN LEFT
  if (Driver::GetInstance()->CanTurnLeft())
  {
    Serial.println("TRAI");
    Driver::GetInstance()->TurnLeft();
  }
  else
  {
    ////////////////////////////////////////////////////////
    // TURN RIGHT
    if (Driver::GetInstance()->CanTurnRight())
    {
      Serial.println("PHAI");
      Driver::GetInstance()->TurnRight();
    }
    else
    {
      ////////////////////////////////////////////////////////
      // GO BACK
      Serial.println("LUI");
      Driver::GetInstance()->GoBack();
      delay(200);
    }
  }
}

void setup() {
  Eye::GetInstance()->Setup();
  Driver::GetInstance()->Setup();
  Encoder::GetInstance()->Setup();

  // Start driver and run
  Driver::GetInstance()->Start();
  Serial.begin(9600);
}

void loop() {
  //BalanceIFButtonPUSH();
  ObstacleAvoidance();
}
