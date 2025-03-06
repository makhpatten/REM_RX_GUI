/////////////////////////////////////////////////////////////////////////////
// CDebugWinDlg dialog used to display channels

#include "stdafx.h"
#include "infinity.h"
#include "cDebugAGCWinDlg.h"
#include "cDebugWinDlg.h"
#include "infinityDlg.h"
#include "msg_defs.h"
#include "config.h"

BEGIN_MESSAGE_MAP(CDebugAGCWinDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LOCAL_AGC_READ, &CDebugAGCWinDlg::OnBnClickedLocalAgcRead)
	ON_BN_CLICKED(IDC_LOCAL_AGC_WRITE, &CDebugAGCWinDlg::OnBnClickedLocalAgcWrite)
	ON_BN_CLICKED(IDC_REMOTE_AGC_WRITE, &CDebugAGCWinDlg::OnBnClickedRemoteAgcWrite)
	ON_BN_CLICKED(IDC_REMOTE_AGC_READ, &CDebugAGCWinDlg::OnBnClickedRemoteAgcRead)
END_MESSAGE_MAP()

CDebugAGCWinDlg::CDebugAGCWinDlg() : CDialog(CDebugAGCWinDlg::IDD)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

void CDebugAGCWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelsDlg)
	//}}AFX_DATA_MAP
}


BOOL CDebugAGCWinDlg::OnInitDialog() {
	return TRUE;
}

void CDebugAGCWinDlg::OnOK() {
	int x;
//	if (m_FreqValue->GetFocus()==NULL) {
		x=1;
//	} else {
		x=2;
//	}
//	CDialog::OnOK();
}


extern char outMsgStr[];
extern CString msgString;
extern char inMsgParams[];


void CDebugAGCWinDlg::OnBnClickedLocalAgcRead() {
//	readLocalAGCCmd();
}

void CDebugAGCWinDlg::OnBnClickedLocalAgcWrite() {
//	writeLocalAGCCmd();
}

void CDebugAGCWinDlg::OnBnClickedRemoteAgcWrite() {
//	writeRemoteAGCCmd();
}

void CDebugAGCWinDlg::OnBnClickedRemoteAgcRead() {
//	readRemoteAGCCmd();
}

ULONG bytes2long(char*);
void long2bytes(ULONG, char*);
extern char freqValChars[];

#if 1==0
void CDebugAGCWinDlg::readLocalAGCCmd() {

	outMsgStr[0]=readLocalAGCCmdStr[0]; //"da" command
	outMsgStr[1]=readLocalAGCCmdStr[1]; // "da" command

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output Read Local AGC Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
	CMainDlg::writeCmd(CMD_READ_LOCAL_AGC_LEN);

#if INTERFACE_USB==1 // only immediately read response in USB version (RS232 version reads then asycronously)
	CMainDlg::readResp(RESP_LOCAL_AGC_LEN);
	CMainDlg::dispLocalAGCResp(); // new function so same thing can be done in RS232 versino
#endif
}

void CDebugAGCWinDlg::readRemoteAGCCmd() {

	outMsgStr[0]=readRemoteAGCCmdStr[0]; //"dc" command
	outMsgStr[1]=readRemoteAGCCmdStr[1]; // "dc" command

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output Read Remote AGC Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
	CMainDlg::writeCmd(CMD_READ_REMOTE_AGC_LEN);

#if INTERFACE_USB==1 // only immediately read response in USB version (RS232 version reads then asycronously)
	CMainDlg::readResp(RESP_REMOTE_AGC_LEN);
    CMainDlg::displayRemoteAGCResp();
#endif

}

void CDebugAGCWinDlg::writeLocalAGCCmd() {
	CString strVal;
	ULONG longVal;

	outMsgStr[0]=writeLocalAGCCmdStr[0]; //"dc" command
	outMsgStr[1]=writeLocalAGCCmdStr[1]; // "dc" command

// Get AGC Maxgain
	CEdit* editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_MAXGAIN);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+2); // Set into outMsgStr[2] and outMsgStr[3]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

// Get AGC Threshold
	editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_THRESHOLD);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+4); // Set into outMsgStr[4] and outMsgStr[5]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

// Get AGC Attack
	editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_ATTACK);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+6); // Set into outMsgStr[6] and outMsgStr[7]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

// Get AGC Decay
	editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_DECAY);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+8); // Set into outMsgStr[8] and outMsgStr[9]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output Write Local AGC Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
	CMainDlg::writeCmd(CMD_WRITE_LOCAL_AGC_LEN);

#if INTERFACE_USB==1 // only immediately read response in USB version (RS232 version reads then asycronously)
	CMainDlg::readResp(RESP_LOCAL_AGC_LEN);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input TA Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif
}


void CDebugAGCWinDlg::writeRemoteAGCCmd() {
	CString strVal;
	ULONG longVal;

	outMsgStr[0]=writeRemoteAGCCmdStr[0]; //"dd" command
	outMsgStr[1]=writeRemoteAGCCmdStr[1]; // "dd" command

// Get AGC Maxgain
	CEdit* editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_MAXGAIN);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+2); // Set into outMsgStr[2] and outMsgStr[3]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

// Get AGC Threshold
	editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_THRESHOLD);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+4); // Set into outMsgStr[4] and outMsgStr[5]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

// Get AGC Attack
	editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_ATTACK);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+6); // Set into outMsgStr[6] and outMsgStr[7]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

// Get AGC Decay
	editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_DECAY);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	long2bytes(longVal,outMsgStr+8); // Set into outMsgStr[8] and outMsgStr[9]
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output Write Remote AGC Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
	CMainDlg::writeCmd(CMD_WRITE_REMOTE_AGC_LEN);

#if INTERFACE_USB==1 // only immediately read response in USB version (RS232 version reads then asycronously)
	CMainDlg::readResp(RESP_REMOTE_AGC_LEN);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input TC Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif

}
#endif

ULONG bytes2long(char x[]) {
	ULONG y;
	y=(ULONG)x[0]&(ULONG)0x0ff;
	y<<=8;
	y|=(ULONG)x[1]&(ULONG)0x0ff;
	return (y);
}

void long2bytes(ULONG u, char x[]) {
	u&=(long unsigned)0x00ffff;
	x[0]=(char)((u>>8)&(long unsigned)0x0ff);
	x[1]=(char)(u&(long unsigned)0x0ff);
}

