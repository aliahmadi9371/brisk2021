//---------------------------------------------------------------------------

#ifndef TcpLineClassH
#define TcpLineClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "TcpRgbClass.h"
#include "defines.h"
//---------------------------------------------------------------------------

class TcpLineClass
{
protected:

	int LineNumber;


public:
	//functions
	__fastcall TcpLineClass();
	~TcpLineClass();
	void InitOneLine(int mySize);
	int GetMinimumFromLine();
	int GetMaximumFromLine();
	void MapLine0To255(int myMin,int myMax, TRGBTriple * QUAD/*, TRGBTriple * QUADPalette*/, int image_index, bool topo);
	void MapLine0To255_2(int myMin,int myMax, TRGBTriple *QUAD/*, TRGBTriple * QUADPalette*/, int image_index);

//	void DeletePioxels();

	void SetPixelCount(int myPixelCount);
	void SetLineNumber(int myLineNumber);

	int GetPixelCount();
	int GetLineNumber();

	int MaxOfLine;
	int MinOfLine;

	int PixelCount;

    //variables
	TcpRgbClass *Pixels;
    bool created;
};
//---------------------------------------------------------------------------
#endif
