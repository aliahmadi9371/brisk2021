//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "oscClass.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeEdit"
#pragma link "VCLTee.TeeComma"
#pragma resource "*.dfm"
ToscForm *oscForm;
//---------------------------------------------------------------------------
__fastcall ToscForm::ToscForm(TComponent* Owner)
	: TForm(Owner)
{
	bool_created = false;
	initForm();
}
//---------------------------------------------------------------------------

void ToscForm::initForm()
{
    Panel_Top->Top = 0;
	Panel_Top->Left = 0;
	Panel_Top->Width = this->Width;

	Panel_Buttom->Left = 0;
	Panel_Buttom->Top = Panel_Top->Height;
	Panel_Buttom->Height = this->Height - Panel_Top->Height;
	Panel_Buttom->Width = this->Width;

	ComboBox_Wave->Top = 0;
	ComboBox_Wave->Height = Panel_Top->Height;

	ComboBox_Scale->Top = 0;
	ComboBox_Scale->Height = Panel_Top->Height;


	Chart->Width = this->Width;
	Chart->Height = this->Height - Panel_Top->Height;
	Chart->Left = 0;
	Chart->Top = Panel_Top->Height;
    X_dots = 0;
}
//---------------------------------------------------------------------------

void ToscForm::createComboBox()
{
	ComboBox_Wave->Items->Add("01 - " + mainForm->data_name_00);
	ComboBox_Wave->Items->Add("02 - " + mainForm->data_name_01);
	ComboBox_Wave->Items->Add("03 - " + mainForm->data_name_02);
	ComboBox_Wave->Items->Add("04 - " + mainForm->data_name_03);
	ComboBox_Wave->Items->Add("05 - " + mainForm->data_name_04);
	ComboBox_Wave->Items->Add("06 - " + mainForm->data_name_05);
	ComboBox_Wave->Items->Add("07 - " + mainForm->data_name_06);
	ComboBox_Wave->Items->Add("08 - " + mainForm->data_name_07);
	ComboBox_Wave->Items->Add("09 - " + mainForm->data_name_08);
	ComboBox_Wave->Items->Add("10 - " + mainForm->data_name_09);
	ComboBox_Wave->Items->Add("11 - " + mainForm->data_name_10);
	ComboBox_Wave->Items->Add("12 - " + mainForm->data_name_11);
	ComboBox_Wave->Items->Add("13 - " + mainForm->data_name_12);
	ComboBox_Wave->Items->Add("14 - " + mainForm->data_name_13);
	ComboBox_Wave->Items->Add("15 - " + mainForm->data_name_14);
	ComboBox_Wave->Items->Add("16 - " + mainForm->data_name_15);
	ComboBox_Wave->Items->Add("17 - " + mainForm->data_name_16);
	ComboBox_Wave->Items->Add("18 - " + mainForm->data_name_17);
	ComboBox_Wave->Items->Add("19 - " + mainForm->data_name_18);
	ComboBox_Wave->Items->Add("20 - " + mainForm->data_name_19);
	ComboBox_Wave->Items->Add("21 - " + mainForm->data_name_20);
	ComboBox_Wave->Items->Add("22 - " + mainForm->data_name_21);
	ComboBox_Wave->Items->Add("23 - " + mainForm->data_name_22);
	ComboBox_Wave->Items->Add("24 - " + mainForm->data_name_23);
	ComboBox_Wave->Items->Add("25 - " + mainForm->data_name_24);
	ComboBox_Wave->Items->Add("26 - " + mainForm->data_name_25);
	ComboBox_Wave->Items->Add("27 - " + mainForm->data_name_26);
}
void __fastcall ToscForm::FormShow(TObject *Sender)
{
	if(!bool_created){
        initForm();
		createComboBox();

		main_data_count = 0;
		main_time = 0;
		main_step = 0;
		main_time_step = 0;
		bool_created = true;

//        this->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall ToscForm::ComboBox_WaveChange(TObject *Sender)
{
	mainForm->LogToFile("ToscForm: ComboBox_WaveChange: ItemIndex: " + IntToStr(ComboBox_Wave->ItemIndex));
	int index = ComboBox_Wave->ItemIndex;
	mainForm->LogToFile("ToscForm: ComboBox_WaveChange: ItemIndex: " + IntToStr(index));
	CreateUnit(index);
	mainForm->LogToFile("ToscForm: ComboBox_WaveChange: CreateUnit: ");
	ComboBox_Scale->ItemIndex = 0;
	ComboBox_ScaleChange(NULL);
	mainForm->LogToFile("ToscForm: ComboBox_WaveChange: ComboBox_ScaleChange: ");
	Chart->Refresh();
	CreateWaveTitle(index);
}
//---------------------------------------------------------------------------


void ToscForm::CreateUnit(int index)
{
	ComboBox_Scale->Items->Clear();
	if(   index == 0   ) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_00); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_00);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_00);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_00);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_00); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_00);  return;}
	else if(index == 01) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_01); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_01);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_01);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_01);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_01); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_01);  return;}
	else if(index == 02) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_02); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_02);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_02);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_02);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_02); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_02);  return;}
	else if(index == 03) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_03); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_03);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_03);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_03);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_03); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_03);  return;}
	else if(index == 04) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_04); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_04);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_04);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_04);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_04); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_04);  return;}
	else if(index == 05) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_05); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_05);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_05);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_05);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_05); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_05);  return;}
	else if(index == 06) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_06); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_06);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_06);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_06);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_06); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_06);  return;}
	else if(index == 07) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_07); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_07);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_07);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_07);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_07); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_07);  return;}
	else if(index == 8)  {ComboBox_Scale->Items->Add("" + mainForm->data_unit_08); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_08);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_08);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_08);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_08); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_08);  return;}
	else if(index == 9)  {ComboBox_Scale->Items->Add("" + mainForm->data_unit_09); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_09);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_09);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_09);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_09); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_09);  return;}
	else if(index == 10) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_10); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_10);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_10);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_10);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_10); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_10);  return;}
	else if(index == 11) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_11); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_11);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_11);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_11);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_11); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_11);  return;}
	else if(index == 12) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_12); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_12);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_12);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_12);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_12); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_12);  return;}
	else if(index == 13) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_13); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_13);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_13);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_13);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_13); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_13);  return;}
	else if(index == 14) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_14); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_14);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_14);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_14);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_14); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_14);  return;}
	else if(index == 15) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_15); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_15);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_15);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_15);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_15); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_15);  return;}
	else if(index == 16) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_16); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_16);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_16);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_16);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_16); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_16);  return;}
	else if(index == 17) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_17); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_17);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_17);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_17);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_17); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_17);  return;}
	else if(index == 18) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_18); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_18);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_18);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_18);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_18); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_18);  return;}
	else if(index == 19) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_19); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_19);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_19);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_19);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_19); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_19);  return;}
	else if(index == 20) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_20); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_20);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_20);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_20);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_20); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_20);  return;}
	else if(index == 21) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_21); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_21);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_21);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_21);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_21); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_21);  return;}
	else if(index == 22) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_22); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_22);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_22);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_22);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_22); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_22);  return;}
	else if(index == 23) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_23); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_23);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_23);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_23);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_23); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_23);  return;}
	else if(index == 24) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_24); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_24);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_24);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_24);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_24); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_24);  return;}
	else if(index == 25) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_25); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_25);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_25);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_25);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_25); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_25);  return;}
	else if(index == 26) {ComboBox_Scale->Items->Add("" + mainForm->data_unit_26); ComboBox_Scale->Items->Add("m" + mainForm->data_unit_26);  ComboBox_Scale->Items->Add("u" + mainForm->data_unit_26);  ComboBox_Scale->Items->Add("n" + mainForm->data_unit_26);  ComboBox_Scale->Items->Add("p" + mainForm->data_unit_26); ComboBox_Scale->Items->Add("f" + mainForm->data_unit_26);  return;}
	else{ return;}
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::ComboBox_ScaleChange(TObject *Sender)
{
	int index = ComboBox_Wave->ItemIndex;

	if(ComboBox_Scale->ItemIndex == 0)     { Series->Clear();oscQueue = (mainForm->ChartQueue[index]); for(int i=0; i<oscQueue.size(); i++){Series->AddXY((double)i*mainForm->rec_step,           oscQueue.arr[i]);} return;}
	else if(ComboBox_Scale->ItemIndex == 1){ Series->Clear();oscQueue = (mainForm->ChartQueue[index]); for(int i=0; i<oscQueue.size(); i++){Series->AddXY((double)i*mainForm->rec_step,pow10l(3)*  oscQueue.arr[i]);} return;}
	else if(ComboBox_Scale->ItemIndex == 2){ Series->Clear();oscQueue = (mainForm->ChartQueue[index]); for(int i=0; i<oscQueue.size(); i++){Series->AddXY((double)i*mainForm->rec_step,pow10l( 6)* oscQueue.arr[i]);} return;}
	else if(ComboBox_Scale->ItemIndex == 3){ Series->Clear();oscQueue = (mainForm->ChartQueue[index]); for(int i=0; i<oscQueue.size(); i++){Series->AddXY((double)i*mainForm->rec_step,pow10l(19)* oscQueue.arr[i]);} return;}
	else if(ComboBox_Scale->ItemIndex == 4){ Series->Clear();oscQueue = (mainForm->ChartQueue[index]); for(int i=0; i<oscQueue.size(); i++){Series->AddXY((double)i*mainForm->rec_step,pow10l(12)* oscQueue.arr[i]);} return;}
	else if(ComboBox_Scale->ItemIndex == 5){ Series->Clear();oscQueue = (mainForm->ChartQueue[index]); for(int i=0; i<oscQueue.size(); i++){Series->AddXY((double)i*mainForm->rec_step,pow10l(15)*oscQueue.arr[i]);} return;}
	else{return;}
}
//---------------------------------------------------------------------------

