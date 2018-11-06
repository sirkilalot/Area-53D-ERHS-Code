task PIDLeft {
	int threshold=5;
	int d,i;
	int X1 = 0, Y2 = 0;
	float a,b,error,p,power;
	float lastError = 0;
	float totalError = 0;
	float Deriv = 0;
	float  Kp = 25;
	float  Ki = 0.04;
	float  Kd = 10;
	int	allowedError=5;
	a=SensorValue[LDE];
	b=a;
	while(true)
	{
		Y2=vexRT[Ch2];
		X1=vexRT[Ch1];
		if(abs(Y2)<threshold) Y2=0;
		if(abs(X1)<threshold) X1=0;


		b=SensorValue[LDE];
		error=(b-a);
		if(abs(error)>allowedError){

			totalError+=error;
			Deriv=error-lastError;
			lastError=error;
			p=error*Kp;
			i=totalError*Ki;
			d=Deriv*Kd;

		}

		else{
			p=0;
			i=0;
			totalError=0;
			d=0;
		}
		if(abs(error)>100) i=0;

		power=-(p+i+d);



		if((abs(vexRT[Ch3]) < threshold)&&(abs(vexRT[Ch2]) < threshold)){
			if(power>127) power=127;
			else if(power<-127) power=-127;
			motor[LDrive]=power;

		}
		else{
			a=SensorValue[LDE];
			motor[LDrive] = Y2+X1;
		}
		wait1Msec(20);

	}
	//END PIDLeft
}

task PIDRight {
	int threshold=5;
	int d,i;
	int X1 = 0, Y2 = 0;
	float a,b,error,p,power;
	float lastError = 0;
	float totalError = 0;
	float Deriv = 0;
	float  Kp = 25;
	float  Ki = 0.04;
	float  Kd = 10;
	int	allowedError=10;
	a=SensorValue[RDE];
	b=a;
	while(true)
	{
		Y2=vexRT[Ch2];
		X1=vexRT[Ch1];
		if(abs(Y2)<threshold) Y2=0;
		if(abs(X1)<threshold) X1=0;



		b=SensorValue[RDE];
		error=(b-a);
		if(abs(error)>allowedError){

			totalError+=error;
			Deriv=error-lastError;
			lastError=error;
			p=error*Kp;
			i=totalError*Ki;
			d=Deriv*Kd;

		}

		else{
			p=0;
			i=0;
			totalError=0;
			d=0;
		}
		if(abs(error)>100) i=0;

		power=-(p+i+d);



		if((abs(vexRT[Ch3]) < threshold)&&(abs(vexRT[Ch2]) < threshold)){
			if(power>127) power=127;
			else if(power<-127) power=-127;
			motor[RDrive]=power;

		}
		else{
			a=SensorValue[RDE];
			motor[RDrive] = Y2-X1;
		}
		wait1Msec(20);

	}
	//END PIDRight
}
/*task LiftControl
{

if(vexRT[Btn5U]) {
motor[LTower]=127;
motor[RTower]=127;
}
else if(vexRT[Btn5D]) {
motor[LTower]=-127;
motor[RTower]=-127;
}
else{
motor[LTower]=0;
motor[RTower]=0;
}
}
}
}*/

task Driving
{
	int Y2=0, Y3=0, Y22=0, Y32=0, reversed=0, threshold=5;
	while (true){
		while(reversed==0){
			Y2=vexRT[Ch2];
			Y3=vexRT[Ch3];
			if(abs(Y2)<threshold) Y2=0;
			if(abs(Y3)<threshold) Y3=0;
			motor[RDrive]=Y2;
			motor[RDrive1]=Y2;
			motor[LDrive]=Y3;
			motor[LDrive1]=Y3;
			if(vexRT[Btn8U]) reversed=1;
		}
		Y32=-vexRT[Ch2Xmtr2];
		Y22=-vexRT[Ch3Xmtr2];
		if(abs(Y22)<threshold) Y22=0;
		if(abs(Y32)<threshold) Y32=0;
		motor[RDrive]=Y22;
		motor[RDrive1]=Y22;
		motor[LDrive]=Y32;
		motor[LDrive1]=Y32;
		if(vexRT[Btn8RXmtr2]) reversed=0;

	}
}

task LiftControl
{
	int auto=1;

	while(true){

		while(auto==1){
		//automatic lift control
		if(vexRT[Btn7U]) LiftPos(2);
		if(vexRT[Btn7L]) LiftPos(1);
		if(vexRT[Btn7D]) LiftPos(0);
		//switch lift to manual control
		if(vexRT[Btn7R]) auto=0;
		}

		//manual lift control
			if(vexRT[Btn5U]) {
			motor[LTower]=127;
			motor[RTower]=127;
		}
		else if(vexRT[Btn5D]) {
			motor[LTower]=-127;
			motor[RTower]=-127;
		}
		else{
			motor[LTower]=0;
			motor[RTower]=0;
		}
		//switch back to automatic
		if(vexRT[Btn7R]) auto=1;

	}
}

task Control
{

	while(true)
	{
		//---------------------------------------------FIRST CONTROLER----------------------------------------------------------


		//4-bar lift


		//capflipper
		if(vexRT[Btn6U]){
			motor[CFlipper]=127;
		}

		else if(vexRT[Btn6D]){
			motor[CFlipper]=-127;
		}
		else
			motor[CFlipper]=0;
		/*
		if (vexRT[Btn8D]){
		reset();
		drive(1300);
		drive(-900);
		delay(300);
		motor[RDrive]=-60;
		motor[RDrive1]=-60;
		motor[LDrive1]=60;
		motor[LDrive1]=60;
		delay(66);
		stopDrive();
		flyStart();
		delay(5500);
		motor[BIntake]=127;
		delay(1000);
		motor[BIntake]=0;
		flyStop();


		}
		*/
		//---------------------------------------------SECOND CONTROLER----------------------------------------------------------

/*
		//ball intake
		if(vexRT[Btn6UXmtr2])
			motor[BIntake]=-127;
		else if(vexRT[Btn6DXmtr2])
			motor[BIntake]=127;
		else motor[BIntake]=0;

		//flywheel
		if (vexRT[Btn5UXmtr2]){
			motor[FlyWheel]=127;
			motor[FlyWheel1]=127;
		}
		else if (vexRT[Btn5DXmtr2]){
			motor[FlyWheel]=-127;
			motor[FlyWheel1]=-127;
		}
		else{
			motor[FlyWheel]=0;
			motor[FlyWheel1]=0;
		}
	*/
	}
}
