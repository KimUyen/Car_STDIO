int cambien = 4;
int led = 1;

void setup() {
  pinMode(led,OUTPUT);
  pinMode(cambien, INPUT_PULLUP);

}

void loop() {
  if(digitalRead(cambien) == 0)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }

}
