#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    onesdf,         sensorPotentiometer)
#pragma config(Sensor, in2,    twosdf,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  RDE,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  CFlip,          sensorQuadEncoder)
#pragma config(Sensor, dgtl11, LDE,            sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           BIntake,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           RDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           FlyWheel,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           FlyWheel1,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           RDrive1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           LDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LTower,        tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port8,           RTower,        tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port9,           LDrive1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          CFlipper,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Public Variables
static float Kp_T=0.4;
static float RequestedVal;

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#include "Functions.c"
#include "DriverTask.c"
#include "AutonTask.c"


void pre_auton()
{

	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.


	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}


task autonomous()
{

	startTask(Auton);
}

task usercontrol()
{
	// User control code here, inside the loop
	//startTask(PIDRight);
	//startTask(PIDLeft);
	startTask(Control);
}
