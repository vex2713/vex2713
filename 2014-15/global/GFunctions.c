//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program

void driveControl(bool isTank){
//Standard drive control
	if (isTank == false){
		//Arcade Drive
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch4];
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch4];
		motor[backLeft]  = vexRT[Ch3] + vexRT[Ch4];
		motor[backRight] = vexRT[Ch3] - vexRT[Ch4];
		}else{
		//Tank Drive
		motor[frontLeft]  = vexRT[Ch3];
		motor[frontRight] = vexRT[Ch2];
		motor[backLeft]  = vexRT[Ch3];
		motor[backRight] = vexRT[Ch2];
	}
}

void driveStraight(float feet){
	float distance=232*feet;
	//(256 per rotation / 13.25in per wheel rotation) * (12in / 1in) = 232 Counts per Foot & 19 Counts per Inch. 
	//Omni-Directional Wheels
	nMotorEncoder[frontRight]  =0;
	nMotorEncoder[frontLeft]  =0;
	float distanceTraveled = 0;
	int rightSensor;
	int leftSensor;
	int rightPower;
	int leftPower;

	while (distance > distanceTraveled)
	{
		rightSensor = nMotorEncoder[frontRight];
		leftSensor = nMotorEncoder[frontLeft];
		distanceTraveled = rightSensor;
		distanceTraveled = abs(distanceTraveled);
		if(leftSensor>rightSensor){
			rightPower =127;
			leftPower =127-(leftSensor-rightSensor);
		}
		else if(rightSensor>leftSensor){
			leftPower =127;
			rightPower =127-(rightSensor-leftSensor);

		}
		else
		{
			rightPower =127;
			leftPower =127;
		}


		leftDriveSpeed(leftPower);
		rightDriveSpeed(rightPower);

	}
	stopDriving();
}

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