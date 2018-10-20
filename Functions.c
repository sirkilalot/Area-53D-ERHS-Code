void reset(){
	SensorValue[RDE]=0;
	SensorValue[LDE]=0;
	SensorValue[LTower]=0;
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
/*
void drive(int g){
	int p;
	p=g-SensorValue[RDE];
	while (abs(p)>7){
		motor[LDrive]=p*4.3;
		motor[LDrive1]=p*4.3;
		motor[RDrive]=p*4.3;
		motor[RDrive1]=p*4.3;
		p=g-SensorValue[RDE];
	}
	stopDrive();
}
*/
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
	p=g-nMotorEncoder[LTower];
	while (abs(p)>20){
		motor[LTower]=p*3.3;
		motor[RTower]=p*3.3;
		p=g-nMotorEncoder[LTower];
	}
	motor[LTower]=0;
	motor[RTower]=0;
}
