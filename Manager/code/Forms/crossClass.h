//---------------------------------------------------------------------------

#ifndef crossClassH
#define crossClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "VCLTee.TeeTools.hpp"
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.BubbleCh.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.BubbleCh.hpp>
#include "VCLTee.TeeTools.hpp"
#include "VCLTee.TeePageNumTool.hpp"
//---------------------------------------------------------------------------
class TCrossForm : public TForm
{
__published:	// IDE-managed Components
	TChart *crsChart;
	TCursorTool *ChartTool1;
	TBubbleSeries *crossSeries;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCrossForm(TComponent* Owner);
	bool created;
	int x,y,z;

	int Gain;
    bool GainChainge;
	int ApproachTb;
	int ApproachAmp;
	void modified_cross();

	bool transparent;
	bool all_scale;
};
//---------------------------------------------------------------------------
extern PACKAGE TCrossForm *CrossForm;
//---------------------------------------------------------------------------
#endif
