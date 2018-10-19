drive(int x){
int error;
int kp=4;
int p=0;
int slave=120;
SensorValue[LDE]=0;
SensorValue[RDE]=0;
	motor[LDrive]=slave;
	motor[LDrive1]=slave;
	motor[RDrive]=127;
	motor[RDrive1]=127;
  while (SensorValue[LDE]<x){
    motor[LDrive]=slave;
	  motor[LDrive1]=slave;
	  motor[RDrive]=127;
	  motor[RDrive1]=127;
    error=SensorValue[LDE]-SensorValue[RDE];
    slave+=error/kp;
    SensorValue[LDE]=0;
    SensorValue[RDE]=0;
  
  }
	motor[LDrive]=0;
	motor[LDrive1]=0;
	motor[RDrive]=0;
	motor[RDrive1]=0;
}
