//---------------------------------------------------------------------------

#ifndef UdpDataSendClassH
#define UdpDataSendClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class UdpDataSendClass
{
private:	// User declarations
public:		// User declarations
	__fastcall UdpDataSendClass(TComponent* Owner);
	DynamicArray<Byte> SettingPacket(unsigned char afm_mode ,unsigned char approach_mode,unsigned char power_on_off);
	DynamicArray<Byte> ApproachPacket(int Refrence, int KI, int KP, int KD, int Bias, int Motor, int Piezo, int KIFeedBack, int Number,int ampdiff, int Start);
	DynamicArray<Byte> ScanPacket(int Resolation, int Delay, int OverScanCount, int StartScanX, int StartScanY ,int StepVerX, int StepVerY, int flyDistance, unsigned char StartStop);
	DynamicArray<Byte> LithoPacket(byte enable ,int Resolation, int Delay, int Litho_Delay, int OverScanCount, int StartScanX, int StartScanY ,int StepVerX, int StepVerY, unsigned char StartStop);
	DynamicArray<Byte> CoarseMovePacket(unsigned char All, unsigned int Speed, unsigned int StepNum);
	DynamicArray<Byte> DncPacket(int From, int Step, int Use, int Drive, int point, int gain, int timeconstant, int rolloff, byte Start, int Ref);
	DynamicArray<Byte> FsPacket(int Resolution, int Delay, int XPoint, int YPoint, byte FSMode, byte Start, byte GoTo);
	DynamicArray<Byte> KpfmPacket(int Frequency, int DriveVoltage, byte LIA1OnOff, int LIA1, int Ki, int Kp, int Kd, int Th, int BiasOnOff);
};
#endif
