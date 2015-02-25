//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program


void stopDriving(){
	//Stops all Driving Motors
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
}

void driveSpeed(int speed, string side){
	if (side == "both"){
		motor[backLeft] = speed;
		motor[frontLeft] = speed;
		motor[backRight] = speed;
		motor[frontRight] = speed;
	}
	else if (side == "left"){
		motor[backLeft] = speed;
		motor[frontLeft] = speed;
	}
	else if (side == "right"){
		motor[backRight] = speed;
		motor[frontRight] = speed;
	}
}


void driveControl(int driveMode){// tank = 1 arcade = 2 RC = 3
	//Standard drive control
	float turnSpeed = 0.8;
	if (driveMode == 2){
		//Arcade Drive
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch4] * turnSpeed;
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch4] * turnSpeed;
		motor[backLeft]  = vexRT[Ch3] + vexRT[Ch4] * turnSpeed;
		motor[backRight] = vexRT[Ch3] - vexRT[Ch4] * turnSpeed;
		}else if(driveMode == 1){
		//Tank Drive
		motor[frontLeft]  = vexRT[Ch3];
		motor[frontRight] = vexRT[Ch2];
		motor[backLeft]  = vexRT[Ch3];
		motor[backRight] = vexRT[Ch2];
		}else if(driveMode == 3){
		//RC Car
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch1] * turnSpeed;
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch1] * turnSpeed;
		motor[backLeft]  = vexRT[Ch3] + vexRT[Ch1] * turnSpeed;
		motor[backRight] = vexRT[Ch3] - vexRT[Ch1] * turnSpeed;
	}
}
