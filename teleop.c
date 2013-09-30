/*
* teleop.c -- Logitech Dual Action Control
* Open an issue if anything needs to be added or changed
* ------------------------------------------------------------
* teleop.c utilizes "tank drive" -- Which means each joystick controls
* an individual motor.
* ------------------------------------------------------------
* ------------------------------------Config of Motors-----------------------------
*    [I/O Port]              [Name]              [Type]              [Description]
*    Port A									 motorA
*    Port B                  motorB              NXT                 Right motor
*    Port C                  motorC              NXT                 Left motor
* ---------------------------------------------------------------------------------
*/

#include "JoystickDriver.c"

int buttonValue; //not sure if I will need this yet, this is just in case

/* These will be the controls for raising the bulldozer and the claw.
We can handle up to 2 buttons pressed at a time. joy1Btn(buttonValue) & joy2btn(buttonValue)
Button Values on a logitech dual action go from 1-10, button's can return
either 0(off) or 1(on).
*/

void moveClaw(){
/* moveClaw will work for any claw-like implement we design
 dpad code    0
					  7   1
					6  -1   2
					  5   3
					    4 			*/
 int x = 0;
	if(joystick.joy1_TopHat == 0){ //if button is in an on state
		motor[motorA] = x + 5;
		x++;
	}
	if(joystick.joy1_TopHat == 4){
		motor[motorA] = x - 5;
		x--;
  }
}

void initControl()
{
  int threshold = 20;             /* Int 'threshold' will allow us to ignore low
                                    readings that keep our robot in perpetual motion.
                                    We need to tinker with the variable */

  while(true)                            // Infinite loop:
  {
    getJoystickSettings(joystick); // get joystick readings
    if(abs(joystick.joy1_y2) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[motorB] = joystick.joy1_y2;         // Motor B is assigned a power level equal to the right analog stick's Y-axis reading.
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[motorB] = 0;                        // Motor B is stopped with a power level of 0.
    }


    if(abs(joystick.joy1_y1) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[motorC] = joystick.joy1_y1;         // Motor C is assigned a power level equal to the left analog stick's Y-axis reading.
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[motorC] = 0;                        // Motor C is stopped with a power level of 0.
    }

		moveClaw();
  }
}


task main()
{
	initControl();
}
