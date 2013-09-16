
task main()
{
	while(true)
	{
	motor[port3] = 95;
	wait1Msec(1000);
	motor[port3] = -95;
}
}
