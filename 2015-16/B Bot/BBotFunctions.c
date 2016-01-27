
void MotorChannels()
{
	motor[fLeft] = vexRT[Ch3];
		motor[fRight] = vexRT[Ch2];
		motor[bLeft] = vexRT[Ch3];
		motor[bRight] = vexRT[Ch2];
}
void AutonomousDrive()
{
  	motor[fLeft] = 127;
		motor[fRight] = 127;
		motor[bLeft] = 127;
		motor[bRight] = 127;
		wait(1.5);
		motor[fLeft] = 0;
		motor[fRight] = 0;
		motor[bLeft] = 0;
		motor[bRight] = 0;
}
task main()
{



}
