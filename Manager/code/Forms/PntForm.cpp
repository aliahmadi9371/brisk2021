//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PntForm.h"
#include "mainUnit.h"
#include "globals.h"
#include "defines.h"
#include "LitoFileCreatorUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma link "hyiedefs"
#pragma link "hyieutils"
#pragma link "iesettings"
#pragma link "ieview"
#pragma link "iexBitmaps"
#pragma link "iexLayers"
#pragma link "iexRulers"
#pragma link "imageenview"
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma link "htmlbtns"
#pragma link "AdvOfficeButtons"
#pragma link "AdvWiiProgressBar"
#pragma link "TeeTree"
#pragma link "rulerbox"
#pragma link "AdvScrollBox"
#pragma link "iegradientbar"
#pragma link "AdvTrackBar"
#pragma resource "*.dfm"
#include "LitoFileCreatorUnit.h"


TPaintForm *PaintForm;
//---------------------------------------------------------------------------
__fastcall TPaintForm::TPaintForm(TComponent* Owner)
	: TForm(Owner)
{
	main = true;
	PaintForm = this;

	ImageEnView->Bitmap->Height = 0;
	ImageEnView->Bitmap->Width = 0;

	Color = 0;

	paint_state = -1;
	painting = false;
	HoldingSomtings = false;

	std::auto_ptr<Graphics::TBitmap> bmpMask(new Graphics::TBitmap);
	std::auto_ptr<Graphics::TBitmap> bmpColor(new Graphics::TBitmap);

	std::auto_ptr<TIconInfo> iconInfo1(new TIconInfo);
	std::auto_ptr<TIconInfo> iconInfo2(new TIconInfo);
	std::auto_ptr<TIconInfo> iconInfo3(new TIconInfo);
	std::auto_ptr<TIconInfo> iconInfo4(new TIconInfo);
	std::auto_ptr<TIconInfo> iconInfo5(new TIconInfo);
	std::auto_ptr<TIconInfo> iconInfo6(new TIconInfo);

	//pen
	bmpMask->LoadFromFile(MainPath + "/Resources/Images/cursors/pen.bmp");
	bmpColor->LoadFromFile(MainPath + "/Resources/Images/cursors/pen.bmp");
	iconInfo1->fIcon = false;
	iconInfo1->xHotspot = 15;
	iconInfo1->yHotspot = 15;
	iconInfo1->hbmMask = bmpMask->Handle;
	iconInfo1->hbmColor = bmpColor->Handle;
	Screen->Cursors[crMyPenCur] = CreateIconIndirect(iconInfo1.get());

	//brush
	bmpMask->LoadFromFile(MainPath + "/Resources/Images/cursors/brush.bmp");
	bmpColor->LoadFromFile(MainPath + "/Resources/Images/cursors/brush.bmp");
	iconInfo2->fIcon = false;
	iconInfo2->xHotspot = 15;
	iconInfo2->yHotspot = 15;
	iconInfo2->hbmMask = bmpMask->Handle;
	iconInfo2->hbmColor = bmpColor->Handle;
	Screen->Cursors[crMyBrushCur] = CreateIconIndirect(iconInfo2.get());

	//line
	bmpMask->LoadFromFile(MainPath + "/Resources/Images/cursors/line.bmp");
	bmpColor->LoadFromFile(MainPath + "/Resources/Images/cursors/line.bmp");
	iconInfo3->fIcon = false;
	iconInfo3->xHotspot = 15;
	iconInfo3->yHotspot = 15;
	iconInfo3->hbmMask = bmpMask->Handle;
	iconInfo3->hbmColor = bmpColor->Handle;
	Screen->Cursors[crMyLineCur] = CreateIconIndirect(iconInfo3.get());

	//rect
	bmpMask->LoadFromFile(MainPath + "/Resources/Images/cursors/rect.bmp");
	bmpColor->LoadFromFile(MainPath + "/Resources/Images/cursors/rect.bmp");
	iconInfo4->fIcon = false;
	iconInfo4->xHotspot = 15;
	iconInfo4->yHotspot = 15;
	iconInfo4->hbmMask = bmpMask->Handle;
	iconInfo4->hbmColor = bmpColor->Handle;
	Screen->Cursors[crMyRectCur] = CreateIconIndirect(iconInfo4.get());

	//circle
	bmpMask->LoadFromFile(MainPath + "/Resources/Images/cursors/circle.bmp");
	bmpColor->LoadFromFile(MainPath + "/Resources/Images/cursors/circle.bmp");
	iconInfo5->fIcon = false;
	iconInfo5->xHotspot = 15;
	iconInfo5->yHotspot = 15;
	iconInfo5->hbmMask = bmpMask->Handle;
	iconInfo5->hbmColor = bmpColor->Handle;
	Screen->Cursors[crMyCircCur] = CreateIconIndirect(iconInfo5.get());

		//circle
	bmpMask->LoadFromFile(MainPath + "/Resources/Images/cursors/eraser.bmp");
	bmpColor->LoadFromFile(MainPath + "/Resources/Images/cursors/eraser.bmp");
	iconInfo6->fIcon = false;
	iconInfo6->xHotspot = 15;
	iconInfo6->yHotspot = 15;
	iconInfo6->hbmMask = bmpMask->Handle;
	iconInfo6->hbmColor = bmpColor->Handle;
	Screen->Cursors[crMyEraseCur] = CreateIconIndirect(iconInfo6.get());
}
//---------------------------------------------------------------------------

