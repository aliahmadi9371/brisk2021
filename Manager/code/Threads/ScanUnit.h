//---------------------------------------------------------------------------

#ifndef ScanUnitH
#define ScanUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Math.hpp>

#include "CoordinateClass.h"
#include "ScanFileCreator.h"
#include "ipwftp.h"
//---------------------------------------------------------------------------
class ScanThread : public TThread
{
private:
	//Events Callbacks
	void __fastcall FtpConnectionStatusEvent(TObject* Sender, TipwFTPConnectionStatusEventParams *e);
	void __fastcall FtpErrorEvent(TObject* Sender, TipwFTPErrorEventParams *e);
	void __fastcall FtpStartTransferEvent(TObject* Sender, TipwFTPStartTransferEventParams *e);
	void __fastcall FtpTransferEvent(TObject* Sender, TipwFTPTransferEventParams *e);
	void __fastcall FtpEndTransferEvent(TObject* Sender, TipwFTPEndTransferEventParams *e);
	void __fastcall CheckTimerEvent(TObject *Sender);

	//Variables
	double Resolution;
	double MaxRange;
	double Range;
	double OverScan;
	double Angle;
	double Center[2];
	bool ThreadStarted;
	bool ConnectedToHost;
	TipwFTP *ipwFTP;

	int* myCenter[2]; //from -50 to +50
	int  myAngle; // degree
	int  myRange; //0 to 100
	int  myResolution; //64, 128, 256, 512, 1024, 2048
	int  myOverScan; // from 0 to 1

	UnicodeString RemotAddressX;
	UnicodeString RemotAddressY;
	UnicodeString RemoteUsrName;
	UnicodeString RemotePasswd;
	UnicodeString RemoteIp;

	UnicodeString LocalFileX;
	UnicodeString LocalFileY;


protected:
	void __fastcall Execute();
public:
	__fastcall ScanThread(bool CreateSuspended);

	//Methods
	void ConfigCalss();
	void InitClass();
	void CreateClassObjects();
	void FtpUploaderSetting(UnicodeString IP,UnicodeString UserName,UnicodeString PassWord);
	void GetScanInfoFromUi();
	void Calibration(bool calc);
	void GetFtpInfo();
	void FtpLogin();
	void FtpLogOff();
	void FtpUploader(UnicodeString RemoteFileName, UnicodeString LocalFileName);
	void FtpDownloader();


	TTimer* checkTimer;
	bool Checker;
    int count;

	CoordinateClass* myCoordinateClass;
	ScanFileCreator* myScanFileCreator;
	//Setter Functions
	void SetReolution(double myValue){
		Resolution = myValue;
	}
	void SetMaxRange(double myValue){
		MaxRange = myValue;
	}
	void SetRange(double myValue){
		Range = myValue;
	}
	void SetOver_Scan(double myValue){
		OverScan = myValue;
	}
	void SetAngle(double myValue){
		Angle = myValue;
	}
	void SetThreadStarted(bool myValue){
		ThreadStarted = myValue;
	}
	void SetConnectedToHost(bool myValue){
		ConnectedToHost = myValue;
	}
	//Getter Functions
	double GetResolution(){
		return Resolution;
	}
	double GetMaxRange(){
		return MaxRange;
	}
	double GetRange(){
		return Range;
	}
	double GetOver_Scan(){
		return OverScan;
	}
	double GetAngle(){
		return Resolution;
	}
	bool SetThreadStarted(){
		return ThreadStarted;
	}
};
//---------------------------------------------------------------------------
#endif
