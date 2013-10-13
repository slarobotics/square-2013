#pragma config(Sensor, S1,     HTIRS2,              sensorI2CCustom)
       //
       // RoboSeek.c - This program uses the HiTechnic IR Seeker V2
       // sensor to follow an IR source.  This program requires the
       // HTIRS2-driver.h driver provided with RobotC.
       //
       // You can copy the "drivers" subdirectory and place it
       // in the same directory as this source file. if you do,
       // you can use the following #include statement to specify
       // the path to the driver.
       //#include "drivers/HTIRS2-driver.h"
       // if you use the "drivers/HTIRS2-driver.h" line,
       // then you should comment out the following line.
       #include "HTIRS2-driver.h"
       // main task
       task main ()
       {
         int _dirAC = 0;
             int acS1, acS2, acS3, acS4, acS5 = 0;
             int maxSig = 0;    // the max signal strength from the seeker.
             int val = 0;       // the translated directional value.
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
         eraseDisplay();
         // loop continuously and read from the sensor.
         while(true)
         {
           // read the current modulated signal direction
           _dirAC = HTIRS2readACDir(HTIRS2);
           if (_dirAC < 0){
      // error! - write to debug stream and then break.
      writeDebugStreamLine("Read dir ERROR!");
      break;
}
    // Get the AC signal strength values.
    if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
    {
      // error! - write to debug stream and then break.
      writeDebugStreamLine("Read sig ERROR!");
      break;
    }  else {
      // find the max signal strength of all detectors.
      maxSig = (acS1 > acS2) ? acS1 : acS2;
      maxSig = (maxSig > acS3) ? maxSig : acS3;
      maxSig = (maxSig > acS4) ? maxSig : acS4;
      maxSig = (maxSig > acS5) ? maxSig : acS5;
}
    // display info
    nxtDisplayCenteredBigTextLine(1, "Dir=%d", _dirAC);
    nxtDisplayCenteredBigTextLine(4, "Sig=%d", maxSig);
    // figure out which direction to go...
    // a value of zero means the signal is not found.
    // 1 corresponds to the far left (approx. 8 o'clock position).
    // 5 corresponds to straight ahead.
    // 9 corresponds to far right.
    // first translate directional index so 0 is straight ahead.
    val = _dirAC - 5;
    // calculate left and right motor speeds.
    motor[motorC] = 50 + 30 * val;
    motor[motorB] = 50 - 30 * val;
    // wait a little before resuming.
    wait10Msec(2);
  }
}
