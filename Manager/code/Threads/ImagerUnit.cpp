﻿//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#include <fstream>
#pragma hdrstop

#include "ImagerUnit.h"
#include "globals.h"
#include "mainUnit.h"


#pragma package(smart_init)
#include<iostream>


//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ImagerThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
using namespace std;

__fastcall ImagerThread::ImagerThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	
}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::Execute()
{
	//---- Place thread code here ----
	created = false;
	mainForm->LogToFile("ImagerThread : Imager Execute ");
	NameThreadForDebugging(System::String(L"ImagerThread"));
	ConfigThread();
	CreateObjects();
	StopStartThread(true);
	created = true;
//	myTimer->Enabled = true;
//	mainForm->LogToFile("ImagerThread : myTimer->Enabled = true; ");
	while(thread_started){
		if(finish){
			mainForm->LogToFile("****************** stop or finish imaging ****************");
			thread_started = false;
			if(HaveLicense && mainForm->myControlPanelForm->StWatchStarted){
				mainForm->myControlPanelForm->stopwatch.Stop();
				double Total =  mainForm->myControlPanelForm->stopwatch.ElapsedMilliseconds;
				mainForm->LogToFile("Total Time = " + FloatToStr(Total));
				LicTable.WorkedTime = LicTable.WorkedTime + Total/1000;
				LicTable.RemainedTime = LicTable.TotalTime - LicTable.WorkedTime;
				mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("License"));
                mainForm->myControlPanelForm->StWatchStarted = false;
			}
			break;
		}
		else if(!(img_queue->isEmpty())){
			ParseData( &(img_queue->peek()) );
			img_queue->dequeue();
		}
		Sleep(10);
	}
	finish = false;
//	mainForm->LogToFile(" 1 - img_queue->isEmpty() = " + BoolToStr(img_queue->isEmpty() , true));
	while(!(img_queue->isEmpty())){
		img_queue->dequeue();
	}


//	mainForm->myTcpThread->ipwTcpServer->CleanupInstance();
//	mainForm->LogToFile(" 2 - img_queue->isEmpty() = " + BoolToStr(img_queue->isEmpty() , true));
	CloseImagerThread();

	this->Terminate();
	this->WaitFor();
	delete this;
}
//---------------------------------------------------------------------------

void ImagerThread::StopStartThread(bool start_stop)
{
	mainForm->LogToFile("ImagerThread : StopStartThread ");
	thread_started = start_stop;
}
//---------------------------------------------------------------------------

void ImagerThread::ConfigThread()
{
	mainForm->LogToFile("ImagerThread : ConfigThread ");
	thread_started = false;
	PictureCount = 0;
	Count = 0;
	CurrentResolution = 0;
	myUdpDataSendClass = NULL;
	finish = false;
	Image_Counter = 0;

//	myTimer = NULL;

	TopoCounter = 0;
	TopoLastLine = -1;
	TopoCounter = 0;


	Images = NULL;
//	CreateFileDescryptor = false;


	counter = 0;

	TopoIndex = mainForm->myOscForm->my_data_set[26].data_index;
	TopoOffset = mainForm->myOscForm->my_data_set[26].data_offset;
	TopoScale =  mainForm->myOscForm->my_data_set[26].data_scale;
}
//---------------------------------------------------------------------------

void ImagerThread::CreateObjects()
{
	mainForm->LogToFile("ImagerThread : CreateObjects ");
	if(!Images){
		Images = new TcpImgClass[IMAGE_INDEX_COUNT];
	}

	if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}

//	myTimer = new TTimer(NULL);
//	myTimer->Enabled = false;
//	myTimer->Interval = 1000;
}
//---------------------------------------------------------------------------

//void __fastcall ImagerThread::CheckTimerEvent(TObject *Sender)
//{
//	mainForm->LogToFile("ImagerThread: CheckTimerEvent");
//
//	mainForm->myControlPanelForm->EnableScanPanel(2);
//	myTimer->Enabled = false;
//}
////---------------------------------------------------------------------------

void ImagerThread::ParseData(NonExtractedLine *myNonExtractedLine)
{
	if(myNonExtractedLine->GetCreated()){

		// Forward or Backward
		bool ForwardBit;
		if(myNonExtractedLine->bytes[3] == 0xFF)
			ForwardBit = true;
		else if(myNonExtractedLine->bytes[3] == 0xBB)
			ForwardBit = false;

		//Picture Index
		PicIndex = BytesToInt(myNonExtractedLine->bytes[4], 0x00, 0x00, 0x00, false);

        //Line Number
		LineNumber = BytesToInt(myNonExtractedLine->bytes[9 ],
									myNonExtractedLine->bytes[10],
									myNonExtractedLine->bytes[11],
									myNonExtractedLine->bytes[12],
									false);

		//Pixel Resolution
		if(LineNumber == 0){
			Resolution = BytesToInt(myNonExtractedLine->bytes[5],
										myNonExtractedLine->bytes[6],
										myNonExtractedLine->bytes[7],
										myNonExtractedLine->bytes[8],
										false);
			CurrentResolution = Resolution;
		}

//		if(PicIndex == 0 && ForwardBit && LineNumber % 16 == 0){
//			mainForm->LogToFile("ImagerThread::ParseData ....... LineNumber == " + IntToStr(LineNumber) + " Peaked.");
//		}





		//Fly mode or not
		bool FlyBit =  myNonExtractedLine->bytes[13];

		int image_index;
		if(PicIndex == 3 && FlyBit)  //amp fly
			image_index = 30;
		else if(PicIndex == 4 && FlyBit) //phase fly
			image_index = 32;
		else
		   image_index = PicIndex*2;

		if(!ForwardBit)
			image_index = image_index +1;


		Line_Number[image_index] = LineNumber+1;
//		if(image_index == 33)
//			mainForm->LogToFile("Line_Number[33] = " + IntToStr(Line_Number[image_index]));

		if(!(PicIndex == 0 && FlyBit)){

			if (Image_Counter == 0) {
			   images_index[0] = image_index;
			   Image_Counter++;
			}
			else{
				bool image_exist = false;
				for(int i=0 ; i < Image_Counter ; i++){
					if (images_index[i] == image_index){
						image_exist = true;
						break;
					}
				}

				if(!image_exist){
					images_index[Image_Counter] = image_index;
					Image_Counter++;
				}
			}





	//		for(int i = 0 ; i < Image_Counter ; i++){
	//			mainForm->LogToFile("Image Index = " + IntToStr(images_index[i]));
	//		}

	//		mainForm->LogToFile("Image dequeue : PicIndex = " + IntToStr(PicIndex) + " _ " + "image_index = " + IntToStr(image_index) + " _ " + "LineNumber = " + IntToStr(LineNumber) + " _ " +  " Resolution = " + IntToStr(Resolution) + " _ " + "ForwardBit = " + BoolToStr(ForwardBit,true));

	//		if(ForwardBit)
	//			mainForm->LogToFile("dequeue " + IntToStr(PicIndex) +  " FF " + "Line " + IntToStr(LineNumber));
	//		else
	//			mainForm->LogToFile("dequeue " + IntToStr(PicIndex) + " BB " + "Line " + IntToStr(LineNumber));


	//		mainForm->LogToFile("LineNumber = " + IntToStr(LineNumber));
			if(LineNumber == 0){
	//			mainForm->LogToFile("LineNumber == 0");
	//			if(mainForm->AppMode == 6)
	//				mainForm->LogToFile("PicIndex : " + IntToStr(PicIndex) + " ForwardBit : " + IntToStr((int)ForwardBit));
				CreateImage(image_index,Resolution,PicIndex,FlyBit,ForwardBit);
				IntiDataToImage(image_index,Resolution,PicIndex,LineNumber,ForwardBit,myNonExtractedLine);
			}
			else//Data
				IntiDataToImage(image_index,Resolution,PicIndex,LineNumber,ForwardBit,myNonExtractedLine);

	//		if(ForwardBit)
	//			mainForm->LogToFile("create image " + IntToStr(PicIndex) +  " FF " + "Line " + IntToStr(LineNumber));
	//		else
	//			mainForm->LogToFile("create image" + IntToStr(PicIndex) + " BB " + "Line " + IntToStr(LineNumber));
		}
	}
}
//---------------------------------------------------------------------------

