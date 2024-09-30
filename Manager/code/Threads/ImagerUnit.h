//---------------------------------------------------------------------------

#ifndef ImagerUnitH
#define ImagerUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>

#include "TcpImgClass.h"
#include "defines.h"
#include "NonExtractedLine.h"
#include "UdpDataSendClass.h"
#include "GWYMaker.h"
//---------------------------------------------------------------------------
class ImagerThread : public TThread
{
private:
	void ParseData(NonExtractedLine *myNonExtractedLine);
	void __fastcall SendPacket();
	void __fastcall AgainScan();

	void __fastcall UpdateImagesOnUi();
	int myCurrentPic;


	void __fastcall AddToFChart();
	double Fchart;
	int XFcahrt;

	void __fastcall AddToBChart();
	double Bchart;
	int XBchart;


	void __fastcall ResetCharts();
    int res;

	void __fastcall ShowCharts();

//	void __fastcall CheckTimerEvent(TObject *Sender);

protected:
	void __fastcall Execute();
	void __fastcall ShowImage();
//	void __fastcall DisableSave();

public:
    void __fastcall StopScan();
	__fastcall ImagerThread(bool CreateSuspended);
	void StopStartThread(bool start_stop);
	void CreateObjects();
	void ConfigThread();
	int BytesToInt(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,bool Bits);
	void IntiDataToImage(int my_image_index, int myResolution, int myPicIndex, int myLineNumber, bool myForwardBit, NonExtractedLine *myNonExtractedLine);
	void CreateImage(int my_image_index, int myResolution, int myPicIndex, bool myFlyBit, bool myForwardBit);
	int FindImage(int myPicIndex, bool myForwardBit, bool myFlyBit);
	int getTcpPacketLine(int myMode);
	void CloseImagerThread();
	void CreateImageFileDescriptor();
	void WriteLine(TFileStream *fs, AnsiString pm);

//	void TopoChartUpdate(int* Data, int resolution, bool FB);
	bool finish;

	UdpDataSendClass* myUdpDataSendClass;

//	TTimer *myTimer;


	TcpImgClass *Images;
	int PictureCount;
	int Count;
	int CurrentResolution;
	bool thread_started;
	bool finished;


	int PicIndex;
	int Resolution;
	int LineNumber;
	int images_index[10];
	int Image_Counter;
	int Line_Number[34];
    int MainInt[34];

	double TopoIndex;
	double TopoOffset;
	int TopoScale;

	bool counter;
	TFileStream *fss;

	int TopoLastLine;
	int TopoLine;
	int TopoCounter;

	int c;
	bool created;
	AnsiString ImageFileName;


    GWYMakerClass* myGWYMaker;
//	void SaveAll(bool final_save);
//	bool CreateFileDescryptor;
};
//---------------------------------------------------------------------------
#endif
