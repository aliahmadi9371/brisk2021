﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "mainUnit.h"
#include "TcpImgClass.h"


#include <fstream>
#include "Pallete_256.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;
__fastcall TcpImgClass::TcpImgClass()
{
	InitClass();
}
//---------------------------------------------------------------------------

TcpImgClass::~TcpImgClass()
{
}
//---------------------------------------------------------------------------

void TcpImgClass::InitClass()
{
//	mainForm->LogToFile("TcpImgClass::InitClass");
	Resolution = 0;
	PicIndex = 0;
	FlyBit = false;
	ForwardBit = false;
	ImageInitBit = false;
	ImageSetBit = false;
	BitMapBit = false;
	ActiveBit = true;
	StopImaging = false;

	LastLine = -1;
//	ptrPalette = NULL;

	FileBit = false;

	Lines = NULL;
	map = NULL;

//	ptr = NULL;
//	ToPoList = new TList;

}
//---------------------------------------------------------------------------

void TcpImgClass::CreateImage(int resolution, int image_index, int pic_index, bool fly, bool forward)
{
	mainForm->LogToFile("TcpImgClass::CreateImage");
	SetResolution(resolution);
	SetPicIndex(pic_index);
	SetFlyBit(fly);
	SetForwardBit(forward);
	Set24BitsFromPacket(pic_index);
	Setimage_index(image_index);
	SetImageName(SetName(image_index));
	//	PaletteCreate(12,0,24,236,248,136);

	InitOneImage(resolution);
	CreateBitMaps(resolution);

	for(int i=0; i<resolution; i++){
		Lines[i].InitOneLine(resolution);
		for(int j=0; j<resolution; j++)
			Lines[i].Pixels[j].Main = 0;

	}
	mainForm->LogToFile("CreateImage " + IntToStr(image_index));

	SetImageInitBit(true);
}
//---------------------------------------------------------------------------

void TcpImgClass::InitOneImage(int myValue)
{
	mainForm->LogToFile("TcpImgClass::InitOneImage");
	Lines = new TcpLineClass[myValue];
}
//---------------------------------------------------------------------------

void TcpImgClass::UpdateColor(int myValue, int myIndex)
{
//	mainForm->LogToFile("TcpImgClass::UpdateColor");
	int Save;
	if(GetResolution() <= 512)
		Save = 1;
	else
	 	Save = GetResolution()/64;
//	if (Save < 2)
//		Save = 1;
//	else if(Save >= 2 && Save<=8)
//		Save = 2;
//	else if (Save == 16)
//		Save = 4;
//	else
//		Save = 8;
//
//	if(mainForm->AppMode == 3 || mainForm->AppMode == 4)
//		Save = Save * 4;

	int Max;
	int Min;
	bool MaxChange = false;
	bool MinChange = false;

	//new line


	if((image_index == 0 || image_index == 1)){
		if( (mainForm->myScanPanelForm->Two_D) && myValue != 0 /*&& ((myValue+1) % Save == 0)*/){
	//		mainForm->LogToFile("2D_leveling for image index " + IntToStr(image_index) + " Line number " + IntToStr(myValue));
			TwoD_Leveling(myValue);
		}
		else{
			if((mainForm->myScanPanelForm->One_D)){
		//		mainForm->LogToFile("1D_leveling for image index " + IntToStr(image_index) + " Line number " + IntToStr(myValue));
				OneD_Leveling(myValue);
			}


			Max = Lines[myValue].MaxOfLine;
			Min = Lines[myValue].MinOfLine;

			if(myValue == 0){
				CurrentMax = Max;
				CurrentMin = Min;
				MaxChange = true;
				MinChange = true;
			}
			else{
				if(Max > CurrentMax){
					CurrentMax = Max;
					MaxChange = true;
				}
				if(Min < CurrentMin){
					CurrentMin = Min;
					MinChange = true;
				}
			}

				ptr = reinterpret_cast<TRGBTriple *>(map->ScanLine[myValue]);
				Lines[myValue].MapLine0To255(CurrentMin, CurrentMax, ptr/*, ptrPalette*/, image_index, true);

//				if(!(mainForm->myScanPanelForm->Two_D)){
			//		if max or min change modfiy all lines
					if( (MinChange || MaxChange) && (myValue != 0)){
						for(int j=0; j< myValue; j++){
							ptr = reinterpret_cast<TRGBTriple *>(map->ScanLine[j]);
							Lines[j].MapLine0To255(CurrentMin, CurrentMax, ptr/*, ptrPalette*/, image_index, true);
						}
					}
//				}
		}



	}
	else{
		Max = Lines[myValue].MaxOfLine;
		Min = Lines[myValue].MinOfLine;

		if(myValue == 0){
			CurrentMax = Max;
			CurrentMin = Min;
			MaxChange = true;
			MinChange = true;
		}
		else{
			if(Max > CurrentMax){
				CurrentMax = Max;
				MaxChange = true;
			}
			if(Min < CurrentMin){
				CurrentMin = Min;
				MinChange = true;
			}
		}


//		if(image_index == 2 || image_index == 3){
//			mainForm->LogToFile("image_index = " + IntToStr(image_index) + " -----------------------------------------------------------------Line = " + IntToStr(myValue));
//		}

		ptr = reinterpret_cast<TRGBTriple *>(map->ScanLine[myValue]);
		Lines[myValue].MapLine0To255(CurrentMin, CurrentMax, ptr/*, ptrPalette*/, image_index, false);


		//if max or min change modfiy all lines
		if( (MinChange || MaxChange) && (myValue != 0)){
			for(int j=0; j< myValue; j++){
				ptr = reinterpret_cast<TRGBTriple *>(map->ScanLine[j]);
				Lines[j].MapLine0To255(CurrentMin, CurrentMax, ptr/*, ptrPalette*/, image_index, false);
			}
		}
	}

//	mainForm->LogToFile("my value = " + IntToStr(myValue));
	if( ( (myValue+1) % Save == 0) /*|| (myValue == 0))*/){
		//save image
		map->SaveToFile(ImageFileName);
	}

	//show image
	if( ( ((myValue+1) % Save == 0) || (myValue == 1))){
		//show image
		TThread::Synchronize(mainForm->myImagerThread,ShowAndSetImages);
	}


//	if(myValue % 16 == 0 && myIndex ==0)
//		mainForm->LogToFile("TcpImgClass::UpdateColor ..... Line Number " + IntToStr(myValue) + " Showed .");
}
//---------------------------------------------------------------------------

