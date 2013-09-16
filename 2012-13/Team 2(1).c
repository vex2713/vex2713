
task main()
{
	while (true)

{
int channel1 = vexRT[Ch1];
int channel2 = vexRT[Ch2];

int left = vexRT[Ch2];
int right = vexRT[Ch2];

if (channel1 < -15 || channel1 > 15)

{

if (channel1 < 0)
	right = channel2 - channel1;

if (channel1 > 0)
	left = channel2 + channel1;

}

motor[port1] = right;
motor[port10] = left;
motor[port3] = left;
motor[port4] = right;
bMotorReflected[port1] = true;
bMotorReflected[port10] = false;
bMotorReflected[port3] = true;
bMotorReflected[port4] = false;
}


}
