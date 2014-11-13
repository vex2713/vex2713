void driveStraight(float feet)
{
	float distance=200*feet;//we measured and found that 200 is a good value
	nMotorEncoder[MotorRightFront]  =0;
	nMotorEncoder[MotorLeftFront]  =0;
	float distanceTraveled = 0;
	int rightSensor;
	int leftSensor;
	int rightPower;
	int leftPower;

	while (distance >= distanceTraveled)
	{
		rightSensor = nMotorEncoder[MotorRightFront];
		leftSensor = -nMotorEncoder[MotorLeftFront];
		distanceTraveled = rightSensor;
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



		motor[MotorLeftFront] = rightPower;
		motor[MotorRightFront] = leftPower;
		motor[MotorLeftBack] = leftPower;
		motor[MotorRightBack] = rightPower;

	}
	motor[MotorRightFront] = 0;
	motor[MotorLeftFront] = 0;
	motor[MotorRightBack] = 0;
	motor[MotorLeftBack] = 0;
}
