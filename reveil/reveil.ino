


// LCD : UART     Switcher : D2   Button : D3/D4   Clock : I2C
// Speaker : D8

//#include <SoftwareSerial.h>
//#include <SerialLCD.h>
#include <Wire.h>
#include <DS1307.h>
#include <ChainableLED.h>
#include <Arduino.h>


#define NUM_LEDS 5

//SerialLCD slcd(0 , 1);
ChainableLED leds(7, 8, NUM_LEDS);



DS1307 clock; //define a object of DS1307 class 

int switcher = 0;
int button1 = 0;
int button2 = 0;

int h = 0, m = 0;

float time;

void setup()
{
  //slcd.begin();
  Serial.begin(9600);
  clock.begin();
  clock.fillByYMD(2013,1,19); // Jan 19,2013
  clock.fillByHMS(23,59,30); // 15:28:30
  clock.fillDayOfWeek(SAT); // Saturday
  clock.setTime(); // write time to the RTC chip
  
  pinMode(2, INPUT);	//Switcher
  pinMode(3, INPUT);	//Bouton1
  pinMode(4, INPUT);	//Bouton2
}
 
void loop() 
{
  if(time <= 0)
  {
    //slcd.noBacklight();  // Turn on the backlight
  }
  switcher = digitalRead(2);
  button1 = digitalRead(3);
  button2 = digitalRead(4);
  
  clock.getTime();
  //slcd.setCursor(0,0);
  
  if(clock.hour < 10)
  {
    //slcd.print("0");
    Serial.print("0")
  }
  Serial.print(float(clock.hour),DEC);
  
  Serial.print(":");
  
  if(clock.minute < 10)
  {
    SerialSerial.print("0");
  }
  Serial.print(float(clock.minute),DEC);
  
  Serial.print(":");
  
  if(clock.second < 10)
  {
    Serial.print("0");
  }
  Serial.print(float(clock.second),DEC);
  
  //Serial.setCursor(0,1);
  Serial.print("Reveil: ");
  if(h < 10)
  {
    Serial.print("0");
  }
  Serial.print(float(h), DEC);
  Serial.print(":");
  
  if(m < 10)
  {
    Serial.print("0");
  }
  Serial.print(float(m), DEC);
  Serial.print(" ");
    
  /*if(switcher == HIGH)
  {
    Serial.setCursor(13,0);
    Serial.print(" ON");
  }
  else
  {
    Serial.setCursor(13,0);
    Serial.print("OFF");
  }*/
  
  if(button1 == HIGH)
  {
    h++;
    delay(125);
    time = 70.0f;
    //Serial.backlight();  // Turn on the backlight
  }
  
  if(button2 == HIGH)
  {
    m++;
    delay(125);
    time = 70.0f;
    //Serial.backlight();  // Turn on the backlight
  }
  
  if(h == 24)
  {
    h = 0;
  }
  
  if(m == 60)
  {
    m = 0;
    h++;
  }
  time--;
}


