//---------------------------------------------------------------------------

#ifndef MovingFormH
#define MovingFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "AdvShapeButton.hpp"
#include "AdvGlowButton.hpp"

#include "htmlbtns.hpp"
#include "AdvOfficeButtons.hpp"
#include "AdvTrackBar.hpp"
#include "AdvPanel.hpp"
#include "CurvyControls.hpp"
#include "AdvGlassButton.hpp"
//---------------------------------------------------------------------------
class TMvFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *CoarsePanel;
	TPanel *PanelShape;
	TImage *ImageTriangle;
	TDBAdvGlowButton *DBAdvGlowButtonA;
	TDBAdvGlowButton *DBAdvGlowButtonB;
	TDBAdvGlowButton *DBAdvGlowButtonC;
	TDBAdvGlowButton *DBAdvGlowButtonAll;
	TDBAdvGlowButton *LeftButton;
	TDBAdvGlowButton *FrontButton;
	TDBAdvGlowButton *RightButton;
	TDBAdvGlowButton *BackButton;
	TPanel *StagePanel;
	TDBAdvGlowButton *UpCoarseButton;
	TDBAdvGlowButton *DownCoarseButton;
	TAdvGlowButton *FastStageButton;
	TAdvGlowButton *FastCoarseButton;
	TPanel *PanelUpDown;
	TAdvPanel *PanelSubStage;
	TPanel *PanelLabelApproach;
	TLabel *LabelApproach;
	TAdvPanel *PanelSubCoarse;
	TPanel *PanelLabelCoarse;
	TLabel *LabelCoarse;
	TCurvyEdit *RightNumber;
	TCurvyEdit *FrontNumber;
	TCurvyEdit *BackNumber;
	TCurvyEdit *LeftNumber;
	TPanel *PanelUp;
	TAdvGlassButton *AdvEditUpLbl;
	TCurvyEdit *AdvEditUp;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall UpButtonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall UpButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall DownButtonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall DownButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DBAdvGlowButtonAClick(TObject *Sender);
	void __fastcall DBAdvGlowButtonCClick(TObject *Sender);
	void __fastcall DBAdvGlowButtonBClick(TObject *Sender);
	void __fastcall DBAdvGlowButtonAllClick(TObject *Sender);
	void __fastcall LeftButtonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall LeftButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall RightButtonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall RightButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FrontButtonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FrontButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BackButtonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BackButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall DBAdvGlowButtonRetractClick(TObject *Sender);
	void __fastcall FastStageButtonClick(TObject *Sender);
	void __fastcall FastCoarseButtonClick(TObject *Sender);
	void __fastcall AdvEditUpKeyPress(TObject *Sender, System::WideChar &Key);

private:	// User declarations
	void __fastcall StepperRetract();
public:		// User declarations
	__fastcall TMvFrm(TComponent* Owner);
	void EnabledMoving(bool enabled);

	void CheckUnCkeck(bool A, bool B, bool C, bool all, bool fast);
	byte StateM;
	bool SShift;
	int Mode;

	void CreateStepperPanel(int h, int w);

	bool first;

	void LoadPictures();

	TGDIPPicture* StepperPic;
	TGDIPPicture* StepperPicHover;
//
	TGDIPPicture* CenterPic;
	TGDIPPicture* CenterPicHover;

	TGDIPPicture* UpPic;
	TGDIPPicture* UpPicHover;

	TGDIPPicture* DownPic;
	TGDIPPicture* DownPicHover;

	TGDIPPicture* LeftPic;
	TGDIPPicture* LeftPicHover;

	TGDIPPicture* RightPic;
	TGDIPPicture* RightPicHover;

	TGDIPPicture* UpCoarsePic;
	TGDIPPicture* UpCoarseHover;

	TGDIPPicture* DownCoarsePic;
	TGDIPPicture* DownCoarsePicHover;

	bool AStepper;
	bool BStepper;
	bool CStepper;
	bool AllStepper;

	void UpDownBorder(TGlowButtonAppearance* appearance, bool UpDown);

	bool FastStage;
	bool FastCoarse;
};
//---------------------------------------------------------------------------
extern PACKAGE TMvFrm *MvFrm;
//---------------------------------------------------------------------------
#endif
