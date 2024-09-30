//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>

#pragma hdrstop
#pragma package(smart_init)
#pragma link "ipwipdaemon"

#include "TcpUnit.h"
#include "globals.h" //queue calss
#include "mainUnit.h"
#include <iostream>

using namespace std;
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TcpUnit::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TcpThread::TcpThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------

void TcpThread::InitClass()
{
	ThreadStarted = false;
//	Connection = false;
	CurrentResolution = -1;
	CurrentSize = -1;
	counter = 0;

    TcpMode = -1;
	FirstTcpMode = false;
	finish = false;
	tmpCount=0;

	OneCounter = 0;
	TwoCounter = 0;
	ThreeCounter = 0;
	FourCounter = 0;
	FiveCounter = 0;
	SixCounter = 0;

	count = 0;

	tcp_imaging = false;
	tcp_dnc = false;

	FsChartsTimer = NULL;
	CurrentFsResolution = 0;

	LocalFileTopo_Fw = "";
	LocalFileTb_Fw = "";
	LocalFileLr_Fw = "";
	LocalFileAmp_Fw = "";
	LocalFilePhase_Fw = "";
	LocalFileCmAfm_Fw = "";

	LocalFileTopo_Bw = "";
	LocalFileTb_Bw = "";
	LocalFileLr_Bw = "";
	LocalFileAmp_Bw = "";
	LocalFilePhase_Bw = "";
	LocalFileCmAfm_Bw = "";
	name = "";
	SaveDirection = "";

	tmpFsSeries = 0;
	tmpFsValue = 0;

	dnc_dis = 0;

	FsUpdateChartsStatus = false;

	fs_set = false;
	TcpAck = false;
	ClientConnected = false;

	ipwTcpServer = NULL;
	ipwTcpClient = NULL;
//	datasend = false;
}
//---------------------------------------------------------------------------

void TcpThread::ConfigCalss()
{
	mainForm->LogToFile("TcpThread::ConfigCalss");

	LocalPort = TcpTable.local_port;
	RemotePort = TcpTable.remote_port;
	Amp_Index = OscTable[6].index;
	Amp_Offset = OscTable[6].offset;
//	Fs_C_Factor_Set = iniFile->ReadBool("FORCE_CONFIG","C_Factor_Set",0);
//	Fs_C_Factor = iniFile->ReadFloat("FORCE_CONFIG","TB_C_Factor",0);
//	mainForm->LogToFile("TCP apm index = " + FloatToStr(Amp_Index));
//	mainForm->LogToFile("TCP apm offset = " + FloatToStr(Amp_Offset));


//	LocalFileTopo_Fw = "fsfile/Fw_Fs_Topo.txt";
//	LocalFileTb_Fw = "fsfile/Fw_Fs_Tb.txt";
//	LocalFileLr_Fw = "fsfile/Fw_Fs_Lr.txt";
//	LocalFileAmp_Fw = "fsfile/Fw_Fs_Amp.txt";
//	LocalFilePhase_Fw = "fsfile/Fw_Fs_Phase.txt";
//	LocalFileCmAfm_Fw = "fsfile/Fw_Fs_CmAfm.txt";
//
//    LocalFileTopo_Bw = "fsfile/Bw_Fs_Topo.txt";
//	LocalFileTb_Bw = "fsfile/Bw_Fs_Tb.txt";
//	LocalFileLr_Bw = "fsfile/Bw_Fs_Lr.txt";
//	LocalFileAmp_Bw = "fsfile/Bw_Fs_Amp.txt";
//	LocalFilePhase_Bw = "fsfile/Bw_Fs_Phase.txt";
//	LocalFileCmAfm_Bw = "fsfile/Bw_Fs_CmAfm.txt";
}
//---------------------------------------------------------------------------

void TcpThread::CreateClassObjects()
{
	mainForm->LogToFile("TcpThread::CreateClassObjects");
	ipwTcpServer = new TipwIPDaemon(NULL);
//	StopWatch = new TStopwatch;
	ipwTcpClient = new TipwIPPort(NULL);

	AmpChartTimer = new TTimer(NULL);
	AmpChartTimer->Enabled = false;
	AmpChartTimer->Interval = 1;
	AmpChartTimer->OnTimer = AmpChartTimerNoti;


	FsChartsTimer = new TTimer(NULL);
	FsChartsTimer->Enabled = false;
	FsChartsTimer->Interval = 250;
	FsChartsTimer->OnTimer = FsChartsTimerNoti;

}
//---------------------------------------------------------------------------

void TcpThread::ListenTcp()
{
	mainForm->LogToFile("TcpThread::ListenTcp");
	if(ipwTcpServer){
		ipwTcpServer->OnConnectionRequest =  TcpConnectionRequestEvent;
		ipwTcpServer->OnConnected = TcpConnectedEvent;
		ipwTcpServer->OnDisconnected = TcpDisconnectedEvent;
//		ipwTcpServer->OnError = TcpErrorEvent;
		ipwTcpServer->OnDataIn = TcpDataInEvent;
		ipwTcpServer->Config("InBufferSize=275000000");
		ipwTcpServer->LocalHost = "0.0.0.0";
		ipwTcpServer->LocalPort = LocalPort;
		ipwTcpServer->Listening = true;
	}
}
//---------------------------------------------------------------------------

void TcpThread::ClientTcp()
{
	mainForm->LogToFile("TcpThread::ClientTcp");
	if(ipwTcpClient){
		ipwTcpClient->RemotePort = RemotePort;
		ipwTcpClient->OnConnected = TcpClientConnectedEvent;
		ipwTcpClient->OnDisconnected = TcpClientDisConnectedEvent;
		ipwTcpClient->Config("MaxLineLength=32776");
		ipwTcpClient->OnError = TcpClientErrorEvent;
		ipwTcpClient->Linger = false;
//		ipwTcpClient->KeepAlive = true;
//		ipwTcpClient->Timeout = 0;
	}

}
//---------------------------------------------------------------------------

