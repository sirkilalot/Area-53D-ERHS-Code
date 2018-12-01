task PIDLeft {
	int threshold=5;
	int d,i;
	int Y3=0;
	float a,b,error,p,power;
	float lastError = 0;
	float totalError = 0;
	float Deriv = 0;
	float  Kp = 22;
	float  Ki = 0.05;
	float  Kd = 5.4;
	int	allowedError=10
	a=SensorValue[LDE];
	b=a;
	while(true)
	{
		Y3=vexRT[Ch3];
		if(abs(Y3)<threshold) Y3=0;


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
			motor[LDrive]=Y3;
		}
		wait1Msec(20);

	}
	//END PIDLeft
}

task PIDRight {
	int threshold=5;
	int d,i;
	int Y2 = 0;
	float a,b,error,p,power;
	float lastError = 0;
	float totalError = 0;
	float Deriv = 0;
	float  Kp = 22;
	float  Ki = 0.05;
	float  Kd = 5.4;
	int	allowedError=10;
	a=SensorValue[RDE];
	b=a;
	while(true)
	{
		Y2=vexRT[Ch2];
		if(abs(Y2)<threshold) Y2=0;



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
			motor[RDrive] = Y2;
		}
		wait1Msec(20);

	}
	//END PIDRight
}


task Driving
{
	int Y2=0, Y3=0, threshold=5;
	while (true){
		while((true)&&(working==1)){
			Y2=vexRT[Ch2];
			Y3=vexRT[Ch3];
			if(abs(Y2)<threshold) Y2=0;
			if(abs(Y3)<threshold) Y3=0;
			motor[RDrive]=Y2;
			motor[LDrive]=Y3;

		}
	}
}
task LiftControl
{
	int auto=0;
	while (true){
		while((true)&&(working==1)){
			/*
			while(auto==1){
			//automatic lift control
			else if(vexRT[Btn7U]) LiftPos(2);
			else if(vexRT[Btn7L]) LiftPos(1);
			else if(vexRT[Btn7D]) LiftPos(0);
			//switch lift to manual control
			if(vexRT[Btn7R]) auto=0;
			}
			*/
			//manual lift control
			if(vexRT[Btn5U]) {
				motor[LTower]=127;
				motor[RTower]=127;
			}
			else if(vexRT[Btn5D]) {
				motor[LTower]=-127;
				motor[RTower]=-127;
			}
			//else if(vexRT[Btn8U]) flipNdip();
		//	else if(vexRT[Btn7U]) LiftPos(2);
		//	else if(vexRT[Btn7L]) LiftPos(1);
		//	else if(vexRT[Btn7D]) LiftPos(0);
			else{
				motor[LTower]=0;
				motor[RTower]=0;
			}
			//switch back to automatic
			//if(vexRT[Btn7R]) auto=1;

		}
	}
}
task Control
{

	while(true)
	{
		//---------------------------------------------FIRST CONTROLER----------------------------------------------------------


		//flip and dip

		//if(vexRT[Btn8U]) flipNdip();

		//capflipper
		if(vexRT[Btn6U]){
			motor[LCap]=40;
			motor[RCap]=40;
		}

		else if(vexRT[Btn6D]){
			motor[RCap]=-42;
			motor[LCap]=-42;
		}
		else {
			motor[RCap]=0;
			motor[LCap]=0;
		}
		if (vexRT[Btn8U])
			flyStart();
		else if (vexRT[Btn8D])
			flyStop();
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
