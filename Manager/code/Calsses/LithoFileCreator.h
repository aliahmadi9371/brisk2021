//---------------------------------------------------------------------------

#ifndef LithoFileCreatorH
#define LithoFileCreatorH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Classes.hpp>
#include <math.h>
#include <stdlib.h>
#include <fstream>
//---------------------------------------------------------------------------
class LithoFileCreator
{
private:
public:
	//functions
	__fastcall LithoFileCreator();
	~LithoFileCreator();
	bool CreateXfile(int start_x, int step_hx, int step_vx, int resolution, int overscan_count);
	bool CreateYfile(int start_y, int step_hy, int step_vy,int resolution, int overscan_count);
//	bool CreateVfile(int resolution);

    int* LithoXFile;
	int* LithoYFile;


	int XLength;
	int YLength;

};
//---------------------------------------------------------------------------
#endif
