#pragma config(Motor,  port1,           motor1,        tmotorVex393, openLoop)
#pragma config(Motor,  port10,          motor2,        tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
motor[motor1] = vexRT[Ch3];
motor[motor2]  = vexRT[Ch3];

}
