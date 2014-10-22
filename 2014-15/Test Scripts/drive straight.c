#pragma config(Sensor, dgtl2,  encoder1,       sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  encoder2,       sensorQuadEncoder)
#pragma config(Motor,  port1,           motor1,        tmotorVex269, openLoop)
#pragma config(Motor,  port10,          motor2,        tmotorVex393, openLoop)
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
void driveStraight(float distance)
{
	SensorValue[encoder1]  =0;
	SensorValue[encoder2]  =0;
	float distanceTraveled = 0;

	while (distance >= distanceTraveled)
	{
		distanceTraveled = SensorValue[encoder1];
		if(SensorValue[encoder2]-SensorValue[encoder1]>30){
			motor[motor1] = 127;
			motor[motor2] = 10;
		}
		else if(SensorValue[encoder1]-SensorValue[encoder2]>30){
			motor[motor1] = 10;
			motor[motor2] = 127;
		}
		else{
			motor[motor1] = 110;
			motor[motor2] = 110;
		}
	}
	motor[motor1] = 0;
	motor[motor2] = 0;
}


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
	driveStraight(2000);
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
	driveStraight(2000);
}
