//---------------------------------------------------------------------------

#ifndef PiezoFormH
#define PiezoFormH
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
#include "VCLTee.TeeLinearGauge.hpp"
#include "VCLTee.TeeNumericGauge.hpp"
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TPiezoFrm : public TForm
{
__published:	// IDE-managed Components
	TShape *Shape1;
	TImage *Image1;
	TImage *Image2;
	TLabel *LabelPiezoValue;
	TShape *Shape2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TPiezoFrm(TComponent* Owner);

	void ModifyPiezo(int value);

	int height;
	int width;

	bool first;

	int PenWidth;
	int zero;

	int buttom;

	void LoadPicture();

	int L1;
	int L2;
	int W1;
	int W2;
	int H1;
	int H2;

	TPicture* GreenPicGround;
	TPicture* OrangePicGround;
	TPicture* YellowPicGround;
	TPicture* RedPicGround;

	TPicture* GreenPicPeizo;
	TPicture* OrangePicPeizo;
	TPicture* YellowPicPeizo;
	TPicture* RedPicPeizo;

	int LastTmp;
	int Tmp;

	bool all_scale;

    int PizoState;
};
//---------------------------------------------------------------------------
extern PACKAGE TPiezoFrm *PiezoFrm;
//---------------------------------------------------------------------------
#endif
