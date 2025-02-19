//---------------------------------------------------------------------------

#ifndef VidClassH
#define VidClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IniFiles.hpp>
#include "VidGrab.hpp"
#include "AdvGroupBox.hpp"


#include "UdpDataSendClass.h"

#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include "PickDlg.hpp"

#include "VidSettingForm.h"
#include "AdvGlowButton.hpp"
#include "AdvShapeButton.hpp"
//---------------------------------------------------------------------------
class TVidForm : public TForm
{
__published:	// IDE-managed Components
	TVideoGrabber *VideoGrabber1;
	TButton *ShotButton;
	TDBAdvGlowButton *BackButton;
	TDBAdvGlowButton *FrontButton;
	TDBAdvGlowButton *LeftButton;
	TDBAdvGlowButton *RightButton;
	TDBAdvGlowButton *SetButton;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall LeftButton1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall LeftButton1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FrontButton1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FrontButton1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall RightButton1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall RightButton1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BackButton1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BackButton1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall SetButton1Click(TObject *Sender);
	void __fastcall ShotButtonClick(TObject *Sender);
	void __fastcall VideoGrabber1MouseLeave(TObject *Sender, int VideoWindow);
	void __fastcall VideoGrabber1MouseEnter(TObject *Sender, int VideoWindow);

private:	// User declarations
	int Camera_Index;

	void __fastcall StepperStage();
public:		// User declarations
	__fastcall TVidForm(TComponent* Owner);
	void EnableStage(bool enabled);

	bool usb_camera;

	void SetRecordFile();

	void Left_start();
	void Left_stop();

	void Right_start();
	void Right_stop();

	void Front_start();
	void Front_stop();

	void Back_start();
	void Back_stop();

	bool first;

	byte StateM;
	int StatusMove;
	int Stop;
	bool SShift;

	bool record;

	TVidSettingFrm* myVidSettingForm;

	void BringToFront();
};
//---------------------------------------------------------------------------
extern PACKAGE TVidForm *VidForm;
//---------------------------------------------------------------------------
#endif