void TPaintForm::CreatObjects()
{
	LastBitmap = new TBitmap;
	GrayBitmap = new TBitmap;
	myTools = new TToolsFrm(this);

	HoldingArea = new TBitmap;
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::CloseButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TPaintForm::CloseButtonClick");
	this->Hide();
	AdvWiiProgressBar->Visible = false;
	AdvWiiProgressBar->Hide();
	AdvWiiProgressBar->SendToBack();
	mainForm->Enabled = true;
	mainForm->myVideoForm->VideoGrabber1->StartPreview();
	if(mainForm->myLithoFrm->LithoDesignFrm->Osc_PreviousState)
		mainForm->myOscForm->p1PauseClick(NULL);
	this->Hide();
	mainForm->myVideoForm->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TPaintForm::FormCreate(TObject *Sender)
{
	this->Hide();
	this->FormStyle = fsStayOnTop;

	SaveButton->BringToFront();
	CloseButton->BringToFront();
	first = false;
    drag = false;
	select = false;
	BitMapSaved = false;
	img_index = 0;

	CreatObjects();
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::FormShow(TObject *Sender)
{
	if(!first){
		SaveButton->Left = 10;
		SaveButton->Top = this->Height - 10 - SaveButton->Height;

		CloseButton->Left = SaveButton->Left + SaveButton->Width + 5;
		CloseButton->Top = SaveButton->Top;

		OpenButton->Left = 10;
		OpenButton->Top = 10 + 10;



		ToolsButton->Left = OpenButton->Left + OpenButton->Width + 10;
		ToolsButton->Top = OpenButton->Top;

		PanelResolution->Top = 10 + 10;
		PanelResolution->Left = ToolsButton->Left + ToolsButton->Width + 10;

		EditButton->Left = OpenButton->Left + OpenButton->Width + 10;
		EditButton->Top = OpenButton->Top;

		ScrollBox->Left = (SaveButton->Left + SaveButton->Width);
		ScrollBox->Top = ScrollBox->Left;
		ScrollBox->Width = this->Width - (2 * ScrollBox->Left);
		ScrollBox->Height = ScrollBox->Width;

		SaveButton->BringToFront();
		CloseButton->BringToFront();
		OpenButton->BringToFront();

		Image->BringToFront();
		ImageEnView->SendToBack();

		AdvWiiProgressBar->Width = 3*AdvWiiProgressBar->Width;
		AdvWiiProgressBar->Height = 3*AdvWiiProgressBar->Height;


		myTools->Height = 500;
		myTools->Width = 500;
		myTools->Top = mainForm->Height/2 - myTools->Height/2;
		myTools->Left = mainForm->Width/2 - myTools->Width/2;

		ToolsPanel->Top = PanelResolution->Top - ToolsPanel->Height / 5;
		ToolsPanel->Left = PanelResolution->Left + PanelResolution->Width + 10;
		AdvComboBoxTools->ItemIndex = AdvComboBoxTools->Items->Count - 1 ;
		InitPaint();

		first = true;

	}

	AdvWiiProgressBar->Visible = false;
	AdvWiiProgressBar->Hide();
	AdvWiiProgressBar->BringToFront();
	mainForm->Enabled = false;

	this->Enabled = true;

//	if(mainForm->myLithoFrm->LithoConfigFrm->changeRes)
//		InitPaint();
}
//---------------------------------------------------------------------------

void TPaintForm::InitPaint()
{
	int item_index = mainForm->myLithoFrm->LithoConfigFrm->AdvComboBoxResolution->ItemIndex;
	int resolution = mainForm->myLithoFrm->LithoConfigFrm->AdvComboBoxResolution->Items->operator [](item_index).ToInt();

	if(ScrollBox->Width > resolution){
		PanelPaint->Align = alClient;
	}
	else{
		PanelPaint->Align = alNone;
		PanelPaint->Left = 0;
		PanelPaint->Top = 0;

		PanelPaint->Width = resolution;
		PanelPaint->Height = resolution;
	}

	AdvWiiProgressBar->Left = ScrollBox->Width/2 - AdvWiiProgressBar->Width/2;
	AdvWiiProgressBar->Top = ScrollBox->Height/2 - AdvWiiProgressBar->Height/2;
	mainForm->myLithoFrm->LithoConfigFrm->changeRes = false;

	LastBitmap->Width = resolution;
	LastBitmap->Height = resolution;
	LastBitmap->Canvas->FillRect(TRect(0,0,resolution, resolution));
	LastBitmap->SaveToFile( MainPath + "/" + "bitmap.bmp");

	FileDataTime = FileAge(MainPath + "/" + "bitmap.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	mainForm->LogToFile("TPaintForm::FormClose");
	Action = Vcl::Forms::caNone;
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::OpenButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TPaintForm::OpenButtonClick");
	if(OpenPictureDialog->Execute() && OpenPictureDialog->FileName != "" ){

		if(ImageEnView->IO->LoadFromFile(OpenPictureDialog->FileName)){
			GrayStylePic();

			LastBitmap->Width = Image->Width;
			LastBitmap->Height = Image->Height;
//			LastBitmap->Canvas->StretchDraw(TRect(0,0,LastBitmap->Width, LastBitmap->Height), ImageEnView->Bitmap);
			LastBitmap->Canvas->CopyRect(TRect(0,0,LastBitmap->Width, LastBitmap->Height), ImageEnView->Bitmap->Canvas, TRect(0,0,ImageEnView->Bitmap->Width, ImageEnView->Bitmap->Height));
			LastBitmap->SaveToFile( MainPath + "/" + "bitmap.bmp");
			Image->Picture->Assign(LastBitmap);
		}
	}
}
//---------------------------------------------------------------------------

void TPaintForm::GrayStylePic()
{
	mainForm->LogToFile("TPaintForm::GrayStylePic");
	int col = ImageEnView->Bitmap->Width;
	int row = ImageEnView->Bitmap->Height;

//	mainForm->LogToFile("row = " + IntToStr(row));
//	mainForm->LogToFile("col = " + IntToStr(col));


	for(int j=0; j<row; j++){
		ptr = (TRGBTriple*)ImageEnView->Bitmap->ScanLine[j];
		for(int i=0; i<col; i++){
			int gray = floor((0.299 * ptr[i].rgbtRed) + (0.587 * ptr[i].rgbtGreen) + (0.114 * ptr[i].rgbtBlue) + 0.5);
			ptr[i].rgbtRed = gray;
			ptr[i].rgbtGreen = gray;
			ptr[i].rgbtBlue = gray;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::SaveButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TPaintForm::SaveButtonClick");
	this->Enabled = false;
	BitMapSaved = true;
	AdvWiiProgressBar->Visible = true;
	AdvWiiProgressBar->Show();
	AdvWiiProgressBar->BringToFront();

	Application->ProcessMessages();
	GrayBitmap->Width = mainForm->myLithoFrm->LithoConfigFrm->scan_resolution;
	GrayBitmap->Height = mainForm->myLithoFrm->LithoConfigFrm->scan_resolution;



	bool m = false;
//	GrayBitmap->Canvas->StretchDraw( TRect(0,0,GrayBitmap->Width,GrayBitmap->Height),  Image->Picture->Graphic);
//	mainForm->LogToFile(IntToStr(GrayBitmap->Width) + " * " + IntToStr(GrayBitmap->Height));
	GrayBitmap->Canvas->CopyRect(TRect(0,0,GrayBitmap->Width,GrayBitmap->Height),  Image->Canvas, Image->ClientRect);


//	myLithoThread = new LithoFileCreatorThread(true);
//	myLithoThread->Priority = tpNormal;
//	myLithoThread->FreeOnTerminate = true;
//	myLithoThread->litho_file2 = true;
//	myLithoThread->Start();
//	while(myLithoThread->litho_file2){
//		Application->ProcessMessages();
	if(!m){
		m = true;
		mainForm->myLithoFrm->LithoDesignFrm->Image->Picture->Bitmap->Assign(GrayBitmap);
		mainForm->myLithoFrm->LithoDesignFrm->InitPaint(true);
	}
//	}
//	mainForm->LogToFile("Picture Size = " + IntToStr(Image->Picture->Width) + " * " + IntToStr(Image->Picture->Height));
//	Image->Picture->SaveToFile("my2.bmp");
//	GrayBitmap->SaveToFile("my.bmp");


	AdvWiiProgressBar->Visible = false;
	AdvWiiProgressBar->Hide();
	AdvWiiProgressBar->SendToBack();
	mainForm->Enabled = true;
	mainForm->myVideoForm->VideoGrabber1->StartPreview();
	mainForm->myOscForm->p1PauseClick(NULL);
	this->Hide();
	mainForm->myVideoForm->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	mainForm->LogToFile("TPaintForm::FormCloseQuery");
	CanClose = false;
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::ToolsButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TPaintForm::ToolsButtonClick");
	this->Enabled = false;
	myTools->Show();
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	mainForm->LogToFile("TPaintForm::ImageMouseDown");
	if(AdvComboBoxTools->ItemIndex == 0 && !painting){   //pen
		if(Button == mbLeft){
			int color = ColorGradientBar->ColorIndex;
//			int color = myTools->AdvEditColor->Text.ToInt();
			widthRec = AdvEditWidth->Text.ToInt();
			Image->Canvas->Pen->Color = RGB2TColor(color,color,color);
			Image->Canvas->Pen->Width = AdvEditWidth->Text.ToInt();
//			Image->Canvas->Brush->Color = RGB2TColor(255,255,255);
			Image->Canvas->MoveTo(X - 12, Y);
			paint_state = 0;
			painting = true;
		}
	}
	else if(AdvComboBoxTools->ItemIndex == 1 && !painting){   //rect
		if(Button == mbLeft){
			int color = ColorGradientBar->ColorIndex;
//			int color = myTools->AdvEditColor->Text.ToInt();
			widthRec = AdvEditWidth->Text.ToInt();
			Image->Canvas->Pen->Color = RGB2TColor(color,color,color);
			Image->Canvas->Pen->Width = widthRec;
			Image->Canvas->Brush->Style = Vcl::Graphics::bsClear;
//			Image->Canvas->Brush->Color = RGB2TColor(255,255,255);
			Image->Canvas->MoveTo(X, Y);
			x1 = X;
			y1 = Y;
			paint_state = 1;
			painting = true;
		}
	}
	else if(AdvComboBoxTools->ItemIndex == 2 && !painting){  //circle
		if(Button == mbLeft){
			int color = ColorGradientBar->ColorIndex;
//			int color = myTools->AdvEditColor->Text.ToInt();
			widthRec = AdvEditWidth->Text.ToInt();
			Image->Canvas->Pen->Color = RGB2TColor(color,color,color);
			Image->Canvas->Pen->Width = widthRec;
			Image->Canvas->Brush->Style = Vcl::Graphics::bsClear;
//			Image->Canvas->Brush->Color = RGB2TColor(255,255,255);
			Image->Canvas->MoveTo(X, Y);
			x1 = X;
			y1 = Y;
			paint_state = 2;
			painting = true;
		}
	}
	else if(AdvComboBoxTools->ItemIndex == 3 && !painting){   //line
		if(Button == mbLeft){
			int color = ColorGradientBar->ColorIndex;
//			int color = myTools->AdvEditColor->Text.ToInt();
			widthRec = AdvEditWidth->Text.ToInt();
			Image->Canvas->Pen->Color = RGB2TColor(color,color,color);
			Image->Canvas->Pen->Width = widthRec;
			Image->Canvas->Brush->Style = Vcl::Graphics::bsClear;
//			Image->Canvas->Brush->Color = RGB2TColor(255,255,255);
			Image->Canvas->MoveTo(X, Y);
			x1 = X;
			y1 = Y;
			paint_state = 3;
			painting = true;
		}
	}
	else if(AdvComboBoxTools->ItemIndex == 4 && !painting){   //brush
		if(Button == mbLeft){
			int color = ColorGradientBar->ColorIndex;
//			int color = myTools->AdvEditColor->Text.ToInt();
			widthRec = AdvEditWidth->Text.ToInt();
			Image->Canvas->Pen->Color = RGB2TColor(color,color,color);
			Image->Canvas->Pen->Width = widthRec;
			Image->Canvas->Brush->Style = Vcl::Graphics::bsSolid;
			Image->Canvas->Brush->Color = RGB2TColor(color,color,color);
			Image->Canvas->MoveTo(X, Y);
			widthRec = 10 + widthRec;
			Image->Canvas->Ellipse(X, Y, X - widthRec, Y - widthRec);
			paint_state = 5;
			painting = true;
		}
	}
	else if(AdvComboBoxTools->ItemIndex == 5 && !painting){  //eraser
		if(Button == mbLeft){
			widthRec = AdvEditWidth->Text.ToInt();
			Image->Canvas->Pen->Color = clWhite;
			Image->Canvas->Pen->Width = widthRec;
			Image->Canvas->Brush->Style = Vcl::Graphics::bsSolid;
			Image->Canvas->Brush->Color = clWhite;
			Image->Canvas->MoveTo(X, Y);
			widthRec = 10 + widthRec;
			Image->Canvas->Rectangle(X, Y, X - widthRec, Y - widthRec);
			paint_state = 4;
			painting = true;
		}
	}
	else if(AdvComboBoxTools->ItemIndex == 6 && !painting){    //none
//		if(Button == mbLeft){
//			int color = myTools->AdvEditColor->Text.ToInt();
//			widthRec = AdvEditWidth->Text.ToInt();
//			Image->Canvas->Pen->Color = RGB2TColor(color,color,color);
//			Image->Canvas->Pen->Width = widthRec;
//			Image->Canvas->Brush->Style = Vcl::Graphics::bsClear;
//			Image->Canvas->MoveTo(X, Y);
//			x1 = X;
//			y1 = Y;
//			paint_state = 6;
//			painting = true;
//		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::ImageMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	mainForm->LogToFile("TPaintForm::ImageMouseUp");
//	mainForm->LogToFile("shift : " + IntToStr(Shift.ToInt()));
	if(painting){
		if(paint_state == 0){
			if(HoldingSomtings){
				if(Shift.ToInt() == 2)
					Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
				HoldingSomtings = false;
			}
		}
		if(paint_state == 1){
			if(HoldingSomtings){
				if(Shift.ToInt() == 2)
					Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
				HoldingSomtings = false;
			}
		}
		else if(paint_state == 2){
			if(HoldingSomtings){
				if(Shift.ToInt() == 2)
					Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
				HoldingSomtings = false;
			}
		}
		else if(paint_state == 3){
			if(HoldingSomtings){
				if(Shift.ToInt() == 2)
					Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
				HoldingSomtings = false;
			}
		}
		else if(paint_state == 4){
			if(HoldingSomtings){
				if(Shift.ToInt() == 2)
					Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
				HoldingSomtings = false;
			}
		}
		else if(paint_state == 5){
			if(HoldingSomtings){
				if(Shift.ToInt() == 2)
					Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
				HoldingSomtings = false;
			}
		}
		else if(paint_state == 6){
//			if(HoldingSomtings){
//				if(Shift.ToInt() == 2)
//					Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
//				HoldingSomtings = false;
//			}
		}
		painting = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::ImageMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(painting && paint_state == 0){ //pen
		Image->Canvas->LineTo(X - 12, Y);
	}
	else if(painting && paint_state == 1){ //rectangle
		if(HoldingSomtings){
			Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
		}
		Capture(x1, y1, X, Y);
		Image->Canvas->Rectangle(x1, y1, x2, y2);
	}
	else if(painting && paint_state == 2){ //circle
		if(HoldingSomtings){
			Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
		}
		Capture(x1, y1, X, Y);
		Image->Canvas->Ellipse(x1, y1, x2, y2);
	}
	else if(painting && paint_state == 3){ //line
		if(HoldingSomtings){
			Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
		}
		Capture(x1, y1, X, Y);
		Image->Canvas->MoveTo(x1, y1);
		Image->Canvas->LineTo(x2, y2);
	}
	else if(painting && paint_state == 4){ //brush
		Image->Canvas->MoveTo(X, Y);
		Image->Canvas->Rectangle(X, Y, X - widthRec, Y - widthRec);
	}
	else if(painting && paint_state == 5){ //eraser
		Image->Canvas->MoveTo(X, Y);
		Image->Canvas->Ellipse(X, Y, X - widthRec, Y - widthRec);
	}
	else if(painting && paint_state == 6){ //none
//		if(HoldingSomtings){
//			Image->Canvas->CopyRect(R1, HoldingArea->Canvas, R2);
//		}
//		Capture(x1, y1, X, Y);
//		Image->Canvas->Chord(x1, y1, x2, y2, x1 + (0.7071 * x1), y1 + (0.7071 * y1), x2 - (0.7071 * x2), y2 + (0.071 * y2));
	}
}
//---------------------------------------------------------------------------

void TPaintForm::Capture(int x1, int y1, int x, int y)
{
	mainForm->LogToFile("TPaintForm::Capture");
	x2 = x;
	y2 = y;
	HoldingArea->Width = abs(x2-x1) + 2 * widthRec;
	HoldingArea->Height = abs(y2-y1) + 2 * widthRec;

	if (x1 < x2){
		R1.Left = x1 - widthRec;
		R1.Right = x2 + widthRec;
	}
	else{
		R1.Left = x2 - widthRec;
		R1.Right = x1 + widthRec;
	}

	if(y1 < y2){
		R1.Top = y1 - widthRec ;
		R1.Bottom = y2 + widthRec;
	}
	else{
		R1.Top = y2 - widthRec;
		R1.Bottom = y1 + widthRec;
	}

	R2.Left = 0;
	R2.Top = 0;
	R2.Right = R1.Right - R1.Left;
	R2.Bottom = R1.Bottom - R1.Top;

	HoldingArea->Canvas->CopyRect(R2, Image->Canvas, R1);
	HoldingSomtings = true;


}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::EditButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TPaintForm::EditButtonClick");
	int item_index = mainForm->myLithoFrm->LithoConfigFrm->AdvComboBoxResolution->ItemIndex;
	int resolution = mainForm->myLithoFrm->LithoConfigFrm->AdvComboBoxResolution->Items->operator [](item_index).ToInt();
	LastBitmap->Width = resolution;
	LastBitmap->Height = resolution;
	LastBitmap->Canvas->CopyRect(TRect(0,0,LastBitmap->Width, LastBitmap->Height), Image->Canvas, Image->ClientRect);
	LastBitmap->SaveToFile( MainPath + "/" + "bitmap.bmp");
//    mainForm->LogToFile("mainpath = " + MainPath);

	UnicodeString app = "mspaint.exe";
	UnicodeString ffile = MainPath + "\\" + "bitmap.bmp";  //critical use of "\\" beacuse of ffile.c_str()
//	UnicodeString ffile = "bitmap.bmp";
//	mainForm->LogToFile("file = " + ffile);
	LastBitmap->LoadFromFile(ffile);
	ShellExecute(0, NULL, app.c_str(), ffile.c_str(), NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TPaintForm::AdvComboBoxToolsChange(TObject *Sender)
{
	mainForm->LogToFile("TPaintForm::AdvComboBoxToolsChange");
    if(AdvComboBoxTools->ItemIndex == 0){   //pen
		Image->Cursor = crMyPenCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 1){	//rect
		Image->Cursor = crMyRectCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 2){	//circle
		Image->Cursor = crMyCircCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 3){	//line
		Image->Cursor = crMyLineCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 4){	//brush
		Image->Cursor = crMyBrushCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 5){	//eraser
		Image->Cursor = crMyEraseCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 6){	//None
		Image->Cursor = crDefault;
	}
}
//---------------------------------------------------------------------------



