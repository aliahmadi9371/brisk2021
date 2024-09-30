//---------------------------------------------------------------------------

#ifndef UdpUnitH
#define UdpUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//#include <Vcl.Controls.hpp>
//#include <Vcl.StdCtrls.hpp>
//#include <Vcl.Forms.hpp>
//#include <System.Generics.Collections.hpp>
//#include <System.Diagnostics.hpp>
//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//#include <string>
//#include <fstream>
#include <IniFiles.hpp>
//#include <queue>
//#include <list>
//#include <stdlib>
//#include <vector>
//#include <cstdio>
#include <IniFiles.hpp>
#include <System.SyncObjs.hpp>

#include "ipwipinfo.h"
#include "ipwudpport.h"
#include "UdpDataSendClass.h"
#include "recUnit.h"
#include "defines.h"

//using  std;
//using queue;

#include "dataCalss.h"
//---------------------------------------------------------------------------
class UdpThread : public TThread
{
__published:

private:
	void __fastcall ipwUDPDataIn(TObject *Sender, TipwUDPPortDataInEventParams *e);
	void __fastcall connectionTimerNotification(TObject *Sender);
	void __fastcall connectionTimerNotification_on(TObject *Sender);
	void __fastcall FastTimerNotification(TObject *Sender);
	void __fastcall ReconnectTimerCheckConnection(TObject *Sender);
	void __fastcall TBUpdateTimerEvent(TObject *Sender);
	void __fastcall tryCountTimerEvent(TObject *Sender);

	void __fastcall UDPPortErrorEvent(TObject* Sender, TipwUDPPortErrorEventParams *e);
	//void __fastcall connectionTimerNotification_test(TObject *Sender);

	TMutex *mutex;

protected:
	void __fastcall Execute();
	void __fastcall StartChartTimer();
	void __fastcall SetCrossForm();
	void __fastcall SetSourceAddress();
	UnicodeString SourceString;

	void __fastcall TurnOff();
	void __fastcall BuffInit();

	void __fastcall SetApproachedState();
	void __fastcall SetNotApproachedState();
public:
	__fastcall UdpThread(bool CreateSuspended);
	void CreateObjects();
	void ConfigThread();
	void ListenUdp();
	void SendBytes();
    void CloseThread();
	void DataBaseSaveBuffInit();
	void SendSettingPacket(unsigned char afm_mode ,unsigned char approach_mode,unsigned char power_on_off);
	void SendApproachPacket(int Refrence, int KI, int KP, int KD, int Bias, int Motor, int Piezo, int KIFeedBack, int Number,int ampdiff, int Start);

	void SendScanInfPacket();
	UdpDataSendClass* myUdpDataSendClass;

	void GetDataFromArray(DynamicArray<Byte> myData);

	int GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,bool bits);

    TipwUDPPort *ipwUDPPort;
	TipwIPInfo *ipwIPInfo;
    bool network;

	TTimer *timer;
	TTimer *on_timer;
	int connection_try;
	int connection_tryCount;
	bool connected_udp;
	bool on_PC;
	bool SendPcOn;

	AnsiString myIp;
	AnsiString broadCastIp;
	AnsiString myHandShake;
	AnsiString pcHandShake;

	int srcPort;
	int dntPort;

	DynamicArray<Byte> tmpData;
	DynamicArray<int> plotData;

	DynamicArray<Byte> SendData;

	void PowerOn();
	void PowerOff();
	void Pairing();

	bool osc;


	int GetNewData(unsigned char data1,
							unsigned char data2,
							unsigned char data3,
							unsigned char data4,
							int count);

	void DataParser(DynamicArray<Byte> myData);


	DataCalss *data_buffer;

	bool thread_started;

	bool record;
	bool start_record;
	bool stop_recored;

	bool recording;
	bool rec_created;
	bool activated;
	int rec_time;
	recUnit *myRecUnit;

	bool fast_approached;
	bool approched;
	bool FastToNormal;
    bool fs_GoTo_set;

	bool All_Scale;

	void SetUdpSendData(DynamicArray<Byte> byts);
	bool LetSendData;
	void SetSendDataTrue();

	int xx;
	int yy;
	int zz;

	void PacketSendLog(int frame);

	TTimer *FastTimer;
	TTimer *ReconnectTimer;
	int FastStep;

	int ApproachCounter;
	double FastAmp;
	String Last_ip;

	bool FirstStart;
	bool ConnectionState;


	int Piezo_Z;
	bool FirstApproachStep;

    int tryOnAdapter;

	TTimer *TBUpdateTimer;
	TTimer *tryCountTimer;

};
//---------------------------------------------------------------------------
#endif
