//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#pragma hdrstop

#include "UdpDataSendClass.h"
#include "defines.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall UdpDataSendClass::UdpDataSendClass(TComponent* Owner)
{

}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::SettingPacket(unsigned char afm_mode ,unsigned char approach_mode,unsigned char power_on_off)
{

//	mainForm->LogToFile("SettingPacket : afm_mode = " + IntToStr(afm_mode));
//	mainForm->LogToFile("SettingPacket : approach_mode = " + IntToStr(approach_mode));
//	mainForm->LogToFile("SettingPacket : power_on_off = " + IntToStr(power_on_off));

//	mainForm->LogToFile("UdpDataSendClass::SettingPacket");
	DynamicArray<Byte> bytes;
	bytes.Length = 6;
	for(int i=0; i<6; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = AFM_MODE_SETIING;
	bytes[3] = afm_mode;
	bytes[4] = approach_mode;
	bytes[5] = power_on_off;


//	for(int i=0; i<6; i++)
//		mainForm->LogToFile("SettingPacket[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));


	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::ApproachPacket(int Refrence, int KI, int KP, int KD,
													int Bias, int Motor, int Piezo,
													int KIFeedBack, int Number,int ampdiff,
													int Start)
{
//	mainForm->LogToFile("UdpDataSendClass::ApproachPacket");
//	mainForm->LogToFile("ApproachPacket : Refrence = " + IntToStr(Refrence));
//	mainForm->LogToFile("ApproachPacket : KI = " + IntToStr(KI));
//	mainForm->LogToFile("ApproachPacket : KP = " + IntToStr(KP));
//	mainForm->LogToFile("ApproachPacket : KD = " + IntToStr(KD));
//	mainForm->LogToFile("ApproachPacket : Bias = " + IntToStr(Bias));
//	mainForm->LogToFile("ApproachPacket : Motor = " + IntToStr(Motor));
//	mainForm->LogToFile("ApproachPacket : Piezo = " + IntToStr(Piezo));
//	mainForm->LogToFile("ApproachPacket : KIFeedBack = " + IntToStr(KIFeedBack));
//	mainForm->LogToFile("ApproachPacket : Number = " + IntToStr(Number));
//	mainForm->LogToFile("ApproachPacket : ampdiff = " + IntToStr(ampdiff));
//	mainForm->LogToFile("ApproachPacket : Start = " + IntToStr(Start));

	DynamicArray<Byte> bytes;
	bytes.Length = 46;

	for(int i=0; i<46; i++)
		bytes[i] = 0;
	//Start Byte
	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = APPROACHE_FRAME;

	//Refrence
	//app_tb_th
	bytes[3] = (byte)((Refrence >> 24) & 0xFF);
	bytes[4] = (byte)((Refrence >> 16) & 0xFF);
	bytes[5] = (byte)((Refrence >> 8) & 0xFF);
	bytes[6] = (byte)((Refrence >> 0) & 0xFF);

	//KI-app
	//piezo_Z_app_ki
	bytes[7] = (byte)((KI >> 24) & 0xFF);
	bytes[8] = (byte)((KI >> 16) & 0xFF);
	bytes[9] = (byte)((KI >> 8) & 0xFF);
	bytes[10] = (byte)((KI >> 0) & 0xFF);

	//KP
	//piezo_Z_feddback_kp
	bytes[11] = (byte)((KP >> 24) & 0xFF);
	bytes[12] = (byte)((KP >> 16) & 0xFF);
	bytes[13] = (byte)((KP >> 8) & 0xFF);
	bytes[14] = (byte)((KP >> 0) & 0xFF);

	//KD
	//piezo_Z_feddback_kd
	bytes[15] = (byte)((KD >> 24) & 0xFF);
	bytes[16] = (byte)((KD >> 16) & 0xFF);
	bytes[17] = (byte)((KD >> 8) & 0xFF);
	bytes[18] = (byte)((KD >> 0) & 0xFF);

	//Bias
	//Bios_Data
	bytes[19] = (byte)((Bias >> 24) & 0xFF);
	bytes[20] = (byte)((Bias >> 16) & 0xFF);
	bytes[21] = (byte)((Bias >> 8) & 0xFF);
	bytes[22] = (byte)((Bias >> 0) & 0xFF);

	//Motor Speed
	//Stepper_speed
	bytes[23] = (byte)((Motor >> 24) & 0xFF);
	bytes[24] = (byte)((Motor >> 16) & 0xFF);
	bytes[25] = (byte)((Motor >> 8) & 0xFF);
	bytes[26] = (byte)((Motor >> 0) & 0xFF);

	//Piezo
	//piezo_Z_init_value
	bytes[27] = (byte)((Piezo >> 24) & 0xFF);
	bytes[28] = (byte)((Piezo >> 16) & 0xFF);
	bytes[29] = (byte)((Piezo >> 8) & 0xFF);
	bytes[30] = (byte)((Piezo >> 0) & 0xFF);

	//KIFeedBack
	//piezo_Z_feddback_ki
	bytes[31] = (byte)((KIFeedBack >> 24) & 0xFF);
	bytes[32] = (byte)((KIFeedBack >> 16) & 0xFF);
	bytes[33] = (byte)((KIFeedBack >> 8) & 0xFF);
	bytes[34] = (byte)((KIFeedBack >> 0) & 0xFF);

	//Step Number Stepper
	//Stepper_step_number
	bytes[35] = (byte)((Number >> 24) & 0xFF);
	bytes[36] = (byte)((Number >> 16) & 0xFF);
	bytes[37] = (byte)((Number >> 8) & 0xFF);
	bytes[38] = (byte)((Number >> 0) & 0xFF);

	//Start
	bytes[39] = (byte)((Start >> 16) & 0xFF); //far_near_act
	bytes[40] = (byte)((Start >> 8) & 0xFF);  //app_micro_stepping
	if(mainForm->myUdpThread->FastToNormal){
		bytes[41] = 0;  //approach_start_stop
	}
	else{
		bytes[41] = (byte)((Start >> 0) & 0xFF);  //approach_start_stop
	}

	//AmpdiffThreashold
	//amp_diff_thr
	bytes[42] = (byte)((ampdiff >> 24) & 0xFF);
	bytes[43] = (byte)((ampdiff >> 16) & 0xFF);
	bytes[44] = (byte)((ampdiff >> 8) & 0xFF);
	bytes[45] = (byte)((ampdiff >> 0) & 0xFF);

//	for(int i=0; i<46; i++)
//		mainForm->LogToFile("ApproachPacket[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));

	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::ScanPacket(int Resolation, int Delay, int OverScanCount, int StartScanX, int StartScanY ,int StepVerX, int StepVerY, int flyDistance, unsigned char StartStop)
{

//	mainForm->LogToFile("UdpDataSendClass::ScanPacket");
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : Resolation = " + IntToStr(Resolation));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : Delay = " + IntToStr(Delay));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : OverScanCount = " + IntToStr(OverScanCount));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : StartScanX = " + IntToStr(StartScanX));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : StartScanY = " + IntToStr(StartScanY));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : StepVerX = " + IntToStr(StepVerX));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : StepVerY = " + IntToStr(StepVerY));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : flyDistance = " + IntToStr(flyDistance));
//	mainForm->LogToFile("UdpDataSendClass : ScanPacket : StartStop = " + IntToStr(StartStop));

	DynamicArray<Byte> bytes;
	bytes.Length = 49;
	for(int i=0; i<49; i++)
		bytes[i] = 0;
	//Start Byte
	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = SCANNING_FRAME;

	//scanning_resolution
	bytes[3] = (byte)((Resolation >> 24) & 0xFF);
	bytes[4] = (byte)((Resolation >> 16) & 0xFF);
	bytes[5] = (byte)((Resolation >> 8) & 0xFF);
	bytes[6] = (byte)((Resolation >> 0) & 0xFF);

	//scanning_delay
	bytes[10] = (byte)((Delay >> 24) & 0xFF);
	bytes[11] = (byte)((Delay >> 16) & 0xFF);
	bytes[12] = (byte)((Delay >> 8) & 0xFF);
	bytes[13] = (byte)((Delay >> 0) & 0xFF);

	//scanning_overscan_count
	bytes[14] = (byte)((OverScanCount >> 24) & 0xFF);
	bytes[15] = (byte)((OverScanCount >> 16) & 0xFF);
	bytes[16] = (byte)((OverScanCount >> 8) & 0xFF);
	bytes[17] = (byte)((OverScanCount >> 0) & 0xFF);

	//piezo_X_start_point
	bytes[22] = (byte)((StartScanX >> 24) & 0xFF);
	bytes[23] = (byte)((StartScanX >> 16) & 0xFF);
	bytes[24] = (byte)((StartScanX >> 8) & 0xFF);
	bytes[25] = (byte)((StartScanX >> 0) & 0xFF);

	//piezo_Y_start_point
	bytes[26] = (byte)((StartScanY >> 24) & 0xFF);
	bytes[27] = (byte)((StartScanY >> 16) & 0xFF);
	bytes[28] = (byte)((StartScanY >> 8) & 0xFF);
	bytes[29] = (byte)((StartScanY >> 0) & 0xFF);

	//StepVerX
	//piezo_X_start_point_step
	bytes[32] = (byte)((StepVerX >> 24) & 0xFF);
	bytes[33] = (byte)((StepVerX >> 16) & 0xFF);
	bytes[34] = (byte)((StepVerX >> 8) & 0xFF);
	bytes[35] = (byte)((StepVerX >> 0) & 0xFF);

	//StepVerY
	//piezo_Y_start_point_step
	bytes[36] = (byte)((StepVerY >> 24) & 0xFF);
	bytes[37] = (byte)((StepVerY >> 16) & 0xFF);
	bytes[38] = (byte)((StepVerY >> 8) & 0xFF);
	bytes[39] = (byte)((StepVerY >> 0) & 0xFF);

	//piezo_z_fly_offset
	bytes[40] = (byte)((flyDistance >> 24) & 0xFF);
	bytes[41] = (byte)((flyDistance >> 16) & 0xFF);
	bytes[42] = (byte)((flyDistance >> 8) & 0xFF);
	bytes[43] = (byte)((flyDistance >> 0) & 0xFF);

	//StartStop
	bytes[30] = StartStop;

	bytes[48] = 0;  //litho enable

	bytes[44] = 0;  //litho delay
	bytes[45] = 0;
	bytes[46] = 0;
	bytes[47] = 0;


