#pragma config(Sensor, dgtl1,  left,           sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  right,          sensorQuadEncoder)

task main()
{
	while (true){


		bMotorReflected[port1] = false;
		bMotorReflected[port10] = true;
		bMotorReflected[port2] = true;
		bMotorReflected[port9] = false;

		if (SensorValue[left] < 5150) {

		motor[port1] = 127;
		motor[port2] = 127;
		motor[port9] = 127;
		motor[port10] = 127;

}

		else {

		motor[port1] = 0;
		motor[port2] = 0;
		motor[port9] = 0;
		motor[port10] = 0;



	}

}}
