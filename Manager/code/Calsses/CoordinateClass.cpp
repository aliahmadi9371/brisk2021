﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "CoordinateClass.h"
#include "globals.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------

__fastcall CoordinateClass::CoordinateClass()
{

}
//---------------------------------------------------------------------------

CoordinateClass::~CoordinateClass()
{

}
//---------------------------------------------------------------------------

void CoordinateClass::StartScan(double* center, double xrange, double yrange, double angle, int resolution, int overscan_count)
{
	mainForm->LogToFile("CoordinateClass::StartScan");
//	mainForm->LogToFile("CoordinateClass::StartScan : center = " + FloatToStr(center[0]) + " , " + FloatToStr(center[1]));
//	mainForm->LogToFile("CoordinateClass::StartScan : xrange = " + FloatToStr(xrange));
//	mainForm->LogToFile("CoordinateClass::StartScan : yrange = " + FloatToStr(yrange));
//	mainForm->LogToFile("CoordinateClass::StartScan : angle = " + FloatToStr(angle));
	Resolution = resolution;
	OverScanCount =  overscan_count;
	angle = DegreeToRadian(angle);

	double Range1 = xrange * cos((double)angle) + yrange * sin((double)angle);
	double Range2 = xrange * sin((double)angle) + yrange * cos((double)angle);

	CalcFirstSquare(center,Range1,Range2);
	CalcRotatedSquare(center,angle);
	CalcRealSquare();
	CalcSteps();
	CalcFinalPoints();
}
//---------------------------------------------------------------------------

void CoordinateClass::CalcFirstSquare(double* center, double xrange, double yrange)
{
//	mainForm->LogToFile("CoordinateClass::CalcFirstSquare");
	CalculateCorner(center,xrange,yrange,1,TL1);
	CalculateCorner(center,xrange,yrange,2,TR1);
	CalculateCorner(center,xrange,yrange,3,BL1);
	CalculateCorner(center,xrange,yrange,4,BR1);


//	mainForm->LogToFile("CalcFirstSquare : top left x = " + FloatToStr(TL1[0]) + " , " + "top left y = " + FloatToStr(TR1[1]));
//	mainForm->LogToFile("CalcFirstSquare : top right x = " + FloatToStr(TR1[0]) + " , " + "top right y = " + FloatToStr(TR1[1]));
//	mainForm->LogToFile("CalcFirstSquare : bot left x = " + FloatToStr(BL1[0]) + " , " + "bot left y = " + FloatToStr(BL1[1]));
//	mainForm->LogToFile("CalcFirstSquare : bot right x = " + FloatToStr(BR1[0]) + " , " + "bot right y = " + FloatToStr(BR1[1]));

}
//---------------------------------------------------------------------------

void CoordinateClass::CalculateCorner(double* center, double xrange, double yrange, int corner, double* result)
{
//	mainForm->LogToFile("CoordinateClass::CalculateCorner");
	switch(corner){
		case 1:{ //top left
			result[0] = - xrange/2;
			result[1] = + yrange/2;
			break;
		}
		case 2:{ //top right
			result[0] = + xrange/2;
			result[1] = + yrange/2;
			break;
		}
		case 3:{ //bot left
			result[0] = - xrange/2;
			result[1] = - yrange/2;;
			break;
		}
		case 4:{ //bot right
			result[0] = + xrange/2;
			result[1] = - yrange/2;
		}
	}
}
//---------------------------------------------------------------------------

void CoordinateClass::CalcRotatedSquare(double* center, double angle)
{
//	mainForm->LogToFile("CoordinateClass::CalcRotatedSquare");
	Rotate(TL1,center,angle,TL2);
	Rotate(TR1,center,angle,TR2);
	Rotate(BL1,center,angle,BL2);
	Rotate(BR1,center,angle,BR2);
//
//	mainForm->LogToFile("CalcRotatedSquare : top left x = " + FloatToStr(TL2[0]) + " , " + "top left y = " + FloatToStr(TL2[1]));
//	mainForm->LogToFile("CalcRotatedSquare : top right x = " + FloatToStr(TR2[0]) + " , " + "top right y = " + FloatToStr(TR2[1]));
//	mainForm->LogToFile("CalcRotatedSquare : bot left x = " + FloatToStr(BL2[0]) + " , " + "bot left y = " + FloatToStr(BL2[1]));
//	mainForm->LogToFile("CalcRotatedSquare : bot right x = " + FloatToStr(BR2[0]) + " , " + "bot right y = " + FloatToStr(BR2[1]));

}
//---------------------------------------------------------------------------

