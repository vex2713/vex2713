#pragma config(Sensor, in1,    ClawPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    LineDetect,     sensorLineFollower)
#pragma config(Sensor, dgtl1,  shldr_enc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  mode3,          sensorDigitalIn)
#pragma config(Sensor, dgtl8,  mode2,          sensorDigitalIn)
#pragma config(Sensor, dgtl9,  mode1,          sensorDigitalIn)
#pragma config(Sensor, dgtl10, LEDY,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, LEDG,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, LEDR,           sensorLEDtoVCC)
#pragma config(Motor,  port2,           BR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           FR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           BL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           S1,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           S2,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           C1,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           C2,            tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//potentiometer: small numbers closed lage numbers opened
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/* wrist encoder positions
*  assumes "Home" is 0 in the up position
*  Open or down for picking up is 102
*  Fully extended is 124 - for maximum height when the shoulder is up
*  Furthest down is 218 ( end of travel - furthest down
*   */

#define	CLAW_MODE_manual 0
#define	CLAW_MODE_pot 1
#define	CLAW_MODE_hold 2
#define CLAW_MODE_closing 3
#define CLAW_MODE_auto_open 4

/* Claw potentiometer wide open 3045 , closed 1876, open for stars 2600 (Feb 23 2017) */
#define CLAW_pot_open 3010
#define CLAW_pot_half_open 2600
#define CLAW_pot_closed 1900

short lineValue;  /* line detector */
//short lift_position;	/* potentiometer bottom 784 top 2485 Feb 17, 2017 */

short claw_mode =	 CLAW_MODE_manual;
short claw_position;	/* actual:	potentiometer reading wide 1400, closed 2780*/
short claw_goal;		/* latched actual:	potentiometer reading when 8R is pressed */
short claw_error;		/* difference between	 */
short claw_drive;

short mode_1, mode_2, mode_3;	 /* autonomous mode variables */

short gyroValue;
short gyroGoal = 0;

/* shoulder encoder positions
*  assumes "Home" is 0 in the down position
*  Up - top of travel is  130 - for maximum height when the shoulder is up
*  Limit switch - end of travel is 144
*   */
#define PARK_SHOULDER 0
#define DEPLOY_SHOULDER 50
#define MAX_SHOULDER 140
#define TOP_SHOULDER 110

#define GOAL_STEP_SIZE 1

/*   shoulder drive modes */
#define	SHOULDER_MODE_manual 0
#define SHOULDER_MODE_test 1


short drive_forward = 1;  // direction control +1 (forward) or -1 ( reverse )

short shoulder_position = 0;


short shoulder_mode = SHOULDER_MODE_manual;//SHOULDER_MODE_test; /* initialize in test mode - no encoder */
short shoulder_goal = 0;
short shoulder_error;
short shoulder_drive;

/*	white reflects high and gives low value.	grey reflects less and gives high value */
/* FIXME - confirm values */
#define LINE_white 400
#define LINE_grey	 1200
#define LINE_threshold ((LINE_white + LINE_grey)/2)

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

/* In the 'pre-automonous' mode, we need to make sure that
* the shovel is not deployed ( by the rubber bands )
* So use the encoder to control the wrist motor
*****  Assumes that the program begins with the shoulder
*   and wrist in the 'park' position to initialize both
*   encoders at 0
*/
task hold_wrist()
{
#if 0
	short wrist_drive;
	while ( true )
	{
		wrist_position = SensorValue[wrist_enc];  // wrist encoder

		if ( wrist_position > 4 )
		{
			/* a drive of 25 seems to hold the wrist up at park - CONFIRM!!! */
			wrist_drive = wrist_position * 6;
			motor[C1] = wrist_drive;
			motor[C2] = wrist_drive;
		}
		else
		{
			/* low power hold mode ... may oscillate */
			wrist_drive = wrist_position * 3;
			motor[C1] = wrist_drive;
			motor[C2] = wrist_drive;
		}

		waitInMilliseconds(20); // delay?

	}
#endif
}

