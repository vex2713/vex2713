#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    teamSwitchPot,  sensorPotentiometer)
#pragma config(Sensor, in2,    gyro1,          sensorGyro)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           frontLeft,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rearLeft,      tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           midLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           conveyor,      tmotorNone, openLoop)
#pragma config(Motor,  port5,           leftFlyWheels, tmotorNone, openLoop)
#pragma config(Motor,  port6,           rightFlyWheels, tmotorNone, openLoop)
#pragma config(Motor,  port7,           capFlip,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           midRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rearRight,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port10,          frontRight,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(bool,  port8,						teamSwitch,
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)


//DL force sensor debugging

//#pragma DebuggerWindows("Sensors")
//#pragma DebuggerWindows("Globals")
//#pragma DebuggerWindows("Locals")



//DL 01/01/19


#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//teamSwitch = true;
int defaultMotorSpeed;
float gyroCorrection;
void pre_auton()
{
}
//beebot
//true is for blue, false is for red.
//between 708 and 4095


void stopMotor()
{
		motor[frontRight] = 0;
		motor[midRight] = 0;
		motor[rearRight] = 0;
		motor[frontLeft] = 0;
		motor[midLeft] = 0;
		motor[rearLeft] = 0;
	}


void turnLeftByTime(int power, int duration)
{

		motor[frontRight] = power;
		motor[midRight] = power;
		motor[rearRight] = power;
		motor[frontLeft] = -1*power;
		motor[midLeft] = -1*power;
		motor[rearLeft] = -1*power;



		sleep(duration);
}

void turnRightByTime(int power, int duration)
{
		motor[frontRight] = -1*power;
		motor[midRight] = -1*power;
		motor[rearRight] = -1*power;
		motor[frontLeft] = power;
		motor[midLeft] = power;
		motor[rearLeft] = power;
				sleep(duration);
}

void goForwardByTime(int power, int duration)
{

		motor[frontRight] = power;
		motor[midRight] = power;
		motor[rearRight] = power;
		motor[frontLeft] = power;
		motor[midLeft] = power;
		motor[rearLeft] = power;


		//sleep is in msec
		sleep(duration);

}

void goForwardDistance(int clicks)
{
	int power;
	power=defaultMotorSpeed;
			writeDebugStreamLine("starting goForwardDistance");
//	writeDebugStreamLine("enc left:%d",SensorValue[leftEncoder]);
//  writeDebugStreamLine("enc left:%d",clicks);


			SensorValue[leftEncoder]=0;



	while	(SensorValue[leftEncoder]<clicks)
	{
			//go forward for 1/10 second
		motor[frontRight] = power;
		motor[midRight] = power;
		motor[rearRight] = power;
		motor[frontLeft] = power;
		motor[midLeft] = power;
		motor[rearLeft] = power;
		sleep(100);

		}
			writeDebugStreamLine("ending goForwardDistance");
}

void goBackByTime(int power, int duration)
{

		motor[frontRight] = -1*power;
		motor[midRight] = -1*power;
		motor[rearRight] = -1*power;
		motor[frontLeft] = -1*power;
		motor[midLeft] = -1*power;
		motor[rearLeft] = -1*power;



		sleep(duration);
}

void goBackDistance(int clicks)
{
	int power;
	power=defaultMotorSpeed;
	writeDebugStreamLine("starting goBackDistance");
	SensorValue[leftEncoder]=0;
	while	(SensorValue[leftEncoder]>=-1*clicks)
	{
			//go back for 1/10 second
		motor[frontRight] = -1*power;
		motor[midRight] = -1*power;
		motor[rearRight] = -1*power;
		motor[frontLeft] = -1*power;
		motor[midLeft] = -1*power;
		motor[rearLeft] = -1*power;
		sleep(100);

		}
		writeDebugStreamLine("ending goBackDistance");

}


void fireRockets(int numberOfRockets)
{
}
void launchBall(int power, int duration)
{
}

