 
/********

leg2——leg1

leg4——leg3

leg6——leg5

**********/
//         211                         111
//            \                       /
//            210 — 200|===|100 — 101
//                      =====
//    411 — 401 — 400 |====| 300 — 301 — 311
//                      =====
//            610 — 600|===|500 — 501
//           /                       \
//        611                          511



#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BlueTooth(11, 10); // (TXD, RXD) of HC-06

char BT_input; // to store input character received via BT.

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

//personalized values for the set of replica MG995s I own  
#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
int pulse = 0;

//pwm.setPWM(i, 0, angleToPulse(angle) );
// Setup legs, three servos per leg
//Front Right
int Leg100 = 15; // Coax ~ Hip  
int Leg100_old_pos = 0;        
int Leg100_new_pos = 0; 
int Leg110 = 14; // Femur ~ Thigh
int Leg110_old_pos = 0;        
int Leg110_new_pos = 0; 
int Leg111 = 13; // Tibia
int Leg111_old_pos = 0;        
int Leg111_new_pos = 0; 

//Front Left
int Leg200 = 12; // Coax           
int Leg200_old_pos = 0;        
int Leg200_new_pos = 0; 
int Leg210 = 11; // Femur
int Leg210_old_pos = 0;        
int Leg210_new_pos = 0; 
int Leg211 = 10; // Tibia
int Leg211_old_pos = 0;        
int Leg211_new_pos = 0; 

//Mid Right
int Leg300 = 9; // Coax   
int Leg300_old_pos = 0;        
int Leg300_new_pos = 0; 
int Leg310 = 8; // Femur
int Leg310_old_pos = 0;        
int Leg310_new_pos = 0; 
int Leg311 = 7; // Tibia
int Leg311_old_pos = 0;        
int Leg311_new_pos = 0; 

//Mid Left
int Leg400 = 6; // Coax           
int Leg400_old_pos = 0;        
int Leg400_new_pos = 0; 
int Leg410 = 5; // Femur
int Leg410_old_pos = 0;        
int Leg410_new_pos = 0; 
int Leg411 = 4; // Tibia
int Leg411_old_pos = 0;        
int Leg411_new_pos = 0; 

//Back Right
int Leg500 = 3; // Coax   
int Leg500_old_pos = 0;        
int Leg500_new_pos = 0; 
int Leg510 = 2; // Femur
int Leg510_old_pos = 0;        
int Leg510_new_pos = 0; 
Servo Leg511; // Tibia          //Coz I am using a 16 channel PWM controller PCA9685 and the Tabia Servos 511 and 611 are connected to PWM pins on MEGA
int Leg511_old_pos = 0;        
int Leg511_new_pos = 0; 

//Back Left
int Leg600 = 1; // Coax           
int Leg600_old_pos = 0;        
int Leg600_new_pos = 0; 
int Leg610 = 0; // Femur        //Coz I am using a 16 channel PWM controller PCA9685 and the Tabia Servos 511 and 611 are connected to PWM pins on MEGA
int Leg610_old_pos = 0;        
int Leg610_new_pos = 0; 
Servo Leg611; // Tibia
int Leg611_old_pos = 0;        
int Leg611_new_pos = 0; 


int i,j,k,n,m,p,q,r;  // leg angle variables
char ActionIndicator;
int StandardPosition = 90;

void setup()
{
// Set all leg elements to initial positions
  BlueTooth.begin(9600);
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates also my digital servos can run at 60Hz too.

  //pwm1.begin();
  //pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency

  //pwm2.begin();
  //pwm2.setPWMFreq(1600);  // This is the maximum PWM frequency
    
  Serial.println("Setting up Legs");
  pwm.setPWM(Leg100, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg110, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg111, 0, angleToPulse(StandardPosition));
  delay(500);

  pwm.setPWM(Leg200, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg210, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg211, 0, angleToPulse(StandardPosition));
  delay(500); 
  
  pwm.setPWM(Leg300, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg310, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg311, 0, angleToPulse(StandardPosition));
  delay(500);

  pwm.setPWM(Leg400, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg410, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg411, 0, angleToPulse(StandardPosition));
  delay(500);

  pwm.setPWM(Leg500, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg510, 0, angleToPulse(StandardPosition));
  Leg511.attach(3);
  Leg511.write(StandardPosition);
  delay(500);
  
  pwm.setPWM(Leg600, 0, angleToPulse(StandardPosition));
  pwm.setPWM(Leg610, 0, angleToPulse(StandardPosition));
  Leg611.attach(2);
  Leg611.write(StandardPosition);
  delay(500);
  Serial.println("Setup Complete");
}

/*******************************************************/
void loop()
{
  if (BlueTooth.available())
 
  {
    BT_input=(BlueTooth.read());
    if (BT_input=='S')
    {
      // Testing walking function
      // start test routines
         setLegs();
         forward_movement();
         delay(2000);
    }
  }
}    
/*******************************************************/


