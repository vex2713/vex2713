#pragma config(Motor,  port1,           wheelLeft,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           lockingMotor,  tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           pullingMotor,  tmotorVex393, openLoop)
#pragma config(Motor,  port10,          wheelRight,    tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

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
	writeDebugStreamLine("Autonomous started");
	motor[wheelLeft] = 127;
	motor[wheelRight]  = 127;
	wait1Msec(1000);
	motor[wheelLeft] = 0;
	motor[wheelRight]  = 0;
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
		//Wheels
		motor[wheelLeft]  = vexRT[Ch2]; //Left side of the robot is controlled by the left joystick, Y-axis
		motor[wheelRight] = vexRT[Ch3];


		//Pully
		if(vexRT[Btn8U] == 1)
		{
			motor[pullingMotor] = 127;
			writeDebugStreamLine("Winding");
		}
		else if(vexRT[Btn8D] == 1)
		{
			motor[pullingMotor] = -127;
			writeDebugStreamLine("Un-Winding");
		}
		else
		{
			motor[pullingMotor] = 0;
			writeDebugStreamLine("Stoping Winding");
		}

		//Locking
		if(vexRT[Btn7U] == 1)
		{
			motor[lockingMotor] = 145;
		}
		else if(vexRT[Btn7D] == 1)
		{
			motor[lockingMotor] = -127;
		}
	}
}
