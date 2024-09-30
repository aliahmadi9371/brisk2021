//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#pragma hdrstop

#include "NonExtractedLine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall NonExtractedLine::NonExtractedLine()
{
	SetCreated(false);
}
//---------------------------------------------------------------------------

NonExtractedLine::~NonExtractedLine()
{

}
//---------------------------------------------------------------------------

void NonExtractedLine::newObject(int myResolution)
{
//	bytes = new unsigned char[myResolution*4 + HEADER_COUNT_IMAGE]; // just data
	bytes.Length = myResolution*4 + HEADER_COUNT_IMAGE;
	SetCreated(true);
}
//---------------------------------------------------------------------------

void NonExtractedLine::newData(TByteDynArray myData,int myResolution)
{
	newObject(myResolution);
	if(GetCreated()){
//		for(int i=0; i<myResolution*4 + HEADER_COUNT_IMAGE; i++)
		bytes = myData;
	}
}
//---------------------------------------------------------------------------

void NonExtractedLine::resetData()
{
	if(Created)
        bytes.Length = 0;
//		delete[] bytes;
	SetCreated(false);
}
//---------------------------------------------------------------------------


