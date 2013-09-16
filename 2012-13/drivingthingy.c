#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"
void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		if( vexRT[Ch4] == 0)

		int iCh1 = vexRT[Ch1];
		int iCh2 = vexRT[Ch2];
		if(vexRT[Ch1] > -15 && vexRT[Ch1] < 15)
		{

			iCh1 = 0;
		}

		bMotorReflected[port3] = false;
		bMotorReflected[port2] = true;
		bMotorReflected[port9] = false;
		bMotorReflected[port8] = true;
		motor[port3] = iCh1;							// Remove these as well and replace with your appropriate code
		motor[port2] = iCh1;              // Remove these as well and replace with your appropriate code

		motor[port9] = iCh2;
		motor[port8] = iCh2;
	}
	else
	{
		bMotorReflected[port3] = true;
		bMotorReflected[port2] = true;
		bMotorReflected[port9] = true;
		bMotorReflected[port8] = true;
		motor[port3] = vexRT[Ch4];							// Remove these as well and replace with your appropriate code
		motor[port2] = vexRT[Ch4];              // Remove these as well and replace with your appropriate code
		motor[port9] = vexRT[Ch4];
		motor[port8] = vexRT[Ch4];

	}




}
