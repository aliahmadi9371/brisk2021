//---------------------------------------------------------------------------

#ifndef ViewerFormH
#define ViewerFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlowButton.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TViewerFrm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TDBAdvGlowButton *DBAdvGlowButtonNext;
	TDBAdvGlowButton *DBAdvGlowButtonPerior;
	TAdvGlowButton *CloseButton;
	TLabel *Label;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall DBAdvGlowButtonNextClick(TObject *Sender);
	void __fastcall DBAdvGlowButtonPeriorClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TViewerFrm(TComponent* Owner);

	bool first;

	int current_image_number;
	int current_image_count;
};
//---------------------------------------------------------------------------
extern PACKAGE TViewerFrm *ViewerFrm;
//---------------------------------------------------------------------------
#endif