void CoordinateClass::Rotate(double* A, double* center, double angle, double* rotate)
{

//	mainForm->LogToFile("CoordinateClass::Rotate");
	rotate[0] = center[0] + (A[0])*cos((double)angle) - (A[1])*sin((double)angle);
	rotate[1] = center[1] + (A[0])*sin((double)angle) + (A[1])*cos((double)angle);

//	mainForm->LogToFile("Rotate : rotate[0] = " + FloatToStr(rotate[0]) + " , " + "rotate[1] = " + FloatToStr(rotate[1]));




}
//---------------------------------------------------------------------------

void CoordinateClass::CalcRealSquare()
{
//	mainForm->LogToFile("CoordinateClass::CalcRealSquare");
	PercentToReal(TL2, RealTL);
	PercentToReal(TR2, RealTR);
	PercentToReal(BL2, RealBL);
	PercentToReal(BR2, RealBR);

//	mainForm->LogToFile("CalcRealSquare : top left x = " + FloatToStr(RealTL[0]) + " , " + "top left y = " + FloatToStr(RealTL[1]));
//	mainForm->LogToFile("CalcRealSquare : top right x = " + FloatToStr(RealTR[0]) + " , " + "top right y = " + FloatToStr(RealTR[1]));
//	mainForm->LogToFile("CalcRealSquare : bot left x = " + FloatToStr(RealBL[0]) + " , " + "bot left y = " + FloatToStr(RealBL[1]));
//	mainForm->LogToFile("CalcRealSquare : bot right x = " + FloatToStr(RealBR[0]) + " , " + "bot right y = " + FloatToStr(RealBR[1]));
}
//---------------------------------------------------------------------------

void CoordinateClass::CalcSteps()
{
//	mainForm->LogToFile("CoordinateClass::CalcSteps");
	Sub(RealTR,RealTL,StepHor);
	Division(StepHor,Resolution,StepHor);

	Sub(RealBL,RealTL,StepVer);
	Division(StepVer,Resolution,StepVer);


//	mainForm->LogToFile("CalcSteps : StepHor x = " + FloatToStr(StepHor[0]) + " , " + "StepHor y = " + FloatToStr(StepHor[1]));
//	mainForm->LogToFile("CalcSteps : StepVer x = " + FloatToStr(StepVer[0]) + " , " + "StepVer y = " + FloatToStr(StepVer[1]));
}
//---------------------------------------------------------------------------


void CoordinateClass::CalcFinalPoints()
{
//	mainForm->LogToFile("CoordinateClass::CalcFinalPoints");
	Multiply(StepHor,OverScanCount/2,OverScanVector);
	Sub(RealTL,OverScanVector,FinalRealTL);
	Sub(RealBL,OverScanVector,FinalRealBL);
	Add(RealTR,OverScanVector,FinalRealTR);
	Add(RealBR,OverScanVector,FinalRealBR);
//
//	mainForm->LogToFile("CalcFinalPoints : OverScanVector x = " + FloatToStr(OverScanVector[0]) + " , " + "OverScanVector y = " + FloatToStr(OverScanVector[1]));
//	mainForm->LogToFile("CalcFinalPoints : top left x = " + FloatToStr(FinalRealTL[0]) + " , " + "top left y = " + FloatToStr(FinalRealTL[1]));
//	mainForm->LogToFile("CalcFinalPoints : top right x = " + FloatToStr(FinalRealTR[0]) + " , " + "top right y = " + FloatToStr(FinalRealTR[1]));
//	mainForm->LogToFile("CalcFinalPoints : bot left x = " + FloatToStr(FinalRealBL[0]) + " , " + "bot left y = " + FloatToStr(FinalRealBL[1]));
//	mainForm->LogToFile("CalcFinalPoints : bot right x = " + FloatToStr(FinalRealBR[0]) + " , " + "bot right y = " + FloatToStr(FinalRealBR[1]));
}
//---------------------------------------------------------------------------

