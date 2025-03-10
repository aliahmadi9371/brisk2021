//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#pragma hdrstop

#include "DataBase.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

void DataBaseClass::CreateObjects(){

	dbConnection = new TSQLConnection(NULL);
	dbSqlQuery = new TSQLQuery(NULL);
	myQuery = new QueryClass;



//	dbConnection->KeepConnection = true;
	dbConnection->DriverName = "Sqlite";
	dbConnection->Params->Add("Database="+DataBasePath);
	dbConnection->LoginPrompt = false;

	dbSqlQuery->SQLConnection = dbConnection;




}
//---------------------------------------------------------------------------

bool DataBaseClass::Execute(UnicodeString query)
{
	try{
		dbSqlQuery->SQL->Text = query;
		dbSqlQuery->ExecSQL(true);
//		mainForm->LogToFile("DataBaseClass : DataBase Message Executed");
		return true;
	}
	catch(Exception& E){
		mainForm->LogToFile(E.Message);
		return false;
	}

}
//---------------------------------------------------------------------------
void DataBaseClass::SelectExecute(UnicodeString query ,UnicodeString TableName, int id)
{
	try{
		dbSqlQuery->SQL->Text = query;
		dbSqlQuery->Active = true;
//		mainForm->LogToFile("FieldCount = " + IntToStr(dbSqlQuery->FieldCount));
//		mainForm->LogToFile("DataBaseClass : DataBase Message SelectExecuted");
	}
	catch(Exception& E){
		mainForm->LogToFile(E.Message);
	}
	ShowSelectResults(TableName , id);
}
//---------------------------------------------------------------------------

void DataBaseClass::Connect()
{
	dbConnection->Connected = true;
	mainForm->LogToFile("DataBaseClass : DataBase Connected");

}
//---------------------------------------------------------------------------

void DataBaseClass::Disconnect(){
	dbConnection->Connected = false;
	mainForm->LogToFile("DataBaseClass : DataBase Disconnected");
}
//---------------------------------------------------------------------------