int ImagerThread::BytesToInt(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,bool Bits)
{
	unsigned char tmp1[4] ;
	int tmp = 0 ;
	memset(tmp1,0x00,4);

	//32 bits or 24 bits
	if(Bits){
		tmp1[1] = data0;
		tmp1[2] = data1;
		tmp1[3] = data2;
		memcpy((void *)&tmp , (void *)tmp1 , 4);
		tmp = tmp >> 8 ;
	}
	else{
		tmp1[0] = data0;
		tmp1[1] = data1;
		tmp1[2] = data2;
		tmp1[3] = data3;
		memcpy((void *)&tmp , (void *)tmp1 , 4);
	}
	return tmp;
}
//---------------------------------------------------------------------------

void ImagerThread::CreateImage(int my_image_index, int myResolution, int myPicIndex, bool myFlyBit, bool myForwardBit)
{
	//Init Image Class for new Image (received LineNumber=0)
	mainForm->LogToFile("ImagerThread::CreateImage");
	PictureCount++;
	Images[my_image_index].CreateImage(myResolution, my_image_index, myPicIndex, myFlyBit, myForwardBit);

	counter++;
	CreateImageFileDescriptor();


//	if(PictureCount == 1){
//		mainForm->myImageFrom->SaveButton->Enabled = true;
//		mainForm->myControlPanelForm->EnableScanPanel(2);
//	}

	mainForm->LogToFile("my_image_index = " + IntToStr(my_image_index));

}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::ResetCharts()
{
//	mainForm->LogToFile("ImagerThread::ResetCharts");
	mainForm->myImageFrom->TopoChart->BottomAxis->Automatic = false;
	mainForm->myImageFrom->TopoChart->BottomAxis->SetMinMax(0,res);
	mainForm->myImageFrom->TopoChart->AutoRepaint = false;
	mainForm->myImageFrom->TopoFWSeries->Clear();
	mainForm->myImageFrom->TopoBWSeries->Clear();
}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::ShowCharts()
{
//	mainForm->LogToFile("ImagerThread::ShowCharts");
	mainForm->myImageFrom->TopoChart->AutoRepaint = true;
	mainForm->myImageFrom->TopoChart->Refresh();
}
//---------------------------------------------------------------------------

void ImagerThread::IntiDataToImage(int my_image_index, int myResolution, int myPicIndex, int myLineNumber, bool myForwardBit, NonExtractedLine *myNonExtractedLine)
{
	if(Images[my_image_index].GetImageInitBit()){

		if(myPicIndex == 0){
			if(TopoLastLine != myLineNumber){
				TopoLastLine = myLineNumber;
				TopoCounter = 0;
	//			mainForm->LogToFile("myLineNumber = " + IntToStr(myLineNumber));
				res = myResolution;
				Synchronize(&ResetCharts);
				c = 0;
				Sleep(1);
			}
			else
				TopoCounter++;
		}


	//	AnsiString ttmp = IntToStr(myLineNumber) + " _ ";
	//	Images[my_image_index].fs->Write(ttmp.c_str(),ttmp.Length());
	//	Images[my_image_index].fs->Write(" ",1);



		int j;
		int Main_Int;
		for( int i=0; i<myResolution; i++){
			j = i*4;
			int t = myResolution * 4;
			if(myForwardBit){


				if(myPicIndex == 0){
					Main_Int = BytesToInt(myNonExtractedLine->bytes[j+HEADER_COUNT_IMAGE + 0],
										  myNonExtractedLine->bytes[j+HEADER_COUNT_IMAGE + 1],
										  myNonExtractedLine->bytes[j+HEADER_COUNT_IMAGE + 2],
										  myNonExtractedLine->bytes[j+HEADER_COUNT_IMAGE + 3],
										  Images[my_image_index].Get_24Bit());
					Main_Int = MAX_VALUE - Main_Int;
				}
				else{
					Main_Int = BytesToInt(myNonExtractedLine->bytes[HEADER_COUNT_IMAGE + j + 0],
										  myNonExtractedLine->bytes[HEADER_COUNT_IMAGE + j + 1],
										  myNonExtractedLine->bytes[HEADER_COUNT_IMAGE + j + 2],
										  myNonExtractedLine->bytes[HEADER_COUNT_IMAGE + j + 3],
										  Images[my_image_index].Get_24Bit());
				}
			}
			else{
				if(myPicIndex == 0){
					Main_Int = BytesToInt(myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 4],
										  myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 3],
										  myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 2],
										  myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 1],
										  Images[my_image_index].Get_24Bit());
					Main_Int = MAX_VALUE - Main_Int;
				}
				else{
					Main_Int = BytesToInt(myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 4],
										  myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 3],
										  myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 2],
										  myNonExtractedLine->bytes[t - j + HEADER_COUNT_IMAGE - 1],
										  Images[my_image_index].Get_24Bit());
				}
			}
			Images[my_image_index].Lines[myLineNumber].Pixels[i].Main = Main_Int; //bytes to int for a line of image


			//min and max line
			if(!(myPicIndex == 0) || !(mainForm->myScanPanelForm->One_D)){
				if(i == 0){
					Images[my_image_index].Lines[myLineNumber].MaxOfLine = Main_Int;
					Images[my_image_index].Lines[myLineNumber].MinOfLine = Main_Int;
				}
				else{
					if(Main_Int > Images[my_image_index].Lines[myLineNumber].MaxOfLine)
						Images[my_image_index].Lines[myLineNumber].MaxOfLine = Main_Int;
					else if(Main_Int < Images[my_image_index].Lines[myLineNumber].MinOfLine)
						Images[my_image_index].Lines[myLineNumber].MinOfLine = Main_Int;
				}
			}

			MainInt[my_image_index] = Main_Int;