// Movement functions
/*          
            pwm.setPWM(Leg100, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg110, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg111, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg200, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg210, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg211, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg300, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg310, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg311, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg400, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg410, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg411, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg500, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg510, 0, angleToPulse(StandardPosition));
            Leg511.write(StandardPosition);
            pwm.setPWM(Leg600, 0, angleToPulse(StandardPosition));
            pwm.setPWM(Leg610, 0, angleToPulse(StandardPosition));
            Leg611.write(StandardPosition);
  */

  
void forward_movement() 
{ 
  
  // Each forward walk request is repeated 10 times then
  // stops. After each movement the hexapod checks for any
  // obstacles in front of it, less than 10cm, if found it
  // stops performs a left, left turn to turn around for 
  // cancelling the remaining forward movements, if any.

  
  ActionIndicator = 'I';
  InitLeg1(ActionIndicator);
  delay(100);
  
  ActionIndicator = 'I';
  InitLeg2(ActionIndicator);
  delay(100);
  
  ActionIndicator = 'I';
  InitLeg5(ActionIndicator);
  delay(100);
  
  ActionIndicator = 'I';
  InitLeg6(ActionIndicator);
  delay(100);
  
  for (p = 1; p <= 10; p += 1) // Perform these actions 4 times.
  {
    // Legs 1,6, and 3 need to move together this achieves about 80mm
    // of forward motion. Legs 1 and 6 move forward 80mm however excert a
    // sidewards movement to the left, leg 3 pushes against this leftward 
    // force so ensuring the hexapod stays on a straight course.
        
        k = 90; // Leg1 Femur
        n = 90; // Leg1 Tibia
        r = 90; // Leg3 Coax
        j = 90; // Leg3 Femur
        m = 90; // Leg6 Femur
        q = 90; // Leg6 Tibia
        
        for (i = 0; i <= 20; i +=1 ) // Move up 30 degrees
        {
             pwm.setPWM(Leg110, 0, angleToPulse(k));
             pwm.setPWM(Leg111, 0, angleToPulse(n));
             pwm.setPWM(Leg300, 0, angleToPulse(r));
             pwm.setPWM(Leg310, 0, angleToPulse(j));
             pwm.setPWM(Leg610, 0, angleToPulse(m));
             Leg611.write(q);  
            
             k = k - 1;
             n = n - 2;
             r = r + 1;
             j = j + 1;
             m = m + 1;
             q = q - 1;
             delay(10);
        }
        // Bring Leg3 Tibia down to 80 degress
        j = 110; // Leg3 Femur    
        
        for (i = 0; i<=30; i += 1) 
        {
              pwm.setPWM(Leg310, 0, angleToPulse(j));
              j = j - 1;
              delay(5);
        }
        // Actual movement, pull with Leg1, push with Leg 3 and 6.  
        n = 50; // Leg1 Tibia
        r = 110; // Leg3 Coax
        q = 70; // Leg6 Tibia
        
        for (i = 0; i <=40; i += 1)
        {
              pwm.setPWM(Leg111, 0, angleToPulse(n));
              pwm.setPWM(Leg300, 0, angleToPulse(r));
              Leg611.write(q);
              r = r - 1;
              n = n + 1;
              q = q + 1;
              delay(10);  
        }
        // Return legs 1, 3 and 6 to standard position    
        k = 70; // Leg1 Femur
        r = 70; // Leg3 Coax
        j = 80; // Leg3 Femur
        m = 110; // Leg6 Femur    
        q = 110; // Leg6 Tibia
       
        for (i = 0; i <= 20; i +=1 ) // Move down 20 degrees
        {
             pwm.setPWM(Leg110, 0, angleToPulse(k));
             pwm.setPWM(Leg300, 0, angleToPulse(r));
             pwm.setPWM(Leg310, 0, angleToPulse(j));
             pwm.setPWM(Leg610, 0, angleToPulse(m));
             Leg611.write(q);
             
             k = k + 1;
             r = r + 1;
             
             if (i < 10) // stops Leg 3 Tibia going more than 10 degrees
             {
                  j = j + 1;      
             }
             m = m - 1; 
             q = q - 1;
             delay(10);     
        }    
     //  delay (2000);
     // Legs 2,5, and 4 need to move together this achieves about 80mm
    // of forward motion. Legs 2 and 5 move forward 80mm however excert a
    // sidewards movement to the left, leg 4 pushes against this leftward 
    // force so ensuring the hexapod stays on a straight course.
        k = 90; // Leg2 Femur
        n = 90; // Leg2 Tibia
        r = 90; // Leg4 Coax
        j = 90; // Leg4 Femur
        m = 90; // Leg5 Femur
        q = 90; // Leg5 Tibia
        
        for (i = 0; i <= 20; i +=1 ) // Move up 30 degrees
        {
             pwm.setPWM(Leg210, 0, angleToPulse(k));
             pwm.setPWM(Leg211, 0, angleToPulse(n));
             pwm.setPWM(Leg400, 0, angleToPulse(r));
             pwm.setPWM(Leg410, 0, angleToPulse(j));
             pwm.setPWM(Leg510, 0, angleToPulse(m));
             Leg511.write(q);
 
             k = k + 1;
             n = n + 2;
             r = r - 1;
             j = j - 1;
             
             if (i < 15 ) // Adjustment to Leg 5, 5 degrees less Tibia than Leg 6
             {
                   m = m - 1;              
             }

             q = q + 1;
             delay(10);
        }
        // Bring Leg4 Tibia down to 80 degress
        j = 70; // Leg4 Femur    
        
        for (i = 0; i<=30; i += 1) 
        {
              pwm.setPWM(Leg410, 0, angleToPulse(j));
              j = j + 1;
              delay(5);
        }
        // Actual movement, pull with Leg2, push with Leg 4 and 5.  
        n = 130; // Leg2 Tibia
        r = 70; // Leg4 Coax
        q = 110; // Leg5 Tibia
        for (i = 0; i <=40; i += 1)
        {
              pwm.setPWM(Leg211, 0, angleToPulse(n));
              pwm.setPWM(Leg400, 0, angleToPulse(r));
              Leg511.write(q);
              r = r + 1;
              n = n - 1;
              q = q - 1;
              delay(10);  
        }
        // Return legs 2, 4 and 5 to standard position    
        k = 110; // Leg2 Femur
        r = 110; // Leg4 Coax
        j = 100; // Leg4 Femur
        m = 75; // Leg5 Femur   //70 
        q = 70; // Leg5 Tibia
        for (i = 0; i <= 20; i +=1 ) // Move down 20 degrees
        {
             pwm.setPWM(Leg210, 0, angleToPulse(k));
             pwm.setPWM(Leg400, 0, angleToPulse(r));
             pwm.setPWM(Leg410, 0, angleToPulse(j));
             pwm.setPWM(Leg510, 0, angleToPulse(m));
             Leg511.write(q);
             
             k = k - 1;
             r = r - 1;
             if (i < 10)  // stops Leg 4 Tibia going more than 10 degrees
             {
                  j = j - 1;      
             }
             if (i < 15) // Adjustment to Leg 5, 5 degrees less Tibia than Leg 6
             {
             m = m + 1;              
             }
 
             q = q + 1;
             delay(10);     
        }    
  }
 delay(5000);
}
    
