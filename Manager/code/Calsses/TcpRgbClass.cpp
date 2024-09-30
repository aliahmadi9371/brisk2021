//---------------------------------------------------------------------------

#pragma hdrstop

#include "TcpRgbClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TcpRgbClass::TcpRgbClass()
{
	Main = -8388607;
	TwoD_Leveled_Main = -8388607;
}
//---------------------------------------------------------------------------
TcpRgbClass::~TcpRgbClass()
{

}
//---------------------------------------------------------------------------

void TcpRgbClass::SetMain(int myM)
{
	Main = myM;
}
//---------------------------------------------------------------------------

int TcpRgbClass::GetMain()
{
	return Main;
}
//---------------------------------------------------------------------------

void TcpRgbClass::SetPixel(unsigned char R, unsigned char G, unsigned char B, unsigned char reserve, TRGBTriple *QUAD)
{
	QUAD->rgbtRed = R ;//rand()%256;
	QUAD->rgbtGreen = G;//rand()%256;
	QUAD->rgbtBlue = B;//rand()%256;
//	QUAD->rgbReserved = reserve;//rand()%256;
}
//---------------------------------------------------------------------------
