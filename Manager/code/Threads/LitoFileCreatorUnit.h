//---------------------------------------------------------------------------

#ifndef LitoFileCreatorUnitH
#define LitoFileCreatorUnitH
//---------------------------------------------------------------------------
#include "Litho_cmdClass.h"
#include "TcpDataSendClass.h"
//---------------------------------------------------------------------------

class LithoFileCreatorThread : public TThread
{
protected:
    TMutex *mutex;
	void __fastcall Execute();
	void __fastcall SendPacket();

public:
	__fastcall LithoFileCreatorThread(bool CreateSuspended);

	bool litho_file;
	int Litho_Resolution;
	void CreateVfile(int resolution);
	void CloseLithoThread();

	TRGBQuad *ptr2;
	bool litho_file2;
	void CreateVfile(int resolution, TBitmap* bitmap);
	bool progress;

	int* LithoVFile;
	int VLength;
	int LineNumber;

	TcpDataSendClass* myTcpDataSendClass;







};
//---------------------------------------------------------------------------
#endif