void CoordinateClass::Sub(double* A, double* B, double* sub)
{
//	mainForm->LogToFile("CoordinateClass::Sub(double* A, double* B, double* sub)");
	sub[0] = A[0] - B[0];
	sub[1] = A[1] - B[1];

}
//---------------------------------------------------------------------------

void CoordinateClass::Sub(double A, double* B, double* sub)
{
//	mainForm->LogToFile("CoordinateClass::Sub(double A, double* B, double* sub)");
	sub[0] = A - B[0];
	sub[1] = A - B[1];

}
//---------------------------------------------------------------------------

void CoordinateClass::PercentToReal(double* A, double* Real)
{
//	mainForm->LogToFile("CoordinateClass::PercentToReal");
	switch (Scanner_Type){
		case 0:{
			Real[0] =  8388607 - A[0] * 167772.14;
			Real[1] =  A[1] * 167772.14 - 8388607;
			break;
		}
		case 1:{
			Real[0] =  8388607 - A[0] * 167772.14;
			Real[1] =  8388607 - A[1] * 167772.14;
			break;
		}
		case 2:{
			Real[0] =  A[0] * 167772.14 - 8388607;
			Real[1] =  8388607 - A[1] * 167772.14;
			break;
		}
		case 3:{
			Real[0] =  A[0] * 167772.14 - 8388607;
			Real[1] =  A[1] * 167772.14 - 8388607;
			break;
		}
	}

}

//---------------------------------------------------------------------------

void CoordinateClass::Add(double* A, double* B, double* add)
{
//	mainForm->LogToFile("CoordinateClass::Add(double* A, double* B, double* add)");
	add[0] = A[0] + B[0];
	add[1] = A[1] + B[1];
}
//---------------------------------------------------------------------------

void CoordinateClass::Add(double* A, double B, double* add)
{
//	mainForm->LogToFile("CoordinateClass::Add(double* A, double B, double* add)");
	add[0] = A[0] + B;
	add[1] = A[1] + B;
}
//---------------------------------------------------------------------------

void CoordinateClass::Division(double* A, double b, double* div)
{
//	mainForm->LogToFile("CoordinateClass::Division");
	div[0] = A[0]/b;
	div[1] = A[1]/b;
}
//---------------------------------------------------------------------------

void CoordinateClass::Absolute(double* A, double* abs)
{
//	mainForm->LogToFile("CoordinateClass::Absolute");
	if(A[0] < 0) abs[0] = A[0] * -1;
	if(A[1] < 0) abs[1] = A[1] * -1;
}
//---------------------------------------------------------------------------

void CoordinateClass::Multiply(double* A,  double b, double* Mul)
{
//	mainForm->LogToFile("CoordinateClass::Multiply");
	Mul[0] = A[0] * b;
	Mul[1] = A[1] * b;
}
//---------------------------------------------------------------------------

void CoordinateClass::CalculateStepHor(double* topleft, double* topright, int resolution, double* stephor)
{
//	mainForm->LogToFile("CoordinateClass::CalculateStepHor");
	Sub(topright,topleft,stephor);
	Division(stephor,resolution,stephor);
}
//---------------------------------------------------------------------------

void CoordinateClass::CalculateStepVer(double* topleft, double* botleft, int resolution, double* stepver)
{
//	mainForm->LogToFile("CoordinateClass::CalculateStepVer");
	Sub(botleft,topleft,stepver);
	Division(stepver,resolution,stepver);
}
//---------------------------------------------------------------------------

int CoordinateClass::NanoDelayCaculate(int resolution, int speed, int eachProcess )
{
//	mainForm->LogToFile("CoordinateClass::NanoDelayCaculate");
	return ( (int)((double) pow( (double)10,(double)9 ) / (speed * resolution * (float)eachProcess)) );
}
//---------------------------------------------------------------------------

double CoordinateClass::RadianToDegree(double radian)
{
//	mainForm->LogToFile("CoordinateClass::RadianToDegree");
	return (double)( radian*180/M_PI );
}
//---------------------------------------------------------------------------

double CoordinateClass::DegreeToRadian(double degree)
{
	mainForm->LogToFile("CoordinateClass::DegreeToRadian");
	return (double)( degree*M_PI/180 );
}
//---------------------------------------------------------------------------