void __fastcall TcpThread::TcpClientConnectedEvent(TObject *Sender, TipwIPPortConnectedEventParams *e)
{
	TcpAck = false;
	ClientConnected = true;
//	mainForm->LogToFile("_______________________TcpThread : TcpClient : Connected Event_______________________");
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::TcpClientDisConnectedEvent(TObject *Sender, TipwIPPortDisconnectedEventParams *e)
{
	ClientConnected = false;
//	mainForm->LogToFile("_______________________TcpThread : TcpClient: DisConnected Event_______________________");
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::TcpClientErrorEvent(System::TObject* Sender, TipwIPPortErrorEventParams *e)
{
	mainForm->LogToFile("TcpThread : TcpClientErrorEvent**************************************************: " + e->Description);
}
//---------------------------------------------------------------------------

void TcpThread::TcpSendData(DynamicArray<Byte> bytes)
{
	ipwTcpClient->Send(bytes);
//	mainForm->LogToFile("TcpThread::TcpSendData");
}
//---------------------------------------------------------------------------

void TcpThread::ConnectToServer()
{
//	mainForm->LogToFile("TcpThread::ConnectToServer");
	ipwTcpClient->Connect(ipwTcpClient->RemoteHost,RemotePort);
}
//---------------------------------------------------------------------------
void TcpThread::DisConnectFromServer()
{
	mainForm->LogToFile("TcpThread::DisConnectFromServer");
	ipwTcpClient->Disconnect();
}
//---------------------------------------------------------------------------

void TcpThread::StopStartThread(bool myValue)
{
	ThreadStarted = myValue;
	if(!myValue){
		ipwTcpServer->Listening = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::Execute()
{
	//---- Place thread code here ----
	NameThreadForDebugging(System::String(L"TcpThread"));
	InitClass();
	ConfigCalss();
	CreateClassObjects();
	ListenTcp();
	ClientTcp();
	StopStartThread(true);
	while(ThreadStarted && !finish){
		Application->ProcessMessages();
		if(finish)
			StopStartThread(false);
		Sleep(20);
	}
//	StopStartThread(false);
	finish = false;
	CloseTcpThread();
}
//---------------------------------------------------------------------------

int TcpThread::GetPacketSize(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3)
{
	unsigned char tmp1[4] ;
	int tmp = 0;
	memset(tmp1,0x00,4);
	tmp1[0] = data0;
	tmp1[1] = data1;
	tmp1[2] = data2;
	tmp1[3] = data3;
	memcpy((void *)&tmp , (void *)tmp1 , 4);
	return tmp;
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::TcpConnectionRequestEvent(TObject* Sender, TipwIPDaemonConnectionRequestEventParams *e)
{
//	mainForm->LogToFile("TcpThread : TcpConnectionRequestEvent : TcpMode = " + IntToStr(TcpMode));
	if(TcpMode == 0 /*&& !FirstTcpMode*/){
		e->Accept = true;
		mainForm->LogToFile("TcpThread : TcpConnectionRequestEvent : img accepted");
	}
	else if(TcpMode == 1 /*&& !FirstTcpMode*/){
		e->Accept = true;
		mainForm->LogToFile("TcpThread : TcpConnectionRequestEvent : dnc accepted");
	}
	else if(TcpMode == 2 /*&& !FirstTcpMode*/){
		e->Accept = true;
		mainForm->LogToFile("TcpThread : TcpConnectionRequestEvent : fs accepted");
	}
	else if(TcpMode == 3 /*&& !FirstTcpMode*/){
		e->Accept = true;
		mainForm->LogToFile("TcpThread : TcpConnectionRequestEvent : litho accepted");
	}
	else if(TcpMode == 4 /*&& !FirstTcpMode*/){
		e->Accept = true;
//		mainForm->LogToFile("TcpThread : TcpConnectionRequestEvent : ack accepted");
	}

}
//---------------------------------------------------------------------------

void __fastcall TcpThread::TcpConnectedEvent(TObject* Sender, TipwIPDaemonConnectedEventParams *e)
{
//	mainForm->LogToFile("TcpThread : TcpConnectedEvent : TcpMode = " + IntToStr(TcpMode));
	if(TcpMode == 0 /*&& !FirstTcpMode*/){
		ipwTcpServer->FSetRecordLength(e->ConnectionId,HEADER_COUNT_IMAGE+PacketSize*4);
		mainForm->LogToFile("TcpThread : TcpConnectedEvent : img connected");
		FirstTcpMode = true;
	}
	else if(TcpMode == 1 /*&& !FirstTcpMode*/){
		ipwTcpServer->FSetRecordLength(e->ConnectionId,HEADER_COUNT_DNC+PacketSize*4);
		mainForm->LogToFile("TcpThread : TcpConnectedEvent : dnc connected");
		FirstTcpMode = true;
	}
	else if(TcpMode == 2 /*&& !FirstTcpMode*/){
		ipwTcpServer->FSetRecordLength(e->ConnectionId,HEADER_COUNT_Force+PacketSize*4);
		mainForm->LogToFile("TcpThread : TcpConnectedEvent : fs connected");
		FirstTcpMode = true;
	}
	else if(TcpMode == 3 /*&& !FirstTcpMode*/){
		ipwTcpServer->FSetRecordLength(e->ConnectionId,4);
		mainForm->LogToFile("TcpThread : TcpConnectedEvent : litho connected");
		FirstTcpMode = true;
	}
	else if(TcpMode == 4 /*&& !FirstTcpMode*/){
		ipwTcpServer->FSetRecordLength(e->ConnectionId,6);
//		mainForm->LogToFile("TcpThread : TcpConnectedEvent : ack connected");
		FirstTcpMode = true;
	}
	Connection = true;
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::TcpDisconnectedEvent(TObject* Sender, TipwIPDaemonDisconnectedEventParams *e)
{
	Connection = false;
//	mainForm->LogToFile("TcpThread : TcpDisconnectedEvent : TcpMode = " + IntToStr(TcpMode));
	if(TcpMode == 0 /*&& !FirstTcpMode*/){
		mainForm->LogToFile("TcpThread : TcpDisconnectedEvent : img disconnected");
	}
	else if(TcpMode == 1 /*&& !FirstTcpMode*/){

		mainForm->LogToFile("TcpThread : TcpDisconnectedEvent : dnc disconnected");
		if(mainForm->myControlPanelForm->fastfast){
			dnc_dis += 1;
			if(dnc_dis == 2){
			  mainForm->myControlPanelForm->dnc = true;
			  dnc_dis = 0;
			}

		}

	}
	else if(TcpMode == 2 /*&& !FirstTcpMode*/){
		mainForm->LogToFile("TcpThread : TcpDisconnectedEvent : fs disconnected");
	}
	else if(TcpMode == 3 /*&& !FirstTcpMode*/){
		mainForm->LogToFile("TcpThread : TcpDisconnectedEvent : litho disconnected");
	}
	else if(TcpMode == 4 /*&& !FirstTcpMode*/){
//		mainForm->LogToFile("TcpThread : TcpConnectedEvent : ack disconnected");
	}
}
//---------------------------------------------------------------------------

//void __fastcall TcpThread::TcpErrorEvent(TObject* Sender, TipwIPDaemonErrorEventParams *e)
//{
//	ShowMessage("TCP Error : " + e->Description);
//}
////---------------------------------------------------------------------------

void __fastcall TcpThread::TcpDataInEvent(TObject* Sender, TipwIPDaemonDataInEventParams *e)
{

//	mainForm->LogToFile("TcpThread::TcpDataInEvent : " + IntToStr(e->TextB[2]) + ", Tcp Mode = " + IntToStr(TcpMode));

	if(TcpMode == 0 && e->TextB[2] == TCP_HEADER_IMAGE){ //scan
//		if(mainForm->AppMode == 5)
//		mainForm->LogToFile("TcpThread : TcpDataInEvent : TCP_HEADER_IMAGE");
//		CurrentResolution = GetPacketSize(e->TextB[5],e->TextB[6],e->TextB[7],e->TextB[8]);
		int LineNumber = GetPacketSize(e->TextB[9],e->TextB[10],e->TextB[11],e->TextB[12]);
		int PicIndex = e->TextB[4];
		int ForwardBit = e->TextB[3];
//		if(LineNumber % 16 == 0 && PicIndex == 0 && ForwardBit == 0xFF)
//			mainForm->LogToFile("TcpThread::TcpDataInEvent ....... Line Number " + IntToStr(LineNumber) + " Recieved and Packet Size is : " + FloatToStr(sizeof(e->TextB)/sizeof(e->TextB[0])));

//		if(LineNumber == 0)
//		mainForm->LogToFile("LineNumber : " + IntToStr(LineNumber));
//		if(e->TextB[3] == 0xBB)
//			mainForm->LogToFile("back");
//		if(e->TextB[3] == 0xFF)
//			mainForm->LogToFile("forward");


//	if(PicIndex == 0){
//		if(ForwardBit == 0xFF){
//			if(LineNumber == 0){
//				OneCounter = 0;
//			}
//			OneCounter++;
//
//			if(OneCounter - 1 != LineNumber){
//				mainForm->LogToFile("One = " + IntToStr(LineNumber-1));
//				OneCounter = LineNumber + 1;
//			}
//			if(OneCounter == CurrentResolution){
////				mainForm->LogToFile("OneCounter = " + IntToStr(OneCounter));
//				OneCounter = 0;
//			}
//		}
//		else{
//			if(LineNumber == 0){
//				TwoCounter = 0;
//			}
//			TwoCounter++;
//			if(TwoCounter - 1 != LineNumber){
//				mainForm->LogToFile("Two = " + IntToStr(LineNumber-1));
//				TwoCounter= LineNumber + 1;
//			}
//			if(TwoCounter == CurrentResolution){
////				mainForm->LogToFile("TwoCounter = " + IntToStr(TwoCounter));
//				TwoCounter = 0;
//			}
//		}
//	}
//
//	if(PicIndex == 1){
//		if(ForwardBit == 0xFF){
//			if(LineNumber == 0)
//				ThreeCounter = 0;
//			ThreeCounter++;
//			if(ThreeCounter - 1 != LineNumber){
//				mainForm->LogToFile("Three = " + IntToStr(LineNumber-1));
//				ThreeCounter = LineNumber + 1;
//			}
//			if(ThreeCounter == CurrentResolution){
////				mainForm->LogToFile("ThreeCounter = " + IntToStr(ThreeCounter));
//				ThreeCounter = 0;
//			}
//		}
//		else{
//        	if(LineNumber == 0)
//				FourCounter = 0;
//			FourCounter++;
//			if(FourCounter - 1 != LineNumber){
//				mainForm->LogToFile("Four = " + IntToStr(LineNumber-1));
//				FourCounter = LineNumber + 1;
//			}
//			if(FourCounter == CurrentResolution){
////				mainForm->LogToFile("FourCounter = " + IntToStr(FourCounter));
//				FourCounter = 0;
//			}
//		}
//	}
//
//	if(PicIndex == 2){
//		if(ForwardBit == 0xFF){
//			if(LineNumber == 0)
//				FiveCounter = 0;
//			FiveCounter++;
//			if(FiveCounter - 1 != LineNumber){
//				mainForm->LogToFile("Five = " + IntToStr(LineNumber-1));
//				FiveCounter = LineNumber + 1;
//			}
//			if(FiveCounter == CurrentResolution){
////				mainForm->LogToFile("FiveCounter = " + IntToStr(FiveCounter));
//				FiveCounter = 0;
//			}
//		}
//		else{
//			if(LineNumber == 0)
//				SixCounter = 0;
//			SixCounter++;
//			if(SixCounter - 1 != LineNumber){
//				mainForm->LogToFile("Six = " + IntToStr(LineNumber-1));
//				SixCounter = LineNumber + 1;
//			}
//			if(SixCounter == CurrentResolution){
////				mainForm->LogToFile("SixCounter = " + IntToStr(SixCounter));
//				SixCounter = 0;
//			}
//		}
//	}

		img_queue->enqueue(e->TextB,CurrentResolution);
	}
	else if(TcpMode == 1 && e->TextB[2] == DNC_FRAME){  //dynamic curve
		mainForm->LogToFile("TcpThread : TcpDataInEvent : DNC_FRAME");
		GetNewDncPacket(e->TextB);
	}
	else if(TcpMode == 2 && e->TextB[2] == FORCE_SPEC_FRAME){ //force spectroscopy
		mainForm->LogToFile("TcpThread : TcpDataInEvent : Force_Spec_FRAME");
//		mainForm->LogToFile("TcpThread : TcpDataInEvent : fs_set = " + BoolToStr(fs_set,true));
		if(!fs_set){
//			mainForm->GetSecure();
//			Synchronize(&StartDownloadFsFiles);

			if(ForcPacketCounter < 12){
				CurrentFsResolution = GetPacketSize(e->TextB[5],e->TextB[6],e->TextB[7],e->TextB[8]);

				int SignalIndex = e->TextB[4];
				mainForm->LogToFile("SignalIndex = " + IntToStr(SignalIndex) );
				int ForwardBit = e->TextB[3];
				mainForm->LogToFile("ForwardBit = " + IntToStr(ForwardBit) );

				mainForm->LogToFile("Length = " + IntToStr(e->TextB.Length) );
				switch(SignalIndex)
				{
					case 0:{
						if(ForwardBit == 0xFF){
							TopoFw = e->TextB;
						}
						else if(ForwardBit == 0xBB){
							TopoBw = e->TextB;
						}
					}
					case 1:{
						if(ForwardBit == 0xFF){
							TbFw = e->TextB;
						}
						else if(ForwardBit == 0xBB){
							TbBw = e->TextB;
						}
					}
					case 2:{
						if(ForwardBit == 0xFF){
							LrFw = e->TextB;
						}
						else if(ForwardBit == 0xBB){
							LrBw = e->TextB;
						}
					}
					case 3:{
						if(ForwardBit == 0xFF){
							AmpFw = e->TextB;
						}
						else if(ForwardBit == 0xBB){
							AmpBw = e->TextB;
						}
					}
					case 4:{
						if(ForwardBit == 0xFF){
							PhaseFw = e->TextB;
						}
						else if(ForwardBit == 0xBB){
							PhaseBw = e->TextB;
						}
					}
					case 5:{
						if(ForwardBit == 0xFF){
							CmAFMFw = e->TextB;
						}
						else if(ForwardBit == 0xBB){
							CmAFMBw = e->TextB;
						}
					}

				}
			}
			ForcPacketCounter++;

			if(ForcPacketCounter == 12){
				mainForm->myForceForm->EnableFsPanel(2);
                mainForm->myImageFrom->PaintBox1->Enabled = true;
				mainForm->LogToFile("_________________________________________________________");
				GetNewForcePacketFile(TopoFw);
				GetNewForcePacketFile(TopoBw);
				GetNewForcePacketFile(TbFw);
				GetNewForcePacketFile(TbBw);
				GetNewForcePacketFile(LrFw);
				GetNewForcePacketFile(LrBw);
				GetNewForcePacketFile(AmpFw);
				GetNewForcePacketFile(AmpBw);
				GetNewForcePacketFile(PhaseFw);
				GetNewForcePacketFile(PhaseBw);
				GetNewForcePacketFile(CmAFMFw);
				GetNewForcePacketFile(CmAFMBw);
				mainForm->LogToFile("_________________________________________________________");
				ForcPacketCounter = 0;
				Synchronize(&OffFs);
				FsChartsTimer->Interval = 20;
				FsChartsTimer->Enabled = true;
				mainForm->Forcing = false;
				mainForm->GetSecure();
			}
		}
		else{
			Synchronize(&OffFs);
			fs_set = false;
            mainForm->Forcing = false;
			mainForm->GetSecure();
		}

	}
	else if(TcpMode == 3 && e->TextB[2] == LITHO_FRAME){ //litho spectroscopy
		mainForm->LogToFile("TcpThread : TcpDataInEvent : LITHO_FRAME");
		if(e->TextB[3] == 1){
			mainForm->myLithoFrm->LithoConfigFrm->EnabledPanels(1);
			mainForm->Lithoing = true;
		}
		else{
			mainForm->Lithoing = false;
			mainForm->myLithoFrm->LithoConfigFrm->litho_startstop = false;
			Synchronize(StopLitho);
			mainForm->myLithoFrm->LithoConfigFrm->EnabledPanels(0);
		}
	}
	else if(TcpMode == 4 && e->TextB[2] == TCP_HEADER_ACK){
//		mainForm->LogToFile("TcpThread : TcpDataInEvent :TCP_HEADER_ACK  Length = " + IntToStr(e->TextB.Length));
		if((e->TextB[3] == 'o' && e->TextB[4] == 'k')){

//			mainForm->LogToFile("TcpThread::TCP_HEADER_ACK : ok Recieved");
			TcpAck = true;
		}
	}
	else{
	}
//
}
//---------------------------------------------------------------------------
void TcpThread::GetNewForcePacketFile(TByteDynArray data)
{
	if(data == TopoFw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : TopoFw");
		if(FileExists(LocalFileTopo_Fw))
			DeleteFileW(LocalFileTopo_Fw);
		FILE = new ofstream(LocalFileTopo_Fw.c_str(), ios::out);
		AnsiString tmp;
		for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
//			mainForm->LogToFile("i = " + IntToStr(i) );
//			mainForm->LogToFile("data[i] = " + IntToStr(data[i]) );
//			mainForm->LogToFile("data[i+1] = " + IntToStr(data[i+1]) );
//			mainForm->LogToFile("data[i+2] = " + IntToStr(data[i+2]) );
//			mainForm->LogToFile("data[i+3] = " + IntToStr(data[i+3]) );
//			mainForm->LogToFile("TopoFw data = " + IntToStr(DATA) );
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == TopoBw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : TopoBw");
		if(FileExists(LocalFileTopo_Bw))
			DeleteFileW(LocalFileTopo_Bw);
		FILE = new ofstream(LocalFileTopo_Bw.c_str(), ios::out);
		AnsiString tmp;
		for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == TbFw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : TbFw");
		if(FileExists(LocalFileTb_Fw))
			DeleteFileW(LocalFileTb_Fw);
		FILE = new ofstream(LocalFileTb_Fw.c_str(), ios::out);
		AnsiString tmp;
        for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == TbBw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : TbBw");
		if(FileExists(LocalFileTb_Bw))
			DeleteFileW(LocalFileTb_Bw);
		FILE = new ofstream(LocalFileTb_Bw.c_str(), ios::out);
		AnsiString tmp;
        for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == LrFw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : LrFw");
		if(FileExists(LocalFileLr_Fw))
			DeleteFileW(LocalFileLr_Fw);
		FILE = new ofstream(LocalFileLr_Fw.c_str(), ios::out);
		AnsiString tmp;
        for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == LrBw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : LrBw");
		if(FileExists(LocalFileLr_Bw))
			DeleteFileW(LocalFileLr_Bw);
		FILE = new ofstream(LocalFileLr_Bw.c_str(), ios::out);
		AnsiString tmp;
        for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == AmpFw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : AmpFw");
		if(FileExists(LocalFileAmp_Fw))
			DeleteFileW(LocalFileAmp_Fw);
		FILE = new ofstream(LocalFileAmp_Fw.c_str(), ios::out);
		AnsiString tmp;
        for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == AmpBw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : AmpBw");
		if(FileExists(LocalFileAmp_Bw))
			DeleteFileW(LocalFileAmp_Bw);
		FILE = new ofstream(LocalFileAmp_Bw.c_str(), ios::out);
		AnsiString tmp;
        for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == PhaseFw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : PhaseFw");
		if(FileExists(LocalFilePhase_Fw))
			DeleteFileW(LocalFilePhase_Fw);
		FILE = new ofstream(LocalFilePhase_Fw.c_str(), ios::out);
		AnsiString tmp;
		for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == PhaseBw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : PhaseBw");
		if(FileExists(LocalFilePhase_Bw))
			DeleteFileW(LocalFilePhase_Bw);
		FILE = new ofstream(LocalFilePhase_Bw.c_str(), ios::out);
		AnsiString tmp;
		for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == CmAFMFw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : CmAFMFw");
		if(FileExists(LocalFileCmAfm_Fw))
			DeleteFileW(LocalFileCmAfm_Fw);
		FILE = new ofstream(LocalFileCmAfm_Fw.c_str(), ios::out);
		AnsiString tmp;
		for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}
	else if(data == CmAFMBw){
		mainForm->LogToFile("TcpThread::GetNewForcePacketFile : CmAFMBw");
		if(FileExists(LocalFileCmAfm_Bw))
			DeleteFileW(LocalFileCmAfm_Bw);
		FILE = new ofstream(LocalFileCmAfm_Bw.c_str(), ios::out);
		AnsiString tmp;
		for(int i=HEADER_COUNT_Force; i<data.Length; i = i+4){
			int j = (i - HEADER_COUNT_Force)/4;
			int DATA = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,1,0,false,-1);
			tmp = IntToStr(DATA)+'\n';
			FILE->write(tmp.c_str(), tmp.Length());
		}
		delete FILE;
	}

}
//---------------------------------------------------------------------------

void __fastcall TcpThread::StopLitho()
{
	mainForm->LogToFile("TcpThread::StopLitho");
	mainForm->myLithoFrm->LithoConfigFrm->StartLitho();
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::StartDownloadFsFiles()
{
//	mainForm->myCommandCreatorThread->myFs->StartDownloadFiles();
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::OffFs()
{
	mainForm->LogToFile("TcpThread::OffFs");
	mainForm->myCommandCreatorThread->myFs->OffFs();
}
//---------------------------------------------------------------------------

void TcpThread::CloseTcpThread()
{
	this->Terminate();
	delete this;
}
//---------------------------------------------------------------------------

void TcpThread::GetNewDncPacket(TByteDynArray data)
{
	mainForm->LogToFile("TcpThread::GetNewDncPacket");
	if(data[3] == PHASE_TCP_DATA){
//		mainForm->LogToFile("Phase : Dnc packet lenght = " + IntToStr(data.Length));
//		mainForm->LogToFile("Phase : Dnc packet sweep point = " + FloatToStr(GetNewDncData(data[4],data[5],data[6],data[7],false,1,0)));
//		mainForm->LogToFile("Phase : from = " + FloatToStr(mainForm->myDynamicCurvePanelForm->Freq_From_Val));
//		mainForm->LogToFile("Phase : to = " + FloatToStr(mainForm->myDynamicCurvePanelForm->Freq_To_Val));
//		mainForm->LogToFile("Phase : steps = " + FloatToStr(mainForm->myDynamicCurvePanelForm->FreqStep));
	}
	else if(data[3] == AMP_TCP_DATA){
        tcp_dnc = false;
		AmpDataLength = GetNewDncData(data[4],data[5],data[6],data[7],false,1,0,false,-1);
//		mainForm->LogToFile("Amp : Dnc packet lenght = " + IntToStr(AmpDataLength));
//		mainForm->LogToFile("Amp : steps = " + FloatToStr(mainForm->myDynamicCurvePanelForm->FreqStep));
		mainForm->myDynamicCurvePanelForm->AmpDncSeries->Clear();
		mainForm->myDynamicCurvePanelForm->AmpChart->BottomAxis->SetMinMax(
			mainForm->myDynamicCurvePanelForm->From_Val,
			mainForm->myDynamicCurvePanelForm->From_Val + mainForm->myDynamicCurvePanelForm->PointsCount_Val * mainForm->myDynamicCurvePanelForm->FreqStep
		);

		int j;
		j = 0 ;
		AmpDataCounter = 0;
		dnc_queue->initQ();
//		mainForm->LogToFile("data.Length = " + IntToStr(data.Length));
		for(int i=HEADER_COUNT_DNC; i<data.Length; i = i+4){
			j = ( (i-HEADER_COUNT_DNC)/4 );
            if(j == 0){
//				mainForm->LogToFile("timer on");
				AmpChartTimer->Enabled = true;

			}
			else if(j > 9){
				double Convert_Data = GetNewDncData(data[i],data[i+1],data[i+2],data[i+3],false,Amp_Index,Amp_Offset,true,6);
//				Convert_Data = Convert_Data * (double)1000;
				if(j == 10){
					AmpMax = Convert_Data;
				}
				else if(Convert_Data > AmpMax){
					AmpMax = Convert_Data;
					Pic_Freq_Index = j;
//					mainForm->LogToFile("TcpThread::GetNewDncPacket : AmpMax =" + FloatToStr(AmpMax));
				}
				dnc_queue->enqueue(Convert_Data);


			}

		}
	}
}
//---------------------------------------------------------------------------

double TcpThread::GetNewDncData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,bool bits,double data_index,double data_offset, bool UnSigned, int ScopIndex)
{
	unsigned char tmp1[4] ;
	int Sindedtmp = 0 ;
	unsigned int UnSindedtmp = 0 ;
	memset(tmp1,0x00,4);

//	if(ScopIndex == 6 && data3 !=0)
//		mainForm->LogToFile(IntToStr(data3));

	//32 bits to 24 bits
	if(bits){
		if(UnSigned){
			tmp1[1] = data0;
			tmp1[2] = data1;
			tmp1[3] = data2;
			memcpy((void *)&UnSindedtmp , (void *)tmp1 , 4);
			UnSindedtmp = UnSindedtmp >> 8 ;
		}
		else{
			tmp1[1] = data0;
			tmp1[2] = data1;
			tmp1[3] = data2;
			memcpy((void *)&Sindedtmp , (void *)tmp1 , 4);
			Sindedtmp = Sindedtmp >> 8 ;
		}
	}
	else{
		if(UnSigned){
			tmp1[0] = data0;
			tmp1[1] = data1;
			tmp1[2] = data2;
			tmp1[3] = data3;
			memcpy((void *)&UnSindedtmp , (void *)tmp1 , 4);
		}
		else{
			tmp1[0] = data0;
			tmp1[1] = data1;
			tmp1[2] = data2;
			tmp1[3] = data3;
			memcpy((void *)&Sindedtmp , (void *)tmp1 , 4);
		}
	}
	double t = 0;
	if(UnSigned)
		t = (double)UnSindedtmp;
	else
		t = (double)Sindedtmp;
	t = data_index * t + data_offset;
	return t;
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::AddDataToAmpDncChart()
{
//	mainForm->LogToFile("TcpThread::AddDataToAmpDncChart");
	if( ( !dnc_queue->isEmpty() && !(dnc_queue->checked[dnc_queue->front - 1]) ) || (dnc_queue->front == 0) ){
		double data = dnc_queue->peek();
//		if(mainForm->myDynamicCurvePanelForm->AmpDncSeries->XValues->)

		int freq = mainForm->myDynamicCurvePanelForm->From_Val + AmpDataCounter * mainForm->myDynamicCurvePanelForm->FreqStep;
//		mainForm->LogToFile("AmpDataCounter = " + IntToStr(AmpDataCounter) + " , freq = " + IntToStr(freq));
		mainForm->myDynamicCurvePanelForm->AmpDncSeries->AddXY(freq, data);
//		mainForm->myDynamicCurvePanelForm->AmpChart->Update();
//		mainForm->LogToFile( IntToStr(AmpDataCounter) + " : " + FloatToStr(mainForm->myDynamicCurvePanelForm->From_Val + AmpDataCounter * mainForm->myDynamicCurvePanelForm->FreqStep) + " , " + FloatToStr(data) );
		AmpDataCounter++;
		dnc_queue->dequeue();
	}
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::AmpChartTimerNoti(TObject *Sender)
{
//	mainForm->LogToFile("TcpThread::AmpChartTimerNoti");
	if(AmpDataCounter >= AmpDataLength - 10){
		AmpChartTimer->Enabled = false;
		Synchronize(&UpdateAmpChart);
	}
	else{
		for(int i=0; i<dnc_queue->size(); i++){
			Synchronize(&AddDataToAmpDncChart);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::UpdateAmpChart()
{
	mainForm->LogToFile("TcpThread::UpdateAmpChart");
	mainForm->myDynamicCurvePanelForm->AmpChart->Refresh();
	mainForm->myDynamicCurvePanelForm->UpDownBorder(mainForm->myDynamicCurvePanelForm->RunAdvGlassButton->Appearance,true);
	mainForm->myDynamicCurvePanelForm->MaxAllAdvEdit->Text = "Max Amp: " +  FormatFloat("#0.0##",AmpMax) + " V";
	mainForm->myDynamicCurvePanelForm->EnableObjects(true);
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::FsChartsTimerNoti(TObject *Sender)
{
	FsChartsTimer->Enabled = false;
	if(FsUpdateChartsStatus){
		FsUpdateChartsStatus = false;
		mainForm->LogToFile("TcpThread : FsChartsTimerNoti : final charts update ");
		Synchronize(&UpdateFsChartsStatus);
	}
	else{
		FsUpdateChartsStatus = false;
		mainForm->LogToFile("TcpThread : FsChartsTimerNoti : start charts creation ");
		CreateCharts(CurrentFsResolution);
	}
}
//---------------------------------------------------------------------------

void TcpThread::CreateChart(int resolution, UnicodeString file, bool direction)
{
//	mainForm->LogToFile("TcpThread::CreateChart");

	Fs_C_Factor_Set = ForceTable.C_Factor_Set;
	Fs_C_Factor = ForceTable.TB_C_Factor;



	if(!DirectoryExists(SaveDirection)){
		AnsiString dir = SaveDirection;
		CreateDirectoryA(dir.c_str(),NULL);
	}
//	mainForm->LogToFile(SaveDirection);
	//open file
	ifstream infile(file.c_str());
	//to series

	tmpCounter = 0;
	int* tmp = new int[tmpResolution];
	while(infile >> tmp[tmpCounter]){
		tmpCounter++;
		if(tmpCounter == resolution)
			break;
	}

	if(mainForm->myForceForm->Mode == 1 || mainForm->myForceForm->Mode == 4 || mainForm->myForceForm->Mode == 5){
		FsRange_z = (mainForm->myForceForm->Finaldz * mainForm->myForceForm->index) * pow10l(mainForm->myForceForm->scale*3) * 1000;
		Fs_XAxis_Offset = mainForm->myForceForm->Start_Topo * mainForm->myForceForm->index * pow10l(mainForm->myForceForm->scale*3) * 1000;
	}
	else{
		FsRange_z = (mainForm->myForceForm->FinalU * mainForm->myForceForm->U_index) * pow10l(mainForm->myForceForm->U_Scale*3);
		Fs_XAxis_Offset = (mainForm->myForceForm->Start_U * mainForm->myUdpThread->data_buffer[17].data_index + mainForm->myUdpThread->data_buffer[17].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[17].data_scale * 3);
	}
//	mainForm->LogToFile("TcpThread::CreateChart: FsRange_z = " + FloatToStr(FsRange_z));
//	mainForm->LogToFile("TcpThread::CreateChart: Fs_XAxis_Offset = " + FloatToStr(Fs_XAxis_Offset));
	double FsStep_t = (mainForm->myForceForm->DelayNumber) / 1000;
	FsTimeRange = FsStep_t * resolution;

	AnsiString address = SaveDirection+ "/" + name+".txt" ;
	ColibratedFile = new ofstream(address.c_str(), ios::out);
	AnsiString tmp1;
	tmp1 = "Step Delay = "+IntToStr(mainForm->myForceForm->DelayNumber)+'\n';
	ColibratedFile->write(tmp1.c_str(), tmp1.Length());
	if(tmpFsSeries == 3 || tmpFsSeries == 4){
		tmp1 = "TB_Factor = "+FloatToStr(Fs_C_Factor)+'\n'+"Topo(nm)	"+name+"(mV)"+"	"+name+"(nN)"+'\n';
	}
	else{
		tmp1 = "Topo(nm)	"+name+"	"+'\n';
	}

	ColibratedFile->write(tmp1.c_str(), tmp1.Length());

	if(direction){
		for(int i=0; i<tmpResolution; i++){
			FsXAxis_z = ((double)i/tmpResolution) * FsRange_z;
			if(mainForm->myForceForm->Mode == 1 || mainForm->myForceForm->Mode == 4 || mainForm->myForceForm->Mode == 5){
				FsXAxis_z = Fs_XAxis_Offset - FsXAxis_z;
			}
			else{
				FsXAxis_z = Fs_XAxis_Offset + FsXAxis_z;
			}
			FsXAxis_t =  FsStep_t * i;
			tmpFsValue = tmp[i];
			Synchronize(&UpdateCharts);
		}
	}else{
		for(int i=0; i<tmpResolution; i++){
			FsXAxis_z = ((double)i/tmpResolution) * FsRange_z;
			if(mainForm->myForceForm->Mode == 1 || mainForm->myForceForm->Mode == 4 || mainForm->myForceForm->Mode == 5){
				FsXAxis_z = Fs_XAxis_Offset - FsXAxis_z;
			}
			else{
				FsXAxis_z = Fs_XAxis_Offset + FsXAxis_z;
			}
			FsXAxis_t =  FsStep_t * i;
			tmpFsValue = tmp[(tmpResolution - 1) - i];
			tmpFsValue2 = tmp[i];
			Synchronize(&UpdateCharts);
		}
	}
	ColibratedFile->close();
	infile.close();
	delete[] tmp;
}
//---------------------------------------------------------------------------

void TcpThread::CreateCharts(int resolution)
{
	mainForm->LogToFile("TcpThread::CreateCharts");
	Synchronize(&ClearAllSeries);
	tmpResolution = resolution;
	for(int i=0; i<12; i++){
		switch(i){
			case 0:{
				tmpFsSeries = 1;
				name = "Topo_Fw";
				CreateChart(resolution, LocalFileTopo_Fw,true);
				DeleteFileW(LocalFileTopo_Fw);
				break;
			}
			case 1:{
				tmpFsSeries = 2;
				name = "Topo_Bw";
				CreateChart(resolution, LocalFileTopo_Bw,false);
				DeleteFileW(LocalFileTopo_Bw);
				break;
			}
			case 2:{
				tmpFsSeries = 3;
				name = "Tb_Fw";
				CreateChart(resolution, LocalFileTb_Fw,true);
				DeleteFileW(LocalFileTb_Fw);
				break;
			}
			case 3:{
				tmpFsSeries = 4;
				name = "Tb_Bw";
				CreateChart(resolution, LocalFileTb_Bw,false);
				DeleteFileW(LocalFileTb_Bw);
				break;
			}
			case 4:{
				tmpFsSeries = 5;
				name = "Lr_Fw";
				CreateChart(resolution, LocalFileLr_Fw,true);
				DeleteFileW(LocalFileLr_Fw);
				break;
			}
			case 5:{
				tmpFsSeries = 6;
				name = "Lr_Bw";
				CreateChart(resolution, LocalFileLr_Bw,false);
				DeleteFileW(LocalFileLr_Bw);
				break;
			}
			case 6:{
				tmpFsSeries = 7;
				name = "Amp_Fw";
				CreateChart(resolution, LocalFileAmp_Fw,true);
				DeleteFileW(LocalFileAmp_Fw);
				DeleteFileW(SaveDirection + "/" + name+".txt");
				break;
			}
			case 7:{
				tmpFsSeries = 8;
				name = "Amp_Bw";
				CreateChart(resolution, LocalFileAmp_Bw,false);
				DeleteFileW(LocalFileAmp_Bw);
				DeleteFileW(SaveDirection + "/" + name+".txt");
				break;
			}
			case 8:{
				tmpFsSeries = 9;
				name = "Phase_Fw";
				CreateChart(resolution, LocalFilePhase_Fw,true);
				DeleteFileW(LocalFilePhase_Fw);
				DeleteFileW(SaveDirection + "/" + name+".txt");
				break;
			}
			case 9:{
				tmpFsSeries = 10;
				name = "Phase_Bw";
				CreateChart(resolution, LocalFilePhase_Bw,false);
				DeleteFileW(LocalFilePhase_Bw);
				DeleteFileW(SaveDirection + "/" + name+".txt");
				break;
			}
			case 10:{
				tmpFsSeries = 11;
				name = "CmAfm_Fw";
				CreateChart(resolution, LocalFileCmAfm_Fw,true);
				DeleteFileW(LocalFileCmAfm_Fw);
				break;
			}
			case 11:{
				tmpFsSeries = 12;
                name = "CmAfm_Bw";
				CreateChart(resolution, LocalFileCmAfm_Bw,false);
				DeleteFileW(LocalFileCmAfm_Bw);

				break;
			}
			default:
				break;
		}
	}


	FsUpdateChartsStatus = true;
	FsChartsTimer->Interval = 100;
	FsChartsTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::ClearAllSeries()
{
	mainForm->LogToFile("TcpThread::ClearAllSeries");
//	mainForm->LogToFile("Tcp : charts autorepaint : false ");
//	mainForm->myForceForm->Series1->AutoRepaint = false;
//	mainForm->myForceForm->Series2->AutoRepaint = false;
//	mainForm->myForceForm->Series3->AutoRepaint = false;
//	mainForm->myForceForm->Series4->AutoRepaint = false;
//	mainForm->myForceForm->Series5->AutoRepaint = false;
//	mainForm->myForceForm->Series6->AutoRepaint = false;
//	mainForm->myForceForm->Series7->AutoRepaint = false;
//	mainForm->myForceForm->Series8->AutoRepaint = false;
//	mainForm->myForceForm->Series9->AutoRepaint = false;
//	mainForm->myForceForm->Series10->AutoRepaint = false;
//	mainForm->myForceForm->Series11->AutoRepaint = false;
//	mainForm->myForceForm->Series12->AutoRepaint = false;

//	mainForm->LogToFile("TcpThread : FsChartsTimerNoti : charts : AutoRepaint : false");
	mainForm->myForceForm->ChartChart->AutoRepaint = false;

//	mainForm->LogToFile("Tcp : charts series : clear ");
	mainForm->myForceForm->Series1->Clear();
	mainForm->myForceForm->Series2->Clear();
	mainForm->myForceForm->Series3->Clear();
	mainForm->myForceForm->Series4->Clear();
	mainForm->myForceForm->Series5->Clear();
	mainForm->myForceForm->Series6->Clear();
	mainForm->myForceForm->Series7->Clear();
	mainForm->myForceForm->Series8->Clear();
	mainForm->myForceForm->Series9->Clear();
	mainForm->myForceForm->Series10->Clear();
	mainForm->myForceForm->Series11->Clear();
	mainForm->myForceForm->Series12->Clear();
	mainForm->myForceForm->Series13->Clear();
	mainForm->myForceForm->Series14->Clear();
	mainForm->myForceForm->Series15->Clear();
	mainForm->myForceForm->Series16->Clear();
	mainForm->myForceForm->Series17->Clear();
	mainForm->myForceForm->Series18->Clear();
	mainForm->myForceForm->Series19->Clear();
	mainForm->myForceForm->Series20->Clear();
	mainForm->myForceForm->Series21->Clear();
	mainForm->myForceForm->Series22->Clear();
	mainForm->myForceForm->Series23->Clear();
	mainForm->myForceForm->Series24->Clear();
	mainForm->myForceForm->Series25->Clear();
	mainForm->myForceForm->Series26->Clear();
	mainForm->myForceForm->Series27->Clear();
	mainForm->myForceForm->Series28->Clear();



}
//---------------------------------------------------------------------------

void __fastcall TcpThread::UpdateCharts()
{
	double X_Value_z = FsXAxis_z;
	double X_Value_t = FsXAxis_t;

	if(tmpFsSeries == 1){
		tmpFsValue = MAX_VALUE - tmpFsValue;
		double Y_Value;
		if(AllScale)
			Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[26].data_index + mainForm->myUdpThread->data_buffer[26].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[26].data_scale * 3) * 1000;
		else
			Y_Value = tmpFsValue;
		//		double Y_Value2 = (tmpFsValue2 * mainForm->myUdpThread->data_buffer[26].data_index + mainForm->myUdpThread->data_buffer[26].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[26].data_scale * 3);
		mainForm->myForceForm->Series1->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series13->AddXY(X_Value_t,Y_Value);
		mainForm->myForceForm->Series25->AddXY(X_Value_t,Y_Value);
//		mainForm->LogToFile("Y_Value = " + FloatToStr(Y_Value));
//		mainForm->LogToFile("X_Value_z = " + FloatToStr(X_Value_z));
//		mainForm->LogToFile("X_Value_t = " + FloatToStr(X_Value_t));
//		mainForm->LogToFile(" ");
		AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());

	}

	if(tmpFsSeries == 2){
		tmpFsValue = MAX_VALUE - tmpFsValue;
		tmpFsValue2 = MAX_VALUE - tmpFsValue2;
		double Y_Value;
		double Y_Value2;
		if(AllScale){
			Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[26].data_index + mainForm->myUdpThread->data_buffer[26].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[26].data_scale * 3) * 1000;
			Y_Value2 = (tmpFsValue2 * mainForm->myUdpThread->data_buffer[26].data_index + mainForm->myUdpThread->data_buffer[26].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[26].data_scale * 3) * 1000;
		}
		else{
			Y_Value = tmpFsValue;
			Y_Value2 = tmpFsValue2;
        }
		mainForm->myForceForm->Series2->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series14->AddXY(X_Value_t,Y_Value2);
		mainForm->myForceForm->Series25->AddXY((X_Value_t+FsTimeRange),Y_Value2);
		AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+ FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 3){
		double Y_Value = 0;
		double Y_Value_mV = 0;
		if(!Fs_C_Factor_Set){
			Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[00].data_index + mainForm->myUdpThread->data_buffer[00].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[00].data_scale * 3);
			Y_Value_mV = Y_Value;
		}
		else{
			Y_Value_mV = (tmpFsValue * mainForm->myUdpThread->data_buffer[00].data_index + mainForm->myUdpThread->data_buffer[00].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[00].data_scale * 3);
			Y_Value = ((tmpFsValue * mainForm->myUdpThread->data_buffer[00].data_index + mainForm->myUdpThread->data_buffer[00].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[00].data_scale * 3)) * Fs_C_Factor;
		}
		mainForm->myForceForm->Series3->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series15->AddXY(X_Value_t,Y_Value);
		mainForm->myForceForm->Series26->AddXY(X_Value_t,Y_Value);
        AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value_mV)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 4){
		double Y_Value = 0;
		double Y_Value_mV = 0;
		if(!Fs_C_Factor_Set){
			Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[00].data_index + mainForm->myUdpThread->data_buffer[00].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[00].data_scale * 3);
			Y_Value_mV = Y_Value;
		}
		else{
			Y_Value_mV = (tmpFsValue * mainForm->myUdpThread->data_buffer[00].data_index + mainForm->myUdpThread->data_buffer[00].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[00].data_scale * 3);
			Y_Value = ((tmpFsValue * mainForm->myUdpThread->data_buffer[00].data_index + mainForm->myUdpThread->data_buffer[00].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[00].data_scale * 3)) * Fs_C_Factor;
		}
		mainForm->myForceForm->Series4->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series16->AddXY(X_Value_t,Y_Value);
		mainForm->myForceForm->Series26->AddXY((X_Value_t+FsTimeRange),Y_Value);
        AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value_mV)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 5){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[01].data_index + mainForm->myUdpThread->data_buffer[01].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[01].data_scale * 3);
		mainForm->myForceForm->Series5->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series17->AddXY(X_Value_t,Y_Value);
		mainForm->myForceForm->Series27->AddXY(X_Value_t,Y_Value);
        AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 6){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[01].data_index + mainForm->myUdpThread->data_buffer[01].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[01].data_scale * 3);
		mainForm->myForceForm->Series6->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series18->AddXY(X_Value_t,Y_Value);
		mainForm->myForceForm->Series27->AddXY((X_Value_t+FsTimeRange),Y_Value);
		AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 7){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[06].data_index + mainForm->myUdpThread->data_buffer[06].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[06].data_scale * 3);
		mainForm->myForceForm->Series7->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series19->AddXY(X_Value_t,Y_Value);
		AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());


	}

	if(tmpFsSeries == 8){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[06].data_index + mainForm->myUdpThread->data_buffer[06].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[06].data_scale * 3);
		mainForm->myForceForm->Series8->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series20->AddXY(X_Value_t,Y_Value);
        AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());

	}

	if(tmpFsSeries == 9){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[07].data_index + mainForm->myUdpThread->data_buffer[07].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[07].data_scale * 3);
		mainForm->myForceForm->Series9->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series21->AddXY(X_Value_t,Y_Value);
        AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 10){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[07].data_index + mainForm->myUdpThread->data_buffer[07].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[07].data_scale * 3);
		mainForm->myForceForm->Series10->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series22->AddXY(X_Value_t,Y_Value);
        AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 11){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[8].data_index + mainForm->myUdpThread->data_buffer[8].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[8].data_scale * 3);
		mainForm->myForceForm->Series11->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series23->AddXY(X_Value_t,Y_Value);
		mainForm->myForceForm->Series28->AddXY(X_Value_t,Y_Value);
		AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}

	if(tmpFsSeries == 12){
		double Y_Value = (tmpFsValue * mainForm->myUdpThread->data_buffer[8].data_index + mainForm->myUdpThread->data_buffer[8].data_offset) * pow10l(mainForm->myUdpThread->data_buffer[8].data_scale * 3);
		mainForm->myForceForm->Series12->AddXY(X_Value_z,Y_Value);
		mainForm->myForceForm->Series24->AddXY(X_Value_t,Y_Value);
		mainForm->myForceForm->Series28->AddXY(X_Value_t+FsTimeRange,Y_Value);
		AnsiString tmp;
		tmp = FloatToStr(X_Value_z)+"	"+FloatToStr(Y_Value)+'\n';
		ColibratedFile->write(tmp.c_str(), tmp.Length());
	}
}
//---------------------------------------------------------------------------

