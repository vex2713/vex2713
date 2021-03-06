#pragma config(Sensor, in1,    Potentiometer,  sensorPotentiometer)
#pragma config(Motor,  port1,           thing1,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           armMotor2,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port5,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           thing2,        tmotorVex269, openLoop)

task main()
{
	while(true)
	{
		{

			if(vexRT[Btn6U] == 1)
			{
				motor[armMotor] = -50;
				motor[armMotor2] = -50;
			}
			else if(vexRT[Btn6D] == 1)
			{
				motor[armMotor] = 50;
				motor[armMotor2] = 50;
			}
			else if(vexRT[Btn7U]==1)
			{
				motor[thing1] = 40;
				motor[thing2] = 40;
			}
			else
			{
				motor[armMotor2] = 0;
				motor[armMotor] = 0;
				motor[thing1] = 0;
				motor[thing2] = 0;
			}

		}
		{

			if(vexRT[Btn6U] == 1)
			{
				motor[armMotor] = -50;
				motor[armMotor2] = -50;
			}
			else if(vexRT[Btn6D] == 1)
			{
				motor[armMotor] = 50;
				motor[armMotor2] = 50;
			}
			else if(vexRT[Btn7U]==1)
			{
				motor[thing1] = 40;
				motor[thing2] = 40;
			}
			else
			{
				motor[armMotor2] = 0;
				motor[armMotor] = 0;
				motor[thing1] = 0;
				motor[thing2] = 0;
			}
			{
				int channel1 = vexRT[Ch1];
				int channel2 = vexRT[Ch2];

				int left = vexRT[Ch2];
				int right = vexRT[Ch2];

				if (channel1 < -15 || channel1 > 15)

				{

					if (channel1 < 0)
						right = channel2 - channel1;

					if (channel1 > 0)
						left = channel2 + channel1;

				}

				motor[port1] = right;
				motor[port10] = left;
				motor[port3] = left;
				motor[port4] = right;
				bMotorReflected[port1] = true;
				bMotorReflected[port10] = false;
				bMotorReflected[port3] = true;
				bMotorReflected[port4] = false;
			}


		}

	}
}