//void TcpImgClass::MapLine0To255(int myMin,int myMax, TRGBTriple * QUAD/*, TRGBTriple * QUADPalette*/, int image_index, bool topo, int line)
//{
//	int tmp = MIN_COLOR;
//	for(int i=0; i<GetResolution(); i++){
//		if(myMin != myMax){
//			tmp = (double)MAX_COLOR * (double)(Lines[line].Pixels[i].Main - myMin) / (double)(myMax - myMin);
//			if(topo){
//				tmp = 255 - tmp;
////				mainForm->LogToFile("max = " + IntToStr(myMax));
////				mainForm->LogToFile("max = " + IntToStr(myMin));
//			}
//		}
////		Pixels[i].Color = tmp;
//
//
//	}
//}
//---------------------------------------------------------------------------

bool TcpImgClass::OneD_Leveling(int currentLine)
{
//	mainForm->LogToFile("TcpImgClass::OneD_Leveling");
	bool ret = false;

	int n = Resolution;
	int q = currentLine;
	int min = MAX_MAX;
	int max = 0;
//	int OutLiers = 0;                                                                      //to remove outliers
	double mean_y = 0;
	double mean_x = 0;
//	arr = new int[n];                                                                      //to remove outliers

//	for(int i=0; i<n; i++){
//		arr[i] = Lines[q].Pixels[i].Main;
//	}
//
//	sort(arr, arr + n);
//	int Q1 = arr[n/4];
//	int Q2 = arr[n*3/4];
//	double diff = (Q2 - Q1)*1.5;

	for (int i=0; i<n; i++){
//	  if(!(Lines[q].Pixels[i].Main < Q1 - diff) || (Lines[q].Pixels[i].Main > Q2 + diff)){ //to remove outliers
		mean_y = mean_y + Lines[q].Pixels[i].Main ;
//	  }                                                                                    //to remove outliers
//	  else{                                                                                //to remove outliers
//		OutLiers++;                                                                        //to remove outliers
//		mainForm->LogToFile("Outlier Pixel = " + IntToStr(i));                             //to remove outliers
//	  }                                                                                    //to remove outliers

	}

//	mean_y = mean_y / (n - OutLiers);                                                      //to remove outliers
	mean_y = mean_y / n;                                                                   //to use outliers

//	mean_x = (n - OutLiers) * ((n - OutLiers)-1) / 2 ;                                     //to remove outliers
//	mean_x = mean_x / (n - OutLiers);                                                      //to remove outliers

	mean_x = n * (n-1) / 2 ;                                                               //to use outliers
	mean_x = mean_x / n;                                                                   //to use outliers

	double slop = 0;
	double a = 0;
	double b = 0;
	for(int i = 0; i<n; i++){
		a = a + (i - mean_x) * (Lines[q].Pixels[i].Main - mean_y);
		b = b + (i - mean_x) * (i - mean_x) ;
	}
	slop = a / b ;
	double constant =  mean_y - slop * mean_x ;

	for(int i=0; i<n; i++){
		Lines[q].Pixels[i].TwoD_Leveled_Main = ((double)Lines[q].Pixels[i].Main - ( (double)i * slop + constant));
		if(Lines[q].Pixels[i].TwoD_Leveled_Main > Lines[q].MaxOfLine)
			Lines[q].MaxOfLine = Lines[q].Pixels[i].TwoD_Leveled_Main;
		if(Lines[q].Pixels[i].TwoD_Leveled_Main < Lines[q].MinOfLine )
			Lines[q].MinOfLine = Lines[q].Pixels[i].TwoD_Leveled_Main;
	}

//	Lines[q].MaxOfLine = Lines[q].GetMaximumFromLine();
//	Lines[q].MinOfLine = Lines[q].GetMinimumFromLine();

//    delete[] arr;
                                                                                           //to remove outliers
	return ret;
}
//---------------------------------------------------------------------------

