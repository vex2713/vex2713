#pragma config(Motor,  port1,           Left,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           Claw,          tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           Arm,           tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          Right,         tmotorVex393_HBridge, openLoop)

task main()
{
	while (true)
	{
		if(vexRT[Btn7U]){//close
			motor[Claw] = 127;
		}
		else if(vexRT[Btn7D]) {//open
			motor[Claw] = -127;
		}
		motor[Left] = vexRT[Ch3];
		motor[Right] = vexRT[Ch2];
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
