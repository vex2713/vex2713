//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program

#include "../../global/GFunctions.c"

/*
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
*/

void driveUntil(float dist){
	if(SensorValue[sonar] > dist){
		leftDriveSpeed(70);
		rightDriveSpeed(70);
		}else if(SensorValue[sonar] < dist){
		leftDriveSpeed(dist*15);
		rightDriveSpeed(dist*15);

		//Output: dgtl7
		//Input: dgtl6
	}
}


void moveShoulder(float position){
	int currentPosition = SensorValue[shoulderPot];
	int targetPosition = 1*position;
	int maxSpeed = 127;
	int speed = 0;

	while(currentPosition < targetPosition){
		speed = targetPosition - currentPosition;
		if (speed > maxSpeed){
			speed = maxSpeed;
		}
		motor[shoulderMotor] = speed;
	}
}

void jointControl(int motorPort, int potentiometer, int tarPos) {
	//step 1: determine the speed
	int speed = abs(SensorValue[potentiometer]-tarPos);
	if(speed>125){
		speed = 125;
	}
	//step 2: determine direction
	if(tarPos>SensorValue[potentiometer]){//motor needs to move forward
		motor[motorPort] = speed;
	}
	else{//motor runs backwards
		motor[motorPort] = -speed;
	}
}

//target position is 4000 and if reading is 3000 the motor speed will decrease
void manualArmControl(){
	motor[shoulderMotor]  = vexRT[Ch3Xmtr2];
	motor[shoulderMotor2]  = vexRT[Ch2Xmtr2];
	motor[elbowMotor]  = vexRT[Ch2Xmtr2];
}

void armControl(int elbowTarPos, int shoulderTarPos){
	jointControl(shoulderMotor, shoulderPot, shoulderTarPos);//shoulder motor = 5 potentiometer = 1
	jointControl(elbowMotor, elbowPot, elbowTarPos);//elbow motor = 6  potentiometer = 2
}

void armAuton(){
	motor[shoulderMotor] = 127;
	wait1Msec(2000);
	motor[shoulderMotor] = 127;
}
