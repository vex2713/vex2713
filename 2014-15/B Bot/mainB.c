#pragma config(Sensor, dgtl1,  liftStop1,      sensorTouch)
#pragma config(Sensor, dgtl2,  liftStop2,      sensorTouch)
#pragma config(Motor,  port1,           backRight,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           lift1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           lift2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           lift3,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           lift4,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "functionsB.c"
/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

int BOT_ID = 2; //2 = B

void pre_auton()
{
	bStopTasksBetweenModes = true;
	string WHEEL_TYPE = "omni";
	nMotorEncoder[backRight]  =0;
	nMotorEncoder[backLeft]  =0;
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
	driveStraight(1, BOT_ID);
	driveStraight(1, BOT_ID);
	servoOpen(8);
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
	while (true){
		driveControl(2); //tank = 1 arcade = 2 RC = 3

		//analogArmControl(armLift, Ch2);//arm shoulder
		//digitalArmContol(armWrist, Btn5U, Btn5D, 100);//arm Wrist
		//digitalServoControl(claw, Btn6D, btn6U);
		//digitalServoControl(claw2, Btn8L, btn8D); //arm claw
	}
}
