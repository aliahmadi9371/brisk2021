//---------------------------------------------------------------------------

#ifndef Kpfm_cmdClassH
#define Kpfm_cmdClassH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Classes.hpp>
#include "UdpDataSendClass.h"
//---------------------------------------------------------------------------
class Kpfm_cmdClass
{
private:


protected:
public:
	__fastcall Kpfm_cmdClass();
	void SendKpfm(int Frequency, int DriveVoltage, byte LIA1OnOff, int LIA1, int Ki, int Kp, int Kd, int Th, int BiasOnOff);
	void CreateObjects();
	void InitValues();
	void ConfigClass();

	UdpDataSendClass* myUdpDataSendClass;
	TMutex *mutex;
};
#endif
