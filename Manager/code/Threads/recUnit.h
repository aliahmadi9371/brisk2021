//---------------------------------------------------------------------------

#ifndef recUnitH
#define recUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.SysUtils.hpp>

#include <string>
#include <iostream>


#include "defines.h"
#include "rec_queueClass.h"
//---------------------------------------------------------------------------
class recUnit : public TThread
{
protected:
	void __fastcall Execute();
	TFileStream *file;

public:
	__fastcall recUnit(bool CreateSuspended);
	__fastcall ~recUnit();
	void StopRecod();

	bool thread_stop;
	bool thread_started;
	bool finishing;
    UnicodeString source;
	UnicodeString dest;
	UnicodeString pm;
	rec_queueClass *my_rec_queueClass;
};
//---------------------------------------------------------------------------
#endif
