#pragma config(Sensor, in1,    teamSelect,     sensorPotentiometer)
#pragma config(Sensor, dgtl10, yellowLED,      sensorLEDtoVCC)
#pragma config(Motor,  port1,           frontRight,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port6,           capFlip,       tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port7,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           midRearLeft,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           midRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rearRight,     tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(bool,  port8,						teamSwitch,
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)


//DL 01/30/19


#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!


void pre_auton()
{
}

task autonomous()
{
	if(SensorValue[teamSelect] < 2350)
  {
 	//turns left
			motor[frontRight] = -60;
			motor[midRight]   = -60;
			motor[rearRight]  = -60;
			motor[frontLeft] = -60;
			motor[midRearLeft] = -60;

			sleep(1000);

			motor[frontRight] = 60;
			motor[midRight]   = 60;
			motor[rearRight]  = 60;
			motor[frontLeft] = -60;
			motor[midRearLeft] = -60;

			sleep(1000);

			motor[frontRight] = -60;
			motor[midRight]   = -60;
			motor[rearRight]  = -60;
			motor[frontLeft] = -60;
			motor[midRearLeft] = -60;
			motor[capFlip] = -60;

			sleep(2700);

			motor[frontRight] = 0;
			motor[midRight]   = 0;
			motor[rearRight]  = 0;
			motor[frontLeft] = 0;
			motor[midRearLeft] = 0;
    }
    else if (SensorValue[teamSelect] > 2350)
  {
  	//turns right
			motor[frontRight] = -60;
			motor[midRight]   = -60;
			motor[rearRight]  = -60;
			motor[frontLeft] = -60;
			motor[midRearLeft] = -60;

			sleep(1000);

			motor[frontRight] = -60;
			motor[midRight]   = -60;
			motor[rearRight]  = -60;
			motor[frontLeft] = 60;
			motor[midRearLeft] = 60;

			sleep(1000);

			motor[frontRight] = -60;
			motor[midRight]   = -60;
			motor[rearRight]  = -60;
			motor[frontLeft] = -60;
			motor[midRearLeft] = -60;
			motor[capFlip] = -60;

			sleep(2700);

			motor[frontRight] = 0;
			motor[midRight]   = 0;
			motor[rearRight]  = 0;
			motor[frontLeft] = 0;
			motor[midRearLeft] = 0;
  }
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//																 User Can't roll Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task user_b_bot()
{

//button 7 up: conveyor
//button 7 dn: conveyor
//button 7 up: conveyor

//set controls in forward driving mode by default

int ControllerDirection;
ControllerDirection=1;

  while(1)
  {
  //Bnt8U and Bnt8U shd toggle controller direction.   You should NOT have to hold down button
    if(vexRT[Btn8U] == 1)
		{
			ControllerDirection=1;
		}
		if(vexRT[Btn8D] == 1)
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
			motor[midRearLeft] = ControllerDirection*vexRT[Ch3];
			//motor[rearLeft] = ControllerDirection*vexRT[Ch3];
			//end set motor speed based on controllers
		}

		if (ControllerDirection==-1)
		{
			//set motor speed based on controller direction but flip left and right
			motor[frontRight] = ControllerDirection*vexRT[Ch3];
			motor[midRight]   = ControllerDirection*vexRT[Ch3];
			motor[rearRight]  = ControllerDirection*vexRT[Ch3];

			motor[frontLeft] = ControllerDirection*vexRT[Ch2];
			motor[midRearLeft] = ControllerDirection*vexRT[Ch2];
			//motor[rearLeft] = ControllerDirection*vexRT[Ch2];
			//end set motor speed based on controllers
		}

		//check for cap  flipping controls
		//Xmtr2
		if((vexRT[Btn5U] == 1)||(vexRT[Btn5UXmtr2] == 1))
		{
			// start the cap flipping motor
			motor[capFlip] = 126;
		}
		if((vexRT[Btn5D] == 1)||(vexRT[Btn5DXmtr2] == 1))
		{
			// stop the cap flipping motor
			motor[capFlip] = 0;
		}
		if((vexRT[Btn6U] == 1)||(vexRT[Btn6UXmtr2] == 1))
		{
			// start the cap flipping motor in reverse
			motor[capFlip] = -126;
		}

		//check for cap flipping+converyor controls
		if((vexRT[Btn7U] == 1)||(vexRT[Btn7UXmtr2] == 1))
		{
			// start the cap flipping motor and conveyor
			motor[capFlip] = -126;
		}

		if((vexRT[Btn7D] == 1)||(vexRT[Btn7DXmtr2] == 1))
		{
			// stop the cap and conveyor motor
			motor[capFlip] = 0;
		}
		if((vexRT[Btn7L] == 1)||(vexRT[Btn7LXmtr2] == 1))
		{
			// start the cap flipping motor in reverse
			motor[capFlip] = 0;
		}
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