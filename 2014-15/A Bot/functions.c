void stopDriving(){
	//Stops all Driving Motors
	motor[MotorRightFront] = 0;
	motor[MotorLeftFront] = 0;
	motor[MotorRightBack] = 0;
	motor[MotorLeftBack] = 0;
}

void leftDriveSpeed(int speed){
	//Make Left Motors drive at speed
	motor[MotorLeftBack] = speed;
	motor[MotorLeftFront] = speed;
}

void rightDriveSpeed(int speed){
	motor[MotorRightBack] = speed;
	motor[MotorRightFront] = speed;
}

void driveStraight(float feet){
	float distance=232*feet;//(256 per rotation / 13.25in per wheel rotation) * (12in / 1in) = 232 Counts per Foot & 19 Counts per Inch
	nMotorEncoder[MotorRightFront]  =0;
	nMotorEncoder[MotorLeftFront]  =0;
	float distanceTraveled = 0;
	int rightSensor;
	int leftSensor;
	//Uselss Note, Please Ignore. Serves no purpose in life
	int rightPower;
	int leftPower;

	while (distance > distanceTraveled)
	{
		rightSensor = nMotorEncoder[MotorRightFront];
		leftSensor = nMotorEncoder[MotorLeftFront];
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
	nMotorEncoder[MotorRightFront]  =0;

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
		currentDistance = abs(nMotorEncoder[MotorRightFront]);
	}
	//Stop Motors
	stopDriving();
}

void armControl(){
	int shoulderMin = 100;
	int shoulderMax = 3500;

	int armMin = 100;
	int armMax = 3500; //How far can it go?

	if (SensorValue[shoulderPot]<shoulderMin || SensorValue[shoulderPot]>shoulderMax){
		motor[armShoulder] = 0;
	}
	else{
		motor[armShoulder] = vexRT[Ch3Xmtr2]; //Xmtr2 == Partner Controller
	}

	if (SensorValue[armPot]<armMin || SensorValue[armPot]>armMax){
		motor[armElbow] = 0;
	}
	else{
		motor[armElbow] = vexRT[Ch2Xmtr2];
	}

}

void pincherControl(){
	if (SensorValue[pincherStart]==1 || vexRT(Btn8D)){
		if (SensorValue[leftPincherStop]==0){
			motor[leftPincher]=127;
		}
		else{
			motor[leftPincher]=0;
		}

		if (SensorValue[rightPincherStop]==0){
			motor[rightPincher]=127;
		}
		else{
			motor[rightPincher]=0;
		}
	}
	else if(vexRT(Btn8U)){
		motor[leftPincher]=-80;
		motor[rightPincher]=-80;
	}
	else{
		motor[rightPincher]=0;
		motor[leftPincher]=0;
	}
}