void putControlsForwardMode()
{
motor[frontRight] = vexRT[Ch2];
motor[midRight]   = vexRT[Ch2];
motor[rearRight]  = vexRT[Ch2];

motor[frontLeft] = vexRT[Ch3];
motor[midLeft] = vexRT[Ch3];
motor[rearLeft] = vexRT[Ch3];
}

void putControlsBackwardMode()
{
motor[frontRight] = -vexRT[Ch2];
motor[midRight]   = -vexRT[Ch2];
motor[rearRight]  = -vexRT[Ch2];

motor[frontLeft] = -vexRT[Ch3];
motor[midLeft] = -vexRT[Ch3];
motor[rearLeft] = -vexRT[Ch3];
}


void turnLeftByDegrees(int targetDegrees)
{
	int power=60;
		power=defaultMotorSpeed;
	SensorValue[gyro1]=0;
	while (abs(SensorValue[gyro1])<(targetDegrees*10))
	{
					//go forward for 1/10 second
		motor[frontRight] = power;
		motor[midRight] = power;
		motor[rearRight] = power;
		motor[frontLeft] = -1*power;
		motor[midLeft] =  -1*power;
		motor[rearLeft] =  -1*power;
		sleep(100);
	}
}

void turnRightByDegrees(int targetDegrees)
{
	int power=60;
			power=defaultMotorSpeed;
		SensorValue[gyro1]=0;
	while (abs(SensorValue[gyro1])<(targetDegrees*10))
	{
					//go forward for 1/10 second
		motor[frontRight] = -1*power;
		motor[midRight] = -1*power;
		motor[rearRight] = -1*power;
		motor[frontLeft] = power;
		motor[midLeft] =  power;
		motor[rearLeft] =  power;
		sleep(100);
	}
}


task autonomous_A()
{
	//for compitition


//goal is to turn flip CAPS and land on platform
//STEPS
//start facing backwares
//turn on flipper
//drive backwars 4 ft
//hopefully will knock ball from 1st cap
//go forward 2 feet
//turn 90 degrees left
//go back 2 feet and hit the 2nd cap
//turn 180 degrees
//start heading for platform


//place on the spots near the flags
writeDebugStreamLine("starting autonomous_A");
//turnLeftByDegrees(270);




motor[capFlip] = -126;
goBackDistance(2050);
//this should have grabbed ball from 1st cap
stopMotor();
motor[capFlip] = 0;
turnLeftByDegrees(70);
stopMotor();
SensorValue[leftEncoder]=0;
//turnRight(60,880);
// ---  turnLeft(60,700);
motor[capFlip] = 126;
goBackDistance(1150);
stopMotor();
motor[capFlip] = 0;
//this shd have flipped 2nd cap


//now start heading for the platform
goForwardDistance(1150);
turnRightByDegrees(90);
goForwardDistance(2050);
turnLeftByDegrees(90);
//then go fwd short distance
motor[capFlip] = 126;
goForwardDistance(1300);
motor[capFlip] = 0;
//then turn left
turnRightByDegrees(90);
//then go fwd longer distance
goBackDistance(2050);
sleep(1000);
//shd now be on the platform




stopMotor();
}





task  autonomous_B()

//for simple testing
//place on the spots near the flags
{
	writeDebugStreamLine("starting autonomous_B");

SensorValue[leftEncoder]=0;


if	(SensorValue[leftEncoder]>-500)
	//go fwd for 1 second
{
	goForwardByTime(60,1000);
}
else
{
stopMotor();
SensorValue[leftEncoder]=0;
}
//turns left, goes back, and flips cap
//turnLeft(60,880);
//turnRight(60,700);
motor[capFlip] = 126;
goBackDistance(2000);
stopMotor();
motor[capFlip] = 0;
}


