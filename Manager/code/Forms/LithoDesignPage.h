//---------------------------------------------------------------------------

#ifndef LithoDesignPageH
#define LithoDesignPageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "AdvGlowButton.hpp"
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include "hyiedefs.hpp"
#include "hyieutils.hpp"
#include "iesettings.hpp"
#include "ieview.hpp"
#include "iexBitmaps.hpp"
#include "iexLayers.hpp"
#include "iexRulers.hpp"
#include "imageenview.hpp"
#include "iexBitmaps.hpp"

#include "PntForm.h"

//---------------------------------------------------------------------------
class TFormLithoDesign : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelPaint;
	TAdvGlowButton *ViewButton;
	TImage *Image;
	TScrollBox *ScrollBox;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ViewButtonClick(TObject *Sender);
	void __fastcall ImageDblClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFormLithoDesign(TComponent* Owner);


	void InitValues();
	void CreateObjects();
	void ConfigClass();

	bool first;
    bool Osc_PreviousState;

	TBitmap *map;



	TPaintForm* myPaintForm;
	void InitPaint(bool state);


};
//---------------------------------------------------------------------------
extern PACKAGE TFormLithoDesign *FormLithoDesign;
//---------------------------------------------------------------------------
#endif
