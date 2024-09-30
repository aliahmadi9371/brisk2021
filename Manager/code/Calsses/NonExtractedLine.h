//---------------------------------------------------------------------------

#ifndef NonExtractedLineH
#define NonExtractedLineH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "defines.h"
//---------------------------------------------------------------------------
//used in tcp queue
//---------------------------------------------------------------------------
class NonExtractedLine
{
protected:
	//Variables
	bool Created;

public:
	__fastcall NonExtractedLine();
	~NonExtractedLine();

	//Methods
	void newObject(int myResolution);
	void newData(TByteDynArray myData,int myResolution);
	void resetData();

	//Variables

	//Other Variables
//	unsigned char *bytes;
	TByteDynArray bytes;

	//Setter Functions
	void SetCreated(bool myValue){
		Created = myValue;
	}

	//Getter Functions
	bool GetCreated(){
		return Created;
	}

};
//---------------------------------------------------------------------------
#endif
