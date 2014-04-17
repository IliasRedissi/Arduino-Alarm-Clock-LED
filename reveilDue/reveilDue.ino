#include <SerialLCD.h>
#include <ChainableLED.h>
#include <Scheduler.h>

#define NUM_LEDS  5

float heure = 0;
float minute = 0;
float seconde = 0;
float temp_heure = 0;
float temp_minute = 0;
float temp_seconde = 0;
float reveil_heure = 0;
float reveil_minute = 0;
bool pression = false;
bool reveilActivate = false;
bool configurated = false;
bool heureConfigure = false;
bool minuteConfigure = false;
bool secondeConfigure = false;
float hue = 0.0;
boolean maxi = true;
double blue = 0;
SerialLCD slcd;
ChainableLED leds(7, 8, NUM_LEDS);
int reveilDebut = 0;
int reveilFin = 0;
void setup() {
  // put your setup code here, to run once:
  
  Scheduler.startLoop(reveil);
  Scheduler.startLoop(horloge);
  Scheduler.startLoop(reveilActivated);
  Serial.begin(9600);
  slcd.begin();
  pinMode(2, INPUT);	//Switcher
  pinMode(3, INPUT);	//Bouton1
  pinMode(4, INPUT);	//Bouton2
  for (byte i=0; i<NUM_LEDS; i++)
    leds.setColorHSB(i, 0, 0, 0);
}

void loop() {
  if (configurated)
  {
    afficherHeure(4);
    delay(1000);

  }
  else
  {
    configuration();
  }
}

void horloge() 
{
  seconde++;
  if(seconde > 59)
  {
    seconde = 0;
    minute++;
  }
  if(minute > 59)
  {
    minute = 0;
    heure++;
  }
  if(heure > 23)
  {
    heure = 0;
  }
  delay(1000);
  
}

void reveil()
{
  if(reveilActivate && configurated){
    afficherReveil();
    if(digitalRead(3) == HIGH)
    {
      reveil_heure++;
      pression = true;
      slcd.backlight();
    }
  
    if(digitalRead(4) == HIGH)
    {
      pression = true;
      reveil_minute++;
      slcd.backlight();
      
    }
    
    if (reveil_minute >= 60) {reveil_minute =0; reveil_heure++;}
    if (reveil_heure >= 24) {reveil_heure =0;}
    if (reveil_minute < 30)
    {
      reveil_heure-1 == -1 ? reveilDebut = 23*60 + reveil_minute + 30 : reveilDebut = (reveil_heure-1)*60+reveil_minute+30;
      reveilFin = reveil_heure*60+reveil_minute;
    }
    else
    {
      reveilDebut = reveil_heure*60+reveil_minute - 30;
      reveilFin = (reveil_heure + 1)*60+(int((reveil_minute + 30)) % 60);
    }
  }
  else
  {
    effacer(1);
  }
  digitalRead(2) == HIGH ? reveilActivate = true : reveilActivate = false;
  delay(225);
}

void afficherHeure(int column)
{ 
  /* Horloge */
  if(configurated)
  {
    slcd.setCursor(column,0);
    if(heure < 10)
    {
      slcd.print("0");
    }
    slcd.print(heure, DEC);
    slcd.print(":");
    if(minute < 10)
    {
      slcd.print("0");
    }
    slcd.print(minute, DEC);
    slcd.print(":");
    if(seconde < 10)
    {
      slcd.print("0");
    }
    slcd.print(seconde, DEC);
  }
  else
  {
    slcd.setCursor(column,0);
    if(temp_heure < 10)
    {
      slcd.print("0");
    }
    slcd.print(temp_heure, DEC);
    slcd.print(":");
    if(temp_minute < 10)
    {
      slcd.print("0");
    }
    slcd.print(temp_minute, DEC);
    slcd.print(":");
    if(temp_seconde < 10)
    {
      slcd.print("0");
    }
    slcd.print(temp_seconde, DEC);
  }


 }

 void afficherReveil(){ 
  /* Réveil */
  slcd.setCursor(0,1);
  slcd.print("Reveil : ");
  if(reveil_heure < 10)
  {
    slcd.print("0");
  }
  slcd.print(reveil_heure, DEC);
  slcd.print(":");
  if(reveil_minute < 10)
  {
    slcd.print("0");
  }
  slcd.print(reveil_minute, DEC);
}

void effacer(int row)
{
  slcd.setCursor(0,row);
  for (int i = 0; i < 16; i++)
  {
    slcd.print(" ");
  }
}


void configuration()
{
    slcd.setCursor(4,0);
    while(!heureConfigure)
    {
      if(digitalRead(4) == HIGH)
      {
        heureConfigure = true;
      }
      if(digitalRead(3) == HIGH)
      {
        temp_heure++;
      }
      if (temp_heure >= 24) {temp_heure = 0;}
      afficherHeure(4);
      delay(200);
    }
    
    while(!minuteConfigure)
    {
      if(digitalRead(4) == HIGH)
      {
        minuteConfigure = true;
        seconde = 0;
        minute = temp_minute;
        heure = temp_heure;
        configurated = true;
      }
      if(digitalRead(3) == HIGH)
      {
        temp_minute++;
      }
      if (temp_minute >= 60) {temp_minute = 0;}
      afficherHeure(4);
      delay(200);
    }

}

void reveilActivated()
{
  Serial.print("Heure actuelle en minutes : ");
  Serial.println(heureEnMinute());
  Serial.print("reveilDebut : ");
  Serial.println(reveilDebut);
  Serial.print("reveilFin : ");
  Serial.println(reveilFin);
  if(configurated && reveilActivate && minute == reveil_minute && heure == reveil_heure)
  {
    if(maxi)
    {
      for (byte i=0; i<NUM_LEDS; i++)
          leds.setColorRGB(i, 0, 0 , blue);
          delay(25);
    
          blue += 1;
            
          if (blue>=255)
            maxi = false;
    }
  }
  else
  { 
    for (byte i=0; i<NUM_LEDS; i++)
      leds.setColorHSB(i, 0, 0, 0);
    maxi = true;
    blue = 0;
  }
  delay(1000);
  yield();
}

int heureEnMinute()
{
  return heure*60+minute;
}