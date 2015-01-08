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
