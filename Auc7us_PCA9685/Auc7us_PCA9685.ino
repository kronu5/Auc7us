//==============================================================================
//Project:    AUC7US
//Type:       Lynxmotion Phoenix Clone
//
//Version:    3.1
//Date:       09-04-2018
//Programmer: Jeroen Janssen    (Xan)       - Main code
//            Kurt Eckhardt     (KurtE)     - Converted to arduino
//            Lex van Teeffelen (Lexons)    - Converted to AliExpress Hexapod
//            Keshav Sharan     (Keshav-s7) - PCA9685 Compatibility
//This code should only be used on phoenix clones running the 
// PCA9685 16PWM channel module.
//==============================================================================

#define DEFINE_HEX_GLOBALS
#if ARDUINO>99
#include <Arduino.h>
#else
#endif
#include <EEPROM.h>
#include <PS2X_lib.h>
#include <SoftwareSerial.h>
#include "Hex_Cfg.h"
#include "Auc7us.h"
#include "Auc7us_Input_PS2.h"
#include "Auc7us_Driver_PCA9685.h"
#include "Auc7us_Code.h"
