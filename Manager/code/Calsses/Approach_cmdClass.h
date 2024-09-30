//---------------------------------------------------------------------------
#ifndef Approach_cmdClassH
#define Approach_cmdClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Math.hpp>
#include <IniFiles.hpp>
#include <System.SyncObjs.hpp>

#include "UdpDataSendClass.h"
//---------------------------------------------------------------------------

class Approach_cmdClass
{
private:
	TMutex *mutex;
protected:
public:
	__fastcall Approach_cmdClass();

	void InitClass();
	void ConfigClass();
	void CreateClassObjects();

	void ApproachData(int mode, int status, bool far_near, bool start, int count);

	void __fastcall SendApprochPacket();

	DynamicArray<Byte> ScanPacket(int Resolation, int RES_CONT, int Delay, int StepSizeX, int StepSizeY, int StartScanX, int StartScanY, unsigned char Start, unsigned char direction, int StartScanXN, int StartScanYN,  unsigned char overscan_, int flyDistance);



	int StatusFarNear;
	bool StartApproch;
	bool FarNear;
	int CountFarNear;
	int ModeTest;

	int statefast;
	int speedfast;
	int stateprecise;
	int speedprecise;
	int stateretract;
	int speedretract;
	double biascalib;
	double biascalib_offset;

	double AmpIndex;
	double AmpOffset;

	double TbIndex;
	double TbOffset;

	int AppMode;
	double Refrence;
	double KI_APP_NonContact;
	double KI_APP_Contact;
	double KI_APP;
	double KP;
	double KD;
	double Bias;
	double Piezo;
	int Num_Stepper;
	double KI_FeedBack_Contact;
	double KI_FeedBack_NonContact;
	double KI_FeedBack;
	int Speed;
	int Micro;



	double Ref1;
    int Ref;

	UdpDataSendClass* myUdpDataSendClass;
};
#endif
