//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ApproachFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdit"
#pragma link "CalcEdit"
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma link "AdvPanel"
#pragma resource "*.dfm"
TApproachPanelForm *ApproachPanelForm;
//---------------------------------------------------------------------------
__fastcall TApproachPanelForm::TApproachPanelForm(TComponent* Owner)
	: TForm(Owner)
{
	first = false;
	fast_checkbox->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::FormCreate(TObject *Sender)
{
	this->Hide();
	GetIniToUi();
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::SetApproach()
{

    mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("APPROACH_CONFIG"));
	if(mainForm->Approached){
		mainForm->LogToFile(" TApproachPanelForm::SetApproach : Approached");
		mainForm->myCommandCreatorThread->StartApprochClick(0,true,true,0,false,0);
	}
	else{
		mainForm->LogToFile(" TApproachPanelForm::SetApproach : !Approached");
		mainForm->myCommandCreatorThread->StartApprochClick(0,false,false,0,false,0);
	}
}
//---------------------------------------------------------------------------

void TApproachPanelForm::GetIniToUi()
{
//	mainForm->LogToFile("GetIniToUi : ****************");

	all_scale = OscChartTable.all_scale;


	RefrenceApp = ApproachTable.Apr_Refrerence_Val;
	KiApp_Contact = ApproachTable.Apr_Ki_Val_Contact;
	KiApp_NonContact = ApproachTable.Apr_Ki_Val_NonContact;
	BiasApp = ApproachTable.Apr_Bias_Val;
	StpApp = ApproachTable.Apr_SteperStepMicro_Val_Precise;
	KdApp = ApproachTable.Apr_Kd_Val;
	KpApp = ApproachTable.Apr_Kp_Val;
	KiFeedback_Contact = ApproachTable.Apr_KiFeedbak_Val_Contact;
	KiFeedback_NonContact = ApproachTable.Apr_KiFeedbak_Val_NonContact;





	switch(mainForm->AppMode){
		case 1:{
			KiAdvEdit->Text = IntToStr(KiApp_Contact);
			BiasAdvEdit->Text = IntToStr(BiasApp);
			RefAdvEdit->Text = IntToStr(RefrenceApp);
			StpAdvEdit->Text = IntToStr(StpApp);
			KdAdvEdit->Text =  IntToStr(KdApp);
			KpAdvEdit->Text =  IntToStr(KpApp);
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_Contact);

			KiApp = KiApp_Contact;
			KiFeedBack = KiFeedback_Contact;
			break;
		}
		case 2:{
			KiAdvEdit->Text = IntToStr(KiApp_NonContact);
			BiasAdvEdit->Text = IntToStr(BiasApp);
			StpAdvEdit->Text = IntToStr(StpApp);
			RefAdvEdit->Text = IntToStr(RefrenceApp);
			KdAdvEdit->Text =  IntToStr(KdApp);
			KpAdvEdit->Text =  IntToStr(KpApp);
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);

			KiApp = KiApp_NonContact;
			KiFeedBack = KiFeedback_NonContact;
			break;
		}
		case 3:{
			KiAdvEdit->Text = IntToStr(KiApp_NonContact);
			BiasAdvEdit->Text = IntToStr(BiasApp);
			StpAdvEdit->Text = IntToStr(StpApp);
			RefAdvEdit->Text = IntToStr(RefrenceApp);
			KdAdvEdit->Text =  IntToStr(KdApp);
			KpAdvEdit->Text =  IntToStr(KpApp);
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);

			KiApp = KiApp_NonContact;
			KiFeedBack = KiFeedback_NonContact;
			break;
		}
		case 4:{
			KiAdvEdit->Text = IntToStr(KiApp_NonContact);
			BiasAdvEdit->Text = IntToStr(BiasApp);
			StpAdvEdit->Text = IntToStr(StpApp);
			RefAdvEdit->Text = IntToStr(RefrenceApp);
			KdAdvEdit->Text =  IntToStr(KdApp);
			KpAdvEdit->Text =  IntToStr(KpApp);
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);

			KiApp = KiApp_NonContact;
			KiFeedBack = KiFeedback_NonContact;
			break;
		}
		case 5:{
			KiAdvEdit->Text = IntToStr(KiApp_Contact);
			BiasAdvEdit->Text = IntToStr(BiasApp);
			StpAdvEdit->Text = IntToStr(StpApp);
			RefAdvEdit->Text = IntToStr(RefrenceApp);
			KdAdvEdit->Text =  IntToStr(KdApp);
			KpAdvEdit->Text =  IntToStr(KpApp);
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_Contact);

			KiApp = KiApp_Contact;
			KiFeedBack = KiFeedback_Contact;
			break;
		}
		case 6:{
			KiAdvEdit->Text = IntToStr(KiApp_NonContact);
			BiasAdvEdit->Text = IntToStr(BiasApp);
			StpAdvEdit->Text = IntToStr(StpApp);
			RefAdvEdit->Text = IntToStr(RefrenceApp);
			KdAdvEdit->Text =  IntToStr(KdApp);
			KpAdvEdit->Text =  IntToStr(KpApp);
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);

			KiApp = KiApp_NonContact;
			KiFeedBack = KiFeedback_NonContact;
			break;
		}
		case 7:{
			KiAdvEdit->Text = IntToStr(KiApp_Contact);
			BiasAdvEdit->Text = IntToStr(BiasApp);
			StpAdvEdit->Text = IntToStr(StpApp);
			RefAdvEdit->Text = IntToStr(RefrenceApp);
			KdAdvEdit->Text =  IntToStr(KdApp);
			KpAdvEdit->Text =  IntToStr(KpApp);
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_Contact);

			KiApp = KiApp_Contact;
			KiFeedBack = KiFeedback_Contact;
			break;
		}
		default:{
			break;
		}


	}
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::FormShow(TObject *Sender)
{

	if(!first){
		first = true;
		GetIniToUi();

		switch (mainForm->AppMode) {
			case 1:{
				break;
			}
			case 2:{
				Panel7->Visible = false;
				break;
			}
			case 3:{
				Panel7->Visible = false;
				break;
			}
			case 4:{
				Panel7->Visible = false;
				break;
			}
			case 5:{
				break;
			}
			case 6:{
				Panel7->Visible = false;
				break;
			}
			case 7:{
				break;
			}
			default:{
				break;
			}
		}

		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;


		PanelSubApproach->Width = w_this - 40;
		PanelSubApproach->Height = h_this - 40;
		PanelSubApproach->Left = 20;
		PanelSubApproach->Top = 20;

		int w = PanelSubApproach->Width;
		int h = PanelSubApproach->Height - PanelLabelApproch->Height;

		int Top = PanelLabelApproch->Height;


		int l = 260;
		int p = 30;

//		KiAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel1->Left = 10;
		Panel1->Top = Top + 20;
		Panel1->Width = l;
		Panel1->Height = p;
		Panel1->BringToFront();

		int left1 = Panel1->Left;

//		BiasAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel2->Left = left1;
		Panel2->Top = Panel1->Top + 50;
		Panel2->Width = l;
		Panel2->Height = p;
		Panel2->BringToFront();

		int left2 = Panel2->Left;

//		KdAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel3->Left = left1;
		Panel3->Top = Panel2->Top + 40;
		Panel3->Width = l;
		Panel3->Height = p;
		Panel3->BringToFront();

//		StpAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel4->Left = left1;
		Panel4->Top = Panel2->Top + 50;
		Panel4->Width = l;
		Panel4->Height = p;
		Panel4->BringToFront();

//		KiFeebackAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel5->Left = left1;
		Panel5->Top = Panel4->Top + 40;
		Panel5->Width = l;
		Panel5->Height = p;
		Panel5->BringToFront();

//		KpAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel6->Left = left2;
		Panel6->Top = Panel5->Top;
		Panel6->Width = l;
		Panel6->Height = p;
		Panel6->BringToFront();

		Panel7->Left = left1;
		Panel7->Top = Panel4->Top + 50;
		Panel7->Width = l;
		Panel7->Height = p;
		Panel7->BringToFront();

		Panel8->Width = 500;
		EditApproachStat->Height = 30;
		LabelApproachStat->Width = 120;
		Panel8->Left = left1 + l + w/48 - Panel8->Width/2;
		Panel8->Top = Panel7->Top + 40;
		Panel8->BringToFront();


		AllEditWhite();
	}
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KiAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TApproachPanelForm::KiAdvEditKeyPress");
        Key = 0;
		KiAdvEdit->Color = clWhite;

		switch(mainForm->AppMode){
			case 1:{
				KiApp_Contact = KiAdvEdit->Text.ToInt();
				ApproachTable.Apr_Ki_Val_Contact = KiApp_Contact;
				break;
			}
			case 2: {
				KiApp_NonContact = KiAdvEdit->Text.ToInt();
				ApproachTable.Apr_Ki_Val_NonContact = KiApp_NonContact;
				break;
			}
			case 3: {
				KiApp_NonContact = KiAdvEdit->Text.ToInt();
				ApproachTable.Apr_Ki_Val_NonContact = KiApp_NonContact;
				break;
			}
			case 4: {
				KiApp_NonContact = KiAdvEdit->Text.ToInt();
				ApproachTable.Apr_Ki_Val_NonContact = KiApp_NonContact;
				break;
			}
			case 5:{
				KiApp_Contact = KiAdvEdit->Text.ToInt();
				ApproachTable.Apr_Ki_Val_Contact = KiApp_Contact;
				break;
			}
			case 6:{
				KiApp_NonContact = KiAdvEdit->Text.ToInt();
				ApproachTable.Apr_Ki_Val_NonContact = KiApp_NonContact;
				break;
			}
			case 7:{
				KiApp_Contact = KiAdvEdit->Text.ToInt();
				ApproachTable.Apr_Ki_Val_Contact = KiApp_Contact;
				break;
			}
			default: {
				break;
            }
		}


		KiApp = KiAdvEdit->Text.ToInt();

		SettApproach();
	}
}
//---------------------------------------------------------------------------



