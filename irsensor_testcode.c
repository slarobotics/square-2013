#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, frontLeftDrive, tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, frontRightDrive, tmotorMatrix, openLoop, reversed)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-irseeker-v2.h"

string sTextLines[8];
// function prototype
void displayText(int nLineNumber, string *cChar, int nValueDC, int nValueAC);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	disableDiagnosticsDisplay();
  initializeRobot();

  waitForStart();   // wait for start of tele-op phase

 while (true)
  {
	    getJoystickSettings(joystick);  // Update Buttons and Joysticks
   servo[servo1] = joystick.joy1_y1;

  }
  // dc and ac directional values.
int _dirDC = 0;
int _dirAC = 0;
// DC and AC values from 5 internal detectors.
int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
int acS1, acS2, acS3, acS4, acS5 = 0;
// we are going to set DSP mode to 1200 Hz.
tHTIRS2DSPMode _mode = DSP_1200;
// attempt to set to DSP mode.
if (HTIRS2setDSPMode(HTIRS2, _mode) == 0)
{
// unsuccessful at setting the mode.
// display error message.
eraseDisplay();
nxtDisplayCenteredTextLine(0, "ERROR!");
nxtDisplayCenteredTextLine(2, "Init failed!");
nxtDisplayCenteredTextLine(3, "Connect sensor");
nxtDisplayCenteredTextLine(4, "to Port 1.");
// make a noise to get their attention.
PlaySound(soundBeepBeep);
// wait so user can read message, then leave main task.
wait10Msec(300);
return;
}
// initialize the array sTextLines.
for (int
i = 0; i < 8; ++i)
sTextLines[i] = "";
// display some header info at top of screen
eraseDisplay();
nxtDisplayTextLine(0, " DC AC");
nxtDisplayTextLine(1, "
-----------------
");
// loop continuously and read from the sensor.
while(true)
{
// Read the current non modulated signal direction
_dirDC = HTIRS2readDCDir(HTIRS2);
if (_dirDC < 0)
break;
// I2C read error occurred
// read the current modulated signal direction
_dirAC = HTIRS2readACDir(HTIRS2);
if (_dirAC < 0)
break;
// I2C read error occurred
// Read the individual signal strengths of the internal sensors
// Do this for both unmodulated (DC) and modulated signals (AC)
if (!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2,dcS3, dcS4, dcS5))
break;
// I2C read error occurred
if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
break;
// I2C read error occurred
displayText(2, "D", _dirDC, _dirAC);
displayText(3, "0", dcS1, acS1);
displayText(4, "1", dcS2, acS2);
displayText(5, "2", dcS3, acS3);
displayText(6, "3", dcS4, acS4);
displayText(7, "4", dcS5, acS5);
// wait a little before resuming.
wait10Msec(5);
}
}
// Minimize LCD screen flicker by only updating LCD when data has changed
void displayText(int nLineNumber, string *cChar, int nValueDC, int nValueAC)
{
string sTemp;
StringFormat(sTemp, "%4d %4d", nValueDC, nValueAC);
// Check if the new line is the same as the previous one
// Only update screen if it's different.
if (sTemp != sTextLines[nLineNumber])
{
string sTemp2;
sTextLines[nLineNumber] = sTemp;
StringFormat(sTemp2, "%s: %s", cChar, sTemp);
nxtDisplayTextLine(nLineNumber, sTemp2);
}
}