//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#pragma hdrstop

#include "DataBaseQueryCreatorClass.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void QueryClass::InitValues()
{
//	License.id = 1;
//	License.TotalTime = 7200;
//	License.WorkedTime = 7200;
//	License.RemainedTime = 0;
}

//---------------------------------------------------------------------------
UnicodeString QueryClass::CreateTable(UnicodeString TableName)
{
//	InitValues();
	if(TableName == "License"){
		query = "CREATE TABLE License(id INTEGER PRIMARY KEY ASC, TotalTime DOUBLE DEFAULT 864000, WorkedTime DOUBLE DEFAULT 864000,RemainedTime DOUBLE DEFAULT 0);";
//		mainForm->LogToFile("query = " + query);
	}
	else if(TableName == "INFO_CONFIG"){
		query = "CREATE TABLE INFO_CONFIG(id INTEGER PRIMARY KEY ASC, url TEXT DEFAULT 'afm-nanoscope.com', tel TEXT DEFAULT '021-76251051');";
	}
	else if(TableName == "APPLICATION_CONFIG"){
		query = "CREATE TABLE APPLICATION_CONFIG(id INTEGER PRIMARY KEY ASC, App_LastMode_Val INTEGER DEFAULT 2, osc INTEGER DEFAULT 1);";
	}
	else if(TableName == "UDP_CONFIG"){
		 query = "CREATE TABLE UDP_CONFIG(id INTEGER PRIMARY KEY ASC, local_port INTEGER DEFAULT 9023, remote_port INTEGER DEFAULT 5560, server TEXT DEFAULT afm_server, system TEXT DEFAULT afm_system, connection_try INTEGER DEFAULT 10, record_time INTEGER DEFAULT 50);";
	}
	else if(TableName == "TCP_CONFIG"){
		 query = "CREATE TABLE TCP_CONFIG(id INTEGER PRIMARY KEY ASC, local_port INTEGER DEFAULT 194 , remote_port INTEGER DEFAULT 8116);";
	}
	else if(TableName == "OSC_CHART_CONFIG"){
		 query = "CREATE TABLE OSC_CHART_CONFIG(id INTEGER PRIMARY KEY ASC, osc1 INTEGER DEFAULT 5, osc2 INTEGER DEFAULT 26, osc3 INTEGER DEFAULT 4, osc4 INTEGER DEFAULT 0, timedev INTEGER DEFAULT 3, all_scale BOOL DEFAULT 1);";
	}
	else if(TableName == "OSC_CONFIG"){
		 query = "CREATE TABLE OSC_CONFIG(id INTEGER PRIMARY KEY ASC, name TEXT DEFAULT Name, _index DOUBLE DEFAULT 1, _offset DOUBLE DEFAULT 0, unit TEXT DEFAULT Unit, scale INTEGER DEFAULT 0);";
	}
	else if(TableName == "APPROACH_CONFIG"){
		 query = "CREATE TABLE APPROACH_CONFIG(id INTEGER PRIMARY KEY ASC, Apr_Refrerence_Val INTEGER DEFAULT 80, Apr_Ki_Val_Contact INTEGER DEFAULT 50000, Apr_Ki_Val_NonContact INTEGER DEFAULT 70000, Apr_Bias_Val INTEGER DEFAULT 0, Apr_Kd_Val INTEGER DEFAULT 0, Apr_Kp_Val INTEGER DEFAULT 0, Apr_KiFeedbak_Val_Contact INTEGER DEFAULT 300000, Apr_KiFeedbak_Val_NonContact INTEGER DEFAULT 300000,Apr_ZPosition_Val INTEGER DEFAULT -8388608, Apr_SteperSpeed_Val_Precise INTEGER DEFAULT 200000, Apr_SteperStepMicro_Val_Precise INTEGER DEFAULT 3, Apr_StepperSpeed_Val_Fast INTEGER DEFAULT 1500000, Apr_StepperStepMicro_Val_Fast INTEGER DEFAULT 3, Apr_StepperStep_Val INTEGER DEFAULT 1, Apr_ScanSpeed_Val INTEGER DEFAULT 1, Apr_BiasIndex_Val DOUBLE DEFAULT 870, Apr_BiasOffset_Val DOUBLE DEFAULT -70000);";
	}
	else if(TableName == "FAST_APPROACH_DNC_CONFIG"){
		 query = "CREATE TABLE FAST_APPROACH_DNC_CONFIG(id INTEGER PRIMARY KEY ASC, Dnc_FrequencyFrom_Val INTEGER DEFAULT 10000, Dnc_FrequencyTo_Val INTEGER DEFAULT 500000, Threshold_Contact INTEGER DEFAULT 7000, Threshold_NonContact INTEGER DEFAULT 2500, Min_Amp INTEGER DEFAULT 170, Max_Amp INTEGER DEFAULT 180, Drive_Start INTEGER DEFAULT 100);";
	}
	else if(TableName == "COARSEMOVE_CONFIG"){
		 query = "CREATE TABLE COARSEMOVE_CONFIG(id INTEGER PRIMARY KEY ASC, Coarse_StepperSpeed_Val_Slow INTEGER DEFAULT 1000000, Coarse_StepperSpeed_Val_Fast INTEGER DEFAULT 100000, Coarse_StepperStepMicro_Val INTEGER DEFAULT 3);";
	}
	else if(TableName == "RETRACT_CONFIG"){
		 query = "CREATE TABLE RETRACT_CONFIG(id INTEGER PRIMARY KEY ASC, Ret_OneStep_Val INTEGER DEFAULT 2, Ret_StepperSpeed_Val INTEGER DEFAULT 200000, Ret_StepperStepMicro_Val INTEGER DEFAULT 3);";
	}
	else if(TableName == "STAGE_CONFIG"){
		 query = "CREATE TABLE STAGE_CONFIG(id INTEGER PRIMARY KEY ASC, Stage_StepperSpeed_Val_Slow INTEGER DEFAULT 500000, Stage_StepperSpeed_Val_Fast INTEGER DEFAULT 100000, Stage_StepperStepMicro_Val INTEGER DEFAULT 3);";
	}
	else if(TableName == "DNC_CONFIG"){
		 query = "CREATE TABLE DNC_CONFIG(id INTEGER PRIMARY KEY ASC, Dnc_FrequencyFromMin_Val INTEGER DEFAULT 10000, Dnc_FrequencyFrom_Val INTEGER DEFAULT 10000, Dnc_FrequencyToMax_Val INTEGER DEFAULT 500000, Dnc_FrequencyTo_Val INTEGER DEFAULT 500000, Dnc_FrequencyUse_Val INTEGER DEFAULT 100000, Dnc_DriveVoltage_Val INTEGER DEFAULT 130, Dnc_PointsCount_Val INTEGER DEFAULT 1024, Dnc_SetPointPercentage_Val INTEGER DEFAULT 60, Dnc_TimeCnt_Val DOUBLE DEFAULT 0, Dnc_RollOff_Val INTEGER DEFAULT 0, Dnc_DriveIndex_Val DOUBLE DEFAULT 1.35, Dnc_DriveOffset_Val DOUBLE DEFAULT 0, Dnc_Refrence_Val DOUBLE DEFAULT 0.165638881023259);";
	}
	else if(TableName == "LITHO_CONFIG"){
		 query = "CREATE TABLE LITHO_CONFIG(id INTEGER PRIMARY KEY ASC, Litho_Delay INTEGER DEFAULT 100);";
	}
	else if(TableName == "SCAN_CONFIG"){
		 query = "CREATE TABLE SCAN_CONFIG(id INTEGER PRIMARY KEY ASC, Scan_Range_Val DOUBLE DEFAULT 10, Scan_X_Center_Val DOUBLE DEFAULT 0, Scan_Y_Center_Val DOUBLE DEFAULT 0, Scan_Speed_Val DOUBLE DEFAULT 1, Scan_Angle_Val INTEGER DEFAULT 0, Scan_Resolution_Val INTEGER DEFAULT 256, Scan_OverScan_Val DOUBLE DEFAULT 12, Scan_1D_Leveling BOOL DEFAULT 0, Scan_2D_Leveling BOOL DEFAULT 0, LITHO_CONFIG INTEGER DEFAULT 1000, Scan_Offset_val DOUBLE DEFAULT 2.2);";
	}
	else if(TableName == "FORCE_CONFIG"){
		 query = "CREATE TABLE FORCE_CONFIG(id INTEGER PRIMARY KEY ASC, Force_StartX_Val DOUBLE DEFAULT 0, Force_StartY_Val DOUBLE DEFAULT 0, Force_Z1_Val DOUBLE DEFAULT 0, Force_Z2_Val DOUBLE DEFAULT 0, Force_U1_Val DOUBLE DEFAULT 0, Force_U2_Val DOUBLE DEFAULT 0, Force_Delay_Val DOUBLE DEFAULT 10000, Force_Resolution_Index INTEGER DEFAULT 1, Force_Mode_Index INTEGER DEFAULT 1, TB_C_Factor DOUBLE DEFAULT 1, C_Factor_Set BOOL DEFAULT 0, K_Factor DOUBLE DEFAULT 0);";
	}
	else if(TableName == "KPFM_CONFIG"){
		 query = "CREATE TABLE KPFM_CONFIG(id INTEGER PRIMARY KEY ASC, Kpfm_Frequency_Val INTEGER DEFAULT 200000, Kpfm_DriveVoltage_Val INTEGER DEFAULT 0, Kpfm_Lia1_Val INTEGER DEFAULT 5012313, Kpfm_Ki_Val INTEGER DEFAULT 1, Kpfm_Kp_Val INTEGER DEFAULT 1, Kpfm_Kd_Val INTEGER DEFAULT 12313, Kpfm_Th_Val INTEGER DEFAULT 20);";
	}
	else if(TableName == "PARAMETERS"){
		 query = "CREATE TABLE PARAMETERS(id INTEGER PRIMARY KEY ASC, APR_Auto_Tune BOOL DEFAULT 0, Scan_leveling INTEGER DEFAULT 2, Scan_Pallet INTEGER DEFAULT 3, Apr_F_CON_FREQ_From INTEGER DEFAULT 50000, Apr_F_CON_FREQ_To INTEGER DEFAULT 150000, Apr_F_CON_DRV_Start INTEGER DEFAULT 10, Apr_F_CON_AMP_MIN INTEGER DEFAULT 70, Apr_F_CON_AMP_MAX INTEGER DEFAULT 80);";
	}
	else if(TableName == "HARDWARE_TYPE"){
		 query = "CREATE TABLE HARDWARE_TYPE(id INTEGER PRIMARY KEY ASC, HardWare_Scanner_Type INTEGER DEFAULT 0, Max_Range DOUBLE DEFAULT 28, last_IP TEXT DEFAULT '192.168.1.25' , LogToFile BOOL DEFAULT 1);";
	}
	else if(TableName == "Calibration"){
		query = "CREATE TABLE Calibration(id INTEGER PRIMARY KEY ASC, Range_um INTEGER DEFAULT 0, X_Range DOUBLE DEFAULT 0, Y_Range DOUBLE DEFAULT 0);";
	}
	return query;
}
//---------------------------------------------------------------------------

