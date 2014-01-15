#pragma config(Sensor, dgtl1,  autonomousSetting, sensorTouch)
#pragma config(Sensor, dgtl2,  autonomousContinue, sensorTouch)
#pragma config(Motor,  port1,           frontLeft,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           backLeft,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          backRight,     tmotorVex393, openLoop, reversed)
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
void forward(float time){
	motor[backLeft] = 127;
	motor[backRight] = 127;
	motor[frontLeft] = 127;
	motor[frontRight] = 127;
	wait1Msec(time * 1000);
	motor[backLeft] = 0;
	motor[backRight] = 0;
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
}

void back(float time){
	motor[backLeft] = -127;
	motor[backRight] = -127;
	motor[frontLeft] = -127;
	motor[frontRight] = -127;
	wait1Msec(time * 1000);
	motor[backLeft] = 0;
	motor[backRight] = 0;
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
}

void turnRight(float time){
	motor[backLeft] = 127;
	motor[backRight] = -127;
	motor[frontLeft] = 127;
	motor[frontRight] = -127;
	wait1Msec(time * 1000);
	motor[backLeft] = 0;
	motor[backRight] = 0;
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
}

void turnLeft(float time){
	motor[backLeft] = -127;
	motor[backRight] = 127;
	motor[frontLeft] = -127;
	motor[frontRight] = 127;
	wait1Msec(time * 1000);
	motor[backLeft] = 0;
	motor[backRight] = 0;
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
}

void waitforbutton(){
	while(SensorValue(autonomousContinue)==0){
	}
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
	//forward(2);
	turnRight(0.5);
	//forward(5);
	//wait1Msec(120);
	//back(5);
	//turnRight(2);
	//forward(1.5);
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
		motor[backLeft]  = vexRT[Ch3]; //Left side of the robot is controlled by the left joystick, Y-axis
		motor[backRight] = vexRT[Ch2];
		motor[frontLeft] = vexRT[Ch3];
		motor[frontRight] = vexRT[Ch2];


		//Pully

		//if(vexRT[Btn8U] == 1)
		//{
		//	motor[pullingMotor] = 127;
		//	writeDebugStreamLine("Winding");
		//}
		//else if(vexRT[Btn8D] == 1)
		//{
		//	motor[pullingMotor] = -127;
		//	writeDebugStreamLine("Un-Winding");
		//}
		//else
		//{
		//	motor[pullingMotor] = 0;
		//	writeDebugStreamLine("Stoping Winding");
		//}

		////Locking
		//if(vexRT[Btn7U] == 1)
		//{
		//	motor[lockingMotor] = 145;
		//}
		//else if(vexRT[Btn7D] == 1)
		//{
		//	motor[lockingMotor] = -127;
		//}
	}
}