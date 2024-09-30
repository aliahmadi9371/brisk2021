//---------------------------------------------------------------------------

#ifndef TcpImgClassH
#define TcpImgClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <System.SyncObjs.hpp>
#include <System.Math.Vectors.hpp>

#include "TcpLineClass.h"
#include "defines.h"
//---------------------------------------------------------------------------
class TcpImgClass
{
protected:

	//Variables
	int Resolution;
	int PicIndex;
	bool FlyBit;
	bool ForwardBit;
	bool ImageInitBit;
	bool ImageSetBit;
	int ImgIndex;
	bool _24Bit;
	int CurrentMax;
	int CurrentMin;
	bool BitMapBit;
	bool ActiveBit;
	bool StopImaging;

	int LastLine;

	bool FileBit;

private:
    void __fastcall ShowAndSetImages();

public:
	__fastcall TcpImgClass();
	~TcpImgClass();

	void CreateImage(int resolution, int image_index, int pic_index, bool fly, bool forward);

//	TList *ToPoList;

    int *arr;
	//Methods
	void InitClass();
	void InitOneImage(int myValue);
	void Set24BitsFromPacket(int myValue);
	void UpdateColor(int myValue, int myIndex);
	void CreateColors();
	void CreateBitMaps(int mySize);
	void DeleteLines();
	void DeleteBiMap();
	void FinalizeImaging();
//	bool PaletteCreate(unsigned char rDark, unsigned char gDark, unsigned char bDark,unsigned char rLight, unsigned char gLight, unsigned char bLight);
	void CreateFiles();
	void SetFolderFiles(UnicodeString dirName);
	void SetImage(int index);


	bool OneD_Leveling(int currentLine);
	bool TwoD_Leveling(int currentLine);

    AnsiString SetName(int my_image_index);


	//Variables
	int image_index;
	TcpLineClass *Lines;
	TBitmap *map;

	TRGBTriple *ptr;
	TRGBTriple *ptr_2;
//	TRGBTriple *ptr_3;
//	TRGBTriple *ptr_4;

	ofstream *file;
//	TFileStream *fs;

	AnsiString ImageName;
	AnsiString ImageFileName;
	AnsiString ImageFileNametxt;

	AnsiString ModeFolder;
	AnsiString FinalFolderName;
	AnsiString IntFileName;
	AnsiString JpgFileName;
	AnsiString TxtFileName;

	int osc;

	void MapLine0To255(int myMin,int myMax, TRGBTriple * QUAD/*, TRGBTriple * QUADPalette*/, int image_index, bool topo, int line);


	//Setter Functions

	void SetImageName(AnsiString myValue){
		ImageName = myValue;
	}
	void Setimage_index(int myValue){
		image_index = myValue;
	}
	void SetResolution(int myValue){
		Resolution = myValue;
	}
	void SetPicIndex(int myValue){
		PicIndex = myValue;
	}
	void SetFlyBit(bool myValue){
		FlyBit = myValue;
	}
	void SetForwardBit(bool myValue){
		ForwardBit = myValue;
	}
	void SetImageInitBit(bool myValue){
		ImageInitBit = myValue;
	}
	void SetImageSetBit(bool myValue){
		ImageSetBit = myValue;
	}
	void SetImgIndex(int myValue){
		ImgIndex = myValue;
	}
	void SetCurrentMax(int myValue){
		CurrentMax = myValue;
	}
	void SetCurrentMin(int myValue){
		CurrentMin = myValue;
	}
	void SetBitMapBit(bool myValue){
		BitMapBit = myValue;
	}
	void SetActiveBit(bool myValue){
		ActiveBit = myValue;
	}
	void Set_24Bit(bool myValue)
	{
		_24Bit = myValue;
	}
	void SetStopImaging(bool myValue){
		StopImaging = myValue;
	}
	void SetFileBit(bool myValue){
		FileBit = myValue;
	}

	//Getter Functions
	AnsiString GetImageName(){
		return ImageName;
	}
	int Getimage_index(){
		return image_index;
	}
	bool GetFlyBit(){
		return FlyBit;
	}
	bool GetForwardBit(){
		return ForwardBit;
	}
	bool GetImageInitBit(){
		return ImageInitBit;
	}
	bool GetImageSetBit(){
		return ImageSetBit;
	}
	int GetImgIndex(){
		return ImgIndex;
	}
    int GetResolution(){
		return Resolution;
	}
	int GetPicIndex(){
		return PicIndex;
	}
	bool Get_24Bit(){
		return _24Bit;
	}
	int GetCurrentMax(){
		return CurrentMax;
	}
	int GetCurrentMin(){
		return CurrentMin;
	}
	bool GetBitMapBit(){
		return BitMapBit;
	}
	bool GetActiveBit(){
		return ActiveBit;
	}
	bool GetStopImaging(){
		return StopImaging;
	}
	bool GetFileBit(){
		return FileBit;
	}
};
//---------------------------------------------------------------------------
#endif