void __fastcall TApproachPanelForm::BiasAdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TApproachPanelForm::BiasAdvEditKeyPress");
        Key = 0;
		BiasAdvEdit->Color = clWhite;
		BiasApp = BiasAdvEdit->Text.ToInt();
		ApproachTable.Apr_Bias_Val = BiasApp;
		mainForm->myScanPanelForm->BiasAdvEdit->Text = IntToStr(BiasApp);
		mainForm->myScanPanelForm->BiasAdvEdit->Color = clWhite;
		SettApproach();
	}
}


//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::StpAdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TApproachPanelForm::StpAdvEditKeyPress");
        Key = 0;
		StpAdvEdit->Color = clWhite;
		StpApp = StpAdvEdit->Text.ToInt();
		ApproachTable.Apr_SteperStepMicro_Val_Precise = StpApp;
		SettApproach();
	}
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::RefAdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TApproachPanelForm::RefAdvEditKeyPress");
        Key = 0;
		RefAdvEdit->Color = clWhite;
		if(RefAdvEdit->Text.ToInt() < 0)
		RefAdvEdit->Text = IntToStr(0);

		RefrenceApp = RefAdvEdit->Text.ToInt();

		ApproachTable.Apr_Refrerence_Val = RefrenceApp;

		SettApproach();
	}
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KdAdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TApproachPanelForm::KdAdvEditKeyPress");
        Key = 0;
		KdAdvEdit->Color = clWhite;
		KdApp = KdAdvEdit->Text.ToInt();

		ApproachTable.Apr_Kd_Val = KdApp;

		if(mainForm->Approached){
			mainForm->myControlPanelForm->EnableApproachPanel(3);
			TThread::Synchronize(mainForm->myCommandCreatorThread,SetApproach);
		}
		else{
			SettApproach();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KpAdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TApproachPanelForm::KpAdvEditKeyPress");
        Key = 0;
		KpAdvEdit->Color = clWhite;
		KpApp = KpAdvEdit->Text.ToInt();

		ApproachTable.Apr_Kp_Val = KpApp;

		if(mainForm->Approached){
			mainForm->myControlPanelForm->EnableApproachPanel(3);
			TThread::Synchronize(mainForm->myCommandCreatorThread,SetApproach);
		}
		else{
			SettApproach();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KiFeebackAdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TApproachPanelForm::KiFeebackAdvEditKeyPress");
		Key = 0;
		KiFeedbackAdvEdit->Color = clWhite;
		switch(mainForm->AppMode){
			case 1:{

				KiFeedback_Contact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_Contact = KiFeedback_Contact;
				break;
			}
			case 2:{
				KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = KiFeedback_NonContact;
				break;
			}
			case 3:{
				KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = KiFeedback_NonContact;
				break;
			}
			case 4:{
				KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = KiFeedback_NonContact;
				break;
			}
			case 5:{
				KiFeedback_Contact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_Contact = KiFeedback_Contact;
				break;
			}
			case 6:{
				KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = KiFeedback_NonContact;
				break;
			}
			case 7:{
				KiFeedback_Contact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_Contact = KiFeedback_Contact;

				break;
			}
			default:{
				break;
			}
		}


		KiFeedBack = KiFeedbackAdvEdit->Text.ToInt();

		if(mainForm->Approached){
//			mainForm->LogToFile("approched feed back enter");
			mainForm->myControlPanelForm->EnableApproachPanel(3);
			TThread::Synchronize(mainForm->myCommandCreatorThread,SetApproach);
		}
		else{
//			mainForm->LogToFile("not approached feed back enter");
			SettApproach();
		}
	}
}
//---------------------------------------------------------------------------

