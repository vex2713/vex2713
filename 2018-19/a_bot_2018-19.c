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
#define LIFT_PRESET_HEIGHT_LOW 10
#define LIFT_PRESET_HEIGHT_MID 248
#define LIFT_PRESET_HEIGHT_HIGH 444
#define LIFT_PRESET_HEIGHT_MAX 600

#define LIFT_PRESET_HEIGHT_LOW_FORK_DOWN 10
#define LIFT_PRESET_HEIGHT_LOW_FORK_UP 10

#define LIFT_PRESET_HEIGHT_MID_FORK_UP 248
#define LIFT_PRESET_HEIGHT_MID_FORK_DOWN 300

#define LIFT_PRESET_HEIGHT_HIGH_FORK_UP 444
#define LIFT_PRESET_HEIGHT_HIGH_FORK_DOWN 500

#define CLAW_PRESET_HEIGHT_LOW 10
#define CLAW_PRESET_HEIGHT_HIGH 1550
#define CLAW_MOTOR_POWER 60

enum preset{low, mid, high};
enum mode{manual, automatic};

//prototypes
void initLiftHeight();

//globals
bool teamSwitch;
enum preset liftPreset;
enum preset clawPreset;
int g_liftValue = 0;
int g_liftPower = 0;
bool upLiftPresetLock = false;
bool downLiftPresetLock = false;
bool upClawPresetLock = false;
bool downClawPresetLock = false;
enum mode clawMode = manual;
enum mode liftMode = manual;
int clawValue = 0;
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
 	//cap autonomus

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
 		sleep(900);
 		motor[liftPair1] = 0;
 		motor[liftPair2] = 0;

 		//foward
 		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(2000);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//turn right
		motor[rightTrack] = -60;
		motor[leftTrack] = 60;
		sleep(900);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//to cap
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(600);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//get cap
  	motor[claw] = 127;
  	sleep(2000);
  	motor[claw] = 0;

  	//turn to pole
  	motor[rightTrack] = -60;
		motor[leftTrack] = 60;
		sleep(900);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//up to pole
		motor[liftPair1] = -40;
  	motor[liftPair2] = -40;
  	sleep(1000);
		motor[liftPair1] = 0;
  	motor[liftPair2] = 0;

		//on top
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(1200);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//turn right
		motor[rightTrack] = -60;
		motor[leftTrack] = 60;
		sleep(900);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//foward
 		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(1000);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;


  /*	else{

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
 		sleep(900);
 		motor[liftPair1] = 0;
 		motor[liftPair2] = 0;

 		//foward
 		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(1500);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//turn right
		motor[rightTrack] = -60;
		motor[leftTrack] = 60;
		sleep(900);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//to cap
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(300);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//get cap
  	motor[claw] = 127;
  	sleep(1000);
  	motor[claw] = 0;
  	*/

	/* flag autonomus
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
		sleep(1500);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//turn right
		motor[rightTrack] = -60;
		motor[leftTrack] = 60;
		sleep(900);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;

		//to flag
		motor[rightTrack] = 60;
		motor[leftTrack] = 60;
		sleep(1000);
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
		sleep(1500);
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
		sleep(1000);
		motor[rightTrack] = 0;
		motor[leftTrack] = 0;
 */
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

		liftPower = 40;
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
			//SensorValue[liftHeight] = 0;
		}
	}
	sleep(250);
	SensorValue[liftHeight] = 0;

}

enum preset getPresetLiftValue(int sensor)
{
	enum preset preset;
/*
	#define LIFT_PRESET_HEIGHT_MAX  600
	#define LIFT_PRESET_HEIGHT_HIGH 444
	                                346
	#define LIFT_PRESET_HEIGHT_MID  248
	                                124
	#define LIFT_PRESET_HEIGHT_LOW  10
	*/
	if(sensor < (LIFT_PRESET_HEIGHT_MID/2))
	{
		//writeDebugStreamLine("reading low");
		preset = low;
	}
	else if(
					(sensor > (LIFT_PRESET_HEIGHT_MID-LIFT_PRESET_HEIGHT_LOW)/2)&&
					(sensor < ((LIFT_PRESET_HEIGHT_HIGH-LIFT_PRESET_HEIGHT_MID)/2)+LIFT_PRESET_HEIGHT_MID)
				 )
	{
		//writeDebugStreamLine("reading mid");
		preset = mid;
	}
	else if(sensor > ((LIFT_PRESET_HEIGHT_HIGH-LIFT_PRESET_HEIGHT_MID)/2)+LIFT_PRESET_HEIGHT_MID)
	{
		//writeDebugStreamLine("reading high");
		preset = high;
	}
	else
	{
		//writeDebugStreamLine("reading default");
		preset = low;
	}

