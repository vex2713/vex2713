//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program


void stopDriving(){
	//Stops all Driving Motors
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
}

void leftDriveSpeed(int speed){
	//Make Left Motors drive at speed
	motor[backLeft] = speed;
	motor[frontLeft] = speed;
}

void rightDriveSpeed(int speed){
	//Make Right motors drive at speed
	motor[backRight] = speed;
	motor[frontRight] = speed;
}

void driveControl(int driveMode){// tank = 1 arcade = 2 RC = 3
	//Standard drive control
	if (driveMode == 2){
		//Arcade Drive
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch4];
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch4];
		motor[backLeft]  = vexRT[Ch3] + vexRT[Ch4];
		motor[backRight] = vexRT[Ch3] - vexRT[Ch4];
		}else if(driveMode == 1){
		//Tank Drive
		motor[frontLeft]  = vexRT[Ch3];
		motor[frontRight] = vexRT[Ch2];
		motor[backLeft]  = vexRT[Ch3];
		motor[backRight] = vexRT[Ch2];
	}
	else if(driveMode == 3){
		//RC Car
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch1];
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch1];
		motor[backLeft]  = vexRT[Ch3] + vexRT[Ch1];
		motor[backRight] = vexRT[Ch3] - vexRT[Ch1];
}

}

void servoOpen(int motnrNumb){
	motor[motnrNumb] = 127;
}

void servoClose(int motnrNumb){
	motor[motnrNumb] = -127;
}

void servoMid(int motnrNumb){
	motor[motnrNumb] = 0;
}

void clawControl(int motorNumb){
	if(vexRT[Btn7U]||vexRT[Btn5D]){//close
		servoOpen(motorNumb);
	}
	else if(vexRT[Btn7D]||vexRT[Btn5U]) {//open
		servoClose(motorNumb);
	}
	else if(vexRT[Btn7R]) {//Mid
		servoMid(motorNumb);
	}
}

void clawPosControl(int motorNumb){
	if(vexRT[Btn8U]){
		servoOpen(motorNumb);
	}
	else if(vexRT[Btn8D]) {
		servoClose(motorNumb);
	}
	else if(vexRT[Btn8R]) {
		servoMid(motorNumb);
	}
}

void driveStraight(float feet, int BOT_ID){
	float distance=232*feet;
	//(256 per rotation / 13.25in per wheel rotation) * (12in / 1in) = 232 Counts per Foot & 19 Counts per Inch. (A-Bot)
	//Omni-Directional Wheels
	if (BOT_ID==1){
		nMotorEncoder[frontRight]  =0;
		nMotorEncoder[frontLeft]  =0;
	}
	else if (BOT_ID==2){
		nMotorEncoder[backRight]  =0;
		nMotorEncoder[backLeft]  =0;
	}

	float distanceTraveled = 0;
	int maxSpeed = 90;

	int rightSensor;
	int leftSensor;
	int rightPower;
	int leftPower;

	while (distance > distanceTraveled)
	{
		if (BOT_ID==1){
			rightSensor = nMotorEncoder[frontRight];
			leftSensor = nMotorEncoder[frontLeft];
		}
		else if (BOT_ID==2){
			rightSensor = nMotorEncoder[backRight];
			leftSensor = nMotorEncoder[backLeft];
		}

		distanceTraveled = rightSensor;
		distanceTraveled = abs(distanceTraveled);
		if(leftSensor>rightSensor){
			rightPower =maxSpeed;
			leftPower =maxSpeed-(leftSensor-rightSensor);
		}
		else if(rightSensor>leftSensor){
			leftPower =maxSpeed;
			rightPower =maxSpeed-(rightSensor-leftSensor);

		}
		else
		{
			rightPower =maxSpeed;
			leftPower =maxSpeed;
		}


		leftDriveSpeed(leftPower);
		rightDriveSpeed(rightPower);

	}
	stopDriving();
}
/*
void testDriveAuto(string direction, int autoSpeed){//12ft = 0.90566 rotation
	while(direction == "F"){
		motor[backLeft] = autoSpeed;
		motor[backRight] = autoSpeed;
		motor[frontLeft] = autoSpeed;
		motor[frontRight] = autoSpeed;
	}
	while(direction == "B"){

	}
	while(direction == "L"){

	}
}
*/
void turn(float deg){
	float targetDistance = 2*abs(deg); //Not sure if 2 is appropriate
	int currentDistance = 0;
	nMotorEncoder[frontRight]  =0;

	if (deg < 0){
		//Turning Left
		leftDriveSpeed(-127);
		rightDriveSpeed(127);
		}else{
		//Turning Right
		leftDriveSpeed(127);
		rightDriveSpeed(-127);
	}
	//Wait until desired angle is reached
	while(targetDistance > currentDistance){
		currentDistance = abs(nMotorEncoder[frontRight]);
	}
	//Stop Motors
	stopDriving();
}
