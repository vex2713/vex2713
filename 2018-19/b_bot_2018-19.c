#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    teamSwitchPot,  sensorPotentiometer)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           frontLeft,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rearLeft,      tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           midLeft,       tmotorVex393_MC29, openLoop)
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



//DL 11/25/17


#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//teamSwitch = true;
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


void turnLeft (int power, int duration)
{
		motor[frontRight] = power;
		motor[midRight] = power;
		motor[rearRight] = power;
		motor[frontLeft] = -1*power;
		motor[midLeft] = -1*power;
		motor[rearLeft] = -1*power;



		sleep(duration);
}

void turnRight(int power, int duration)
{
		motor[frontRight] = -1*power;
		motor[midRight] = -1*power;
		motor[rearRight] = -1*power;
		motor[frontLeft] = power;
		motor[midLeft] = power;
		motor[rearLeft] = power;
				sleep(duration);
}

void goForward(int power, int duration)
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

void goBack(int power, int duration)
{

		motor[frontRight] = -1*power;
		motor[midRight] = -1*power;
		motor[rearRight] = -1*power;
		motor[frontLeft] = -1*power;
		motor[midLeft] = -1*power;
		motor[rearLeft] = -1*power;



		sleep(duration);
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

task autonomous_A()
{

//goal is to turn flip top
//STEPS
//turn on spinner in cap flippy way
//go forward 1 foot
// turn rt 90 deegree
//drive forward 1 foot

//place on the spots near the flags
writeDebugStreamLine("starting autonomous_A");

SensorValue[leftEncoder]=0;

while	(SensorValue[leftEncoder]<600)
{
	//go forward for 1/10 second
		goForward(60,100);

}
stopMotor();
SensorValue[leftEncoder]=0;
//turnRight(60,880);
turnLeft(60,700);
motor[capFlip] = 126;
goBack(60,2000);
stopMotor();
motor[capFlip] = 0;
}

//69,420


task  autonomous_B()
//place on the spots near the flags
{
	writeDebugStreamLine("starting autonomous_B");

SensorValue[leftEncoder]=0;


if	(SensorValue[leftEncoder]>-500)
	//go fwd for 1 second
{
	goForward(60,1000);
}
else
{
stopMotor();
SensorValue[leftEncoder]=0;
}
//turns left, goes back, and flips cap
//turnLeft(60,880);
turnRight(60,700);
motor[capFlip] = 126;
goBack(60,2000);
stopMotor();
motor[capFlip] = 0;
}


task autonomous()
{
	//need to check for potentiomter then reverse commands if necessary
	if (SensorValue[teamSwitchPot] < 2047)
	{
		startTask(autonomous_A)
	}
	else
	{
		startTask(autonomous_B)
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

	while(1)
	{
//		writeDebugStreamLine("pot value: %d", SensorValue[teamSwitchPot]);
		writeDebugStreamLine("enc left:%d",SensorValue[leftEncoder]);
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

//set motor speed based on controllers

//	motor[frontRight] = ControllerDirection*vexRT[Ch2];
//	motor[midRight]   = ControllerDirection*vexRT[Ch2];
//	motor[rearRight]  = ControllerDirection*vexRT[Ch2];

//	motor[frontLeft] = ControllerDirection*vexRT[Ch3];
//	motor[midLeft] = ControllerDirection*vexRT[Ch3];
//	motor[rearLeft] = ControllerDirection*vexRT[Ch3];
//end set motor speed based on controllers


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