bool TcpImgClass::TwoD_Leveling(int currentLine)
{//	mainForm->LogToFile("TcpImgClass::TwoD_Leveling");	bool ret = false;	//	int n = Resolution;
	int q = currentLine + 1;

	int **X = new int*[n*q];
	for (int i = 0; i < n*q; i++)
		X[i] = new int[3];

	long double **Y = new long double*[n*q];
	for (int i = 0; i < n*q; i++)
		Y[i] = new long double[1];

	int **XT = new int*[3];
	for(int i=0; i<3; i++)
		XT[i] = new int[n*q];

	long double **XTX = new long double*[3];
	for(int i=0; i<3; i++)
		XTX[i] = new long double[3];

	long double **XTXElhagh = new long double*[3];
		for(int i=0; i<3; i++)
			XTXElhagh[i] = new long double[3];

	long double **XTXElhaghT = new long double*[3];
		for(int i=0; i<3; i++)
			XTXElhaghT[i] = new long double[3];

	long double **XTX_1 = new long double*[3];
		for(int i=0; i<3; i++)
			XTX_1[i] = new long double[3];

	long double **XTX_1XT = new long double*[3];
		for(int i=0; i<3; i++)
			XTX_1XT[i] = new long double[n*q];

	long double **tetha = new long double*[3];
		for(int i=0; i<3; i++)
			tetha[i] = new long double[1];

	//X     (n*q * 3)
	for(int i=0; i<q; i++){
		for(int j=0; j<n; j++){
			X[i*n+j][0] = 1;
			X[i*n+j][1] = i;
			X[i*n+j][2] = j;

		}
	}
	//___________________________________________________________

	//Y		(n*q * 1)
	for(int i=0; i<q; i++){
		for(int j=0; j<n; j++){
			Y[i*n+j][0] = Lines[i].Pixels[j].Main;
		}
	}
	//___________________________________________________________


	//XT	(3 * n*q)
	for(int i=0; i<3; i++){
		for(int j=0; j<n*q; j++){
			XT[i][j] = X[j][i];
		}
	}
	//___________________________________________________________


	// XT * X   (3*3)
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			long double t=0;
			for(int z=0 ; z<n*q; z++){
				 t += XT[i][z]*X[z][j];
			}
			XTX[i][j] = t;
		}
	}
	//___________________________________________________________

	//(XT * X)^-1  (3*3)
	long double det = 0;
	long double det1 = ( (XTX[1][1] * XTX[2][2]) - (XTX[1][2] * XTX[2][1]) );
	long double det2 = ( (XTX[1][0] * XTX[2][2]) - (XTX[1][2] * XTX[2][0]) );
	long double det3 = ( (XTX[1][0] * XTX[2][1]) - (XTX[1][1] * XTX[2][0]) );
	det = (XTX[0][0]*det1 - XTX[0][1]*det2 + XTX[0][2]*det3);