//	//... dont care
//	bytes[7] = (byte)((DontCare1 >> 16) & 0xFF);
//	bytes[8] = (byte)((DontCare1 >> 8) & 0xFF);
//	bytes[9] = (byte)((DontCare1 >> 0) & 0xFF);

//	//DontCare
//	bytes[31] = direction;

//	//Bias     dont care
//	bytes[18] = (byte)((StepSizeY >> 24) & 0xFF);
//	bytes[19] = (byte)((StepSizeY >> 16) & 0xFF);
//	bytes[20] = (byte)((StepSizeY >> 8) & 0xFF);
//	bytes[21] = (byte)((StepSizeY >> 0) & 0xFF);

//	for(int i=0; i<49; i++)
//		mainForm->LogToFile("ScanPacket[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));

	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::CoarseMovePacket(unsigned char All, unsigned int Speed, unsigned int StepNum)
{
//	mainForm->LogToFile("UdpDataSendClass::CoarseMovePacket");
//	mainForm->LogToFile("CoarseMovePacket : All = " + IntToStr(All));
//	mainForm->LogToFile("CoarseMovePacket : Speed = " + IntToStr((int)Speed));
//	mainForm->LogToFile("CoarseMovePacket : StepNum = " + IntToStr((int)StepNum));

	DynamicArray<Byte> bytes;
	bytes.Length = 12;
	for(int i=0; i<12; i++)
		bytes[i] = 0;
	//Start Byte
	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = COARSE_MOVE_FRAME;

	//All
	bytes[3] = All;

	//Speed
	bytes[4] = (byte)((Speed >> 24) & 0xFF);
	bytes[5] = (byte)((Speed >> 16) & 0xFF);
	bytes[6] = (byte)((Speed >> 8) & 0xFF);
	bytes[7] = (byte)((Speed >> 0) & 0xFF);

	//Step Number
	bytes[8] = (byte)((StepNum >> 24) & 0xFF);
	bytes[9] = (byte)((StepNum >> 16) & 0xFF);
	bytes[10] = (byte)((StepNum >> 8) & 0xFF);
	bytes[11] = (byte)((StepNum >> 0) & 0xFF);

//	for(int i=0; i<12; i++)
//		mainForm->LogToFile("CoarseMovePacket[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));

	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::DncPacket(int From, int Step, int Use, int Drive, int point, int gain,
													int timeconstant, int rolloff, byte Start, int Ref)
{
//	mainForm->LogToFile("UdpDataSendClass::DncPacket");
//	mainForm->LogToFile("DncPacket : From = " + IntToStr(From));
//	mainForm->LogToFile("DncPacket : Step = " + IntToStr(Step));
//	mainForm->LogToFile("DncPacket : Use = " + IntToStr(Use));
//	mainForm->LogToFile("DncPacket : Drive = " + IntToStr(Drive));
//	mainForm->LogToFile("DncPacket : point = " + IntToStr(point));
//	mainForm->LogToFile("DncPacket : gain = " + IntToStr(gain));
//	mainForm->LogToFile("DncPacket : timeconstant = " + IntToStr(timeconstant));
//	mainForm->LogToFile("DncPacket : rolloff = " + IntToStr(rolloff));
//	mainForm->LogToFile("DncPacket : Start = " + IntToStr(Start));
//	mainForm->LogToFile("DncPacket : Ref = " + IntToStr(Ref));

	DynamicArray<Byte> bytes;
	bytes.Length = 40;
	for(int i=0; i<40; i++)
		bytes[i] = 0;
	//Start Byte
	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = DNC_FRAME;

	//From
	bytes[3] = (byte)((From >> 24) & 0xFF);
	bytes[4] = (byte)((From >> 16) & 0xFF);
	bytes[5] = (byte)((From >> 8) & 0xFF);
	bytes[6] = (byte)((From >> 0) & 0xFF);
	//Step
	bytes[7] = (byte)((Step >> 24) & 0xFF);
	bytes[8] = (byte)((Step >> 16) & 0xFF);
	bytes[9] = (byte)((Step >> 8) & 0xFF);
	bytes[10] = (byte)((Step >> 0) & 0xFF);
	//Use
	bytes[11] = (byte)((Use >> 24) & 0xFF);
	bytes[12] = (byte)((Use >> 16) & 0xFF);
	bytes[13] = (byte)((Use >> 8) & 0xFF);
	bytes[14] = (byte)((Use >> 0) & 0xFF);
	//Drive
	bytes[15] = (byte)((Drive >> 24) & 0xFF);
	bytes[16] = (byte)((Drive >> 16) & 0xFF);
	bytes[17] = (byte)((Drive >> 8) & 0xFF);
	bytes[18] = (byte)((Drive >> 0) & 0xFF);
	//Point
	bytes[19] = (byte)((point >> 24) & 0xFF);
	bytes[20] = (byte)((point >> 16) & 0xFF);
	bytes[21] = (byte)((point >> 8) & 0xFF);
	bytes[22] = (byte)((point >> 0) & 0xFF);
	//Gain
	bytes[23] = (byte)((gain >> 24) & 0xFF);
	bytes[24] = (byte)((gain >> 16) & 0xFF);
	bytes[25] = (byte)((gain >> 8) & 0xFF);
	bytes[26] = (byte)((gain >> 0) & 0xFF);
	//TimeConstant
	bytes[27] = (byte)((timeconstant >> 24) & 0xFF);
	bytes[28] = (byte)((timeconstant >> 16) & 0xFF);
	bytes[29] = (byte)((timeconstant >> 8) & 0xFF);
	bytes[30] = (byte)((timeconstant >> 0) & 0xFF);
	//RollOff
	bytes[31] = (byte)((rolloff >> 24) & 0xFF);
	bytes[32] = (byte)((rolloff >> 16) & 0xFF);
	bytes[33] = (byte)((rolloff >> 8) & 0xFF);
	bytes[34] = (byte)((rolloff >> 0) & 0xFF);
	//Start DNC
	bytes[35] = Start;

	//Refrence
	bytes[36] = (byte)((Ref >> 24) & 0xFF);
	bytes[37] = (byte)((Ref >> 16) & 0xFF);
	bytes[38] = (byte)((Ref >> 8) & 0xFF);
	bytes[39] = (byte)((Ref >> 0) & 0xFF);


//	for(int i=0; i<40; i++)
//		mainForm->LogToFile("DncPacket[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));

	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::FsPacket(int Resolution, int Delay, int XPoint, int YPoint, byte FSMode, byte Start, byte GoTo)
{
//	mainForm->LogToFile("UdpDataSendClass::FsPacket");
//	mainForm->LogToFile("FsPacket : Resolution = " + IntToStr(Resolution));
//	mainForm->LogToFile("FsPacket : Delay = " + IntToStr(Delay));
//	mainForm->LogToFile("FsPacket : XPoint = " + IntToStr(XPoint));
//	mainForm->LogToFile("FsPacket : YPoint = " + IntToStr(YPoint));
//	mainForm->LogToFile("FsPacket : FSMode = " + IntToStr(FSMode));
//	mainForm->LogToFile("FsPacket : Start = " + IntToStr(Start));
//	mainForm->LogToFile("FsPacket : GoTo = " + IntToStr(GoTo));

	DynamicArray<Byte> bytes;
	bytes.Length = 22;
	for(int i=0; i<22; i++)
		bytes[i] = 0;
	//Start Byte
	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = FORCE_SPEC_FRAME;

	//Resolution
	bytes[3] = (byte)((Resolution >> 24) & 0xFF);
	bytes[4] = (byte)((Resolution >> 16) & 0xFF);
	bytes[5] = (byte)((Resolution >> 8) & 0xFF);
	bytes[6] = (byte)((Resolution >> 0) & 0xFF);
	//Delay
	bytes[7] = (byte)((Delay >> 24) & 0xFF);
	bytes[8] = (byte)((Delay >> 16) & 0xFF);
	bytes[9] = (byte)((Delay >> 8) & 0xFF);
	bytes[10] = (byte)((Delay >> 0) & 0xFF);
	//XPoint
	bytes[11] = (byte)((XPoint >> 24) & 0xFF);
	bytes[12] = (byte)((XPoint >> 16) & 0xFF);
	bytes[13] = (byte)((XPoint >> 8) & 0xFF);
	bytes[14] = (byte)((XPoint >> 0) & 0xFF);
	//YPoint
	bytes[15] = (byte)((YPoint >> 24) & 0xFF);
	bytes[16] = (byte)((YPoint >> 16) & 0xFF);
	bytes[17] = (byte)((YPoint >> 8) & 0xFF);
	bytes[18] = (byte)((YPoint >> 0) & 0xFF);

	//FS mode
	bytes[19] = FSMode;

	//FS Start Stop
	bytes[20] = Start;

	//FS GoTo flag
	bytes[21] = GoTo;


//	for(int i=0; i<22; i++)
//		mainForm->LogToFile("Fs[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));

	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::LithoPacket(byte enable ,int Resolation, int Delay, int Litho_Delay, int OverScanCount, int StartScanX, int StartScanY ,int StepVerX, int StepVerY, unsigned char StartStop)
{

//	mainForm->LogToFile("UdpDataSendClass::LithoPacket");
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : Resolation = " + IntToStr(Resolation));
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : Delay = " + IntToStr(Delay));
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : Litho_Delay = " + IntToStr(Litho_Delay));
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : OverScanCount = " + IntToStr(OverScanCount));
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : StartScanX = " + IntToStr(StartScanX));
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : StartScanY = " + IntToStr(StartScanY));
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : StepVerX = " + IntToStr(StepVerX));
//	mainForm->LogToFile("UdpDataSendClass::LithoPacket : StepVerY = " + IntToStr(StepVerY));


	DynamicArray<Byte> bytes;
	bytes.Length = 49;
	for(int i=0; i<49; i++)
		bytes[i] = 0;
	//Start Byte
	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = LITHO_FRAME;

	//scanning_resolution
	bytes[3] = (byte)((Resolation >> 24) & 0xFF);
	bytes[4] = (byte)((Resolation >> 16) & 0xFF);
	bytes[5] = (byte)((Resolation >> 8) & 0xFF);
	bytes[6] = (byte)((Resolation >> 0) & 0xFF);

	//scanning_delay
	bytes[10] = (byte)((Delay >> 24) & 0xFF);
	bytes[11] = (byte)((Delay >> 16) & 0xFF);
	bytes[12] = (byte)((Delay >> 8) & 0xFF);
	bytes[13] = (byte)((Delay >> 0) & 0xFF);

	//scanning_overscan_count
	bytes[14] = (byte)((OverScanCount >> 24) & 0xFF);
	bytes[15] = (byte)((OverScanCount >> 16) & 0xFF);
	bytes[16] = (byte)((OverScanCount >> 8) & 0xFF);
	bytes[17] = (byte)((OverScanCount >> 0) & 0xFF);

	//piezo_X_start_point
	bytes[22] = (byte)((StartScanX >> 24) & 0xFF);
	bytes[23] = (byte)((StartScanX >> 16) & 0xFF);
	bytes[24] = (byte)((StartScanX >> 8) & 0xFF);
	bytes[25] = (byte)((StartScanX >> 0) & 0xFF);

	//piezo_Y_start_point
	bytes[26] = (byte)((StartScanY >> 24) & 0xFF);
	bytes[27] = (byte)((StartScanY >> 16) & 0xFF);
	bytes[28] = (byte)((StartScanY >> 8) & 0xFF);
	bytes[29] = (byte)((StartScanY >> 0) & 0xFF);

	//StepVerX
	//piezo_X_start_point_step
	bytes[32] = (byte)((StepVerX >> 24) & 0xFF);
	bytes[33] = (byte)((StepVerX >> 16) & 0xFF);
	bytes[34] = (byte)((StepVerX >> 8) & 0xFF);
	bytes[35] = (byte)((StepVerX >> 0) & 0xFF);

	//StepVerY
	//piezo_Y_start_point_step
	bytes[36] = (byte)((StepVerY >> 24) & 0xFF);
	bytes[37] = (byte)((StepVerY >> 16) & 0xFF);
	bytes[38] = (byte)((StepVerY >> 8) & 0xFF);
	bytes[39] = (byte)((StepVerY >> 0) & 0xFF);

	//litho_delay
	bytes[44] = (byte)((Litho_Delay >> 24) & 0xFF);
	bytes[45] = (byte)((Litho_Delay >> 16) & 0xFF);
	bytes[46] = (byte)((Litho_Delay >> 8) & 0xFF);
	bytes[47] = (byte)((Litho_Delay >> 0) & 0xFF);


	//StartStop
	bytes[30] = StartStop;

	bytes[48] = enable;  //litho enable

//	for(int i=0; i<49; i++)
//		mainForm->LogToFile("LithoPacket[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));

	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> UdpDataSendClass::KpfmPacket(int Frequency, int DriveVoltage, byte LIA1OnOff, int LIA1, int Ki, int Kp, int Kd, int Th, int BiasOnOff)
{
//	mainForm->LogToFile("UdpDataSendClass::KpfmPacket");
	DynamicArray<Byte> bytes;
	bytes.Length = 33;
	for(int i=0; i<33; i++)
		bytes[i] = 0;
	//Start Byte
	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = KPFM_FRAME;

	//KPFM frequency
	bytes[3] = (byte)((Frequency >> 24) & 0xFF);
	bytes[4] = (byte)((Frequency >> 16) & 0xFF);
	bytes[5] = (byte)((Frequency >> 8) & 0xFF);
	bytes[6] = (byte)((Frequency >> 0) & 0xFF);

	//drive voltage
	bytes[7] = (byte)((DriveVoltage >> 24) & 0xFF);
	bytes[8] = (byte)((DriveVoltage >> 16) & 0xFF);
	bytes[9] = (byte)((DriveVoltage >> 8) & 0xFF);
	bytes[10] = (byte)((DriveVoltage >> 0) & 0xFF);

	// KPFM optimal phase LIA1 On/Off
	bytes[11] = LIA1OnOff;

	// KPFM_optimal_phase_LIA_1_value
	bytes[12] = (byte)((LIA1 >> 24) & 0xFF);
	bytes[13] = (byte)((LIA1 >> 16) & 0xFF);
	bytes[14] = (byte)((LIA1 >> 8) & 0xFF);
	bytes[15] = (byte)((LIA1 >> 0) & 0xFF);

	//bias ki
	bytes[16] = (byte)((Ki >> 24) & 0xFF);
	bytes[17] = (byte)((Ki >> 16) & 0xFF);
	bytes[18] = (byte)((Ki >> 8) & 0xFF);
	bytes[19] = (byte)((Ki >> 0) & 0xFF);

	//bias kp
	bytes[20] = (byte)((Kp >> 24) & 0xFF);
	bytes[21] = (byte)((Kp >> 16) & 0xFF);
	bytes[22] = (byte)((Kp >> 8) & 0xFF);
	bytes[23] = (byte)((Kp >> 0) & 0xFF);

	//bias kd
	bytes[24] = (byte)((Kd >> 24) & 0xFF);
	bytes[25] = (byte)((Kd >> 16) & 0xFF);
	bytes[26] = (byte)((Kd >> 8) & 0xFF);
	bytes[27] = (byte)((Kd >> 0) & 0xFF);

	//bias th
	bytes[28] = (byte)((Th >> 24) & 0xFF);
	bytes[29] = (byte)((Th >> 16) & 0xFF);
	bytes[30] = (byte)((Th >> 8) & 0xFF);
	bytes[31] = (byte)((Th >> 0) & 0xFF);

	//KPFM_bias_feedback_on_off
	bytes[32] = BiasOnOff;

//	for(int i=0; i<33; i++)
//		mainForm->LogToFile("KpfmPacket[" + IntToStr(i) + "] = " + IntToHex((int)bytes[i],2));

	return bytes;
}
//---------------------------------------------------------------------------
