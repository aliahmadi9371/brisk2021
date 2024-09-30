//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#pragma hdrstop

#include "recUnit.h"
#pragma package(smart_init)
#include "mainUnit.h"
#include "globals.h"
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall recUnit::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall recUnit::recUnit(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------

__fastcall recUnit::~recUnit()
{
	thread_started = false;
}
//---------------------------------------------------------------------------

void __fastcall recUnit::Execute()
{
	NameThreadForDebugging(System::String(L"record"));
	//---- Place thread code here ----

	thread_stop = false;
	thread_started = false;
	TDateTime dateTime;
	UnicodeString time = dateTime.CurrentDateTime().FormatString("hhMMss");
	UnicodeString date = dateTime.CurrentDateTime().FormatString("yyyymmdd");

	UnicodeString RecordFolder = DownloadPath + "/" + "records";
	if( !DirectoryExists(RecordFolder) ){
		AnsiString dir = RecordFolder;
		CreateDirectoryA(dir.c_str(),NULL);
	}
	switch(mainForm->AppMode){
		case 1:{
			if( !DirectoryExists(RecordFolder + "/" + "Contact") ){
				AnsiString dir = RecordFolder + "/" + "Contact";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "Contact/Osc") ){
				AnsiString dir = RecordFolder + "/" + "Contact/Osc";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "Contact/Osc" + "/" + date)){
				AnsiString dir = RecordFolder + "/" + "Contact/Osc" + "/" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "Contact/Osc" + "/" + date + "/" + time + ".afm";
			break;
		}
		case 2:{
			if( !DirectoryExists(RecordFolder + "/" + "NonContact") ){
				AnsiString dir = RecordFolder + "/" + "NonContact";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "NonContact/Osc") ){
				AnsiString dir = RecordFolder + "/" + "NonContact/Osc";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "NonContact/Osc" + "/" + date)){
				AnsiString dir = RecordFolder + "/" + "NonContact/Osc" + "/" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "NonContact/Osc" + "/" + date + "/" + time + ".afm";
			break;
		}
			case 3:{
			if( !DirectoryExists(RecordFolder + "/" + "MFM") ){
				AnsiString dir = RecordFolder + "/" + "MFM";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "MFM/Osc") ){
				AnsiString dir = RecordFolder + "/" + "MFM/Osc";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "MFM/Osc" + "/" + date)){
				AnsiString dir = RecordFolder + "/" + "MFM/Osc" + "/" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "MFM/Osc" + "/" + date + "/" + time + ".afm";
			break;
		}
			case 4:{
			if( !DirectoryExists(RecordFolder + "/" + "EFM") ){
				AnsiString dir = RecordFolder + "/" + "EFM";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "EFM/Osc") ){
				AnsiString dir = RecordFolder + "/" + "EFM/Osc";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "EFM/Osc" + "/" + date)){
				AnsiString dir = RecordFolder + "/" + "EFM/Osc" + "/" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "EFM/Osc" + "/" + date + "/" + time + ".afm";
			break;
		}

		case 5:{
			if( !DirectoryExists(RecordFolder + "/" + "ForceSpectroscopy") ){
				AnsiString dir = RecordFolder + "/" + "ForceSpectroscopy";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "ForceSpectroscopy/Osc") ){
				AnsiString dir = RecordFolder + "/" + "ForceSpectroscopy/Osc";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "ForceSpectroscopy/Osc" + "/" + date)){
				AnsiString dir = RecordFolder + "/" + "ForceSpectroscopy/Osc" + "/" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "ForceSpectroscopy/Osc" + "/" + date + "/" + time + ".afm";
			break;
		}
		case 6:{
			if( !DirectoryExists(RecordFolder + "/" + "KPFM") ){
				AnsiString dir = RecordFolder + "/" + "KPFM";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "KPFM/Osc") ){
				AnsiString dir = RecordFolder + "/" + "KPFM/Osc";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "KPFM/Osc" + "/" + date)){
				AnsiString dir = RecordFolder + "/" + "KPFM/Osc" + "/" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "KPFM/Osc" + "/" + date + "/" + time + ".afm";
			break;
		}
		case 7:{
			if( !DirectoryExists(RecordFolder + "/" + "Lithography") ){
				AnsiString dir = RecordFolder + "/" + "Lithography";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "Lithography/Osc") ){
				AnsiString dir = RecordFolder + "/" + "Lithography/Osc";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "Lithography/Osc" + "/"+ date)){
				AnsiString dir = RecordFolder + "/" + "Lithography/Osc" + "/" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "Lithography/Osc" + "/" + date + "/" + time + ".afm";
			break;
		}
		default:
			break;
	}


	file = new TFileStream(source,fmCreate);
	my_rec_queueClass = new rec_queueClass(1000);
	thread_started = true;

	while(thread_started){
		if(!(my_rec_queueClass->isEmpty())){
			DynamicArray<Byte> tmp = my_rec_queueClass->peek();
			file->WriteData(tmp,tmp.Length);
			my_rec_queueClass->dequeue();
		}
		if(finishing){
			while(!(my_rec_queueClass->isEmpty())){
				DynamicArray<Byte> tmp = my_rec_queueClass->peek();
				file->WriteData(tmp,tmp.Length);
				my_rec_queueClass->dequeue();
			}
			file->Free();
			delete file;
			delete[] my_rec_queueClass;
			thread_started = false;
			thread_stop = true;
			this->Terminate();

			return;
		}
//		S1eep(1);
	}
}
//---------------------------------------------------------------------------

void recUnit::StopRecod()
{
	finishing = true;
}
//---------------------------------------------------------------------------
