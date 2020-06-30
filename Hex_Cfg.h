
#ifndef HEX_CFG_PHOENIX3_H
#define HEX_CFG_PHOENIX3_H

//#define OPT_TERMINAL_MONITOR
//#define OPT_FIND_SERVO_OFFSETS  //Only works with OPT_TERMINAL_MONITOR
#define OPT_GPPLAYER
#define OPT_SINGLELEG /////?????

#define DBGSerial Serial
//#define DEBUG_IOPINS

#if defined(UBRR1H)
#define SSCSerial Serial1
#else
#endif

#define USEPS2
#define USE_SSC32
//#define  cSSC_BINARYMODE 1
//#undef OPT_FIND_SERVO_OFFSETS
#define cSSC_BAUD 38400   //SSC32 BAUD rate

//==============================================================================
//[Arduino pin configuration] $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#define SOUND_PIN     5
#define PS2_DAT       6
#define PS2_CMD       7
#define PS2_SEL       8
#define PS2_CLK       9
#define cSSC_IN      10
#define cSSC_OUT     11

//==============================================================================
//[PCA9685 pin configuration] $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$...Use for PCA9685
#define cRFCoxaPin     15   //Front Right leg Hip Horizontal
#define cRFFemurPin    14   //Front Right leg Hip Vertical
#define cRFTibiaPin    13   //Front Right leg Knee
#define cRFTarsPin    999   //Tar (4DOF, not needed)

#define cLFCoxaPin     12   //Front Left leg Hip Horizontal
#define cLFFemurPin    11   //Front Left leg Hip Vertical
#define cLFTibiaPin    10   //Front Left leg Knee
#define cLFTarsPin    999   //Tar (4DOF, not needed)

#define cRMCoxaPin      9   //Middle Right leg Hip Horizontal
#define cRMFemurPin     8   //Middle Right leg Hip Vertical
#define cRMTibiaPin     7   //Middle Right leg Knee
#define cRMTarsPin    999   //Tar (4DOF, not needed)

#define cLMCoxaPin      6   //Middle Left leg Hip Horizontal
#define cLMFemurPin     5   //Middle Left leg Hip Vertical
#define cLMTibiaPin     4   //Middle Left leg Knee
#define cLMTarsPin    999   //Tar (4DOF, not needed)

#define cRRCoxaPin      3   //Rear Right leg Hip Horizontal
#define cRRFemurPin     2   //Rear Right leg Hip Vertical
#define cRRTibiaPin     3   //Rear Right leg Knee $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$...ARDUINO_pin
#define cRRTarsPin    999   //Tar (4DOF, not needed)

#define cLRCoxaPin      1   //Rear Left leg Hip Horizontal
#define cLRFemurPin     0   //Rear Left leg Hip Vertical
#define cLRTibiaPin     2   //Rear Left leg Knee  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$...ARDUINO_pin
#define cLRTarsPin    999   //Tar (4DOF, not needed)

//==============================================================================
//[Inverse Servo Direction]
#define cRRCoxaInv  0
#define cRMCoxaInv  0
#define cRFCoxaInv  0
#define cRRFemurInv 0
#define cRMFemurInv 0
#define cRFFemurInv 0
#define cRRTibiaInv 0
#define cRMTibiaInv 0
#define cRFTibiaInv 0

#define cLRCoxaInv  1
#define cLMCoxaInv  1
#define cLFCoxaInv  1
#define cLRFemurInv 1
#define cLMFemurInv 1
#define cLFFemurInv 1
#define cLRTibiaInv 1
#define cLMTibiaInv 1
#define cLFTibiaInv 1

//==============================================================================
//[Min/Max angles]                 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$...VERIFY ANGLES NEEDED
#define cRRCoxaMin1	   -260//	-26
#define cRRCoxaMax1		  740//	 74
#define cRRFemurMin1  -1010//	101
#define cRRFemurMax1	  950//	 95
#define cRRTibiaMin1  -1060//-106
#define cRRTibiaMax1	  770//	 77

#define cRMCoxaMin1    -530//	-53
#define cRMCoxaMax1		  530//	 53
#define cRMFemurMin1  -1010//  -101
#define cRMFemurMax1	  950//	 95
#define cRMTibiaMin1  -1060//  -106
#define cRMTibiaMax1    770//	 77

#define cRFCoxaMin1    -580//	-58
#define cRFCoxaMax1     740//  74
#define cRFFemurMin1  -1010// -101
#define cRFFemurMax1    950//	 95
#define cRFTibiaMin1  -1060// -106
#define cRFTibiaMax1    770//	 77

