//---------------------------------------------------------------------------

#ifndef TcpUnitH
#define TcpUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Classes.hpp>
#include <IniFiles.hpp>
#include "ipwipdaemon.h"
#include "ipwipport.h"
#include "systdate.h"
#include <System.Diagnostics.hpp>

#include "defines.h"
#include<iostream>
#include<fstream>
using namespace std;
//---------------------------------------------------------------------------
class TcpThread : public TThread
{
private:
	//Events Callbacks
	void __fastcall TcpConnectionRequestEvent(TObject* Sender, TipwIPDaemonConnectionRequestEventParams *e);
	void __fastcall TcpConnectedEvent(TObject* Sender, TipwIPDaemonConnectedEventParams *e);
	void __fastcall TcpDisconnectedEvent(TObject* Sender, TipwIPDaemonDisconnectedEventParams *e);
//	void __fastcall TcpErrorEvent(TObject* Sender, TipwIPDaemonErrorEventParams *e);
	void __fastcall TcpDataInEvent(TObject* Sender, TipwIPDaemonDataInEventParams *e);

	void __fastcall TcpClientConnectedEvent(TObject *Sender, TipwIPPortConnectedEventParams *e);
	void __fastcall TcpClientDisConnectedEvent(TObject *Sender, TipwIPPortDisconnectedEventParams *e);
	void __fastcall TcpClientErrorEvent(System::TObject* Sender, TipwIPPortErrorEventParams *e);

	void __fastcall AmpChartTimerNoti(TObject *Sender);
	void __fastcall StartDownloadFsFiles();

	void __fastcall FsChartsTimerNoti(TObject *Sender);
	void __fastcall ClearAllSeries();
	void __fastcall UpdateCharts();
	void CreateCharts(int resolution);
	void __fastcall UpdateFsChartsStatus();
	bool FsUpdateChartsStatus;

	//Variables
	bool ThreadStarted;
	bool Connection;

	int LocalPort;
	int RemotePort;


	int tmpCount;

//    TStopwatch* StopWatch;

protected:
	void __fastcall Execute();
	void __fastcall AddDataToAmpDncChart();
	void __fastcall UpdateAmpChart();
	void CreateChart(int resolution, UnicodeString file, bool direction);
	void __fastcall StopLitho();
	void __fastcall OffFs();

//    TMutext mutex;
public:
	__fastcall TcpThread(bool CreateSuspended);

	TipwIPDaemon *ipwTcpServer;
	TipwIPPort *ipwTcpClient;

	int PacketSize;
	int TcpMode;
	bool FirstTcpMode;
	TByteDynArray bytes;
	int length;
    int Pic_Freq_Index;
	//Methods
	void ConfigCalss();
	void InitClass();
	void CreateClassObjects();
	void ListenTcp();
	void ClientTcp();
    void TcpSendData(DynamicArray<Byte> bytes);
	void ConnectToServer();
	void DisConnectFromServer();
	int GetPacketSize(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3);
	void StopStartThread(bool myValue);
	void CloseTcpThread();
	void GetNewDncPacket(TByteDynArray data);
	void GetNewForcePacketFile(TByteDynArray data);
	double GetNewDncData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,bool bits,double data_index,double data_offset, bool UnSigned, int ScopIndex);
//    int* ByteToType()

	int counter;
	bool finish;
	int AmpDataLength;
	int AmpDataCounter;
	double AmpMin;
	double AmpMax;

	int Counter;
    int dnc_dis;

	double Amp_Index;
	double Amp_Offset;

	TTimer* AmpChartTimer;
//	bool datasend;
//	TByteDynArray SendBytess;
//	void SendBytes();

	bool tcp_imaging;
	bool tcp_dnc;

	int OneCounter;
	int TwoCounter;
	int ThreeCounter;
	int FourCounter;
	int FiveCounter;
	int SixCounter;


	int CurrentResolution;
	int CurrentSize;

	TByteDynArray TopoFw;
	TByteDynArray TopoBw;
	TByteDynArray TbFw;
	TByteDynArray TbBw;
	TByteDynArray LrFw;
	TByteDynArray LrBw;
	TByteDynArray AmpFw;
	TByteDynArray AmpBw;
	TByteDynArray PhaseFw;
	TByteDynArray PhaseBw;
	TByteDynArray CmAFMFw;
	TByteDynArray CmAFMBw;


	int count;

	bool TcpAck;
    bool ClientConnected;

	//Variables

	//Setter Functions
	void Set_PacketSize(int myValue){
		PacketSize = myValue;
	}
	void Set_ThreadStarted(bool myValue){
		ThreadStarted = myValue;
	}
	void Set_Connection(bool myValue){
		Connection = myValue;
	}
	void Set_LocalPort(int myValue){
		LocalPort = myValue;
	}
	void Set_CurrentResolution(int myValue){
		CurrentResolution = myValue;
	}
	void Set_CurrentSize(int myValue){
		CurrentSize = myValue;
	}

	//Getter Functions
	int Get_PacketSize(){
		return PacketSize;
	}
	bool Get_ThreadStarted(){
		return ThreadStarted;
	}
	bool Get_Connection(){
		return Connection;
	}
	int Get_LocalPort(){
		return LocalPort;
	}
	int Get_CurrentResolution(){
		return CurrentResolution;
	}
	int Get_CurrentSize(){
		return CurrentSize;
	}

	TTimer* FsChartsTimer;
	int CurrentFsResolution;

	UnicodeString LocalFileTopo_Fw;
	UnicodeString LocalFileTb_Fw;
	UnicodeString LocalFileLr_Fw;
	UnicodeString LocalFileAmp_Fw;
	UnicodeString LocalFilePhase_Fw;
	UnicodeString LocalFileCmAfm_Fw;

	UnicodeString LocalFileTopo_Bw;
	UnicodeString LocalFileTb_Bw;
	UnicodeString LocalFileLr_Bw;
	UnicodeString LocalFileAmp_Bw;
	UnicodeString LocalFilePhase_Bw;
	UnicodeString LocalFileCmAfm_Bw;
	UnicodeString SaveDirection;
	int tmpFsSeries;
	int tmpFsValue;
	int tmpCounter;
	int tmpResolution;

	double FsXAxis_z;
//	double FsXAxis_zd;
//    double FsXAxis_znd;
	double FsXAxis_t;
	double FsTimeRange;
	double FsRange_z;
	bool Fs_C_Factor_Set;
	double Fs_C_Factor;
	double Fs_XAxis_Offset;
	double tmpFsValue2;

	ofstream *ColibratedFile;
	ofstream *FILE;
	AnsiString name;
    int ForcPacketCounter;

	bool fs_set;

};
//---------------------------------------------------------------------------
#endif

