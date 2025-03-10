//---------------------------------------------------------------------------
#ifndef globalsH
#define globalsH

#include "queueClassTcp.h"
#include "queueClassUdp.h"
#include "queueClassTcpDnc.h"

extern queueClassUdp *data_queue;
extern queueClassTcp *img_queue;
extern queueClassTcpDnc *dnc_queue;
extern int UdpTbRef;
extern int UdpAmpRef;
extern bool AllScale;
extern bool HaveLicense;
extern bool SaveImages;


extern UnicodeString MainPath;
extern UnicodeString UploadPath;
extern UnicodeString DownloadPath;
extern UnicodeString DataBasePath;
extern UnicodeString LastImagesFolderPath;

extern DWORD hid;
extern DWORD sid;
extern UnicodeString DBPassWord;

extern int Scanner_Type;

extern struct ForceCommands{
	bool start;
	double startx;
	double starty;
	int resolution;
	int delay;
	int mode;
	int GOTO;
	int dz1;
	int dz2;
	int u1;
	int u2;
	int currentZ;
	int currentU;
}FsCommand;

extern struct ScanCommands{
	bool start;
	bool set;
	int Changer;
}ScanCommand;

extern struct LicenseTable {
	int id;
	double TotalTime;
	double WorkedTime;
	double RemainedTime;
}LicTable;

extern struct INFO_CONFIG {
	int id;
	UnicodeString url;
	UnicodeString tel;
}InfoTable;

extern struct APPLICATION_CONFIG {
	int id;
	int App_LastMode_Val;
	int osc;
}ApplicationTable;

extern struct UDP_CONFIG {
	int id;
	int local_port;
	int remote_port;
	UnicodeString server;
	UnicodeString system;
	int connection_try;
	int record_time;
}UdpTable;

extern struct TCP_CONFIG{
	int id;
	int local_port;
	int remote_port;

}TcpTable;

extern struct OSC_CHART_CONFIG{
	int id;
	int osc1;
	int osc2;
	int osc3;
	int osc4;
	int timedev;
	bool all_scale;

}OscChartTable;

extern struct OSC_CONFIG{
	int id;
	UnicodeString name;
	double index;
	double offset;
	UnicodeString unit;
	int scale;
}OscTable[27];

extern struct APPROACH_CONFIG{
	int id;
	int Apr_Refrerence_Val;
	int Apr_Ki_Val_Contact;
	int Apr_Ki_Val_NonContact;
	int Apr_Bias_Val;
	int Apr_Kd_Val;
	int Apr_Kp_Val;
	int Apr_KiFeedbak_Val_Contact;
	int Apr_KiFeedbak_Val_NonContact;
	int Apr_ZPosition_Val;
	int Apr_SteperSpeed_Val_Precise;
	int Apr_SteperStepMicro_Val_Precise;
	int Apr_StepperSpeed_Val_Fast;
	int Apr_StepperStepMicro_Val_Fast;
	int Apr_StepperStep_Val;
	int Apr_ScanSpeed_Val;
	int Apr_BiasIndex_Val;
	int Apr_BiasOffset_Val;
}ApproachTable;

extern struct FAST_APPROACH_DNC_CONFIG{
	int id;
	int Dnc_FrequencyFrom_Val;
	int Dnc_FrequencyTo_Val;
	int Threshold_Contact;
	int Threshold_NonContact;
	int Min_Amp;
	int Max_Amp;
	int Drive_Start;
}FastApproachTable;

extern struct COARSEMOVE_CONFIG{
	int id;
	int Coarse_StepperSpeed_Val_Slow;
	int Coarse_StepperSpeed_Val_Fast;
	int Coarse_StepperStepMicro_Val;
}MoveTable;

extern struct RETRACT_CONFIG{
	int id;
	int Ret_OneStep_Val;
	int Ret_StepperSpeed_Val;
	int Ret_StepperStepMicro_Val;
}RetractTable;

extern struct STAGE_CONFIG{
	int id;
	int Stage_StepperSpeed_Val_Slow;
	int Stage_StepperSpeed_Val_Fast;
	int Stage_StepperStepMicro_Val;
}StageTable;

extern struct DNC_CONFIG{
	int id;
	int Dnc_FrequencyFromMin_Val;
	int Dnc_FrequencyFrom_Val;
	int Dnc_FrequencyToMax_Val;
	int Dnc_FrequencyTo_Val;
	int Dnc_FrequencyUse_Val;
	int Dnc_DriveVoltage_Val;
	int Dnc_PointsCount_Val;
	int Dnc_SetPointPercentage_Val;
	double Dnc_TimeCnt_Val;
	int Dnc_RollOff_Val;
	double Dnc_DriveIndex_Val;
	double Dnc_DriveOffset_Val;
	double Dnc_Refrence_Val;
}DncTable;

extern struct SCAN_CONFIG{
	int id;
	double Scan_Range_Val;
	double Scan_X_Center_Val;
	double Scan_Y_Center_Val;
	double Scan_Speed_Val;
	int Scan_Angle_Val;
	int Scan_Resolution_Val;
	double Scan_OverScan_Val;
	bool Scan_1D_Leveling;
	bool Scan_2D_Leveling;
	int LITHO_CONFIG;
	double Scan_Offset_val;
}ScanTable;

extern struct LITHO_CONFIG{
	int id;
	int Litho_Delay;
}LithoTable;

extern struct FORCE_CONFIG{
	int id;
	double Force_StartX_Val;
	double Force_StartY_Val;
	double Force_Z1_Val;
	double Force_Z2_Val;
	double Force_U1_Val;
	double Force_U2_Val;
	int Force_Delay_Val;
	int Force_Resolution_Index;
	int Force_Mode_Index;
	double TB_C_Factor;
	bool C_Factor_Set;
	double K_Factor;

}ForceTable;

extern struct KPFM_CONFIG{
	int id;
	int Kpfm_Frequency_Val;
	int Kpfm_DriveVoltage_Val;
	int Kpfm_Lia1_Val;
	int Kpfm_Ki_Val;
	int Kpfm_Kp_Val;
	int Kpfm_Kd_Val;
	int Kpfm_Th_Val;
}KpfmTable;

extern struct PARAMETERS{
	int id;
	bool APR_Auto_Tune;
	int Scan_leveling;
	int Scan_Pallet;
	int Apr_F_CON_FREQ_From;
	int Apr_F_CON_FREQ_To;
	int Apr_F_CON_DRV_Start;
	int Apr_F_CON_AMP_MIN;
	int Apr_F_CON_AMP_MAX;
}ParametersTable;

extern struct HARDWARE_TYPE{
	int id;
	int HardWare_Scanner_Type;
	double Max_Range;
	UnicodeString last_IP;
    bool LogToFile;
}HardwareTable;

extern struct Colibration{
	int id;
	int Range_um;
	double X_Range;
	double Y_Range;

}ColibrationTable[56];



//---------------------------------------------------------------------------
#endif



