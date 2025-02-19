//---------------------------------------------------------------------------

#ifndef Dnc_cmdClassH
#define Dnc_cmdClassH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Classes.hpp>
#include <System.Math.hpp>
#include <System.SyncObjs.hpp>

#include "UdpDataSendClass.h"
//---------------------------------------------------------------------------
class Dnc_cmdClass
{
private:
	TMutex *mutex;
	void __fastcall SendDncPacket();
protected:
public:
	__fastcall Dnc_cmdClass();
	void ConfigCalss();
	void InitClass();
	void CreateClassObjects();
	void GetDataFromUi();
	void GetDataFromIni();
	void CalculateParams();
	void StartDncProcess(bool start);

	UdpDataSendClass* myUdpDataSendClass;

	int From_Val;
	int To_Val;
	int Use_Val;
	int Drive_Val;
	int PointsCount_Val;
	int SetPoint_Val;
	double TimeCnt_Val;
	int PointsCount;
	int Gain_Val;
	int Rolloff;

	double AmpIndex;
	double AmpOffset;

	int From;
	int To;
	int Use;
	int TimeConstant;
	int Step;
	int Reference;
	int Drive;
	int Point;
	int Gain;
	int RollOff;
};
#endif
