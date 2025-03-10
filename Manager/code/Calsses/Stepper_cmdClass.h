//---------------------------------------------------------------------------

#ifndef Stepper_cmdClassH
#define Stepper_cmdClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Math.hpp>
#include <IniFiles.hpp>
#include <System.SyncObjs.hpp>

#include "UdpDataSendClass.h"
//---------------------------------------------------------------------------
class Stepper_cmdClass
{
protected:
private:
	TMutex *mutex;
	void __fastcall SendCoarseMovePacket();
public:
	__fastcall Stepper_cmdClass();

	void InitClass();
	void CreateClassObjects();
	void ConfigClass();

	void StepperALL(byte StateM, bool Shift);
	void StepperOFF(byte StateM, bool Shift);
	void StepperA(byte StateM, bool Shift);
	void StepperB(byte StateM, bool Shift);
	void StepperC(byte StateM, bool Shift);
	void StepperSide(byte StateM, int StatusMove, int Stop, bool Shift);





	UdpDataSendClass* myUdpDataSendClass;
};
//---------------------------------------------------------------------------
#endif
