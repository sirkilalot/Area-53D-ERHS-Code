#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    BATERY_2_PORT,  sensorAnalog)
#pragma config(Sensor, in7,    AutoSelect,     sensorPotentiometer)
#pragma config(Sensor, in8,    rightMogo,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  backLeftDrive,  sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  drfbLeft,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  backRightDrive, sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           mobileBoiBaseR, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           backRightDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           frontRightDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           coneIntake,    tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_4)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_1)
#pragma config(Motor,  port6,           top,           tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_3)
#pragma config(Motor,  port7,           drFrBr,        tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port8,           backLeftDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           frontLeftDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mobileBoiBaseL, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//This code is for the VEX cortex platform
#pragma platform(VEX2)
//Select Download method as "competition"
#pragma competitionControl(Competition)
//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void pre_auton()
{
	bStopTasksBetweenModes = true;
}
//declare auton variables
//int rightAutonSpeed = 125;	int leftAutonSpeed = 125;
//declaration of drive values: 0 is stopped, 1 is driving forward, 2 is driving backwards
int  leftDrive = 0, rightDrive = 0, mogoLift = 0, drFrBrBaseVal = 0, drFrBrTop = 0, coneIntakeVal = 0;
//declaration of numerical operands for functions and IMEs
float kP = .2, fRSpeed = 124., error = 0.;

//~~~~~~~sensor functions~~~~~~~
void potReset() {
	SensorValue[rightMogo] = 0;
	SensorValue[backLeftDrive] = 0;
	SensorValue[drfbLeft] = 0;
	SensorValue[backRightDrive] = 0;
}
void imeReset(){
  nMotorEncoder[frontLeftDrive] = 0;
  nMotorEncoder[frontRightDrive] = 0;
  nMotorEncoder[backLeftDrive] = 0;
  nMotorEncoder[backRightDrive] = 0;
}
//~~~~~~~auton driving functions~~~~~~~
void stopDriveTrain (){
	motor [frontLeftDrive] = 0;
	motor [frontRightDrive] = 0;
	motor [backLeftDrive] = 0;
	motor [backRightDrive] = 0;
	leftDrive = 0; rightDrive = 0;
}
void stopDTyMobi(){
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] = 0;
	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
	motor[mobileBoiBaseL] = 0;
	motor[mobileBoiBaseR] = 0;
	leftDrive = 0; rightDrive = 0; mogoLift = 0;
}
void stopDrfb () {
	motor[drFrBr]=0;
	}
