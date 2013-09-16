
task main()
{

bMotorReflected[port1] = false;
bMotorReflected[port10] = true;
bMotorReflected[port2] = true;
bMotorReflected[port9] = false;

while (true)

{

motor[port1] = vexRT[Ch3];
motor[port2] = vexRT[Ch3];
motor[port9] = vexRT[Ch2];
motor[port10] = vexRT[Ch2];


}

}
