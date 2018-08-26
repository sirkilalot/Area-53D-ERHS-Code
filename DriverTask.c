task PIDLeft {
	int threshold=5;
	int d,i;
	int X1 = 0, Y2 = 0;
	float a,b,error,p,power;
	float lastError = 0;
	float totalError = 0;
	float Deriv = 0;
	float  Kp = 25;
	float  Ki = 0;
	float  Kd = 10;
	int	allowedError=5;
	a=SensorValue[LDE];
	b=a;
	while(true)
	{
		Y2=vexRt[Ch2];
		X1=vexRT[ch1];
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
	float  Kp = 4;
	float  Ki = 0.04;
	float  Kd = 100;
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

task FlipaCap
{
	int CF=180;
	if(SensorValue[CFlip]%CF==0) SensorValue[CFlip]+=1;
	while(SensorValue[CFlip]>CF) SensorValue[CFlip]-=CF;
	while(SensorValue[CFlip]<CF) motor[CFlipper]=127;
	motor[CFlipper]=-127;
	wait1Msec(3);
	motor[CFlipper]=0;
}

task Control
{
	int threshold = 5;
	int Y2=0, X1=0, Y3=0, on=0;
	while(true)
	{
		//---------------------------------------------FIRST CONTROLER----------------------------------------------------------
		//Drive
		Y2=vexRT[Ch2];
		Y3=vexRT[Ch3];
		if(abs(Y2)<threshold) Y2=0;
		if(abs(Y3)<threshold) Y3=0;
		motor[RDrive]=Y2;
		motor[LDrive]=Y3;

		//6-bar lift
		if(vexRT[Btn5U]){
			motor[LTower]=127;
			motor[RTower]=127;
		}
		else if(vexRT[Btn5D]){
			motor[LTower]=-127;
			motor[RTower]=-127;
		}
		else{
			motor[LTower]=0;
			motor[RTower]=0;
		}

				//capflipper

		if(vexRT[Btn8R]){
			starttask(FlipaCap);
		}
		else if(vexRT[Btn6U]){
			on=1;
			motor[CFlipper]=-127;
		}

		else if(vexRT[Btn6D]){
			on=1;
			motor[CFlipper]=127;
		}
		else if(on==1){
			on=0;
			motor[CFlipper]=0;
		}

		//---------------------------------------------SECOND CONTROLER----------------------------------------------------------


		//ball intake
		if(vexRT[Btn6UXmtr2])
			motor[BIntake]=127;
		else if(vexRT[Btn6DXmtr2])
			motor[BIntake]=-127;
		else motor[BIntake]=0;

		//flywheel
		if (vexRT[Btn5UXmtr2])
			motor[FlyWheel]=127;
		else
			motor[FlyWheel]=0;
	}
}