task autonomous()
{
defaultMotorSpeed=126;
gyroCorrection=1.1;
	//need to check for potentiomter then reverse commands if necessary
	if (SensorValue[teamSwitchPot] < 2047)
	{
		startTask(autonomous_A);
		//autonomous_A has is to flip caps then go to central pad
	}
	else
	{
		startTask(autonomous_B);
		//could use this for testing auto with ball launcher
	}

writeDebugStreamLine("enc left:%d",SensorValue[leftEncoder]);

}
 //end autonomous


/////////////////////////////////////////////////////////////////////////////////////////
//
//																 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task user_b_bot()
{
//set controls in forward driving mode by default
int ControllerDirection;
ControllerDirection=1;
//writeDebugStreamLine("enc left:%d",clicks);

	while(1)
	{
//		writeDebugStreamLine("pot value: %d", SensorValue[teamSwitchPot]);
		writeDebugStreamLine("enc left:%d",SensorValue[leftEncoder]);
		writeDebugStreamLine("gyro:%d",SensorValue[gyro1]);

		sleep(50);




//		Bnt8R and Bnt8L shd toggle controller direction.   You should NOT have to hold down button
		if(vexRT[Btn8R] == 1)
			{
				ControllerDirection=1;
			}

			if(vexRT[Btn8L] == 1)
			{
			   ControllerDirection=-1;
			}




if (ControllerDirection==1)
{
	//set motor speed based on controller direction

	motor[frontRight] = ControllerDirection*vexRT[Ch2];
	motor[midRight]   = ControllerDirection*vexRT[Ch2];
	motor[rearRight]  = ControllerDirection*vexRT[Ch2];

	motor[frontLeft] = ControllerDirection*vexRT[Ch3];
	motor[midLeft] = ControllerDirection*vexRT[Ch3];
	motor[rearLeft] = ControllerDirection*vexRT[Ch3];
//end set motor speed based on controllers

}


if (ControllerDirection==-1)
{
	//set motor speed based on controller direction but flip left and right

	motor[frontRight] = ControllerDirection*vexRT[Ch3];
	motor[midRight]   = ControllerDirection*vexRT[Ch3];
	motor[rearRight]  = ControllerDirection*vexRT[Ch3];

	motor[frontLeft] = ControllerDirection*vexRT[Ch2];
	motor[midLeft] = ControllerDirection*vexRT[Ch2];
	motor[rearLeft] = ControllerDirection*vexRT[Ch2];
//end set motor speed based on controllers

}

//check for cap  flipping controls
		if(vexRT[Btn5U] == 1)
		{
			// start the cap flipping motor
			motor[capFlip] = 126;
		}
		if(vexRT[Btn5D] == 1)
		{
			// stop the cap flipping motor
			motor[capFlip] = 0;
		}
		if(vexRT[Btn6U] == 1)
		{
		// start the cap flipping motor in reverse
			motor[capFlip] = -126;

		}
		if(vexRT[Btn6D] == 1)
		{
			// stop the cap flipping motor
			motor[capFlip] = 0;

		}


//check for cap+converyoe  flipping controls
		if(vexRT[Btn7U] == 1)
		{
			// start the cap flipping motor and conveyor
			motor[capFlip] = -126;
			motor[conveyor] = 126;
		}
		if(vexRT[Btn7D] == 1)
		{
			// stop the cap and conveyor motor
			motor[capFlip] = 0;
			motor[conveyor] = 0;
		}
		if(vexRT[Btn7L] == 1)
		{
		// start the cap flipping motor in reverse
			motor[capFlip] = 0;
			motor[conveyor] = -126;

		}



//check for flywheel constrol belt control.
//Need to assign a button.
// run leftFLyWheels in one direction
//  run rightFlyWheens in other direction
			if(vexRT[Btn7R] == 1)
			{
			motor[leftFlyWheels] = 126;
			motor[rightFlyWheels] = -126;
			}
				else
			{
			motor[leftFlyWheels] = 0;
			motor[rightFlyWheels] = 0;
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
	// Insert user code here. This is where you use the joystick values to update your motors, etc.                                                                                                                    h
	// .....................................................................................

	startTask(user_b_bot);
}
