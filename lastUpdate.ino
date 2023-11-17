#include <Servo.h>

int EnPin[4] = {46, 47, 48, 49};
int ExPin[4] = {50, 51, 52, 53};
int ServoPin[4] = {2, 3, 4, 5};
int En[4] = {0, 0, 0, 0};
int Ex[4] = {0, 0, 0, 0};
int Num[4] = {0, 0, 0, 0};
int EnSTATE[4] = {0, 0, 0, 0};
int ExSTATE[4] = {0, 0, 0, 0};
int EnTOGGLE[4] = {0, 0, 0, 0};
int ExTOGGLE[4] = {0, 0, 0, 0};
int Red[4] = {23, 25, 27, 29};
int Green[4] = {22, 24, 26, 28};


int DELAY_TIMEOUT =1000;
unsigned long tm = 0;
int max_value = 0;
int gate=0;


Servo servo[4]; // Create an array of 4 servo objects

void setup() {
  for (int i = 0; i < 4; i++) { // Correct the loop termination condition to 4
    pinMode(ExPin[i], INPUT);
    pinMode(EnPin[i], INPUT);
    pinMode(ServoPin[i], OUTPUT);
    pinMode(Green[i], OUTPUT);
    pinMode(Red[i], OUTPUT);
    
    servo[i].attach(ServoPin[i]); // Attach servos to their respective pins
  }

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop()
{
  // delay(2000);
  


  TrafficState();

  for (int i = 0; i < 4; i++) 
  {
    if (Num[i] <0)
    {
      EnTOGGLE[i] = 0;
      ExTOGGLE[i] = 0;
      TrafficState();
    }
  }
  
  
  
  Gatecontrol();
  // open(1);


  
}


void open(int i)
{
  servo[i].write(0);
  digitalWrite(Green[i],HIGH);
  digitalWrite(Red[i],LOW);
}

void close(int i)
{
  servo[i].write(95);
  digitalWrite(Green[i],LOW);
  digitalWrite(Red[i],HIGH);
}


void TrafficState()
{

  for (int i = 0; i < 4; i++) 
  { 
    En[i] = digitalRead(EnPin[i]);
    Ex[i] = digitalRead(ExPin[i]);
    // Serial.print(i);
    // Serial.print("En :");
    // Serial.print(En[i]);
    // // Serial.println();
    // Serial.print(i);
    // Serial.print(". Ex :");
    // Serial.println(Ex[i]);
    // Serial.println();
    // Serial.println();
  
  }  

  for( int i =0; i <4; i ++)
  {
    if(EnSTATE[i]==1 && En[i] == 1)
    {
      EnTOGGLE[i]++;
      EnSTATE[i]=0;
    }
    else if(EnSTATE[i]==0 && En[i] == 0)
    {
      EnSTATE[i]=1;
    }



    if(ExSTATE[i]==1 && Ex[i] == 1)
    {
      ExTOGGLE[i]++;
      ExSTATE[i]=0;
    }
    else if(ExSTATE[i]==0 && Ex[i] == 0)
    {
      ExSTATE[i]=1;
    }

  // Serial.print(i);
  // Serial.print("EnSTATE :");
  // Serial.print(EnSTATE[i]);
  // Serial.println();
  // Serial.print(i);
  // Serial.print("ExSTATE :");
  // Serial.print(ExSTATE[i]);
  // Serial.println();
  // Serial.println();

   Num[i] = EnTOGGLE[i] - ExTOGGLE[i];
 
  
  Serial.print(i);
  Serial.print(" . Num :");
  Serial.println(Num[i]);

  }


}




void Gatecontrol()
{

  max_value = 0;
 if (millis() - tm > DELAY_TIMEOUT) 
 {
 
      for (int i = 0; i < 4; i++) // find most densed lane
      {
        if (Num[i] > max_value && Num[i] > Num[gate]) 
        {
        max_value = Num[i];
        gate= i;
        }

        

      }


//  Serial.println(gate);
  if(max_value> 0)
  {
   open(gate); // open most densed lane
    tm = millis();
  }


    // close other gates
   for(int i =0 ; i < 4 ; i ++)
   {
      if(gate!= i)
      {
        close (i);
        tm = millis();
              
      }
      if (Num[i] ==0) 
      {
      close (i);
      tm = millis();
      }
    }
  }
}