UnicodeString QueryClass::Insert(UnicodeString TableName, int id)
{
	if(TableName == "License"){
		query = "INSERT INTO License(id,TotalTime,WorkedTime,RemainedTime) VALUES(1,"+FloatToStr(LicTable.TotalTime)+","+FloatToStr(LicTable.WorkedTime)+","+FloatToStr(LicTable.RemainedTime)+");";
//		mainForm->LogToFile("query = " + query);
	}
	else if(TableName == "INFO_CONFIG"){
		query = "INSERT INTO INFO_CONFIG(id,url,tel) VALUES("+IntToStr(id)+"," + InfoTable.url+","+InfoTable.tel+");";
	}
	else if(TableName == "APPLICATION_CONFIG"){
		query = "INSERT INTO APPLICATION_CONFIG(id,App_LastMode_Val,osc) VALUES("+IntToStr(id)+","+IntToStr(ApplicationTable.App_LastMode_Val)+","+IntToStr(ApplicationTable.osc)+");";
	}
	else if(TableName == "UDP_CONFIG"){
		 query = "INSERT INTO UDP_CONFIG(id,local_port,remote_port,server,system,connection_try,record_time ) VALUES(1,"+IntToStr(UdpTable.local_port)+","+IntToStr(UdpTable.remote_port)+","+UdpTable.server+","+UdpTable.system+","+IntToStr(UdpTable.connection_try)+","+IntToStr(UdpTable.record_time)+");";
	}
	else if(TableName == "TCP_CONFIG"){
		 query = "INSERT INTO TCP_CONFIG(id,local_port,remote_port) VALUES("+IntToStr(id)+","+IntToStr(TcpTable.local_port)+","+IntToStr(TcpTable.remote_port)+");";
	}
	else if(TableName == "OSC_CHART_CONFIG"){
		 query = "INSERT INTO OSC_CHART_CONFIG(id,osc1,osc2,osc3,osc4,timedev,all_scale) VALUES("+IntToStr(id)+","+IntToStr(OscChartTable.osc1)+","+IntToStr(OscChartTable.osc2)+","+IntToStr(OscChartTable.osc3)+","+IntToStr(OscChartTable.osc4)+","+IntToStr(OscChartTable.timedev)+","+BoolToStr(OscChartTable.all_scale , true)+");";
	}
	else if(TableName == "OSC_CONFIG"){
		 query = "INSERT INTO OSC_CONFIG(id,name,_index,_offset,unit,scale) VALUES("+IntToStr(id)+","+OscTable[id].name+","+FloatToStr(OscTable[id].index)+","+FloatToStr(OscTable[id].offset)+","+OscTable[id].unit+","+IntToStr(OscTable[id].scale)+");";
	}
	else if(TableName == "APPROACH_CONFIG"){
		 query = "INSERT INTO APPROACH_CONFIG(id,Apr_Refrerence_Val,Apr_Ki_Val_Contact,Apr_Ki_Val_NonContact,Apr_Bias_Val,Apr_Kd_Val"
		 ",Apr_Kp_Val,Apr_KiFeedbak_Val_Contact,Apr_KiFeedbak_Val_NonContact,Apr_ZPosition_Val,Apr_SteperSpeed_Val_Precise,Apr_SteperStepMicro_Val_Precise"
		 ",Apr_StepperSpeed_Val_Fast,Apr_StepperStepMicro_Val_Fast,Apr_StepperStep_Val,Apr_ScanSpeed_Val,Apr_BiasIndex_Val,Apr_BiasOffset_Val)"
		 " VALUES("+IntToStr(id)+"," + IntToStr(ApproachTable.Apr_Refrerence_Val)+","+IntToStr(ApproachTable.Apr_Ki_Val_Contact)+","
		 +IntToStr(ApproachTable.Apr_Ki_Val_NonContact)+","+IntToStr(ApproachTable.Apr_Bias_Val)+","+IntToStr(ApproachTable.Apr_Kd_Val)
		 +","+IntToStr(ApproachTable.Apr_Kp_Val)+","+IntToStr(ApproachTable.Apr_KiFeedbak_Val_Contact)+","+IntToStr(ApproachTable.Apr_KiFeedbak_Val_NonContact)
		 +","+IntToStr(ApproachTable.Apr_ZPosition_Val)+","+IntToStr(ApproachTable.Apr_SteperSpeed_Val_Precise)
		 +","+IntToStr(ApproachTable.Apr_SteperStepMicro_Val_Precise)+","+IntToStr(ApproachTable.Apr_StepperSpeed_Val_Fast)
		 +","+IntToStr(ApproachTable.Apr_StepperStepMicro_Val_Fast)+","+IntToStr(ApproachTable.Apr_StepperStep_Val)
		 +","+IntToStr(ApproachTable.Apr_ScanSpeed_Val)+","+IntToStr(ApproachTable.Apr_BiasIndex_Val)+","+IntToStr(ApproachTable.Apr_BiasOffset_Val)+");";
	}
	else if(TableName == "FAST_APPROACH_DNC_CONFIG"){
		 query = "INSERT INTO FAST_APPROACH_DNC_CONFIG(id,Dnc_FrequencyFrom_Val,Dnc_FrequencyTo_Val,Threshold_Contact,Threshold_NonContact"
		 ",Min_Amp,Max_Amp,Drive_Start) VALUES("+IntToStr(id)+","+IntToStr(FastApproachTable.Dnc_FrequencyFrom_Val)+","+IntToStr(FastApproachTable.Dnc_FrequencyTo_Val)
		 +","+IntToStr(FastApproachTable.Threshold_Contact)+","+IntToStr(FastApproachTable.Threshold_NonContact)+","
		 +IntToStr(FastApproachTable.Min_Amp)+","+IntToStr(FastApproachTable.Max_Amp)+","+IntToStr(FastApproachTable.Drive_Start)+");";
	}
	else if(TableName == "COARSEMOVE_CONFIG"){
		 query = "INSERT INTO COARSEMOVE_CONFIG(id,Coarse_StepperSpeed_Val_Slow,Coarse_StepperSpeed_Val_Fast,Coarse_StepperStepMicro_Val)"
		 " VALUES("+IntToStr(id)+","+IntToStr(MoveTable.Coarse_StepperSpeed_Val_Slow)+","+IntToStr(MoveTable.Coarse_StepperSpeed_Val_Fast)+","+IntToStr(MoveTable.Coarse_StepperStepMicro_Val)+");";
	}
	else if(TableName == "RETRACT_CONFIG"){
		 query = "INSERT INTO RETRACT_CONFIG(id,Ret_OneStep_Val,Ret_StepperSpeed_Val,Ret_StepperStepMicro_Val)"
		 " VALUES("+IntToStr(id)+","+IntToStr(RetractTable.Ret_OneStep_Val)+","+IntToStr(RetractTable.Ret_StepperSpeed_Val)+","+IntToStr(RetractTable.Ret_StepperStepMicro_Val)+");";
	}
	else if(TableName == "STAGE_CONFIG"){
		 query = "INSERT INTO STAGE_CONFIG(id,Stage_StepperSpeed_Val_Slow,Stage_StepperSpeed_Val_Fast,Stage_StepperStepMicro_Val)"
		 " VALUES("+IntToStr(id)+","+IntToStr(StageTable.Stage_StepperSpeed_Val_Slow)+","+IntToStr(StageTable.Stage_StepperSpeed_Val_Fast)+","+IntToStr(StageTable.Stage_StepperStepMicro_Val)+");";
	}
	else if(TableName == "DNC_CONFIG"){
		 query = "INSERT INTO DNC_CONFIG(id,Dnc_FrequencyFromMin_Val,Dnc_FrequencyFrom_Val,Dnc_FrequencyToMax_Val,Dnc_FrequencyTo_Val,Dnc_FrequencyUse_Val,Dnc_DriveVoltage_Val"
		 ",Dnc_PointsCount_Val,Dnc_SetPointPercentage_Val,Dnc_TimeCnt_Val,Dnc_RollOff_Val,Dnc_DriveIndex_Val,Dnc_DriveOffset_Val,Dnc_Refrence_Val)"
		 " VALUES("+IntToStr(id)+","+IntToStr(DncTable.Dnc_FrequencyFromMin_Val)+","+IntToStr(DncTable.Dnc_FrequencyFrom_Val)+","+IntToStr(DncTable.Dnc_FrequencyToMax_Val)
		 +","+IntToStr(DncTable.Dnc_FrequencyTo_Val)+","+IntToStr(DncTable.Dnc_FrequencyUse_Val)+","+IntToStr(DncTable.Dnc_DriveVoltage_Val)
		 +","+IntToStr(DncTable.Dnc_PointsCount_Val)+","+IntToStr(DncTable.Dnc_SetPointPercentage_Val)+","+FloatToStr(DncTable.Dnc_TimeCnt_Val)
		 +","+IntToStr(DncTable.Dnc_RollOff_Val)+","+FloatToStr(DncTable.Dnc_DriveIndex_Val)+","+FloatToStr(DncTable.Dnc_DriveOffset_Val)+","+FloatToStr(DncTable.Dnc_Refrence_Val)+");";
	}
	else if(TableName == "SCAN_CONFIG"){
		 query = "INSERT INTO SCAN_CONFIG(id,Scan_Range_Val,Scan_X_Center_Val,Scan_Y_Center_Val,Scan_Speed_Val,Scan_Angle_Val,Scan_Resolution_Val"
		 ",Scan_OverScan_Val,Scan_1D_Leveling,Scan_2D_Leveling,LITHO_CONFIG,Scan_Offset_val) VALUES("+IntToStr(id)+","+FloatToStr(ScanTable.Scan_Range_Val)
		 +","+FloatToStr(ScanTable.Scan_X_Center_Val)+","+FloatToStr(ScanTable.Scan_Y_Center_Val)+","+FloatToStr(ScanTable.Scan_Speed_Val)
		 +","+IntToStr(ScanTable.Scan_Angle_Val)+","+IntToStr(ScanTable.Scan_Resolution_Val)+","+FloatToStr(ScanTable.Scan_OverScan_Val)
		 +","+BoolToStr(ScanTable.Scan_1D_Leveling,true)+","+BoolToStr(ScanTable.Scan_2D_Leveling,true)+","+IntToStr(ScanTable.LITHO_CONFIG)+","+FloatToStr(ScanTable.Scan_Offset_val)+");";
	}
	else if(TableName == "LITHO_CONFIG"){
		 query = "INSERT INTO LITHO_CONFIG(id,Litho_Delay) VALUES(1,"+IntToStr(LithoTable.Litho_Delay)+");";
	}
	else if(TableName == "FORCE_CONFIG"){
		 query = "INSERT INTO FORCE_CONFIG(id,Force_StartX_Val,Force_StartY_Val,Force_Z1_Val,Force_Z2_Val,Force_U1_Val,Force_U2_Val"
		 ",Force_Delay_Val,Force_Resolution_Index,Force_Mode_Index,TB_C_Factor,C_Factor_Set,K_Factor) VALUES("+IntToStr(id)+","+FloatToStr(ForceTable.Force_StartX_Val)+","
		 +FloatToStr(ForceTable.Force_StartY_Val)+","+FloatToStr(ForceTable.Force_Z1_Val)+","+FloatToStr(ForceTable.Force_Z2_Val)+","+FloatToStr(ForceTable.Force_U1_Val)+","
		 +FloatToStr(ForceTable.Force_U2_Val)+","+IntToStr(ForceTable.Force_Delay_Val)+","+IntToStr(ForceTable.Force_Resolution_Index)+","+IntToStr(ForceTable.Force_Mode_Index)+","
		 +FloatToStr(ForceTable.TB_C_Factor)+","+BoolToStr(ForceTable.C_Factor_Set,true)+","+FloatToStr(ForceTable.K_Factor)+");";
	}
	else if(TableName == "KPFM_CONFIG"){
		 query = "INSERT INTO KPFM_CONFIG(id,Kpfm_Frequency_Val,Kpfm_DriveVoltage_Val,Kpfm_Lia1_Val,Kpfm_Ki_Val,Kpfm_Kp_Val,Kpfm_Kd_Val,Kpfm_Th_Val)"
		 " VALUES("+IntToStr(id)+","+IntToStr(KpfmTable.Kpfm_Frequency_Val)+","+IntToStr(KpfmTable.Kpfm_DriveVoltage_Val)+","+IntToStr(KpfmTable.Kpfm_Lia1_Val)+","
		 +IntToStr(KpfmTable.Kpfm_Ki_Val)+","+IntToStr(KpfmTable.Kpfm_Kp_Val)+","+IntToStr(KpfmTable.Kpfm_Kd_Val)+","+IntToStr(KpfmTable.Kpfm_Th_Val)+");";
	}
    else if(TableName == "PARAMETERS"){
		 query = "INSERT INTO PARAMETERS(id,APR_Auto_Tune,Scan_leveling,Scan_Pallet,Apr_F_CON_FREQ_From,Apr_F_CON_FREQ_To,Apr_F_CON_DRV_Start,Apr_F_CON_AMP_MIN,Apr_F_CON_AMP_MAX)"
		 " VALUES("+IntToStr(id)+","+BoolToStr(ParametersTable.APR_Auto_Tune,true)+","+IntToStr(ParametersTable.Scan_leveling)+","+IntToStr(ParametersTable.Scan_Pallet)+","
		 +IntToStr(ParametersTable.Apr_F_CON_FREQ_From)+","+IntToStr(ParametersTable.Apr_F_CON_FREQ_To)+","+IntToStr(ParametersTable.Apr_F_CON_DRV_Start)+","
		 +IntToStr(ParametersTable.Apr_F_CON_AMP_MIN)+","+IntToStr(ParametersTable.Apr_F_CON_AMP_MAX)+");";
	}
    else if(TableName == "HARDWARE_TYPE"){
		 query = "INSERT INTO HARDWARE_TYPE(id,HardWare_Scanner_Type,Max_Range,last_IP,LogToFile) VALUES(1,"+IntToStr(HardwareTable.HardWare_Scanner_Type)+","
		 +FloatToStr(HardwareTable.Max_Range)+","+HardwareTable.last_IP+","+BoolToStr(HardwareTable.LogToFile , true)+");";
	}
	else if(TableName == "Calibration"){
		query = "INSERT INTO Calibration(id,Range_um,X_Range,Y_Range) VALUES("+IntToStr(id)+","+IntToStr(ColibrationTable[id].Range_um)+","+FloatToStr(ColibrationTable[id].X_Range)+","+FloatToStr(ColibrationTable[id].Y_Range)+");";
	}

	return query;
}
//---------------------------------------------------------------------------

