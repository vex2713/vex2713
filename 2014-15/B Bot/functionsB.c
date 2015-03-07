//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program

#include "../global/GFunctions.c"

void setLiftSpeed(int speed){
	if(SensorValue(liftStop1)==1 || speed<=0){
		writeDebugStream("Lift Stop Button Pushed, not moving lift");
		wait1Msec(10);
		} else {
		motor[lift1] = speed;
		motor[lift2] = speed;
		motor[lift3] = speed;
		motor[lift4] = speed;
	}
}

void holdLift(){
	setLiftSpeed(20);
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
