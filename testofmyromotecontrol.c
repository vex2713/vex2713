#pragma config(Motor,  port4,           armMotor2,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           armMotor,      tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
while(true)
{
    //Arm Control
    if(vexRT[Btn6U] == 0)
    {
      motor[armMotor] = 40;
      motor[armMotor2] = 40;
    }
    else if(vexRT[Btn6D] == 0)
    {
      motor[armMotor] = -40;
      motor[armMotor2] = -40;
    }


}
}