//			if(my_image_index == 2)
//				mainForm->LogToFile(" Line Number = " + IntToStr(LineNumber) + " , Pixel = " + IntToStr(i) + " , Main = " + IntToStr(Main_Int));
			//SaveInt;
			Images[my_image_index].file->write((char *)&Main_Int, sizeof(Main_Int));


	//		AnsiString tmp = IntToStr(Main_Int);
	//		Images[my_image_index].fs->Write(tmp.c_str(),tmp.Length());
	//		Images[my_image_index].fs->Write(" ",1);

			if(myPicIndex == 0){
				if(myForwardBit){
					XFcahrt = i;
					Fchart = (double)Main_Int*TopoIndex + TopoOffset;
					Fchart = pow10l(TopoScale*3)*Fchart;
					Synchronize(&AddToFChart);
	//				mainForm->myImageFrom->TopoFWSeries->AddXY(i,(double)Main_Int*TopoIndex + TopoOffset);
				}
				else{
					XBchart = i;

					Bchart = (double)Main_Int*TopoIndex + TopoOffset;
					Bchart = pow10l(TopoScale*3)*Bchart;
					Synchronize(&AddToBChart);
	//				mainForm->myImageFrom->TopoBWSeries->AddXY(myResolution-i,(double)Main_Int*TopoIndex + TopoOffset);
				}
			}
		}

	//	Images[my_image_index].fs->Write("\r\n", 2);

		try{
			Images[my_image_index].UpdateColor(myLineNumber , myPicIndex);
		}
		catch(Exception &exception){
			ShowMessage("UpdateColor Exception : " + exception.Message);
	//		mainForm->LogToFile("UpdateColor Exception : " + exception.Message + " _ " + exception.StackTrace);
		}


		if(myPicIndex == 0 && TopoCounter == 1){
			TopoCounter = 0;
	//		mainForm->LogToFile("Update ****************************************");
			Synchronize(&ShowCharts);
		}

			//check end
			if(myLineNumber == CurrentResolution -1 ){
				Count++;
//				mainForm->LogToFile("ImagerThread::IntiDataToImage ..... End of Image " + Images[my_image_index].ImageName);
		//		PanelForm->Memo2->Lines->Add(IntToStr(Count) + " _ " + IntToStr(my_image_index) + " _ " + Images[my_image_index].ImageName + "end");
				if(Count == PictureCount) {
	//				SaveAll(true);
					SaveImages = true;
                    mainForm->myImageFrom->SaveButton->Visible = false;
					finish = true;

				}
			}
	}
//	myCurrentPic = my_image_index;
//	Synchronize(&UpdateImagesOnUi);
}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::AddToFChart()
{
	c++;
	mainForm->myImageFrom->TopoFWSeries->AddXY(XFcahrt,Fchart);
}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::AddToBChart()
{
	mainForm->myImageFrom->TopoBWSeries->AddXY(XBchart,Bchart);
}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::UpdateImagesOnUi()
{
//	Images[myCurrentPic].ShowAndSetImages();
}
//---------------------------------------------------------------------------

int ImagerThread::FindImage(int myPicIndex, bool myForwardBit, bool myFlyBit)
{
	mainForm->LogToFile("ImagerThread : FindImage ");
 for(int i=0; i<IMAGE_COUNT; i++)
	if(Images[i].GetImageInitBit()){
		if(Images[i].GetPicIndex() == myPicIndex && Images[i].GetForwardBit() == myForwardBit && Images[i].GetFlyBit() == myForwardBit)
			return i;
	}
	return -1;
}
//--------------------------------------------------------------------------

void __fastcall ImagerThread::SendPacket()
{
	mainForm->myUdpThread->SendBytes();
}
//---------------------------------------------------------------------------

int ImagerThread::getTcpPacketLine(int myMode)
{
	int ret = -1;
	switch (myMode) {
		case 1:{
			ret = (ControlPanelForm->resolution) * 3 * 2;
			break;
		}
		case 2:{
			ret = (ControlPanelForm->resolution) * 3 * 2;
			break;
		}
	//	case 3:
	//	case 4:
	//	case 5:
	//	case 6:
	//	case 7:
	//	case 8:
	//	case 9:
		default:{
			break;
		}
	}
	return ret;
}
//---------------------------------------------------------------------------


void ImagerThread::CloseImagerThread()
{
	mainForm->LogToFile("ImagerThread::CloseImagerThread");
//	mainForm->LogToFile("Image_Counter = " + IntToStr(Image_Counter));
	for (int j = 0 ; j < Image_Counter ; j++) {
//	  mainForm->LogToFile("images_number = " + IntToStr(j));
//	  mainForm->LogToFile("images_index[j] = " + IntToStr(images_index[j]));
//	  mainForm->LogToFile("Line_Number[images_index[j]] = " + IntToStr(Line_Number[images_index[j]]));
//	  mainForm->LogToFile("Resolution = " + IntToStr(Resolution));
//	  mainForm->LogToFile("start = " + IntToStr(Line_Number[images_index[j]]*Resolution+1));
//	  mainForm->LogToFile("stop = " + IntToStr(Resolution*Resolution+1));
	  for(int i = Line_Number[images_index[j]]*Resolution+1 ; i < (Resolution*Resolution+1) ; i++){
		Images[images_index[j]].file->write((char *)&MainInt[images_index[j]], sizeof(MainInt[images_index[j]]));
//		mainForm->LogToFile("LineNumber = " + IntToStr(i));
	  }
	}

//	Synchronize(&DisableSave);
//	for(int i=0; i<1000000; i++)
//		Application->ProcessMessages();

//	if(CreateFileDescryptor){
		for(int i=0; i<IMAGE_INDEX_COUNT; i++){
			if(Images[i].GetImageInitBit()){
				Images[i].file->close();
//				FileClose(Images[i].fs->Handle);
			}
		}
//	}

	img_queue->initQ();
	TThread::Synchronize(mainForm->myCommandCreatorThread,StopScan);
	Sleep(750);
	ImageFileName = ImageFileName.SubString(0,ImageFileName.Length()-4) + ".gwy";
	myGWYMaker = new GWYMakerClass();
	myGWYMaker->StartSaving(ImageFileName);
	delete myGWYMaker;

	if(mainForm->myOscForm->FlyError){
		mainForm->myOscForm->FlyError = false;
        ShowMessage("Please Readjust Z-Piezo position ");
	}

//    mainForm->myTcpThread->tcp_imaging = false;

//	mainForm->Scaning = false;
//	mainForm->myControlPanelForm->EnableScanPanel(true);
//	mainForm->myVideoForm->Enabled = true;
//	mainForm->myDynamicCurvePanelForm->Enabled = true;
	if(mainForm->myScanPanelForm->ContinuousCheckBox->Checked){
//		mainForm->LogToFile("Again");
		TThread::Synchronize(mainForm->myCommandCreatorThread,AgainScan);
	}
	else{
		mainForm->myControlPanelForm->AgainScan = false;
		mainForm->myCommandCreatorThread->myScan->Continues = false;

		mainForm->myKpfmFrm->Enabled = true;
		Synchronize(&ShowImage);

		mainForm->myControlPanelForm->EnableScanPanel(0);
        mainForm->GetSecure();
		for(int i=0; i<IMAGE_INDEX_COUNT; i++){
			if(Images[i].GetImageInitBit()){
				for(int j=0; j<Resolution; j++){
//						try{
							delete[] Images[i].Lines[j].Pixels;
							Images[i].Lines[j].created = false;
							Images[i].Lines[j].Pixels = NULL;
//						}
//						catch(Exception &exception){
//							ShowMessage("delete[] Images[i].Lines[j].Pixels : " + exception.Message + " _ " + exception.StackTrace + " , i , j = " + IntToStr(i) + " , " + IntToStr(j));
//						}
				}

			}

			if(Images[i].GetBitMapBit()){
				if(Images[i].GetImageInitBit()){
//					try{
						delete[] Images[i].Lines;
						Images[i].Lines = NULL;
						Images[i].SetImageInitBit(false);
//					}
//					catch(Exception &exception){
//						ShowMessage("Images[i].Lines : " + exception.Message + " _ " + exception.StackTrace + " , i  = " + IntToStr(i));
//					}
				}


//				try{
					delete Images[i].map;
					Images[i].map = NULL;
					Images[i].SetBitMapBit(false);
//				}
//				catch(Exception &exception){
//					ShowMessage("Images[i].map : " + exception.Message + " _ " + exception.StackTrace + " , i  = " + IntToStr(i));
//				}

			}

		}


		delete[] Images;
		Images = NULL;
	}

//	mainForm->LogToFile("ImagerThread::CloseImagerThread Finished");

}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::ShowImage()
{
	mainForm->LogToFile("ImagerThread::ShowImage");
    mainForm->myControlPanelForm->scan_selcet = false;
	mainForm->myImageFrom->ShowImages();

}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::StopScan()
{
	mainForm->LogToFile("ImagerThread::StopScan");
	ScanCommand.start = false;
	ScanCommand.set = true;
	ScanCommand.Changer = -2;
	mainForm->myCommandCreatorThread->scan_command = true;
//	mainForm->myCommandCreatorThread->StartScanClick(false,true,-2);
}
//---------------------------------------------------------------------------

