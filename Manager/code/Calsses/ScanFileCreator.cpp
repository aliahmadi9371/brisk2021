//---------------------------------------------------------------------------
#pragma hdrstop
#include "ScanFileCreator.h"
#include <fstream>
#include "globals.h"


//---------------------------------------------------------------------------
#include "mainUnit.h"
//---------------------------------------------------------------------------

__fastcall ScanFileCreator::ScanFileCreator()
{

}
//---------------------------------------------------------------------------

ScanFileCreator::~ScanFileCreator()
{

}
//---------------------------------------------------------------------------

bool ScanFileCreator::CreateXfile(int start_x, int step_hx, int step_vx, int resolution, int overscan_count)
{
	mainForm->LogToFile("ScanFileCreator::CreateXfile");
	double a1,c1;
	double a2,b2;
	double a3,b3,c3;

	double q = start_x;
	double o = overscan_count;
	double p = resolution;
	double s = step_hx;

    XLength = 2 * p + (4 * o) - 1;
//	mainForm->LogToFile("XFileTcpData.Length = " + IntToStr(XLength));
	XFileTcpData = new int[XLength];

//	mainForm->LogToFile("CreateXfile : overscan_count = " + FloatToStr(overscan_count));
//	mainForm->LogToFile("CreateXfile : resolution = " + FloatToStr(resolution));
//	mainForm->LogToFile("CreateXfile : start_x = " + IntToStr(start_x));
//	mainForm->LogToFile("CreateXfile : step_hx = " + IntToStr(step_hx));
//	mainForm->LogToFile("CreateXfile : step_vx = " + IntToStr(step_vx));


//	ShowMessage("o = " + FloatToStr(o));
	a1 = s / (2.0 * o);

	c1 = q - s * o / 2.0;

	a2 = s;
	b2 = q - (s * o);

	a3 = -s / (2.0 * o);
	b3 = (p * s + 2 * o * s) / o;
	c3 = p * s + q - a3 * pow(p,2.0) + ((-2 * a3 * o) - b3) * p - a3 * pow(o,2.0) - b3 * o;

	double* points = new double[8192];

	for (int i = 0; i < o; i++)
		points[i] = a1 * pow((double)i, 2.0) + c1;

	//check
	if ((points[0] <= -8388607) || (points[0] >= 8388607)){
		// out of bound check
//		mainForm->LogToFile("point[0] = " + FloatToStr(points[0]));
//		mainForm->LogToFile("return false x");
		return false;
	}

	for (int i = o; i < o + p; i++)
		points[i] = a2 * i + b2;
    for (int i = o + p; i < p + 3 * o; i++)
		points[i] = a3 * pow((double)i, 2.0) + b3 * i + c3;

	//check
	if ((points[(int)(p + 2 * o)] >= 8388607) || (points[(int)(p + 2 * o)] >= 8388607)){
	 // out of bound check
//		mainForm->LogToFile("return false x");
		return false;
	}

	for (int i = p + 2 * o + 1; i < 2 * p + (4 * o); i++)
		points[i] = points[(int)(2 * p + (4 * o) - i)];

//	if( !DirectoryExists(UploadPath) ){
//		AnsiString dir = UploadPath;
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//
//	if( !DirectoryExists(DownloadPath) ){
//		AnsiString dir = DownloadPath;
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//	if(!DirectoryExists(UploadPath + "/scan")){
//		AnsiString dir = UploadPath + "/scan";
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//	AnsiString name = UploadPath + "/scan/Xpoints.txt";
//	DeleteFileW(name);
//	ofstream *file;
//	file = new ofstream(name.c_str(), ios::out);
//	AnsiString tmp;
	for(int i=0; i < 2 * p + (4 * o) - 1; i++){
		XFileTcpData[i] = (int)(points[i+1] - points[i]);
//		tmp = IntToStr((int)(points[i+1] - points[i]))+'\n';
//		file->write(tmp.c_str(), tmp.Length());
	}
//	file->close();
	delete[] points;

//	mainForm->LogToFile("scan file for x");
	return true;
}
//---------------------------------------------------------------------------

bool ScanFileCreator::CreateYfile(int start_y, int step_hy, int step_vy,int resolution, int overscan_count)
{
	mainForm->LogToFile("ScanFileCreator::CreateYfile");
	double a1,c1;
	double a2,b2;
	double a3,b3,c3;



	int q = start_y;
	int o = overscan_count;
	int p = resolution;
	int s = step_hy;

    YLength = 2 * p + (4 * o) - 1;
//	mainForm->LogToFile("YFileTcpData.Length = " + IntToStr(YLength));
	YFileTcpData = new int[YLength];

//	mainForm->LogToFile("CreateYfile : overscan_count = " + FloatToStr(overscan_count));
//	mainForm->LogToFile("CreateYfile : resolution = " + FloatToStr(resolution));
//	mainForm->LogToFile("CreateYfile : start_y = " + IntToStr(start_y));
//	mainForm->LogToFile("CreateYfile : step_hy = " + IntToStr(step_hy));
//	mainForm->LogToFile("CreateYfile : step_vy = " + IntToStr(step_vy));

	a1 = s / ((double)2 * (double)o);
	c1 = q - s * o / (double)2;

	a2 = s;
	b2 = q - (s * o);

	a3 = (double)-s / (double)((double)2 * o);
	b3 = (double)(p * s + (double)2 * o * s) / (double)o;
	c3 = p * s + q - a3 * pow((double)p, (double)2) + ((-2 * a3 * o) - b3) * p - a3 * pow((double)o, (double)2) - b3 * o;

	double* points = new double[8192];

	for (int i = 0; i < o; i++)
		points[i] = a1 * pow((double)i, (double)2) + c1;

	//check
	if ((points[0] <= -8388607) || (points[0] >= 8388607)){// out of bound check
//		mainForm->LogToFile("return false y");
		return false;
	}

	for (int i = o; i < o + p; i++)
		points[i] = a2 * i + b2;
	for (int i = o + p; i < p + 3 * o; i++)
		points[i] = a3 * pow((double)i, (double)2) + b3 * i + c3;

	//check
	if ((points[p + 2 * o] >= 8388607) || (points[p + 2 * o] >= 8388607)){
	 // out of bound check
//		mainForm->LogToFile("return false y");
		return false;
	}

	for (int i = p + 2 * o + 1; i < 2 * p + (4 * o); i++)
		points[i] = points[2 * p + (4 * o) - i];
//	if( !DirectoryExists(UploadPath) ){
//		AnsiString dir = UploadPath;
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//
//	if( !DirectoryExists(DownloadPath) ){
//		AnsiString dir = DownloadPath;
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//	if(!DirectoryExists(UploadPath + "/scan")){
//		AnsiString dir = UploadPath + "/scan";
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//	AnsiString name = UploadPath + "/scan/Ypoints.txt";
//	DeleteFileW(name);
//	ofstream *file;
//	file = new ofstream(name.c_str(), ios::out);
//	AnsiString tmp;
	for(int i=0; i < 2 * p + (4 * o) - 1; i++){
		YFileTcpData[i] = (int)(points[i+1] - points[i]);
//		tmp = IntToStr((int)(points[i+1] - points[i]))+'\n';
//		file->write(tmp.c_str(), tmp.Length());
	}
//	file->close();
	delete[] points;
//	mainForm->LogToFile("scan file for y");
	return true;
}
//---------------------------------------------------------------------------