void ToscForm::CreateWaveTitle(int index)
{
	if(   index == 00  ){Chart->Title->Caption = mainForm->data_name_00;}
	else if(index == 01){Chart->Title->Caption = mainForm->data_name_01;}
	else if(index == 02){Chart->Title->Caption = mainForm->data_name_02;}
	else if(index == 03){Chart->Title->Caption = mainForm->data_name_03;}
	else if(index == 04){Chart->Title->Caption = mainForm->data_name_04;}
	else if(index == 05){Chart->Title->Caption = mainForm->data_name_05;}
	else if(index == 06){Chart->Title->Caption = mainForm->data_name_06;}
	else if(index == 07){Chart->Title->Caption = mainForm->data_name_07;}
	else if(index == 8) {Chart->Title->Caption = mainForm->data_name_08;}
	else if(index == 9) {Chart->Title->Caption = mainForm->data_name_09;}
	else if(index == 10){Chart->Title->Caption = mainForm->data_name_10;}
	else if(index == 11){Chart->Title->Caption = mainForm->data_name_11;}
	else if(index == 12){Chart->Title->Caption = mainForm->data_name_12;}
	else if(index == 13){Chart->Title->Caption = mainForm->data_name_13;}
	else if(index == 14){Chart->Title->Caption = mainForm->data_name_14;}
	else if(index == 15){Chart->Title->Caption = mainForm->data_name_15;}
	else if(index == 16){Chart->Title->Caption = mainForm->data_name_16;}
	else if(index == 17){Chart->Title->Caption = mainForm->data_name_17;}
	else if(index == 18){Chart->Title->Caption = mainForm->data_name_18;}
	else if(index == 19){Chart->Title->Caption = mainForm->data_name_19;}
	else if(index == 20){Chart->Title->Caption = mainForm->data_name_20;}
	else if(index == 21){Chart->Title->Caption = mainForm->data_name_21;}
	else if(index == 22){Chart->Title->Caption = mainForm->data_name_22;}
	else if(index == 23){Chart->Title->Caption = mainForm->data_name_23;}
	else if(index == 24){Chart->Title->Caption = mainForm->data_name_24;}
	else if(index == 25){Chart->Title->Caption = mainForm->data_name_25;}
	else if(index == 26){Chart->Title->Caption = mainForm->data_name_26;}
	else {return;}
}
//---------------------------------------------------------------------------