void __fastcall ImagerThread::AgainScan()
{
	mainForm->LogToFile("ImagerThread::AgainScan");
	mainForm->myControlPanelForm->AgainScan = true;
	mainForm->myControlPanelForm->AdvBadgeButtonStartScanClick(NULL);
}
//---------------------------------------------------------------------------


void ImagerThread::CreateImageFileDescriptor()
{
	mainForm->LogToFile("ImagerThread::CreateImageFileDescriptor");
	switch(mainForm->AppMode){
		case 1:{
			bool user = false;
			if(counter == 6){
				AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
				AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
				AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
				AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;
				AnsiString ModeFolder = "Contact";
				AnsiString FinalFolderName = "";

				if( !DirectoryExists(PicFolder) ){
					AnsiString dir = PicFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/";

				if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
					AnsiString dir = PicFolder + "/" + ModeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder;

				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

				if(UserFolder != ""){
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
						if( CreateDirectoryA(dir.c_str(),NULL) == 0){
							mainForm->LogToFile("ImagerThread : CreateImageFileDescriptor : can not create : " + UserFolder);
							mainForm->myControlPanelForm->FolderCreated = false;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
								AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
								CreateDirectoryA(dir2.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						}
						else{
							user = true;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
								AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
								CreateDirectoryA(dir.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
						}
					}
					else{
						user = true;
						if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
							AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
							CreateDirectoryA(dir.c_str(),NULL);
						}
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					}
				}
				else{
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						CreateDirectoryA(dir.c_str(),NULL);
					}
					else{
					}
					FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
				}
//				mainForm->LogToFile(" ImagerThread : CreateImageFileDescriptor : " + FinalFolderName);
				ImageFileName = "";
				if(user)
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				else
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				fss = new TFileStream(ImageFileName, fmCreate);
				TDateTime DateTime = TDateTime::CurrentDateTime();

				WriteLine(fss,";Brisk Parameterfile");
				WriteLine(fss,"Version : 1.11");
				WriteLine(fss,"Date : " + DateTime.FormatString("dd") + "/" + DateTime.FormatString("mm") + "/" + DateTime.FormatString("yyyy"));
				WriteLine(fss,"Time : " + DateTime.FormatString("hh") + ":" + DateTime.FormatString("MM") + ":" + DateTime.FormatString("ss"));
				WriteLine(fss,"UserName : Brisk-AFM");
				WriteLine(fss,"Mode : Contact");
				WriteLine(fss,"SetPoint           :    " + IntToStr(mainForm->myApproachPanelForm->RefrenceApp));
				WriteLine(fss,"SetPointPhysUnit   : mV");
				WriteLine(fss,"FeedBackModus      : cmAFM");
				WriteLine(fss,"Bias               :   " + IntToStr(mainForm->myApproachPanelForm->BiasApp));
				WriteLine(fss,"BiasPhysUnit       : mV");
				WriteLine(fss,"Ki                 :   " + IntToStr(mainForm->myApproachPanelForm->KiFeedBack));
				WriteLine(fss,"Kp                 :   " + IntToStr(mainForm->myApproachPanelForm->KpApp));
				WriteLine(fss,"XScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"YScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"XPhysUnit  : µm");
				WriteLine(fss,"YPhysUnit  : µm");
				WriteLine(fss,"Speed      :  " + FloatToStr(mainForm->myScanPanelForm->Speed) + " ; " + "lines/sec");
				WriteLine(fss,"Angle      :  " + FloatToStr(mainForm->myScanPanelForm->Angle));
				WriteLine(fss,"xPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterX));
				WriteLine(fss,"xCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterY));
				WriteLine(fss,"dzdx       : dz/dx=0°");
				WriteLine(fss,"dzdy       : dz/dy=0°");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Fwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Bwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[2].ImageName + ".int");
				WriteLine(fss,"Caption    : Tb-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[0].data_index  * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[3].ImageName + ".int");
				WriteLine(fss,"Caption    : Tb-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[0].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[4].ImageName + ".int");
				WriteLine(fss,"Caption    : Lr-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[1].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[5].ImageName + ".int");
				WriteLine(fss,"Caption    : Lr-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[1].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				FileClose(fss->Handle);
				delete fss;

			}
			break;
		}

		case 2:{
			bool user = false;
			if(counter == 6){
				AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
				AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
				AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
				AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;
				AnsiString ModeFolder = "NonContact";
				AnsiString FinalFolderName = "";

				if( !DirectoryExists(PicFolder) ){
					AnsiString dir = PicFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/";

				if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
					AnsiString dir = PicFolder + "/" + ModeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder;

				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

				if(UserFolder != ""){
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
						if( CreateDirectoryA(dir.c_str(),NULL) == 0){
							mainForm->LogToFile("ImagerThread : CreateImageFileDescriptor : can not create : " + UserFolder);
							mainForm->myControlPanelForm->FolderCreated = false;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
								AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
								CreateDirectoryA(dir2.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						}
						else{
							user = true;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
								AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
								CreateDirectoryA(dir.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
						}
					}
					else{
						user = true;
						if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
							AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
							CreateDirectoryA(dir.c_str(),NULL);
						}
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					}
				}
				else{
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						CreateDirectoryA(dir.c_str(),NULL);
					}
					else{
					}
					FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
				}
//				mainForm->LogToFile(" ImagerThread : CreateImageFileDescriptor : " + FinalFolderName);
				ImageFileName = "";
				if(user)
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				else
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				fss = new TFileStream(ImageFileName, fmCreate);
				TDateTime DateTime = TDateTime::CurrentDateTime();

				WriteLine(fss,";Brisk Parameterfile");
				WriteLine(fss,"Version : 1.11");
				WriteLine(fss,"Date : " + DateTime.FormatString("dd") + "/" + DateTime.FormatString("mm") + "/" + DateTime.FormatString("yyyy"));
				WriteLine(fss,"Time : " + DateTime.FormatString("hh") + ":" + DateTime.FormatString("MM") + ":" + DateTime.FormatString("ss"));
				WriteLine(fss,"UserName : Brisk-AFM");
				WriteLine(fss,"Mode : Non-Contact");
				WriteLine(fss,"Dnc_From           : " + IntToStr(mainForm->myDynamicCurvePanelForm->From_Val) + " Hz");
				WriteLine(fss,"Dnc_To             : " + IntToStr(mainForm->myDynamicCurvePanelForm->To_Val) + " Hz");
				WriteLine(fss,"Dnc_Use            : " + IntToStr(mainForm->myDynamicCurvePanelForm->Use_Val) + " Hz");
				WriteLine(fss,"Dnc_Drive          : " + IntToStr(mainForm->myDynamicCurvePanelForm->Drive_Val) + " mV");
				WriteLine(fss,"Dnc_PeakAmp        : " + mainForm->myDynamicCurvePanelForm->MaxAllAdvEdit->Text);
				WriteLine(fss,"Dnc_MaxAmp         : " + mainForm->myDynamicCurvePanelForm->MaxAdvEdit->Text + " mV");
				WriteLine(fss,"SetPoint           : " + IntToStr(mainForm->myDynamicCurvePanelForm->SetPoint_Val) + "%");
				WriteLine(fss,"FeedBackModus      : ncmAFM");
				WriteLine(fss,"Bias               :   " + IntToStr(mainForm->myApproachPanelForm->BiasApp));
				WriteLine(fss,"BiasPhysUnit       : mV");
				WriteLine(fss,"Ki                 :   " + IntToStr(mainForm->myApproachPanelForm->KiFeedBack));
				WriteLine(fss,"Kp                 :   " + IntToStr(mainForm->myApproachPanelForm->KpApp));
				WriteLine(fss,"XScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"YScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"XPhysUnit  : µm");
				WriteLine(fss,"YPhysUnit  : µm");
				WriteLine(fss,"Speed      :  " + FloatToStr(mainForm->myScanPanelForm->Speed) + " ; " + "lines/sec");
				WriteLine(fss,"Angle      :  " + FloatToStr(mainForm->myScanPanelForm->Angle));
				WriteLine(fss,"xPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterX));
				WriteLine(fss,"xCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterY));
				WriteLine(fss,"dzdx       : dz/dx=0°");
				WriteLine(fss,"dzdy       : dz/dy=0°");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Fwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Bwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index)* pow10l(9));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[6].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[7].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[8].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[9].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				FileClose(fss->Handle);
				delete fss;


			}
			break;
		}

		case 3:{
			bool user = false;
			if(counter == 10){
				AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
				AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
				AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
				AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;
				AnsiString ModeFolder = "EFM";
				AnsiString FinalFolderName = "";

				if( !DirectoryExists(PicFolder) ){
					AnsiString dir = PicFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/";

				if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
					AnsiString dir = PicFolder + "/" + ModeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder;

				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

				if(UserFolder != ""){
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
						if( CreateDirectoryA(dir.c_str(),NULL) == 0){
							mainForm->LogToFile("ImagerThread : CreateImageFileDescriptor : can not create : " + UserFolder);
							mainForm->myControlPanelForm->FolderCreated = false;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
								AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
								CreateDirectoryA(dir2.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						}
						else{
							user = true;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
								AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
								CreateDirectoryA(dir.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
						}
					}
					else{
						user = true;
						if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
							AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
							CreateDirectoryA(dir.c_str(),NULL);
						}
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					}
				}
				else{
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						CreateDirectoryA(dir.c_str(),NULL);
					}
					else{
					}
					FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
				}
//				mainForm->LogToFile(" ImagerThread : CreateImageFileDescriptor : " + FinalFolderName);
				ImageFileName = "";
				if(user)
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				else
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				fss = new TFileStream(ImageFileName, fmCreate);
				TDateTime DateTime = TDateTime::CurrentDateTime();

				WriteLine(fss,";Brisk Parameterfile");
				WriteLine(fss,"Version : 1.11");
				WriteLine(fss,"Date : " + DateTime.FormatString("dd") + "/" + DateTime.FormatString("mm") + "/" + DateTime.FormatString("yyyy"));
				WriteLine(fss,"Time : " + DateTime.FormatString("hh") + ":" + DateTime.FormatString("MM") + ":" + DateTime.FormatString("ss"));
				WriteLine(fss,"UserName : Brisk-AFM");
				WriteLine(fss,"Mode : EFM");
				WriteLine(fss,"Dnc_From           : " + IntToStr(mainForm->myDynamicCurvePanelForm->From_Val) + " Hz");
				WriteLine(fss,"Dnc_To             : " + IntToStr(mainForm->myDynamicCurvePanelForm->To_Val) + " Hz");
				WriteLine(fss,"Dnc_Use            : " + IntToStr(mainForm->myDynamicCurvePanelForm->Use_Val) + " Hz");
				WriteLine(fss,"Dnc_Drive          : " + IntToStr(mainForm->myDynamicCurvePanelForm->Drive_Val) + " mV");
				WriteLine(fss,"Dnc_PeakAmp        : " + mainForm->myDynamicCurvePanelForm->MaxAllAdvEdit->Text);
				WriteLine(fss,"Dnc_MaxAmp         : " + mainForm->myDynamicCurvePanelForm->MaxAdvEdit->Text + " mV");
				WriteLine(fss,"SetPoint           : " + IntToStr(mainForm->myDynamicCurvePanelForm->SetPoint_Val) + "%");
				WriteLine(fss,"FeedBackModus      : ncmAFM");
				WriteLine(fss,"Bias               :   " + IntToStr(mainForm->myApproachPanelForm->BiasApp));
				WriteLine(fss,"BiasPhysUnit       : mV");
				WriteLine(fss,"Ki                 :   " + IntToStr(mainForm->myApproachPanelForm->KiFeedBack));
				WriteLine(fss,"Kp                 :   " + IntToStr(mainForm->myApproachPanelForm->KpApp));
				WriteLine(fss,"XScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"YScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"XPhysUnit  : µm");
				WriteLine(fss,"YPhysUnit  : µm");
				WriteLine(fss,"Speed      :  " + FloatToStr(mainForm->myScanPanelForm->Speed) + " ; " + "lines/sec");
				WriteLine(fss,"Angle      :  " + FloatToStr(mainForm->myScanPanelForm->Angle));
				WriteLine(fss,"xPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterX));
				WriteLine(fss,"xCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterY));
				WriteLine(fss,"dzdx       : dz/dx=0°");
				WriteLine(fss,"dzdy       : dz/dy=0°");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Forward");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Bwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[6].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[7].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[8].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[9].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[30].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Fly-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[31].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Fly-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[32].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Fly-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[33].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Fly-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				FileClose(fss->Handle);
				delete fss;

			}
			break;
		}

		case 4:{
			bool user = false;
			if(counter == 10){
				AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
				AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
				AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
				AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;
				AnsiString ModeFolder = "MFM";
				AnsiString FinalFolderName = "";

				if( !DirectoryExists(PicFolder) ){
					AnsiString dir = PicFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/";

				if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
					AnsiString dir = PicFolder + "/" + ModeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder;

				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

				if(UserFolder != ""){
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
						if( CreateDirectoryA(dir.c_str(),NULL) == 0){
							mainForm->LogToFile("ImagerThread : CreateImageFileDescriptor : can not create : " + UserFolder);
							mainForm->myControlPanelForm->FolderCreated = false;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
								AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
								CreateDirectoryA(dir2.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						}
						else{
							user = true;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
								AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
								CreateDirectoryA(dir.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
						}
					}
					else{
						user = true;
						if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
							AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
							CreateDirectoryA(dir.c_str(),NULL);
						}
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					}
				}
				else{
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						CreateDirectoryA(dir.c_str(),NULL);
					}
					else{
					}
					FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
				}
//				mainForm->LogToFile(" ImagerThread : CreateImageFileDescriptor : " + FinalFolderName);
				ImageFileName = "";
				if(user)
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				else
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				fss = new TFileStream(ImageFileName, fmCreate);
				TDateTime DateTime = TDateTime::CurrentDateTime();

				WriteLine(fss,";Brisk Parameterfile");
				WriteLine(fss,"Version : 1.11");
				WriteLine(fss,"Date : " + DateTime.FormatString("dd") + "/" + DateTime.FormatString("mm") + "/" + DateTime.FormatString("yyyy"));
				WriteLine(fss,"Time : " + DateTime.FormatString("hh") + ":" + DateTime.FormatString("MM") + ":" + DateTime.FormatString("ss"));
				WriteLine(fss,"UserName : Brisk-AFM");
				WriteLine(fss,"Mode : MFM");
				WriteLine(fss,"Dnc_From           : " + IntToStr(mainForm->myDynamicCurvePanelForm->From_Val) + " Hz");
				WriteLine(fss,"Dnc_To             : " + IntToStr(mainForm->myDynamicCurvePanelForm->To_Val) + " Hz");
				WriteLine(fss,"Dnc_Use            : " + IntToStr(mainForm->myDynamicCurvePanelForm->Use_Val) + " Hz");
				WriteLine(fss,"Dnc_Drive          : " + IntToStr(mainForm->myDynamicCurvePanelForm->Drive_Val) + " mV");
				WriteLine(fss,"Dnc_PeakAmp        : " + mainForm->myDynamicCurvePanelForm->MaxAllAdvEdit->Text);
				WriteLine(fss,"Dnc_MaxAmp         : " + mainForm->myDynamicCurvePanelForm->MaxAdvEdit->Text + " mV");
				WriteLine(fss,"SetPoint           : " + IntToStr(mainForm->myDynamicCurvePanelForm->SetPoint_Val) + "%");
				WriteLine(fss,"FeedBackModus      : ncmAFM");
				WriteLine(fss,"Bias               :   " + IntToStr(mainForm->myApproachPanelForm->BiasApp));
				WriteLine(fss,"BiasPhysUnit       : mV");
				WriteLine(fss,"Ki                 :   " + IntToStr(mainForm->myApproachPanelForm->KiFeedBack));
				WriteLine(fss,"Kp                 :   " + IntToStr(mainForm->myApproachPanelForm->KpApp));
				WriteLine(fss,"XScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"YScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"XPhysUnit  : µm");
				WriteLine(fss,"YPhysUnit  : µm");
				WriteLine(fss,"Speed      :  " + FloatToStr(mainForm->myScanPanelForm->Speed) + " ; " + "lines/sec");
				WriteLine(fss,"Angle      :  " + FloatToStr(mainForm->myScanPanelForm->Angle));
				WriteLine(fss,"xPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterX));
				WriteLine(fss,"xCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterY));
				WriteLine(fss,"dzdx       : dz/dx=0°");
				WriteLine(fss,"dzdy       : dz/dy=0°");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Fwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Bwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[6].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[7].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[8].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[9].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[30].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Fly-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[31].ImageName + ".int");
				WriteLine(fss,"Caption    : Amp-Fly-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[32].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Fly-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[33].ImageName + ".int");
				WriteLine(fss,"Caption    : Phase-Fly-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
				WriteLine(fss,"PhysUnit   : °");
				WriteLine(fss,"FileDescEnd");

				FileClose(fss->Handle);
				delete fss;

			}
			break;
		}

		case 5:{
			bool user = false;
			if(counter == 6){
				AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
				AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
				AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
				AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;
				AnsiString ModeFolder = "ForceSpec";
				AnsiString FinalFolderName = "";

				if( !DirectoryExists(PicFolder) ){
					AnsiString dir = PicFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/";

				if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
					AnsiString dir = PicFolder + "/" + ModeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder;

				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

				if(UserFolder != ""){
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
						if( CreateDirectoryA(dir.c_str(),NULL) == 0){
							mainForm->LogToFile("ImagerThread : CreateImageFileDescriptor : can not create : " + UserFolder);
							mainForm->myControlPanelForm->FolderCreated = false;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
								AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
								CreateDirectoryA(dir2.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						}
						else{
							user = true;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
								AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
								CreateDirectoryA(dir.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
						}
					}
					else{
						user = true;
						if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
							AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
							CreateDirectoryA(dir.c_str(),NULL);
						}
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					}
				}
				else{
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						CreateDirectoryA(dir.c_str(),NULL);
					}
					else{
					}
					FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
				}
				mainForm->LogToFile(" ImagerThread : CreateImageFileDescriptor : " + FinalFolderName);
				ImageFileName = "";
				if(user)
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				else
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				fss = new TFileStream(ImageFileName, fmCreate);
				TDateTime DateTime = TDateTime::CurrentDateTime();

				WriteLine(fss,";Brisk Parameterfile");
				WriteLine(fss,"Version : 1.11");
				WriteLine(fss,"Date : " + DateTime.FormatString("dd") + "/" + DateTime.FormatString("mm") + "/" + DateTime.FormatString("yyyy"));
				WriteLine(fss,"Time : " + DateTime.FormatString("hh") + ":" + DateTime.FormatString("MM") + ":" + DateTime.FormatString("ss"));
				WriteLine(fss,"UserName : Brisk-AFM");
				WriteLine(fss,"Mode : Force Spectroscopy");
				WriteLine(fss,"SetPoint           :    " + IntToStr(mainForm->myApproachPanelForm->RefrenceApp));
				WriteLine(fss,"SetPointPhysUnit   : mV");
				WriteLine(fss,"FeedBackModus      : cmAFM");
				WriteLine(fss,"Bias               :   " + IntToStr(mainForm->myApproachPanelForm->BiasApp));
				WriteLine(fss,"BiasPhysUnit       : mV");
				WriteLine(fss,"Ki                 :   " + IntToStr(mainForm->myApproachPanelForm->KiFeedBack));
				WriteLine(fss,"Kp                 :   " + IntToStr(mainForm->myApproachPanelForm->KpApp));
				WriteLine(fss,"XScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"YScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"XPhysUnit  : µm");
				WriteLine(fss,"YPhysUnit  : µm");
				WriteLine(fss,"Speed      :  " + FloatToStr(mainForm->myScanPanelForm->Speed) + " ; " + "lines/sec");
				WriteLine(fss,"Angle      :  " + FloatToStr(mainForm->myScanPanelForm->Angle));
				WriteLine(fss,"xPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterX));
				WriteLine(fss,"xCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterY));
				WriteLine(fss,"dzdx       : dz/dx=0°");
				WriteLine(fss,"dzdy       : dz/dy=0°");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Fwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Bwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[2].ImageName + ".int");
				WriteLine(fss,"Caption    : Tb-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[0].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[3].ImageName + ".int");
				WriteLine(fss,"Caption    : Tb-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[0].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[4].ImageName + ".int");
				WriteLine(fss,"Caption    : Lr-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[1].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[5].ImageName + ".int");
				WriteLine(fss,"Caption    : Lr-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[1].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				FileClose(fss->Handle);
				delete fss;

			}
			break;
		}

		case 6:{
			bool user = false;
			if(counter == 6){
				AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
				AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
				AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
				AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;
				AnsiString ModeFolder = "KPFM";
				AnsiString FinalFolderName = "";

				if( !DirectoryExists(PicFolder) ){
					AnsiString dir = PicFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/";

				if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
					AnsiString dir = PicFolder + "/" + ModeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder;

				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

				if(UserFolder != ""){
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
						if( CreateDirectoryA(dir.c_str(),NULL) == 0){
							mainForm->LogToFile("ImagerThread : CreateImageFileDescriptor : can not create : " + UserFolder);
							mainForm->myControlPanelForm->FolderCreated = false;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
								AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
								CreateDirectoryA(dir2.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						}
						else{
							user = true;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
								AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
								CreateDirectoryA(dir.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
						}
					}
					else{
						user = true;
						if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
							AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
							CreateDirectoryA(dir.c_str(),NULL);
						}
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					}
				}
				else{
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						CreateDirectoryA(dir.c_str(),NULL);
					}
					else{
					}
					FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
				}
//				mainForm->LogToFile(" ImagerThread : CreateImageFileDescriptor : " + FinalFolderName);
				ImageFileName = "";
				if(user)
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				else
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				fss = new TFileStream(ImageFileName, fmCreate);
				TDateTime DateTime = TDateTime::CurrentDateTime();

				WriteLine(fss,";Brisk Parameterfile");
				WriteLine(fss,"Version : 1.11");
				WriteLine(fss,"Date : " + DateTime.FormatString("dd") + "/" + DateTime.FormatString("mm") + "/" + DateTime.FormatString("yyyy"));
				WriteLine(fss,"Time : " + DateTime.FormatString("hh") + ":" + DateTime.FormatString("MM") + ":" + DateTime.FormatString("ss"));
				WriteLine(fss,"UserName : Brisk-AFM");
				WriteLine(fss,"Mode : KPFM");
				WriteLine(fss,"Dnc_From           : " + IntToStr(mainForm->myDynamicCurvePanelForm->From_Val) + " Hz");
				WriteLine(fss,"Dnc_To             : " + IntToStr(mainForm->myDynamicCurvePanelForm->To_Val) + " Hz");
				WriteLine(fss,"Dnc_Use            : " + IntToStr(mainForm->myDynamicCurvePanelForm->Use_Val) + " Hz");
				WriteLine(fss,"Dnc_Drive          : " + IntToStr(mainForm->myDynamicCurvePanelForm->Drive_Val) + " mV");
				WriteLine(fss,"Dnc_PeakAmp        : " + mainForm->myDynamicCurvePanelForm->MaxAllAdvEdit->Text);
				WriteLine(fss,"Dnc_MaxAmp         : " + mainForm->myDynamicCurvePanelForm->MaxAdvEdit->Text + " mV");
				WriteLine(fss,"SetPoint           : " + IntToStr(mainForm->myDynamicCurvePanelForm->SetPoint_Val) + "%");
				WriteLine(fss,"FeedBackModus      : ncmAFM");
				WriteLine(fss,"Bias               :   " + IntToStr(mainForm->myApproachPanelForm->BiasApp));
				WriteLine(fss,"BiasPhysUnit       : mV");
				WriteLine(fss,"Ki                 :   " + IntToStr(mainForm->myApproachPanelForm->KiFeedBack));
				WriteLine(fss,"Kp                 :   " + IntToStr(mainForm->myApproachPanelForm->KpApp));
				WriteLine(fss,"XScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"YScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"XPhysUnit  : µm");
				WriteLine(fss,"YPhysUnit  : µm");
				WriteLine(fss,"Speed      :  " + FloatToStr(mainForm->myScanPanelForm->Speed) + " ; " + "lines/sec");
				WriteLine(fss,"Angle      :  " + FloatToStr(mainForm->myScanPanelForm->Angle));
				WriteLine(fss,"xPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterX));
				WriteLine(fss,"xCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterY));
				WriteLine(fss,"dzdx       : dz/dx=0°");
				WriteLine(fss,"dzdy       : dz/dy=0°");

				if(mainForm->myKpfmFrm->lia){           //LIA2
                    WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
					WriteLine(fss,"Caption    : Topo-Fwd");
					WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
					WriteLine(fss,"PhysUnit   : nm");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
					WriteLine(fss,"Caption    : Topo-Bwd");
					WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
					WriteLine(fss,"PhysUnit   : nm");
					WriteLine(fss,"FileDescEnd");

                    WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[2].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-2we-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[15].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[3].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-2we-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[15].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[4].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-2we-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[16].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[5].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-2we-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[16].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[6].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[7].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[8].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[9].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[10].ImageName + ".int");
					WriteLine(fss,"Caption    : Bias-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[17].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[11].ImageName + ".int");
					WriteLine(fss,"Caption    : Bias-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[17].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[12].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia2X-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[11].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[13].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia2X-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[11].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[14].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia2Y-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[12].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[15].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia2Y-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[12].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");
				}
				else{                                   //LIA1
					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
					WriteLine(fss,"Caption    : Topo-Fwd");
					WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
					WriteLine(fss,"PhysUnit   : nm");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
					WriteLine(fss,"Caption    : Topo-Bwd");
					WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
					WriteLine(fss,"PhysUnit   : nm");
					WriteLine(fss,"FileDescEnd");

                    WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[2].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-we-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[13].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[3].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-we-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[13].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[4].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-we-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[14].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[5].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-we-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[14].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[6].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[7].ImageName + ".int");
					WriteLine(fss,"Caption    : Amp-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[6].data_index * pow10l(3)));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[8].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[9].ImageName + ".int");
					WriteLine(fss,"Caption    : Phase-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[7].data_index));
					WriteLine(fss,"PhysUnit   : °");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[10].ImageName + ".int");
					WriteLine(fss,"Caption    : Bias-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[17].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[11].ImageName + ".int");
					WriteLine(fss,"Caption    : Bias-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[17].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[12].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia1X-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[9].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[13].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia1X-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[9].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[14].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia1Y-Fwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[10].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");

					WriteLine(fss,"FileDescBegin");
					WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[15].ImageName + ".int");
					WriteLine(fss,"Caption    : Lia1Y-Bwd");
					WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[10].data_index));
					WriteLine(fss,"PhysUnit   : mV");
					WriteLine(fss,"FileDescEnd");
				}

				FileClose(fss->Handle);
				delete fss;
			}
			break;
		}

		case 7:{
			bool user = false;
			if(counter == 6){
				AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
				AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
				AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
				AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;
				AnsiString ModeFolder = "Lithography";
				AnsiString FinalFolderName = "";

				if( !DirectoryExists(PicFolder) ){
					AnsiString dir = PicFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/";

				if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
					AnsiString dir = PicFolder + "/" + ModeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder;

				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

				if(UserFolder != ""){
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
						if( CreateDirectoryA(dir.c_str(),NULL) == 0){
							mainForm->LogToFile("ImagerThread : CreateImageFileDescriptor : can not create : " + UserFolder);
							mainForm->myControlPanelForm->FolderCreated = false;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
								AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
								CreateDirectoryA(dir2.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						}
						else{
							user = true;
							if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
								AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
								CreateDirectoryA(dir.c_str(),NULL);
							}
							FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
						}
					}
					else{
						user = true;
						if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
							AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
							CreateDirectoryA(dir.c_str(),NULL);
						}
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					}
				}
				else{
					if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
						AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
						CreateDirectoryA(dir.c_str(),NULL);
					}
					else{
					}
					FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
				}
//				mainForm->LogToFile(" ImagerThread : CreateImageFileDescriptor : " + FinalFolderName);
				ImageFileName = "";
				if(user)
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				else
					ImageFileName = FinalFolderName + "/" + TimeFolder + "_" + "images" + ".txt";
				fss = new TFileStream(ImageFileName, fmCreate);
				TDateTime DateTime = TDateTime::CurrentDateTime();

				WriteLine(fss,";Brisk Parameterfile");
				WriteLine(fss,"Version : 1.11");
				WriteLine(fss,"Date : " + DateTime.FormatString("dd") + "/" + DateTime.FormatString("mm") + "/" + DateTime.FormatString("yyyy"));
				WriteLine(fss,"Time : " + DateTime.FormatString("hh") + ":" + DateTime.FormatString("MM") + ":" + DateTime.FormatString("ss"));
				WriteLine(fss,"UserName : Brisk-AFM");
				WriteLine(fss,"Mode : Lithography");
				WriteLine(fss,"SetPoint           :    " + IntToStr(mainForm->myApproachPanelForm->RefrenceApp));
				WriteLine(fss,"SetPointPhysUnit   : mV");
				WriteLine(fss,"FeedBackModus      : cmAFM");
				WriteLine(fss,"Bias               :   " + IntToStr(mainForm->myApproachPanelForm->BiasApp));
				WriteLine(fss,"BiasPhysUnit       : mV");
				WriteLine(fss,"Ki                 :   " + IntToStr(mainForm->myApproachPanelForm->KiFeedBack));
				WriteLine(fss,"Kp                 :   " + IntToStr(mainForm->myApproachPanelForm->KpApp));
				WriteLine(fss,"XScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"YScanRange :    " + FloatToStr(mainForm->myScanPanelForm->Range));
				WriteLine(fss,"XPhysUnit  : µm");
				WriteLine(fss,"YPhysUnit  : µm");
				WriteLine(fss,"Speed      :  " + FloatToStr(mainForm->myScanPanelForm->Speed) + " ; " + "lines/sec");
				WriteLine(fss,"Angle      :  " + FloatToStr(mainForm->myScanPanelForm->Angle));
				WriteLine(fss,"xPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yPixel     :    " + IntToStr(mainForm->myScanPanelForm->Resolution));
				WriteLine(fss,"yCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterX));
				WriteLine(fss,"xCenter    :    " + FloatToStr(mainForm->myScanPanelForm->CenterY));
				WriteLine(fss,"dzdx       : dz/dx=0°");
				WriteLine(fss,"dzdy       : dz/dy=0°");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[0].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Fwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[1].ImageName + ".int");
				WriteLine(fss,"Caption    : Topo-Bwd");
				WriteLine(fss,"Scale      : " +  FloatToStr(mainForm->myOscForm->my_data_set[3].data_index * pow10l(9)));
				WriteLine(fss,"PhysUnit   : nm");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[2].ImageName + ".int");
				WriteLine(fss,"Caption    : Tb-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[0].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[3].ImageName + ".int");
				WriteLine(fss,"Caption    : Tb-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[0].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[4].ImageName + ".int");
				WriteLine(fss,"Caption    : Lr-Fwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[1].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				WriteLine(fss,"FileDescBegin");
				WriteLine(fss,"FileName   : " + TimeFolder + "_" + Images[5].ImageName + ".int");
				WriteLine(fss,"Caption    : Lr-Bwd");
				WriteLine(fss,"Scale      : " + FloatToStr(mainForm->myOscForm->my_data_set[1].data_index * pow10l(3)));
				WriteLine(fss,"PhysUnit   : mV");
				WriteLine(fss,"FileDescEnd");

				FileClose(fss->Handle);
				delete fss;

			}
			break;
		}
		default:{
			break;
		}
	}

//	CreateFileDescryptor = true;

}
//---------------------------------------------------------------------------

void ImagerThread::WriteLine(TFileStream *fs, AnsiString pm)
{
//	mainForm->LogToFile("ImagerThread::WriteLine");
	fs->Write(pm.c_str(),pm.Length());
	fs->Write("\r\n", 2);
}
//---------------------------------------------------------------------------

//void ImagerThread::SaveAll(bool final_save)
//{
//
//
//	for(int i=0; i<IMAGE_INDEX_COUNT; i++){
//		if( Images[i].GetImageInitBit() ){
//			//create file
//			if( !(Images[i].GetFileBit()) )
//				Images[i].CreateFiles();
//
//			//save Int
//			for(int j=0; j<CurrentResolution; j++){
//				if(Images[i].Lines[j].created){
//					for(int z=0; z<CurrentResolution; z++){
//						Images[i].file->write((char *)&(Images[i].Lines[j].Pixels[z].M), 4);
//					}
//				}
//				else{
//					for(int z=0; z<CurrentResolution; z++){
//						int m = 8388608;
//						Images[i].file->write((char *)(m), 4);
//					}
//				}
//			}
//
//
//			//save Image
//			try{
//				Images[i].map->SaveToFile(Images[i].ImageFileName);
//			}
//			catch(Exception &exception){
//				ShowMessage("first save image Exception : " + exception.Message + " _ " + exception.StackTrace);
//			}
//		}
//	}
////	if(!CreateFileDescryptor && final_save)
//	CreateImageFileDescriptor();
//	Synchronize(&EnableSave);
//}
////---------------------------------------------------------------------------
//
//void __fastcall ImagerThread::EnableSave()
//{
//	mainForm->myImageFrom->SaveButton->Enabled = true;
//}
////---------------------------------------------------------------------------
//
//void __fastcall ImagerThread::DisableSave()
//{
//	mainForm->myImageFrom->SaveButton->Enabled = false;
//}
////---------------------------------------------------------------------------





