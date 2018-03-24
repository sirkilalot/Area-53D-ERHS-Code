#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  dr4bLeft,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  dr4bRight,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  mobileTouchTouch, sensorTouch)
#pragma config(Sensor, dgtl6,  leftMogo,       sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  rightMogo,      sensorNone)
#pragma config(Sensor, dgtl9,  backleftpot,    sensorQuadEncoder)
#pragma config(Sensor, dgtl11, backrightpot,   sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           mobileBoiBaseR, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           drFrBrBase,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           drFrBrBase2,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           frontLeftDrive, tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_4)
#pragma config(Motor,  port5,           frontRightDrive, tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_1)
#pragma config(Motor,  port6,           backLeftDrive, tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_3)
#pragma config(Motor,  port7,           backRightDrive, tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port8,           rightTop,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftTop,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mobileBoiBaseL, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;


//declare auton variables
int rightAutonSpeed = 125;	int leftAutonSpeed = 125;
int autonomousIMEtotalFL = 0, autonomousIMEtotalBL = 0, autonomousIMEtotalFR = 0, autonomousIMEtotalBR = 0;
//declaration of drive values: 0 is stopped, 1 is driving forward, 2 is driving backwards
int lcdyeeMode = 0, leftDrive = 0, rightDrive = 0, mogoLift = 0, drFrBrBaseVal = 0, drFrBrTop = 0, coneIntakeVal = 0;
//declaration of numerical operands for functions and IMEs
float kP = .2, fRSpeed = 124., fLSpeed = 124., rMod = 0., error = 0.;

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
//~~~~~~~~~~~LCD_functions~~~~~~~~~~~~\\
void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}
task lcdSet(){
	bLCDBacklight = true;
	clearLCD();
	while (True){
		if (nLCDButtons == 1){
			lcdyeeMode=lcdyeeMode-1;
			clearLCD();
			while(nLCDButtons == 1)
			{
				wait1Msec(10);
			}
		}
		if (nLCDButtons == 4){
			lcdyeeMode=lcdyeeMode+1;
			clearLCD();
			while(nLCDButtons == 4)
			{
				wait1Msec(10);
			}
		}
		/*if (nLCDButtons == 2){
			lcdyeeMode = 4;
			while(nLCDButtons == 4)
			{
				wait1Msec(10);
			}
		}*/
		if (lcdyeeMode > 4 || lcdyeeMode < 1){
			lcdyeeMode = 1;
		}
	}
}

task menuSwitch(){
	while (True){
		wait1Msec(10);
		if (lcdyeeMode == 1){
					clearLCD();
					displayLCDCenteredString(0, "Long Side");
					displayLCDCenteredString(1, "Red Side");
		}else if (lcdyeeMode == 2){
					clearLCD();
					displayLCDCenteredString(0, "Defense");
					displayLCDCenteredString(1, "No Boi");
		}else if (lcdyeeMode == 3){
					clearLCD();
					displayLCDCenteredString(0, "Auton 3");
					displayLCDCenteredString(1, "just reeee");
		}/*else if (lcdyeeMode == 4){
				clearLCD();
				displayLCDCenteredString(0, "The imes...");
				displayLCDCenteredString(1, "reset");
				imeReset();
		}*/
	}
}
//~~~~~~~~~PRE AUTON TASKS~~~~~~~~~~\\
void pre_auton()
{
	startTask( lcdSet );
	startTask( menuSwitch );
	//bStopTasksBetweenModes = true;
}

//~~~~~~~sensor functions~~~~~~~\\
void sensorResetDT () {
	SensorValue[backleftpot] = 0;
	SensorValue[backRightpot] = 0;
	SensorValue[leftMogo] = 0;

}
void potentiomReset() {
	//SensorValue[leftBackDrivePot] = 0;
	//SensorValue[rightBackDrivePot] = 0;
}
void imeReset(){
  nMotorEncoder[frontLeftDrive] = 0;
  nMotorEncoder[frontRightDrive] = 0;
  nMotorEncoder[backLeftDrive] = 0;
  nMotorEncoder[backRightDrive] = 0;
}
void autonAddition(){
	autonomousIMEtotalFL += nMotorEncoder[frontLeftDrive];
	autonomousIMEtotalFR += nMotorEncoder[frontRightDrive];
	autonomousIMEtotalBL += nMotorEncoder[backLeftDrive];
	autonomousIMEtotalBR += nMotorEncoder[backRightDrive];
	imeReset();
}
void resetGyro(){
	SensorValue[gyro] = 0;
}

