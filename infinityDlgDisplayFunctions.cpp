#include "stdafx.h"
#include "infinity.h"
#include "cDebugWinDlg.h"
#include "infinityDlg.h"
#include "cDebugAGCWinDlg.h"
#include "msg_defs.h"
#include "led_defs.h"
#include "CStingerDlg.h"
#include "config.h"

extern CString msgString;
extern char inMsgParams[];
ULONG bytes2long(char*);
extern char freqValChars[];
extern long unsigned sdRamLongValue;
extern CListBox* m_sdRamLongText;

void CMainDlg::displayLocalAGCResp() {
	ULONG localAGCValue;

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input TA Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
// Set AGC Max gain
	localAGCValue=bytes2long(inMsgParams);
	sprintf(freqValChars,"%10ld",localAGCValue);
	CEdit* editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_MAXGAIN);
	editControl->SetWindowText(freqValChars);

// Set AGC threshold
	localAGCValue=bytes2long(inMsgParams+2);
	sprintf(freqValChars,"%10ld",localAGCValue);
	editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_THRESHOLD);
	editControl->SetWindowText(freqValChars);

// Set AGC attack
	localAGCValue=bytes2long(inMsgParams+4);
	sprintf(freqValChars,"%10ld",localAGCValue);
	editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_ATTACK);
	editControl->SetWindowText(freqValChars);

// Set AGC decay
	localAGCValue=bytes2long(inMsgParams+6);
	sprintf(freqValChars,"%10ld",localAGCValue);
	editControl = (CEdit*) GetDlgItem(IDC_LOCAL_AGC_DECAY);
	editControl->SetWindowText(freqValChars);
}


void CMainDlg::displayRemoteAGCResp() {
	ULONG remoteAGCValue;

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input TC Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
// Set AGC Max gain
	remoteAGCValue=bytes2long(inMsgParams);
	sprintf(freqValChars,"%10ld",remoteAGCValue);
	CEdit* editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_MAXGAIN);
	editControl->SetWindowText(freqValChars);

// Set AGC threshold
	remoteAGCValue=bytes2long(inMsgParams+2);
	sprintf(freqValChars,"%10ld",remoteAGCValue);
	editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_THRESHOLD);
	editControl->SetWindowText(freqValChars);

// Set AGC attack
	remoteAGCValue=bytes2long(inMsgParams+4);
	sprintf(freqValChars,"%10ld",remoteAGCValue);
	editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_ATTACK);
	editControl->SetWindowText(freqValChars);

// Set AGC decay
	remoteAGCValue=bytes2long(inMsgParams+6);
	sprintf(freqValChars,"%10ld",remoteAGCValue);
	editControl = (CEdit*) GetDlgItem(IDC_REMOTE_AGC_DECAY);
	editControl->SetWindowText(freqValChars);
}

/*
void CMainDlg::displaySDRAMAudioResp() {
//	sprintf(freqValChars,"0x%2x%2x%2x%2x",sdRamLongValue);
	sdRamLongValue=(long unsigned)((int)inMsgParams[0]&(int)0x0ff);
	sdRamLongValue<<=8;
	sdRamLongValue+=(long unsigned)((int)inMsgParams[1]&(int)0x0ff);
	sdRamLongValue<<=8;
	sdRamLongValue+=(long unsigned)((int)inMsgParams[2]&(int)0x0ff);
	sdRamLongValue<<=8;
	sdRamLongValue+=(long unsigned)((int)inMsgParams[3]&(int)0x0ff);
	sprintf(freqValChars,"0x%8lx",sdRamLongValue);
	m_sdRamLongText->ResetContent();
	m_sdRamLongText->InsertString(0,freqValChars);
}
*/

void CMainDlg::displayDeviationResp() {
	CString strVal;
	ULONG longVal;

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_DEVIATION);
	longVal=(long unsigned)inMsgParams[0]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[1]&(long unsigned)0x0ff;
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);
}

extern ULONG respFreqKHz;
extern ULONG freq_3bytes_to_value(char*);
extern int inMsgType;
//extern bool MyDeviceDetected;
extern void freqKHzToMHzString(ULONG,char *);
extern CEdit *m_FreqValue;
extern CButton *m_stingerCmd;
extern ULONG tuneFreqKHz;
extern float paramValueFloat;
extern int paramValueInt;
extern CDC *drawingContextMain;

void CMainDlg::displayFreqResp() {
	respFreqKHz=freq_3bytes_to_value(inMsgParams);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//	if (inMsgType==CMD_SET_FREQ) {
//		msgString="Input SS Msg: Freq =";
//	} else {
//		msgString="Input Unknown Msg: Freq =";
//	}
	msgString.Format("%s %ld kHz",msgString,respFreqKHz);
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	if (MyDeviceDetected==TRUE && tuneFreqKHz!=respFreqKHz) {
	if (tuneFreqKHz!=respFreqKHz) {
		freqKHzToMHzString(respFreqKHz,freqValChars);
		m_FreqValue->SetWindowText(freqValChars);
	}

// If stinger command echo on, send stinger command
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}
