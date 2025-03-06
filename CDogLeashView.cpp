#include "stdafx.h"
#include "cDogLeashView.h"
#include "sys_clk.h"
#include "msg_defs.h"
#include "infinityDlg.h"
#include "config.h"

CDogleashCmdDlg::CDogleashCmdDlg(CWnd* pParent /*=NULL*/):CDialog(CDogleashCmdDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}



//CDogleashCmdCmdDlg *pDogleashCmdWinDlg=(CDogleashCmdCmdDlg*)0;


void CDogleashCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStingerRecCmdDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDogleashCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CStingerRecCmdDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_MARK_PATTEN, &CStingerRecCmdDlg::OnMarkPatten)
//	ON_BN_CLICKED(IDC_DOGLEASH_REFRESH, &CDogleashCmdDlg::OnBnClickedDogleashRefresh)
	ON_BN_CLICKED(IDC_DOGLEASH_ERASE, &CDogleashCmdDlg::OnBnClickedDogleashErase)
	ON_WM_TIMER()
END_MESSAGE_MAP()

CListBox *pDogleashCmdTxt;
CListBox *pDogleashTimeRemain;
void updateDogleashWindow();
CDogleashCmdDlg *pDogleashWinDlg=(CDogleashCmdDlg*)0;
extern CSetSysClkDlg *pSetSysClkDlg;

BOOL CDogleashCmdDlg::OnInitDialog() {
	dogleashModeCmd(0); // The 0 indicates return current dog leash
	pDogleashCmdTxt=(CListBox*)GetDlgItem(IDC_DOGLEASH_CMD_TEXT);
	pDogleashTimeRemain=(CListBox*)GetDlgItem(IDC_DOGLEASH_TIMEREMAIN);
	updateDogleashWindow();
	SetTimer(ID_TIMER_DOGLEASH_TIMEREMAIN, 500, NULL);

	return TRUE;
}

void CDogleashCmdDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ID_TIMER_DOGLEASH_TIMEREMAIN) {
		dogleashModeCmd(0); // The 0 indicates return current dog leash
		updateDogleashWindow();
		SetTimer(ID_TIMER_DOGLEASH_TIMEREMAIN, 500, NULL);
	} else {
		CDialog::OnTimer(nIDEvent);
	}
}
/* now done in onTimer()
void CDogleashCmdDlg::OnBnClickedDogleashRefresh() {
	dogleashModeCmd(0); // The 0 indicates return current dog leash
	updateDogleashWindow();
}
*/

void CDogleashCmdDlg::OnBnClickedDogleashErase() {
	dogleashModeCmd(1); // The 1 indicates cancel current dog leash
	updateDogleashWindow();
}
extern char outMsgStr[];


void CDogleashCmdDlg::dogleashModeCmd(int mode) { // The mode indicates turn record on or off
//	outMsgStr[0]=dogleashModeCmdStr[0]; //"dh" command
//	outMsgStr[1]=dogleashModeCmdStr[1]; // "dh" command
	outMsgStr[2]=mode; // 0: return status, 1: erase dogleash
//	CMainDlg::writeCmd(CMD_DOGLEASH_MODE_LEN);  //Write out DH msg of length 3
#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_DOGLEASH_MODE_LEN);  //Read in TH msg of length 23 ??? (never trust these comments...check msg_defs.h)
#endif
}
extern char inMsgParams[];
extern void updateStingerCmdTxt(CListBox *editText);

void updateDogleashWindow() {
	CString strval;
	long unsigned longVal;
	long unsigned hoursVal,daysVal,minsVal,secsVal;
// First update stinger command printout
	updateStingerCmdTxt(pDogleashCmdTxt);
// Now update seconds remaining
	pDogleashTimeRemain->ResetContent();

// maximum number of minutes (2 bytes define minutes)=65536 minutes max (45 days, 12 hours, 16 minutes)
// number of seconds: 65536*60=0x3C0000

//	inMsgParams[1]=1;
//	inMsgParams[18]=0x3c;
//	inMsgParams[19]=0x00;
//	inMsgParams[20]=0x00;


	if (inMsgParams[1]!=0) {

// compute longVal, number of seconds from three byte value
		longVal=((long unsigned)inMsgParams[18])&(long unsigned)0x0ff;
		longVal<<=8;
		longVal+=((long unsigned)inMsgParams[19])&(long unsigned)0x0ff;
		longVal<<=8;
		longVal+=((long unsigned)inMsgParams[20])&(long unsigned)0x0ff;

// compute days, hours, etc
		daysVal=longVal/((long unsigned)3600*(long unsigned)24);
		hoursVal=(longVal-(daysVal*3600*24))/3600;
		minsVal=(longVal-(daysVal*3600*24)-(hoursVal*3600))/60;
		secsVal=longVal-(daysVal*3600*24)-(hoursVal*3600)-(minsVal*60);

// select print format
		if (daysVal==0) {
			if (hoursVal==0) {
				strval.Format("%2ld mins, %2ld secs",minsVal,secsVal);
			} else {
				strval.Format("%2ld hours, %2ld mins, %2ld secs",hoursVal,minsVal,secsVal);
			}
		} else {
			strval.Format("%2ld days,%2ld hours, %2ld mins, %2ld secs",daysVal,hoursVal,minsVal,secsVal);
		}
		pDogleashTimeRemain->InsertString(-1,strval);
	}
}