void __fastcall TcpThread::UpdateFsChartsStatus()
{
//	mainForm->LogToFile("Tcp : charts autorepaint : true ");
//	mainForm->myForceForm->Series1->AutoRepaint = true;
//	mainForm->myForceForm->Series2->AutoRepaint = true;
//	mainForm->myForceForm->Series3->AutoRepaint = true;
//	mainForm->myForceForm->Series4->AutoRepaint = true;
//	mainForm->myForceForm->Series5->AutoRepaint = true;
//	mainForm->myForceForm->Series6->AutoRepaint = true;
//	mainForm->myForceForm->Series7->AutoRepaint = true;
//	mainForm->myForceForm->Series8->AutoRepaint = true;
//	mainForm->myForceForm->Series9->AutoRepaint = true;
//	mainForm->myForceForm->Series10->AutoRepaint = true;
//	mainForm->myForceForm->Series11->AutoRepaint = true;
//	mainForm->myForceForm->Series12->AutoRepaint = true;

//	mainForm->myForceForm->Series1->Repaint();
//	mainForm->myForceForm->Series2->Repaint();
//	mainForm->myForceForm->Series3->Repaint();
//	mainForm->myForceForm->Series4->Repaint();
//	mainForm->myForceForm->Series5->Repaint();
//	mainForm->myForceForm->Series6->Repaint();
//	mainForm->myForceForm->Series7->Repaint();
//	mainForm->myForceForm->Series8->Repaint();
//	mainForm->myForceForm->Series9->Repaint();
//	mainForm->myForceForm->Series10->Repaint();
//	mainForm->myForceForm->Series11->Repaint();
//	mainForm->myForceForm->Series12->Repaint();

//	mainForm->LogToFile("Tcp : charts :  AutoRepaint : true ");
	mainForm->myForceForm->ChartChart->AutoRepaint = true;
	mainForm->myForceForm->ChartChart->Refresh();
	mainForm->myForceForm->ChartPicker->Enabled = true;
	mainForm->myForceForm->EnableFsPanel(0);
	mainForm->GetSecure();
	mainForm->myForceForm->PickSeries(mainForm->myForceForm->ChartPicker->ItemIndex + 1);
    mainForm->myImageFrom->PaintBox1->Enabled = true;
//	mainForm->myForceForm->ChartAdvWiiProgressBar->Visible = false;
}
//---------------------------------------------------------------------------

