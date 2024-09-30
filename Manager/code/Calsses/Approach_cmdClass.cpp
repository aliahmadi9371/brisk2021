//---------------------------------------------------------------------------
#pragma hdrstop
#include "Approach_cmdClass.h"
#pragma package(smart_init)

#include "mainUnit.h"
#include "globals.h"
//---------------------------------------------------------------------------

__fastcall Approach_cmdClass::Approach_cmdClass()
{
    InitClass();
	CreateClassObjects();
	ConfigClass();
}
//---------------------------------------------------------------------------

void Approach_cmdClass::InitClass()
{
    StatusFarNear = 0;
	StartApproch = false;
	FarNear = false;
	CountFarNear = 0;
	ModeTest = 0;

	Ref1 = 0;


	myUdpDataSendClass = NULL;
	mutex = NULL;
}
//---------------------------------------------------------------------------

void Approach_cmdClass::ConfigClass()
{
	mainForm->LogToFile("Approach_cmdClass::ConfigClass");

	Refrence = ApproachTable.Apr_Refrerence_Val;
	KI_APP_Contact = ApproachTable.Apr_Ki_Val_Contact;
	KI_APP_NonContact = ApproachTable.Apr_Ki_Val_NonContact;
	KP = ApproachTable.Apr_Kp_Val;
	KD = ApproachTable.Apr_Kd_Val;
	Bias = ApproachTable.Apr_Bias_Val;
	Piezo = ApproachTable.Apr_ZPosition_Val;
	Num_Stepper = 0 ;
	KI_FeedBack_Contact = ApproachTable.Apr_KiFeedbak_Val_Contact;
	KI_FeedBack_NonContact = ApproachTable.Apr_KiFeedbak_Val_NonContact;

	stateprecise = ApproachTable.Apr_SteperStepMicro_Val_Precise;
	speedprecise = ApproachTable.Apr_SteperSpeed_Val_Precise;

	statefast = ApproachTable.Apr_StepperStepMicro_Val_Fast;
	speedfast = ApproachTable.Apr_StepperSpeed_Val_Fast;

	stateretract = RetractTable.Ret_StepperStepMicro_Val;
	speedretract = RetractTable.Ret_StepperSpeed_Val;

	biascalib = ApproachTable.Apr_BiasIndex_Val; //bias
	biascalib_offset = ApproachTable.Apr_BiasOffset_Val; //bias

	TbIndex = OscTable[0].index;
	TbOffset = OscTable[0].offset;

	AmpIndex = OscTable[6].index;
	AmpOffset = OscTable[0].offset;

}
//---------------------------------------------------------------------------

void Approach_cmdClass::CreateClassObjects()
{
	if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}

	if(!mutex){
		mutex = new TMutex(false);
	}
}
//---------------------------------------------------------------------------

