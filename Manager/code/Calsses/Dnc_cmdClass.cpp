//---------------------------------------------------------------------------
#pragma hdrstop
#include "Dnc_cmdClass.h"
#pragma package(smart_init)
#include "mainUnit.h"
//---------------------------------------------------------------------------

__fastcall Dnc_cmdClass::Dnc_cmdClass()
{
	InitClass();
	ConfigCalss();
	CreateClassObjects();
}
//---------------------------------------------------------------------------

void Dnc_cmdClass::ConfigCalss()
{

}
//---------------------------------------------------------------------------

void Dnc_cmdClass::InitClass()
{
	myUdpDataSendClass = NULL;
	mutex = NULL;
}
//---------------------------------------------------------------------------

void Dnc_cmdClass::CreateClassObjects()
{
	if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}

	if(!mutex){
		mutex = new TMutex(false);
	}
}
//---------------------------------------------------------------------------

void Dnc_cmdClass::GetDataFromUi()
{
	mainForm->LogToFile("Dnc_cmdClass::GetDataFromUi");
	From_Val = mainForm->myDynamicCurvePanelForm->From_Val;
	To_Val = mainForm->myDynamicCurvePanelForm->To_Val;
	Use_Val = mainForm->myDynamicCurvePanelForm->Use_Val;
	Drive_Val = mainForm->myDynamicCurvePanelForm->MainDriveVal;
	PointsCount_Val = mainForm->myDynamicCurvePanelForm->PointsCount_Val;
	SetPoint_Val = mainForm->myDynamicCurvePanelForm->SetPoint_Val;
	TimeCnt_Val = mainForm->myDynamicCurvePanelForm->TimeCnt_Val;
	PointsCount = mainForm->myDynamicCurvePanelForm->PointsCount_Val;
	Gain_Val = mainForm->myDynamicCurvePanelForm->Gain_Val;
	Rolloff = mainForm->myDynamicCurvePanelForm->Rolloff;


//	mainForm->LogToFile("From freq(Hz) = " + IntToStr(From_Val));
//	mainForm->LogToFile("to freq(Hz) = " + IntToStr(To_Val));
//	mainForm->LogToFile("use freq(Hz) = " + IntToStr(Use_Val));
//	mainForm->LogToFile("drive voltage(mV) = " + IntToStr(Drive_Val));
//	mainForm->LogToFile("sweep points val = " + IntToStr(PointsCount_Val));
//	mainForm->LogToFile("set point(%) = " + IntToStr(SetPoint_Val));
//	mainForm->LogToFile("delay(ms) = " + FloatToStr(TimeCnt_Val));
//	mainForm->LogToFile("sweep points = " + IntToStr(PointsCount));
//	mainForm->LogToFile("gain = " + IntToStr(Gain_Val));
//	mainForm->LogToFile("roll off = " + IntToStr(Rolloff));
}
//---------------------------------------------------------------------------

void Dnc_cmdClass::GetDataFromIni()
{
	mainForm->LogToFile("Dnc_cmdClass::GetDataFromIni");
	AmpIndex = OscTable[6].index;
	AmpOffset = OscTable[6].offset;

}

//---------------------------------------------------------------------------

void Dnc_cmdClass::CalculateParams()
{
	mainForm->LogToFile("Dnc_cmdClass::CalculateParams");
	//frequencies
	From = From_Val;
	To = To_Val;
	Use = Use_Val;

	//time constant
	double AA = 500 * 25 * PointsCount_Val;
	double BB = TimeCnt_Val * PointsCount_Val * 1000000;
	double CC = BB - AA;
	TimeConstant = (int)(CC / (25 * 1024));

	//step
	int tmp = To_Val - From_Val;
	int DivFromTo = abs(tmp);
	Step = DivFromTo/PointsCount_Val;

	//reference
//	Reference = SetPoint_Val;

	int percent = mainForm->myDynamicCurvePanelForm->SetPoint_Val; //set point value in precentage
	double reference =  mainForm->myDynamicCurvePanelForm->MaxPointofUse; //value of use
//	mainForm->LogToFile("max reference = " + FloatToStr(reference));
//	mainForm->LogToFile("percent = " + IntToStr(percent));
	reference = (percent/(double)100) * reference;
//	mainForm->LogToFile("reference = " + FloatToStr(reference));
	Reference = (reference - AmpOffset)/(double)AmpIndex; //convert to pure data
//	mainForm->LogToFile("Ref = " + FloatToStr(Reference));

	//drive
	Drive = Drive_Val;

	//point count
	Point = PointsCount;
//	mainForm->LogToFile("PointsCount = " + IntToStr(PointsCount));

	//gain
	Gain = Gain_Val;

	//roll off
	RollOff = Rolloff;
}
//---------------------------------------------------------------------------

void Dnc_cmdClass::StartDncProcess(bool start)
{
	mainForm->LogToFile("Dnc_cmdClass::StartDncProcess");
	GetDataFromUi();
	GetDataFromIni();
	CalculateParams();

	mainForm->myTcpThread->PacketSize = (int)Point;
	mainForm->myTcpThread->TcpMode = 1;

//	mainForm->LogToFile("From freq(Hz) to btisk = " + IntToStr(From));
//	mainForm->LogToFile("step freq(Hz) to btisk = " + IntToStr(Step));
//	mainForm->LogToFile("use freq(Hz) to btisk = " + IntToStr(Use));
//	mainForm->LogToFile("drive voltage(mV) to btisk = " + IntToStr(Drive));
//	mainForm->LogToFile("sweep points val to btisk = " + IntToStr(Point));
//	mainForm->LogToFile("delay(ms) to btisk = " + FloatToStr(TimeConstant));
//	mainForm->LogToFile("gain to btisk = " + IntToStr(Gain));
//	mainForm->LogToFile("roll off to btisk = " + IntToStr(RollOff));
//	mainForm->LogToFile("reference to btisk = " + IntToStr(Reference));


	mutex->Acquire();
	if(mainForm->myDynamicCurvePanelForm->contact && !mainForm->myApproachPanelForm->fast_checkbox->Checked){
		mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->DncPacket(From,Step,Use,0,Point,Gain,TimeConstant,RollOff,start,Reference));
		mainForm->myUdpThread->SetSendDataTrue();
//		TThread::Synchronize(mainForm->myUdpThread,SendDncPacket);
	}
	else{
		mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->DncPacket(From,Step,Use,Drive,Point,Gain,TimeConstant,RollOff,start,Reference));
		mainForm->myUdpThread->SetSendDataTrue();
//		TThread::Synchronize(mainForm->myUdpThread,SendDncPacket);
	}

	mutex->Release();
}
//---------------------------------------------------------------------------

void __fastcall Dnc_cmdClass::SendDncPacket()
{
	mainForm->LogToFile("Dnc_cmdClass::SendDncPacket");
	mainForm->myUdpThread->SendBytes();
}
//---------------------------------------------------------------------------



