/////////////////////////////////////////////////////////////////////////////
// CSetSysClkDlg dialog
#include "stdafx.h"
//#include "afxwin.h"
#include "sys_clk.h"
#include "infinityDlg.h"
#include "msg_defs.h"
#include "cDebugWinDlg.h"
#include "config.h"

CSetSysClkDlg::CSetSysClkDlg(CWnd* pParent /*=NULL*/):CDialog(CSetSysClkDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CSetSysClkDlg)
	//}}AFX_DATA_INIT
}



//CDogleashCmdCmdDlg *pDogleashCmdWinDlg=(CDogleashCmdCmdDlg*)0;


void CSetSysClkDlg::DoDataExchange(CDataExchange* pDX)
{
//   	DDX_Control(pDX, IDC_DATETIMEPICKER1,pTimeBoxDDE);
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSysClkDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetSysClkDlg, CDialog)
	//{{AFX_MSG_MAP(CSetSysClkDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SYS_CLK_UPDATE, &CSetSysClkDlg::OnBnClickedSysClkUpdate)
	ON_BN_CLICKED(IDC_SYS_CLK_SET, &CSetSysClkDlg::OnBnClickedSysClkSet)
	ON_BN_CLICKED(IDC_SYS_CLK_SET_WINTIME, &CSetSysClkDlg::OnBnClickedSysClkSetWintime)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

CMonthCalCtrl* pCalendarBox;
CDateTimeCtrl* pTimeBox;
extern char outMsgStr[];
extern char inMsgParams[];
CTime tempTime;
int updateTimeBox();
void updateTimeCommand();
extern CString msgString;
int sysClockFormat;
extern unsigned int year,month,day,hour,min,sec;

BOOL CSetSysClkDlg::OnInitDialog() {
	pTimeBox=(CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER1);
	pTimeBox->SetFormat(_T("dd-MMM-yyyy hh:mm:ss tt "));
	tempTime=CTime(year,month,day,hour,min,sec,-1);
	pTimeBox->SetTime(&tempTime);



//	pTimeBoxDDE.SetFormat(_T("dd-MMM-yyyy hh:mm:ss tt "));
	sysClockFormat=0; // Indicate that it says windows
//	pCalendarBox=(CMonthCalCtrl *)GetDlgItem(IDC_MONTHCALENDAR1);
//	outMsgStr[0]=timeDateReadCmdStr[0]; //"di" command
//	outMsgStr[1]=timeDateReadCmdStr[1]; // "di" command
	msgString.Format("Output Read Time Msg (DJ)");
	CDebugWinDlg::DisplayData2(msgString);
//	CMainDlg::writeCmd(CMD_TIME_DATE_READ_LEN);  //Write out DJ msg of length 2

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_TIME_DATE_LEN);  //Read in TI msg of length 8
	msgString.Format("Input TI Msg: Secs:%d, Minutes:%d, Hours:%d",(int)inMsgParams[0],(int)inMsgParams[1],(int)inMsgParams[2]);
	CDebugWinDlg::DisplayData2(msgString);
	msgString.Format("Input TI Msg: Days:%d, Months:%d, Years:%d",(int)inMsgParams[3],(int)inMsgParams[4],(int)inMsgParams[5]);
	CDebugWinDlg::DisplayData2(msgString);
	int updateReturnVal;
	updateReturnVal=updateTimeBox();
	if (updateReturnVal==1) { // if correct time read, indicate sys clock format=1
		sysClockFormat=1;
	}
#endif

	SetTimer(ID_TIMER_TIMECLOCKUPDATE, 1000, NULL); //Update clock every half second

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSetSysClkDlg::OnTimer(UINT nIDEvent) {
	if (nIDEvent==ID_TIMER_TIMECLOCKUPDATE) {
// Only update if not currently editing date-time picker
		CWnd *x;
		x=GetFocus();
		if ((CDateTimeCtrl *)x!=pTimeBox) {
			updateTimeCommand();
		}
// Restart Timer
		SetTimer(ID_TIMER_TIMECLOCKUPDATE, 1000, NULL); //re-activate timer to update clock every half second
	} else {
		CDialog::OnTimer(nIDEvent);
	}
}

void CSetSysClkDlg::OnBnClickedSysClkUpdate() {
	updateTimeCommand();
}

void updateTimeCommand() {
//	outMsgStr[0]=timeDateReadCmdStr[0]; //"di" command
//	outMsgStr[1]=timeDateReadCmdStr[1]; // "di" command
	msgString.Format("Output Read Time Msg (DJ)");
	CDebugWinDlg::DisplayData2(msgString);
//	CMainDlg::writeCmd(CMD_TIME_DATE_READ_LEN);  //Write out DJ msg of length 2

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_TIME_DATE_LEN);  //Read in TI msg of length 8
	msgString.Format("Input TI Msg: Secs:%d, Minutes:%d, Hours:%d",(int)inMsgParams[0],(int)inMsgParams[1],(int)inMsgParams[2]);
	CDebugWinDlg::DisplayData2(msgString);
	msgString.Format("Input TI Msg: Days:%d, Months:%d, Years:%d",(int)inMsgParams[3],(int)inMsgParams[4],(int)inMsgParams[5]);
	CDebugWinDlg::DisplayData2(msgString);
	int updateReturnVal;
	updateReturnVal=updateTimeBox();
	if (updateReturnVal==0) { // Incorrect time read so do something
		if (sysClockFormat==1) { // Read previously correctly, so indicate problem with ? marks
			pTimeBox->SetFormat(_T("dd-MMM-yyyy hh:mm:ss tt '(???)'"));
		}
	} else sysClockFormat=1;
#endif

}

void sendSetTimeCmd(CTime*);

void CSetSysClkDlg::OnBnClickedSysClkSet() {
	pTimeBox->GetTime(tempTime);
	sendSetTimeCmd(&tempTime);
}

void CSetSysClkDlg::OnBnClickedSysClkSetWintime() {
	tempTime = CTime::GetCurrentTime();
	pTimeBox->SetTime(&tempTime);
	sendSetTimeCmd(&tempTime);
}

void sendSetTimeCmd(CTime *x) {
	outMsgStr[0]=CMD_TIME_SET_1; //"cl" command
	outMsgStr[1]=CMD_TIME_SET_2; // "cl" command
	outMsgStr[2]=(char)x->GetHour();
	outMsgStr[3]=(char)x->GetMinute();
	outMsgStr[4]=(char)x->GetSecond();
	CMainDlg::writeCmd(CMD_TIME_SET_LEN);  //Write out cl msg of length 7

	outMsgStr[0]=CMD_DATE_SET_1; //"cn" command
	outMsgStr[1]=CMD_DATE_SET_2; // "cn" command
	outMsgStr[2]=(char)x->GetDay();
	outMsgStr[3]=(char)x->GetMonth();
	outMsgStr[4]=(char)(x->GetYear()-2000);
	CMainDlg::writeCmd(CMD_DATE_SET_LEN);  //Write out cn msg of length 7

}

extern int setSysClkWinFlag;

afx_msg void CSetSysClkDlg::OnClose() {
	setSysClkWinFlag=0;
	CDialog::OnClose();
}
