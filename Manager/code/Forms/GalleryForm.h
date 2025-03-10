//---------------------------------------------------------------------------

#ifndef GalleryFormH
#define GalleryFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlowButton.hpp"
#include "AdvPanel.hpp"
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "Image.h"
#include "AdvScrollBox.hpp"

#include "ViewerForm.h"
#include "AdvGlassButton.hpp"

#include "CurvyControls.hpp"
#include "GWYMaker.h"
#include <fstream>
//---------------------------------------------------------------------------
class TGalleyForm : public TForm
{
__published:	// IDE-managed Components
	TAdvPanel *PanelSubGallery;
	TPanel *PanelLabelGallery;
	TLabel *LabelGallery;
	TAdvGlowButton *OpenButton;
	TOpenTextFileDialog *OpenTextFileDialog;
	TAdvScrollBox *AdvScrollBox;
	TMemo *Memo;
	TPanel *RangePanel;
	TAdvGlassButton *RangeAdvEditLbl;
	TAdvGlowButton *SaveButton;
	TCurvyEdit *AdvEditRange;
	TPanel *SaveInfoPanel;
	TPanel *ZUnitPanel;
	TAdvGlassButton *AdvGlassButton1;
	TCurvyCombo *AdvComboBoxSelect;
	TPanel *ScalePanel;
	TAdvGlassButton *AdvGlassButton2;
	TCurvyEdit *IndexAdvEdit;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall AdvScrollBoxMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall AdvScrollBoxMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SaveButtonClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TGalleyForm(TComponent* Owner);
	void ReadFromIntFile(bool txt ,int ImageNum ,UnicodeString FileAdd);
	int GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3);

	bool first;

	void InitVal();
	void CreateObjects();
	void ConfigClass();
	void InitDir();

	TImageShapeForm* Images;
	TImageShapeForm** image_address_array;
	TViewerFrm* myViewer;
	int currentimagecount;
	UnicodeString OpenedFileName;
	double SaveRange;
	int SaveResolution;
	GWYMakerClass* myGWYMaker;
	ifstream intdata;
    bool Osc_PreviousState;
};
//---------------------------------------------------------------------------
extern PACKAGE TGalleyForm *GalleyForm;
//---------------------------------------------------------------------------
#endif
