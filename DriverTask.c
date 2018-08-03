task PIDLeft {
	int threshold=5;
	int d,i;
	int X1 = 0, Y2 = 0;
	float a,b,error,p,power;
	float lastError = 0;
	float totalError = 0;
	float Deriv = 0;
	float  Kp = 5;
	float  Ki = 0.03;
	float  Kd = 60.0;
	int	allowedError=20;
	a=SensorValue[LDE];
	b=a;
	while(true)
	{
		if(abs(vexRT[Ch3]) > threshold){
			Y2 = vexRT[Ch3];
			}else{
			Y2 = 0;
		}
			clearLCDLine(1);
		clearLCDLine(0);

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
		displayNextLCDNumber(p);
		displayNextLCDString(" ");
		displayNextLCDNumber(i);
		displayNextLCDString(" ");
		displayNextLCDNumber(d);
		displayNextLCDString(" ");
		displayNextLCDNumber(power);
		displayNextLCDString(" ");
		displayLCDPos(1,1);
		displayNextLCDNumber(error);
		displayNextLCDString(" ");


		if((abs(vexRT[Ch3]) < threshold)&&(abs(vexRT[Ch2]) < threshold)){
			if(power>127) power=127;
			else if(power<-127) power=-127;
			motor[LDrive]=power;
			motor[TopLDrive]=power;
			displayNextLCDNumber(power);
		}
		else{
			a=SensorValue[LDE];
			motor[LDrive] = Y2;
			motor[TopLDrive]=Y2;
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
	float  Kp = 5;
	float  Ki = 0.03;
	float  Kd = 60.0;
	int	allowedError=20;
	a=SensorValue[RDE];
	b=a;
	while(true)
	{
		if(abs(vexRT[Ch2]) > threshold){
			X1 = vexRT[Ch2];
			}else{
			X1 = 0;
		}
			clearLCDLine(1);
		clearLCDLine(0);

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
		displayNextLCDNumber(p);
		displayNextLCDString(" ");
		displayNextLCDNumber(i);
		displayNextLCDString(" ");
		displayNextLCDNumber(d);
		displayNextLCDString(" ");
		displayNextLCDNumber(power);
		displayNextLCDString(" ");
		displayLCDPos(1,1);
		displayNextLCDNumber(error);
		displayNextLCDString(" ");


		if((abs(vexRT[Ch3]) < threshold)&&(abs(vexRT[Ch2]) < threshold)){
			if(power>127) power=127;
			else if(power<-127) power=-127;
			motor[RDrive]=power;
			motor[TopRDrive]=power;
			displayNextLCDNumber(power);
		}
		else{
			a=SensorValue[RDE];
			motor[RDrive] = X1;
			motor[TopRDrive]=X1;
		}
		wait1Msec(20);

	}
	//END PIDRight
}

void Control()
{
	//DECLARATIONS
	int threshold = 5;

		while(true){

		}
}