	//writeDebugStreamLine("getPresetLiftValue- sensor:%d preset:%d", sensor, preset);
	return preset;
}

int getLiftValue(int btnFiveUp,int btnFiveDown,int btnSevenUp,int btnSevenDown)
{
	int diff;
	int targetHeightValue;
	int liftValue;

	if((btnFiveUp == 1)||(btnFiveDown == 1))
	{
		//writeDebugStreamLine("button 5");
		liftMode = manual;
		if(g_liftPower < 90)
		{
			g_liftPower = g_liftPower + 2;
		}
	}
	//writeDebugStreamLine("g_liftPower %d", g_liftPower);

	//lift
	if((btnFiveUp == 1)&&(liftMode == manual))
	{
		liftValue = g_liftPower * -1;
	}
	else if((btnFiveDown == 1)&&(liftMode == manual))
	{
		liftValue = g_liftPower;
	}
	else
	{
		liftValue = 0;
		g_liftPower = 0;
	}

	//Maintain lift preset values in manual lift mode
	if(liftMode == manual)
	{
		liftPreset = getPresetLiftValue(SensorValue[liftHeight]);
	}

	//##################################################################################
	//lift preset
	//writeDebugStreamLine("liftPreset %d", liftPreset);
	if(btnSevenUp == 0)
	{
		upLiftPresetLock = false;
	}
	if(btnSevenDown == 0)
	{
		downLiftPresetLock = false;
	}

	//lift mode
	if((btnSevenUp == 1)||(btnSevenDown == 1))
	{
		liftMode = automatic;
	}
	//low to mid
	if((btnSevenUp == 1)&&(liftPreset == low)&&(upLiftPresetLock == false))
	{
		liftPreset = mid;
		upLiftPresetLock = true;
	}
	//mid to high
	else if((btnSevenUp == 1)&&(liftPreset == mid)&&(upLiftPresetLock == false))
	{
		liftPreset = high;
		upLiftPresetLock = true;
	}
	//high to mid
	else if((btnSevenDown == 1)&&(liftPreset == high)&&(downLiftPresetLock == false))
	{
		liftPreset = mid;
		downLiftPresetLock = true;
	}
	//mid to low
	else if((btnSevenDown == 1)&&(liftPreset == mid)&&(downLiftPresetLock == false))
	{
		liftPreset = low;
		downLiftPresetLock = true;
	}

	//set lift motor values
	switch (liftPreset)
	{
		case low: 	targetHeightValue = LIFT_PRESET_HEIGHT_LOW;
               	break;
		case mid: 	targetHeightValue = LIFT_PRESET_HEIGHT_MID;
               	break;
		case high: 	targetHeightValue = LIFT_PRESET_HEIGHT_HIGH;
               	break;
		default:		targetHeightValue = LIFT_PRESET_HEIGHT_LOW;
               	break;
	}
	//compare sensor value with preset value
	diff = targetHeightValue - SensorValue[liftHeight];
	//writeDebugStreamLine("diff:%d target:%d sensor:%d presetv:%d liftMode:%d", diff,targetHeightValue,SensorValue[liftHeight],liftPreset,liftMode);
	//sleep(100);
	//if sensor show lift is lower by more than 50, go up fast
	if((diff > 50)&&(liftMode == automatic))
	{
		liftValue = -45;
	}
	//if sensor show lift is lower by less than 50, go up slow
	else if((diff < 50)&&(diff > 10)&&(liftMode == automatic))
	{
		liftValue = -25;
	}
	//if sensor show lift is high by more than 50, go down fast
	else if((diff < -50)&&(liftMode == automatic))
	{
		if(SensorValue[liftHeight] < LIFT_PRESET_HEIGHT_MID)
		{
			liftValue = 38;
		}
		else
		{
			liftValue = 30;
		}
	}
	//if sensor show lift is lower by less than 50, go down slow
	else if((diff > -50)&&(diff < -10)&&(liftMode == automatic))
	{
		if(SensorValue[liftHeight] < LIFT_PRESET_HEIGHT_MID)
		{
			liftValue = 26;
		}
		else
		{
			liftValue = 18;
		}
	}
	return liftValue;
}