void reverse_movement()
{ // Each reverse walk request is repeated 10 times then stops.
  // Obstacle avoidance is not possible as head cannot turn 180 
  // degrees.
  ActionIndicator = 'I';
  InitLeg1(ActionIndicator);
  delay(100);
  ActionIndicator = 'I';
  InitLeg2(ActionIndicator);
  delay(100);
  ActionIndicator = 'I';
  InitLeg5(ActionIndicator);
  delay(100);
  ActionIndicator = 'I';
  InitLeg6(ActionIndicator);
  delay(100);
  for (p = 1; p <= 2; p += 1)
  {
    // Legs 1,6, and 3 need to move together
      MoveLeg6(Leg600_old_pos,Leg600_new_pos,'B');
      delay(100);
      MoveLeg1(Leg100_old_pos,Leg100_new_pos,'B');
      delay(100);
      MoveLeg3(Leg300_old_pos,Leg300_new_pos,'B');
      delay(100);      

   // Legs 2,5, and 4 need to move together
      MoveLeg5(Leg500_old_pos,Leg500_new_pos,'B'); 
      delay(100);  
      MoveLeg2(Leg200_old_pos,Leg200_new_pos,'B');
      delay(100);
      MoveLeg4(Leg400_old_pos,Leg400_new_pos,'B');   
      delay(100);      
  }         
}

void crab_left()        
{ // Each crab walk request consists of 10 steps then stopping.
  // The head is turned in the direction of movement so allowing
  // obstacle avoidance detection in that direction.
  for (i = 1; i <= 2; i += 1)
  {
  }  
}

void crab_right()     
{ // Each crab walk request consists of 10 steps then stopping.
  // The head is turned in the direction of movement so allowing
  // obstacle avoidance detection in that direction.
  for (i = 1; i <= 2; i += 1)
  {
  } 
}

