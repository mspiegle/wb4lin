#ifndef COMMON_H_
#define COMMON_H_

#include <wx/wxprec.h>

//some defines
#define BAUDRATE B19200
#define FRAMESIZE 28
#define HEADER0 0x5A
#define HEADER1 0xA5
#define LAMBDA_TABLE_SIZE 65
#define TEWB_UMAX 8184

//app-specific
#define APP_NAME "Wideband 4 Linux"

//data types for display controls
enum {
	TEWB_DEFAULT = -1,
	TEWB_TICK = 0,
	TEWB_AFR_RAW,
	TEWB_AFR_IPX,
	TEWB_U1,
	TEWB_U2,
	TEWB_U3,
	TEWB_T1,
	TEWB_T2,
	TEWB_T3,
	TEWB_THERM,
	TEWB_RPM,
};



//event IDs
enum {
	ID_FileOpen = wxID_HIGHEST + 1,
	ID_FileSave,
	ID_FileExport,
	ID_FileQuit,
	ID_WidebandConnect,
	ID_WidebandConfig,
	ID_DashboardAddGauge,
	ID_DashboardAddMeter,
	ID_DashboardAddDigit,
	ID_DashboardAddGraph,
	ID_HelpAbout,
	ID_Test,
	ID_RemoveThis,
	ID_GraphMenuConfig,
	ID_GraphMenuRemove,
	ID_GaugeMenuRemove,
	ID_GaugeMenuConfig,
	ID_DigitMenuRemove,
	ID_DigitMenuConfig,
	ID_GaugeDialogOk,
	ID_GaugeDialogCancel,
	ID_TestButton,
	ID_ConnectOkButton,
	ID_ConnectCancelButton,
	ID_FindSerialsButton,
	ID_DestroyGauge,
	ID_DestroyDigit
};

#endif /*COMMON_H_*/
