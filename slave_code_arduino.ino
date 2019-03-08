
// Wire Slave Sender

#include <Wire.h>
int table[]={0,0,0};
int x1,x2;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
int soil11,soil22;
void setup()
{
  Serial.begin(115200);
  Wire.begin(8);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  
}

void loop()
{

  soil1();
  soil2();
  ultrasonic();

  Serial.print("Soil1: ");
  Serial.print(soil11);
  Serial.print('\t');
  Serial.print("Soil2: ");
  Serial.print(soil22);
  Serial.print('\t');
  Serial.print("Distance: ");
  Serial.println(table[2]);

  delay(2000);
}


    void requestEvent()
     {
       uint8_t Buffer[3];
       Buffer[0]=table[0];
       Buffer[1]=table[1];
       Buffer[2]=table[2];
       Wire.write(Buffer,3); 
                         
       }


  
void ultrasonic()
    {
    
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distance= duration*0.034/2;
        table[2]=distance;
     }
void soil1()
  {
      x1=(analogRead(A0))/10;
      table[0]=x1;
      soil11=(table[0])*10;
     
  }

void soil2()
  {
      x2=(analogRead(A1))/10;
      table[1]=x2;
      soil22=(table[1])*10;
     
  }


