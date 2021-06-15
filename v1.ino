#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



const int okbutton = 2;
const int upbutton = 3;    
const int downbutton = 4; 
const int relaypin1 = 5;    
const int relaypin2 = 6; 
const int inflatepin = 7; 
const int deflatepin = 8; 
const int pumppin = 9; 
const int statepin = 10; 
int potpin = A0; 
    
int modestatus = 1;
int backrestangle = 0;
int hourt = 0;
int mint = 0;
int state = 0;



void setup() 
{
 Serial.begin(38400);
 delay(3000); // wait for console opening
 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) 
  {
    Serial.println("RTC lost power, lets set the time!");
 
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }

  
 lcd.init();                      
 pinMode(okbutton, INPUT);
 pinMode(upbutton, INPUT);
 pinMode(downbutton, INPUT);
 pinMode(relaypin1, OUTPUT);
 pinMode(relaypin2, OUTPUT);
 pinMode(inflatepin, OUTPUT);
 pinMode(deflatepin, OUTPUT);
 pinMode(pumppin, OUTPUT);
 pinMode(statepin, INPUT);

 digitalWrite(relaypin1, HIGH);
 digitalWrite(relaypin2, HIGH);
 digitalWrite(inflatepin, HIGH);
 digitalWrite(deflatepin, HIGH);
 digitalWrite(pumppin, HIGH);
}

