#pragma config(Sensor, dgtl1,  toggle,         sensorTouch)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	bool go = false;
	int toggleMove = SensorValue(toggle);

	while(true){
		if(toggleMove == 1){

			go = !go;
			wait1Mec(1000);
		}
		if(go == true){
			motor[rightMotor] = 127;

		}
		else{
			motor[rightMotor] = 0;
		}
	}

}

//Quick code thrown together to test stuff. Quite messy
