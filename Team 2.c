
task main()
{
	while (true)

{
motor[port1] = vexRT[Ch2];
motor[port10] = vexRT[Ch2];
motor[port3] = vexRT[Ch2];
motor[port4] = vexRT[Ch2];

bMotorReflected[port1] = true;
bMotorReflected[port10] = false;
bMotorReflected[port3] = true;
bMotorReflected[port4] = false;
}


}
