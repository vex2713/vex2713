#pragma config(Sensor, in1,    P_wrist,        sensorPotentiometer)
#pragma config(Sensor, in2,    P_elbow,        sensorPotentiometer)
#pragma config(Motor,  port2,           BR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           FR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           S1,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           S2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           W,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           BL,            tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

	int wrist_goal;
	int elbow_goal;


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
	motor[FR] = 100;
	motor[FL]  = 100;
	motor[BL] = 100;
	motor[BR]  = 100;
	waitInMilliseconds(2000);
	motor[FR] = 0;
	motor[FL]  = 0;
	motor[BL] = 0;
	motor[BR]  = 0;


	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
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
	int wrist_up = 0;  // keep track of last action up?
	int elbow_up = 0;
	word wrist_position;

	while(1 == 1)
	{
		motor[FL] = vexRT[Ch3] / 1;
		motor[FR] = vexRT[Ch2] / 1;
		motor[BL] = vexRT[Ch3] / 1;
		motor[BR] = vexRT[Ch2] / 1;
		motor[S1] = vexRT[Btn5U] / Btn5D;
		motor[S2] = vexRT[Btn5U] / Btn5D;
		motor[W] = vexRT[Btn6U] / Btn6D;
		wrist_position = SensorValue[in1];  // wrist potentiometer

		if(vexRT[Btn5U] == 1)       	//If button 5U is pressed...
		{
			motor[S1] = 127;
			motor[S2] = 127;//...raise the arm.
			elbow_up = 1;
		}
		else if(vexRT[Btn5D] == 1)  	//Else, if button 5D is pressed...
		{
			motor[S1] = -127;
			motor[S2] = -127;  //... drop the arm
			elbow_up = 0;
		}
		else if(elbow_up == 1)  	//Else, if last action was up ... hold
		{
			motor[S1] = 64;
			motor[S2] = 64;  //... hold the arm ?? ( need to close the loop with a potentiometer! )
		}
		else                      		//Else (neither button is pressed)...
		{
			motor[S1] = 0;
			motor[S2] = 0; //...arm is down ... relax
		}
		if(vexRT[Btn6U])     // == 1)       	//If button 6U is pressed...
		{
			//motor[W] = 127;    	//...raise the hand.
			wrist_up = 1;
			if(wrist_goal < (1024-10))
				wrist_goal += 10;
		}
		else if(vexRT[Btn6D] == 1)  	//Else, if button 6D is pressed...

		{
			//motor[W] = -127;   // ... lower the hand
			wrist_up = 0;
			if(wrist_goal > 10)
				wrist_goal -= 10;
		}
		else if(wrist_up == 1)  	//Else, if last action was up, hold
		{
			motor[W] = 48;   // ... hold my hand ?? ( need to close the loop with a potentiometer! )

		}
		else                      		//Else (neither button is pressed)...
		{
			motor[W] = 0;    		//...wrist is down ... relax.
		}


		{
			if (wrist_position != wrist_goal)
				motor[W] = (wrist_position - wrist_goal);
			robotType(recbot);
			motor[port7] = 127;
			untilPotentiometerGreaterThan(wrist_goal, in1);
			motor[port7] = 0;
			wait(0.5);
			motor[port7] = -127;
			untilPotentiometerLessThan(wrist_goal, in1);
			motor[port7] = 0;
		}
	}
}