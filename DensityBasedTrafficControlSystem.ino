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

Servo servo[4]; // Create an array of 4 servo objects

void setup() {
  for (int i = 0; i < 4; i++) { // Correct the loop termination condition to 4
    pinMode(ExPin[i], INPUT);
    pinMode(EnPin[i], INPUT);
    pinMode(ServoPin[i], OUTPUT);
    servo[i].attach(ServoPin[i]); // Attach servos to their respective pins
  }

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop()
{
  // delay(2000);
  
  for (int i = 0; i < 4; i++) { 
    En[i] = digitalRead(EnPin[i]);
    Ex[i] = digitalRead(ExPin[i]);
  //   Serial.print(i);
  //   Serial.print("En :");
  //   Serial.print(En[i]);
  // Serial.println();
  //   Serial.print(i);
  //   Serial.print("Ex :");
  //   Serial.print(Ex[i]);
  //   Serial.println();
  //   Serial.println();
  
  }

  TrafficState();


  
}


void open(int i)
{
  servo[i].write(0);
}

void close(int i)
{
  servo[i].write(95);
}


void TrafficState()
{

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
  Serial.print("Num :");
  Serial.println(Num[i]);

  }


}