void loop() 
{
  lcd.clear();
  while (modestatus ==1)
  {
   
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("MANUAL MODE  <--");
    lcd.setCursor(0,1);
    lcd.print("AUTO MODE");

    DateTime now = rtc.now();
    lcd.setCursor(0,3);
    lcd.print(now.hour(), DEC);  
    lcd.print(":");
    lcd.print(now.minute(), DEC);  
    lcd.print(":");
    lcd.print(now.second(), DEC);  
    
    if (digitalRead(okbutton) == HIGH)
    {
      modestatus = 3;     
    }
    else if (digitalRead(downbutton) == HIGH)
    {
      modestatus = 2;
    }
  }

  delay (300);
  lcd.clear();
 while (modestatus ==2)
  {
   
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("MANUAL MODE");
    lcd.setCursor(0,1);
    lcd.print("AUTO MODE    <--");

    DateTime now = rtc.now();
    lcd.setCursor(0,3);
    lcd.print(now.hour(), DEC);  
    lcd.print(":");
    lcd.print(now.minute(), DEC);  
    lcd.print(":");
    lcd.print(now.second(), DEC);  
    
    if (digitalRead(okbutton) == HIGH)
    {
      modestatus = 4;     
    }
    else if (digitalRead(upbutton) == HIGH)
    {
      modestatus = 1;
    }
  }
  
   delay (300);

    while (modestatus ==3)
  {
    int pval = analogRead(potpin);
    backrestangle = map(pval, 0, 1024, 45, 0);  
    lcd.clear();
    delay(2000);
    while (digitalRead(okbutton) == LOW)
    {
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("SET BACKREST ANGLE:");
      lcd.setCursor(5,2);
      lcd.print(backrestangle); 
      if (digitalRead(upbutton) == HIGH)
      {
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, LOW);
      }      
     else if (digitalRead(downbutton) == HIGH)
     {
        digitalWrite(relaypin1, LOW);
        digitalWrite(relaypin2, HIGH);
     }
      else
      {
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, HIGH);
      }
     pval = analogRead(potpin);
     backrestangle = map(pval, 0, 1024, 45, 0);    
        
    }






    
   /* int i = 1; 
    while (i==1)
    {
      int pval = analogRead(potpin);
      int pbrangle = map(pval, 0, 1024, 45, 0);  
      backrestangle = pbrangle;
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("SET BACKREST ANGLE:");
      lcd.setCursor(5,2);
      lcd.print(backrestangle); 
      if (digitalRead(okbutton) == HIGH)
     {
        i=2;     
     }
     
      if (digitalRead(upbutton) == HIGH)
     {
      if (backrestangle < 45)
      {backrestangle = backrestangle + 1;}
     }
     
     if (digitalRead(downbutton) == HIGH)
     {
      if (backrestangle > 0)
      {backrestangle = backrestangle - 1;}
     }

     if (pbrangle < backrestangle)
     {
      while (pbrangle < backrestangle)   //loop to increase angle
      {
        pval = analogRead(potpin);
        pbrangle = map(pval, 0, 1024, 45, 0);
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, LOW);
      }
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, HIGH);
     }

      else if (pbrangle > backrestangle)
     {
       while (pbrangle > backrestangle) // loop to decrease angle
      {
        pval = analogRead(potpin);
        pbrangle = map(pval, 0, 1024, 45, 0);
        digitalWrite(relaypin1, LOW);
        digitalWrite(relaypin2, HIGH);
      }
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, HIGH);
     }
      
   }  */




   

     lcd.clear(); 
     delay(2000);
     int j = 1; 
    while (j==1)
    {
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("SET NO OF HOURS:");
      lcd.setCursor(5,2);
      lcd.print(hourt); 
      if (digitalRead(okbutton) == HIGH)
      {
        j=2;    
      }
      if (digitalRead(upbutton) == HIGH)
      {
        hourt = hourt + 1;
        delay(250);
      }
      if (digitalRead(downbutton) == HIGH)
     {
      if (hourt > 0)
      {hourt = hourt - 1;delay(250);}
     }    
    } 

     lcd.clear(); 
     delay(2000);
     int k = 1; 
    while (k==1)
      {
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("SET NO OF MINUTES:");
      lcd.setCursor(5,2);
      lcd.print(mint); 
      if (digitalRead(okbutton) == HIGH)
      {
        k=2;    
      }
      if (digitalRead(upbutton) == HIGH)
      {
        mint = mint + 1;
        delay(250);
      }
      if (digitalRead(downbutton) == HIGH)
     {
      if (mint > 0)
      {mint = mint - 1;delay(250);}
     }    
    }
     lcd.clear(); 
     delay(500);
     DateTime now = rtc.now();
     DateTime future (now + TimeSpan(0,hourt,mint,0));
     int h = (future.hour());
     int m = (future.minute());Serial.print(h); Serial.print(",");Serial.print(m);
     int z = 1;
     while ( z == 1 )
     {
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("PRESENT TIME :");
      DateTime now = rtc.now();
      lcd.setCursor(0,1);
      lcd.print(now.hour(), DEC);  
      lcd.print(":");
      lcd.print(now.minute(), DEC);  
      //lcd.print(":");
     // lcd.print(now.second(), DEC);  
      if (now.hour() == h) {z=2;}
      lcd.setCursor(0,2);
      lcd.print("SUPINE POS TIME:");
      lcd.setCursor(0,3);
      lcd.print(h);  
      lcd.print(":");
      lcd.print(m);  
      
     }
     lcd.clear(); 
     int y = 1;
     while ( y == 1 )
     {
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("PRESENT TIME :");
      DateTime now = rtc.now();
      lcd.setCursor(0,1);
      lcd.print(now.hour(), DEC);  
      lcd.print(":");
      lcd.print(now.minute(), DEC);  
     // lcd.print(":");
     // lcd.print(now.second(), DEC);  
      if (now.minute() == m) {y=2;}
      lcd.setCursor(0,2);
      lcd.print("SUPINE POS TIME:");
      lcd.setCursor(0,3);
      lcd.print(h);  
      lcd.print(":");
      lcd.print(m);  
      
     }

     lcd.clear(); 
     delay(500);
     lcd.backlight();
     lcd.setCursor(0,0);
     lcd.print("RETURNING TO SUPINE");
     lcd.setCursor(0,2);
     lcd.print("POSITION");

     
    /* int pval = analogRead(potpin);
     int pbrangle = map(pval, 0, 1024, 45, 0);
      while (pbrangle > 0)
      {
        pval = analogRead(potpin);
        pbrangle = map(pval, 0, 1024, 45, 0);
        digitalWrite(relaypin1, LOW);
        digitalWrite(relaypin2, HIGH);
      }  */

        digitalWrite(relaypin1, LOW);
        digitalWrite(relaypin2, HIGH);
        delay(10000);
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, HIGH);
    
    modestatus = 1 ;
  }



  while (modestatus ==4)
  {
    int pval = analogRead(potpin);
    backrestangle = map(pval, 0, 1024, 45, 0);  
    lcd.clear();
    delay(2000);
    while (digitalRead(okbutton) == LOW)
    {
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("SET BACKREST ANGLE:");
      lcd.setCursor(5,2);
      lcd.print(backrestangle); 
      if (digitalRead(upbutton) == HIGH)
      {
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, LOW);
      }      
     else if (digitalRead(downbutton) == HIGH)
     {
        digitalWrite(relaypin1, LOW);
        digitalWrite(relaypin2, HIGH);
     }
      else
      {
        digitalWrite(relaypin1, HIGH);
        digitalWrite(relaypin2, HIGH);
      }
     pval = analogRead(potpin);
     backrestangle = map(pval, 0, 1024, 45, 0);    
        
    }

    lcd.clear();
    delay(2000);
    while (digitalRead(okbutton) == LOW)
    {
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("BLUETOOTH:");
      if (digitalRead(statepin) == HIGH)
      {lcd.print("CONNECTED");}
      else
      {lcd.print("NOT CNTD");}
      
      lcd.setCursor(6,1);
      lcd.print("RELAX");

      if(Serial.available() > 0)  // Checks whether data is comming from the serial port
      { 
             state = Serial.read(); // Reads the data from the serial port
      }
      
      if (state == '1') 
      {
          lcd.setCursor(0,3);
          lcd.print("RETURNING TO SUPINE");
          digitalWrite(relaypin1, LOW);
          digitalWrite(relaypin2, HIGH);
          delay(10000);
          digitalWrite(relaypin1, HIGH);
          digitalWrite(relaypin2, HIGH);
          lcd.clear();
          state = 0;
      }
     else if (state == '2') 
     {
          lcd.setCursor(0,3);
          lcd.print("RETURNING TO SUPINE");
          digitalWrite(relaypin1, LOW);
          digitalWrite(relaypin2, HIGH);
          delay(10000);
          digitalWrite(relaypin1, HIGH);
          digitalWrite(relaypin2, HIGH);
          lcd.setCursor(0,3);
          lcd.print("INFLATABLE ACTIVE");
          while (digitalRead(okbutton) == LOW)
          {
            digitalWrite(inflatepin, LOW);
            digitalWrite(pumppin, LOW);
            delay(10000);                   //CHANGE THIS DELAY TO THE NUMBER OF MILLI SECONDS IT TAKE TO INFLATE THE BLADDER, 
            digitalWrite(inflatepin, HIGH);
            digitalWrite(pumppin, HIGH);
            delay(60000);                  //THE NUMBER OF MILLI SECONDS THE BLADDER SHOULD STAY INFLATED , SET TO 1 MIN FOR NOW
            digitalWrite(deflatepin, LOW);
            digitalWrite(pumppin, LOW);
            delay(10000);                   //CHANGE THIS DELAY TO THE NUMBER OF MILLI SECONDS IT TAKE TO DEFLATE THE BLADDER, 
            digitalWrite(deflatepin, HIGH);
            digitalWrite(pumppin, HIGH);
            if (digitalRead(okbutton) == LOW){break;}
            delay(60000);                  //THE NUMBER OF MILLI SECONDS THE BLADDER SHOULD STAY DEFLATED , SET TO 1 MIN FOR NOW
          }
          
          
          lcd.clear();
          state = 0;
         
     } 
      
    }
     lcd.clear();
     modestatus = 1;
     delay(2000);
  
  }


}
