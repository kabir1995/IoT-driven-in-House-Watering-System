
// Wire Master Reader
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "xxxxxxx.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "HOME"
#define WIFI_PASSWORD "abcd12345"
int table[]={0,0,0};
int x1,x2,x3;
int val;
//byte data,sensor;
void setup()
   {
        Wire.begin(D1,D2); // join i2c bus (address optional for master)
        Serial.begin(115200);  // start serial for output
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        //WiFi.begin(WIFI_SSID);
        Serial.print("connecting");
        while (WiFi.status() != WL_CONNECTED) 
        {
        Serial.print(".");
        delay(100);
        }
        Serial.println();
        Serial.print("connected: ");
        Serial.println(WiFi.localIP());
        Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
        Serial.println("Welcome to IoT based Garded");
        Firebase.set("Plant 1/Water PUMP",0);
        Firebase.set("Plant 2/Water PUMP",0);
        Firebase.set("WATER Tank/Water PUMP",0);
        pinMode(D5, OUTPUT);
        pinMode(D6, OUTPUT);
        pinMode(D7, OUTPUT);

   }

        int n=0;
        int x=0;
        int y=0;

void soil1(){
  
      if (x1>=900){
                    Firebase.setString("Plant 1/Soil Sensor Status","Dry"); 
                    Serial.println("Soil_Sensor1/Status:Dry");
                    Firebase.setInt("Plant 1/Water PUMP",1);
                    //delay(3000);
                    //Firebase.setInt("WATER_PUMP/PUMP1",0);

                  }

      else if(x1<=350)       {
            
                    Firebase.setString("Plant 1/Soil Sensor Status","Too Wet") ;

                    Serial.println("Soil_Sensor1/Status:Too Wet");
                    Firebase.setInt("Plant 1/Water PUMP",0);
                  }
     else        {
                    Firebase.setString("Plant 1/Soil Sensor Status","Suitable"); 
                    Serial.println("Soil_Sensor1/Status:Suitable");
                    
                  }
                  

  
             }    

 void soil2(){
     if (x2>=900){
                    Firebase.setString("Plant 2/Soil Sensor Status","Dry"); 
                    Firebase.setInt("Plant 2/Water PUMP",1);
                    Serial.println("Soil_Sensor2/Status: Dry");
                    //delay(3000);
                    //Firebase.setInt("WATER_PUMP/PUMP2",0);
                    //return;
                  
                  }
      
else if(x2<=350)  {
              
              Firebase.setString("Plant 2/Soil Sensor Status","Too Wet");
            
              Serial.println("Soil_Sensor2/Status: Too Wet");
              Firebase.setInt("Plant 2/Water PUMP",0);
              //return;
                  }
                  
      else       {
                    Firebase.setString("Plant 2/Soil Sensor Status","Suitable"); 
                  
                    Serial.println("Soil_Sensor2/Status: Suitable");
               
                  }
  
              }    
void ultra(){
  
         if (x3>=9)  {
                    Firebase.setString("WATER Tank/Ultrasonic Sensor Status","Water Level Low"); 
                    Firebase.setInt("WATER Tank/Water PUMP",1);
                    Serial.println("Pumping Water------");
                    //delay(5000);
                    //Firebase.setInt("WATER_PUMP/PUMP3",0);
                   // Serial.println("Stop Pumping");
                    //return;
                  
                  }

        else if(x3<=4) {
              
              Firebase.setString("WATER Tank/Ultrasonic Sensor Status","Sufficient");
            
              
              Firebase.setInt("WATER Tank/Water PUMP",0);
              //return;
                  }
                                    
        else   {
                    Firebase.setString("WATER Tank/Ultrasonic Sensor Status","Enough Water"); 
                    Serial.println("Enough Water------");

                  }
  
              }

