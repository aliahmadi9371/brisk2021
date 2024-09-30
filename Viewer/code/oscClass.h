//---------------------------------------------------------------------------

#ifndef oscClassH
#define oscClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>

#include "queueClass.h"
#include "VCLTee.TeeTools.hpp"
#include "VCLTee.TeeEdit.hpp"
#include "VCLTee.TeeComma.hpp"
//---------------------------------------------------------------------------
class ToscForm : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ComboBox_Wave;
	TChart *Chart;
	TFastLineSeries *Series;
	TCursorTool *ChartToolHori;
	TCursorTool *ChartToolVert;
	TPanel *Panel_Buttom;
	TPanel *Panel_Top;
	TComboBox *ComboBox_Scale;
	TTeeCommander *TeeCommander;
	TChartEditor *ChartEditor;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboBox_WaveChange(TObject *Sender);
	void __fastcall ComboBox_ScaleChange(TObject *Sender);


private:	// User declarations

public:		// User declarations
	__fastcall ToscForm(TComponent* Owner);
	void initForm();
    bool bool_created;

	queueClass oscQueue;
	void createComboBox();

	int main_data_count;
	int time_length_prime;
    int j;
	int main_time;
	int main_step;
	int main_time_step;

	void CreateUnit(int index);
	void CreateWaveTitle(int index);
    double X_dots;
};
//---------------------------------------------------------------------------
extern PACKAGE ToscForm *oscForm;
//---------------------------------------------------------------------------
#endif
