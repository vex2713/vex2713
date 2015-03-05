//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program

#include "../global/GFunctions.c"

void setLiftSpeed(int speed){
	if((SensorValue[liftStop1]==1 || SensorValue[liftStop2]==1) && speed<=0){
		speed=0;
	}
	motor[lift1] = speed;
	motor[lift2] = speed;
	motor[lift3] = speed;
	motor[lift4] = speed;
}

void holdLift(){
	motor[lift1] = 20;
	motor[lift2] = 20;
	motor[lift3] = 20;
	motor[lift4] = 20;
}

void liftControl(){
	if(vexRT[Btn8U]){
		setLiftSpeed(75);
	}
	else if(vexRT[Btn8D]){
		setLiftSpeed(-20);
		while(vexRT[Btn8D]){
			setLiftSpeed(-5);
		}
	}
	else {
		holdLift();
	}
}
