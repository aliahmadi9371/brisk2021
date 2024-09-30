//---------------------------------------------------------------------------

#ifndef GWYMakerH
#define GWYMakerH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <iostream>

#include <string>
//---------------------------------------------------------------------------
class GWYMakerClass
{
private:
public:
	__fastcall GWYMakerClass();
	void StartSaving(UnicodeString GwyFileAdd);
	void StartSavingFromGallery(UnicodeString GwyFileAdd, int ImageCounts);
	void SetTextLine(AnsiString Text);
	void SetSize(bool Scan, int Resolution , AnsiString Pallet);
	void SetTitel(int ImageNum,AnsiString title);
	void SetVisible(int ImageNum,bool Visible);
	void SetDataField(int ImageNum,int Resolution);
	void Setxres(int Resolution);
	void Setyres(int Resolution);
	void Setxreal(double XReal);
	void Setyreal(double YReal);
	void SetData(bool Scan,int ImageNum,int osc,int Resolution);
	void SetPallet(int ImageNum,AnsiString PalletName);
	void SetXYObjectUnit(int value);
	void SetXYUnit(AnsiString unit);
	void SetZObjectUnit(int value);
	void SetZUnit(AnsiString unit);
	void SetPixels(int Resolution);

	ofstream *file;

	int NULLbyte;
    int ImageCount;
};
//---------------------------------------------------------------------------
#endif
