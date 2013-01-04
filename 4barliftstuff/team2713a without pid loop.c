
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    Potentiometer,  sensorPotentiometer)
#pragma config(Sensor, I2C_1,  frontIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  backIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           thing1top,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           backMotor,     tmotorVex269, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armMotor2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           wristmotor,    tmotorVex393, openLoop)
#pragma config(Motor,  port7,           frontMotor,    tmotorVex269, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port8,           rightMotor,    tmotorVex269, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex269, openLoop, encoder, encoderPort, I2C_4, 1000)
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
	motor[wristmotor] = 100;
	wait1Msec(1000);
	while((SensorValue[I2C_1] <= 69)&&(SensorValue[I2C_3]<= 69))
	{
		motor[frontMotor] = 63;
		motor[backMotor]  = 63;
	}
	while((SensorValue[I2C_1] >= 69)&&(SensorValue[I2C_3] >= 69))
	{
		motor[frontMotor] = 0;
		motor[backMotor] = 0;
	}
	wait1Msec(500);
	while(SensorValue[Potentiometer] >= 72)
	{
		motor[armMotor] = 63;
		motor[armMotor2] = 63;
	}
	while(SensorValue[Potentiometer] <= 72)
	{
		motor[armMotor] = 0;
		motor[armMotor2] = 0;
	}
	wait1Msec(500);
	motor[wristmotor] = 100;

	wait1Msec(1000);
	motor[thing1top] = -100;

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

		if(vexRT[Btn7U] == 1)
		{
			motor[armMotor] = 100;
			motor[armMotor2] = 100;
		}
		else if(vexRT[Btn7D] == 1)
		{
			motor[armMotor] = -100;
			motor[armMotor2] = -100;
		}
		else if(vexRT[Btn5U]==1)
		{
			motor[thing1top] = 100;

		}
		else if (vexRT[Btn5D] == 1)
		{
			motor[thing1top] = -100;

		}
		else if (vexRT[Btn7U] == 1)
		{
		motor[wristmotor] = 100;
		}
		else if (vexRT[Btn7D] == 1)
		{
			motor[wristmotor] = -100;
		}
		else
		{
			motor[armMotor2] = 0;
			motor[armMotor] = 0;
			motor[thing1top] = 0;
			motor[wristmotor] = 0;
		}
		if( vexRT[Ch4] == 0)
		{
			int iCh1 = vexRT[Ch1];
			int iCh2 = vexRT[Ch2];
			if(vexRT[Ch1] > -15 && vexRT[Ch1] < 15)
			{

				iCh1 = 0;
			}

			bMotorReflected[port8] = false;
			bMotorReflected[port10] = true;
			bMotorReflected[port2] = false;
			bMotorReflected[port7] = true;
			motor[port8] = iCh1;							// Remove these as well and replace with your appropriate code
			motor[port10] = iCh1;              // Remove these as well and replace with your appropriate code

			motor[port2] = iCh2;
			motor[port7] = iCh2;
		}
		else
		{
			bMotorReflected[port8] = true;
			bMotorReflected[port10] = true;
			bMotorReflected[port2] = true;
			bMotorReflected[port7] = true;
			motor[port8] = vexRT[Ch4];							// Remove these as well and replace with your appropriate code
			motor[port10] = vexRT[Ch4];              // Remove these as well and replace with your appropriate code
			motor[port2] = vexRT[Ch4];
			motor[port7] = vexRT[Ch4];

		}
	}
}
