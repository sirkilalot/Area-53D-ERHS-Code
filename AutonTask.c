task Auton
{
	//------------------------------------------DECLARATIONS----------------------------------------------------------------------


	//------------------------------------------MOVEMENTCODE----------------------------------------------------------------------
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
