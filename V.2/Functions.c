void reset(){
	SensorValue[RDE]=0;
	SensorValue[LDE]=0;

}
/*
void flyStart(){
	motor[FlyWheel]=127;
	motor[FlyWheel1]=127;
}
void flyStop(){
	motor[FlyWheel]=0;
	motor[FlyWheel]=0;
}
*/
void stopDrive(){
	motor[LDrive]=0;
	motor[LDrive1]=0;
	motor[RDrive]=0;
	motor[RDrive1]=0;
}
//-----------------------------------------DRIVING---------------------------------------------------------------
void drive(int x){
	int error;
	float kp=2.05;
	int slave=-85;
	int master=-100;
	if (x<0){
		slave*=-1;
		master*=-1;
	}

	int totalticks=0;
	SensorValue[LDE]=0;
	SensorValue[RDE]=0;
	motor[LDrive]=slave;
	motor[LDrive1]=slave;
	motor[RDrive]=master;
	motor[RDrive1]=master;
	while (abs(totalticks)<abs(x)){
		motor[LDrive]=slave;
		motor[LDrive1]=slave;
		motor[RDrive]=master;
		motor[RDrive1]=master;
		displayLCDNumber(0,0,totalticks);
		error=SensorValue[RDE]-SensorValue[LDE];
		slave+=error/kp;
		totalticks+=SensorValue[LDE];
		SensorValue[LDE]=0;
		SensorValue[RDE]=0;

		delay(100);
	}
	stopDrive();
}
//-------------------------------------------------------------------------------------------------------------------------
void LTurn(){
	motor[LDrive]=-127;
	motor[LDrive1]=-127;
	motor[RDrive]=127;
	motor[RDrive1]=127;
}

void LiftPos(int x){
	int g,pos;
	int kp=.47;
	if(x==0) g=0;
	else if(x==1) g=1500;
	else if(x==2) g=3000;
	pos=g-SensorValue[Lift];
	while(abs(pos)>120){
		motor[LTower]=pos*kp;
		motor[RTower]=pos*kp;
		pos=g-SensorValue[Lift];
		delay(75);
	}
	motor[LTower]=0;
	motor[RTower]=0;
}
void flipNdip(){
	while (SensorValue[Lift]<(SensorValue[Lift]+500)){
		motor[LTower]=127;
		motor[RTower]=127;
	}
	motor[LTower]=0;
	motor[RTower]=0;
		motor[CFlipper]=127;
		delay(1800);
	motor[CFlipper]=0;
	while (SensorValue[Lift]<(SensorValue[Lift]-850)){
		motor[LTower]=-80;
		motor[RTower]=-80;
	}

}
