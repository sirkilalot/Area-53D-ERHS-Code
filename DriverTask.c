/*
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
*/
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
			Y2=vexRt[Ch2];
			X1=vexRT[ch1];
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

task flipCap
{
int CF=180;
int CFN=CF;
	SensorValue[CFlip]=abs(sensorValue[CFlip]);
	while (sensorValue[CFlip]>CF) sensorValue[CFlip]-=CF;
	while((CFN-sensorValue[CFlip])>=5) motor[CFlipper]=127;
	motor[CFlipper]=0;
	sensorValue[CFlip]-=CF;
}

task Control
{
	//DECLARATIONS
	int threshold = 5;
	int Y2=0, X1=0, Y4=0, on=0;
	while(true)
	{
//---------------------------------------------FIRST CONTROLER----------------------------------------------------------
			//drive
			Y2=vexRt[Ch2];
			X1=vexRT[Ch1];
			if(abs(Y2)<threshold) Y2=0;
			if(abs(X1)<threshold) X1=0;
			motor[RDrive]=Y2-X1;
			motor[RDrive]=Y2+X1;

			//capflipper
			if(vexRT[Btn7L]==1){
				startTask(flipCap);
			}
			else if(vexRT[Btn7U]==1){
				on=1;
				motor[CFlipper]=127;
			}
			else if(vexRT[Btn7D]==1){
				on=1;
				motor[CFlipper]=-127;
			}
			else if(on==1){
				on=0;
				motor[CFlipper]=0;
			}

			//6-bar lift
			Y4=vexRT[Ch4];
			if(abs(Y4)<threshold) Y4=0;
			motor[LeftBar]=Y4;
			motor[RightBar]=Y4;
//---------------------------------------------SECOND CONTROLER----------------------------------------------------------

			//ball intake
			if(vexRT[Btn7UXmtr2])
				motor[BIntake]=127;
			else if(vexRT[Btn7DXmtr2])
				motor[BIntake]=-127;
			else motor[BIntake]=0;
			//flywheel
			motor[FlyWheel]=127;
		}
}
