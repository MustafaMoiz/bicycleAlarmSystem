#define BUTTON_0 digitalRead(2)
#define BUTTON_1 digitalRead(3)
#define BUTTON_2 digitalRead(4)
#define ALARM digitalRead(5)

int PASSCODE1[] = {1,2,3};
int PASSCODE2[] = {2,1,3};
int i;
int button[] = {0,0,0};
int relay = 13;
bool unlocked = false;
bool toggle = false;

void stage1()
{
  if (unlocked)
  {
    if (ALARM == LOW)
    {
      digitalWrite(12, LOW);
      while (1)
      {
        while(ALARM == HIGH)
        {
          Serial.println("Bicycle disconnected!");
          digitalWrite(10, HIGH);
          delay(1000);
          if (ALARM == LOW)
          {
            unlocked = !unlocked;
            Serial.print(unlocked);
            digitalWrite(10, LOW);
            delay(1000);
            stage1();
          }
        }    
      }
    }
  }

  else 
  {
    digitalWrite(12, HIGH);
  }
    while(1)
   {
    if ((ALARM == LOW || unlocked))
    {
      digitalWrite(relay, LOW);  
      button0Status();
      button1Status();
      button2Status();
      checkStage1();
   }   

   else 
   {
      soundAlarm();
   }
  }
}

void stage2()
{
    if(unlocked)
    {
      digitalWrite(12, LOW);
    }
    else
    {
      digitalWrite(12, HIGH);
    }
    
    while(1)
   {
    if (ALARM == LOW || unlocked)
    {    
      button0Status();
      button1Status();
      button2Status();
      checkStage2();
    }  

    else 
    {
      soundAlarm();
    }  
  }
}

void button0Status()
{
  if (BUTTON_0 == LOW)
  {
    button[0]++;
    Serial.println(button[0]);
    delay(300);
  }
}

void button1Status()
{
  if (BUTTON_1 == LOW)
  {
    button[1]++;
    Serial.println(button[1]);
    delay(300);
  }
}

void button2Status()
{
  if (BUTTON_2 == LOW)
  {
    button[2]++;
    Serial.println(button[2]);
    delay(300);
  }
}

void checkStage1()
{
  if (PASSCODE1[0] == button[0] && PASSCODE1[1] == button[1] && PASSCODE1[2] == button[2])
  {
    digitalWrite(12, LOW); 
    digitalWrite(11, HIGH); 
    delay(500);
    digitalWrite(11, LOW); 

    for (i=0; i<3; i++)
    {
      button[i] = 0;
    }

    stage2();
  }
}

void checkStage2()
{
  if (PASSCODE2[0] == button[0] && PASSCODE2[1] == button[1] && PASSCODE2[2] == button[2])
  {
    digitalWrite(12, LOW); 
    for(i=0; i<3; i++)
    {
      digitalWrite(11, HIGH); 
      delay(500);
      digitalWrite(11, LOW); 
      delay(500);
    }

    for (i=0; i<3; i++)
    {
      button[i] = 0;
    }
    
    unlocked = !unlocked;
    Serial.println(unlocked);
    stage1();
  }
}

void soundAlarm()
{
  while(1)
  {
    digitalWrite(12, LOW);
    digitalWrite(relay, HIGH);
    delay(100);
    digitalWrite(relay, LOW);
    delay(1000);
  }
}

void setup() {

  Serial.begin(9600);
  for (i=9; i<13; i++)
  {
    pinMode(i, OUTPUT);
  }

  for (i=2; i<6; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }

  stage1();
}

void loop() {

}