void Approach_cmdClass::ApproachData(int mode, int status, bool far_near, bool start,
									 int count)
{
	mainForm->LogToFile("Approach_cmdClass::ApproachData");
	ConfigClass();

	Bias = mainForm->myApproachPanelForm->BiasApp;
	Num_Stepper = mainForm->myApproachPanelForm->StpApp;
	KI_APP = mainForm->myApproachPanelForm->KiApp;
	KI_FeedBack = mainForm->myApproachPanelForm->KiFeedBack;
	KP = mainForm->myApproachPanelForm->KpApp;
	KD = mainForm->myApproachPanelForm->KdApp;

	StatusFarNear = status;
	StartApproch = start;
	FarNear = far_near;


	int StartState = 0;
	int state = 0;
	int speed = 0;
//	mainForm->LogToFile("mode  = " + IntToStr(mode));
	switch (mode)
	{
		case 0:{
			speed = speedfast;
			state = statefast;
			break;
		}
		case 1:{
			speed = speedprecise;
			state = stateprecise;
		}
			break;
		case 2:{
			speed = speedretract;
			state = stateretract;
			break;
		}
	}

//	mainForm->LogToFile("speed _ SteperSpeed: " + IntToStr(speed));
//	mainForm->LogToFile("state _ StepperStepMicro: " + IntToStr(state));

	int CountStep = 0;
	if (FarNear == true)
		StartState += 131072;
	else
		StartState += 0;
	if (StatusFarNear == 1)
		StartState += 65536;
	else
		StartState += 0;

	switch (state)
	{
		case 0:{ StartState += 0; break;  }
		case 1:{ StartState += 256; break;}
		case 2:{ StartState += 512; break;}
		case 3:{ StartState += 768; break;}
	}

	if (StartApproch == true)
		StartState += 1;
	else
		StartState += 0;

	if (FarNear == true)
		CountStep = count;
	else
	{
//			if (ModeTest == 1)
//			{
//				CountStep = 1;
//			}
//		if (mode == 0)
//			CountStep = 1;
//		else
			CountStep = Num_Stepper;
	}



	int AmplitueDiffThreshold = 0;
//		if (UDPInterface.Data.DataUDP.AppMode == 1)
//		{
//
//
//		}
//		else
//		{


	//contact approach: 1,5,7
	//non-contact approach 2,3,4,6

	switch (mainForm->AppMode){
		case 1:{
			Refrence = mainForm->myApproachPanelForm->RefrenceApp;
			Refrence = Refrence / (double)1000; //Refrence or V from mV
			Refrence = (Refrence - TbOffset)/(double)TbIndex; //convert to pure data
			Ref = UdpTbRef - Refrence; //UdpTbRef realtime data
//			mainForm->LogToFile("Contact : UdpTbRef = " + IntToStr((int)UdpTbRef) + " , Refrence = " + IntToStr((int)Refrence));
//			mainForm->LogToFile("Refrence = " + FloatToStr(Refrence) + " , UdpTbRef = " + IntToStr(UdpTbRef) + " , Ref = " + IntToStr(Ref));
			break;
		}
		case 2:{
			int percent = mainForm->myDynamicCurvePanelForm->SetPoint_Val; //set point value in precentage
			double reference =  mainForm->myDynamicCurvePanelForm->MaxPointofUse; //value of use
			reference = (percent/(double)100) * reference;
			int Reference = (reference - AmpOffset)/(double)AmpIndex; //convert to pure data
			Ref = Reference;
//			mainForm->LogToFile("NonContact : UdpTbRef = " + IntToStr((int)UdpTbRef) + " , Refrence = " + IntToStr((int)Reference));
//			mainForm->LogToFile("Ref = " + FloatToStr(Ref));
			break;
		}
		case 3:{
			int percent = mainForm->myDynamicCurvePanelForm->SetPoint_Val; //set point value in precentage
			double reference =  mainForm->myDynamicCurvePanelForm->MaxPointofUse; //value of use
			reference = (percent/(double)100) * reference;
			int Reference = (reference - AmpOffset)/(double)AmpIndex; //convert to pure data
			Ref = Reference;
//			mainForm->LogToFile("NonContact : UdpTbRef = " + IntToStr((int)UdpTbRef) + " , Refrence = " + IntToStr((int)Reference));
//			mainForm->LogToFile("Ref = " + FloatToStr(Ref));
			break;
		}
		case 4:{
			int percent = mainForm->myDynamicCurvePanelForm->SetPoint_Val; //set point value in precentage
			double reference =  mainForm->myDynamicCurvePanelForm->MaxPointofUse; //value of use
			reference = (percent/(double)100) * reference;
			int Reference = (reference - AmpOffset)/(double)AmpIndex; //convert to pure data
			Ref = Reference;
//			mainForm->LogToFile("NonContact : UdpTbRef = " + IntToStr((int)UdpTbRef) + " , Refrence = " + IntToStr((int)Reference));
//			mainForm->LogToFile("Ref = " + FloatToStr(Ref));
			break;
		}
		case 5:{
			Refrence = mainForm->myApproachPanelForm->RefrenceApp;
			Refrence = Refrence / (double)1000; //Refrence ro V from mV
			Refrence = (Refrence - TbOffset)/(double)TbIndex; //convert to pure data
			Ref = UdpTbRef - Refrence; //UdpTbRef realtime data
//			mainForm->LogToFile("Force Spec : UdpTbRef = " + IntToStr((int)UdpTbRef) + " , Refrence = " + IntToStr((int)Refrence));
//			mainForm->LogToFile("Refrence = " + FloatToStr(Refrence) + " , UdpTbRef = " + IntToStr(UdpTbRef) + " , Ref = " + IntToStr(Ref));
			break;
		}
		case 6:{
			int percent = mainForm->myDynamicCurvePanelForm->SetPoint_Val; //set point value in precentage
			double reference =  mainForm->myDynamicCurvePanelForm->MaxPointofUse; //value of use
			reference = (percent/(double)100) * reference;
			int Reference = (reference - AmpOffset)/(double)AmpIndex; //convert to pure data
			Ref = Reference;
//			mainForm->LogToFile("NonContact : UdpTbRef = " + IntToStr((int)UdpTbRef) + " , Refrence = " + IntToStr((int)Reference));
//			mainForm->LogToFile("Ref = " + FloatToStr(Ref));
			break;
		}
		case 7:{
			Refrence = mainForm->myApproachPanelForm->RefrenceApp;
			Refrence = Refrence / (double)1000; //Refrence ro V from mV
			Refrence = (Refrence - TbOffset)/(double)TbIndex; //convert to pure data
			Ref = UdpTbRef - Refrence; //UdpTbRef realtime data
//			mainForm->LogToFile("Force Spec : UdpTbRef = " + IntToStr((int)UdpTbRef) + " , Refrence = " + IntToStr((int)Refrence));
//			mainForm->LogToFile("Refrence = " + FloatToStr(Refrence) + " , UdpTbRef = " + IntToStr(UdpTbRef) + " , Ref = " + IntToStr(Ref));
			break;
		}
		default:{
			break;
		}
	}



	Bias = ((double)Bias * (double)biascalib) + (double)biascalib_offset;

//	mainForm->LogToFile("Approach_cmdClass: ApproachData: Bias: " + FloatToStr(Bias));

	if(mainForm->myApproachPanelForm->fast_checkbox->Checked){
        if (mainForm->AppMode == 1 ||  mainForm->AppMode == 5 || mainForm->AppMode == 7)
		{
			AmplitueDiffThreshold = FastApproachTable.Threshold_Contact;
		}
        else if ((mainForm->AppMode == 2 || mainForm->AppMode == 3 || mainForm->AppMode == 4 || mainForm->AppMode == 6) /*||(mainForm->AppMode == 3)||(mainForm->AppMode == 4)*/)
		{
			AmplitueDiffThreshold = FastApproachTable.Threshold_NonContact;
        }
	}
	else{
		if (mainForm->AppMode == 1 ||  mainForm->AppMode == 5 || mainForm->AppMode == 7)
		{
			AmplitueDiffThreshold = KI_FeedBack_Contact;
		}
		else if ((mainForm->AppMode == 2 || mainForm->AppMode == 3 || mainForm->AppMode == 4 || mainForm->AppMode == 6) /*||(mainForm->AppMode == 3)||(mainForm->AppMode == 4)*/)
		{
			AmplitueDiffThreshold = KI_FeedBack_NonContact;
		}
	}

//	mainForm->LogToFile("Start Approache process Refrence: " + IntToHex((int)Refrence,8));
//	mainForm->LogToFile("Start Approache process KI_APP: " + IntToHex((int)KI_APP,8));
//	mainForm->LogToFile("Start Approache process KP: " + IntToHex((int)KP,8));
//	mainForm->LogToFile("Start Approache process Bias: " + IntToHex((int)Bias,8));
//	mainForm->LogToFile("Start Approache process speed: " + IntToHex((int)speed,8));
//	mainForm->LogToFile("Start Approache process Piezo: " + IntToHex((int)Piezo,8));
//	mainForm->LogToFile("Start Approache process KI_FeedBack: " + IntToHex((int)KI_FeedBack,8));
//	mainForm->LogToFile("Start Approache process CountStep: " + IntToHex((int)CountStep,8));
//	mainForm->LogToFile("Start Approache process AmplitueDiffThreshold: " + IntToHex((int)AmplitueDiffThreshold,8));
//	mainForm->LogToFile("Start Approache process StartState: " + IntToHex((int)StartState,8));

	mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->ApproachPacket((int)Ref,(int)KI_APP,(int)KP,(int)KD,(int)Bias,(int)speed, (int)Piezo, (int)KI_FeedBack, CountStep, AmplitueDiffThreshold, StartState));
	mainForm->myUdpThread->SetSendDataTrue();
	//	TThread::Synchronize(mainForm->myUdpThread,SendApprochPacket);

}
//---------------------------------------------------------------------------

void __fastcall Approach_cmdClass::SendApprochPacket()
{
	mainForm->LogToFile("Approach_cmdClass::SendApprochPacket");
	mainForm->myUdpThread->SendBytes();
}
//---------------------------------------------------------------------------

