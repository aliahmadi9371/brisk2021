//---------------------------------------------------------------------------
#ifndef TcpRgbClassH
#define TcpRgbClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TcpRgbClass
{
protected:

public:
	__fastcall TcpRgbClass();
	~TcpRgbClass();
	void SetPixel(unsigned char R, unsigned char G, unsigned char B, unsigned char reserve, TRGBTriple *QUAD);

	void SetMain(int myM);
	int GetMain();

	int Main;  //main parsed data
	int TwoD_Leveled_Main;
};
//---------------------------------------------------------------------------
#endif
