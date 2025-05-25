//#define BLYNK_TEMPLATE_ID "TMPL3kwyc7m9z"
//#define BLYNK_TEMPLATE_NAME "WASTEBINPROJECT"
//#define BLYNK_AUTH_TOKEN "iuxI4A9cvB2PjnPIzQoQF8ynub4eOnHn"
//
//#define BLYNK_PRINT Serial
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <BlynkSimpleEsp32.h>
//
//char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "AK";  
//char pass[] = "12345678";

#include <ESP32Servo.h>
#include <NewPing.h>
Servo right;
Servo left;
#define IN1 13
#define IN2 12
#define IN3 14
#define IN4 26
#define highpin 34
int servoflag=0;
int searchingflag=0;
int flag=0;
int flg=0;
int returnflag=0;
int pos1=120;
int pos2=120;
void vehicle();
void returnvehicle();

#define TRIGGER_PIN 5  
#define ECHO_PIN1 4  
#define ECHO_PIN2 15  
#define MAX_DISTANCE 200 
NewPing sonar1(TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE); 
NewPing sonar2(TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE);

void setup() 
{
  Serial.begin(9600);
  //Blynk.begin(auth, ssid, pass); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(highpin,INPUT);
  right.attach(21,500,2400);
  left.attach(23,500,2400);
  vehicle();
  
}
void vehicleforward() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void vehicleleft() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void vehicleright() 
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void vehicleback()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void vehicleStop() 
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  flg=0;
  ultra();
  if(flg==1)
  {
     vehicleStop(); 
  }
}

void vehicle()                                    //FIRST PATTERN
{ 
    Serial.println("vehicleforward");
    vehicleforward();
    delay(5000);
    ultra();
    if(flg==1)
    {
      vehicleStop(); 
    }
    Serial.println("vehicleright");
    vehicleright();
    delay(2000);
    ultra();
    if(flg==1)
    {
      vehicleStop(); 
    }
    Serial.println("vehicleforward");
    vehicleforward();
    delay(5000);
    ultra();
    if(flg==1)
    {
      vehicleStop(); 
    }
     Serial.println("vehiclestop");
     vehicleStop();
     delay(1000);
     flag=1;
  
}
void returnvehicle()                           //RETURNING PATTERN
{
    if(returnflag==0)
    {
    Serial.println("vehicleback");
    vehicleback();
    delay(3000);
    Serial.println("vehicleleft");
    vehicleleft();
    delay(5000);
    ultra();
    if(flg==1)
    {
      vehicleStop(); 
    }
    Serial.println("vehicleforward");
    vehicleforward();
    delay(5000);
    ultra();
    if(flg==1)
    {
      vehicleStop(); 
    }
    Serial.println("vehicleleft");
    vehicleleft();
    delay(2000);
    ultra();
    if(flg==1)
    {
      vehicleStop(); 
    }
    Serial.println("vehicleforward");
    vehicleforward();
    delay(5000);
    ultra();
    if(flg==1)
    {
      vehicleStop(); 
    }
    Serial.println("vehiclestop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    returnflag=1;
    searchingflag=1;
    }
    else
    {
     vehicleStop(); 
    }
}
void ultra()                                          //ULTRASONIC OBSTACLE CODE
{
  Serial.print(sonar2.ping_cm()); 
  Serial.println("cm");
   if(sonar2.ping_cm()<=10)
  {
    Serial.println("OBSTACLE DETECTED");
    flg=1;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(1000);
    
  }
  else
  {
    Serial.println("NO OBSTACLE");     
  }
}
void loop()                                  //VOID LOOP AND BIN STATUS ULTRASONIC
{ 
  //Blynk.run();
  int pinstatus=digitalRead(34);
  Serial.println(pinstatus);
  Serial.print("Ping1: ");
  int ult=sonar1.ping_cm();
  Serial.print(ult); 
  Serial.println("cm");
   if(ult<=8)
  {
    Serial.println("BIN IS  FULL");
   // Blynk.virtualWrite(V0,"BIN IS  FULL");
  }
  else
  {
    Serial.println("BIN IS EMPTY");
   //Blynk.virtualWrite(V0,"BIN IS EMPTY"); 
  }
  if(flag==1)
  {
    if(pinstatus==HIGH)                      //WASTE BIN PICKING BY SERVO
    {
    if(servoflag==0)
    {
    vehicleStop();
    delay(1000);
    vehicleforward();
    delay(3000);
    vehicleStop();
    Serial.println("WASTE DUMPING");
     for (pos1 =120; pos1 >= 0; pos1--)          
      {
      right.write(pos1);
      pos2 = map(pos1, 0, 120, 120, 0);
      left.write(pos2);                  
      delay(15);                       
      }     
     delay(1000);                       
     for (pos1 = 0; pos1 <= 120; pos1++)          
      {
      right.write(pos1);
      pos2 = map(pos1, 120, 0, 0, 120);
      left.write(pos2);                  
      delay(15);                       
      } 
      servoflag=1;
      returnvehicle();
    }      
    }
   else
   {
    Serial.println("no bin found"); 
    if(searchingflag==0)
    {
    vehicleStop();
    delay(1000);
    vehicleright();
    delay(2500);
    vehicleleft();
    delay(5000);
    vehicleright();
    delay(2500);
    if(pinstatus==HIGH)
    { 
    if(servoflag==0)
    {
    vehicleforward();
    delay(3000);
    vehicleStop();
    Serial.println("WASTE DUMPING");
     for (pos1 =120; pos1 >= 0; pos1--)          
      {
      right.write(pos1);
      pos2 = map(pos1, 0, 120, 120, 0);
      left.write(pos2);                  
      delay(15);                       
      }     
     delay(1000);                       
     for (pos1 = 0; pos1 <= 120; pos1++)          
      {
      right.write(pos1);
      pos2 = map(pos1, 120, 0, 0, 120);
      left.write(pos2);                  
      delay(15);                       
      }
      servoflag=1;
      returnvehicle();   
     }
    }
     else
     {
      Serial.println("returning vehicle");
      returnvehicle();
     }
   }
   } 
 }
