//---------------------------------------------------------------------------
#pragma hdrstop
#include "globals.h"
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
queueClassUdp *data_queue;
queueClassTcp *img_queue;
queueClassTcpDnc *dnc_queue;

int UdpTbRef = -8388607;
int UdpAmpRef = -8388607;
bool AllScale = true;
bool HaveLicense = true;
bool SaveImages = false;

DWORD hid = 0;
DWORD sid = 0;
UnicodeString DBPassWord = "";

UnicodeString MainPath;
UnicodeString UploadPath;
UnicodeString DownloadPath;
UnicodeString DataBasePath;
UnicodeString LastImagesFolderPath = "Null";

int Scanner_Type = 0;

LicenseTable LicTable;
INFO_CONFIG InfoTable;
APPLICATION_CONFIG ApplicationTable;
UDP_CONFIG UdpTable;
TCP_CONFIG TcpTable;
OSC_CHART_CONFIG OscChartTable;
OSC_CONFIG OscTable[27];
APPROACH_CONFIG ApproachTable;
FAST_APPROACH_DNC_CONFIG FastApproachTable;
COARSEMOVE_CONFIG MoveTable;
RETRACT_CONFIG RetractTable;
STAGE_CONFIG StageTable;
DNC_CONFIG DncTable;
SCAN_CONFIG ScanTable;
LITHO_CONFIG LithoTable;
FORCE_CONFIG ForceTable;
KPFM_CONFIG KpfmTable;
PARAMETERS ParametersTable;
HARDWARE_TYPE HardwareTable;
Colibration ColibrationTable[56];

ForceCommands FsCommand;
ScanCommands ScanCommand;

//---------------------------------------------------------------------------
#pragma package(smart_init)