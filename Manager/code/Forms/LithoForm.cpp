//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LithoForm.h"
#include "mainUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvPanel"
#pragma link "AdvGlowButton"
#pragma link "PlanImageDraw"
#pragma link "Planner"
#pragma link "PictureContainer"
#pragma resource "*.dfm"
TLithoFrm *LithoFrm;
//---------------------------------------------------------------------------
__fastcall TLithoFrm::TLithoFrm(TComponent* Owner)
	: TForm(Owner)
{
	first = false;

}
//---------------------------------------------------------------------------

void TLithoFrm::InitValues()
{
	mainForm->LogToFile("TLithoFrm::InitValues");
	firstFolder = false;

	LithoConfigFrm = NULL;
//	LithoDesignFrm = NULL;

	ConfigPage = false;
	DesignPage = false;

}
//---------------------------------------------------------------------------

void TLithoFrm::CreateObjects()
{
	mainForm->LogToFile("TLithoFrm::CreateObjects");
	LithoConfigFrm = new TFormLithoConfig(this);
	LithoDesignFrm = new TFormLithoDesign(this);
}
//---------------------------------------------------------------------------

void TLithoFrm::ConfigClass()
{
	mainForm->LogToFile("TLithoFrm::ConfigClass");
//	Application->CreateForm(__classid(TFormLithoConfig), &FormLithoConfig);
	LithoConfigFrm->Parent = PanelPages;
	LithoConfigFrm->SetParentComponent(PanelPages);
//	LithoConfigFrm->Show();

//	Application->CreateForm(__classid(TFormLithoDesign), &FormLithoDesign);
	LithoDesignFrm->Parent = PanelPages;
	LithoDesignFrm->SetParentComponent(PanelPages);;

//	LithoDesignFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TLithoFrm::FormShow(TObject *Sender)
{
	mainForm->LogToFile("TLithoFrm::FormShow");
	if(!first){

		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;

		PanelSubLitho->Left = 20;
		PanelSubLitho->Top = 20;
		PanelSubLitho->Width = w_this - 40;
		PanelSubLitho->Height = h_this - 40;


		LithoConfigPageButtonClick(NULL);
		first = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TLithoFrm::FormCreate(TObject *Sender)
{
	mainForm->LogToFile("TLithoFrm::FormCreate");
	this->Hide();

	InitValues();
	CreateObjects();
	ConfigClass();
}
//---------------------------------------------------------------------------

void __fastcall TLithoFrm::LithoConfigPageButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TLithoFrm::LithoConfigPageButtonClick , ConfigPage = " + BoolToStr(ConfigPage,true));
	if(!ConfigPage){
		ConfigPage = true;
		DesignPage = false;

		LithoConfigPageButton->Appearance->BorderColor = TColor(0x00F0D27D);
		LithoConfigPageButton->Font->Color = TColor(0x00F0D27D);

		LithoDesignPageButton->Appearance->BorderColor = TColor(0x008B6757);
		LithoDesignPageButton->Font->Color = clWhite;

		LithoConfigFrm->Show();
		LithoDesignFrm->Hide();
	}


}
//---------------------------------------------------------------------------

void __fastcall TLithoFrm::LithoDesignPageButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TLithoFrm::LithoDesignPageButtonClick , DesignPage = " + BoolToStr(DesignPage,true));
	if(!DesignPage){
		ConfigPage = false;
		DesignPage = true;

        LithoConfigPageButton->Appearance->BorderColor = TColor(0x008B6757);
		LithoConfigPageButton->Font->Color = clWhite;

		LithoDesignPageButton->Appearance->BorderColor = TColor(0x00F0D27D);
		LithoDesignPageButton->Font->Color = TColor(0x00F0D27D);

		LithoConfigFrm->Hide();
		LithoDesignFrm->Show();
	}
}
//---------------------------------------------------------------------------