void drfbFull(){
	while (SensorValue[drfbLeft] <=82) {
	motor[drFrBr]=127;
		}
stopDrfb();
}
void mogoLiftDown(){
		while (SensorValue[rightMogo] <=1350) { //1495
	motor[mobileBoiBaseL]=-127;
	motor[mobileBoiBaseR]=-127;
		}
stopDTyMobi();
}
void mogoLiftup(){
		while (SensorValue[rightMogo] >=0) {
	motor[mobileBoiBaseL]=127;
	motor[mobileBoiBaseR]=127;
		}
stopDTyMobi();
}
void topOut(){
	motor[top]=127;
	delay(200);
}
void topIn(){
	motor[top]=-127;
	delay(200);
}
void rotateIn(){
	motor[coneIntake]=127;
}
void rotateOut(){
	motor[coneIntake]=-127;
}
void rotateStop(){
	motor[coneIntake]=0;
}
void topStop(){
	motor[top]=0;
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
task autonomous()
{
	if(SensorValue[AutoSelect] <= 1350) //Main
    {
	imeReset();
	potReset();
	mogoLiftDown ();
	drfbFull ();
	topOut();
	rotateIn();
				while (SensorValue[backRightDrive] <= 1300){ //Drive forward
	motor[backLeftDrive]=127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=127;
	motor[frontRightDrive]=127;
	motor[drFrBr]=20;
			}
			stopDriveTrain();
	motor[mobileBoiBaseL]=0;
	motor[mobileBoiBaseR]=0;
		delay(10);
	mogoLiftup ();
				while (SensorValue[backRightDrive] >= 50){ //Drive backwards
	motor[backLeftDrive]=-127;
	motor[backRightDrive]=-127;
	motor[frontLeftDrive]=-127;
	motor[frontRightDrive]=-127;
	motor[drFrBr]=20;
			}
		stopDriveTrain();
		delay(10);
						while (SensorValue[backRightDrive] <= 780){ //Turn
	motor[backLeftDrive]=-127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=-127;
	motor[frontRightDrive]=127;
	motor[drFrBr]=20;
			}
	stopDriveTrain();
		delay(10);
						while (SensorValue[backRightDrive] <= 950){ //Forward
	motor[backLeftDrive]=120;
	motor[backRightDrive]=120;
	motor[frontLeftDrive]=120;
	motor[frontRightDrive]=120;
	motor[drFrBr]=20;
			}
		stopDriveTrain();
		delay(10);
							while (SensorValue[rightMogo] >=-500) { //Bring out Mogo
	motor[mobileBoiBaseL]=-127;
	motor[mobileBoiBaseR]=-127;
	motor[drFrBr]=20;
		}
	motor[mobileBoiBaseL]=0;
	motor[mobileBoiBaseR]=0;
		delay(10);
								while (SensorValue[backRightDrive] <= 0){ //Back up
	motor[backLeftDrive]=-127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=-127;
	motor[frontRightDrive]=127;
	motor[drFrBr]=20;
			}
	stopDriveTrain();
		delay(10);
	}
 else if(SensorValue[AutoSelect] >= 1350 && SensorValue[AutoSelect] <= 2550)
    {
	motor[backLeftDrive]=127;  //Drive forward
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=127;
	motor[frontRightDrive]=127;
	delay(12500);
			}
 else if(SensorValue[AutoSelect] >= 2550 && SensorValue[AutoSelect] <= 4095)
    {
	motor[backLeftDrive]=127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=127;
	motor[frontRightDrive]=127;
	delay(12500);
			}
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
task usercontrol()
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LCD_FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
string mainBattery, backupBattery; //Set up Variables "mainBattery" "backupBattery"
bLCDBacklight = true; //Turn on the Backlight in the LCD
	int X1 = 0, Y2 = 0, threshold = 5; //Set Integer Variables
	while (1==1) //Infinite Loop
	{
		clearLCDLine(0); //Clears the Top Section of the Display
 clearLCDLine(1); //Clears the Bottom Section of the Display
if(SensorValue[AutoSelect] <= 1350)
		{
			displayLCDCenteredString(0, "Autonomous:"); //Display "Autonomous:" on the Top Line
			displayLCDCenteredString(1, "MGLb"); //Display the Autonomous on the Top Line
		}
else if(SensorValue[AutoSelect] >= 1350 && SensorValue[AutoSelect] <= 2550)
		{
			displayLCDCenteredString(0, "Autonomous:"); //Display "Autonomous:" on the Top Line
			displayLCDCenteredString(1, "Defense"); //Display the Autonomous on the Top Line
		}
else if(SensorValue[AutoSelect] >= 2550 && SensorValue[AutoSelect] <= 3500)
		{
			displayLCDCenteredString(0, "Autonomous:"); //Display "Autonomous:" on the Top Line
			displayLCDCenteredString(1, "SGC"); //Display the Autonomous on the Top Line
		}
else if(SensorValue[AutoSelect] >= 3500)
		{
//Display the Primary Robot battery voltage
displayLCDString(0, 0, "Primary: ");
sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the Value to be Displayed
displayNextLCDString(mainBattery);

int battery2Level = (int)((float)SensorValue[ BATERY_2_PORT ] * 5.48);


//Display the Backup battery voltage
displayLCDString(1, 0, "Backup: ");
sprintf(backupBattery, "%1.2f%c", battery2Level, 'V');    //Build the Value to be Displayed
displayNextLCDString(backupBattery);
//wait1Msec(200);
}
//~~~~~~~~~~~~~~~~~~Drivetrain PID~~~~~~~~~~~~~~~~~~~~~//

		//front alignment check every 600 ticks, calculate error
		if (abs(nMotorEncoder[frontLeftDrive]) || abs(nMotorEncoder[frontRightDrive]) >= 600){
			error = abs(nMotorEncoder[frontLeftDrive]) - abs(nMotorEncoder[frontRightDrive]);
			fRSpeed += error * kP;
			imeReset();
		}

//~~~~~~~~~~~~~~~~~~~~~~~Driver_Control_Controller_1~~~~~~~~~~~~~~~~~~~~~~~~~//
	  //if right joystick up || down
		if(abs(vexRT[Ch2]) > threshold){
			if(vexRT[Ch2] < 0){
				X1 = -1;
			}else if(vexRT[Ch2] > 0){
				X1 = 1;
			}
		}else{
			X1 = 0;
		}
		//if left joystick up || down
		if(abs(vexRT[Ch3]) > threshold){
			Y2 = vexRT[Ch3];
			/*if(vexRT[Ch3] < 0){
				Y2 = -1;
			}else if(vexRT[Ch3] > 0){
				Y2 = 1;
			}*/
		}else{
			Y2 = 0;
		}//drive the bois
		motor[frontLeftDrive] = Y2;
		motor[frontRightDrive] = X1 * fRSpeed;
		motor[backLeftDrive] = Y2;
		motor[backRightDrive] = X1 * fRSpeed;

		//if right top trigger pressed
		if (vexRT[Btn6U] == 1){
			mogoLift = 1;
			motor [mobileBoiBaseL] = 127;
			motor [mobileBoiBaseR] = 127;
		}
		//if right bottom trigger pressed
		else if (vexRT[Btn6D] == 1){
			mogoLift = 2;
			motor [mobileBoiBaseL] = -127;
			motor [mobileBoiBaseR] = -127;
		}else{
			mogoLift = 0;
			motor [mobileBoiBaseL] = 0;
			motor [mobileBoiBaseR] = 0;
		}

		//temporary ime reset
		if(vexRT[Btn7U] == 1){
			imeReset();
		}

//~~~~~~~~~~~~~~~~~~~~~~Diver_2~~~~~~~~~~~~~~~~~~~~~~~//

		//Cone intake control
		if(vexRT [Btn6UXmtr2]==1){
			coneIntakeVal = 1;
			motor[coneIntake] = 50;
		}
		else if(vexRT [Btn6DXmtr2]==1) {
			coneIntakeVal = 2;
	    		motor[coneIntake] = -50;
		}

		//Drive fourbar base (motors y'd)
		if(abs(vexRT[Ch2Xmtr2]) > threshold){
			if (vexRT[Ch2Xmtr2] > 0){ drFrBrBaseVal = 1; }else{ drFrBrBaseVal = 2; }
			motor[drFrBr] = vexRT[Ch2Xmtr2];
		}
		else{
			drFrBrBaseVal = 0;
			motor[drFrBr] = 0;
		}

		//Top bois
		if(abs(vexRT[Ch3Xmtr2]) > threshold){
			if (vexRT[Ch3Xmtr2] > 0){ drFrBrTop = 1; }else{ drFrBrTop = 2; }
			motor[top] = vexRT[Ch3Xmtr2];
		}
		else{
			drFrBrTop = 0;
			motor[top] = 0;
		}
}
}
