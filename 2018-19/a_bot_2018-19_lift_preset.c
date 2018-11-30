#pragma config(Sensor, in1,    teamSwitchPot,  sensorPotentiometer)
#pragma config(Sensor, in2,    forkLiftPot,    sensorPotentiometer)
#pragma config(Sensor, dgtl11, liftHeight,     sensorQuadEncoder)
#pragma config(Motor,  port2,           liftPair1,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftPair2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           deployClaw,    tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port6,           rightTrack,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftTrack,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(bool,  port8,						teamSwitch,
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#define HOLD_POWER 30
#define LIFT_PRESET_HEIGHT_LOW 0
#define LIFT_PRESET_HEIGHT_MID 100
#define LIFT_PRESET_HEIGHT_HIGH 200
#define LIFT_PRESET_HEIGHT_MAX 600

enum preset{low, mid, high};
enum direction{up, down};

//prototypes
void initLiftHeight();

//globals
bool teamSwitch;

//teamSwitch = true;
void pre_auton()
{
}

//true is for blue, false is for red.
//between 708 and 4095

task autonomous()
{
	//lift1 range shd be 0 to 656
// lift shd be lowered prior to autonomous routine starting
//there will be a separate control for the fork lift
//SensorValue[liftHeight] = 0;
if(SensorValue[teamSwitchPot] > 2350)
{
 	teamSwitch = true;
}
	else
{
		teamSwitch = false;
}




//auto Blue
	if( teamSwitch == true){
 		//lift up body
		motor[liftPair1] = -40;
  	motor[liftPair2] = -40;
  	sleep(750);
		motor[liftPair1] = 0;
  	motor[liftPair2] = 0;

		//deploy claw
  	motor[claw] = -127;
  	sleep(3000);
  	motor[claw] = 0;

 		//lower body
 		motor[liftPair1] = 40;
 		motor[liftPair2] = 40;
 		sleep(750);
 		motor[liftPair1] = 0;
 		motor[liftPair2] = 0;

  	//move forward
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(2100);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//turn right
		motor[rightTrack] = -60;
		motor[leftTrack] = 60;
		sleep(1800);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//to flag
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(2800);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;
	}
	//auto Red
	//if( teamSwitch == false){
	else{
		//lift up
		motor[liftPair1] = -40;
	  motor[liftPair2] = -40;
	  sleep(750);
		motor[liftPair1] = 0;
	  motor[liftPair2] = 0;

		//deploy claw
	  motor[claw] = -127;
	  sleep(3000);
	  motor[claw] = 0;

	 	//lower
	 	motor[liftPair1] = 40;
	 	motor[liftPair2] = 40;
	 	sleep(700);
	 	motor[liftPair1] = 0;
	 	motor[liftPair2] = 0;

	  //move forward
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(2050);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//turn left
		motor[rightTrack] = 60;
		motor[leftTrack] = -60;
		sleep(900);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//to flag
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(2900);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

	}
}
 //end autonomous


