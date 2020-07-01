#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(11, 10); // (TXD, RXD) of HC-06

char BT_input; // to store input character received via BT.

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;
int pulse = 0;




void setup()  
{
   BlueTooth.begin(9600);
  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //yield();
}

void loop() 
{
  if (BlueTooth.available())
 
  {
    BT_input=(BlueTooth.read());
    if (BT_input=='U')
    {
      pulse = 575;
      pwm.setPWM(0, 0, pulse );
      //Serial.println(pulse);
      BlueTooth.println(pulse);
    }
    else if (BT_input=='L')
    {
      pulse = 150;
      pwm.setPWM(0, 0, pulse );
      //Serial.println(pulse);
      BlueTooth.println(pulse);
    }
    else if (BT_input=='i')
    {
      pulse = pulse+5;
      pwm.setPWM(0, 0, pulse );
      //Serial.println(pulse);
      BlueTooth.println(pulse);
    }
    else if (BT_input=='d')
    {
      pulse = pulse-5;
      pwm.setPWM(0, 0, pulse );
      //Serial.println(pulse);
      BlueTooth.println(pulse);
    }
    else if (BT_input=='s')
    {
      pulse = pulse-1;
      pwm.setPWM(0, 0, pulse );
      //Serial.println(pulse);
      BlueTooth.println(pulse);
    }
    else if (BT_input=='S')
    {
      pulse = pulse+1;
      pwm.setPWM(0, 0, pulse );
      //Serial.println(pulse);
      BlueTooth.println(pulse);
    }   
   // You may add other if else condition here. 
  }
}



/*
void loop() 
{


  for( int angle =0; angle<181; angle +=20){
    delay(500);
    pwm.setPWM(0, 0, angleToPulse(angle) );
  }

  delay(1000);
 
}

 * angleToPulse(int ang)
 * gets angle in degree and returns the pulse width
 * also prints the value on seial monitor
 * written by Ahmad Nejrabi for Robojax, Robojax.com
 */



/*
int angleToPulse(int ang)
{
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");//Serial.print(ang);
   Serial.print(" pulse: ");//Serial.println(pulse);
   return pulse;
}
*/
