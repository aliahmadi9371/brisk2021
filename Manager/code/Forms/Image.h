//---------------------------------------------------------------------------

#ifndef ImageH
#define ImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "hyiedefs.hpp"
#include "hyieutils.hpp"
#include "iesettings.hpp"
#include "ieview.hpp"
#include "iexBitmaps.hpp"
#include "iexLayers.hpp"
#include "iexRulers.hpp"
#include "imageenview.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TImageShapeForm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TLabel *LabelName;
	TPanel *NotFoundPanel;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ImageDblClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TImageShapeForm(TComponent* Owner);
	void CreateObject(int Resolution);

	int image_number;
	UnicodeString IntAdd;
	double Scale;
	UnicodeString ZUnit;
	int* Main;


};
//---------------------------------------------------------------------------
extern PACKAGE TImageShapeForm *ImageShapeForm;
//---------------------------------------------------------------------------
#endif
