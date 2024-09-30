//---------------------------------------------------------------------------

#ifndef mainUnitH
#define mainUnitH
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
#include <System.SysUtils.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.FileCtrl.hpp>
#include "VCLTee.TeeSurfa.hpp"
#include "VCLTee.TeeComma.hpp"
#include <Vcl.ActnColorMaps.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include "ipwftp.h"
#include "AdvGroupBox.hpp"
#include "AdvBadge.hpp"
#include "AdvEdit.hpp"
#include "AdvWiiProgressBar.hpp"
#include "AdvPanel.hpp"
#include "AdvSmoothPanel.hpp"
#include "CalcEdit.hpp"
#include "DBAdvEd.hpp"
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include "htmlbtns.hpp"
#include <string>
#include <iostream>
#include <Vcl.Menus.hpp>
#include <System.Diagnostics.hpp>
#include <IniFiles.hpp>
#include "VCLTee.TeeEdit.hpp"
//#inclide <SystemTypes.h>
#include "LoggerThread.h"


#include "UdpUnit.h"
#include "TcpUnit.h"
#include "ImagerUnit.h"
#include "CommandCreatorUnit.h"
#include "SplashScreenForm.h"
#include "oscClass.h"
#include "crossClass.h"
#include "VidClass.h"
#include "ImgClass.h"
#include "PanelsForm.h"
#include "ControlPanelFrm.h"
#include "ScanFrm.h"
#include "ApproachFrm.h"
#include "DncFrm.h"
#include "MovingForm.h"
#include "PiezoForm.h"
#include "ForceForm.h"
#include "SettingForm.h"
#include "LithoForm.h"
#include "GalleryForm.h"
#include "KpfmForm.h"
#include "DataBase.h"
#include "UnikeyCommands.h"

struct Version{
	int major1;
	int major2;
	int minor1;
	int minor2;
};
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *bot_pnl;
	TPanel *vid_pnl;
	TPanel *img_pnl;
	TPanel *ctrl_pnl;
	TPanel *ptz_sub_pnl;
	TPanel *osc_sub_pnl;
	TTimer *ChartTimer2;
	TAdvWiiProgressBar *ExitAdvWiiProgressBar;
	TPanel *ext_pnl;
	TPanel *crslbl_pnl;
	TPanel *crscht_pnl;
	TCurvyEdit *Label1;
	TCurvyEdit *Label2;
	TCurvyEdit *Label3;
	TLabel *Label4;
	THTMLRadioButton *Gain100;
	THTMLRadioButton *Gain10;
	THTMLRadioButton *Gain1;
	TPanel *crslbl_pnl_zoom;
	TCurvyEdit *Label5;
	TCurvyEdit *Label6;
	TCurvyEdit *Label7;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ChartTimer2Timer(TObject *Sender);
	void __fastcall Gain100Click(TObject *Sender);
	void __fastcall Gain10Click(TObject *Sender);
	void __fastcall Gain1Click(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall Label2Click(TObject *Sender);
	void __fastcall Label3Click(TObject *Sender);
	void __fastcall crslbl_pnlClick(TObject *Sender);



private:	// User declarations
    void __fastcall ChartTimerTimer(TObject *Sender);
public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
	__fastcall ~TmainForm();



	void ShowAfrerSpalsh();
	void CreateMenu(TComboBox *ComboBox);
	void CreatePanels();
	void RunApplication();
	void RunOsc();
	void RunMainChart();

    void Confige();

	TTimer* ChartTimer;
    void createPanels();

	void RunUdpThread();
	void RunScanThread();
	void RunCommanderThread();
	void RunImagerThread();
	void RunTCPThread();

	void ShowSplash();
	void ShowCamera();
	void ShowOsc();
	void ShowControlPanel();
	void ShowImageBox();
	void ShowPiezo();

	void ExitApp();

	void LogToFile(AnsiString Message);


	UdpThread* myUdpThread;
	TcpThread* myTcpThread;
	ImagerThread* myImagerThread;
	CommandCreatorThread* myCommandCreatorThread;


	TRect MainRect;

	bool Approaching;
	bool Approached;
	bool Scaning;
	bool Forcing;
	bool Lithoing;
	bool CameraMoving;
	bool StageMoving;
    bool Kpfming;

	int AppMode;
//	int Scanner_Type;
	int Max_Range;

//	TSplashForm* mySplashForm;
	TCrossForm* myCrossForm;
	ToscForm* myOscForm;
	TVidForm* myVideoForm;
	TImgForm* myImageFrom;
	TCtrlForm* myMainControlPanelForm;
	TControlPanelForm *myControlPanelForm;
	TScanPanelForm* myScanPanelForm;
	TApproachPanelForm* myApproachPanelForm;
	TDynamicCurveForm* myDynamicCurvePanelForm;
	TMvFrm* myMovingPanelForm;
	TPiezoFrm* myPiezoFrom;
	TForceFrm* myForceForm;
	TSettingFrm* mySettingForm;
	TLithoFrm* myLithoFrm;
	TGalleyForm* GalFrm;
	TKpfmFrm* myKpfmFrm;
	DataBaseClass* myDataBase;
	UniKeyClass* myUniKey;

	double X_Range[200];
	double Y_Range[200];

	bool firstchart;

	UnicodeString CurrentPicFolderName;

	void CreateLoger();

	double avg(double a, double b);


	LoggerThread* myLoggerThread;
	void StartLogger();

	int GetSecure();

	bool ResetLicense;

	int Mode;


	Version SoftwareVersion;
	bool VersionTrue;
	int LicenseTime;
    int ClientID;

};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
