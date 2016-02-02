
void NoJoystickDrive()
{
	motor[frontRight] = 100;
	motor[frontLeft] = 100;
	motor[backRight] = 100;
	motor[backLeft] = 100;
	wait(3);
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
}
void UsercontrolFunctions
{
	while (true)
	{
		motor[frontRight] = vexRT[Ch2];
		motor[frontLeft] = vexRT[Ch3];
		motor[backRight] = vexRT[Ch2];
		motor[backLeft] = vexRT[Ch3];
	}
}