UnicodeString QueryClass::Update(UnicodeString TableName, int id)
{
	if(TableName == "License"){
		query = "UPDATE License SET (id,TotalTime,WorkedTime,RemainedTime) = (1,"+FloatToStr(LicTable.TotalTime)+","+FloatToStr(LicTable.WorkedTime)+","+FloatToStr(LicTable.RemainedTime)+") WHERE ID = 1;";
//		mainForm->LogToFile("query = " + query);
	}
	else if(TableName == "INFO_CONFIG"){
		query = "UPDATE INFO_CONFIG SET (id,url,tel) = (1,'"+ InfoTable.url+"'"+","+"'"+InfoTable.tel+"'"+");";
	}
	else if(TableName == "APPLICATION_CONFIG"){
		query = "UPDATE APPLICATION_CONFIG SET (id,App_LastMode_Val,osc) = (1,"+IntToStr(ApplicationTable.App_LastMode_Val)+","+IntToStr(ApplicationTable.osc)+")WHERE ID = 1;";
	}
	else if(TableName == "UDP_CONFIG"){
		 query = "UPDATE UDP_CONFIG SET (id,local_port,remote_port,server,system,connection_try,record_time ) = (1,"+IntToStr(UdpTable.local_port)+","+IntToStr(UdpTable.remote_port)+","+UdpTable.server+","+UdpTable.system+","+IntToStr(UdpTable.connection_try)+","+IntToStr(UdpTable.record_time)+")WHERE ID = 1;";
	}
	else if(TableName == "TCP_CONFIG"){
		 query = "UPDATE TCP_CONFIG SET (id,local_port,remote_port) = (1,"+IntToStr(TcpTable.local_port)+","+IntToStr(TcpTable.remote_port)+")WHERE ID = 1;";
	}
	else if(TableName == "OSC_CHART_CONFIG"){
		 query = "UPDATE OSC_CHART_CONFIG SET (id,osc1,osc2,osc3,osc4,timedev,all_scale) = (1,"+IntToStr(OscChartTable.osc1)+","+IntToStr(OscChartTable.osc2)+","+IntToStr(OscChartTable.osc3)+","+IntToStr(OscChartTable.osc4)+","+IntToStr(OscChartTable.timedev)+","+BoolToStr(OscChartTable.all_scale,true)+")WHERE ID = 1;";
	}
	else if(TableName == "OSC_CONFIG"){
		 query = "UPDATE OSC_CONFIG SET(id,name,_index,_offset,unit,scale) = ("+IntToStr(OscTable[id].id)+","+"'"+OscTable[id].name+"'"+","+FloatToStr(OscTable[id].index)+","+FloatToStr(OscTable[id].offset)+","+"'"+OscTable[id].unit+"'"+","+IntToStr(OscTable[id].scale)+")WHERE ID = "+ IntToStr(id)+";";
		 mainForm->LogToFile("query = " + query);
	}
	else if(TableName == "APPROACH_CONFIG"){
		 query = "UPDATE APPROACH_CONFIG SET (id,Apr_Refrerence_Val,Apr_Ki_Val_Contact,Apr_Ki_Val_NonContact,Apr_Bias_Val,Apr_Kd_Val"
		 ",Apr_Kp_Val,Apr_KiFeedbak_Val_Contact,Apr_KiFeedbak_Val_NonContact,Apr_ZPosition_Val,Apr_SteperSpeed_Val_Precise,Apr_SteperStepMicro_Val_Precise"
		 ",Apr_StepperSpeed_Val_Fast,Apr_StepperStepMicro_Val_Fast,Apr_StepperStep_Val,Apr_ScanSpeed_Val,Apr_BiasIndex_Val,Apr_BiasOffset_Val)"
		 " = (1," + IntToStr(ApproachTable.Apr_Refrerence_Val)+","+IntToStr(ApproachTable.Apr_Ki_Val_Contact)+","
		 +IntToStr(ApproachTable.Apr_Ki_Val_NonContact)+","+IntToStr(ApproachTable.Apr_Bias_Val)+","+IntToStr(ApproachTable.Apr_Kd_Val)
		 +","+IntToStr(ApproachTable.Apr_Kp_Val)+","+IntToStr(ApproachTable.Apr_KiFeedbak_Val_Contact)+","+IntToStr(ApproachTable.Apr_KiFeedbak_Val_NonContact)
		 +","+IntToStr(ApproachTable.Apr_ZPosition_Val)+","+IntToStr(ApproachTable.Apr_SteperSpeed_Val_Precise)
		 +","+IntToStr(ApproachTable.Apr_SteperStepMicro_Val_Precise)+","+IntToStr(ApproachTable.Apr_StepperSpeed_Val_Fast)
		 +","+IntToStr(ApproachTable.Apr_StepperStepMicro_Val_Fast)+","+IntToStr(ApproachTable.Apr_StepperStep_Val)
		 +","+IntToStr(ApproachTable.Apr_ScanSpeed_Val)+","+IntToStr(ApproachTable.Apr_BiasIndex_Val)+","+IntToStr(ApproachTable.Apr_BiasOffset_Val)+")WHERE ID = 1;";
	}
	else if(TableName == "FAST_APPROACH_DNC_CONFIG"){
		 query = "UPDATE FAST_APPROACH_DNC_CONFIG SET (id,Dnc_FrequencyFrom_Val,Dnc_FrequencyTo_Val,Threshold_Contact,Threshold_NonContact"
		 ",Min_Amp,Max_Amp,Drive_Start) = (1,"+IntToStr(FastApproachTable.Dnc_FrequencyFrom_Val)+","+IntToStr(FastApproachTable.Dnc_FrequencyTo_Val)
		 +","+IntToStr(FastApproachTable.Threshold_Contact)+","+IntToStr(FastApproachTable.Threshold_NonContact)+","
		 +IntToStr(FastApproachTable.Min_Amp)+","+IntToStr(FastApproachTable.Max_Amp)+","+IntToStr(FastApproachTable.Drive_Start)+")WHERE ID = 1;";
	}
	else if(TableName == "COARSEMOVE_CONFIG"){
		 query = "UPDATE COARSEMOVE_CONFIG SET (id,Coarse_StepperSpeed_Val_Slow,Coarse_StepperSpeed_Val_Fast,Coarse_StepperStepMicro_Val)"
		 " = (1,"+IntToStr(MoveTable.Coarse_StepperSpeed_Val_Slow)+","+IntToStr(MoveTable.Coarse_StepperSpeed_Val_Fast)+","+IntToStr(MoveTable.Coarse_StepperStepMicro_Val)+")WHERE ID = 1;";
	}
	else if(TableName == "RETRACT_CONFIG"){
		 query = "UPDATE RETRACT_CONFIG SET (id,Ret_OneStep_Val,Ret_StepperSpeed_Val,Ret_StepperStepMicro_Val)"
		 " = (1,"+IntToStr(RetractTable.Ret_OneStep_Val)+","+IntToStr(RetractTable.Ret_StepperSpeed_Val)+","+IntToStr(RetractTable.Ret_StepperStepMicro_Val)+")WHERE ID = 1;";
	}
	else if(TableName == "STAGE_CONFIG"){
		 query = "UPDATE STAGE_CONFIG SET (id,Stage_StepperSpeed_Val_Slow,Stage_StepperSpeed_Val_Fast,Stage_StepperStepMicro_Val)"
		 " = (1,"+IntToStr(StageTable.Stage_StepperSpeed_Val_Slow)+","+IntToStr(StageTable.Stage_StepperSpeed_Val_Fast)+","+IntToStr(StageTable.Stage_StepperStepMicro_Val)+")WHERE ID = 1;";
	}
	else if(TableName == "DNC_CONFIG"){
		 query = "UPDATE DNC_CONFIG SET (id,Dnc_FrequencyFromMin_Val,Dnc_FrequencyFrom_Val,Dnc_FrequencyToMax_Val,Dnc_FrequencyTo_Val,Dnc_FrequencyUse_Val,Dnc_DriveVoltage_Val"
		 ",Dnc_PointsCount_Val,Dnc_SetPointPercentage_Val,Dnc_TimeCnt_Val,Dnc_RollOff_Val,Dnc_DriveIndex_Val,Dnc_DriveOffset_Val,Dnc_Refrence_Val)"
		 " = (1,"+IntToStr(DncTable.Dnc_FrequencyFromMin_Val)+","+IntToStr(DncTable.Dnc_FrequencyFrom_Val)+","+IntToStr(DncTable.Dnc_FrequencyToMax_Val)
		 +","+IntToStr(DncTable.Dnc_FrequencyTo_Val)+","+IntToStr(DncTable.Dnc_FrequencyUse_Val)+","+IntToStr(DncTable.Dnc_DriveVoltage_Val)
		 +","+IntToStr(DncTable.Dnc_PointsCount_Val)+","+IntToStr(DncTable.Dnc_SetPointPercentage_Val)+","+FloatToStr(DncTable.Dnc_TimeCnt_Val)
		 +","+IntToStr(DncTable.Dnc_RollOff_Val)+","+FloatToStr(DncTable.Dnc_DriveIndex_Val)+","+FloatToStr(DncTable.Dnc_DriveOffset_Val)+","+FloatToStr(DncTable.Dnc_Refrence_Val)+")WHERE ID = 1;";
	}
	else if(TableName == "SCAN_CONFIG"){
		 query = "UPDATE SCAN_CONFIG SET (id,Scan_Range_Val,Scan_X_Center_Val,Scan_Y_Center_Val,Scan_Speed_Val,Scan_Angle_Val,Scan_Resolution_Val"
		 ",Scan_OverScan_Val,Scan_1D_Leveling,Scan_2D_Leveling,LITHO_CONFIG,Scan_Offset_val) = (1,"+FloatToStr(ScanTable.Scan_Range_Val)
		 +","+FloatToStr(ScanTable.Scan_X_Center_Val)+","+FloatToStr(ScanTable.Scan_Y_Center_Val)+","+FloatToStr(ScanTable.Scan_Speed_Val)
		 +","+IntToStr(ScanTable.Scan_Angle_Val)+","+IntToStr(ScanTable.Scan_Resolution_Val)+","+FloatToStr(ScanTable.Scan_OverScan_Val)
		 +","+BoolToStr(ScanTable.Scan_1D_Leveling,true)+","+BoolToStr(ScanTable.Scan_2D_Leveling,true)+","+IntToStr(ScanTable.LITHO_CONFIG)+","+FloatToStr(ScanTable.Scan_Offset_val)+")WHERE ID = 1;";
	}
	else if(TableName == "LITHO_CONFIG"){
		 query = "UPDATE LITHO_CONFIG SET(id,Litho_Delay)  = (1,"+IntToStr(LithoTable.Litho_Delay)+")WHERE ID = 1;";
	}
	else if(TableName == "FORCE_CONFIG"){
		 query = "UPDATE FORCE_CONFIG SET (id,Force_StartX_Val,Force_StartY_Val,Force_Z1_Val,Force_Z2_Val,Force_U1_Val,Force_U2_Val"
		 ",Force_Delay_Val,Force_Resolution_Index,Force_Mode_Index,TB_C_Factor,C_Factor_Set,K_Factor) = (1,"+FloatToStr(ForceTable.Force_StartX_Val)+","
		 +FloatToStr(ForceTable.Force_StartY_Val)+","+FloatToStr(ForceTable.Force_Z1_Val)+","+FloatToStr(ForceTable.Force_Z2_Val)+","+FloatToStr(ForceTable.Force_U1_Val)+","
		 +FloatToStr(ForceTable.Force_U2_Val)+","+IntToStr(ForceTable.Force_Delay_Val)+","+IntToStr(ForceTable.Force_Resolution_Index)+","+IntToStr(ForceTable.Force_Mode_Index)+","
		 +FloatToStr(ForceTable.TB_C_Factor)+","+BoolToStr(ForceTable.C_Factor_Set,true)+","+FloatToStr(ForceTable.K_Factor)+")WHERE ID = 1;";
	}
	else if(TableName == "KPFM_CONFIG"){
		 query = "UPDATE KPFM_CONFIG SET (id,Kpfm_Frequency_Val,Kpfm_DriveVoltage_Val,Kpfm_Lia1_Val,Kpfm_Ki_Val,Kpfm_Kp_Val,Kpfm_Kd_Val,Kpfm_Th_Val)"
		 " = (1,"+IntToStr(KpfmTable.Kpfm_Frequency_Val)+","+IntToStr(KpfmTable.Kpfm_DriveVoltage_Val)+","+IntToStr(KpfmTable.Kpfm_Lia1_Val)+","
		 +IntToStr(KpfmTable.Kpfm_Ki_Val)+","+IntToStr(KpfmTable.Kpfm_Kp_Val)+","+IntToStr(KpfmTable.Kpfm_Kd_Val)+","+IntToStr(KpfmTable.Kpfm_Th_Val)+")WHERE ID = 1;";
	}
	else if(TableName == "PARAMETERS"){
		 query = "UPDATE PARAMETERS SET (id,APR_Auto_Tune,Scan_leveling,Scan_Pallet,Apr_F_CON_FREQ_From,Apr_F_CON_FREQ_To,Apr_F_CON_DRV_Start,Apr_F_CON_AMP_MIN,Apr_F_CON_AMP_MAX)"
		 " = (1,"+BoolToStr(ParametersTable.APR_Auto_Tune,true)+","+IntToStr(ParametersTable.Scan_leveling)+","+IntToStr(ParametersTable.Scan_Pallet)+","
		 +IntToStr(ParametersTable.Apr_F_CON_FREQ_From)+","+IntToStr(ParametersTable.Apr_F_CON_FREQ_To)+","+IntToStr(ParametersTable.Apr_F_CON_DRV_Start)+","
		 +IntToStr(ParametersTable.Apr_F_CON_AMP_MIN)+","+IntToStr(ParametersTable.Apr_F_CON_AMP_MAX)+");";
	}
	else if(TableName == "HARDWARE_TYPE"){
		 query = "UPDATE HARDWARE_TYPE SET (id,HardWare_Scanner_Type,Max_Range,last_IP,LogToFile) = (1,"+IntToStr(HardwareTable.HardWare_Scanner_Type)+","
		 +FloatToStr(HardwareTable.Max_Range)+","+"'"+HardwareTable.last_IP+"'"+","+BoolToStr(HardwareTable.LogToFile,true)+")WHERE ID = 1;";

	}
	else if(TableName == "Calibration"){
		query = "UPDATE Calibration SET(id,Range_um,X_Range,Y_Range) = ("+IntToStr(ColibrationTable[id].id)+","+IntToStr(ColibrationTable[id].Range_um)+","+FloatToStr(ColibrationTable[id].X_Range)+","+FloatToStr(ColibrationTable[id].Y_Range)+")WHERE ID = "+ IntToStr(id)+";";
	}
//	mainForm->LogToFile("query = " + query);
	return query;
}
//---------------------------------------------------------------------------

UnicodeString QueryClass::Select(UnicodeString TableName, int id)
{
	query = "SELECT * FROM " + TableName + " WHERE ID = " + IntToStr(id)+";";
//	mainForm->LogToFile("query = " + query);
	return query;
}
