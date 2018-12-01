void reset(){
	SensorValue[RDE]=0;
	SensorValue[LDE]=0;

}

void flyStart(){
motor[FlyWheel]=127;
motor[FlyWheel1]=127;
}
void flyStop(){
motor[FlyWheel]=0;
motor[FlyWheel1]=0;
}

void stopDrive(){
	motor[LDrive]=0;

	motor[RDrive]=0;

}
//-----------------------------------------DRIVING---------------------------------------------------------------
void drive(int x){
	float error;
	float kp=2.05;
	float slave=-85;
	int master=-100;
	if (x>0){
		slave*=-1;
		master*=-1;
	}

	int totalticks=0;
	SensorValue[LDE]=0;
	SensorValue[RDE]=0;
	motor[LDrive]=slave;
	motor[RDrive]=master;
	while (abs(totalticks)<abs(x)){
		motor[LDrive]=slave;
		motor[RDrive]=master;
		//clearLCDLine(0);
		//displaynextLCDNumber(totalticks);
		error=SensorValue[RDE]-SensorValue[LDE];
		slave+=error/kp;
		totalticks+=abs(SensorValue[LDE]);
		SensorValue[LDE]=0;
		SensorValue[RDE]=0;

		delay(100);
	}
	stopDrive();
}
//-------------------------------------------------------------------------------------------------------------------------
//turning P loop where right is possitive, and x is in degrees
void turn(float x){
	float error,p,g,diff,a,b;
	float kp=4;
	float slave=100;
	int master=-100;
	//temp
	float xConstant=(635/90);
	//endtemp

	g=x*xConstant;
	if (x<0){
		slave*=-1;
		master*=-1;
	}
	int totaldiff=0;
	SensorValue[LDE]=0;
	SensorValue[RDE]=0;
	motor[LDrive]=slave;
	motor[RDrive]=master;
	error=g-totaldiff;
	while ((totaldiff<abs(x))&&(error>7)){
		motor[LDrive]=slave;
		motor[RDrive]=master;
		//displayLCDNumber(0,0,totalticks);
		clearLCDLine(0);
		displaynextLCDNumber(totaldiff);
		error=g-totaldiff;
		slave=error*kp;
		master=-error*kp;
		if (x<0){
		slave*=-1;
		master*=-1;
		}
		a=abs(SensorValue[RDE]);
		b=abs(SensorValue[LDE]);
		totaldiff=abs(a-b);

		delay(100);
	}
	stopDrive();
}


void LiftPos(int x){
	float g,pos;
	float kp=.47;
	//bottom-most lift position
	if(x==0) g=1060;
	//middle cap position
	else if(x==1) g=2340;
	//highest cap position
	else if(x==2) g=3200;
	//for auton to riase but not tip in climbing
	else if(x==3) g=1800;
	pos=g-SensorValue[Lift];
	while(abs(pos)>120){
		motor[LTower]=pos*kp;
		motor[RTower]=pos*kp;
		pos=g-SensorValue[Lift];
		delay(20);
	}
	motor[LTower]=0;
	motor[RTower]=0;
}
//-----------------------not implimented yet----------------------------
void flipNdip(){
	working=0;
	float g;
	int b;
	b=SensorValue[Lift];
	while (SensorValue[Lift]<b+260){
		motor[LTower]=60;
		motor[RTower]=60;
	}
	motor[LTower]=10;
	motor[RTower]=10;

	motor[RCap]=60;
	motor[LCap]=60;
	delay(2200);
	drive(50);
	motor[RCap]=0;
	motor[LCap]=0;
	while (b<SensorValue[Lift]){
		motor[LTower]=-60;
		motor[RTower]=-60;
	}
	drive(-200);
	working=1;

}
