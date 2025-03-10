//---------------------------------------------------------------------------
#ifndef Litho_cmdClassH
#define Litho_cmdClassH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Classes.hpp>
#include "UdpDataSendClass.h"
#include "CoordinateClass.h"
#include "LithoFileCreator.h"
#include "LitoFileCreatorUnit.h"
#include "ipwftp.h"
#include "TcpDataSendClass.h"

//---------------------------------------------------------------------------
class Litho_cmdClass
{
private:
    //Events Callbacks
//	void __fastcall FtpConnectionStatusEvent(TObject* Sender, TipwFTPConnectionStatusEventParams *e);
//	void __fastcall FtpErrorEvent(TObject* Sender, TipwFTPErrorEventParams *e);
//	void __fastcall FtpStartTransferEvent(TObject* Sender, TipwFTPStartTransferEventParams *e);
//	void __fastcall FtpTransferEvent(TObject* Sender, TipwFTPTransferEventParams *e);
//	void __fastcall FtpEndTransferEvent(TObject* Sender, TipwFTPEndTransferEventParams *e);
	void __fastcall CheckTimerEvent(TObject *Sender);

//	void FtpLogin();
//	void FtpLogOff();
//	void FtpUploader(UnicodeString RemoteFileName, UnicodeString LocalFileName);
//	void FtpDownloader();
//	void FtpUploaderSetting(UnicodeString IP,UnicodeString UserName,UnicodeString PassWord);
	void GetFtpInfo();


//	TipwFTP *ipwFTP;
	TMutex *mutex;
protected:
public:
	__fastcall Litho_cmdClass();

	void InitClass();
	void CreateClassObjects();
	void ConfigCalss();
	void SendLithoPacket();

	void LithoProc(int scan_resolution,
				   int scan_speed,
				   int scan_overscan,
				   double scan_x_center,
				   double scan_y_center,
				   double scan_Xrange,
				   double scan_Yrange,
				   int litho_delay,
				   bool litho_startstop,
				   int Changer
				  );

	TTimer* checkTimer;
	UdpDataSendClass* myUdpDataSendClass;
	CoordinateClass* myCoordinateClass;
	LithoFileCreator* myLithoFileCreator;
	TcpDataSendClass* myTcpDataSendClass;




	int my_scan_resolution;
	int my_scan_speed;
	int my_scan_delay;
	int my_scan_overscan;
	double my_overscan;
	int my_overscan_count;
	double my_center[2];
	int my_scan_x_start;
	int my_scan_y_start;
	int my_scan_x_step;
	int my_scan_y_step;
	double my_scan_Xrange;
	double my_scan_Yrange;
	int my_litho_delay;
	bool my_litho_startstop;

	UnicodeString RemoteFileX;
	UnicodeString RemoteFileY;
	UnicodeString RemoteFileV;

	UnicodeString RemotePath;
	UnicodeString RemoteUsrName;
	UnicodeString RemotePasswd;
	UnicodeString RemoteIp;

	UnicodeString LocalFileX;
	UnicodeString LocalFileY;
	UnicodeString LocalFileV;


	bool ConnectedToHost;
	int uploadCounter;

	bool delay;

};
#endif
