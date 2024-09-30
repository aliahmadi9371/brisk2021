//---------------------------------------------------------------------------

#ifndef VidSettingFormH
#define VidSettingFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvCombo.hpp"
#include "CalcEdit.hpp"
#include "CurvyControls.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "AdvGlassButton.hpp"
//---------------------------------------------------------------------------
class TVidSettingFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelSubResolution;
	TCalcLabel *ResoulitionAdvComboBoxLbl;
	TCurvyCombo *ResoulitionAdvComboBox;
	TPanel *PanelLogo;
	TImage *ImageLogo;
	TPanel *PanelResolution;
	TPanel *PanelCameraName;
	TPanel *PanelCamera;
	TPanel *PanelSubCameraName;
	TCalcLabel *DeviceNameEditLbl;
	TPanel *PanelSubCamera;
	TCalcLabel *CameraAdvComboBoxLbl;
	TCurvyCombo *CameraAdvComboBox;
	TAdvGlassButton *DeviceNameEdit;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CameraAdvComboBoxChange(TObject *Sender);
	void __fastcall ResoulitionAdvComboBoxChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TVidSettingFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVidSettingFrm *VidSettingFrm;
//---------------------------------------------------------------------------
#endif
