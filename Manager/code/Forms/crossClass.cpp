//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "crossClass.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeePageNumTool"
#pragma resource "*.dfm"
TCrossForm *CrossForm;
//---------------------------------------------------------------------------
__fastcall TCrossForm::TCrossForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void TCrossForm::modified_cross()
{
	try{
		crossSeries->Clear();

//		mainForm->LogToFile("TB =  " + FloatToStr(x));
//		mainForm->LogToFile("LR =  " + FloatToStr(y));
//		mainForm->LogToFile("Intensity =  " + FloatToStr(z));

//		if(all_scale ){

			if(x){
				mainForm->Label3->Text = "TB: " + FormatFloat("#", RoundTo(x,00))+ " mV";
				mainForm->Label5->Text = 	mainForm->Label3->Text;
			}
			else {
				mainForm->Label3->Text = "TB: 0 mV";
				mainForm->Label5->Text = 	mainForm->Label3->Text;
			}

			if(y){
				mainForm->Label2->Text = "LR: " + FormatFloat("#", RoundTo(y,00))+ " mV";
				mainForm->Label6->Text = mainForm->Label2->Text;
			}
			else{
				mainForm->Label2->Text = "LR: 0 mV";
				mainForm->Label6->Text = mainForm->Label2->Text;
			}

			if(z){
				mainForm->Label1->Text =  "Intensity: " + FormatFloat( "#",abs(RoundTo(z,00))) + " mV";
				mainForm->Label7->Text =  mainForm->Label1->Text;
			}
			else{
				mainForm->Label1->Text = "Intensity: 0 mV";
				mainForm->Label7->Text = mainForm->Label1->Text;
			}

			if(x > Gain)
				x = Gain;
			if(y > Gain)
				y = Gain;
			if(x < -Gain)
				x = -Gain;
			if(y < -Gain)
				y = -Gain;
//
//		}
//		else{
//			if(x){
//				mainForm->Label3->Text = "TB =  " + FormatFloat("#", RoundTo(x,00));
//				mainForm->Label5->Text = 	mainForm->Label3->Text;
//			}
//			else{
//				mainForm->Label3->Text = "TB = 0";
//				mainForm->Label5->Text = 	mainForm->Label3->Text;
//			}
//
//			if(y){
//				mainForm->Label2->Text = "LR = " + FormatFloat("#", RoundTo(y,00));
//				mainForm->Label6->Text = mainForm->Label2->Text;
//			}
//			else{
//				mainForm->Label2->Text = "LR = 0 mV";
//				mainForm->Label6->Text = mainForm->Label2->Text;
//			}
//
//			if(z){
//				mainForm->Label1->Text =  "Intensity = " + FormatFloat( "#",abs(RoundTo(z,00)));
//				mainForm->Label7->Text =  mainForm->Label1->Text;
//			}
//			else{
//				mainForm->Label1->Text = "Intensity = 0";
//                mainForm->Label7->Text =  mainForm->Label1->Text;
//			}
//
//			if(x > 72886297)
//				x = 72886297;
//			if(y > 72886297)
//				y = 72886297;
//			if(x < -72886297)
//				x = -72886297;
//			if(y < -72886297)
//				y = -72886297;
//		}


		crossSeries->AddBubble(y,x,Gain/10);

		if(GainChainge){
			crsChart->LeftAxis->SetMinMax(-Gain,Gain);
			crsChart->BottomAxis->SetMinMax(-Gain,Gain);
			GainChainge = false;
		}

	}
	catch (Exception &exception){
		ShowMessage("modified_cross Exception : " + exception.Message + " _ " + exception.StackTrace);
	}

}
//---------------------------------------------------------------------------

void __fastcall TCrossForm::FormCreate(TObject *Sender)
{
	this->Hide();

	created = false;

	transparent = false;

	crsChart->AutoRepaint = true;

	ChartTool1->XValue = 0;
	ChartTool1->YValue = 0;
	Gain = 100;
	GainChainge = true;
	x = 0;
	y = 0;
	z = 0;

	ApproachTb = 0;
	ApproachAmp = 0;
	crsChart->Title->Caption="Cross";
	crsChart->Legend->Visible = false;
	crsChart->Title->Visible = false;
	crsChart->View3D = false;



//	crossSeries->AddXY(0,0);
//	modified_cross();

	created = true;


//	all_scale = OscChartTable.all_scale;


}
//---------------------------------------------------------------------------

