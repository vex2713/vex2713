#pragma config(Sensor, dgtl1,  altControl,     sensorTouch)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           backRight,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	word strafeLeft=false;
	word strafeRight=false;
	word rotateLeft=false;
	word rotateRight=false;
	bool altControlUse=SensorValue(altControl);


	while(true){
		//Update buttons
		if(altControlUse==1){
			strafeLeft=vexRT[Btn7L];
			strafeRight=vexRT[Btn7R];
			rotateLeft=vexRT[Btn8L];
			rotateRight=vexRT[Btn8R];
		}
		else{
			strafeLeft=vexRT[Btn5U];
			strafeRight=vexRT[Btn6U];
			rotateLeft=vexRT[Btn5D];
			rotateRight=vexRT[Btn6D];
		}


		//Set motor direction based on button
		if(strafeLeft==1){
			//Move straight to the left
			motor[frontLeft]  = -127;
			motor[frontRight] = 127;
			motor[backLeft]  = 127;
			motor[backRight] = -127;
		}
		else if(strafeRight==1){
			//Move straight to the right
			motor[frontLeft]  = 127;
			motor[frontRight] = -127;
			motor[backLeft]  = -127;
			motor[backRight] = 127;
		}

		else if(rotateRight==1){
			//Rotate Clockwise
			motor[frontLeft]  = 127;
			motor[frontRight] = -127;
			motor[backLeft]  = 127;
			motor[backRight] = -127;
		}

		else if(rotateLeft==1){
			//Rotate Counter-Clockwise
			motor[frontLeft]  = -127;
			motor[frontRight] = 127;
			motor[backLeft]  = -127;
			motor[backRight] = 127;
		}
		else{
			//Tank Drive
			motor[frontLeft]  = vexRT[Ch2];
			motor[frontRight] = vexRT[Ch3];
			motor[backLeft]  = vexRT[Ch2];
			motor[backRight] = vexRT[Ch3];
		}
	}
}
