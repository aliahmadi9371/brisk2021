//---------------------------------------------------------------------------

#ifndef LithoFormH
#define LithoFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvPanel.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "AdvGlowButton.hpp"
#include <Vcl.ExtDlgs.hpp>
#include <jpeg.hpp>
#include "PlanImageDraw.hpp"
#include "Planner.hpp"
#include "PictureContainer.hpp"
#include <Vcl.Dialogs.hpp>

#include "LithoConfigPage.h"
#include "LithoDesignPage.h"
//---------------------------------------------------------------------------
class TLithoFrm : public TForm
{
__published:	// IDE-managed Components
	TAdvPanel *PanelSubLitho;
	TPanel *PanelLithoPages;
	TPanel *PanelLithoLabel;
	TLabel *LithoLabel;
	TAdvGlowButton *LithoConfigPageButton;
	TAdvGlowButton *LithoDesignPageButton;
	TPanel *PanelPages;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall LithoConfigPageButtonClick(TObject *Sender);
	void __fastcall LithoDesignPageButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TLithoFrm(TComponent* Owner);
	void InitValues();
	void CreateObjects();
	void ConfigClass();

	TOpenPictureDialog* dialog;
	TPicture *Picture;


	bool first;
	bool firstFolder;

	TFormLithoConfig* LithoConfigFrm;
	bool ConfigPage;

	TFormLithoDesign* LithoDesignFrm;
	bool DesignPage;
};
//---------------------------------------------------------------------------
extern PACKAGE TLithoFrm *LithoFrm;
//---------------------------------------------------------------------------
#endif
