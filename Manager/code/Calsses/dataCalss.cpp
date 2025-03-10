//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#pragma hdrstop

#include "dataCalss.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall DataCalss::DataCalss()
{
	bool_created = false;
	BufSize = BufferSize;
	mcounter = 0;
}
//---------------------------------------------------------------------------

double DataCalss::GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,bool bits, bool UnSigned, int ScopIndex, bool allIndex)
{
	unsigned char tmp1[4] ;
	int Sindedtmp = 0 ;
	unsigned int UnSindedtmp = 0 ;
	memset(tmp1,0x00,4);

	//LogData(17, ScopIndex, data0, data1, data2, data3);

	//32 bits to 24 bits
	if(bits){       //24bit
		if(UnSigned){
			tmp1[1] = data0;
			tmp1[2] = data1;
			tmp1[3] = data2;
			memcpy((void *)&UnSindedtmp , (void *)tmp1 , 4);
			UnSindedtmp = UnSindedtmp >> 8 ;
		}
		else{
			tmp1[1] = data0;
			tmp1[2] = data1;
			tmp1[3] = data2;
			memcpy((void *)&Sindedtmp , (void *)tmp1 , 4);
			Sindedtmp = Sindedtmp >> 8 ;
		}
	}
	else{       //32bit
		if(UnSigned){
			tmp1[0] = data0;
			tmp1[1] = data1;
			tmp1[2] = data2;
			tmp1[3] = data3;
			memcpy((void *)&UnSindedtmp , (void *)tmp1 , 4);
		}
		else{
			tmp1[0] = data0;
			tmp1[1] = data1;
			tmp1[2] = data2;
			tmp1[3] = data3;
			memcpy((void *)&Sindedtmp , (void *)tmp1 , 4);
		}
	}

	counter++;
	double t = 0;
	if(UnSigned)
		t = (double)UnSindedtmp;
	else
		t = (double)Sindedtmp;

//	mainForm->LogToFile("KPFM_LIA1_AMP = " + IntToStr());

	if(ScopIndex == 26)
		t = MAX_VALUE - t;
	if(allIndex){
		t = data_index * t + data_offset;
		t = pow10l(data_scale*3) * t;
	}

	if(counter >= my_q_ptr->srDev){
		counter = 0;
		my_q_ptr->enqueue(t);
	}
	return t;
}
//---------------------------------------------------------------------------

double DataCalss::Average()
{
	currAvg = data_buf[counter - 1];
	currAvg = data_index * currAvg + data_offset;
	if(data_scale != 0)
		currAvg = pow10l(data_scale) * currAvg;

	my_q_ptr->enqueue(currAvg);
	return currAvg;
}
//---------------------------------------------------------------------------

void DataCalss::setscale(int scale)
{
	data_scale = scale;
}
//---------------------------------------------------------------------------

void DataCalss::CreateClass(queueClassUdp* q_ptr, double index, double offset, int scale)
{
    my_q_ptr = q_ptr;
	counter = 0;
	currAvg = 0;
	data_index = index;
	data_offset = offset;
	data_scale = scale;
	bool_created = true;
}
//---------------------------------------------------------------------------

void DataCalss::LogData(int packet_index, int ScopIndex, unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3)
{
	if(packet_index != -1){
		if(packet_index == ScopIndex){
            mcounter++;
			if(mcounter % 500 == 0){
				mainForm->LogToFile("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
				mainForm->LogToFile("packet_index : " + IntToStr(packet_index));
				mainForm->LogToFile("data0 : " + IntToHex((int)data0,2));
				mainForm->LogToFile("data1 : " + IntToHex((int)data1,2));
				mainForm->LogToFile("data2 : " + IntToHex((int)data2,2));
				mainForm->LogToFile("data3 : " + IntToHex((int)data3,2));
				mainForm->LogToFile("mcounter : " + IntToStr(mcounter));
				mainForm->LogToFile("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
			}
		}
	}
}
//---------------------------------------------------------------------------