int getClawValue(int btnSixUp,int btnSixDown,int btnEightUp,int btnEightDown)
{
	int diff;
	int targetValue;

	if((btnSixUp == 1)||(btnSixDown == 1))
	{
		//writeDebugStreamLine("claw in manual mode");
		clawMode = manual;
	}

	//claw manual mode
	//up
	if((btnSixUp == 1)&&(clawMode == manual)&&(SensorValue[forkLiftPot] < CLAW_PRESET_HEIGHT_HIGH))
	{
		clawValue = CLAW_MOTOR_POWER;
	}
	//down
	else if((btnSixDown == 1)&&(clawMode == manual)&&(SensorValue[forkLiftPot] > CLAW_PRESET_HEIGHT_LOW))
	{
		clawValue = CLAW_MOTOR_POWER * -1;
	}
	//stop
	else
	{
		clawValue = 0;
	}

	//##################################################################################
	//claw preset
	//writeDebugStreamLine("clawPreset %d", clawPreset);
	if(btnEightUp == 0)
	{
		upClawPresetLock = false;
	}
	if(btnEightDown == 0)
	{
		downClawPresetLock = false;
	}

	//mode
	if((btnEightUp == 1)||(btnEightDown == 1))
	{
		clawMode = automatic;
	}
	//low to high
	if((btnEightUp == 1)&&(clawPreset == low)&&(upClawPresetLock == false))
	{
		clawPreset = high;
		upClawPresetLock = true;
	}
	//high to low
	if((btnEightDown == 1)&&(clawPreset == high)&&(downClawPresetLock == false))
	{
		clawPreset = low;
		downClawPresetLock = true;
	}

	//set claw motor values
	switch (clawPreset)
	{
		case low: 	targetValue = CLAW_PRESET_HEIGHT_LOW;
		break;
		case high: 	targetValue = CLAW_PRESET_HEIGHT_HIGH;
		break;
		default:	targetValue = CLAW_PRESET_HEIGHT_LOW;
		break;
	}

	//compare sensor value with preset value
	diff = targetValue - SensorValue[forkLiftPot];

	//if diff is greater than 250 go up fast
	if((diff > 250)&&(clawMode == automatic))
	{
		clawValue = CLAW_MOTOR_POWER;
	}
	//if diff is between 50 and 250 go up slow
	if((diff < 250)&&(diff > 50)&&(clawMode == automatic))
	{
		clawValue = CLAW_MOTOR_POWER/2;
	}
	//down
	//if diff is less than -250 go down fast
	if((diff < -250)&&(clawMode == automatic))
	{
		clawValue = CLAW_MOTOR_POWER * -1;
	}
	//if diff is between -250 and -50 go down slow
	if((diff > -250)&&(diff < -50)&&(clawMode == automatic))
	{
		clawValue = CLAW_MOTOR_POWER/2 * -1;
	}

//	writeDebugStreamLine("diff:%d target:%d sensor:%d presetv:%d clawMode:%d clawValue:%d", diff,targetValue,SensorValue[forkLiftPot],clawPreset,clawMode,clawValue);
//	sleep(100);
	return clawValue;
}

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
	int clawDrive = 0;
	int count = 0;

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

			//lift progressive g_liftPower
			g_liftValue = getLiftValue(vexRT[Btn5UXmtr2],vexRT[Btn5DXmtr2],vexRT[Btn7UXmtr2],vexRT[Btn7DXmtr2]);
			//writeDebugStreamLine("liftValue %d", liftValue);
			//sleep(25);
			motor[liftPair1] = g_liftValue;
			motor[liftPair2] = g_liftValue;
			//##################################################################################

			//claw
			clawDrive = getClawValue(vexRT[Btn6UXmtr2],vexRT[Btn6DXmtr2],vexRT[Btn8UXmtr2],vexRT[Btn8DXmtr2]);
			//writeDebugStreamLine("clawDrive %d", clawDrive);
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

			//lift progressive g_liftPower
			g_liftValue = getLiftValue(vexRT[Btn5U],vexRT[Btn5D],vexRT[Btn7U],vexRT[Btn7D]);
			//writeDebugStreamLine("liftValue %d", liftValue);
			motor[liftPair1] = g_liftValue;
			motor[liftPair2] = g_liftValue;

			//claw
			clawDrive = getClawValue(vexRT[Btn6U],vexRT[Btn6D],vexRT[Btn8U],vexRT[Btn8D]);
			//writeDebugStreamLine("clawDrive %d", clawDrive);
			motor[claw] = clawDrive;
			//writeDebugStreamLine("clawDrive:[%d] g_liftValue:[%d]", clawDrive, g_liftValue);

		}
		sleep(10);
	}
}