/////////////////////////////////////////////////////////////////////////////////////////
//
// initLiftHeight
//
// Initializes the liftHeight sensor by moving down the lift and checking the value of
// the sensor until it doesn't change anymore
//
/////////////////////////////////////////////////////////////////////////////////////////
void initLiftHeight()
{
	writeDebugStreamLine("initLiftHeight");
	bool done = false;
	int current_position = 0;
	int previous_position = 0;
	int diff;
	int liftPower;
	while(!done)
	{
		previous_position = SensorValue[liftHeight];

		liftPower = 20;
		motor[liftPair1] = liftPower;
		motor[liftPair2] = liftPower;
		sleep(250);
		liftPower = 0;
		motor[liftPair1] = liftPower ;
		motor[liftPair2] = liftPower ;

		current_position = SensorValue[liftHeight];
		diff = abs(previous_position) - abs(current_position);
		writeDebugStreamLine("comparing: %d -- %d [%d]", previous_position,current_position,abs(diff));
		if(abs(diff) <= 1)
		{
			done = true;
			SensorValue[liftHeight] = 0;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
//
// initLiftHeight
//
// Initializes the liftHeight sensor by moving down the lift and checking the value of
// the sensor until it doesn't change anymore
//
/////////////////////////////////////////////////////////////////////////////////////////
void moveLiftToPreset(enum preset liftPreset,enum direction dir)
{
	writeDebugStreamLine("moveLiftToPreset");
	writeDebugStreamLine("height value: %d - %d", SensorValue[liftHeight], liftPreset);
	int heightValue;

	switch (liftPreset)
	{
		case low: 	heightValue = LIFT_PRESET_HEIGHT_LOW+5;
               	break;
		case mid: 	heightValue = LIFT_PRESET_HEIGHT_MID;
               	break;
		case high: 	heightValue = LIFT_PRESET_HEIGHT_HIGH;
               	break;
		default: 		heightValue = LIFT_PRESET_HEIGHT_LOW;
               	break;
	}

	if(dir == up)
	{
		while(SensorValue[liftHeight] < heightValue)
		{
			writeDebugStreamLine("height value: %d - %d", SensorValue[liftHeight], heightValue);
			motor[liftPair1] = -40;
			motor[liftPair2] = -40;
		}
	}
	else //down
	{
		while(SensorValue[liftHeight] > heightValue)
		{
			writeDebugStreamLine("height value: %d - %d", SensorValue[liftHeight], heightValue);
			motor[liftPair1] = 20;
			motor[liftPair2] = 20;
		}
	}}
/////////////////////////////////////////////////////////////////////////////////////////
//
//																 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
task usercontrol()
{
	bool partnerMode = true;
	int power = 0;
	int liftValue = 0;
	int clawDrive = 0;
	int count = 0;
	enum preset liftPreset;
	enum direction liftDirection;

	//init lift height
	initLiftHeight();
	//init lift preset value
	liftPreset = low;

	while(1)
	{
		//writeDebugStreamLine("pot value: %d", SensorValue[teamSwitchPot]);
		//writeDebugStreamLine("pot value: %d", SensorValue[forkLiftPot]);

		//select partner or user mode
		if((vexRT[Btn7R] == 1)&&(vexRT[Btn7L] == 1)&&(partnerMode == true))
		{
			count = count + 1;
			//writeDebugStreamLine("count %d", count);
			if(count > 200)
			{
				motor[claw] = 50;
				sleep(50);
				motor[claw] = 0;
				sleep(50);
				partnerMode = false;
				writeDebugStreamLine("solo %d", count);
				count = 0;
			}
		}
		else if ((vexRT[Btn7R] == 1)&&(vexRT[Btn7L] == 1)&&(partnerMode == false))
		{
			count = count + 1;
			//writeDebugStreamLine("count %d", count);
			if(count > 200)
			{
				motor[claw] = -50;
				sleep(50);
				motor[claw] = 50;
				sleep(50);
				motor[claw] = -50;
				sleep(50);
				motor[claw] = 50;
				sleep(50);
				motor[claw] = 0;
				sleep(50);
				partnerMode = true;
				writeDebugStreamLine("partner %d", count);
				count = 0;
			}
		}

		if(partnerMode)
		{
			//drive
			motor[rightTrack] = vexRT[Ch2];
			motor[leftTrack] = vexRT[Ch3];

			////////////////////////////////////////////////////

			//lift progressive power
			if((vexRT[Btn5UXmtr2] == 1)||(vexRT[Btn5DXmtr2] == 1))
			{
				if(power < 126)
				{
					power = power + 1;
				}
			}
			//writeDebugStreamLine("power %d", power);

			//lift
			if(vexRT[Btn5UXmtr2] == 1)
			{
				liftValue = power * -1;
			}
			else if(vexRT[Btn5DXmtr2] == 1)
			{
				liftValue = power;
			}
			else
			{
				liftValue = 0;
				power = 0;
			}

			//##################################################################################
			//lift preset
			//button toggle
			//LIFT_PRESET_HEIGHT_2
			//low to mid
			if((vexRT[Btn7UXmtr2] == 1)&&(liftPreset == low))
			{
				liftPreset = mid;
				liftDirection = up;
				writeDebugStreamLine("liftPreset %d", liftPreset);
				moveLiftToPreset(liftPreset,liftDirection);
			}
			//mid to high
			if((vexRT[Btn7UXmtr2] == 1)&&(liftPreset == mid))
			{
				liftPreset = high;
				liftDirection = up;
				writeDebugStreamLine("liftPreset %d", liftPreset);
				moveLiftToPreset(liftPreset,liftDirection);
			}
			//high to mid
			if((vexRT[Btn7DXmtr2] == 1)&&(liftPreset == high))
			{
				liftPreset = mid;
				liftDirection = down;
				writeDebugStreamLine("liftPreset %d", liftPreset);
				moveLiftToPreset(liftPreset,liftDirection);
			}
			//mid to low
			if((vexRT[Btn7DXmtr2] == 1)&&(liftPreset == mid))
			{
				liftPreset = low;
				liftDirection = down;
				writeDebugStreamLine("liftPreset %d", liftPreset);
				moveLiftToPreset(liftPreset,liftDirection);
			}


			//writeDebugStreamLine("liftValue %d", liftValue);
			motor[liftPair1] = liftValue;
			motor[liftPair2] = liftValue;

			//claw
			if ((vexRT[Btn6DXmtr2] == 1)&&(SensorValue[forkLiftPot] > 20))
			{
				clawDrive = -60;
			}
			else if ((vexRT[Btn6UXmtr2] == 1)&&(SensorValue[forkLiftPot] < 1500))
			{
		    clawDrive = 60;
			}
			else //all controls released
			{
				clawDrive = 0;
			}
			motor[claw] = clawDrive;
		}
		/////////////////////////////////////////////////////////////////////////////
		//Single user mode
		else
		{
			//drive
			motor[rightTrack] = vexRT[Ch2];
			motor[leftTrack] = vexRT[Ch3];

			////////////////////////////////////////////////////

			//lift progressive power
			if((vexRT[Btn5U] == 1)||(vexRT[Btn5D] == 1))
			{
				if(power < 126)
				{
					power = power + 1;
				}
			}
			//writeDebugStreamLine("power %d", power);

			//lift
			if(vexRT[Btn5U] == 1)
			{
				liftValue = power * -1;
			}
			else if(vexRT[Btn5D] == 1)
			{
				liftValue = power;

			}
			else
			{
				liftValue = 0;
				power = 0;
			}

			//writeDebugStreamLine("liftValue %d", liftValue);
			motor[liftPair1] = liftValue;
			motor[liftPair2] = liftValue;

			//claw
			if ((vexRT[Btn6D] == 1)&&(SensorValue[forkLiftPot] > 20))
			{
				clawDrive = -60;
			}
			else if ((vexRT[Btn6U] == 1)&&(SensorValue[forkLiftPot] < 1500))
			{
				clawDrive = 60;
			}
			else //all controls released
			{
				clawDrive = 0;
			}
			motor[claw] = clawDrive;

		}
		sleep(10);
	}
}
