//---------------------------------------------------------------------------

#pragma hdrstop

#include "TcpLineClass.h"
#include "mainUnit.h"
#include "Pallete_256.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TcpLineClass::TcpLineClass()
{

	LineNumber = 0;
	PixelCount = 0;
	created = false;

	MaxOfLine = -8388607;
	MinOfLine = +8388607;
	Pixels = NULL;
}
//---------------------------------------------------------------------------

TcpLineClass::~TcpLineClass()
{
//	mainForm->LogToFile("~TcpLineClass(");
}
//---------------------------------------------------------------------------

void TcpLineClass::InitOneLine(int mySize)
{
	Pixels = new TcpRgbClass[mySize];
	SetPixelCount(mySize);
	created = true;
}
//---------------------------------------------------------------------------

void TcpLineClass::SetPixelCount(int myPixelCount)
{
	PixelCount = myPixelCount;
}
//---------------------------------------------------------------------------

void TcpLineClass::SetLineNumber(int myLineNumber)
{
	LineNumber = myLineNumber;
}
//---------------------------------------------------------------------------

int TcpLineClass::GetPixelCount()
{
	return PixelCount;
}
//---------------------------------------------------------------------------

int TcpLineClass::GetLineNumber()
{
	return LineNumber;
}
//---------------------------------------------------------------------------

int TcpLineClass::GetMinimumFromLine()
{
	int Min = Pixels[0].Main;
	for(int i=0; i<GetPixelCount(); i++)
		if(Pixels[i].Main < Min)
			Min = Pixels[i].Main;

	return Min;
}
//---------------------------------------------------------------------------

int TcpLineClass::GetMaximumFromLine()
{
	int Max = Pixels[0].Main;
	for(int i=0; i<GetPixelCount(); i++)
		if(Pixels[i].Main > Max)
			Max = Pixels[i].Main;

	return Max;
}
//---------------------------------------------------------------------------

void TcpLineClass::MapLine0To255(int myMin,int myMax, TRGBTriple *QUAD/*, TRGBTriple * QUADPalette*/, int image_index , bool topo)
{
//	mainForm->LogToFile("TcpLineClass::MapLine0To255");

	int tmp = MIN_COLOR;

	for(int i=0; i<PixelCount; i++){
		if(myMin != myMax){
//			if(image_index == 2 || image_index == 3)
//				mainForm->LogToFile("image_index = " + IntToStr(image_index) + " , Pixel = " + IntToStr(i) + " , Main = " + IntToStr(Pixels[i].Main));
			if((mainForm->myScanPanelForm->One_D) && (image_index == 0 || image_index == 1) ){
				tmp = (double)MAX_COLOR * (double)(Pixels[i].TwoD_Leveled_Main - myMin) / (double)(myMax - myMin);
			}
			else{
				tmp = (double)MAX_COLOR * (double)(Pixels[i].Main - myMin) / (double)(myMax - myMin);
            }
//			if(topo){
				tmp = 255 - tmp;
//				mainForm->LogToFile("max = " + IntToStr(myMax));
//				mainForm->LogToFile("max = " + IntToStr(myMin));
//			}
		}
//		Pixels[i].Color = tmp;
		Pixels[i].SetPixel(Pallete[MAX_COLOR - tmp][0], Pallete[MAX_COLOR - tmp][1], Pallete[MAX_COLOR - tmp][2], 0, &QUAD[i]);
	}
}
//---------------------------------------------------------------------------

void TcpLineClass::MapLine0To255_2(int myMin,int myMax, TRGBTriple *QUAD/*, TRGBTriple * QUADPalette*/, int image_index)
{
//	mainForm->LogToFile("TcpLineClass::MapLine0To255_2");
	int tmp = MIN_COLOR;
	for(int i=0; i<PixelCount; i++){
		if(myMin != myMax){
			tmp = (double)MAX_COLOR * (double)(Pixels[i].TwoD_Leveled_Main - myMin) / (double)(myMax - myMin);
			tmp = 255 - tmp;
			//			if(image_index == 6 || image_index == 7)
			//				if(i%8 == 0)
			//					mainForm->LogToFile("image_index = " + IntToStr(image_index) + " , tmp = " + IntToStr(tmp)
		}
//		else{
//			mainForm->LogToFile("min == max, image_index = " + IntToStr(image_index));
//		}
//		Pixels[i].Color = tmp;
		Pixels[i].SetPixel(Pallete[MAX_COLOR - tmp][0], Pallete[MAX_COLOR - tmp][1], Pallete[MAX_COLOR - tmp][2], 0, &QUAD[i]);
	}
}
//---------------------------------------------------------------------------

//void TcpLineClass::DeletePioxels()
//{
//	if(Pixels)
//		delete[] Pixels;
//}
//---------------------------------------------------------------------------

