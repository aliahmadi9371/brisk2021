//---------------------------------------------------------------------------

#ifndef TcpDataSendClassH
#define TcpDataSendClassH
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TcpDataSendClass
{
private:	// User declarations
public:		// User declarations
	DynamicArray<Byte> ScanXFilePacket(int* Data , int itemCount);
	DynamicArray<Byte> ScanYFilePacket(int* Data , int itemCount);
	DynamicArray<Byte> ForceZFilePacket(int* Data , int itemCount);
	DynamicArray<Byte> ForceUFilePacket(int* Data , int itemCount);
    DynamicArray<Byte> LithoXFilePacket(int* Data , int itemCount);
	DynamicArray<Byte> LithoYFilePacket(int* Data , int itemCount);
	DynamicArray<Byte> LithoVFilePacket(int* Data , int itemCount ,int LineNumber);

};
#endif


