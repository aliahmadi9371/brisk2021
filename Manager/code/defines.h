#define UPD_HEADER_0 0XC1
#define UPD_HEADER_1 0XB7

#define TCP_HEADER_0 0XC1
#define TCP_HEADER_1 0XB7
#define TCP_HEADER_IMAGE 0XDF
#define TCP_HEADER_ACK 0XC5

#define AFM_MODE_SETIING  0X12
#define APPROACHE_FRAME    0XC2
#define SCANNING_FRAME    0XDF
#define COARSE_MOVE_FRAME 0XD3
#define DNC_FRAME         0XF0
#define FORCE_SPEC_FRAME  0X46
#define KPFM_FRAME        0XF1
#define CROSS_HAIR_FRAME  0XA2
#define ISO_STAGE_FRAME   0X73
#define LITHO_FRAME 0xDC

#define BufferSize 32
#define QueueSize 1000
#define ChartXSize 1500
#define ChartYSize 410
#define Plot_Timer 30
#define TIME_DEV 1

#define CMD_QUEUE_SIZE 100
#define LOG_QUEUE_SIZE 100
#define __DEBUG true

#define MAX_TCP_RESOLUTION 2048
#define IMAGE_INDEX_COUNT 17*2

#define AMP_TCP_DATA 0XF0
#define PHASE_TCP_DATA 0XF1

#define IMAGE_COUNT 12*2
#define MAX_TCP_HEIGHT 2048
#define MAX_TCP_WIDTH 2048
#define MAX_TCP_PERLINE 65536
#define DEFAULT_INDEX 0

#define HEADER_COUNT_IMAGE 14
#define HEADER_COUNT_DNC 8
#define HEADER_COUNT_Force 9

#define MIN_COLOR 0
#define MAX_COLOR 255

#define MIN_VALUE -8388607
#define MAX_VALUE 8388607
#define MAX_MAX 16777215
//#define MAX_MAX 16777216

#define PIC0_FF "Topo-F"
#define PIC0_BB "Topo-B"

#define PIC1_FF "TB-F"
#define PIC1_BB "TB-B"

#define PIC2_FF "LR-F"
#define PIC2_BB "LR-B"

#define PIC3_FF "Amp-F"
#define PIC3_BB "Amp-B"

#define PIC4_FF "Phase-F"
#define PIC4_BB "Phase-B"

#define PIC5_FF "Bias-F"
#define PIC5_BB "Bias-B"

#define PIC6_FF "Cafm-F"
#define PIC6_BB "Cafm-B"

#define PIC7_FF "AmpWe-F"
#define PIC7_BB "AmpWe-B"

#define PIC8_FF "PhaseWe-F"
#define PIC8_BB "PhaseWe-B"

#define PIC9_FF "Lia1x_F"
#define PIC9_BB "Lia1x_B"

#define PIC10_FF "Lia1y-F"
#define PIC10_BB "Lia1y-B"

#define PIC11_FF "Amp2We-F"
#define PIC11_BB "Amp2We-B"

#define PIC12_FF "Phase2We-F"
#define PIC12_BB "Phase2We-B"

#define PIC13_FF "Lia2x-F"
#define PIC13_BB "Lia2x-B"

#define PIC14_FF "Lia2y-F"
#define PIC14_BB "Lia2y-B"

#define PIC15_FF "Amp_Fly-F"
#define PIC15_BB "Amp_Fly-B"

#define PIC16_FF "Phase_Fly-F"
#define PIC16_BB "Phase_Fly-B"

#define crMyPenCur 25
#define crMyBrushCur 26
#define crMyLineCur 27
#define crMyRectCur 28
#define crMyCircCur 29
#define crMyEraseCur 30
