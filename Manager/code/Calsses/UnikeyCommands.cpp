//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnikeyCommands.h"
#include "mainUnit.h"
#include "globals.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

DWORD UniKeyClass::FindDongle()
{
	mainForm->LogToFile("UniKeyClass::FindDongle");
	rt = UniKey_Find(&mHand, &HID, &lP2);
	if (rt != 0)
		HID = 0;
	UnicodeString hid = HID;

	return HID;

}
//---------------------------------------------------------------------------

void UniKeyClass::OpenDongle()
{
	mainForm->LogToFile("UniKeyClass::OpenDongle");
	mP1 = 49675;
	mP2 = 13171;
	mP3 = 1848;
	mP4 = 21313;
	mHardID = HID;
	rt = UniKey_User_Logon(&mHand, &mP1, &mP2);
}
//---------------------------------------------------------------------------

void UniKeyClass::WriteResetLicence()
{
	mP1 = 19;
	mP2 = 24;

	for(int i = 0; i<30; i++)
		mBuf[i] = 0;

	rt = UniKey_Write_Memory(&mHand, &mP1, &mP2, &mBuf[0]);
//	if (rt != 0){
//	  str = "UniKey__Write_Memory Failed! Error code: ";
////	  FmtStr(str, 'UniKey__Write_Memory Failed! Error code: %d', [rt]);
//	  output->Lines->Append(str + rt);
//	}
//	else{
//	  str = "UniKey__Write_Memory: StartAddr = ";
////	  FmtStr(str, 'UniKey__Write_Memory: StartAddr = %d, Length = %d, Data = %s', [mp1, mp2, PAnsiChar(@mbuf[0])]);
//	  output->Lines->Append(str + mP1 + " , Length = " + mP2 + " , Data = " + PAnsiChar(&mBuf[0]));
//	}

}
//---------------------------------------------------------------------------

int UniKeyClass::ReadDongle()
{
	mainForm->LogToFile("UniKeyClass::ReadDongle");
	 mP1 = 5;
	 mP2 = 24;
	 rt = UniKey_Read_Memory(&mHand, &mP1, &mP2, &tmpBuf[0]);


	 DongleVersion.major1 = tmpBuf[0];
	 DongleVersion.major2 = tmpBuf[1];
	 DongleVersion.minor1 = tmpBuf[2];
	 DongleVersion.minor2 = tmpBuf[3];


	 if(tmpBuf[4] == 1)
		HaveLicense = true;
	 else
		HaveLicense = false;

	 int DBPass[6];
	 UnicodeString Pass = "";
	 for(int i = 0 ; i<6; i++){
		DBPass[i] = tmpBuf[i+6];
		Pass = Pass + IntToStr(DBPass[i]);
	 }
	 DBPassWord = Pass;

	 mainForm->ClientID = GetNewData(0,0,tmpBuf[12],tmpBuf[13]);
	 mainForm->LicenseTime = GetNewData(tmpBuf[14],tmpBuf[15],tmpBuf[16],tmpBuf[17]);


	 if(tmpBuf[18] == 1)
		mainForm->ResetLicense = true;
	 else
		mainForm->ResetLicense = false;

	 return tmpBuf[5];
}
//---------------------------------------------------------------------------

DWORD UniKeyClass::ReadSoftID()
{
	mainForm->LogToFile("UniKeyClass::ReadSoftID");

	SID = 0;
	rt = UniKey_Read_SoftID(&mHand, &SID);
    if (rt != 0)
		SID = 0;

	UnicodeString sid = SID;

	return SID;
}
//---------------------------------------------------------------------------

void UniKeyClass::LogOff()
{
	mainForm->LogToFile("UniKeyClass::LogOff");
	rt = UniKey_Logoff(&mHand);
}
//---------------------------------------------------------------------------

int UniKeyClass::GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3)
{
	unsigned char tmp1[4] ;
	 for(int i=0; i<4;i++)
		tmp1[i] = 0;
	 int tmp = 0 ;
	 memset(tmp1,0x00,4);

	 tmp1[0] = data3;
	 tmp1[1] = data2;
	 tmp1[2] = data1;
	 tmp1[3] = data0;
	 memcpy((void *)&tmp , (void *)tmp1 , 4);


	 return tmp;
}
