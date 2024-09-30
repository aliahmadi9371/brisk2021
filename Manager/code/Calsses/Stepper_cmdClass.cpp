//---------------------------------------------------------------------------
#pragma hdrstop
#include "Stepper_cmdClass.h"
#pragma package(smart_init)

#include "mainUnit.h"
//---------------------------------------------------------------------------
__fastcall Stepper_cmdClass::Stepper_cmdClass()
{
	InitClass();
	CreateClassObjects();
	ConfigClass();
}
//---------------------------------------------------------------------------

void Stepper_cmdClass::InitClass()
{

}
//---------------------------------------------------------------------------

void Stepper_cmdClass::CreateClassObjects()
{
	mainForm->LogToFile("Stepper_cmdClass::CreateClassObjects");
	myUdpDataSendClass = new UdpDataSendClass(NULL);
	mutex = new TMutex(false);
}
//---------------------------------------------------------------------------

void Stepper_cmdClass::ConfigClass()
{



}
//---------------------------------------------------------------------------

void Stepper_cmdClass::StepperSide(byte StateM, int StatusMove, int Stop, bool Shift)
{
	mainForm->LogToFile("Stepper_cmdClass::StepperSide");
	int State = StageTable.Stage_StepperStepMicro_Val;
	int SpeedFast = StageTable.Stage_StepperSpeed_Val_Fast;
	int SpeedSlow = StageTable.Stage_StepperSpeed_Val_Slow;

	int Speed;
	if (Shift)
		Speed = SpeedFast;
	else
		Speed = SpeedSlow;

	byte Setting = 0;
	switch (State){
		case 0:{
			Setting = 0;
			break;
		}
		case 1:{
			Setting = 64;
			break;
		}
		case 2: {
			Setting = 128;
			break;
		}
		case 3:{
			Setting = 192;
			break;
        }
	}

	if (StateM == 0)
		Setting += 0;
	else
		Setting += 32;

	if (Stop == 0){
		if (StatusMove == 0)
			Setting += 16;
		else
			Setting += 8;
	}
	else
		Setting += 0;


	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->CoarseMovePacket(Setting,Speed,0));
	mainForm->myUdpThread->SetSendDataTrue();
	mutex->Release();
}
//---------------------------------------------------------------------------

void __fastcall Stepper_cmdClass::SendCoarseMovePacket()
{
	mainForm->LogToFile("Stepper_cmdClass::SendCoarseMovePacket");
	mainForm->myUdpThread->SendBytes();
}
//---------------------------------------------------------------------------

void Stepper_cmdClass::StepperALL(byte StateM, bool Shift)
{
	mainForm->LogToFile("Stepper_cmdClass::StepperALL");

	int State = MoveTable.Coarse_StepperStepMicro_Val;
	int SpeedFast = MoveTable.Coarse_StepperSpeed_Val_Fast;
	int SpeedSlow = MoveTable.Coarse_StepperSpeed_Val_Slow;


	int Speed;
	if (Shift)
		Speed = SpeedFast;
	else
		Speed = SpeedSlow;

	byte Setting = 0;
	switch (State){
		case 0:{
			Setting = 0;
			break;
		}
		case 1:{
			Setting = 64;
			break;
		}
		case 2:{
			Setting = 128;
			break;
		}
		case 3:{
			Setting = 192;
			break;
        }
	}

	if (StateM == 0)
		Setting += 0;
	else
		Setting += 32;

	Setting += 7;
//	ByteTobit = convert(setting);
//	satusDir = setting.ToString();

	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->CoarseMovePacket(Setting,Speed,0));
	mainForm->myUdpThread->SetSendDataTrue();
	mutex->Release();
}
//---------------------------------------------------------------------------

