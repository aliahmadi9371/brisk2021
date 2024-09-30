//---------------------------------------------------------------------------

#ifndef SplashScreenFormH
#define SplashScreenFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvTreeComboBox.hpp"
#include "AdvWiiProgressBar.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "AdvGlowButton.hpp"
#include "CurvyControls.hpp"
#include "HTMLabel.hpp"
#include "dbhtmlab.hpp"
//---------------------------------------------------------------------------
class TSplashForm : public TForm
{
__published:	// IDE-managed Components
	TAdvWiiProgressBar *AdvWiiProgressBar;
	TImage *Image1;
	TPanel *Panel1;
	TLabel *LabelTel;
	TCurvyCombo *ComboBoxModes;
	TDBAdvGlowButton *Button2;
	TDBAdvGlowButton *Button1;
	TLabel *LabelUrl;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *ExpiredLabel;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LabelUrlMouseEnter(TObject *Sender);
	void __fastcall LabelUrlMouseLeave(TObject *Sender);
	void __fastcall LabelUrlClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSplashForm(TComponent* Owner);
	__fastcall ~TSplashForm();
	void SetMainGeo(int top, int left);
	void SetMainSize(int width, int height);
	void SetOtherGeo();

	int GetItemIndex(int mode);
	int GetAppMode(int index);


	bool FirstShow;

	int mode;

	bool first;

	AnsiString url;

};
//---------------------------------------------------------------------------
extern PACKAGE TSplashForm *SplashForm;
//---------------------------------------------------------------------------
#endif