//	mainForm->LogToFile(" det of (XT * X)  = " + FloatToStr(det));


	if(det !=0){
		ret = true;
		long double DetInvers = 1/det;

		XTXElhagh[0][0] = +( XTX[1][1]*XTX[2][2] - XTX[1][2]*XTX[2][1] );
		XTXElhagh[0][1] = -( XTX[1][0]*XTX[2][2] - XTX[1][2]*XTX[2][0] );
		XTXElhagh[0][2] = +( XTX[1][0]*XTX[2][1] - XTX[1][1]*XTX[2][0] );

		XTXElhagh[1][0] = -( XTX[0][1]*XTX[2][2] - XTX[0][2]*XTX[2][1] );
		XTXElhagh[1][1] = +( XTX[0][0]*XTX[2][2] - XTX[0][2]*XTX[2][0] );
		XTXElhagh[1][2] = -( XTX[0][0]*XTX[2][1] - XTX[0][1]*XTX[2][0] );

		XTXElhagh[2][0] = +( XTX[0][1]*XTX[1][2] - XTX[1][1]*XTX[0][2] );
		XTXElhagh[2][1] = -( XTX[0][0]*XTX[1][2] - XTX[0][2]*XTX[1][0] );
		XTXElhagh[2][2] = +( XTX[0][0]*XTX[1][1] - XTX[0][1]*XTX[1][0] );

		//___________________________________________________________
		//XTXElhaghT	(3 * 3)
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				XTXElhaghT[i][j] = XTXElhagh[j][i];
			}
		}

		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
				XTX_1[i][j] = DetInvers * XTXElhaghT[i][j];
		//___________________________________________________________

		// ( (XT * X)^-1 ) * XT     (3 * n*q)
		for(int i=0; i<3; i++){
			for(int j=0; j<n*q; j++){
				double t = 0;
				for(int z=0 ; z<3; z++){
					t += XTX_1[i][z]*XT[z][j];
				}
				XTX_1XT[i][j] = t;
			}
		}
		//___________________________________________________________


		//  ( (XT * X)^-1 ) * XT ) * Y          (3 * 1)
		for(int i=0; i<3; i++){
//			for(int j=0; j<1; j++){
				double t = 0;
				for(int z=0 ; z<n*q; z++){
					t += XTX_1XT[i][z]*Y[z][0];
				}
				tetha[i][0] = t;
//			}
		}
		//___________________________________________________________

		double a = tetha[0][0];
		double b = tetha[1][0];
		double c = tetha[2][0];

//		mainForm->LogToFile( "a = " + FloatToStr(a) );
//		mainForm->LogToFile( "b = " + FloatToStr(b) );
//		mainForm->LogToFile( "c = " + FloatToStr(c) );
//		mainForm->LogToFile("_______________currentLine_________________ " + IntToStr(q));


		//Plane = X * ϴ
		int min,max;
		int t;
		for(int i=0; i<n*q; i++){
			double A = (X[i][0] * a + X[i][1] * b + X[i][2] * c);
//			if(Y[i][0] > A){
//				t = Y[i][0] - A;
//			}
//			else{
//				t = A - Y[i][0];
//			}

//			mainForm->LogToFile("before = " + FloatToStr(Y[i][0]) + " " + FloatToStr(Lines[(int)(i/n)].Pixels[i%n].Main));
			t = Y[i][0] - A ;
			Lines[(int)(i/n)].Pixels[i%n].TwoD_Leveled_Main = t;
//			mainForm->LogToFile("after = " + IntToStr(Lines[(int)(i/n)].Pixels[i%n].Main));

			if(i == 0){
				min = t;
				max = t;
			}

			if(t > max)
				max = t;
			if(t < min)
				min = t;

//			Lines[i/n].MaxOfLine = max;
//			Lines[i/n].MinOfLine = min;


//			Lines[(int)(i/n)].Pixels[i%n].Main = t;
//			Lines[(i/n)].MaxOfLine = Lines[(i/n)].GetMaximumFromLine();
//			Lines[(i/n)].MinOfLine = Lines[(i/n)].GetMinimumFromLine();
		}

		bool mydoing = false;
		for(int i=0; i<q; i++){
			mydoing = true;
			try{
				ptr_2 = reinterpret_cast<TRGBTriple *>(map->ScanLine[i]);
			}
			catch(Exception &exception){
				mydoing = false;
				ShowMessage("modify ScanLine Exception: " + exception.Message + " _ " + exception.StackTrace);
			}

			if(mydoing){
				try{
					Lines[i].MapLine0To255_2(min, max, ptr_2/*, ptrPalette*/, image_index);
				}
				catch(Exception &exception){
					ShowMessage("modify MapLine0To255 Exception: " + exception.Message + " _ " + exception.StackTrace);
				}
			}
		}
	}

	//release memory
	for(int i = 0; i < n*q; i++){
		delete[] X[i];
		X[i] = NULL;
	}

	delete[] X;
	X = NULL;

	for(int i = 0; i < n*q; i++){
		delete[] Y[i];
		Y[i] = NULL;
	}
	delete[] Y;
	Y = NULL;

	for(int i = 0; i < 3; i++){
		delete[] XT[i];
		XT[i] = NULL;
	}
	delete[] XT;
	XT = NULL;

	for(int i = 0; i < 3; i++){
		delete[] XTX[i];
	}
	delete[] XTX;

	for(int i = 0; i < 3; i++){
		delete[] XTXElhagh[i];
		XTXElhagh[i] = NULL;
	}
	delete[] XTXElhagh;
	XTXElhagh = NULL;

	for(int i = 0; i < 3; i++){
		delete[] XTXElhaghT[i];
		XTXElhaghT[i] = NULL;
	}
	delete[] XTXElhaghT;
	XTXElhaghT = NULL;

	for(int i = 0; i < 3; i++){
		delete[] XTX_1[i];
		XTX_1[i] = NULL;
	}
	delete[] XTX_1;
	XTX_1 = NULL;

	for(int i = 0; i < 3; i++){
		delete[] XTX_1XT[i];
		XTX_1XT[i] = NULL;
	}
	delete[] XTX_1XT;
	XTX_1XT = NULL;

	for(int i = 0; i < 3; i++){
		delete[] tetha[i];
		tetha[i] = NULL;
	}
	delete[] tetha;
	tetha = NULL;
	return ret;}