void Stepper_cmdClass::StepperOFF(byte StateM, bool Shift)
{
	mainForm->LogToFile("Stepper_cmdClass::StepperOFF");

	int State = MoveTable.Coarse_StepperStepMicro_Val;
	int SpeedFast = MoveTable.Coarse_StepperSpeed_Val_Fast;
	int SpeedSlow = MoveTable.Coarse_StepperSpeed_Val_Slow;


	int Speed;
	if (Shift)
		Speed = SpeedFast;
	else
		Speed = SpeedSlow;

	byte Setting = 0;
	switch (State){
		case 0:{
			Setting = 0;
			break;
		}
		case 1:{
			Setting = 64;
			break;
		}
		case 2:{
			Setting = 128;
			break;
		}
		case 3:{
			Setting = 192;
			break;
        }
	}


	if (StateM == 0)
		Setting += 0;
	else
		Setting += 32;

	Setting += 0;

//	ByteTobit = convert(setting);
//	satusDir = setting.ToString();

	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->CoarseMovePacket(Setting,Speed,0));
	mainForm->myUdpThread->SetSendDataTrue();
	mutex->Release();
}
//---------------------------------------------------------------------------

void Stepper_cmdClass::StepperA(byte StateM, bool Shift)
{
	mainForm->LogToFile("Stepper_cmdClass::StepperA");

	int State = MoveTable.Coarse_StepperStepMicro_Val;
	int SpeedFast = MoveTable.Coarse_StepperSpeed_Val_Fast;
	int SpeedSlow = MoveTable.Coarse_StepperSpeed_Val_Slow;


	int Speed;
	if (Shift)
		Speed = SpeedFast;
	else
		Speed = SpeedSlow;

	byte Setting = 0;
	switch (State){
		case 0:{
			Setting = 0;
			break;
		}
		case 1:{
			Setting = 64;
			break;
		}
		case 2:{
			Setting = 128;
			break;
		}
		case 3:{
			Setting = 192;
			break;
        }
	}


	if (StateM == 0)
		Setting += 0;
	else
		Setting += 32;

	Setting += 1;

//	ByteTobit = convert(setting);
//	satusDir = setting.ToString();

	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->CoarseMovePacket(Setting,Speed,0));
	mainForm->myUdpThread->SetSendDataTrue();
	mutex->Release();
}
//---------------------------------------------------------------------------

void Stepper_cmdClass::StepperB(byte StateM, bool Shift)
{
	mainForm->LogToFile("Stepper_cmdClass::StepperB");
	int State = MoveTable.Coarse_StepperStepMicro_Val;
	int SpeedFast = MoveTable.Coarse_StepperSpeed_Val_Fast;
	int SpeedSlow = MoveTable.Coarse_StepperSpeed_Val_Slow;

	int Speed;
	if (Shift)
		Speed = SpeedFast;
	else
		Speed = SpeedSlow;

	byte Setting = 0;
	switch (State){
		case 0:{
			Setting = 0;
			break;
		}
		case 1:{
			Setting = 64;
			break;
		}
		case 2:{
			Setting = 128;
			break;
		}
		case 3:{
			Setting = 192;
			break;
        }
	}


	if (StateM == 0)
		Setting += 0;
	else
		Setting += 32;

	Setting += 2;

//	ByteTobit = convert(setting);
//	satusDir = setting.ToString();

	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->CoarseMovePacket(Setting,Speed,0));
	mainForm->myUdpThread->SetSendDataTrue();
	mutex->Release();
}
//---------------------------------------------------------------------------

void Stepper_cmdClass::StepperC(byte StateM, bool Shift)
{
	mainForm->LogToFile("Stepper_cmdClass::StepperC");
	int State = MoveTable.Coarse_StepperStepMicro_Val;
	int SpeedFast = MoveTable.Coarse_StepperSpeed_Val_Fast;
	int SpeedSlow = MoveTable.Coarse_StepperSpeed_Val_Slow;

	int Speed;
	if (Shift)
		Speed = SpeedFast;
	else
		Speed = SpeedSlow;

	byte Setting = 0;
	switch (State){
		case 0:{
			Setting = 0;
			break;
		}
		case 1:{
			Setting = 64;
			break;
		}
		case 2:{
			Setting = 128;
			break;
		}
		case 3:{
			Setting = 192;
			break;
		}
	}


	if (StateM == 0)
		Setting += 0;
	else
		Setting += 32;

	Setting += 4;

//	ByteTobit = convert(setting);
//	satusDir = setting.ToString();

	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->CoarseMovePacket(Setting,Speed,0));
	mainForm->myUdpThread->SetSendDataTrue();
	mutex->Release();
}
//---------------------------------------------------------------------------
