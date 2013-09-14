#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    Potentiometer,  sensorPotentiometer)
#pragma config(Sensor, I2C_1,  frontIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  backIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           thing1top,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           wristmotorr,   tmotorVex393, openLoop)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           armMotor2,     tmotorVex393, openLoop)
#pragma config(Motor,  port6,           wristmotorl,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           frontMotor,    tmotorVex269, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port8,           rightMotor,    tmotorVex269, openLoop, reversed, encoder, encoderPort, I2C_4, 1000)
#pragma config(Motor,  port9,           leftMotor,     tmotorVex269, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port10,          backMotor,     tmotorVex269, openLoop, reversed, encoder, encoderPort, I2C_3, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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

	bStopTasksBetweenModes = true;

	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[frontMotor] = 0;
	nMotorEncoder[backMotor] = 0;
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

	wait1Msec(1000);
	while((SensorValue(leftIEM) <= 1000 && SensorValue(rightIEM)<= 1000))
	{
		motor[rightMotor] = 100;
		motor[leftMotor] = -100;
	}
	wait1Msec(1000);
	SensorValue(leftIEM) = 0;
	SensorValue(rightIEM) = 0;
	while(SensorValue(Potentiometer) >= 35)
	{
		motor[leftMotor] = 127;
		motor[rightMotor] = 127;
	}
	wait1Msec(1000);
	motor[thing1top] = 100;
	wait1Msec(1000);
	while((SensorValue(leftIEM) <= 1000 && SensorValue(rightIEM)<= 1000))
	{
		motor[rightMotor] = -100;
		motor[leftMotor] = 100;
	}
	wait1Msec(1000);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;

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
		if(vexRT[Btn5U]==1)
		{
			motor[thing1top] = -127;
		}
		else if (vexRT[Btn5D] == 1)
		{
			motor[thing1top] = 127;
		}
		else
		{
			motor[thing1top] = 0;
		}
		if(
			motor[frontMotor] = vexRT[Ch1];
			motor[backMotor] = vexRT[Ch1];
			motor[leftMotor] = vexRT[Ch3];
			motor[rightMotor] = vexRT[Ch3];
			motor[armMotor] = vexRT[Ch3Xmtr2];
			motor[armMotor2] = vexRT[Ch3Xmtr2];
			motor[wristmotorl] = vexRT[Ch2Xmtr2];
			motor[wristmotorr] = vexRT[Ch2Xmtr2];
		}
	}

}
