#pragma config(Motor,  port1,           FR,            tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           M,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           BL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           FL,            tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                           - Dual Joystick Control with Arm - 1 Remote -                            *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses both the Left and the Right joysticks to run the robot using "tank control".    *|
|*  The Group 6 buttons on the top-right of the VEXnet Joystick are used to raise and lower an arm.   *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    2)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]              [Name]              [Type]              [Description]                   *|
|*    Motor - Port 2          rightMotor           VEX Motor           Right motor                    *|
|*    Motor - Port 3          leftMotor            VEX Motor           Left motor                     *|
|*    Motor - Port 6          armMotor             VEX Motor           Arm motor                      *|
\*----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
	while(1 == 1)
	{
		//Driving Motor Control
		motor[FL] = vexRT[Ch3] / 1;
		motor[FR] = vexRT[Ch2] / 1;
		motor[BL] = vexRT[Ch3] / 1;
		motor[BR] = vexRT[Ch2] / 1;
	}
}
//    ;multi potato drive

//Arm Control
// if(vexRT[Btn6U] == 1)
// {
//   motor[armMotor] = 40;
//  }
// else if(vexRT[Btn6D] == 1)
// {
//   motor[armMotor] = -40;
// }
// else
//{
//  motor[armMotor] = 0;
// }
