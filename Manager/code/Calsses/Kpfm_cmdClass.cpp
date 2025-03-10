//---------------------------------------------------------------------------

#pragma hdrstop

#include "Kpfm_cmdClass.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall Kpfm_cmdClass::Kpfm_cmdClass()
{
	InitValues();
	CreateObjects();
	ConfigClass();
}
//---------------------------------------------------------------------------

void Kpfm_cmdClass::CreateObjects()
{
	mainForm->LogToFile("Kpfm_cmdClass::CreateObjects");
	if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}
	if(!mutex){
		mutex = new TMutex(false);
	}
}
//---------------------------------------------------------------------------

void Kpfm_cmdClass::InitValues()
{
	mainForm->LogToFile("Kpfm_cmdClass::InitValues");
	myUdpDataSendClass = NULL;
	mutex = NULL;
}
//---------------------------------------------------------------------------

void Kpfm_cmdClass::ConfigClass()
{

}
//---------------------------------------------------------------------------

void Kpfm_cmdClass::SendKpfm
(int Frequency, int DriveVoltage, byte LIA1OnOff, int LIA1, int Ki, int Kp, int Kd, int Th, int BiasOnOff)
{
	mainForm->LogToFile("Kpfm_cmdClass::SendKpfm");
//	mainForm->LogToFile("Kpfm_cmdClass: Frequency : " + IntToStr(Frequency));
//	mainForm->LogToFile("Kpfm_cmdClass: DriveVoltage : " + IntToStr(DriveVoltage));
//	mainForm->LogToFile("Kpfm_cmdClass: LIA1OnOff : " + IntToStr(LIA1OnOff));
//	mainForm->LogToFile("Kpfm_cmdClass: LIA1 : " + IntToStr(LIA1));
//	mainForm->LogToFile("Kpfm_cmdClass: Ki : " + IntToStr(Ki));
//	mainForm->LogToFile("Kpfm_cmdClass: Kp : " + IntToStr(Kp));
//	mainForm->LogToFile("Kpfm_cmdClass: Kd : " + IntToStr(Kd));
//	mainForm->LogToFile("Kpfm_cmdClass: Th : " + IntToStr(Th));
//	mainForm->LogToFile("Kpfm_cmdClass: BiasOnOff : " + IntToStr(BiasOnOff));


	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->KpfmPacket(Frequency, DriveVoltage, LIA1OnOff, LIA1, Ki, Kp, Kd, Th, BiasOnOff));
	mainForm->myUdpThread->SetSendDataTrue();
	mutex->Release();
}
//---------------------------------------------------------------------------
