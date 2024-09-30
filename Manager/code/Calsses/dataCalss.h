//---------------------------------------------------------------------------

#ifndef dataCalssH
#define dataCalssH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "defines.h"
#include "queueClassUdp.h"

//---------------------------------------------------------------------------
class DataCalss
{
private:
protected:
public:
	__fastcall DataCalss();
	double Average();
	double GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,bool bits, bool UnSigned, int ScopIndex, bool allIndex);

	int data_buf[BufferSize];
	int BufSize;
	int counter;
	double currAvg;
	double data_index;
	double data_offset;
	int data_scale;
	queueClassUdp* my_q_ptr;
	void setscale(int scale);

	void CreateClass(queueClassUdp* q_ptr, double index, double offset, int scale);
	bool bool_created;


	void LogData(int packet_index, int ScopIndex, unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3);
	int mcounter;

};
//---------------------------------------------------------------------------
#endif
