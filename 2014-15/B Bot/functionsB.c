//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program

#include "../global/GFunctions.c"

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