void loop()
{

  Wire.requestFrom(8, 5);    // request 3 bytes from slave device #2
  for(int i=0;i<3;i++)
    { 
    int c = Wire.read(); // receive a byte as character 
    table[i]=c;   
    }
    
     x1=(table[0])*10;
     x2=(table[1])*10;
     x3=table[2];
    
     soil1();
     soil2();
     ultra();
                         

        Firebase.setFloat("Plant 1/Soil Sensor Moisture Level",x1);
        Serial.print("Soil_Sensor1/Level: ");
        Serial.println(x1);
        Firebase.setFloat("Plant 2/Soil Sensor Moisture Level",x2);
        Serial.print("Soil_Sensor2/Level: ");
        Serial.println(x2);
        Firebase.setFloat("WATER Tank/Distance from Water Surface",x3);
        Serial.print("Sensor_Data/Ultrasonic_Sensor: ");
        Serial.println(x3);
x = Firebase.getInt("Plant 1/Water PUMP");
n = Firebase.getInt("Plant 2/Water PUMP");
y = Firebase.getInt("WATER Tank/Water PUMP"); 
 
if (x==0&n==0&y==0) 
          {
          Serial.println("PUMP1 OFF,PUMP2 OFF,PUMP3 OFF");
          digitalWrite(D5,LOW);
          digitalWrite(D6,LOW);
          digitalWrite(D7,LOW);  
          Firebase.setString("Plant 1/Water PUMP Status","OFF");
          Firebase.setString("Plant 2/Water PUMP Status","OFF");
          Firebase.setString("WATER Tank/Water PUMP Status","OFF");
          }
else if(x==0&n==0&y==1)
           {
          Serial.println("PUMP1 OFF,PUMP2 OFF,PUMP3 ON");
          digitalWrite(D5,LOW);
          digitalWrite(D6,LOW); 
          digitalWrite(D7,HIGH);  
          Firebase.setString("Plant 1/Water PUMP Status","OFF");
          Firebase.setString("Plant 2/Water PUMP Status","OFF");
          Firebase.setString("WATER Tank/Water PUMP Status","ON");

           }
else if(x==0&n==1&y==0)
           {
          Serial.println("PUMP1 OFF,PUMP2 ON,PUMP3 OFF");
          digitalWrite(D5,LOW);
          digitalWrite(D6,HIGH); 
          digitalWrite(D7,LOW);  
          Firebase.setString("Plant 1/Water PUMP Status","OFF");
          Firebase.setString("Plant 2/Water PUMP Status","ON");
          Firebase.setString("WATER Tank/Water PUMP Status","OFF");

           }
else if(x==0&n==1&y==1)
           {
          Serial.println("PUMP1 OFF,PUMP2 ON,PUMP3 ON");
          digitalWrite(D5,LOW);
          digitalWrite(D6,HIGH); 
          digitalWrite(D7,HIGH);  
          Firebase.setString("Plant 1/Water PUMP Status","OFF");
          Firebase.setString("Plant 2/Water PUMP Status","ON");
          Firebase.setString("WATER Tank/Water PUMP Status","ON");

           }
else if(x==1&n==0&y==0)
           {
          Serial.println("PUMP1 ON,PUMP2 OFF,PUMP3 OFF");
          digitalWrite(D5,HIGH);
          digitalWrite(D6,LOW); 
          digitalWrite(D7,LOW);  
          Firebase.setString("Plant 1/Water PUMP Status","ON");
          Firebase.setString("Plant 2/Water PUMP Status","OFF");
          Firebase.setString("WATER Tank/Water PUMP Status","OFF");

           }
else if(x==1&n==0&y==1)
           {
          Serial.println("PUMP1 ON,PUMP2 OFF,PUMP3 ON");
          digitalWrite(D5,HIGH);
          digitalWrite(D6,LOW); 
          digitalWrite(D7,HIGH);  
          Firebase.setString("Plant 1/Water PUMP Status","ON");
          Firebase.setString("Plant 2/Water PUMP Status","OFF");
          Firebase.setString("WATER Tank/Water PUMP Status","ON");

           }
else if(x==1&n==1&y==0)
           {
          Serial.println("PUMP1 ON,PUMP2 ON,PUMP3 OFF");
          digitalWrite(D5,HIGH);
          digitalWrite(D6,HIGH); 
          digitalWrite(D7,LOW);  
          Firebase.setString("Plant 1/Water PUMP Status","ON");
          Firebase.setString("Plant 2/Water PUMP Status","ON");
          Firebase.setString("WATER Tank/Water PUMP Status","OFF");

           }           
else
          {
          Serial.println("PUMP1 ON,PUMP2 ON,PUMP3 ON");
          digitalWrite(D5,HIGH);
          digitalWrite(D6,HIGH); 
          digitalWrite(D7,HIGH);  
          Firebase.setString("Plant 1/Water PUMP Status","ON");
          Firebase.setString("Plant 2/Water PUMP Status","ON");
          Firebase.setString("WATER Tank/Water PUMP Status","ON");

           }

}


