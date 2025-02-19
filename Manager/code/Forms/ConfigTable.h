//---------------------------------------------------------------------------

#ifndef ConfigTableH
#define ConfigTableH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "RowConfigFrm.h"
#include "OscConfigFrm.h"
#include "AdvGlassButton.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "ColibrationConfigRows.h"
//---------------------------------------------------------------------------
class TConfTable : public TForm
{
__published:	// IDE-managed Components
	TScrollBox *ScrollBox1;
	TPanel *HeaderPanel;
	TAdvGlassButton *AdvGlassButton27;
	TAdvGlassButton *AdvGlassButton28;
	TAdvGlassButton *AdvGlassButton29;
	TAdvGlassButton *AdvGlassButton30;
	TAdvGlassButton *AdvGlassButton31;
	TPanel *HeaderPanel2;
	TAdvGlassButton *AdvGlassButton1;
	TAdvGlassButton *AdvGlassButton2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ScrollBox1MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall ScrollBox1MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
private:	// User declarations
public:		// User declarations
	__fastcall TConfTable(TComponent* Owner);

	TRowFrm* myRows[7];
	TOscConfigForm* myOscConfigFrm[27];
	TColibration *myColibration[56];

	void InitValues();
	void CreatObjects();

	bool first;
	bool Showing;

};
//---------------------------------------------------------------------------
extern PACKAGE TConfTable *ConfTable;
//---------------------------------------------------------------------------
#endif
