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

void setLiftSpeed(int speed){
	motor[lift1] = speed;
	motor[lift2] = speed;
	motor[lift3] = speed;
	motor[lift4] = speed;
}

void holdLift(){
	motor[lift1] = 45;
	motor[lift2] = 45;
	motor[lift3] = 45;
	motor[lift4] = 45;
}

void liftControl(){
	if(SensorValue[liftStop1] || SensorValue[liftStop2]){
		setLiftSpeed(0);
	}
	else if(vexRT[Btn8U]){
		setLiftSpeed(100);
	}
	else if(vexRT[Btn8D]){
		setLiftSpeed(100);
	}
	else {
		holdLift();
	}
}
