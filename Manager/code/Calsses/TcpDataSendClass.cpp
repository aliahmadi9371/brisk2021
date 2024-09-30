//---------------------------------------------------------------------------

#pragma hdrstop

#include "TcpDataSendClass.h"
#include "defines.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

DynamicArray<Byte> TcpDataSendClass::ScanXFilePacket(int* Data , int itemCount)
{
	DynamicArray<Byte> bytes;
	bytes.Length = itemCount * 4 + 9;
	mainForm->LogToFile("itemCount = " + IntToStr(itemCount));
	mainForm->LogToFile("XLength = " + IntToStr(bytes.Length));
	for(int i=0; i<itemCount; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = SCANNING_FRAME;
	bytes[3] = 0x00;

	//resolution
	bytes[4] = (byte)((itemCount >> 24) & 0xFF);
	bytes[5] = (byte)((itemCount >> 16) & 0xFF);
	bytes[6] = (byte)((itemCount >> 8) & 0xFF);
	bytes[7] = (byte)((itemCount >> 0) & 0xFF);

//	mainForm->LogToFile("XLength HEX = " + IntToHex(bytes[4], 2) + " " + IntToHex(bytes[5], 2) + " " + IntToHex(bytes[6], 2) + " " + IntToHex(bytes[7], 2));


	for(int i=0; i<itemCount; i++){
		int j = i * 4 + 8;
		bytes[j] = (byte)((Data[i] >> 24) & 0xFF);
		bytes[j+1] = (byte)((Data[i] >> 16) & 0xFF);
		bytes[j+2] = (byte)((Data[i] >> 8) & 0xFF);
		bytes[j+3] = (byte)((Data[i] >> 0) & 0xFF);
	}

	bytes[bytes.Length-1] = '\0';

	delete mainForm->myCommandCreatorThread->myScan->myScanFileCreator->XFileTcpData;
	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> TcpDataSendClass::ScanYFilePacket(int* Data , int itemCount)
{
	DynamicArray<Byte> bytes;
	bytes.Length = itemCount * 4 + 9;
	mainForm->LogToFile("itemCount = " + IntToStr(itemCount));
	mainForm->LogToFile("YLength = " + IntToStr(bytes.Length));
	for(int i=0; i<itemCount; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = SCANNING_FRAME;
	bytes[3] = 0x01 ;

	//resolution
	bytes[4] = (byte)((itemCount >> 24) & 0xFF);
	bytes[5] = (byte)((itemCount >> 16) & 0xFF);
	bytes[6] = (byte)((itemCount >> 8) & 0xFF);
	bytes[7] = (byte)((itemCount >> 0) & 0xFF);

	for(int i=0; i<itemCount; i++){
		int j = i * 4 + 8;
		bytes[j] = (byte)((Data[i] >> 24) & 0xFF);
		bytes[j+1] = (byte)((Data[i] >> 16) & 0xFF);
		bytes[j+2] = (byte)((Data[i] >> 8) & 0xFF);
		bytes[j+3] = (byte)((Data[i] >> 0) & 0xFF);
	}
	bytes[bytes.Length-1] = '\0';
	delete mainForm->myCommandCreatorThread->myScan->myScanFileCreator->YFileTcpData;
	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> TcpDataSendClass::ForceZFilePacket(int* Data , int itemCount)
{
    DynamicArray<Byte> bytes;
	bytes.Length = itemCount * 4 + 8;
	mainForm->LogToFile("itemCount = " + IntToStr(itemCount));
	mainForm->LogToFile("ZLength = " + IntToStr(bytes.Length));
	for(int i=0; i<itemCount; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = FORCE_SPEC_FRAME;
	bytes[3] = 0x00 ;

	//resolution
	bytes[4] = (byte)((itemCount >> 24) & 0xFF);
	bytes[5] = (byte)((itemCount >> 16) & 0xFF);
	bytes[6] = (byte)((itemCount >> 8) & 0xFF);
	bytes[7] = (byte)((itemCount >> 0) & 0xFF);

	for(int i=0; i<itemCount; i++){
		int j = i * 4 + 8;
		bytes[j] = (byte)((Data[i] >> 24) & 0xFF);
		bytes[j+1] = (byte)((Data[i] >> 16) & 0xFF);
		bytes[j+2] = (byte)((Data[i] >> 8) & 0xFF);
		bytes[j+3] = (byte)((Data[i] >> 0) & 0xFF);
	}
//	bytes[bytes.Length-1] = '\0';
	delete mainForm->myCommandCreatorThread->myFs->zpoints;
	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> TcpDataSendClass::ForceUFilePacket(int* Data , int itemCount)
{
    DynamicArray<Byte> bytes;
	bytes.Length = itemCount * 4 + 9;
	mainForm->LogToFile("itemCount = " + IntToStr(itemCount));
	mainForm->LogToFile("ULength = " + IntToStr(bytes.Length));
	for(int i=0; i<itemCount; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = FORCE_SPEC_FRAME;
	bytes[3] = 0x01 ;

	//resolution
	bytes[4] = (byte)((itemCount >> 24) & 0xFF);
	bytes[5] = (byte)((itemCount >> 16) & 0xFF);
	bytes[6] = (byte)((itemCount >> 8) & 0xFF);
	bytes[7] = (byte)((itemCount >> 0) & 0xFF);

	for(int i=0; i<itemCount; i++){
		int j = i * 4 + 8;
		bytes[j] = (byte)((Data[i] >> 24) & 0xFF);
		bytes[j+1] = (byte)((Data[i] >> 16) & 0xFF);
		bytes[j+2] = (byte)((Data[i] >> 8) & 0xFF);
		bytes[j+3] = (byte)((Data[i] >> 0) & 0xFF);
	}
	bytes[bytes.Length-1] = '\0';
	delete mainForm->myCommandCreatorThread->myFs->upoints;
	return bytes;
}
//---------------------------------------------------------------------------

DynamicArray<Byte> TcpDataSendClass::LithoXFilePacket(int* Data , int itemCount)
{
    DynamicArray<Byte> bytes;
	bytes.Length = itemCount * 4 + 13;
//	mainForm->LogToFile("XLength = " + IntToStr(bytes.Length));
	for(int i=0; i<itemCount; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = LITHO_FRAME;
	bytes[3] = 0x00;

	//resolution
	bytes[4] = (byte)((itemCount >> 24) & 0xFF);
	bytes[5] = (byte)((itemCount >> 16) & 0xFF);
	bytes[6] = (byte)((itemCount >> 8) & 0xFF);
	bytes[7] = (byte)((itemCount >> 0) & 0xFF);

	//line number
	bytes[8] = 0x00;
	bytes[9] = 0x00;
	bytes[10] = 0x00;
	bytes[11] = 0x00;

//	mainForm->LogToFile("XLength HEX = " + IntToHex(bytes[4], 2) + " " + IntToHex(bytes[5], 2) + " " + IntToHex(bytes[6], 2) + " " + IntToHex(bytes[7], 2));


	for(int i=0; i<itemCount; i++){
		int j = i * 4 + 12;
		bytes[j] = (byte)((Data[i] >> 24) & 0xFF);
		bytes[j+1] = (byte)((Data[i] >> 16) & 0xFF);
		bytes[j+2] = (byte)((Data[i] >> 8) & 0xFF);
		bytes[j+3] = (byte)((Data[i] >> 0) & 0xFF);
	}
	bytes[bytes.Length-1] = '\0';
	delete mainForm->myCommandCreatorThread->myLitho->myLithoFileCreator->LithoXFile;
	return bytes;

}
//---------------------------------------------------------------------------

DynamicArray<Byte> TcpDataSendClass::LithoYFilePacket(int* Data , int itemCount)
{
	DynamicArray<Byte> bytes;
	bytes.Length = itemCount * 4 + 13;
	mainForm->LogToFile("YLength = " + IntToStr(bytes.Length));
	for(int i=0; i<itemCount; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = LITHO_FRAME;
	bytes[3] = 0x01 ;

	//resolution
	bytes[4] = (byte)((itemCount >> 24) & 0xFF);
	bytes[5] = (byte)((itemCount >> 16) & 0xFF);
	bytes[6] = (byte)((itemCount >> 8) & 0xFF);
	bytes[7] = (byte)((itemCount >> 0) & 0xFF);

	//line number
	bytes[8] = 0x00;
	bytes[9] = 0x00;
	bytes[10] = 0x00;
	bytes[11] = 0x00;

	for(int i=0; i<itemCount; i++){
		int j = i * 4 + 12;
		bytes[j] = (byte)((Data[i] >> 24) & 0xFF);
		bytes[j+1] = (byte)((Data[i] >> 16) & 0xFF);
		bytes[j+2] = (byte)((Data[i] >> 8) & 0xFF);
		bytes[j+3] = (byte)((Data[i] >> 0) & 0xFF);
	}
	bytes[bytes.Length-1] = '\0';
	delete mainForm->myCommandCreatorThread->myLitho->myLithoFileCreator->LithoYFile;
	return bytes;

}
//---------------------------------------------------------------------------

DynamicArray<Byte> TcpDataSendClass::LithoVFilePacket(int* Data , int itemCount ,int LineNumber)
{
    DynamicArray<Byte> bytes;
	bytes.Length = itemCount * 4 + 13;
//	mainForm->LogToFile("VLength = " + IntToStr(bytes.Length));
	for(int i=0; i<itemCount; i++)
		bytes[i] = 0;

	bytes[0] = UPD_HEADER_0;
	bytes[1] = UPD_HEADER_1;
	bytes[2] = LITHO_FRAME;
	bytes[3] = 0x02 ;

	//resolution
	bytes[4] = (byte)((itemCount >> 24) & 0xFF);
	bytes[5] = (byte)((itemCount >> 16) & 0xFF);
	bytes[6] = (byte)((itemCount >> 8) & 0xFF);
	bytes[7] = (byte)((itemCount >> 0) & 0xFF);

	//line number
	bytes[8] = (byte)((LineNumber >> 24) & 0xFF);
	bytes[9] = (byte)((LineNumber >> 16) & 0xFF);
	bytes[10] = (byte)((LineNumber >> 8) & 0xFF);
	bytes[11] = (byte)((LineNumber >> 0) & 0xFF);


	for(int i=0; i<itemCount; i++){
		int j = i * 4 + 12;
		bytes[j] = (byte)((Data[i] >> 24) & 0xFF);
		bytes[j+1] = (byte)((Data[i] >> 16) & 0xFF);
		bytes[j+2] = (byte)((Data[i] >> 8) & 0xFF);
		bytes[j+3] = (byte)((Data[i] >> 0) & 0xFF);
	}
	bytes[bytes.Length-1] = '\0';
	return bytes;

}