void pre_auton()
{
	SensorValue[LEDG]=0; /* 0 is off, 1 is on */
	SensorValue[LEDR]=0;
	SensorValue[LEDY]=0;

	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[in4] = sensorNone;
	wait1Msec(1000);
	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in4] = sensorGyro;
	wait1Msec(2000);
	SensorValue[in4] = 0;	 // zero gyro
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.

	mode_1 = SensorValue[mode1];
	mode_2 = SensorValue[mode2];
	mode_3 = SensorValue[mode3];

	/* let the LED's confirm the autonomous armed or not ... red is OFF!!! */
	if (mode_3 == 0)
	{
		SensorValue[LEDR]=1;
	}
	else
	{
		SensorValue[LEDY]=1;
	}

	/* zero or initialize the shoulder encoder */
	SensorValue[shldr_enc] = 0;

	claw_position = SensorValue[ClawPot];  /* initial position ( near closed ) */
	claw_goal = claw_position + 120; /* open just a little */

	shoulder_position = SensorValue[shldr_enc];




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
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................
	/* let the mode_1, mode_2 set the autonomous program;
	*	 1,2
	*	 1,1 start on left, pick up cube and deliver
	*	 1,0 start on right, pick up cube and deliver
	*	 0,1 start on left, pick up stars and deliver
	*	 0,0 start on right, pick up stars and deliver
	*	 let mode_3 = 0 be used to not do autonomous
	*/

	int i;	/* loop counter */

	SensorValue[LEDG]=0; /* 0 is OFF, 1 is ON */
	SensorValue[LEDR]=0;
	SensorValue[LEDY]=0;

	/* mode_3 to bypass autonomous */
	if ( mode_3 == 0)
	{
		while(1)
	 {
			waitInMilliseconds(500);
			SensorValue[LEDR]=0;
			waitInMilliseconds(500);
			SensorValue[LEDR]=1;
		}
	}
	else /* green light means GO!!!! */
	{
		SensorValue[LEDG]=1;
	}

	/* first, deploy the claw! */
	resetTimer(T1);
	motor[C1] = -60;
	motor[C2] = -60;

	/* FIXME - add timeout or check if pot stops changing */
	while (SensorValue[ClawPot] < claw_goal)
	{
		waitInMilliseconds(5);
		if (getTimer(T1, seconds) > 5)
		{
			break;
		}
	}
	motor[C1] = 0;
	motor[C2] = 0;
	waitInMilliseconds(200); /* allow it to drop */

	/* now fully open */
		/* drop back down AND open claw for pickup at the same time !!!! */
	if ( mode_2 == 0) /* going for a cube ... open wide */
	{
		claw_goal = CLAW_pot_open; // 3010
	}
	else /* pick up some stars - can't open wide! */
	{
		claw_goal = CLAW_pot_half_open; //2600
	}


	resetTimer(T1);
	motor[C1] = -60;
	motor[C2] = -60;
	while (SensorValue[ClawPot] < claw_goal)
	{
		waitInMilliseconds(5);
		if (getTimer(T1, seconds) > 3)
		{
			break;
		}
	}
	motor[C1] = 0;
	motor[C2] = 0;


  /* approach the cube ( or other object ) */
	motor[FL] = 127;
	motor[FR] = 127;
	motor[BL] = 127;
	motor[BR] = 127;
	waitInMilliseconds (3000);
	/* step 3:  stop motor:   */
	motor[FL] = 0;
	motor[FR] = 0;
	motor[BL] = 0;
	motor[BR] = 0;

	/* close the claw - and hold - pot value is dropping as we close */
	resetTimer(T1);
	claw_position = SensorValue[ClawPot];
	motor[C1] = 40;
	motor[C2] = 40;
	waitInMilliseconds(100);
	while ( (SensorValue[ClawPot] <  claw_position) /* exits if it stops closing! */
		      && (getTimer(T1, seconds) < 3) )
	{
		claw_position = SensorValue[ClawPot];
		waitInMilliseconds(100);
	}
	/* drop to 'hold' torque */
	motor[C1] = 30;
	motor[C2] = 30;

	/* FIXME - if coming up empty, the claw will have fully closed ... open, move up, and try again! */

	/* Turn  to face the wall or away from it depending on stars or cubes */
	/* FIXME note, if on the wall getting stars, we may have to turn before deploying the outriggers
	 * but if getting cubes, we may have to lift before turning */


	 	/* now we need to turn towards or away from the wall - mode dependent! */
	if (mode_2 == 1)  /* cube quest, turning 120 degrees from wall and lifting */
	{
		gyroGoal = 1200; /* 120 degrees - face away from the wall*/
		shoulder_position = SensorValue[shldr_enc];
		waitInMilliseconds(100);
		while ( (SensorValue[shldr_enc] <  DEPLOY_SHOULDER)
					&& (SensorValue[shldr_enc] > shoulder_position) ) /* check for 'stall' */
		{
				shoulder_position = SensorValue[shldr_enc];
				waitInMilliseconds(100);
		}
	}
	else /* going to stars ... do not deploy yet! turn 90 degrees towards the Wall */
	{
		gyroGoal = 900; /* 90 degrees */
	}

	//	turn left ( counterclockwise gyro +)	 FIXME, what about starting on the left?	Jumper option or program?
	if (mode_1 != mode_2) /* cubes from right or stars from left, turn counter clockwise */
	{
		motor[FL] = -50;
		motor[BL] = -50;
		motor[FR] = 50;
		motor[BR] = 50;
	}
	else	/* cubes from right or starts from left, turn clockwise */
	{
		motor[FL] = 50;
		motor[BL] = 50;
		motor[FR] = -50;
		motor[BR] = -50;
	}

	/* turn either way until reaching goal - absolute value */
	resetTimer(T1);
	while(abs(gyroValue) < gyroGoal)
	{
		gyroValue = SensorValue[in4];
		wait1Msec(1);
		if (getTimer(T1, seconds) > 5)
		{
			break;
		}
	}
	/* apply brake */
	if (mode_1 != mode_2)
	{
		motor[FL] = 5;
		motor[BL] = 5;
		motor[FR] = -5;
		motor[BR] = -5;
	}
	else
	{
		motor[FL] = -5;
		motor[BL] = -5;
		motor[FR] = 5;
		motor[BR] = 5;
	}
	wait1Msec(50);

	/* if stars, move forward, then turn 180 degrees and deploy outrigger */

	/*  next - go all the way to the wall and then launch the payload and open claw at top */

	/* then .. call it quits!!! */