void DataBaseClass::CreateTables(){
	if(dbConnection->Connected){
		if(Execute(myQuery->CreateTable("License"))){
			LicTable.id = 1;
			LicTable.TotalTime = 864000;
			LicTable.RemainedTime = 0;
			LicTable.WorkedTime = 864000;
			Execute(myQuery->Insert("License"));
//			mainForm->LogToFile("DataBaseClass: License Table Created");
		}
		if(Execute(myQuery->CreateTable("INFO_CONFIG"))){
			InfoTable.id = 1;
			InfoTable.url = "'afm-nanoscope.com'";
			InfoTable.tel = "'021-76251051'";
			Execute(myQuery->Insert("INFO_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: INFO_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("APPLICATION_CONFIG"))){
			ApplicationTable.id = 1;
			ApplicationTable.App_LastMode_Val = 1;
			ApplicationTable.osc = 1;
			Execute(myQuery->Insert("APPLICATION_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: APPLICATION_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("UDP_CONFIG"))){
			UdpTable.id = 1;
			UdpTable.local_port = 9023;
			UdpTable.remote_port = 5560;
			UdpTable.server = "'afm_server'";
			UdpTable.system = "'afm_system'";
			UdpTable.connection_try = 10;
			UdpTable.record_time = 50;
			Execute(myQuery->Insert("UDP_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: UDP_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("TCP_CONFIG"))){
			TcpTable.id = 1;
			TcpTable.local_port = 194;
            TcpTable.remote_port = 8116;
			Execute(myQuery->Insert("TCP_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: TCP_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("OSC_CHART_CONFIG"))){
			OscChartTable.id = 1;
			OscChartTable.osc1 = 5;
			OscChartTable.osc2 = 26;
			OscChartTable.osc3 = 4;
			OscChartTable.osc4 = 0;
			OscChartTable.timedev = 3;
			OscChartTable.all_scale = true;
			Execute(myQuery->Insert("OSC_CHART_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: OSC_CHART_CONFIG Table Created");
		}

		if(Execute(myQuery->CreateTable("OSC_CONFIG"))){
            for(int i = 0; i<27; i++){
				if(i==0){
					OscTable[i].id = i;
					OscTable[i].name = "'TB'";
					OscTable[i].index = 0.000001372 ;
					OscTable[i].offset = 0;
					OscTable[i].unit = "'V'";
					OscTable[i].scale = 1;
				}
				else if(i==1){
					OscTable[i].id = i;
					OscTable[i].name = "'LR'";
					OscTable[i].index = 0.000001372;
					OscTable[i].offset = 0;
					OscTable[i].unit = "'V'";
					OscTable[i].scale = 1;
				}
				else if(i==2){
					OscTable[i].id = i;
					OscTable[i].name = "'SUM'";
					OscTable[i].index = -0.000001372;
					OscTable[i].offset = 0;
					OscTable[i].unit = "'V'";
					OscTable[i].scale = 1;
				}
				else if(i==3){
                    OscTable[i].id = i;
					OscTable[i].name = "'PIEZO_Z_STATE'";
					OscTable[i].index = 0.00000000000027425;
					OscTable[i].offset = 0.0000023;
					OscTable[i].unit = "'m'";
					OscTable[i].scale = 2;
				}
				else if(i==4){
                    OscTable[i].id = i;
					OscTable[i].name = "'PIEZO_Y_STATE'";
					OscTable[i].index = 0.0000000000018;
					OscTable[i].offset = 0.0000000000000000000003;
					OscTable[i].unit = "'m'";
					OscTable[i].scale = 2;
				}
				else if(i==5){
                    OscTable[i].id = i;
					OscTable[i].name = "'PIEZO_X_STATE'";
					OscTable[i].index = -0.0000000000019;
					OscTable[i].offset = 0.00000000000000000000002;
					OscTable[i].unit = "'m'";
					OscTable[i].scale = 2;
				}
				else if(i==6){
                    OscTable[i].id = i;
					OscTable[i].name = "'AMP'";
					OscTable[i].index = 0.0000001460;
					OscTable[i].offset = 0;
					OscTable[i].unit = "'V'";
					OscTable[i].scale = 0;
				}
				else if(i==7){
                    OscTable[i].id = i;
					OscTable[i].name = "'PHASE'";
					OscTable[i].index = 0.0000001460;
					OscTable[i].offset = 0;
					OscTable[i].unit = "'�'";
					OscTable[i].scale = 0;
				}
				else if(i==8){
                    OscTable[i].id = i;
					OscTable[i].name = "'CAFM'";
					OscTable[i].index = 0.000001372;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==9){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA1_X'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==10){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA1_Y'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==11){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA2_X'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==12){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA2_Y'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==13){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA1_AMP'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==14){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA1_PHASE'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==15){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA2_AMP'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==16){
                    OscTable[i].id = i;
					OscTable[i].name = "'KPFM_LIA2_PHASE'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==17){
                    OscTable[i].id = i;
					OscTable[i].name = "'BIAS'";
					OscTable[i].index = 0.000001149425287;
					OscTable[i].offset = 0.0804597701149;
					OscTable[i].unit = "'V'";
					OscTable[i].scale = 0;
				}
				else if(i==18){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX1_OUPUT'";
					OscTable[i].index = 0.000001372;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==19){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX2_OUPUT'";
					OscTable[i].index = 0.000001372;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==20){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX3_OUPUT'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==21){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX4_OUPUT'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==22){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX1_INPUT'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==23){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX2_INPUT'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==24){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX3_INPUT'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==25){
                    OscTable[i].id = i;
					OscTable[i].name = "'AUX4_INPUT'";
					OscTable[i].index = 1;
					OscTable[i].offset = 0;
					OscTable[i].unit = "''";
					OscTable[i].scale = 0;
				}
				else if(i==26){
                    OscTable[i].id = i;
					OscTable[i].name = "'TOPO'";
					OscTable[i].index = 0.00000000000027425;
					OscTable[i].offset = 0;
					OscTable[i].unit = "'m'";
					OscTable[i].scale = 2;
				}
				Execute(myQuery->Insert("OSC_CONFIG" , i));
			}
//			mainForm->LogToFile("DataBaseClass: OSC_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("APPROACH_CONFIG"))){
			ApproachTable.id = 1;
			ApproachTable.Apr_Refrerence_Val = 80;
			ApproachTable.Apr_Ki_Val_Contact = 50000;
			ApproachTable.Apr_Ki_Val_NonContact = 70000;
			ApproachTable.Apr_Bias_Val = 0;
			ApproachTable.Apr_Kd_Val = 0;
			ApproachTable.Apr_Kp_Val = 0;
			ApproachTable.Apr_KiFeedbak_Val_Contact = 300000;
			ApproachTable.Apr_KiFeedbak_Val_NonContact = 300000;
			ApproachTable.Apr_ZPosition_Val = -8388608;
			ApproachTable.Apr_SteperSpeed_Val_Precise = 200000;
			ApproachTable.Apr_SteperStepMicro_Val_Precise = 3;
			ApproachTable.Apr_StepperSpeed_Val_Fast = 1500000;
			ApproachTable.Apr_StepperStepMicro_Val_Fast = 3;
			ApproachTable.Apr_StepperStep_Val = 1;
			ApproachTable.Apr_ScanSpeed_Val = 1;
			ApproachTable.Apr_BiasIndex_Val = 870;
			ApproachTable.Apr_BiasOffset_Val = -70000;
			Execute(myQuery->Insert("APPROACH_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: APPROACH_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("FAST_APPROACH_DNC_CONFIG"))){
			FastApproachTable.id = 1;
			FastApproachTable.Dnc_FrequencyFrom_Val = 10000;
			FastApproachTable.Dnc_FrequencyTo_Val = 500000;
			FastApproachTable.Threshold_Contact = 7000;
			FastApproachTable.Threshold_NonContact = 2500;
			FastApproachTable.Min_Amp = 170;
			FastApproachTable.Max_Amp = 180;
			FastApproachTable.Drive_Start = 100;
			Execute(myQuery->Insert("FAST_APPROACH_DNC_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: FAST_APPROACH_DNC_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("COARSEMOVE_CONFIG"))){
			MoveTable.id = 1;
			MoveTable.Coarse_StepperSpeed_Val_Slow = 1000000;
			MoveTable.Coarse_StepperSpeed_Val_Fast = 100000;
			MoveTable.Coarse_StepperStepMicro_Val = 3;
			Execute(myQuery->Insert("COARSEMOVE_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: COARSEMOVE_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("RETRACT_CONFIG"))){
			RetractTable.id = 1;
			RetractTable.Ret_OneStep_Val = 2;
			RetractTable.Ret_StepperSpeed_Val = 200000;
			RetractTable.Ret_StepperStepMicro_Val = 3;
			Execute(myQuery->Insert("RETRACT_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: RETRACT_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("STAGE_CONFIG"))){
			StageTable.id = 1;
			StageTable.Stage_StepperSpeed_Val_Slow = 500000;
			StageTable.Stage_StepperSpeed_Val_Fast = 100000;
			StageTable.Stage_StepperStepMicro_Val = 3;
			Execute(myQuery->Insert("STAGE_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: STAGE_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("DNC_CONFIG"))){
			DncTable.id = 1;
			DncTable.Dnc_FrequencyFromMin_Val = 10000;
			DncTable.Dnc_FrequencyFrom_Val = 10000;
			DncTable.Dnc_FrequencyToMax_Val = 500000;
			DncTable.Dnc_FrequencyTo_Val = 500000;
			DncTable.Dnc_FrequencyUse_Val = 100000;
			DncTable.Dnc_DriveVoltage_Val = 130;
			DncTable.Dnc_PointsCount_Val = 1024;
			DncTable.Dnc_SetPointPercentage_Val = 60;
			DncTable.Dnc_TimeCnt_Val = 0;
			DncTable.Dnc_RollOff_Val = 0;
			DncTable.Dnc_DriveIndex_Val = 1.35;
			DncTable.Dnc_DriveOffset_Val = 0;
			DncTable.Dnc_Refrence_Val = 0.165638881023259;
			Execute(myQuery->Insert("DNC_CONFIG"));
			mainForm->LogToFile("DataBaseClass: DNC_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("SCAN_CONFIG"))){
			ScanTable.id = 1;
			ScanTable.Scan_Range_Val = 10;
			ScanTable.Scan_X_Center_Val = 0;
			ScanTable.Scan_Y_Center_Val = 0;
			ScanTable.Scan_Speed_Val = 1;
			ScanTable.Scan_Angle_Val = 0;
			ScanTable.Scan_Resolution_Val = 64;
			ScanTable.Scan_OverScan_Val = 12;
			ScanTable.Scan_1D_Leveling = false;
			ScanTable.Scan_2D_Leveling = false;
			ScanTable.LITHO_CONFIG = 1000;
			ScanTable.Scan_Offset_val = 2.2;
			Execute(myQuery->Insert("SCAN_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: SCAN_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("LITHO_CONFIG"))){
			LithoTable.id = 1;
			LithoTable.Litho_Delay = 100;
			Execute(myQuery->Insert("LITHO_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: LITHO_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("FORCE_CONFIG"))){
			ForceTable.id = 1;
			ForceTable.Force_StartX_Val = 0;
			ForceTable.Force_StartY_Val = 0;
			ForceTable.Force_Z1_Val = 0;
			ForceTable.Force_Z2_Val = 0;
			ForceTable.Force_U1_Val = 0;
			ForceTable.Force_U2_Val = 0;
			ForceTable.Force_Delay_Val = 10000;
			ForceTable.Force_Resolution_Index = 1;
			ForceTable.Force_Mode_Index = 0;
			ForceTable.TB_C_Factor = 1;
			ForceTable.C_Factor_Set = false;
			ForceTable.K_Factor = 0.2;
			Execute(myQuery->Insert("FORCE_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: FORCE_CONFIG Table Created");
		}
		if(Execute(myQuery->CreateTable("KPFM_CONFIG"))){
			KpfmTable.id = 1;
			KpfmTable.Kpfm_Frequency_Val = 200000;
			KpfmTable.Kpfm_DriveVoltage_Val = 1500;
			KpfmTable.Kpfm_Lia1_Val = 5012313;
			KpfmTable.Kpfm_Ki_Val = 1;
			KpfmTable.Kpfm_Kp_Val = 1;
			KpfmTable.Kpfm_Kd_Val = 12313;
			KpfmTable.Kpfm_Th_Val = 20;
			Execute(myQuery->Insert("KPFM_CONFIG"));
//			mainForm->LogToFile("DataBaseClass: KPFM_CONFIG Table Created");
		}
//		if(Execute(myQuery->CreateTable("PARAMETERS"))){
//			ParametersTable.id = 1;
//			ParametersTable.APR_Auto_Tune = false;
//			ParametersTable.Scan_leveling = 2;
//			ParametersTable.Scan_Pallet = 3;
//			ParametersTable.Apr_F_CON_FREQ_From = 50000;
//			ParametersTable.Apr_F_CON_FREQ_To = 150000;
//			ParametersTable.Apr_F_CON_DRV_Start = 10;
//			ParametersTable.Apr_F_CON_AMP_MIN = 70;
//			ParametersTable.Apr_F_CON_AMP_MAX = 80;
//			Execute(myQuery->Insert("PARAMETERS"));
//			mainForm->LogToFile("DataBaseClass: PARAMETERS Table Created");
//		}
		if(Execute(myQuery->CreateTable("HARDWARE_TYPE"))){
			HardwareTable.id = 1;
			HardwareTable.HardWare_Scanner_Type = 0;
			HardwareTable.Max_Range = 30;
			HardwareTable.last_IP = "'0.0.0.0'";
			HardwareTable.LogToFile = true;
			Execute(myQuery->Insert("HARDWARE_TYPE"));
//			mainForm->LogToFile("DataBaseClass: HARDWARE_TYPE Table Created");
		}
		if(Execute(myQuery->CreateTable("Calibration"))){
			for(int i = 0; i<56; i++){
				if(i==0){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 0 ;
					ColibrationTable[i].Y_Range = 0;

				}
				else if(i==1){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 4.75407;
					ColibrationTable[i].Y_Range = 4.0961;
				}
				else if(i==2){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 7.74996;
					ColibrationTable[i].Y_Range = 7.8043;
				}
				else if(i==3){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 10.74809;
					ColibrationTable[i].Y_Range = 11.4031;
				}
				else if(i==4){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 13.74828;
					ColibrationTable[i].Y_Range = 14.8997;
				}
				else if(i==5){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 16.75035;
					ColibrationTable[i].Y_Range = 18.3013;
				}
				else if(i==6){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 19.75412;
					ColibrationTable[i].Y_Range = 21.6151;
				}
				else if(i==7){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 22.75941;
					ColibrationTable[i].Y_Range = 24.8483;
				}
				else if(i==8){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 25.76604;
					ColibrationTable[i].Y_Range = 28.0081;
				}
				else if(i==9){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 28.77383;
					ColibrationTable[i].Y_Range = 31.1017;
				}
				else if(i==10){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i;
					ColibrationTable[i].X_Range = 31.7826;
					ColibrationTable[i].Y_Range = 34.1363;
				}
				else if(i==11){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 37.80236;
					ColibrationTable[i].Y_Range = 40.0573;
				}
				else if(i==12){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 43.82388;
					ColibrationTable[i].Y_Range = 45.8287;
				}
				else if(i==13){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 49.84572;
					ColibrationTable[i].Y_Range = 51.5081;
				}
				else if(i==14){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 55.86644;
					ColibrationTable[i].Y_Range = 57.1531;
				}
				else if(i==15){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 61.8846;
					ColibrationTable[i].Y_Range = 62.8213;
				}
				else if(i==16){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 67.89876;
					ColibrationTable[i].Y_Range = 68.5703;
				}
				else if(i==17){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 73.90748;
					ColibrationTable[i].Y_Range = 74.4577;
				}
				else if(i==18){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 79.90932;
					ColibrationTable[i].Y_Range = 80.5411;
				}
				else if(i==19){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 85.90284;
					ColibrationTable[i].Y_Range = 86.8781;
				}
				else if(i==20){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 91.6728;
					ColibrationTable[i].Y_Range = 92.8982;
				}
				else if(i==21){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 43.13572;
					ColibrationTable[i].Y_Range = 47.50868;
				}
				else if(i==22){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 45.58536;
					ColibrationTable[i].Y_Range = 50.09404;
				}
				else if(i==23){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 48.02364;
					ColibrationTable[i].Y_Range = 52.65716;
				}
				else if(i==24){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 50.45248;
					ColibrationTable[i].Y_Range = 55.20092;
				}
				else if(i==25){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 52.8738;
					ColibrationTable[i].Y_Range = 57.7282;
				}
				else if(i==26){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 55.28952;
					ColibrationTable[i].Y_Range = 60.24188;
				}
				else if(i==27){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 57.70156;
					ColibrationTable[i].Y_Range = 62.74484;
				}
				else if(i==28){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 60.11184;
					ColibrationTable[i].Y_Range = 65.23996;
				}
				else if(i==29){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 62.52228;
					ColibrationTable[i].Y_Range = 67.73012;
				}
				else if(i==30){
					ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 64.9348;
					ColibrationTable[i].Y_Range = 70.2182;
				}
				else{
                    ColibrationTable[i].id = i;
					ColibrationTable[i].Range_um = i*2 - 10;
					ColibrationTable[i].X_Range = 100;
					ColibrationTable[i].Y_Range = 100;
				}
				Execute(myQuery->Insert("Calibration" , i));
			}
//			mainForm->LogToFile("DataBaseClass: Colibration Table Created");
		}

	}

}
//---------------------------------------------------------------------------
void DataBaseClass::ShowSelectResults(UnicodeString TableName , int id)
{
	TStringList* names;
	TField* currentField;
	names = new TStringList;

	if (!dbSqlQuery->IsEmpty()) {
		if(TableName == "License"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			LicTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			LicTable.TotalTime = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			LicTable.WorkedTime = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			LicTable.RemainedTime = currentField->AsString.ToDouble();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select License");
		}
		else if(TableName == "INFO_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			InfoTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			InfoTable.url = currentField->AsString;
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			InfoTable.tel = currentField->AsString;
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select INFO_CONFIG");
		}
		else if(TableName == "APPLICATION_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			ApplicationTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			ApplicationTable.App_LastMode_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			ApplicationTable.osc = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select APPLICATION_CONFIG");
		}
		else if(TableName == "UDP_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			UdpTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			UdpTable.local_port = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			UdpTable.remote_port = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			UdpTable.server = currentField->AsString;
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			UdpTable.system = currentField->AsString;
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			UdpTable.connection_try = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			UdpTable.record_time = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select UDP_CONFIG");
		}
		else if(TableName == "TCP_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			TcpTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			TcpTable.local_port = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			TcpTable.remote_port = currentField->AsString.ToDouble();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select TCP_CONFIG");
		}
		else if(TableName == "OSC_CHART_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			OscChartTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			OscChartTable.osc1 = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			OscChartTable.osc2 = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			OscChartTable.osc3 = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			OscChartTable.osc4 = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			OscChartTable.timedev = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			OscChartTable.all_scale = (currentField->AsString == "1");
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select OSC_CHART_CONFIG");
		}
		else if(TableName == "OSC_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			OscTable[id].id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			OscTable[id].name = currentField->AsString;
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			OscTable[id].index = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			OscTable[id].offset = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			OscTable[id].unit = currentField->AsString;
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			OscTable[id].scale = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select OSC_CONFIG");
		}
		else if(TableName == "APPROACH_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			ApproachTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			ApproachTable.Apr_Refrerence_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			ApproachTable.Apr_Ki_Val_Contact = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			ApproachTable.Apr_Ki_Val_NonContact = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			ApproachTable.Apr_Bias_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			ApproachTable.Apr_Kd_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			ApproachTable.Apr_Kp_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[7]);
			ApproachTable.Apr_KiFeedbak_Val_Contact = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[8]);
			ApproachTable.Apr_KiFeedbak_Val_NonContact = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[9]);
			ApproachTable.Apr_ZPosition_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[10]);
			ApproachTable.Apr_SteperSpeed_Val_Precise = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[11]);
			ApproachTable.Apr_SteperStepMicro_Val_Precise = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[12]);
			ApproachTable.Apr_StepperSpeed_Val_Fast = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[13]);
			ApproachTable.Apr_StepperStepMicro_Val_Fast = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[14]);
			ApproachTable.Apr_StepperStep_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[15]);
			ApproachTable.Apr_ScanSpeed_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[16]);
			ApproachTable.Apr_BiasIndex_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[17]);
			ApproachTable.Apr_BiasOffset_Val = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select APPROACH_CONFIG");
		}
		else if(TableName == "FAST_APPROACH_DNC_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			FastApproachTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			FastApproachTable.Dnc_FrequencyFrom_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			FastApproachTable.Dnc_FrequencyTo_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			FastApproachTable.Threshold_Contact = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			FastApproachTable.Threshold_NonContact = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			FastApproachTable.Min_Amp = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			FastApproachTable.Max_Amp = currentField->AsString.ToInt();
            currentField = dbSqlQuery->FieldByName(names->Strings[7]);
			FastApproachTable.Drive_Start = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select FAST_APPROACH_DNC_CONFIG");
		}
		else if(TableName == "COARSEMOVE_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			MoveTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			MoveTable.Coarse_StepperSpeed_Val_Slow = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			MoveTable.Coarse_StepperSpeed_Val_Fast = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			MoveTable.Coarse_StepperStepMicro_Val = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select COARSEMOVE_CONFIG");
		}
		else if(TableName == "RETRACT_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			RetractTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			RetractTable.Ret_OneStep_Val= currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			RetractTable.Ret_StepperSpeed_Val= currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			RetractTable.Ret_StepperStepMicro_Val= currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select RETRACT_CONFIG");
		}
        else if(TableName == "STAGE_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			StageTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			StageTable.Stage_StepperSpeed_Val_Slow = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			StageTable.Stage_StepperSpeed_Val_Fast = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			StageTable.Stage_StepperStepMicro_Val = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select STAGE_CONFIG");
		}
		else if(TableName == "DNC_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			DncTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			DncTable.Dnc_FrequencyFromMin_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			DncTable.Dnc_FrequencyFrom_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			DncTable.Dnc_FrequencyToMax_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			DncTable.Dnc_FrequencyTo_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			DncTable.Dnc_FrequencyUse_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			DncTable.Dnc_DriveVoltage_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[7]);
			DncTable.Dnc_PointsCount_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[8]);
			DncTable.Dnc_SetPointPercentage_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[9]);
			DncTable.Dnc_TimeCnt_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[10]);
			DncTable.Dnc_RollOff_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[11]);
			DncTable.Dnc_DriveIndex_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[12]);
			DncTable.Dnc_DriveOffset_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[13]);
			DncTable.Dnc_Refrence_Val = currentField->AsString.ToDouble();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select DNC_CONFIG");
		}
		else if(TableName == "SCAN_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			ScanTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			ScanTable.Scan_Range_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			ScanTable.Scan_X_Center_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			ScanTable.Scan_Y_Center_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			ScanTable.Scan_Speed_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			ScanTable.Scan_Angle_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			ScanTable.Scan_Resolution_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[7]);
			ScanTable.Scan_OverScan_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[8]);
			ScanTable.Scan_1D_Leveling = (currentField->AsString == "1");
			currentField = dbSqlQuery->FieldByName(names->Strings[9]);
			ScanTable.Scan_2D_Leveling = (currentField->AsString == "1");
			currentField = dbSqlQuery->FieldByName(names->Strings[10]);
			ScanTable.LITHO_CONFIG = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[11]);
			ScanTable.Scan_Offset_val = currentField->AsString.ToDouble();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select SCAN_CONFIG");
		}
		else if(TableName == "LITHO_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			LithoTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			LithoTable.Litho_Delay = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select LITHO_CONFIG");
		}
		else if(TableName == "FORCE_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			ForceTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			ForceTable.Force_StartX_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			ForceTable.Force_StartY_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			ForceTable.Force_Z1_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			ForceTable.Force_Z2_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			ForceTable.Force_U1_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			ForceTable.Force_U2_Val = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[7]);
			ForceTable.Force_Delay_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[8]);
			ForceTable.Force_Resolution_Index = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[9]);
			ForceTable.Force_Mode_Index = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[10]);
			ForceTable.TB_C_Factor = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[11]);
			ForceTable.C_Factor_Set = (currentField->AsString == "1");
			currentField = dbSqlQuery->FieldByName(names->Strings[12]);
			ForceTable.K_Factor = currentField->AsString.ToDouble();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select FORCE_CONFIG");
		}
		else if(TableName == "KPFM_CONFIG"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			KpfmTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			KpfmTable.Kpfm_Frequency_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			KpfmTable.Kpfm_DriveVoltage_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			KpfmTable.Kpfm_Lia1_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			KpfmTable.Kpfm_Ki_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			KpfmTable.Kpfm_Kp_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			KpfmTable.Kpfm_Kd_Val = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[7]);
			KpfmTable.Kpfm_Th_Val = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select KPFM_CONFIG");
		}
		else if(TableName == "PARAMETERS"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			ParametersTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			ParametersTable.APR_Auto_Tune = (currentField->AsString == "1");
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			ParametersTable.Scan_leveling = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			ParametersTable.Scan_Pallet = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			ParametersTable.Apr_F_CON_FREQ_From = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[5]);
			ParametersTable.Apr_F_CON_FREQ_To = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[6]);
			ParametersTable.Apr_F_CON_DRV_Start = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[7]);
			ParametersTable.Apr_F_CON_AMP_MIN = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[8]);
			ParametersTable.Apr_F_CON_AMP_MAX = currentField->AsString.ToInt();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select PARAMETERS");
		}
		else if(TableName == "HARDWARE_TYPE"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			HardwareTable.id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			HardwareTable.HardWare_Scanner_Type = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			HardwareTable.Max_Range = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			HardwareTable.last_IP = currentField->AsString;
			currentField = dbSqlQuery->FieldByName(names->Strings[4]);
			HardwareTable.LogToFile = (currentField->AsString == "1");
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select HARDWARE_TYPE");
		}
		else if(TableName == "Calibration"){
			dbSqlQuery->First();
			dbSqlQuery->GetFieldNames(names);
			currentField = dbSqlQuery->FieldByName(names->Strings[0]);
			ColibrationTable[id].id = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[1]);
			ColibrationTable[id].Range_um = currentField->AsString.ToInt();
			currentField = dbSqlQuery->FieldByName(names->Strings[2]);
			ColibrationTable[id].X_Range = currentField->AsString.ToDouble();
			currentField = dbSqlQuery->FieldByName(names->Strings[3]);
			ColibrationTable[id].Y_Range = currentField->AsString.ToDouble();
			dbSqlQuery->Fields->Clear();
//			mainForm->LogToFile("Show Select Colibration");
		}
	}
	names->Free();
}