// Movement routines
void MoveLeg1(int oldp, int newp, char action)
{
  switch (action) 
  {
  case 'F':  
    // Move Femur up 35, Tibia out 35
    j = 90;
    
    for (i = 90; i <= 125; i += 1){
      pwm.setPWM(Leg110, 0, angleToPulse(i));
      pwm.setPWM(Leg111, 0, angleToPulse(j));      
      j = j - 1;
      delay(10);
    }   
    // Move Femur down 50
    
    for (i = 125; i >= 75; i -=1){
      pwm.setPWM(Leg110, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia back 35
    
    for (i = 55; i <= 90; i +=1){
      pwm.setPWM(Leg111, 0, angleToPulse(j));
      delay
      (10);     
    }    
    // Move Femur up 15
    
    for (i = 75; i <= 90; i +=1){
      pwm.setPWM(Leg110, 0, angleToPulse(i));
      delay(10);     
    }     
  break;
  
  
  case 'B':
    j = 90;
    for (i = 90; i <= 115; i += 1){
      pwm.setPWM(Leg110, 0, angleToPulse(i));
      pwm.setPWM(Leg111, 0, angleToPulse(j));
      j = j + 1;
      delay(10);
    }   
    // Move Femur down 25
    for (i = 115; i >= 90; i -=1){
      pwm.setPWM(Leg110, 0, angleToPulse(i));
      delay(10);     
    }  
    // Move Tibia out 25
    for (i = 115; i >= 90; i -=1){
      pwm.setPWM(Leg111, 0, angleToPulse(j));
      delay(10);     
    } 
    break;
  }     
}

void MoveLeg2(int oldp, int newp, char action)
{
      // Move Femur up 35, Tibia out 35
  switch (action) {
  case 'F':    
    j = 90;
    for (i = 90; i >= 55; i -= 1){
      pwm.setPWM(Leg210, 0, angleToPulse(i));
      pwm.setPWM(Leg211, 0, angleToPulse(j));
      j = j + 1;
      delay(10);
    }   
    // Move Femur down 50
    for (i = 55; i <= 105; i +=1){
      pwm.setPWM(Leg210, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia back 35
    for (i = 125; i >= 90; i -=1){
      pwm.setPWM(Leg211, 0, angleToPulse(i));
      delay(10);     
    }    
    // Move Femur up 15
    for (i = 105; i >= 90; i -=1){
      pwm.setPWM(Leg210, 0, angleToPulse(i));
      delay(10);     
    } 
    break;
  case 'B':
      j = 90;
    for (i = 90; i >= 65; i -= 1){
      pwm.setPWM(Leg210, 0, angleToPulse(i));
      pwm.setPWM(Leg211, 0, angleToPulse(j));
      j = j - 1;
      delay(10);
    }   
    // Move Femur down 25
    for (i = 65; i <= 90; i +=1){
      pwm.setPWM(Leg210, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia out 35
    for (i = 65; i <= 90; i +=1){
      pwm.setPWM(Leg211, 0, angleToPulse(i));
      delay(10);     
    }  
    break;
  }   
}

void MoveLeg3(int oldp, int newp, char action)
{
 // Move Femur up 25, Tibia stays at 90, Coax moves forward 25
  j = 90;
  switch (action) {
  case 'F': 
    for (i = 90; i <= 115; i += 1){
      pwm.setPWM(Leg300, 0, angleToPulse(i));
      pwm.setPWM(Leg310, 0, angleToPulse(j));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j + 1;
      delay(10);
    } 
    break;
  case 'B':  
    for (i = 90; i >= 65; i -= 1){
      pwm.setPWM(Leg300, 0, angleToPulse(i));
      pwm.setPWM(Leg310, 0, angleToPulse(j));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j + 1;
      delay(10);
    }  
    break;
  }  
    // Move Femur down 25, Tibia out 25
    j = 115;
    for (i = 115; i >= 90; i -=1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j - 1;
      delay(10);     
    }
  switch (action){
  case 'F':      
    // Move Coax around 50
    for (i = 115; i >= 65; i -=1){
      pwm.setPWM(Leg300, 0, angleToPulse(i));
      pwm.setPWM(Leg311, 0, angleToPulse(StandardPosition));
      delay(10); 
    }   
    // Move Femur up 25, Tibia in 25
    j = 90;
    for (i = 90; i <= 115; i +=1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j + 1;
      delay(10);     
    }  
    // Move Coax around 25, Tibra down 25
    j = 115;
    for (i = 65; i <= 90; i +=1){
      pwm.setPWM(Leg300, 0, angleToPulse(i));
      pwm.setPWM(Leg310, 0, angleToPulse(j));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j - 1;
      delay(10);     
    }  
    break;
  case 'B':
    for (i = 65; i <= 115; i +=1){
      pwm.setPWM(Leg300, 0, angleToPulse(i));
      pwm.setPWM(Leg311, 0, angleToPulse(StandardPosition));
      delay(10); 
    }  
    // Move Femur up 25, Tibia in 25
    j = 90;
    for (i = 90; i <= 115; i +=1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j + 1;
      delay(10);     
    } 
    j = 115;
    for (i = 115; i >= 90; i -=1){
      pwm.setPWM(Leg300, 0, angleToPulse(i));
      pwm.setPWM(Leg310, 0, angleToPulse(j));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j - 1;
      delay(10);     
    } 
    break;
  }             
}

void MoveLeg4(int oldp, int newp, char action)
{
 // Move Femur up 25, Tibia stays at 90, Coax moves forward 25
  j = 90;
  switch (action) 
  {
        case 'F': 
          for (i = 90; i >= 65; i -= 1){
            pwm.setPWM(Leg400, 0, angleToPulse(i));
            pwm.setPWM(Leg410, 0, angleToPulse(j));
            pwm.setPWM(Leg411, 0, angleToPulse(j));
            j = j - 1;
            delay(10);
          }   
          break;
         case 'B': 
          for (i = 90; i <= 115; i += 1){
            pwm.setPWM(Leg400, 0, angleToPulse(i));
            pwm.setPWM(Leg410, 0, angleToPulse(j));
            pwm.setPWM(Leg411, 0, angleToPulse(j));
            j = j - 1;
            delay(10);
          } 
          break;
   } 
          // Move Femur down 25, Tibia out 25
          j = 65;
          for (i = 65; i <= 90; i +=1){
            pwm.setPWM(Leg410, 0, angleToPulse(i));
            pwm.setPWM(Leg411, 0, angleToPulse(j));
            j = j + 1;
            delay(10);     
          }            
  switch (action) 
  {
    case 'F':      
      // Move Coax around 50
      for (i = 65; i <= 115; i +=1){
        pwm.setPWM(Leg400, 0, angleToPulse(i));
        pwm.setPWM(Leg411, 0, angleToPulse(StandardPosition));
        delay(10); 
      }       
      // Move Femur up 25, Tibia in 25
      j = 90;
      for (i = 90; i >= 65; i -=1){
        pwm.setPWM(Leg410, 0, angleToPulse(i));
        pwm.setPWM(Leg411, 0, angleToPulse(j));
        j = j - 1;
        delay(10);     
      }  
      // Move Coax around 25, Tibra down 25
      j = 65;
      for (i = 115; i >= 90; i -=1){
        pwm.setPWM(Leg400, 0, angleToPulse(i));
        pwm.setPWM(Leg410, 0, angleToPulse(j));
        pwm.setPWM(Leg411, 0, angleToPulse(j));
        j = j + 1;
        delay(10);     
      } 
      break;
    case 'B':
       // Move Coax around 50
      for (i = 115; i >= 65; i -=1){
        pwm.setPWM(Leg400, 0, angleToPulse(i));
        pwm.setPWM(Leg411, 0, angleToPulse(StandardPosition));
        delay(10); 
      }   
      // Move Femur up 25, Tibia in 25
      j = 90;
      for (i = 90; i >= 65; i -=1){
        pwm.setPWM(Leg410, 0, angleToPulse(i));
        pwm.setPWM(Leg411, 0, angleToPulse(j));
        j = j - 1;
        delay(10);     
      }  
      // Move Coax around 25, Tibra down 25
      j = 65;
      for (i = 65; i <= 90; i +=1){
        pwm.setPWM(Leg400, 0, angleToPulse(i));
        pwm.setPWM(Leg410, 0, angleToPulse(j));
        pwm.setPWM(Leg411, 0, angleToPulse(j));
        j = j + 1;
        delay(10);     
      }  
      break;
    }         
}

void MoveLeg5(int oldp, int newp, char action)
{
    // Move Femur up 25, Tibia out 25
      switch (action) {
  case 'F': 
    j = 90;
    for (i = 90; i <= 115; i += 1){
      pwm.setPWM(Leg510, 0, angleToPulse(i));
      Leg511.write(j);
      j = j + 1;
      delay(10);
    }   
    // Move Femur down 25
    for (i = 115; i >= 90; i -=1){
      pwm.setPWM(Leg510, 0, angleToPulse(i));
      delay(10);     
    }  
    // Move Tibia out 25
    for (i = 115; i >= 90; i -=1){
      Leg511.write(1);
      delay(10);     
    } 
        break;
  case 'B':
      // Move Femur up 35, Tibia out 35
    j = 90;
    for (i = 90; i <= 125; i += 1){
      pwm.setPWM(Leg510, 0, angleToPulse(i));
      Leg511.write(j);
      j = j - 1;
      delay(10);
    }   
    // Move Femur down 50
    for (i = 125; i >= 75; i -=1){
      pwm.setPWM(Leg510, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia back 35
    for (i = 55; i <= 90; i +=1){
      Leg511.write(i);
      delay
      (10);     
    }    
    // Move Femur up 15
    for (i = 75; i <= 90; i +=1){
      pwm.setPWM(Leg510, 0, angleToPulse(i));
      delay(10);     
    }     
    break;
  }       
}

void MoveLeg6(int oldp, int newp, char action)
{
    // Move Femur up 25, Tibia in 25    
      switch (action) {
  case 'F': 
    j = 90;
    for (i = 90; i >= 65; i -= 1){
      pwm.setPWM(Leg610, 0, angleToPulse(i));
      Leg611.write(j);
      j = j - 1;
      delay(10);
    }   
    // Move Femur down 25
    for (i = 65; i <= 90; i +=1){
      pwm.setPWM(Leg610, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia out 35
    for (i = 65; i <= 90; i +=1){
      Leg611.write(i);
      delay(10);     
    }  
        break;
  case 'B':
      j = 90;
    for (i = 90; i >= 55; i -= 1){
      pwm.setPWM(Leg610, 0, angleToPulse(i));
      Leg611.write(j);
      j = j + 1;
      delay(10);
    }   
    // Move Femur down 50
    for (i = 55; i <= 105; i +=1){
      pwm.setPWM(Leg610, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia back 35
    for (i = 125; i >= 90; i -=1){
      Leg611.write(i);
      delay(10);     
    }    
    // Move Femur up 15
    for (i = 105; i >= 90; i -=1){
      pwm.setPWM(Leg610, 0, angleToPulse(i));
      delay(10);     
    } 
    break;
  }    
}

void CrabLegs1and2(char action)
{
  switch (action) {
    case 'L':
        MoveLeg2(Leg200_old_pos,Leg200_new_pos,'F');
        MoveLeg1(Leg100_old_pos,Leg100_new_pos,'B');
    break;
    case 'R':
        MoveLeg1(Leg100_old_pos,Leg100_new_pos,'F');
        MoveLeg2(Leg200_old_pos,Leg200_new_pos,'B');
    break;
  }
  delay(10);
}
// legs 3 and 4 need the walking actions from legs 1 and 2

void CrabLegs3and4(char action)
{
  switch (action) {
    case 'L':
        CrabLeg4(Leg400_old_pos,Leg400_new_pos,'F');
        CrabLeg3(Leg300_old_pos,Leg300_new_pos,'B');
    break;
    case 'R':
        CrabLeg3(Leg300_old_pos,Leg300_new_pos,'F');
        CrabLeg4(Leg400_old_pos,Leg400_new_pos,'B');
    break;
  }
  delay(10);
}

void CrabLegs5and6(char action)
{
  switch (action) {
    case 'L':
        MoveLeg6(Leg600_old_pos,Leg600_new_pos,'B');
        MoveLeg5(Leg500_old_pos,Leg500_new_pos,'F');
    break;
    case 'R':
        MoveLeg5(Leg500_old_pos,Leg500_new_pos,'B');
        MoveLeg6(Leg600_old_pos,Leg600_new_pos,'F');
    break;
  }
  delay(10);
}

void CrabLeg3(int oldp, int newp, char action)
{
  switch (action) {
  case 'F':  
    // Move Femur up 35, Tibia out 35
    j = 90;
    for (i = 90; i <= 125; i += 1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j - 1;
      delay(10);
    }   
    // Move Femur down 50
    for (i = 125; i >= 75; i -=1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia back 35
    for (i = 55; i <= 90; i +=1){
      pwm.setPWM(Leg311, 0, angleToPulse(i));
      delay
      (10);     
    }    
    // Move Femur up 15
    for (i = 75; i <= 90; i +=1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      delay(10);     
    }     
  break;
  case 'B':
    j = 90;
    for (i = 90; i <= 115; i += 1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      pwm.setPWM(Leg311, 0, angleToPulse(j));
      j = j + 1;
      delay(10);
    }   
    // Move Femur down 25
    for (i = 115; i >= 90; i -=1){
      pwm.setPWM(Leg310, 0, angleToPulse(i));
      delay(10);     
    }  
    // Move Tibia out 25
    for (i = 115; i >= 90; i -=1){
      pwm.setPWM(Leg311, 0, angleToPulse(i));
      delay(10);     
    } 
    break;
  }     
}

void CrabLeg4(int oldp, int newp, char action)
{
    switch (action) {
  case 'F':    
    j = 90;
    for (i = 90; i >= 55; i -= 1){
      pwm.setPWM(Leg410, 0, angleToPulse(i));
      pwm.setPWM(Leg411, 0, angleToPulse(j));
      j = j + 1;
      delay(10);
    }   
    // Move Femur down 50
    for (i = 55; i <= 105; i +=1){
      pwm.setPWM(Leg410, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia back 35
    for (i = 125; i >= 90; i -=1){
      pwm.setPWM(Leg411, 0, angleToPulse(i));
      delay(10);     
    }    
    // Move Femur up 15
    for (i = 105; i >= 90; i -=1){
      pwm.setPWM(Leg410, 0, angleToPulse(i));
      delay(10);     
    } 
    break;
  case 'B':
      j = 90;
    for (i = 90; i >= 65; i -= 1){
      pwm.setPWM(Leg410, 0, angleToPulse(i));
      pwm.setPWM(Leg411, 0, angleToPulse(i));
      j = j - 1;
      delay(10);
    }   
    // Move Femur down 25
    for (i = 65; i <= 90; i +=1){
      pwm.setPWM(Leg410, 0, angleToPulse(i));
      delay(10);     
    }
    // Move Tibia out 35
    for (i = 65; i <= 90; i +=1){
      pwm.setPWM(Leg411, 0, angleToPulse(i));
      delay(10);     
    }  
    break;
  }   
}


void InitLeg1(char action)
{
  switch (action) {
  case 'C':
          for (i = 90; i >= 45; i -= 1){
          pwm.setPWM(Leg100, 0, angleToPulse(i));
          delay(10);
        } 
       break;    
  case 'U':
        j = 90;
        for (i = 90; i <= 175; i += 1){
          pwm.setPWM(Leg110, 0, angleToPulse(i));
          pwm.setPWM(Leg111, 0, angleToPulse(j));
          j = j + 1;
          delay(10);
        }
        break;
   case 'D':
        j = 175;
        for (i = 175; i >= 90; i -= 1){
          pwm.setPWM(Leg110, 0, angleToPulse(i));
          pwm.setPWM(Leg111, 0, angleToPulse(j));
          j = j - 1;
          delay(10);        
        }
        break;
   case 'S':
        for (i = 90; i <= 105; i += 1){
        pwm.setPWM(Leg110, 0, angleToPulse(i));
        delay(10);
        }
        pwm.setPWM(Leg100, 0, angleToPulse(StandardPosition));
        for (i = 105; i >= 90; i -= 1){
        pwm.setPWM(Leg110, 0, angleToPulse(i));
          delay(10);
        }
        pwm.setPWM(Leg110, 0, angleToPulse(StandardPosition));
        pwm.setPWM(Leg111, 0, angleToPulse(StandardPosition));
        break;
   case 'I':
        for (j = 90; j <= 105; j += 1){
        pwm.setPWM(Leg110, 0, angleToPulse(j));
        delay(10);
        }
        for (i = 90; i <= 115; i += 1){
        pwm.setPWM(Leg100, 0, angleToPulse(i));
        delay(10);
        }
        for (k = 105; k >= 90; k -= 1){
        pwm.setPWM(Leg110, 0, angleToPulse(k));
        delay(10);
        }         
        break;     
  }   
}

void InitLeg2(char action)
{
    switch (action) {
    case 'C':
          for (i = 90; i <= 145; i += 1){
          pwm.setPWM(Leg200, 0, angleToPulse(i));
          delay(10);
        } 
       break;   
    case 'U':
        j = 90;
        for (i = 90; i >= 5; i -= 1){
          pwm.setPWM(Leg210, 0, angleToPulse(i));
          pwm.setPWM(Leg211, 0, angleToPulse(j));
          j = j - 1;
          delay(10);
        }
        break;  
    case 'D':
        j = 5;
        for (i = 5; i <= 90; i += 1){
          pwm.setPWM(Leg210, 0, angleToPulse(i));
          pwm.setPWM(Leg211, 0, angleToPulse(j));
          j = j + 1;
          delay(10);
        }      
        break;
   case 'S':
        for (i = 90; i >= 65; i -= 1){
          pwm.setPWM(Leg210, 0, angleToPulse(i));
          delay(10);
        }
          pwm.setPWM(Leg200, 0, angleToPulse(StandardPosition));
        for (i = 65; i <= 90; i += 1){
          pwm.setPWM(Leg210, 0, angleToPulse(i));
          delay(10);
        }
        pwm.setPWM(Leg210, 0, angleToPulse(StandardPosition));
        pwm.setPWM(Leg211, 0, angleToPulse(StandardPosition));
        break;  
   case 'I':
        for (j = 90; j >= 65; j -= 1){
        pwm.setPWM(Leg210, 0, angleToPulse(j));
        delay(10);
        }
        for (i = 90; i >= 65; i -= 1){
        pwm.setPWM(Leg200, 0, angleToPulse(i));
        delay(10);
        }
        for (k = 65; k <= 90; k += 1){
        pwm.setPWM(Leg210, 0, angleToPulse(k));
        delay(10);
        }    
        break;
    }
}

void InitLeg3(char action)
{
  switch (action) {
  case 'C':
          for (i = 90; i >= 45; i -= 1){
          pwm.setPWM(Leg300, 0, angleToPulse(i));
          delay(10);
        } 
       break; 
  case 'U':
        j = 90;
        for (i = 90; i <= 175; i += 1){
          pwm.setPWM(Leg310, 0, angleToPulse(i));
          pwm.setPWM(Leg311, 0, angleToPulse(j));
          j = j + 1;
          delay(10);
        }
        break;
   case 'D':
        j = 175;
        for (i = 175; i >= 90; i -= 1){
          pwm.setPWM(Leg310, 0, angleToPulse(i));
          pwm.setPWM(Leg311, 0, angleToPulse(j));
          j = j - 1;
          delay(10);        
        }
        break;
   case 'S':
        for (i = 90; i <= 105; i += 1){
        pwm.setPWM(Leg310, 0, angleToPulse(i));
        delay(10);
        }
        pwm.setPWM(Leg300, 0, angleToPulse(StandardPosition));
        for (i = 105; i >= 90; i -= 1){
        pwm.setPWM(Leg310, 0, angleToPulse(i));
        delay(10);
        }
        pwm.setPWM(Leg310, 0, angleToPulse(StandardPosition));
        pwm.setPWM(Leg311, 0, angleToPulse(StandardPosition));
        break;
   case 'I':
        for (j = 90; j <= 105; j += 1){
          pwm.setPWM(Leg110, 0, angleToPulse(j));
          delay(10);
        }
        for (i = 90; i <= 115; i += 1){
          pwm.setPWM(Leg300, 0, angleToPulse(i));
          delay(10);
        } 
        for (k = 105; k >= 90; k -= 1){
          pwm.setPWM(Leg310, 0, angleToPulse(k));
          delay(10);
        }         
        break;     
  }   
}

void InitLeg4(char action)
{
    switch (action) {
    case 'C':
          for (i = 90; i <= 145; i += 1){
          pwm.setPWM(Leg400, 0, angleToPulse(i));
          delay(10);
        } 
       break;     
    case 'U':
        j = 90;
        for (i = 90; i >= 5; i -= 1){
          pwm.setPWM(Leg410, 0, angleToPulse(i));
          pwm.setPWM(Leg411, 0, angleToPulse(j));
          j = j - 1;
          delay(10);
        }
        break;  
    case 'D':
        j = 5;
        for (i = 5; i <= 90; i += 1){
          pwm.setPWM(Leg410, 0, angleToPulse(i));
          pwm.setPWM(Leg411, 0, angleToPulse(j));
          j = j + 1;
          delay(10);
        }      
        break;
   case 'S':
        for (i = 90; i >= 65; i -= 1){
          pwm.setPWM(Leg410, 0, angleToPulse(i));
          delay(10);
        }
          pwm.setPWM(Leg400, 0, angleToPulse(StandardPosition));
        for (i = 65; i <= 90; i += 1){
          pwm.setPWM(Leg410, 0, angleToPulse(i));
          delay(10);
        }
          pwm.setPWM(Leg410, 0, angleToPulse(StandardPosition));
          pwm.setPWM(Leg411, 0, angleToPulse(StandardPosition));
        break;  
  case 'I':
        for (i = 90; i >= 65; i -= 1){
          pwm.setPWM(Leg400, 0, angleToPulse(i));
          delay(10);
        }
        break;          
    }
}
void InitLeg5(char action){
  switch (action) {
  case 'C':  
          for (i = 90; i <= 135; i += 1){
          pwm.setPWM(Leg500, 0, angleToPulse(i));
          delay(10);
        } 
       break;   
  case 'U':
        j = 90;
        for (i = 90; i <= 175; i += 1){
          pwm.setPWM(Leg510, 0, angleToPulse(i));
          Leg511.write(j);
          j = j + 1;
          delay(10);
        }
        break;
   case 'D':
        j = 175;
        for (i = 175; i >= 90; i -= 1){
          pwm.setPWM(Leg510, 0, angleToPulse(i));
          Leg511.write(j);
          j = j - 1;
          delay(10);        
        }
        break;
   case 'S':
        for (i = 90; i <= 105; i += 1){
          pwm.setPWM(Leg510, 0, angleToPulse(i));
          delay(10);
        }
          pwm.setPWM(Leg500, 0, angleToPulse(StandardPosition));
        for (i = 105; i >= 90; i -= 1){
          pwm.setPWM(Leg510, 0, angleToPulse(i));
          delay(10);
        }
        pwm.setPWM(Leg510, 0, angleToPulse(StandardPosition));
        Leg511.write(StandardPosition);
        break;
   case 'I':
        for (j = 90; j <= 105; j += 1){
          pwm.setPWM(Leg510, 0, angleToPulse(i));
          delay(10);
        }   
        for (i = 90; i >= 65; i -= 1){
          pwm.setPWM(Leg500, 0, angleToPulse(i));
          delay(10);
        } 
         for (k = 105; k >= 90; k -= 1){
          pwm.setPWM(Leg510, 0, angleToPulse(k));
          delay(10);
        }        
        break;     
  }   
}

void InitLeg6(char action)
{
    switch (action) {
    case 'C': 
          for (i = 90; i >= 45; i -= 1){
          pwm.setPWM(Leg600, 0, angleToPulse(i));
          delay(10);
        } 
       break;    
    case 'U':
        j = 90;
        for (i = 90; i >= 5; i -= 1){
          pwm.setPWM(Leg610, 0, angleToPulse(i));
          Leg611.write(j);
          j = j - 1;
          delay(10);
        }
        break;  
    case 'D':
        j = 5;
        for (i = 5; i <= 90; i += 1){
          pwm.setPWM(Leg610, 0, angleToPulse(i));
          Leg611.write(j);;
          j = j + 1;
          delay(10);
        }      
        break;
   case 'S':
        for (i = 90; i >= 65; i -= 1){
          pwm.setPWM(Leg610, 0, angleToPulse(i));
          delay(10);
        }
          pwm.setPWM(Leg600, 0, angleToPulse(StandardPosition));
        for (i = 65; i <= 90; i += 1){
          pwm.setPWM(Leg610, 0, angleToPulse(i));
          delay(10);
        }
        pwm.setPWM(Leg610, 0, angleToPulse(StandardPosition));
        Leg611.write(StandardPosition);
        break;
   case 'I':
        for (j = 90; j >= 65; j -= 1){
          pwm.setPWM(Leg610, 0, angleToPulse(j));
          delay(10);
        }
         for (i = 90; i <= 115; i += 1){
          pwm.setPWM(Leg600, 0, angleToPulse(i));
          delay(10);
        }
        for (k = 65; k <= 90; k += 1){
          pwm.setPWM(Leg610, 0, angleToPulse(k));
          delay(10);
        } 
        break;            
    }
}

void setLegs()
{
  ActionIndicator = 'S';
  InitLeg1(ActionIndicator);
  delay(10);
  ActionIndicator = 'S';
  InitLeg2(ActionIndicator);
  delay(10);
  ActionIndicator = 'S';
  InitLeg3(ActionIndicator);
  delay(10);
  ActionIndicator = 'S';
  InitLeg4(ActionIndicator);
  delay(10);
  ActionIndicator = 'S';
  InitLeg5(ActionIndicator);
  delay(10);
  ActionIndicator = 'S';
  InitLeg6(ActionIndicator);  
  delay(2000);
}


int angleToPulse(int ang)
{
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   //Serial.print("Angle: ");Serial.print(ang);
   //Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}
