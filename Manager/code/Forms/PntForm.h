//---------------------------------------------------------------------------

#ifndef PntFormH
#define PntFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlowButton.hpp"
#include "hyiedefs.hpp"
#include "hyieutils.hpp"
#include "iesettings.hpp"
#include "ieview.hpp"
#include "iexBitmaps.hpp"
#include "iexLayers.hpp"
#include "iexRulers.hpp"
#include "imageenview.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include "htmlbtns.hpp"
#include "AdvOfficeButtons.hpp"
#include "AdvWiiProgressBar.hpp"

#include "ToolsForm.h"
#include "TeeTree.hpp"
#include "rulerbox.hpp"
#include "AdvScrollBox.hpp"
#include "iegradientbar.hpp"
#include "LitoFileCreatorUnit.h"


#include <Vcl.ComCtrls.hpp>
#include "AdvTrackBar.hpp"
//---------------------------------------------------------------------------
class TPaintForm : public TForm
{
__published:	// IDE-managed Components

	TAdvGlowButton *SaveButton;
	TAdvGlowButton *CloseButton;
	TAdvGlowButton *OpenButton;
	TOpenPictureDialog *OpenPictureDialog;
	TPanel *PanelPaint;
	TImageEnView *ImageEnView;
	TImage *Image;
	TAdvWiiProgressBar *AdvWiiProgressBar;
	TAdvGlowButton *ToolsButton;
	TPanel *PanelResolution;
	TAdvGlassButton *AdvEditResolutionLbl;
	TCurvyEdit *AdvEditResolution;
	TAdvGlowButton *EditButton;
	TAdvScrollBox *ScrollBox;
	TIEGradientBar *ColorGradientBar;
	TPanel *ToolsPanel;
	TCurvyCombo *AdvComboBoxTools;
	TPanel *PanelWidth;
	TAdvGlassButton *AdvEditWidthLbl;
	TCurvyEdit *AdvEditWidth;
	TAdvGlassButton *AdvComboBoxToolsLbl;
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

//	void __fastcall ImageMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
//	void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift,int X, int Y);
//	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall SaveButtonClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ToolsButtonClick(TObject *Sender);
	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ImageMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall EditButtonClick(TObject *Sender);
	void __fastcall AdvComboBoxToolsChange(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TPaintForm(TComponent* Owner);

	bool first;
	bool select;
	bool drag;

	int x;
	int y;

	bool CreateVfile(int resolution);


	int img_index;

	void GrayStylePic();
	TRGBTriple *ptr;

	bool main;
	TBitmap* LastBitmap;
	TBitmap* GrayBitmap;
	TPicture* LastPicture;
	void CreatObjects();
	int paint_state;
	bool painting;
	int Color;

	TToolsFrm* myTools;

	void SetImagePainting(int state, int color, int width);

	void InitPaint();

	int x1;
	int y1;
	int x2;
	int y2;

	TBitmap* HoldingArea;
	TRect R1;
	TRect R2;

	void Capture(int x1, int y1, int x, int y);
	bool HoldingSomtings;
	int widthRec;

	int FileDataTime;
	LithoFileCreatorThread* myLithoThread;
	bool BitMapSaved;


};
//---------------------------------------------------------------------------
extern PACKAGE TPaintForm *PaintForm;
//---------------------------------------------------------------------------
#endif
