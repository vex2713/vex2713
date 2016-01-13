#pragma config(Motor,  port1,           bLeft,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           fRight,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           fLeft,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           sLeft,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           sRight,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Track,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          bRight,        tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//THIS IS A COMPLETELY USELESS LINE OF CODE THAT YOU SHOULD IGNORE BECAUSE IT SERVES ABSOLUTELY NO PURPOSE

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
	motor[fLeft] = 127;
	motor[fRight] = 127;
	motor[bLeft] = 127;
	motor[bRight] = 127;
	wait(1.5);
	motor[fLeft] = 0;
	motor[fRight] = 0;
	motor[bLeft] = 0;
	motor[bRight] = 0;
	motor[sLeft] = 127;
	motor[sRight] = 127;

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
	while (true)
	{
		motor[fLeft] = vexRT[Ch3];
		motor[fRight] = vexRT[Ch2];
		motor[bLeft] = vexRT[Ch3];
		motor[bRight] = vexRT[Ch2];

		if(vexRT[Btn5U]){//Spinning up shooter
			motor[sLeft] = 127;
			motor[sRight] = 127;
		}
		else {
			motor[sLeft] = 0;
			motor[sRight] = 0;
		}
		if(vexRT[Btn5D]) {//Running track
			motor[Track] = 127;
		}
		else {
			motor[Track] = 0;
		}
	}
}
