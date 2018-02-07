#pragma config(Motor,  port2,           liftUpLeftDownRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftUpRightDownLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           deployClaw,    tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port6,           rightTrack,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftTrack,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

void pre_auton()
{
}

task autonomous()
{

}//end autonomous


/////////////////////////////////////////////////////////////////////////////////////////
//
//																 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task user_c_bot()
{
	while(1)
	{
    //lift
		motor[liftUpLeftDownRight] = vexRT[Ch2Xmtr2];
		motor[liftUpRightDownLeft] = vexRT[Ch2Xmtr2];

		//drive
		motor[rightTrack] = vexRT[Ch2];
		motor[leftTrack] = vexRT[Ch3];

		//claw
		motor[claw] = vexRT[Ch3Xmtr2];

		//Deploy claw
		if(vexRT[Btn7UXmtr2] == 1)
		{
			motor[deployClaw] = 127;
		}
		else if(vexRT[Btn7DXmtr2] == 1)
		{
			motor[deployClaw] = -127;
		}
		else
		{
			motor[deployClaw] = 0;
		}


		sleep(10);
	}
}



task usercontrol()
{
	// User control code here, inside the loop

	// This is the main execution loop for the user control program. Each time through the loop
	// your program should update motor + servo values based on feedback from the joysticks.

	// .....................................................................................
	// Insert user code here. This is where you use the joystick values to update your motors, etc.
	// .....................................................................................

	startTask(user_c_bot);
}
