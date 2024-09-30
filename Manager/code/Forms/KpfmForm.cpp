//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "KpfmForm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvPanel"
#pragma link "AdvGlowButton"
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma resource "*.dfm"
TKpfmFrm *KpfmFrm;
//---------------------------------------------------------------------------
__fastcall TKpfmFrm::TKpfmFrm(TComponent* Owner)
	: TForm(Owner)
{
	bias = false;
	phase = false;
	lia = false;
}
//---------------------------------------------------------------------------

void TKpfmFrm::GetIniKpfmForm()
{

	freq = KpfmTable.Kpfm_Frequency_Val;
	voltage = KpfmTable.Kpfm_DriveVoltage_Val;
	lia1 = KpfmTable.Kpfm_Lia1_Val;
	ki = KpfmTable.Kpfm_Ki_Val;
	kp = KpfmTable.Kpfm_Kp_Val;
	kd = KpfmTable.Kpfm_Kd_Val;
	th = KpfmTable.Kpfm_Th_Val;
	Voltage_index = ApproachTable.Apr_BiasIndex_Val; //bias
	Voltage_offset = ApproachTable.Apr_BiasOffset_Val; //bias

}
//---------------------------------------------------------------------------

//void TKpfmFrm::SetIniKpfmForm()
//{
//	TIniFile *iniFile = new TIniFile(MainPath + "/config.ini");
//	iniFile->WriteInteger("KPFM_CONFIG", "Kpfm_Frequency_Val",freq);
//	iniFile->WriteInteger("KPFM_CONFIG", "Kpfm_DriveVoltage_Val",voltage);
//	iniFile->WriteInteger("KPFM_CONFIG", "Kpfm_Lia1_Val",lia1);
//	iniFile->WriteInteger("KPFM_CONFIG", "Kpfm_Ki_Val",ki);
//	iniFile->WriteInteger("KPFM_CONFIG", "Kpfm_Kp_Val",kp);
//	iniFile->WriteInteger("KPFM_CONFIG", "Kpfm_Kd_Val",kd);
//	iniFile->WriteInteger("KPFM_CONFIG", "Kpfm_Th_Val",th);
//	delete iniFile;
//}
//---------------------------------------------------------------------------

