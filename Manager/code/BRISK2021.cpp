//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
//USEFORM("Forms\MovingForm.cpp", MvFrm);
//USEFORM("Forms\ImgClass.cpp", ImgForm);
//USEFORM("Forms\PanelsForm.cpp", CtrlForm);
//USEFORM("Forms\oscClass.cpp", oscForm);
//USEFORM("Forms\DncFrm.cpp", DynamicCurveForm);
//USEFORM("Forms\ApproachFrm.cpp", ApproachPanelForm);
//USEFORM("Forms\crossClass.cpp", CrossForm);
//USEFORM("Forms\ControlPanelFrm.cpp", ControlPanelForm);
//USEFORM("Forms\PiezoForm.cpp", PiezoFrm);
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Forms\oscClass.cpp", oscForm);
USEFORM("Forms\OscConfigFrm.cpp", OscConfigForm);
USEFORM("Forms\LithoForm.cpp", LithoFrm);
USEFORM("Forms\MovingForm.cpp", MvFrm);
USEFORM("Forms\PaintShapeForm.cpp", ShapeForm);
USEFORM("Forms\PntForm.cpp", PaintForm);
USEFORM("Forms\QuestionForm.cpp", QFrm);
USEFORM("Forms\PanelsForm.cpp", CtrlForm);
USEFORM("Forms\PiezoForm.cpp", PiezoFrm);
USEFORM("Forms\ForceForm.cpp", ForceFrm);
USEFORM("Forms\DncFrm.cpp", DynamicCurveForm);
USEFORM("Forms\ForceChartFrm.cpp", ForceChartForm);
USEFORM("Forms\Image.cpp", ImageShapeForm);
USEFORM("Forms\LithoConfigPage.cpp", FormLithoConfig);
USEFORM("Forms\LithoDesignPage.cpp", FormLithoDesign);
USEFORM("Forms\ImgClass.cpp", ImgForm);
USEFORM("Forms\KpfmForm.cpp", KpfmFrm);
USEFORM("Forms\SettingForm.cpp", SettingFrm);
USEFORM("Forms\SplashScreenForm.cpp", SplashForm);
USEFORM("Forms\RowConfigFrm.cpp", RowFrm);
USEFORM("Forms\ScanFrm.cpp", ScanPanelForm);
USEFORM("Forms\ToolsForm.cpp", ToolsFrm);
USEFORM("Forms\ViewerForm.cpp", ViewerFrm);
USEFORM("mainUnit.cpp", mainForm);
USEFORM("Forms\VidClass.cpp", VidForm);
USEFORM("Forms\VidSettingForm.cpp", VidSettingFrm);
USEFORM("Forms\crossClass.cpp", CrossForm);
USEFORM("Forms\ApproachFrm.cpp", ApproachPanelForm);
USEFORM("Forms\ConfigTable.cpp", ConfTable);
USEFORM("Forms\ControlPanelFrm.cpp", ControlPanelForm);
USEFORM("Forms\ColibrationConfigRows.cpp", Colibration);
USEFORM("Forms\ConfigFrm.cpp", ConfigForm);
USEFORM("Forms\GalleryForm.cpp", GalleyForm);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TmainForm), &mainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);

	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
