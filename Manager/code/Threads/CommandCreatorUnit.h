//---------------------------------------------------------------------------

#ifndef CommandCreatorUnitH
#define CommandCreatorUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IniFiles.hpp>
#include <System.SyncObjs.hpp>

#include "Approach_cmdClass.h"
#include "Scan_cmdClass.h"
#include "Stepper_cmdClass.h"

#include "UdpDataSendClass.h"
#include "Dnc_cmdClass.h"

#include "ForceSpce_cmdClass.h"
#include "CmdQueue.h"
#include "Litho_cmdClass.h"
#include "Kpfm_cmdClass.h"
//---------------------------------------------------------------------------
class CommandCreatorThread : public TThread
{
private:

protected:
	TMutex *mutex;
	void __fastcall Execute();
	void __fastcall SendPacket();
public:
	__fastcall CommandCreatorThread(bool CreateSuspended);




	void ConfigThread();
	void CreateObjects();
	void StartScanClick(/*bool start, bool set, int Changer*/);
	void StartApprochClick(int mode, bool start, bool set, int StatusFarNear, bool FarNear,int CountFarNear);
	void StartStageClick(byte StateM, int StatusMove, int Stop, bool Shift);
	void StartRetractClick(int Mode, byte StateM, bool Shift);
	void StartRetDownUpClick(int Num, int Status, bool DownUp);
	void StartDncClick(bool start);
	void StartLitho(int scan_resolution, int scan_speed, int scan_overscan, double scan_x_center, double scan_y_center, double scan_Xrange, double scan_Yrange, int litho_delay, bool litho_startstop, int LastLithoChanger);

	void StartStopFsClick(/*bool start, double startx, double starty, int resolution, int delay, int mode, int GOTO, int dz1, int dz2, int u1, int u2, int currentZ, int currentU*/);
	void SendKpfm(int Frequency, int DriveVoltage, byte LIA1OnOff, int LIA1, int Ki, int Kp, int Kd, int Th, int BiasOnOff);

	int getTcpPacketLine(int myMode);
	int RetractCount(int Num);
	void Approacching();


	bool thread_started;



	Scan_cmdClass* myScan;
	double myResolution;
	double myXRange;
	double myYRange;
	double myAngle;
	double myCenter[2];
	double myOverScan;
	double mySpeed;
    int myFlyDis;
	UnicodeString myRemoteIp;




	bool StartApproch;

	Stepper_cmdClass* myStepper;
	Dnc_cmdClass* myDnc;
	Approach_cmdClass* myApproach;
	UdpDataSendClass* myUdpDataSendClass;

	Litho_cmdClass* myLitho;

	Fs_cmdClass* myFs;
	Kpfm_cmdClass* myKpfm;

	CmdQueueClass* myCmdQueue;
	void StartProcess(int cmd);

	bool litho_file;
	int Litho_Resolution;
	bool CreateVfile(int resolution);

	TRGBQuad *ptr2;
	bool litho_file2;
	bool CreateVfile(int resolution, TBitmap* bitmap);
	bool progress;
    bool UpdateTB;

	bool litho_upload;

	bool force_file;
	bool scan_command;
};
//---------------------------------------------------------------------------
#endif