void TKpfmFrm::SetUiKpfmForm()
{
	FreqAdvEdit->Text = IntToStr(freq);
	VoltageAdvEdit->Text = IntToStr(voltage);
	Lia1AdvEdit->Text = IntToStr(lia1);
	KiAdvEdit->Text = IntToStr(ki);
	KpAdvEdit->Text = IntToStr(kp);
	KdAdvEdit->Text = IntToStr(kd);
	ThAdvEdit->Text = IntToStr(th);

	voltage = voltage * Voltage_index + Voltage_offset;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::FormShow(TObject *Sender)
{
	if(!first){
        int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;

		PanelSubKpfm->Width = w_this - 40;
		PanelSubKpfm->Height = h_this - 40;
		PanelSubKpfm->Left = 20;
		PanelSubKpfm->Top = 20;

		int w = PanelSubKpfm->Width;
		int h = PanelSubKpfm->Height - PanelSubKpfm->Height;

		int Top = PanelSubKpfm->Top + 10;

		int l = 260;
		int p = 30;

        int left1 =  10;
		int left2 = w - 10 - 100;

		Panel1->Left = left1;
		Panel1->Top = Top + 10;
		Panel1->Width = l;
		Panel1->Height = p;
		Panel1->BringToFront();

		Panel2->Left = left1;
		Panel2->Top = Panel1->Top + 40;
		Panel2->Width = l;
		Panel2->Height = p;
		Panel2->BringToFront();

		Panel3->Left = left1;
		Panel3->Top = Panel2->Top + 40;
		Panel3->Width = l;
		Panel3->Height = p;
		Panel3->BringToFront();

		Panel4->Left = left1;
		Panel4->Top = Panel3->Top + 40;
		Panel4->Width = l;
		Panel4->Height = p;
		Panel4->BringToFront();

		Panel5->Left = left1;
		Panel5->Top = Panel4->Top + 40;
		Panel5->Width = l;
		Panel5->Height = p;
		Panel5->BringToFront();

		Panel6->Left = left1;
		Panel6->Top = Panel5->Top + 40;
		Panel6->Width = l;
		Panel6->Height = p;
		Panel6->BringToFront();

		Panel7->Left = left1;
		Panel7->Top = Panel6->Top + 40;
		Panel7->Width = l;
		Panel7->Height = p;
		Panel7->BringToFront();

		BiasFeedbackButton->Left = left2;
		PhaseFeedbackButton->Left = left2;
		LiaButton->Left = left2;

		BiasFeedbackButton->Top = Top + 10;
		PhaseFeedbackButton->Top = BiasFeedbackButton->Top + BiasFeedbackButton->Height + 10;
		LiaButton->Top = PhaseFeedbackButton->Top + PhaseFeedbackButton->Height + 10;

		BiasFeedbackButton->BringToFront();
		PhaseFeedbackButton->BringToFront();
		LiaButton->BringToFront();



		Panel8->Left = left1;
		Panel8->Top = Panel7->Top + 40;
		Panel8->Width = l;
		Panel8->Height = p;
		Panel8->BringToFront();


		Panel9->Left = left1;
		Panel9->Top = Panel8->Top + 40;
		Panel9->Width = l;
		Panel9->Height = p;
		Panel9->BringToFront();


		first = true;

		GetIniKpfmForm();
		SetUiKpfmForm();
		AllEditWhite();
	}


}
//---------------------------------------------------------------------------
void __fastcall TKpfmFrm::FormCreate(TObject *Sender)
{
	this->Hide();
	first = false;

	bias = false;
	phase = false;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::BiasFeedbackButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TKpfmFrm::BiasFeedbackButtonClick");
	if(bias){
		bias = false;
		BiasFeedbackButton->Appearance->BorderColor = TColor(0x008B6757);
		BiasFeedbackButton->Font->Color = clWhite;
	}
	else{
		bias = true;
		BiasFeedbackButton->Appearance->BorderColor = TColor(0x00F0D27D);
		BiasFeedbackButton->Font->Color = TColor(0x00F0D27D);
	}
	if(bias && lia)
		bbias = 0x03;
	else if(bias && !lia)
		bbias = 0x01;
	else if(!bias & lia)
		bbias = 0x02;
	else
		bbias = 0x00;
    TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::PhaseFeedbackButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TKpfmFrm::PhaseFeedbackButtonClick");
	if(phase){
		phase = false;
		PhaseFeedbackButton->Appearance->BorderColor = TColor(0x008B6757);
		PhaseFeedbackButton->Font->Color = clWhite;
	}
	else{
		phase = true;
		PhaseFeedbackButton->Appearance->BorderColor = TColor(0x00F0D27D);
		PhaseFeedbackButton->Font->Color = TColor(0x00F0D27D);
	}

	if(phase)
		pphase = 1;
	else
		pphase = 0;
	TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::SendKpfm()
{
	mainForm->LogToFile("TKpfmFrm::SendKpfm");
    mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("KPFM_CONFIG"));
	mainForm->myCommandCreatorThread->SendKpfm(freq, voltage, pphase, lia1, ki, kp, kd, th, bbias);
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::FreqAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TKpfmFrm::FreqAdvEditKeyPress");
		Key = 0;
		FreqAdvEdit->Color =clWhite;
		freq = FreqAdvEdit->Text.ToInt();
		KpfmTable.Kpfm_Frequency_Val = freq;
		TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
	}
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::VoltageAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TKpfmFrm::VoltageAdvEditKeyPress");
		Key = 0;
		voltage = VoltageAdvEdit->Text.ToInt();
		VoltageAdvEdit->Color = clWhite;
		KpfmTable.Kpfm_DriveVoltage_Val = voltage;
		voltage = voltage * Voltage_index + Voltage_offset;
		TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
	}
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::Lia1AdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TKpfmFrm::Lia1AdvEditKeyPress");
		Key = 0;
		lia1 = Lia1AdvEdit->Text.ToInt();
		Lia1AdvEdit->Color = clWhite;
		KpfmTable.Kpfm_Lia1_Val = lia1;
		TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
	}
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::KiAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TKpfmFrm::KiAdvEditKeyPress");
		Key = 0;
		ki = KiAdvEdit->Text.ToInt();
		KiAdvEdit->Color = clWhite;
		KpfmTable.Kpfm_Ki_Val = ki;
		TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
	}
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::KpAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TKpfmFrm::KpAdvEditKeyPress");
		Key = 0;
		kp = KpAdvEdit->Text.ToInt();
		KpAdvEdit->Color = clWhite;
		KpfmTable.Kpfm_Kp_Val = kp;
		TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
	}
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::KdAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TKpfmFrm::KdAdvEditKeyPress");
		Key = 0;
		kd = KdAdvEdit->Text.ToInt();
		KdAdvEdit->Color = clWhite;
		KpfmTable.Kpfm_Kd_Val = kd;
		TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
	}
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::ThAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TKpfmFrm::ThAdvEditKeyPress");
        Key = 0;
		th = ThAdvEdit->Text.ToInt();
		ThAdvEdit->Color = clWhite;
		KpfmTable.Kpfm_Th_Val = th;
		TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
	}
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::LiaButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TKpfmFrm::LiaButtonClick");
	if(lia){
		lia = false;
		LiaButton->Caption = "LIA1";
		LiaButton->Appearance->BorderColor = TColor(0x008B6757);
		LiaButton->Font->Color = clWhite;
		mainForm->myImageFrom->Togle1_2(false);
	}
	else{
		lia = true;
		LiaButton->Caption = "LIA2";
		LiaButton->Appearance->BorderColor = TColor(0x00F0D27D);
		LiaButton->Font->Color = TColor(0x00F0D27D);
        mainForm->myImageFrom->Togle1_2(true);
	}
	if(bias && lia)
		bbias = 0x03;
	else if(bias && !lia)
		bbias = 0x01;
	else if(!bias & lia)
		bbias = 0x02;
	else
		bbias = 0x00;
	TThread::Synchronize(mainForm->myCommandCreatorThread,SendKpfm);
}
//---------------------------------------------------------------------------

void TKpfmFrm::AllEditWhite()
{
	FreqAdvEdit->Color = clWhite;
	VoltageAdvEdit->Color = clWhite;
	Lia1AdvEdit->Color = clWhite;
	KiAdvEdit->Color = clWhite;
	KpAdvEdit->Color = clWhite;
	KdAdvEdit->Color = clWhite;
	ThAdvEdit->Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::FreqAdvEditChange(TObject *Sender)
{
	FreqAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::VoltageAdvEditChange(TObject *Sender)
{
	VoltageAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::Lia1AdvEditChange(TObject *Sender)
{
	Lia1AdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::KiAdvEditChange(TObject *Sender)
{
	KiAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::KpAdvEditChange(TObject *Sender)
{
	KpAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::KdAdvEditChange(TObject *Sender)
{
	KdAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TKpfmFrm::ThAdvEditChange(TObject *Sender)
{
	ThAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------


