﻿//---------------------------------------------------------------------------

#ifndef CoordinateClassH
#define CoordinateClassH

#include <vcl.h>
#include <System.Classes.hpp>
#include <System.Math.hpp>
#include <math.h>

//Angle in Radian
//R and C in percent

//---------------------------------------------------------------------------
class CoordinateClass
{
private:



	double OverScan;

public:
	//functions
	__fastcall CoordinateClass();
	~CoordinateClass();
	void Rotate(double* A, double* center, double angle, double* rotate);
	void Sub(double* A, double* B, double* sub); //A - B
	void Sub(double A, double* B, double* sub); //A - b
	void Add(double* A, double* B, double* add);//A + B
	void Add(double* A, double B, double* add); //A + b
	void Division(double* A,  double b, double* div); //A/b
	void Absolute(double* A, double* abs);
	void Multiply(double* A,  double b, double* Mul);
	double RadianToDegree(double radian);
	double DegreeToRadian(double degree);

	void StartScan(double* center, double xrange, double yrange, double angle, int resolution, int overscan_count);
	void CalcFirstSquare(double* center, double xrange, double yrange);
	void CalculateCorner(double* center, double xrange, double yrange, int corner, double* result);
	void CalcRotatedSquare(double* center, double angle);
	void CalcRealSquare();
	void CalcSteps();
	void CalcFinalPoints();

	void PercentToReal(double* A, double* Real);

	void CalculateStepHor(double* topleft, double* topright, int resolution, double* stephor);
	void CalculateStepVer(double* topleft, double* botleft, int resolution, double* stepver);
	int NanoDelayCaculate(int resolution, int speed, int eachProcess);

	int Resolution;

	int OverScanCount;

	double CP[2];	//Center	(Percentage)
	double RP;		//Range  	(Percentage)
	double ϴR;		//Angle  	(Radian)
	double ϴD;		//Angle  	(Degree)

	double StepHor[2];
	double StepVer[2];
	double OverScanVector[2];

	double TL1[2];
	double TR1[2];
	double BL1[2];
	double BR1[2];

	double TL2[2];
	double TR2[2];
	double BL2[2];
	double BR2[2];

	double RealTL[2];
	double RealTR[2];
	double RealBL[2];
	double RealBR[2];

	double FinalRealTL[2];
	double FinalRealTR[2];
	double FinalRealBL[2];
	double FinalRealBR[2];

};
//---------------------------------------------------------------------------
#endif
