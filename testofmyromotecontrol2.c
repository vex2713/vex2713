#pragma config(Sensor, in1,    Potentiometer,  sensorPotentiometer)
#pragma config(Motor,  port4,           armMotor2,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           armMotor,      tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true)
	{

		if(vexRT[Btn7U] == 1)
		{
			if(SensorValue[Potentiometer] >= 4050)
			{
				motor[armMotor] = -40;
				motor[armMotor2] = -40;
			}
			if(SensorValue[Potentiometer] < 4000)
			{
				motor[armMotor] = 40;
				motor[armMotor2] = 40;
			}

		}
		else if(vexRT[Btn7D] == 1)
		{
			if(SensorValue[Potentiometer] >= 3050)
			{
				motor[armMotor] = -40;
				motor[armMotor2] = -40;
			}
			if(SensorValue[Potentiometer] < 3000)
			{
				motor[armMotor] = 40;
				motor[armMotor2] = 40;
			}

		}
		else if(vexRT[Btn7L] == 1)
		{
			if(SensorValue[Potentiometer] >= 2050)
			{
				motor[armMotor] = -40;
				motor[armMotor2] = -40;
			}
			if(SensorValue[Potentiometer] < 2000)
			{
				motor[armMotor] = 40;
				motor[armMotor2] = 40;
			}

		}
		if(vexRT[Btn7R] == 1)
		{
			if(SensorValue[Potentiometer] >= 1050)
			{
				motor[armMotor] = -40;
				motor[armMotor2] = -40;
			}
			if(SensorValue[Potentiometer] < 1000)
			{
				motor[armMotor] = 40;
				motor[armMotor2] = 40;
			}

		}
		else
		{
			motor[armMotor2] = 0;
			motor[armMotor] = 0;
		}



	}
}
