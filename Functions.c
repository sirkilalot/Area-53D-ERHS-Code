void reset(){
	SensorValue[RDE]=0;
	SensorValue[LDE]=0;
	SensorValue[RTower]=0;
}

void dflip(){
	int p;
	p=110-SensorValue[CFlip];
	while (abs(p)>8){
		motor[CFlipper]=p*3.3;
		p=110-SensorValue[CFlip];
	}
	motor[CFlipper]=-10;
}
void uflip(){
	int p;
	p=SensorValue[CFlip]-110;
	while (abs(p)>8){
		motor[CFlipper]=p*3.3;
		p=SensorValue[CFlip]-110;
	}
	motor[CFlipper]=-10;
}
void flyStart(){
	motor[FlyWheel]=127;
	motor[FlyWheel1]=127;
}
void flyStop(){
	motor[FlyWheel]=0;
	motor[FlyWheel]=0;
}
void stopDrive(){
	motor[LDrive]=0;
	motor[LDrive1]=0;
	motor[RDrive]=0;
	motor[RDrive1]=0;
}

void drive(int g){
	int p;
	p=g-SensorValue[RDE];
	while (abs(p)>5){
		motor[LDrive]=p*3.3;
		motor[LDrive1]=p*3.3;
		motor[RDrive]=p*3.3;
		motor[RDrive1]=p*3.3;
		p=g-SensorValue[RDE];
	}
	stopDrive();
}
void LTurn(){
	motor[LDrive]=-127;
	motor[LDrive1]=-127;
	motor[RDrive]=127;
	motor[RDrive1]=127;
}

void Lift(int x){
	int g,p;
	if(x==0) g=0;
	else if(x==1) g=600;
	else if(x==2) g=900;
	p=g-SensorValue[RTower];
	while (abs(p)>5){
		motor[LTower]=p*3.3;
		motor[RTower]=p*3.3;
		p=g-SensorValue[RTower];
	}
	motor[LTower]=0;
	motor[RTower]=0;
}
