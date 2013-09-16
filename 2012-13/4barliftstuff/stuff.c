
task main()
{
	while(true)
	{
		motor[port8] = vexRT[Ch3];
		motor[port10] = vexRT[Ch2];
		motor[port9] = vexRT[Ch1];
		motor[port7] = vexRT[Ch4];
	}


}
