#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S2,     HTIRS2,         sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_Matrix_S1_1, motorA,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, motorB,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, motorC,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorD,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servoA,               tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_2, servoB,               tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_3, servoC,               tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_4, servoD,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c" //DO NOT TOUCH- These are the joystick drivers.
#include "/drivers/include/hitechnic-irseeker-v2.h" //IR sensor drivers- Don't touch this as well!

/*
* teleop.c
* -- This is a program to use teleop in the competition
*/

void setPowerAllMotors(int x){
// simultanously set power for all motors to the specified amount
	motor[motorA] = x;
	motor[motorB] = x;
	motor[motorC] = x;
	motor[motorD] = x;
}


void enterSafeMode(){

//STOP EVERYTHING NOTHING CAN MOVE
	setPowerAllMotors(0);
}

//teleop code: we want to check if teleop is successful
void initControl()
{
  int threshold = 10;             /* Int 'threshold' will allow us to ignore low
                                    readings that keep our robot in perpetual motion.
                                    We need to tinker with the variable */

  while(true)                            // Infinite loop:
  {
    getJoystickSettings(joystick); // get joystick readings
    if(abs(joystick.joy1_y1) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[motorA] = joystick.joy1_y1;
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[motorA] = 0;
    }


    if(abs(joystick.joy1_y2) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[motorB] = joystick.joy1_y2;
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[motorB] = 0;
    }

    //and the following is for the 2nd controller.

	if(joy1Btn(1) == 1){ // for flag raiser
		motor[motorC] = 100;
	} else {
		motor[motorC] = 0;
	}

	if(joy1Btn(7) == 1){ // for micah's pulley
		motor[motorD] = 100;
	} if(joy1Btn(8) == 1) {
		motor[motorD] = 0;
	}

	int servoPosition = ServoValue[servo1];
	if(joy1Btn(5) == 1){
		servo[servo1] = 160;
		wait1Msec(2000);
		servo[servo1] = 0;
	}

	if (joy1Btn(9) == 1 && joy1Btn(10) == 1){
		enterSafeMode();
	} else {
		//Umm.. I don't know what to put here.... I'll think of something
	}

  }
}

// This code may be VERY problematic. Be careful if using


task main()
{
initControl();
}