//~~~~~~~auton driving functions~~~~~~~\\
void driveForward (int rSpeed, int tdelay){
	motor [frontLeftDrive] = 127;
	motor [frontRightDrive] = rSpeed;
	motor [backLeftDrive] = 127;
	motor [backRightDrive] = rSpeed;
	delay(tdelay); leftDrive = 1; rightDrive = 1;
}
void rightSpin (int mPower, int tdelay){
	motor [frontLeftDrive] = mPower;
	motor [frontRightDrive] = -mPower;
	motor [backLeftDrive] = mPower;
	motor [backRightDrive] = -mPower;
	delay(tdelay); leftDrive = 1; rightDrive = 2;
}
void leftSpin (int mPower, int tdelay){
	motor [frontLeftDrive] = -mPower;
	motor [frontRightDrive] = mPower;
	motor [backLeftDrive] = -mPower;
	motor [backRightDrive] = mPower;
	delay(tdelay); leftDrive = 2; rightDrive = 1;
}
void driveTrainLeft(int mPower, int tdelay){
	motor[frontLeftDrive] = mPower;
	motor[backLeftDrive] = mPower;
	delay(tdelay);
}
void driveBackwards (int rSpeed, int tdelay){
	motor [frontLeftDrive] = -127;
	motor [frontRightDrive] = -1 * rSpeed;
	motor [backLeftDrive] = -127;
	motor [backRightDrive] = -1 * rSpeed;
	delay(tdelay); leftDrive = 2; rightDrive = 2;
}
void stopDriveTrain (){
	motor [frontLeftDrive] = 0;
	motor [frontRightDrive] = 0;
	motor [backLeftDrive] = 0;
	motor [backRightDrive] = 0;
	leftDrive = 0; rightDrive = 0;
}
void mobileDrive (int mPower, int tdelay){
	motor [mobileBoiBaseL] = mPower;
	motor [mobileBoiBaseR] = mPower;
	delay(tdelay);
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

void driveDosBouysAuton(string motot1, string motot2, int driveType, int tdelay, int speedyBoi){
	//0 corresponds to stop, 1 corresonds to forward, 2 corresponds to backwards
	switch(driveType){
		case(0):
			motor[motot1] = speedyBoi;
			motor[motot2] = speedyBoi;
		case(1):
			motor[motot1] = speedyBoi;
			motor[motot2] = speedyBoi;
		case(2):
			motor[motot1] = speedyBoi;
			motor[motot2] = speedyBoi;
	}
	delay(tdelay);
}

int inchtoTicksTorque(float inches)
{
	int ticks;
	ticks = inches * 99.82;
	return ticks;
}

void moveDT(float distance, int speed)
{
	setLCDPosition(0, 0);
	displayNextLCDNumber(SensorValue[frontRightDrive]);
	setLCDPosition(1,0);
	displayNextLCDNumber(SensorValue[frontLeftDrive]);
	resetMotorEncoder(frontLeftDrive);
	resetMotorEncoder(frontRightDrive);
	SensorValue[frontLeftDrive] = -1000;
	SensorValue[frontRightDrive] = 1000;
	while (inchtoTicksTorque(abs(SensorValue[frontRightDrive]) < distance + 300|| abs(SensorValue[frontLeftDrive]) < distance + 300))
	{
		motor[frontLeftDrive] = speed;
		motor[frontRightDrive] = speed;
		motor[backLeftDrive] = speed;
		motor[backRightDrive] = speed;
	}
		motor[frontLeftDrive] = 0;
		motor[frontRightDrive] = 0;
		motor[backLeftDrive] = 0;
		motor[backRightDrive] = 0;
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
if (lcdyeeMode == 1){ //runs default auton
sensorResetDT ();
					while (SensorValue[leftMogo] >=-500) {
	motor[mobileBoiBaseL]=-127;
	motor[mobileBoiBaseR]=-127;
		}
	motor[mobileBoiBaseL]=0;
	motor[mobileBoiBaseR]=0;
		delay(10);
				while (SensorValue[backrightpot] <= 1300){
	motor[backLeftDrive]=127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=127;
	motor[frontRightDrive]=127;
			}
			stopDriveTrain();
	motor[mobileBoiBaseL]=0;
	motor[mobileBoiBaseR]=0;
		delay(10);
					while (SensorValue[leftMogo] <=0) {
	motor[mobileBoiBaseL]=127;
	motor[mobileBoiBaseR]=127;
		}
	motor[mobileBoiBaseL]=0;
	motor[mobileBoiBaseR]=0;
		delay(10);
				while (SensorValue[backrightpot] >= 50){
	motor[backLeftDrive]=-127;
	motor[backRightDrive]=-127;
	motor[frontLeftDrive]=-127;
	motor[frontRightDrive]=-127;
			}
		stopDriveTrain();
		delay(10);
						while (SensorValue[backrightpot] <= 780){
	motor[backLeftDrive]=-127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=-127;
	motor[frontRightDrive]=127;
			}
	stopDriveTrain();
		delay(10);
						while (SensorValue[backrightpot] <= 950){
	motor[backLeftDrive]=120;
	motor[backRightDrive]=120;
	motor[frontLeftDrive]=120;
	motor[frontRightDrive]=120;
			}
		stopDriveTrain();
		delay(10);
							while (SensorValue[leftMogo] >=-500) {
	motor[mobileBoiBaseL]=-127;
	motor[mobileBoiBaseR]=-127;
		}
	motor[mobileBoiBaseL]=0;
	motor[mobileBoiBaseR]=0;
		delay(10);
								while (SensorValue[backrightpot] <= 0){
	motor[backLeftDrive]=-127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=-127;
	motor[frontRightDrive]=127;
			}
	stopDriveTrain();
		delay(10);
}else if (lcdyeeMode == 2){
					while (SensorValue[backrightpot] <= 10000){
	motor[backLeftDrive]=127;
	motor[backRightDrive]=127;
	motor[frontLeftDrive]=127;
	motor[frontRightDrive]=127;
			}
			stopDriveTrain();
//runs auton 2, the electronic bugaloo
	
}else if (lcdyeeMode == 3){//autony boi 3, the disco tech digeridee
	
}
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Tasks                                        */
/*                                                                           */
/*  This task is used to control stacking robot during the user control      */
/*   phase of a VEX Competition.                                             */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//no u, finna dab

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
	/*SensorValue[gyro] = 0;
	SensorFullCount[gyro] = 3600;*/

	imeReset();
	int X1 = 0, Y2 = 0, threshold = 25; //Set Integer Variables

	clearLCD();
	/*startTask( lcdSet ); BSTOPTASKSBETWEENMODES HAS BEEN COMMENTED OUT, THEY ARE ALREADY
	STARTED IN PREAUTON AND SHOULDNT STOP BUT MIGHT
	startTask( menuSwitch );*/ 

	while (1==1)
	{

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

//~~~~~~~~~~~~~~~~~~~~~~driver_2~~~~~~~~~~~~~~~~~~~~~~~//

		//Cone intake control
		if(vexRT [Btn5UXmtr2]==1){
			coneIntakeVal = 1;
			//motor[coneIntake] = 127;
		}
		else if(vexRT [Btn5DXmtr2]==1) {
			coneIntakeVal = 2;
	    //		motor[coneIntake] = -127;
		}
		else if(coneIntakeVal == 1 || 2){
			coneIntakeVal = 0;
			//motor[coneIntake] = 0;
		}

		//Drive fourbar base (motors y'd)
		if(abs(vexRT[Ch2Xmtr2]) > threshold){
			if (vexRT[Ch2Xmtr2] > 0){ drFrBrBaseVal = 1; }else{ drFrBrBaseVal = 2; }
			motor[drFrBrBase] = vexRT[Ch2Xmtr2]; motor[drFrBrBase2] = vexRT[Ch2Xmtr2];
		}
		else{
			drFrBrBaseVal = 0;
			motor[drFrBrBase] = 0;
		}

		//Top bois
		if(abs(vexRT[Ch3Xmtr2]) > threshold){
			if (vexRT[Ch3Xmtr2] > 0){ drFrBrTop = 1; }else{ drFrBrTop = 2; }
			motor[leftTop] = vexRT[Ch3Xmtr2]; motor[rightTop] = vexRT[Ch3Xmtr2];
		}
		else{
			drFrBrTop = 0;
			motor[leftTop] = 0; motor[rightTop] = 0;
		}
}
}