void TApproachPanelForm::SettApproach()
{
	mainForm->LogToFile(" TApproachPanelForm::SettApproach");
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("APPROACH_CONFIG"));
	mainForm->Approaching = false;
	mainForm->GetSecure();
	mainForm->Approached = false;
	mainForm->myControlPanelForm->EnableApproachPanel(1);
	TThread::Synchronize(mainForm->myCommandCreatorThread,SetApproach);
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KiFeedbackAdvEditChange(TObject *Sender)
{
	KiFeedbackAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KiAdvEditChange(TObject *Sender)
{
	KiAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KdAdvEditChange(TObject *Sender)
{
	KdAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::StpAdvEditChange(TObject *Sender)
{
	StpAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::BiasAdvEditChange(TObject *Sender)
{
	BiasAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::KpAdvEditChange(TObject *Sender)
{
	KpAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TApproachPanelForm::RefAdvEditChange(TObject *Sender)
{
	RefAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------


void TApproachPanelForm::AllEditWhite()
{
	KpAdvEdit->Color = clWhite;
	BiasAdvEdit->Color = clWhite;
	StpAdvEdit->Color = clWhite;
	KdAdvEdit->Color = clWhite;
	KiAdvEdit->Color = clWhite;
	KiFeedbackAdvEdit->Color = clWhite;
	RefAdvEdit->Color = clWhite;
}
//---------------------------------------------------------------------------




