//---------------------------------------------------------------------------

#ifndef ForceSpce_cmdClassH
#define ForceSpce_cmdClassH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Classes.hpp>
#include "TcpDataSendClass.h"
#include "UdpDataSendClass.h"
#include <fstream>
#include "ipwftp.h"
//---------------------------------------------------------------------------
class Fs_cmdClass
{
private:
	void __fastcall SendFsPacket();

//	void __fastcall FtpConnectionStatusEvent(TObject* Sender, TipwFTPConnectionStatusEventParams *e);
//	void __fastcall FtpErrorEvent(TObject* Sender, TipwFTPErrorEventParams *e);
//	void __fastcall FtpStartTransferEvent(TObject* Sender, TipwFTPStartTransferEventParams *e);
//	void __fastcall FtpTransferEvent(TObject* Sender, TipwFTPTransferEventParams *e);
//	void __fastcall FtpEndTransferEvent(TObject* Sender, TipwFTPEndTransferEventParams *e);
//	void __fastcall checkTimerUpLoaderEvent(TObject *Sender);
//	void __fastcall checkTimerDnloaderEvent(TObject *Sender);
	void __fastcall CheckTimerEvent(TObject *Sender);

	TMutex *mutex;
protected:
public:
	__fastcall Fs_cmdClass();
	void ConfigCalss();
	void InitClass();
	void CreateClassObjects();
	void GetDataFromUi();
	void GetDataFromIni();
	void CalculateParams();
	void StartFsProcess(bool start, double startx, double starty, int resolution, int delay, int mode, int GOTO, int z1, int z2, int u1, int u2, int currentZ, int currentU);
	void CreateFsFiles(int resolution, int delay, int mode, int dz1, int dz2, int u1, int u2, int currentZ, int currentU);
	bool UploadFilesToBrisk();
	void Start(bool start);
	void SendForceCommand();
    void SendGotoCmdStart();

	UdpDataSendClass* myUdpDataSendClass;
	TcpDataSendClass* myTcpDataSendClass;

	void CreateZPoints(int dz1, int dz2, int resolution, int currentZ, int mode);
	void CreateUPoints(int u1, int u2, int resolution, int currentU, int mode);

//	TipwFTP *ipwFTP;
//	TTimer* checkTimerUpLoader;
//	TTimer* checkTimerDnLoader;
	TTimer* CheckTimer;
	void GetFtpInfo();
//	void FtpLogin();
//	void FtpLogOff();
//	void FtpUploader(UnicodeString RemoteFileName, UnicodeString LocalFileName);
//	void FtpDownloader(UnicodeString RemoteFileName, UnicodeString LocalFileName);
//	void FtpUploaderSetting(UnicodeString IP,UnicodeString UserName,UnicodeString PassWord);

	void SendFsCmdStart();
	void SendFsCmdSotp();
	void __fastcall OffFs();




	void __fastcall StartDownloadFiles();

	bool ConnectedToHost;

	UnicodeString RemoteFileZ;
	UnicodeString RemoteFileU;
	UnicodeString RemotePath;
	UnicodeString RemoteUsrName;
	UnicodeString RemotePasswd;
	UnicodeString RemoteIp;
	UnicodeString LocalFileZ;
	UnicodeString LocalFileU;


	UnicodeString RemoteFileTopo_Fw;
	UnicodeString RemoteFileTb_Fw;
	UnicodeString RemoteFileLr_Fw;
	UnicodeString RemoteFileAmp_Fw;
	UnicodeString RemoteFilePhase_Fw;
	UnicodeString RemoteFileCmAfm_Fw;

	UnicodeString LocalFileTopo_Fw;
	UnicodeString LocalFileTb_Fw;
	UnicodeString LocalFileLr_Fw;
	UnicodeString LocalFileAmp_Fw;
	UnicodeString LocalFilePhase_Fw;
	UnicodeString LocalFileCmAfm_Fw;


	UnicodeString RemoteFileTopo_Bw;
	UnicodeString RemoteFileTb_Bw;
	UnicodeString RemoteFileLr_Bw;
	UnicodeString RemoteFileAmp_Bw;
	UnicodeString RemoteFilePhase_Bw;
	UnicodeString RemoteFileCmAfm_Bw;

	UnicodeString LocalFileTopo_Bw;
	UnicodeString LocalFileTb_Bw;
	UnicodeString LocalFileLr_Bw;
	UnicodeString LocalFileAmp_Bw;
	UnicodeString LocalFilePhase_Bw;
	UnicodeString LocalFileCmAfm_Bw;

	UnicodeString SaveDirection;



	int UpCount;
	bool UpLoad;
	int DnCount;
	bool DnLoad;

	int* zpoints;
	int* upoints;

	int FsXStart;
	int FsYStart;
	int FsResolution;
	int FsDelay;
	int FsMode;
	int FsGoto;

	bool justSet;
	bool justGo;

	int tmpSeries;
	int tmpValue;

	bool delay;

	int ZLength;
    int ULength;
};
#endif
