//---------------------------------------------------------------------------

#ifndef TopoFormH
#define TopoFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
//---------------------------------------------------------------------------
class TTopoFrm : public TForm
{
__published:	// IDE-managed Components
	TChart *TopoChart;
	TFastLineSeries *TopoFWSeries;
	TFastLineSeries *TopoBWSeries;
	TButton *ImagesButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ImagesButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TTopoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTopoFrm *TopoFrm;
//---------------------------------------------------------------------------
#endif
