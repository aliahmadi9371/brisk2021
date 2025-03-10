//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GalleryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma link "AdvPanel"
#pragma link "AdvScrollBox"
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma resource "*.dfm"

#include "mainUnit.h"

TGalleyForm *GalleyForm;
//---------------------------------------------------------------------------
__fastcall TGalleyForm::TGalleyForm(TComponent* Owner)
	: TForm(Owner)
{
	GalleyForm = this;
	currentimagecount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TGalleyForm::FormCreate(TObject *Sender)
{
	InitVal();
	CreateObjects();
	ConfigClass();
}
//---------------------------------------------------------------------------


void TGalleyForm::InitVal()
{
	first = false;
}
//---------------------------------------------------------------------------

void TGalleyForm::CreateObjects()
{
	myViewer = new TViewerFrm(this);
}
//---------------------------------------------------------------------------

void TGalleyForm::ConfigClass()
{
	InitDir();
}
//---------------------------------------------------------------------------

void TGalleyForm::InitDir()
{
	OpenTextFileDialog->InitialDir = ".";
}
//---------------------------------------------------------------------------

void __fastcall TGalleyForm::FormShow(TObject *Sender)
{
	if(!first){



		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;

		PanelSubGallery->Width = w_this - 40;
		PanelSubGallery->Height = h_this - 40;
		PanelSubGallery->Left = 20;
		PanelSubGallery->Top = 20;

		SaveInfoPanel->Top = OpenButton->Top;
		SaveInfoPanel->Left = PanelSubGallery->Width - SaveInfoPanel->Width - 25;

		AdvScrollBox->Height = PanelSubGallery->Height - (OpenButton->Height + 20 + PanelLabelGallery->Height);

		myViewer->Height = mainForm->Height - 20;
		myViewer->Width = mainForm->Height - 20;
		myViewer->Top = mainForm->Height/2 - myViewer->Height/2;
		myViewer->Left = mainForm->Width/2 - myViewer->Width/2;

		first = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TGalleyForm::OpenButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TGalleyForm::OpenButtonClick");
	if(OpenTextFileDialog->Execute() && OpenTextFileDialog->FileName != ""){
		OpenedFileName = OpenTextFileDialog->FileName;
		if(ExtractFileExt(OpenedFileName) == ".txt"){
			SaveInfoPanel->Visible = true;
			RangePanel->Visible = false;
			ZUnitPanel->Visible = false;
			ScalePanel->Visible = false;
			SaveInfoPanel->Height = SaveButton->Height + 10;

			TStringList* list = new TStringList;
			TStringList* newlist = new TStringList;
			TStringList* finallist = new TStringList;
			TStringList* namelist = new TStringList;
			TStringList* IntAddlist = new TStringList;
			TStringList* Unitlist = new TStringList;
			TStringList* Scalelist = new TStringList;
			UnicodeString folder = ExtractFileDir(OpenTextFileDialog->FileName);
			UnicodeString tmp;
			UnicodeString tmp2;
			list->LoadFromFile(OpenTextFileDialog->FileName);
	//		mainForm->LogToFile("OpenTextFileDialog->FileName = " + OpenTextFileDialog->FileName);
			Memo->Lines->Clear();
			Memo->Lines->LoadFromFile(OpenTextFileDialog->FileName);
//			mainForm->LogToFile("list->Count = " + IntToStr(list->Count));
			for(int i=0; i<list->Count; i++){

				if(ContainsText(list->operator [](i), "FileName   : ")){

					tmp = list->operator [](i);
//					mainForm->LogToFile("1- " + tmp);
					tmp =  tmp.SubString(14,tmp.Length()-13);
					IntAddlist->Add(folder + "\\" + tmp);
//					mainForm->LogToFile("2- " + tmp);
					tmp =  tmp.SubString(0,tmp.Length()-3);
//					mainForm->LogToFile("3- " + tmp);
					tmp2 = tmp;
//					mainForm->LogToFile("4- " + tmp2);
					tmp2 = tmp2.SubString(8,tmp.Length()-8);
//					mainForm->LogToFile("5- " + tmp2);
					namelist->Add(tmp2);
					tmp = tmp + "bmp";
//					mainForm->LogToFile("6- " + tmp);
					newlist->Add(tmp);
				}
				else if(ContainsText(list->operator [](i), "xPixel     :    ")){
					tmp = list->operator [](i);
					tmp =  tmp.SubString(17,tmp.Length()-16);
					SaveResolution = tmp.ToInt();
//					mainForm->LogToFile("SaveResolution  = " + IntToStr(SaveResolution));
				}
				else if(ContainsText(list->operator [](i), "XScanRange :    ")){
                    tmp = list->operator [](i);
					tmp =  tmp.SubString(17,tmp.Length()-16);
					SaveRange = tmp.ToDouble();
//					mainForm->LogToFile("SaveRange  = " + FloatToStr(SaveRange));
				}
				else if(ContainsText(list->operator [](i), "Scale      : ")){
					tmp = list->operator [](i);
					tmp =  tmp.SubString(14,tmp.Length()-13);
//					mainForm->LogToFile("Scale  =  " + tmp);
					Scalelist->Add(tmp);
				}
				else if(ContainsText(list->operator [](i), "PhysUnit   : ")){
					tmp = list->operator [](i);
					if(tmp.SubString(0,16) != "SetPointPhysUnit"){

//						mainForm->LogToFile(tmp);
						tmp =  tmp.SubString(14,tmp.Length()-13);
//						mainForm->LogToFile("Unit  =  " + tmp);
						Unitlist->Add(tmp);
					}
				}

			}

			mainForm->LogToFile("newlist->Count = " + IntToStr(newlist->Count));
			for(int i=0; i<newlist->Count; i++){
				finallist->Add(folder + "\\" + newlist->operator [](i));
			}

			int top = 0;

			for(int i=0; i<currentimagecount; i++){
				delete image_address_array[i];
			}
			delete[]image_address_array;


			image_address_array = new TImageShapeForm*[finallist->Count];
			currentimagecount = finallist->Count;
			mainForm->LogToFile("currentimagecount = " + IntToStr(currentimagecount));
			for(int i=0; i<currentimagecount; i++){
					Images = new TImageShapeForm(this);
					image_address_array[i] = Images;
					image_address_array[i]->CreateObject(SaveResolution);
					image_address_array[i]->image_number = i;
					image_address_array[i]->Parent = AdvScrollBox;
					image_address_array[i]->SetParentComponent(AdvScrollBox);
					if(FileExists(finallist->operator [](i)))
						image_address_array[i]->Image->Picture->Bitmap->LoadFromFile(finallist->operator [](i));
					else
						image_address_array[i]->NotFoundPanel->Visible = true;
					image_address_array[i]->Left = 10;
					image_address_array[i]->Width = 100;
					image_address_array[i]->Height = 100;
					image_address_array[i]->Top = top;
					top = top + Images->Height + 20;
					image_address_array[i]->BringToFront();
					image_address_array[i]->LabelName->Caption = namelist->operator [](i);
					mainForm->LogToFile(image_address_array[i]->LabelName->Caption + " , " + IntToStr(top));
					image_address_array[i]->IntAdd = IntAddlist->operator [](i);
					image_address_array[i]->Scale = Scalelist->operator [](i).ToDouble();
					image_address_array[i]->ZUnit = Unitlist->operator [](i);


					if(image_address_array[i]->ZUnit.Length() == 2){
						UnicodeString ScaleChar = image_address_array[i]->ZUnit.SubString(0,1);
						if(ScaleChar == "m")
							image_address_array[i]->Scale = image_address_array[i]->Scale * pow10l(-3);
						else if(ScaleChar == "�")
							image_address_array[i]->Scale = image_address_array[i]->Scale * pow10l(-6);
						else if(ScaleChar == "n")
							image_address_array[i]->Scale = image_address_array[i]->Scale * pow10l(-9);

						image_address_array[i]->ZUnit = image_address_array[i]->ZUnit[2];
					}

//					mainForm->LogToFile(image_address_array[i]->ZUnit);

					image_address_array[i]->Show();
			}

			Memo->Height = AdvScrollBox->Height;
			delete list;
			delete newlist;
			delete finallist;
			delete IntAddlist;
			delete Unitlist;
			delete Scalelist;
		}
		else
		{
			SaveInfoPanel->Visible = true;
			RangePanel->Visible = true;
			ZUnitPanel->Visible = true;
			ScalePanel->Visible = true;
			SaveInfoPanel->Height = SaveButton->Height + 3 * RangePanel->Height + 15;

			Memo->Lines->Clear();
			TStringList* newlist = new TStringList;
			UnicodeString tmp;

			UnicodeString folder = ExtractFileDir(OpenTextFileDialog->FileName);
			tmp = OpenTextFileDialog->FileName;
//			mainForm->LogToFile("1- " + tmp);
			tmp =  tmp.SubString(0,tmp.Length()-3);
			tmp = tmp + "bmp";
//			mainForm->LogToFile("6- " + tmp);
			newlist->Add(tmp);

            for(int i=0; i<currentimagecount; i++){
				delete image_address_array[i];
			}
			delete[]image_address_array;

			image_address_array = new TImageShapeForm*[1];
			currentimagecount = 1;

			for(int i=0; i<currentimagecount; i++){
				Images = new TImageShapeForm(this);
				image_address_array[i] = Images;
				image_address_array[i]->image_number = i;
				image_address_array[i]->Parent = AdvScrollBox;
				image_address_array[i]->SetParentComponent(AdvScrollBox);
				if(FileExists(newlist->operator [](i)))
					image_address_array[i]->Image->Picture->Bitmap->LoadFromFile(newlist->operator [](i));
				else
					image_address_array[i]->NotFoundPanel->Visible = true;
				image_address_array[i]->Left = 10;
				image_address_array[i]->Width = 100;
				image_address_array[i]->Height = 100;
				image_address_array[i]->Top = 0;
				image_address_array[i]->BringToFront();
				image_address_array[i]->LabelName->Caption = OpenedFileName.SubString(folder.Length()+2,OpenedFileName.Length()-folder.Length()-5);
				mainForm->LogToFile(image_address_array[i]->LabelName->Caption);
				mainForm->LogToFile(folder);
				image_address_array[i]->IntAdd = OpenedFileName;
				image_address_array[i]->Show();
			}

			delete newlist;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TGalleyForm::AdvScrollBoxMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	AdvScrollBox->VertScrollBar->Position += 10;
}
//---------------------------------------------------------------------------

void __fastcall TGalleyForm::AdvScrollBoxMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	AdvScrollBox->VertScrollBar->Position -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TGalleyForm::SaveButtonClick(TObject *Sender)
{
	myGWYMaker = new GWYMakerClass();

	mainForm->LogToFile("TGalleyForm::SaveButtonClick");

	UnicodeString GWYAddress = OpenedFileName.SubString(0,OpenedFileName.Length()-4) + ".gwy";
	if(ExtractFileExt(OpenedFileName) == ".txt"){

        for(int i=0; i<currentimagecount; i++){
			ReadFromIntFile(true,i ,image_address_array[i]->IntAdd);
		}
		myGWYMaker->StartSavingFromGallery(GWYAddress,currentimagecount);
	}
	else{

		for(int i=0; i<currentimagecount; i++){

			ReadFromIntFile(false,i ,image_address_array[i]->IntAdd);
			image_address_array[i]->ZUnit = AdvComboBoxSelect->Text;
			image_address_array[i]->Scale = IndexAdvEdit->Text.ToDouble();
		}
		SaveRange = AdvEditRange->Text.ToDouble();

		myGWYMaker->StartSavingFromGallery(GWYAddress,currentimagecount);
	}

	delete myGWYMaker;
}
//---------------------------------------------------------------------------

void TGalleyForm::ReadFromIntFile(bool txt,int ImageNum ,UnicodeString FileAdd)
{
//	mainForm->LogToFile("ReadFileClass::ReadFromIntFile");
	mainForm->LogToFile("FileAdd = " + FileAdd);

	intdata.open(FileAdd.c_str(), std::ios::binary); // opens the file

	intdata.seekg(0, intdata.end);
	double Length = intdata.tellg();
	intdata.seekg(0, intdata.beg);

	int PictureResolution = sqrt(Length/4);
	if(!txt){
		SaveResolution = PictureResolution;
		image_address_array[ImageNum]->CreateObject(SaveResolution);
	}


//	mainForm->LogToFile("indata.open = " + BoolToStr(intdata.is_open(),true));
//	mainForm->LogToFile("Length = " + FloatToStr(Length));
//	mainForm->LogToFile("PictureResolution = " + IntToStr(PictureResolution));

	unsigned char * buffer = new unsigned char [PictureResolution*4];

	for(int LineNumber = 0; LineNumber<PictureResolution; LineNumber++)
	{
		intdata.seekg (LineNumber*PictureResolution*4, intdata.beg);
		intdata.read(buffer,PictureResolution*4);

		for(int i = 0; i<PictureResolution; i++){
			image_address_array[ImageNum]->Main[(PictureResolution * LineNumber) + i] =  GetNewData(buffer[i*4],buffer[i*4+1],buffer[i*4+2],buffer[i*4+3]);
		}
	}
	mainForm->LogToFile("ImageNum = " + IntToStr(ImageNum));
	mainForm->LogToFile("first = " + IntToStr(image_address_array[ImageNum]->Main[0]));
	mainForm->LogToFile("Last = " + IntToStr(image_address_array[ImageNum]->Main[PictureResolution*PictureResolution-1]));


	delete[] buffer;
	buffer = NULL;
	intdata.close();



}
//---------------------------------------------------------------------------

int TGalleyForm::GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3)
{

	unsigned char tmp1[4] ;
	int tmp = 0 ;
	memset(tmp1,0x00,4);


	tmp1[0] = data0;
	tmp1[1] = data1;
	tmp1[2] = data2;
	tmp1[3] = data3;

//	mainForm->LogToFile("data 0 = " + IntToHex((int)data0,2));
//	mainForm->LogToFile("data 1 = " + IntToHex((int)data1,2));
//	mainForm->LogToFile("data 2 = " + IntToHex((int)data2,2));
//	mainForm->LogToFile("data 3 = " + IntToHex((int)data3,2));

	memcpy((void *)&tmp , (void *)tmp1 , 4);

	return tmp;
}

