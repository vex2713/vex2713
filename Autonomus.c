
task main()
{

bMotorReflected[port1] = false;
bMotorReflected[port10] = true;
bMotorReflected[port2] = true;
bMotorReflected[port9] = false;

motor[port1] = 127;
motor[port2] = 127;
motor[port9] = 127;
motor[port10] = 127;

wait1Msec(5000);

motor[port1] = 0;
motor[port2] = 0;
motor[port9] = 0;
motor[port10] = 0;

}