#if 0  /* FIXME  old autonomous - use this with 'mode_3'? */
	waitInMilliseconds (500);
	motor[S1] = 75;
	motor[S2] = 75;
	waitInMilliseconds (1000);
	motor[S1] = 0;
	motor[S2] = 0;
	waitInMilliseconds (1000);
	/* step 4:  back off ( shake off star? ) */
	/* all motors off  */
	/*  FIXME - we have an encoder now ... do something with the wrist and shoulder !!!! */
	motor[FL] = -127;
	motor[FR] = -127;
	motor[BL] = -127;
	motor[BR] = -127;
	waitInMilliseconds (1500);
#endif

	allMotorsOff();
}



/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


#define MAX_MOTOR 127
#define MIN_MOTOR -127



#define DRIVE_GAIN 0.75

task user_a_bot()
{
		short LED_toggle = 0;

	//	short shoulder_mode = SHOULDER_MODE_manual;//SHOULDER_MODE_test; /* initialize in test mode - no encoder */
	//	short shoulder_goal = 0;
	//	short shoulder_error;
	//	short shoulder_drive;
  // 	short shoulder_limit;
	// short limit_count = 0;
		SensorValue[LEDG]=1;  /* 0 is OFF, 1 is ON */
	  SensorValue[LEDR]=0;
	  SensorValue[LEDY]=0;

	while(1 == 1)
	{
			/* heartbeat ... it's alive!!!! */
			if (LED_toggle++ == 10)
		  {
					SensorValue[LEDG]=1;
		  }
		  else if (LED_toggle == 20)
		  {
					SensorValue[LEDG]=0;
					LED_toggle = 0;
		  }

		/**********************************************************************
		*****               holomonic wheels       ***************************
		*   are controlled here with the joy-sticks "tractor mode"
		*  Use buttons 7U ( forward ) and 7D ( backwards ) to reverse the drive
		*********************************************************************/
		if (drive_forward == 1)
		{
			motor[FL] = vexRT[Ch3] * DRIVE_GAIN; // / 1;
			motor[FR] = vexRT[Ch2] * DRIVE_GAIN; // / 1;
			motor[BL] = vexRT[Ch3] * DRIVE_GAIN; // / 1;
			motor[BR] = vexRT[Ch2] * DRIVE_GAIN; // / 1;
		}
		else if (drive_forward == -1)
		{
			motor[FL] = vexRT[Ch2] * -DRIVE_GAIN; // / 1;
			motor[FR] = vexRT[Ch3] * -DRIVE_GAIN; // / 1;
			motor[BL] = vexRT[Ch2] * -DRIVE_GAIN; // / 1;
			motor[BR] = vexRT[Ch3] * -DRIVE_GAIN; // / 1;


		}


		/*  ToDo:  add other drive modes depending on the driver preference */

		if (vexRT[Btn7U] == 1)
		{
			drive_forward = 1;
		}
		else if (vexRT[Btn7D] == 1)
		{
			drive_forward = -1;
		}

		//	motor[S1] = vexRT[Btn5U] / Btn5D;
		//	motor[S2] = vexRT[Btn5U] / Btn5D;
		//	motor[W] = vexRT[Btn6U] / Btn6D;

		/*   define potentiometer variables for position control here */
  	lineValue = SensorValue[LineDetect];
		shoulder_position = SensorValue[shldr_enc];  // shoulder encoder
		claw_position = SensorValue[ClawPot];	 // claw potentiometer goes 0 to 4095


		/*************************************************************************
		*****************        SHOULDER control         ***********************
		* Test Mode:   normal 'motor control' Btn5U/D controls motor drive up/down
		*        set with button 8L
		* Manual Mode:  position control:  Btn5U/D controls motor position up/down
		*        set with button 8U or 8D
		*************************************************************************/
		//		if ((vexRT[Btn8U] == 1) && (vexRT[Btn8D] == 1) && (vexRT[Btn8R] == 1) )
		//	  {
		//		 	SensorValue[wrist_enc] = 0;  // wrist encoder
		//	    SensorValue[shldr_enc] = 0;
		//  	}

		//		if((vexRT[Btn8U] == 1) || (vexRT[Btn8D] == 1))
		//		{
		shoulder_mode =  SHOULDER_MODE_manual;  /* position drive using encoder for 'hold' */
		//			shoulder_goal = shoulder_position;
		//		}
#if 0
		else if(vexRT[Btn8L] == 1)
		{
			shoulder_mode =  SHOULDER_MODE_test;   /* test motors - no encoder */
		}

		/*   now drive the wrist motor depending on the mode */
		if (shoulder_mode ==  SHOULDER_MODE_test)	/* drive motors directly up/down - for testing!!! */
		{
			SensorValue[LEDR]=0;
			if((vexRT[Btn5U]) && (shoulder_limit == 0))     //If button 6U is pressed... instruct the wrist UP higher
			{
				motor[S1] = 127 ;
				motor[S2] = 127 ;    //...raise the arm.
			}
			else if(vexRT[Btn5D] == 1)  	//Else, if button 6D is pressed... instruct the wrist DOWN lower
			{
				motor[S1] = -127 ;
				motor[S2] = -127 ;    // ... lower the arm
			}
			else
			{
				motor[S1] = 0 ;
				motor[S2] = 0 ;    // ... lower the arm
			}
		}  // END SHOULDER_MODE_test - drive motors directly
		else if (shoulder_mode ==  SHOULDER_MODE_manual)  /* control the shoulder by position ( encoder ) */
#endif
		if (shoulder_mode ==  SHOULDER_MODE_manual)  /* control the shoulder by position ( encoder ) */
		{
			SensorValue[LEDY]=1;
			/*  Step 1:  check to see if the goal needs to be updated */
			if(vexRT[Btn5U] == 1)     // == 1)       	//If button 5U is pressed... instruct the shoulder UP higher
			{
				if(shoulder_goal < (shoulder_position + GOAL_STEP_SIZE))
				{
					shoulder_goal = (shoulder_position + GOAL_STEP_SIZE);
					if (shoulder_goal > MAX_SHOULDER)
					{
						shoulder_goal = MAX_SHOULDER;
					}
				}
				else if(shoulder_goal < (MAX_SHOULDER-GOAL_STEP_SIZE))	/* limit check */
				{
					shoulder_goal += GOAL_STEP_SIZE;
				}
			}
			else if(vexRT[Btn5D] == 1)  	//Else, if button 5D is pressed... instruct the shoulder DOWN lower
			{
				if(shoulder_goal > (shoulder_position - GOAL_STEP_SIZE))
				{
					shoulder_goal = (shoulder_position - GOAL_STEP_SIZE);
					if (shoulder_goal < 0)
					{
						shoulder_goal = 0;
					}
				}
				else if(shoulder_goal > GOAL_STEP_SIZE)  /* limit check */
				{
					shoulder_goal -= GOAL_STEP_SIZE;
				}
			}

			/*  Step 2:  Apply the drive based on the goal and error */
			//completely flat=1982 when down
			//up all the way=3584
			//flat up all the way=0

			shoulder_error = shoulder_goal - shoulder_position ;
			shoulder_drive =  shoulder_error * 3;
			if (shoulder_drive > MAX_MOTOR )   /* limit check */
			{
				shoulder_drive = MAX_MOTOR;
			}
			else if (shoulder_drive < MIN_MOTOR ) /* limit check */
			{
				shoulder_drive = MIN_MOTOR;
			}

			/* limit switch  check! */
			//			if ((shoulder_limit == 1) && (shoulder_drive > 0))
			//			{
			//				shoulder_drive = 0;
			//			}
			/* drive the motor according to the error signal */
			motor[S1] = shoulder_drive ;
			motor[S2] = shoulder_drive ;
		}  // end SHOULDER_MODE_manual  ( position drive with encoder )
		//		else  // shoulder_mode undefined !!!!
		//		{
		//			motor[S1] = 0 ;
		//			motor[S2] = 0 ;
		//			shoulder_mode =  SHOULDER_MODE_test;
		// ToDo  set error mode
		//		}

		/* if we are somehow at the limit - reset the encoder */
		//		if (shoulder_limit == 1)
		//		{
		//			limit_count += 1;
		//			if (limit_count >= 10)
		//			{
		//				SensorValue[shldr_enc] = MAX_SHOULDER;
		//			}
		//		}
		//		else
		//		{
		//			limit_count = 0;
		//		}

		/*************************************************************************
		***************************      shoulder control    ************************
		*  Test Mode:   normal 'motor control' Btn6U/D controls motor drive up/down
		*        set with button 8R
		*  Manual Mode:  position control:  Btn6U/D controls motor position up/down
		*        set with button 8U
		*  Slave Mode:  position control: shoulder position controls wrist goal
		*        set with button 8D
		*************************************************************************/
#if 0
		if(vexRT[Btn8U] == 1)

		motor[BL] = vexRT[Ch2] * -DRIVE_GAIN; // / 1;
		motor[BR] = vexRT[Ch3] * -DRIVE_GAIN; // / 1;


		/* drive scissor lift - directly with button 5 U/D */
		if ((vexRT[Btn5U] == 1) && (SensorValue[shldr_enc] < 12345)) /* FIXME - change limit to encoder */
		{
			motor[S1] = 127;
			motor[S2] = 127;
			//			motor[L3] = 127;
		}
		else if (vexRT[Btn5D] == 1)
		{
			motor[S1] = -127;
			motor[S2] = -127;
			//			motor[L3] = -127;
		}
		else
		{
			motor[S1] = 0;
			motor[S2] = 0;
			//			motor[L3] = 0;
		}
#endif
		/***********************************************
		*****************			 claw			**************
		* Use button 6D/U to close/open the claw
		*
		* Use button 8R to put the claw into 'hold' mode
		*	 where it will use the potentiometer to maintain
		*	 the last position when 8R was pressed
		* Claw potentiometer wide open 1876, closed 3035 (Feb 17 2017)
		if ((claw_position > CLAW_pot_open)   // open 3010
#define CLAW_pot_closed 1900
		*********************************************/
		//		if (vexRT[Btn8R] == 1)	/* switch to 'pot' mode */
		//		{
		//			claw_mode =	 CLAW_MODE_pot;
		//			claw_position = SensorValue[ClawPot];
		//			claw_goal = claw_position;	/* actual:	potentiometer reading */
		//			writeDebugStreamLine("claw pot mode: %d", claw_goal);
		//		}
		if (vexRT[Btn8R] == 1)	/* switch to 'hold' mode hard */
		{
			claw_mode =	 CLAW_MODE_hold;
			claw_drive = 30;  /* ToDo - harder hold torque */
			writeDebugStreamLine("claw hold mode: %d", claw_goal);
		}
		else if (vexRT[Btn8L] == 1) /* switch to 'hold' mode soft */
		{
			claw_mode =	 CLAW_MODE_hold;
			claw_drive = 20;   /* ToDo - figure out a safe hold torque */
			writeDebugStreamLine("claw hold mode: %d", claw_goal);
		}
		else if (claw_mode == CLAW_MODE_auto_open)
		{
			if (claw_position < (CLAW_pot_open + 200 ))
			{
				claw_mode = CLAW_MODE_manual;
				claw_drive = 0;
			}
		}
		/* up high - auto open hard to drop  */
		else if (shoulder_position > TOP_SHOULDER )
		{
			claw_drive = -127;
			claw_mode =	 CLAW_MODE_auto_open;
		}

		/* manual mode, entered automatically with 6U or 6D */
		else if (vexRT[Btn6D] == 1)	 /* manual drive open 6D */
		{
			if (claw_position < CLAW_pot_open)   // open 3010 closed 1900
			{
				claw_drive = -60;
			}
			else
			{
				claw_drive = 0;
			}
			claw_mode =	 CLAW_MODE_manual;
		}
		//		else if (vexRT[Btn8D] == 1)	 /* manual drive closed 6D */
		else if (vexRT[Btn6U] == 1)	 /* manual drive closed 6U */
		{
			if (claw_position > CLAW_pot_closed)   // open 3010 closed 1900
			{
				claw_drive = 80;
				claw_mode =	 CLAW_MODE_closing;
			}
			else
			{
				claw_mode =	 CLAW_MODE_manual;
				claw_drive = 0;
			}
		}
		/* if last op is closing, apply hold torque */
		else if (claw_mode == CLAW_MODE_closing)
		{
			if (claw_position > CLAW_pot_closed)   // open 3010 closed 1900
			{
				claw_drive = 30;
			}
			else /* ... unless already closed */
			{
				claw_mode =	 CLAW_MODE_manual;
				claw_drive = 0;
			}
		}
		else if (claw_mode == CLAW_MODE_manual) /* let it rest! */
		{
			claw_drive = 0;
		}
		/*	if hold mode, then use the potentiometer to set the motor drive */
		else if (claw_mode ==	 CLAW_MODE_pot)
		{
			claw_error = (claw_position- claw_goal);
			claw_drive = claw_error / 4;
			if (claw_drive > MAX_MOTOR )	 /* limit check */
			{
				claw_drive = MAX_MOTOR;
			}
			else if (claw_drive < MIN_MOTOR )		/* limit check */
			{
				claw_drive = MIN_MOTOR;
			}
		} // end CLAW_MODE_HOLD

		/* now set the motor drive */
		motor[C1] = claw_drive;
		motor[C2] = claw_drive;

		wait1Msec(20);

	}	 // end while(1)
}	 // end task
task usercontrol()
{
	// User control code here, inside the loop

	// This is the main execution loop for the user control program. Each time through the loop
	// your program should update motor + servo values based on feedback from the joysticks.

	// .....................................................................................
	// Insert user code here. This is where you use the joystick values to update your motors, etc.
	// .....................................................................................

	stopTask(hold_wrist);
	startTask(user_a_bot);
}