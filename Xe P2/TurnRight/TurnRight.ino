//Motor A
    int enA = 13;
    int in1 = 6;
    int in2 = 11;
     
    //Motor B
    int enB = 7;
    int in3 = 5;
    int in4 = 10;
     
    // Encoder
    #define ENCODER_LEFT  2
    #define ENCODER_RIGHT  3
    #define NUMPULSE_90 8
    volatile unsigned int pulses[2] = {0, 0};  // number of pulses
    typedef enum 
    {
      LEFT = 0,
      RIGHT = 1,
      CENTER
    }Direct;
    void setup()
    {
      pinMode(enA, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT); 
     
      pinMode(enB,OUTPUT);
      pinMode(in3, OUTPUT);
      pinMode(in4, OUTPUT); 
    }
    void STOP()
    {      
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      
    }
    void loop()
    {      
      turnRight();
      delay(1000);  
    }
    void turnRight()
    {  
      //Running motor A 
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH); 
      analogWrite(enA, 200); //Speed PWM: 0~255 
      //Running motor B
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enB, 200); //Speed PWM: 0~255  
     
      runEncoder (32,RIGHT);
      STOP();
    }
     
    void runEncoder (int numPulse, int direction)
    {
        attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), counter_left, FALLING);
        attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), counter_right, FALLING);
        
        while (pulses[direction] < numPulse)
        {
          // Do nothing
        }
        
        detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
        detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
        pulses[LEFT] = 0;
        pulses[RIGHT] = 0;
    }
     
     void counter_left()
     {
        //Update count
          pulses[LEFT]++;     
     }
     
      void counter_right()
     {
        //Update count
          pulses[RIGHT]++;      
     }
