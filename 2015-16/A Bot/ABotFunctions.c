//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program

#include "../global/GFunctions.c"

void ClawControl
{
	while (true)
	{
		motor[Left] = vexRT[Ch3];
		motor[Right] = vexRT[Ch2];

		if(vexRT[Btn7U]){//close
			motor[Claw] = 127;
		}
		else if(vexRT[Btn7D]) {//open
			motor[Claw] = -127;
		}
		if(vexRT[Btn6U]){
			motor[Arm] = 127;
		}
		else if (vexRT[Btn6D]){
			motor[Arm] = -127;
		}
		else {
			motor[Arm] = 0;
		}
	}
}
void ABotAutonomous
{
	motor[Left] = 100;
	motor[Right] = 100;
	wait(1.5);
	motor[Left] = 0;
	motor[Right] = 0;
}
