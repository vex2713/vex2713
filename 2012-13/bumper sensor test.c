#pragma config(Sensor, dgtl1,  touchSensor,         sensorTouch)
#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  wait1Msec(2000);  // Robot waits for 2000 milliseconds before executing program

  while(SensorValue(touchSensor) == 0)  // Loop while robot's bumper/touch sensor isn't pressed in
  {
    motor[rightMotor] = 63;	 // Motor on port2 is run at half (63) power forward
    motor[leftMotor]  = 63;	 // Motor on port3 is run at half (63) power forward
  }
}