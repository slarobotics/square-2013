#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*   HiTechnic Experimenter's Kit for the SuperPro

Experiment 5 - Ambient Canceling Light Sensor

This program reads the light level with a reference light source on and also off,
calculates the background light level to create an ambient (background) canceling light sensor.

*/

#include "drivers/hitechnic-superpro.h"

task main() {
  int wlight;
  int wolight;
  int lightdelta;

  // The data to be written: 0x3F = 111111 binary,
  // makes all digital ports outputs.
  HTSPBsetupIO(HTSPB, 0x3F);

  while(true) {
    // Switch off LED on port B0
    HTSPBwriteIO(HTSPB, 0x00);
    wait1Msec(30);
    wolight = HTSPBreadADC(HTSPB, 0, 10);

    // Switch on LED on port B0
    HTSPBwriteIO(HTSPB, 0x01);
    wait1Msec(30);
    wlight = HTSPBreadADC(HTSPB, 0, 10);

    // Calculate the difference
    lightdelta = wlight - wolight;

    eraseDisplay();
		nxtDisplayTextLine(1, "L_On : %4d", wlight);
		nxtDisplayTextLine(2, "L_Off: %4d", wolight);
		nxtDisplayTextLine(4, "L_Delta: %4d", lightdelta);
    wait1Msec(30);
  }
}