#define cLRCoxaMin1    -740//	-74
#define cLRCoxaMax1     260//	 26
#define cLRFemurMin1   -950//	-95
#define cLRFemurMax1   1010//	101
#define cLRTibiaMin1   -770//	-77
#define cLRTibiaMax1   1060//	106

#define cLMCoxaMin1    -530//	-53
#define cLMCoxaMax1     530//	 53
#define cLMFemurMin1   -950//	-95
#define cLMFemurMax1   1010//	101
#define cLMTibiaMin1   -770//	-77
#define cLMTibiaMax1   1060//	106

#define cLFCoxaMin1    -740//	-74
#define cLFCoxaMax1     580//	 58
#define cLFFemurMin1   -950//	-95
#define cLFFemurMax1   1010//	101
#define cLFTibiaMin1   -770//	-77
#define cLFTibiaMax1   1060//	106

//==============================================================================
//[Leg dimensions]
//Universal dimensions for each leg in mm
//Set up for the Chinese Phoenix Clones!
#define cXXCoxaLength     29	//Verified
#define cXXFemurLength    85	//Verified
#define cXXTibiaLength   125	//Verified
#define cXXTarsLength     85	// 4DOF only...

#define cRRCoxaLength     cXXCoxaLength
#define cRRFemurLength    cXXFemurLength
#define cRRTibiaLength    cXXTibiaLength
#define cRRTarsLength     cXXTarsLength

#define cRMCoxaLength     cXXCoxaLength
#define cRMFemurLength    cXXFemurLength
#define cRMTibiaLength    cXXTibiaLength
#define cRMTarsLength     cXXTarsLength

#define cRFCoxaLength     cXXCoxaLength
#define cRFFemurLength    cXXFemurLength
#define cRFTibiaLength    cXXTibiaLength
#define cRFTarsLength     cXXTarsLength

#define cLRCoxaLength     cXXCoxaLength
#define cLRFemurLength    cXXFemurLength
#define cLRTibiaLength    cXXTibiaLength
#define cLRTarsLength     cXXTarsLength

#define cLMCoxaLength     cXXCoxaLength
#define cLMFemurLength    cXXFemurLength
#define cLMTibiaLength    cXXTibiaLength
#define cLMTarsLength     cXXTarsLength

#define cLFCoxaLength     cXXCoxaLength
#define cLFFemurLength    cXXFemurLength
#define cLFTibiaLength    cXXTibiaLength
#define cLFTarsLength     cXXTarsLength

//==============================================================================
//[Body dimensions]

#define cRRCoxaAngle1    -600
#define cRMCoxaAngle1		    0
#define cRFCoxaAngle1     600
#define cLRCoxaAngle1    -600
#define cLMCoxaAngle1		    0
#define cLFCoxaAngle1     600

#define cRROffsetX        -43
#define cRROffsetZ         74
#define cRMOffsetX        -65
#define cRMOffsetZ          0
#define cRFOffsetX        -43
#define cRFOffsetZ        -74

#define cLROffsetX         43
#define cLROffsetZ         74
#define cLMOffsetX         65
#define cLMOffsetZ          0
#define cLFOffsetX         43
#define cLFOffsetZ        -74

//==============================================================================
//[Start positions legs]
#define cHexInitXZ        105
#define CHexInitXZCos60    53
#define CHexInitXZSin60    91
#define CHexInitY          25

#define cRRInitPosX      CHexInitXZCos60
#define cRRInitPosY      CHexInitY
#define cRRInitPosZ      CHexInitXZSin60

#define cRMInitPosX      cHexInitXZ
#define cRMInitPosY      CHexInitY
#define cRMInitPosZ      0

#define cRFInitPosX      CHexInitXZCos60
#define cRFInitPosY      CHexInitY
#define cRFInitPosZ      -CHexInitXZSin60

#define cLRInitPosX      CHexInitXZCos60
#define cLRInitPosY      CHexInitY
#define cLRInitPosZ      CHexInitXZSin60

#define cLMInitPosX      cHexInitXZ
#define cLMInitPosY      CHexInitY
#define cLMInitPosZ      0

#define cLFInitPosX      CHexInitXZCos60
#define cLFInitPosY      CHexInitY
#define cLFInitPosZ      -CHexInitXZSin60

//==============================================================================
#endif CFG_HEX_H
