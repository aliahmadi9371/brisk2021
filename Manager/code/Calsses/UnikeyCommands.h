//---------------------------------------------------------------------------

#ifndef UnikeyCommandsH
#define UnikeyCommandsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.FMTBcd.hpp>
#include "UniKey.h"

struct version{
	int major1;
	int major2;
	int minor1;
	int minor2;
};
//---------------------------------------------------------------------------
class UniKeyClass
{
public:

	DWORD FindDongle();
	DWORD ReadSoftID();
	void OpenDongle();
	void WriteResetLicence();
	int ReadDongle();
	void LogOff();

//    int i;
//	int num;
//	String str;
//	Word mUniKeyNumber;
	Byte tmpBuf[30];
//	Char cStr[100];
	Byte mBuf[30];
	Word mP1;
	Word mP2;
	Word mP3;
	Word mP4;
	WORD rt;
	DWORD HID;
	DWORD SID;
	DWORD lP2;
	WORD mHand;
	DWORD mHardID;

   version DongleVersion;
   int GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3);


};
#endif
