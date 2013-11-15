void moveToBeacon(){
	int _dirAC = 0;
	 int acS1, acS2, acS3, acS4, acS5 = 0;

	 int maxSig = 0; // the max signal strength from the seeker.
	 int val = 0; // the translated directional value.


	 // we are going to set DSP mode to 1200 Hz.
	 //HTIRS2_DSP_MODE _mode = DSP_1200;

	 // attempt to set to DSP mode.
	 if (HTIRS2setDSPMode(HTIRS2, DSP_1200) == 0)
	 {
	 }

	 // loop continuously and read from the sensor.
	 while(true)
	 {
	 // read the current modulated signal direction
	 _dirAC = HTIRS2readACDir(HTIRS2);
	 if (_dirAC < 0)
	 {
	 break;
	 }

	 // Get the AC signal strength values.
	 if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
	 {
	 break;
	 } else {
	 // find the max signal strength of all detectors.
	 maxSig = (acS1 > acS2) ? acS1 : acS2;
	 maxSig = (maxSig > acS3) ? maxSig : acS3;
	 maxSig = (maxSig > acS4) ? maxSig : acS4;
	 maxSig = (maxSig > acS5) ? maxSig : acS5;
	 }

	 // figure out which direction to go...
	 // a value of zero means the signal is not found.
	 // 1 corresponds to the far left (approx. 8 o'clock position).
	 // 5 corresponds to straight ahead.
	 // 9 corresponds to far right.

	 // first translate directional index so 0 is straight ahead.
	 val = _dirAC - 5;

	 // calculate left and right motor speeds.
	 motor[motorA] = 50 + 30 * val;
	 motor[motorB] = 50 - 30 * val;

	 // wait a little before resuming.
	 wait10Msec(2);

	}
}

task main(){

	motor[motorD] = 100;
	wait1msec(2000);
	moveToBeacon();

}