//---------------------------------------------------------------------------

void __fastcall TcpImgClass::ShowAndSetImages()
{
//	mainForm->LogToFile("TcpImgClass::ShowAndSetImages");
	//set image
	try{
		SetImage(image_index);
	}
	catch(Exception &exception){
		ShowMessage("SetImage Exception : " + exception.Message + " _ " + exception.StackTrace);
	}

	//show image
	try{
		mainForm->myImageFrom->ShowImageNumber();
	}
	catch(Exception &exception){
		ShowMessage("ShowImageNumber Exception : " + exception.Message + " _ " + exception.StackTrace);
	}
}
//---------------------------------------------------------------------------

void TcpImgClass::CreateBitMaps(int mySize)
{
	mainForm->LogToFile("TcpImgClass::CreateBitMaps");
	map = new TBitmap;
	map->SetSize(mySize,mySize);
	map->Canvas->Brush->Color = 0x008B6757;
	map->Canvas->FillRect(TRect(TPoint(0,0),mySize,mySize));
	map->PixelFormat = pf24bit;

	CreateFiles();

	BitMapBit = true;
}
//---------------------------------------------------------------------------

void TcpImgClass::SetFolderFiles(UnicodeString dirName)
{
	mainForm->LogToFile("TcpImgClass::SetFolderFiles");
	if( !DirectoryExists(UploadPath) ){
		AnsiString dir = UploadPath;
		CreateDirectoryA(dir.c_str(),NULL);
	}

	if( !DirectoryExists(DownloadPath) ){
		AnsiString dir = DownloadPath;
		CreateDirectoryA(dir.c_str(),NULL);
	}

	AnsiString PicFolder = DownloadPath + "/" + mainForm->myControlPanelForm->PicFolder;
	AnsiString DateFolder = mainForm->myControlPanelForm->DateFolder;
	AnsiString TimeFolder = mainForm->myControlPanelForm->TimeFolder;
	AnsiString UserFolder = mainForm->myControlPanelForm->ImageFolderUser;

	ModeFolder = "";
	FinalFolderName = "";
	IntFileName = "";
	JpgFileName = "";
	TxtFileName = "";

	FinalFolderName = PicFolder;
	if( !DirectoryExists(PicFolder) ){
		AnsiString dir = PicFolder;
		CreateDirectoryA(dir.c_str(),NULL);
	}

	ModeFolder = dirName;
	if( !DirectoryExists(PicFolder + "/" + ModeFolder) ){
		AnsiString dir = PicFolder + "/" + ModeFolder;
		CreateDirectoryA(dir.c_str(),NULL);
	}
	else{
	}
	FinalFolderName = PicFolder + "/" + ModeFolder;

	if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder)){
		AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder;
		CreateDirectoryA(dir.c_str(),NULL);
	}
	else{
	}
	FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder;

	if(UserFolder != ""){
		if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder)){
			AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder;
			if( CreateDirectoryA(dir.c_str(),NULL) == 0){
				mainForm->LogToFile("can not create = " + UserFolder);
				mainForm->myControlPanelForm->FolderCreated = false;
				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder)){
					AnsiString dir2 = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
					CreateDirectoryA(dir2.c_str(),NULL);
				}
				else{
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + TimeFolder;
			}
			else{
				if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
					AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
					CreateDirectoryA(dir.c_str(),NULL);
				}
				else{
				}
				FinalFolderName = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
			}
		}
		else{
			if(!DirectoryExists(PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder)){
				AnsiString dir = PicFolder + "/" + ModeFolder + "/" + DateFolder + "/" + UserFolder + "/" + TimeFolder;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			else{
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

	IntFileName = FinalFolderName + "/" + TimeFolder + "_" + ImageName + ".int";
	TxtFileName = FinalFolderName + "/" + TimeFolder + "_" + ImageName + ".txt";
	JpgFileName = FinalFolderName + "/" + TimeFolder + "_" + ImageName + ".bmp";
	LastImagesFolderPath = FinalFolderName;
//	mainForm->LogToFile("file name : " + FinalFolderName + TimeFolder + "_" + ImageName);
	ImageFileName = JpgFileName;
}
//---------------------------------------------------------------------------

void TcpImgClass::CreateFiles()
{
	mainForm->LogToFile("TcpImgClass::CreateFiles");
	switch(mainForm->AppMode){
		case 1:{
			SetFolderFiles("Contact");
			break;
		}
		case 2:{
			SetFolderFiles("NonContact");
			break;
		}
		case 3:{
			SetFolderFiles("EFM");
			break;
		}
		case 4:{
			SetFolderFiles("MFM");
			break;
		}
		case 5:{
			SetFolderFiles("ForceSpec");
			break;
		}
		case 6:{
			SetFolderFiles("KPFM");
			break;
		}
		case 7:{
			SetFolderFiles("Lithography");
			break;
		}
		default:{
			break;
		}
	}

	mainForm->CurrentPicFolderName = FinalFolderName;
//	mainForm->LogToFile("IntFileName = " + IntFileName);
//	mainForm->LogToFile("TxtFileName = " + TxtFileName);
//	mainForm->LogToFile("JpgFileName = " + JpgFileName);
	file = new ofstream(IntFileName.c_str(), ios::binary);
//	fs = new TFileStream(TxtFileName, fmCreate);

	FileBit = true;
}
//---------------------------------------------------------------------------

void TcpImgClass::DeleteLines()
{
	if(Lines){
		delete[] Lines;
		Lines = NULL;
	}
}
//---------------------------------------------------------------------------

void TcpImgClass::DeleteBiMap()
{
	if(map){
		delete map;
        map = NULL;
	}
}
//---------------------------------------------------------------------------

void TcpImgClass::FinalizeImaging()
{
//	if(file)
//		file->close();
//	DeleteBiMap();
//	for(int i=0; i<GetResolution(); i++){
//		Lines[i].DeletePioxels();
//	}
//	DeleteLines();
}
//---------------------------------------------------------------------------

//bool TcpImgClass::PaletteCreate(unsigned char rDark, unsigned char gDark, unsigned char bDark,unsigned char rLight, unsigned char gLight, unsigned char bLight)
//{
//	double ar;
//	double ag;
//	double ab;
//
//	ar = (rLight - rDark)/(double)256;
//	ag = (gLight - gDark)/(double)256;
//	ab = (bLight - bDark)/(double)256;
//
//	if(ptrPalette) delete[] ptrPalette;
//	if(!ptrPalette)
//		ptrPalette = new TRGBTriple[256];
//	for(int i=0; i<256; i++){
//		int r = (int)floor( (rDark + i * ar) + 0.5 );
//		int g = (int)floor( (gDark + i * ag) + 0.5 );
//		int b = (int)floor( (bDark + i * ab) + 0.5 );
//		ptrPalette[i].rgbtRed = r;
//		ptrPalette[i].rgbtGreen = g;
//		ptrPalette[i].rgbtBlue = b;
//
////		mainForm->LogToFile( IntToStr(i) + " _ (" + IntToStr(r) + "," + IntToStr(g) + "," + IntToStr(b) + ")" );
////				ptrPalette[i].rgbReserved = 0;
//	}

	//1 RED
	//2 GREEN
	//3 BLUE

//	switch (rgb){
////	mainForm->LogToFile("switch");
//		case 1:{
//			mainForm->LogToFile("1");

//			break;
//		}
//		case 2:{
////			mainForm->LogToFile("2");
//			if(!ptrPalette)
//				ptrPalette = new TRGBTriple[256];
//			for(int i=0; i<256; i++){
//				ptrPalette[i].rgbtRed = rgb1;
//				ptrPalette[i].rgbtGreen = i;
//				ptrPalette[i].rgbtBlue = rgb2;
////				ptrPalette[i].rgbReserved = 0;
//			}
//			break;
//		}
//		case 3:{
////			mainForm->LogToFile("3");
//			if(!ptrPalette)
//				ptrPalette = new TRGBTriple[256];
//			for(int i=0; i<256; i++){
//				ptrPalette[i].rgbtRed = rgb1;
//				ptrPalette[i].rgbtGreen = rgb2;
//				ptrPalette[i].rgbtBlue = i;
////				ptrPalette[i].rgbReserved = 0;
//			}
//			break;
//		}
//	}
//	return true;
//	mainForm->LogToFile("PaletteCreate");
//}
//---------------------------------------------------------------------------

void TcpImgClass::SetImage(int index)
{
//	mainForm->LogToFile("TcpImgClass::SetImage");
	if(ImageInitBit){
		switch (index) {
			case 0:{

				try{
					mainForm->myImageFrom->Image1->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 1 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 1 **************");
				}
				break;
			}
			case 1:{
				try{
					mainForm->myImageFrom->Image2->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 2 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 2 **************");
				}
				break;
			}
			case 2:{
				try{
					mainForm->myImageFrom->Image3->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 3 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 3 **************");
				}
				break;
			}
			case 3:{
				try{
					mainForm->myImageFrom->Image4->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 4 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 4 **************");
				}
				break;
			}
			case 4:{
				try{
					mainForm->myImageFrom->Image5->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 5 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 5 **************");
				}
				break;
			}
			case 5:{
				try{
					mainForm->myImageFrom->Image6->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 6 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 6 **************");
				}
				break;
			}
			case 6:{
				try{
					mainForm->myImageFrom->Image7->Picture->Assign(map);
				}
				catch(Exception &exception){
						ShowMessage("Image 7 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 7 **************");
				}
				break;
			}
			case 7:{
				try{
					mainForm->myImageFrom->Image8->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 8 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 8 **************");
				}
				break;
			}
			case 8:{
				try{
					mainForm->myImageFrom->Image9->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 9 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 9 **************");
				}
				break;
			}
			case 9:{
				try{
					mainForm->myImageFrom->Image10->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 10 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 10 **************");
				}
				break;
			}
			case 10:{
				try{
					mainForm->myImageFrom->Image11->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 11 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 11 **************");
				}
				break;
			}
			case 11:{
				try{
					mainForm->myImageFrom->Image12->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 12 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 12 **************");
				}
				break;
			}
			case 12:{
				try{
					mainForm->myImageFrom->Image13->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 13 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 13 **************");
				}
				break;
			}
			case 13:{
				try{
					mainForm->myImageFrom->Image14->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 14 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 14 **************");
				}
				break;
			}
			case 14:{
				try{
					mainForm->myImageFrom->Image15->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 15 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 15 **************");
				}
				break;
			}
			case 15:{
				try{
					mainForm->myImageFrom->Image16->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 16 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 16 **************");
				}
				break;
			}
			case 16:{
				try{
					mainForm->myImageFrom->Image17->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 17 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 17 **************");
				}
				break;
			}
			case 17:{
				try{
					mainForm->myImageFrom->Image18->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 18 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 18 **************");
				}
				break;
			}
			case 18:{
				try{
					mainForm->myImageFrom->Image19->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 19 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 19 **************");
				}
				break;
			}
			case 19:{
				try{
					mainForm->myImageFrom->Image20->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 20 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 20 **************");
				}
				break;
			}
			case 20:{
				try{
					mainForm->myImageFrom->Image21->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 21 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 21 **************");
				}
				break;
			}
			case 21:{
				try{
					mainForm->myImageFrom->Image22->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 22 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 22 **************");
				}
				break;
			}
			case 22:{
				try{
					mainForm->myImageFrom->Image23->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 23 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 23 **************");
				}
				break;
			}
			case 23:{
				try{
					mainForm->myImageFrom->Image24->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 24 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 24 **************");
				}
				break;
			}
			case 24:{
				try{
					mainForm->myImageFrom->Image25->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 25 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 25 **************");
				}
				break;
			}
			case 25:{
				try{
					mainForm->myImageFrom->Image26->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 26 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 26 **************");
				}
				break;
			}
			case 26:{
				try{
					mainForm->myImageFrom->Image27->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 27 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 27 **************");
				}
				break;
			}
			case 27:{
				try{
					mainForm->myImageFrom->Image28->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 28 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 28 **************");
				}
				break;
			}
			case 28:{
				try{
					mainForm->myImageFrom->Image29->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 29 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 29 **************");
				}
				break;
			}
			case 29:{
				try{
					mainForm->myImageFrom->Image30->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 30 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 30 **************");
				}
				break;
			}
			case 30:{
				try{
					mainForm->myImageFrom->Image31->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 31 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 31 **************");
				}
				break;
			}
			case 31:{
				try{
					mainForm->myImageFrom->Image32->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 32 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 32 **************");
				}
				break;
			}
			case 32:{
				try{
					mainForm->myImageFrom->Image33->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 33 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 33 **************");
				}
				break;
			}
			case 33:{
				try{
					mainForm->myImageFrom->Image34->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 34 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image 34 **************");
				}
				break;
			}
			default:{
				try{
					mainForm->myImageFrom->Image1->Picture->Assign(map);
				}
				catch(Exception &exception){
					ShowMessage("Image 1 Exception : " + exception.Message + " _ " + exception.StackTrace);
//					mainForm->LogToFile("Image default **************");
				}
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall SetImages()
{

}
//---------------------------------------------------------------------------

void TcpImgClass::Set24BitsFromPacket(int myValue)
{
	mainForm->LogToFile("TcpImgClass::Set24BitsFromPacket");
	switch (myValue){
		case 0:{
		 //Topo 24bits
			Set_24Bit(true);
			break;
		}
		case 1:{
		 //Tb 24bits
			Set_24Bit(true);
			break;
		}
		case 2:{
		 //Lr 24bits
			Set_24Bit(true);
			break;
		}
		case 3:{
		 // Amplitude 32bits
			Set_24Bit(false);
			break;
		}
		case 4:{
		//Phase 32bits
			Set_24Bit(false);
			break;
		}
		case 5:{
		//Bias 24bits
			Set_24Bit(true);
			break;
		}
		case 6:{
		//CAFM 24bits
			Set_24Bit(true);
			break;
		}
		case 7:{
		//AMP(we) 32bits
			Set_24Bit(false);
			break;
		}
		case 8:{
		//Phase(we) 32bits
			Set_24Bit(false);
			break;
		}
		case 9:{
		 //LA1X 32bits
			Set_24Bit(false);
			break;
		}
		case 10:{
		//LA1Y 32bits
			Set_24Bit(false);
			break;
		}
		case 11:{
		//AMP(2We) 32bits
			Set_24Bit(false);
			break;
		}
		case 12:{
		//Phase(2we) 32bits
			Set_24Bit(false);
			break;
		}
		case 13:{
		//LA2X 32bits
			Set_24Bit(false);
			break;
		}
		case 14:{
		 //LA2Y 32bits
			Set_24Bit(false);
			break;
		}
	}
}
//---------------------------------------------------------------------------

AnsiString TcpImgClass::SetName(int my_image_index)
{
	mainForm->LogToFile("TcpImgClass::SetName");
	AnsiString ret = "";
	switch (my_image_index){
		case 0:{
			ret = PIC0_FF;
			osc = 3;
			break;
		}
		case 1:{
			ret = PIC0_BB;
			osc = 3;
			break;
		}
		case 2:{
			ret = PIC1_FF;
			osc = 0;
			break;
		}
		case 3:{
			ret = PIC1_BB;
			osc = 0;
			break;
		}
		case 4:{
			ret = PIC2_FF;
			osc = 1;
			break;
		}
		case 5:{
			ret = PIC2_BB;
			osc = 1;
			break;
		}
		case 6:{
			ret = PIC3_FF;
			osc = 6;
			break;
		}
		case 7:{
			ret = PIC3_BB;
			osc = 6;
			break;
		}
		case 8:{
			ret = PIC4_FF;
			osc = 7;
			break;
		}
		case 9:{
			ret = PIC4_BB;
			osc = 7;
			break;
		}
		case 10:{
			ret = PIC5_FF;
			osc = 17;
			break;
		}
		case 11:{
			ret = PIC5_BB;
			osc = 17;
			break;
		}
		case 12:{
			ret = PIC6_FF;
			osc = 25;
			break;
		}
		case 13:{
			ret = PIC6_BB;
			osc = 25;
			break;
		}
		case 14:{
			ret = PIC7_FF;
			osc = 25;
			break;
		}
		case 15:{
			ret = PIC7_BB;
			osc = 25;
			break;
		}
		case 16:{
			ret = PIC8_FF;
			osc = 25;
			break;
		}
		case 17:{
			ret = PIC8_BB;
			osc = 25;
			break;
		}
		case 18:{
			ret = PIC9_FF;
			osc = 25;
			break;
		}
		case 19:{
			ret = PIC9_BB;
			osc = 25;
			break;
		}
		case 20:{
			ret = PIC10_FF;
			osc = 25;
			break;
		}
		case 21:{
			ret = PIC10_BB;
			osc = 25;
			break;
		}
		case 22:{
			ret = PIC11_FF;
			osc = 25;
			break;
		}
		case 23:{
			ret = PIC11_BB;
			osc = 25;
			break;
		}
		case 24:{
			ret = PIC12_FF;
			osc = 25;
			break;
		}
		case 25:{
			ret = PIC12_BB;
			osc = 25;
			break;
		}
		case 26:{
			ret = PIC13_FF;
			osc = 25;
			break;
		}
		case 27:{
			ret = PIC13_BB;
			osc = 25;
			break;
		}
		case 28:{
			ret = PIC14_FF;
			osc = 25;
			break;
		}
		case 29:{
			ret = PIC14_BB;
			osc = 25;
			break;
		}
		case 30:{
			ret = PIC15_FF;
			osc = 6;
			break;
		}
		case 31:{
			ret = PIC15_BB;
			osc = 6;
			break;
		}
		case 32:{
			ret = PIC16_FF;
			osc = 7;
			break;
		}
		case 33:{
			ret = PIC16_BB;
            osc = 7;
			break;
		}
	}
	return ret;
}
//--------------------------------------------------------------------------


