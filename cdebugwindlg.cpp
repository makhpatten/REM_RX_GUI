/////////////////////////////////////////////////////////////////////////////
// CDebugWinDlg dialog used to display channels

#include "stdafx.h"
#include "infinity.h"
#include "cDebugWinDlg.h"
#include "infinityDlg.h"
#include "cDebugAGCWinDlg.h"
#include "msg_defs.h"
#include "config.h"

//#include "cscandlg.h"
//#include "led_defs.h"

//ULONG nScanSteps;

//#define MAX_STEPS 100

extern char InputReport[];
int continuousFlag=FALSE;
int	printMsgsFlag=FALSE;


BEGIN_MESSAGE_MAP(CDebugWinDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
		// No message handlers
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDSCANOK, &CDebugWinDlg::OnBnClickedScanok)
	ON_BN_CLICKED(IDC_CONTINUOUS, &CDebugWinDlg::OnBnClickedContinuous)
	ON_BN_CLICKED(IDC_SPPWRITE, &CDebugWinDlg::OnBnClickedSppwrite)
	ON_BN_CLICKED(IDC_SPPREAD, &CDebugWinDlg::OnBnClickedSppread)
	ON_BN_CLICKED(IDC_DEVIATIONWRITE, &CDebugWinDlg::OnBnClickedDeviationwrite)
	ON_BN_CLICKED(IDC_DEVIATIONREAD, &CDebugWinDlg::OnBnClickedDeviationread)
	ON_BN_CLICKED(IDC_CENTERFREQWRITE, &CDebugWinDlg::OnBnClickedCenterfreqwrite)
	ON_BN_CLICKED(IDC_CENTERFREQREAD, &CDebugWinDlg::OnBnClickedCenterfreqread)
	ON_BN_CLICKED(IDC_DELTAPHASEWRITE, &CDebugWinDlg::OnBnClickedDeltaphasewrite)
	ON_BN_CLICKED(IDC_DELTAPHASEREAD4, &CDebugWinDlg::OnBnClickedDeltaphaseread4)
	ON_BN_CLICKED(IDC_CLKSPERFSWRITE, &CDebugWinDlg::OnBnClickedClksperfswrite)
	ON_BN_CLICKED(IDC_CLKSPERFSREAD, &CDebugWinDlg::OnBnClickedClksperfsread)
	ON_BN_CLICKED(IDC_BERREAD, &CDebugWinDlg::OnBnClickedBERRead)
	ON_BN_CLICKED(IDC_OSCCONTROLWRITE, &CDebugWinDlg::OnBnClickedOsccontrolWrite)
	ON_BN_CLICKED(IDC_OSCCONTROLREAD, &CDebugWinDlg::OnBnClickedOsccontrolRead)
	ON_BN_CLICKED(IDC_RESET, &CDebugWinDlg::OnBnClickedRestoreOsc)
//	ON_BN_CLICKED(IDC_BAND_SW1, &CDebugWinDlg::OnBnClickedBandSw1)
//	ON_BN_CLICKED(IDC_BAND_SW0, &CDebugWinDlg::OnBnClickedBandSw0)
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SQUELCH, &CDebugWinDlg::OnNMReleasedcaptureSquelch)
	ON_BN_CLICKED(IDC_PRINT_MSGS, &CDebugWinDlg::OnBnClickedPrintMsgs)
	ON_BN_CLICKED(IDC_RESYNCMSGS, &CDebugWinDlg::OnBnClickedResyncmsgs)
	ON_BN_CLICKED(IDC_UPDATE_BANDSW, &CDebugWinDlg::OnBnClickedUpdateBandsw)
	ON_BN_CLICKED(IDC_READ_SQUELCH, &CDebugWinDlg::OnBnClickedReadSquelch)
//	ON_BN_CLICKED(IDCLOCAL_AGC_WRITE, &CDebugWinDlg::OnBnClickedAgcWrite)
//	ON_BN_CLICKED(IDC_LOCAL_AGC_READ, &CDebugWinDlg::OnBnClickedLocalAgcRead)
//	ON_BN_CLICKED(IDC_LOCAL_AGC_WRITE, &CDebugWinDlg::OnBnClickedLocalAgcWrite)
//	ON_BN_CLICKED(IDC_REMOTE_AGC_WRITE, &CDebugWinDlg::OnBnClickedRemoteAgcWrite)
//	ON_BN_CLICKED(IDC_REMOTE_AGC_READ, &CDebugWinDlg::OnBnClickedRemoteAgcRead)
ON_BN_CLICKED(IDC_UPDATE_CUSTOMERID, &CDebugWinDlg::OnBnClickedUpdateCustomerid)
ON_BN_CLICKED(IDC_DEBUG_AGC_WIN2, &CDebugWinDlg::OnBnClickedDebugAgcWin2)
//ON_LBN_SELCHANGE(IDC_SQUELCH_VALUE_TXT, &CDebugWinDlg::OnLbnSelchangeSquelchValueTxt)
ON_BN_CLICKED(IDC_WRITE_SQUELCH, &CDebugWinDlg::OnBnClickedWriteSquelch)
ON_EN_CHANGE(IDC_SPPADDR, &CDebugWinDlg::OnEnChangeSppaddr)
ON_EN_CHANGE(IDC_SPPDATA, &CDebugWinDlg::OnEnChangeSppdata)
ON_BN_CLICKED(IDC_EEPROM_PIC1_WRITE, &CDebugWinDlg::OnBnClickedEepromPic1Write)
ON_BN_CLICKED(IDC_EEPROM_PIC1_READ, &CDebugWinDlg::OnBnClickedEepromPic1Read)
END_MESSAGE_MAP()


CDebugWinDlg::CDebugWinDlg() : CDialog(CDebugWinDlg::IDD)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

void CDebugWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelsDlg)
	//}}AFX_DATA_MAP
	//	DDX_Control(pDX, IDC_SCANAREA, m_scanArea);
	//	DDX_Control(pDX, IDC_START_FREQ, m_startFreqTxt);
	//	DDX_Control(pDX, IDC_STOP_FREQ, m_stopFreqTxt);
	//	DDX_Control(pDX, IDC_STEP_FREQ, m_stepFreqTxt);
	//DDX_Control(pDX, IDC_SPPADDR, m_sppAddr);
	//DDX_Control(pDX, IDC_SPPDATA, m_sppData);
	DDX_Control(pDX, IDC_DEVIATION, m_deviation);
	DDX_Control(pDX, IDC_CENTERFREQ, m_centerFreq);
	DDX_Control(pDX, IDC_DELTAPHASE, m_deltaPhase);
	DDX_Control(pDX, IDC_CLOCKSPERFS, m_clocksPerFs);
//	DDX_Control(pDX, IDC_BAND_SW1, m_band_sw1);
//	DDX_Control(pDX, IDC_BAND_SW0, m_band_sw0);
//	DDX_Control(pDX, IDC_SLIDER1, m_squelch);
}

// Globals for control item pointers
CSliderCtrl *squelchSlider;
CListBox *displayMsgs;
CButton *continuousButton;
CButton *printMsgsButton;
CListBox *m_squelchOnValue;
CListBox *m_squelchOffValue;
CListBox *m_hysterOnValue;
CListBox *m_hysterOffValue;
CButton* m_band_sw0;	
CButton* m_band_sw1;
CListBox* m_customerID;
CListBox* m_sdRamLongText;
CEdit *m_sppAddr;
CEdit *m_sppData;
CEdit *m_eepromPic1Addr;
CEdit *m_eepromPic1Data;


// External globals
extern char freqValChars[];
extern long unsigned customerID;

BOOL CDebugWinDlg::OnInitDialog() {
//	squelchSlider = (CSliderCtrl*) GetDlgItem(IDC_SQUELCH);
//	squelchSlider->SetRange(0,255); 
	displayMsgs = (CListBox*) GetDlgItem(IDC_DISPLAYMSGS);
	continuousButton = (CButton*) GetDlgItem(IDC_CONTINUOUS);
	m_squelchOnValue = (CListBox*) GetDlgItem(IDC_SQUELCH_VALUE_TXT);
	m_squelchOffValue = (CListBox*) GetDlgItem(IDC_SQUELCH_OFF_VALUE_TXT);
	m_hysterOnValue = (CListBox*) GetDlgItem(IDC_HYSTER_VALUE_TXT);
	m_hysterOffValue = (CListBox*) GetDlgItem(IDC_HYSTER_OFF_VALUE_TXT);
	m_band_sw0 = (CButton*) GetDlgItem(IDC_BAND_SW0);
	m_band_sw1 = (CButton*) GetDlgItem(IDC_BAND_SW1);
	m_customerID = (CListBox*) GetDlgItem(IDC_STINGER_CUSTOMERID);
	m_sdRamLongText = (CListBox*)GetDlgItem(IDC_SDRAM_AUDIO);

	m_sppAddr = (CEdit*) GetDlgItem(IDC_SPPADDR);
	m_sppData = (CEdit*) GetDlgItem(IDC_SPPDATA);

	m_eepromPic1Addr = (CEdit*) GetDlgItem(IDC_EEPROM_PIC1_ADDR);
	m_eepromPic1Data = (CEdit*) GetDlgItem(IDC_EEPROM_PIC1_DATA);

	if (customerID<0x010) {
	  sprintf(freqValChars,"00%1x",(long unsigned)customerID&(long unsigned)0x0fff);
	} else if (customerID<0x100) {
	  sprintf(freqValChars,"0%2x",(long unsigned)customerID&(long unsigned)0x0fff);
	} else {
	  sprintf(freqValChars,"%3x",(long unsigned)customerID&(long unsigned)0x0fff);
	}
	m_customerID->SetWindowTextA(freqValChars);

//	squelchSlider = (CSliderCtrl*) GetDlgItem(IDC_SQUELCH);
//	squelchSlider->SetRange(0,255);


	if (continuousFlag==1) {
		continuousButton->SetWindowTextA("Pause");
	} else {
		continuousButton->SetWindowTextA("Continue");
	}
	printMsgsButton = (CButton*) GetDlgItem(IDC_PRINT_MSGS);
	if (printMsgsFlag==1) {
		printMsgsButton->SetWindowTextA("Stop Msgs Print");
	} else {
		printMsgsButton->SetWindowTextA("Print Msgs");
	}

// Update band SW checks
	readBandSWCmd();
// Update squelch value
	readSquelchCmd();

//	m_FreqValue=(CEdit*) GetDlgItem(IDC_STOP_FREQ);
//	m_FreqValue->SetWindowText("300000"); 
//	m_FreqValue=(CEdit*) GetDlgItem(IDC_STEP_FREQ);
//	m_FreqValue->SetWindowText("5000"); 
//	m_squelch.SetRange(0,255);

	SetTimer(ID_TIMER_DEBUG_SDRAM_AUDIO, 200, NULL);
	return TRUE;
}

void CDebugWinDlg::OnTimer(UINT nIDEvent) {
	if (nIDEvent==ID_TIMER_DEBUG_SDRAM_AUDIO) {
		readSDRAMAudioCmd();
		SetTimer(ID_TIMER_DEBUG_SDRAM_AUDIO, 200, NULL);
	} else {
		CDialog::OnTimer(nIDEvent);
	}
}


extern char outMsgStr[];
extern CString msgString;
extern char inMsgParams[];
extern long unsigned sdRamLongValue;

void CDebugWinDlg::readSDRAMAudioCmd() {
//	outMsgStr[0]=readSDRAMAudioCmdStr[0]; //"dk" command
//	outMsgStr[1]=readSDRAMAudioCmdStr[1]; // "dk" command

//	CMainDlg::writeCmd(CMD_READ_SDRAM_AUDIO_LEN);

}

void CDebugWinDlg::OnBnClickedSppwrite()
{
	CString strVal;
	double doubleVal;

	outMsgStr[0]=CMD_FPGA_REG_SET_1; //"cc" command
	outMsgStr[1]=CMD_FPGA_REG_SET_2; // "cc" command

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_SPPADDR);
	editControl->GetWindowText(strVal);
	doubleVal = strtod(strVal, 0); //convert to float
	outMsgStr[2]=(char)(doubleVal);
	strVal.Format("%d",(int)outMsgStr[2]); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

	charValueFromDlgItem(IDC_SPPDATA,outMsgStr+3);

	CMainDlg::writeCmd(CMD_FPGA_REG_SET_LEN);

}

void CDebugWinDlg::OnBnClickedSppread()
{

	CString strVal;
	double doubleVal;
	CEdit* editControl = (CEdit*) GetDlgItem(IDC_SPPADDR);

	outMsgStr[0]=CMD_FPGA_REG_REQ_1; //"cb" command
	outMsgStr[1]=CMD_FPGA_REG_REQ_2; // "cb" command

	editControl->GetWindowText(strVal);
	doubleVal = strtod(strVal, 0); //convert to float
	outMsgStr[2]=(char)(doubleVal);

	strVal.Format("%d",outMsgStr[2]); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

	CMainDlg::writeCmd(CMD_FPGA_REG_REQ_LEN);

}

void CDebugWinDlg::FPGARegUpdate() {
	CString strVal;
	short int shortIntVal;

	strVal.Format("%d",inMsgParams[0]);
	m_sppAddr->SetWindowText(strVal);
	shortIntVal=(short int)(inMsgParams[1]&0x0ff);
	if (shortIntVal<0x10) {
		strVal.Format("0x0%1x",shortIntVal);
	} else {
		strVal.Format("0x%2x",shortIntVal);
	}
	m_sppData->SetWindowText(strVal);
}

void CDebugWinDlg::EepromPic1Update() {
	CString strVal;
	short int shortIntVal;

	strVal.Format("%d",inMsgParams[0]);
	m_eepromPic1Addr->SetWindowText(strVal);
	shortIntVal=(short int)(inMsgParams[1]&0x0ff);
	if (shortIntVal<0x10) {
		strVal.Format("0x0%1x",shortIntVal);
	} else {
		strVal.Format("0x%2x",shortIntVal);
	}
	m_eepromPic1Data->SetWindowText(strVal);
}

void CDebugWinDlg::OnBnClickedDeviationwrite()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=setDevCmdStr[0]; //"cf" command: write Deviation
//	outMsgStr[1]=setDevCmdStr[1]; // "cf" command: write deviation

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_DEVIATION);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	longVal&=(long unsigned)0x00ffff;
	outMsgStr[2]=(char)((longVal>>8)&(long unsigned)0x0ff);
	outMsgStr[3]=(char)((longVal)&(long unsigned)0x0ff);
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CF Msg: Deviation=%ld",longVal);
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_SET_DEV_LEN);
#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_SET_DEV_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input %c%c Msg (should be SF)",InputReport[0],InputReport[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif
}

void CDebugWinDlg::OnBnClickedDeviationread()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=readDevCmdStr[0]; //"cg" command: read Deviation
//	outMsgStr[1]=readDevCmdStr[1]; // "cg" command: read deviation

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CG Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_READ_DEV_LEN);
#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_READ_DEV_LEN);
	CMainDlg::displayDeviationResp();

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SG Msg: dev bytes:%d %d",(int)inMsgParams[0],inMsgParams[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif

}

void CDebugWinDlg::OnBnClickedCenterfreqwrite()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=setTxFreqCmdStr[0]; //"ch" command: write center frequency
//	outMsgStr[1]=setTxFreqCmdStr[1]; // "ch" command: write center frequency

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_CENTERFREQ);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
//	longVal&=(long unsigned)0x00ffffff;
	outMsgStr[2]=(char)((longVal>>24)&(long unsigned)0x0ff);
	outMsgStr[3]=(char)((longVal>>16)&(long unsigned)0x0ff);
	outMsgStr[4]=(char)((longVal>>8)&(long unsigned)0x0ff);
	outMsgStr[5]=(char)((longVal)&(long unsigned)0x0ff);
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CH Msg: Center Freq=%ld",longVal);
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_SET_TX_FREQ_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_SET_TX_FREQ_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input %c%c Msg (should be SH)",(int)InputReport[0],(int)InputReport[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif
}

void CDebugWinDlg::OnBnClickedCenterfreqread()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=readTxFreqCmdStr[0]; //"cj" command: read center freq
//	outMsgStr[1]=readTxFreqCmdStr[1]; // "cj" command: read center freq

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CJ Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_READ_TX_FREQ_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_READ_TX_FREQ_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SJ Msg: dev bytes:%d %d,%d,%d",(int)inMsgParams[0],inMsgParams[1],inMsgParams[2],inMsgParams[3]);
	CDebugWinDlg::DisplayData2(msgString);
#endif

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_CENTERFREQ);
	longVal=(long unsigned)inMsgParams[0]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[1]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[2]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[3]&(long unsigned)0x0ff;
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);
#endif
}

void CDebugWinDlg::OnBnClickedDeltaphasewrite()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=setDeltaPhaseCmdStr[0]; //"ck" command: write delta phase
//	outMsgStr[1]=setDeltaPhaseCmdStr[1]; // "ck" command: write delta phase

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_DELTAPHASE);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
//	longVal&=(long unsigned)0x00ffffff;
	outMsgStr[2]=(char)((longVal>>16)&(long unsigned)0x0ff);
	outMsgStr[3]=(char)((longVal>>8)&(long unsigned)0x0ff);
	outMsgStr[4]=(char)((longVal)&(long unsigned)0x0ff);
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CK Msg: Center Freq=%ld",longVal);
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_SET_DELTA_PHASE_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_SET_DELTA_PHASE_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input %c%c Msg (should be SK)",(int)InputReport[0],(int)InputReport[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif
}

void CDebugWinDlg::OnBnClickedDeltaphaseread4()
{
	CString strVal;
	long unsigned longVal;
//	outMsgStr[0]=readDeltaPhaseCmdStr[0]; //"cl" command: read delta phase
//	outMsgStr[1]=readDeltaPhaseCmdStr[1]; // "cl" command: read delta phase

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CL Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_READ_DELTA_PHASE_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_READ_DELTA_PHASE_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SL Msg: dev bytes:%d %d,%d",(int)inMsgParams[0],inMsgParams[1],inMsgParams[2]);
	CDebugWinDlg::DisplayData2(msgString);
#endif

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_DELTAPHASE);
	longVal=(long unsigned)inMsgParams[0]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[1]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[2]&(long unsigned)0x0ff;
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);
#endif
}

void CDebugWinDlg::OnBnClickedClksperfswrite()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=setClksPerFsCmdStr[0]; //"cm" command: write clks per fs
//	outMsgStr[1]=setClksPerFsCmdStr[1]; // "cm" command: write clks per fs

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_CLOCKSPERFS);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
//	longVal&=(long unsigned)0x00ffffff;
	outMsgStr[2]=(char)((longVal>>8)&(long unsigned)0x0ff);
	outMsgStr[3]=(char)((longVal)&(long unsigned)0x0ff);
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CM Msg: Center Freq=%ld",longVal);
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_SET_CLKS_PER_FS_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_SET_CLKS_PER_FS_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input %c%c Msg (should be SM)",(int)InputReport[0],(int)InputReport[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif
}

void CDebugWinDlg::OnBnClickedClksperfsread()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=readClksPerFsCmdStr[0]; //"cn" command: read clocks per Fs
//	outMsgStr[1]=readClksPerFsCmdStr[1]; // "cn" command: read clocks per Fs

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CN Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_READ_CLKS_PER_FS_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_READ_CLKS_PER_FS_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SN Msg: dev bytes:%d %d",(int)inMsgParams[0],inMsgParams[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_CLOCKSPERFS);
	longVal=(long unsigned)inMsgParams[0]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[1]&(long unsigned)0x0ff;
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);
#endif
}

void CDebugWinDlg::OnBnClickedBERRead()
{
	CString strVal;
	long unsigned longVal;

//	outMsgStr[0]=readBERCmdStr[0]; //"co" command: read BER
//	outMsgStr[1]=readBERCmdStr[1]; // "co" command: read BER

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CO Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_READ_BER_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_READ_BER_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SO Msg: dev bytes:%d,%d,%d",(int)inMsgParams[0],inMsgParams[1],inMsgParams[2]);
	CDebugWinDlg::DisplayData2(msgString);
#endif

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_BER);
	longVal=(long unsigned)inMsgParams[2]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[1]&(long unsigned)0x0ff;
	longVal*=(long unsigned)256;
	longVal+=(long unsigned)inMsgParams[0]&(long unsigned)0x0ff;
	strVal.Format("%lu",longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);
#endif
}

void CDebugWinDlg::OnBnClickedOsccontrolWrite()
{
// "cp" command: set clks per fs
//	outMsgStr[0]=setOscCtrlCmdStr[0]; 
//	outMsgStr[1]=setOscCtrlCmdStr[1]; 

	charValueFromDlgItem(IDC_OSC1_CONTROL1,outMsgStr+2);
	charValueFromDlgItem(IDC_OSC1_CONTROL2,outMsgStr+3);
	charValueFromDlgItem(IDC_OSC1_CONTROL3,outMsgStr+4);
	charValueFromDlgItem(IDC_OSC1_NCOUNT1,outMsgStr+5);
	charValueFromDlgItem(IDC_OSC1_NCOUNT2,outMsgStr+6);
	charValueFromDlgItem(IDC_OSC1_NCOUNT3,outMsgStr+7);
	charValueFromDlgItem(IDC_OSC1_RCOUNT1,outMsgStr+8);
	charValueFromDlgItem(IDC_OSC1_RCOUNT2,outMsgStr+9);
	charValueFromDlgItem(IDC_OSC1_RCOUNT3,outMsgStr+10);

	charValueFromDlgItem(IDC_OSC2_CONTROL1,outMsgStr+11);
	charValueFromDlgItem(IDC_OSC2_CONTROL2,outMsgStr+12);
	charValueFromDlgItem(IDC_OSC2_CONTROL3,outMsgStr+13);
	charValueFromDlgItem(IDC_OSC2_NCOUNT1,outMsgStr+14);
	charValueFromDlgItem(IDC_OSC2_NCOUNT2,outMsgStr+15);
	charValueFromDlgItem(IDC_OSC2_NCOUNT3,outMsgStr+16);
	charValueFromDlgItem(IDC_OSC2_RCOUNT1,outMsgStr+17);
	charValueFromDlgItem(IDC_OSC2_RCOUNT2,outMsgStr+18);
	charValueFromDlgItem(IDC_OSC2_RCOUNT3,outMsgStr+19);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CP Msg (Set Osc1&2 Ctrl)");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_SET_OSC_CTRL_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_SET_OSC_CTRL_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input %c%c Msg (should be SM)",(int)InputReport[0],(int)InputReport[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif
}

void CDebugWinDlg::OnBnClickedOsccontrolRead()
{
//	CString strVal;
//	long unsigned longVal;

// "cq" command: read Oscilator Control
//	outMsgStr[0]=readOscCtrlCmdStr[0];
//	outMsgStr[1]=readOscCtrlCmdStr[1]; 

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CQ Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_READ_OSC_CTRL_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_READ_OSC_CTRL_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SQ Msg: dev bytes:%d %d",(int)inMsgParams[0],inMsgParams[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif

	charValueToDlgItem(IDC_OSC1_CONTROL1,inMsgParams);
	charValueToDlgItem(IDC_OSC1_CONTROL2,inMsgParams+1);
	charValueToDlgItem(IDC_OSC1_CONTROL3,inMsgParams+2);
	charValueToDlgItem(IDC_OSC1_NCOUNT1,inMsgParams+3);
	charValueToDlgItem(IDC_OSC1_NCOUNT2,inMsgParams+4);
	charValueToDlgItem(IDC_OSC1_NCOUNT3,inMsgParams+5);
	charValueToDlgItem(IDC_OSC1_RCOUNT1,inMsgParams+6);
	charValueToDlgItem(IDC_OSC1_RCOUNT2,inMsgParams+7);
	charValueToDlgItem(IDC_OSC1_RCOUNT3,inMsgParams+8);

	charValueToDlgItem(IDC_OSC2_CONTROL1,inMsgParams+9);
	charValueToDlgItem(IDC_OSC2_CONTROL2,inMsgParams+10);
	charValueToDlgItem(IDC_OSC2_CONTROL3,inMsgParams+11);
	charValueToDlgItem(IDC_OSC2_NCOUNT1,inMsgParams+12);
	charValueToDlgItem(IDC_OSC2_NCOUNT2,inMsgParams+13);
	charValueToDlgItem(IDC_OSC2_NCOUNT3,inMsgParams+14);
	charValueToDlgItem(IDC_OSC2_RCOUNT1,inMsgParams+15);
	charValueToDlgItem(IDC_OSC2_RCOUNT2,inMsgParams+16);
	charValueToDlgItem(IDC_OSC2_RCOUNT3,inMsgParams+17);
#endif
}

void CDebugWinDlg::charValueFromDlgItem(int dialogID,char *p_outMsgStr) {
	long unsigned longVal;
	CString strVal;
	CEdit* editControl = (CEdit*) GetDlgItem(dialogID);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to long
	p_outMsgStr[0]=(char)(longVal&(long unsigned)0x0ff);
	if (longVal<16) {
		strVal.Format("0x0%1x",(int)longVal); //Set string to what parameter ended up
	} else {
		strVal.Format("0x%2x",(int)longVal&(int)0x0ff); //Set string to what parameter ended up
	}
	editControl->SetWindowText(strVal);
}

void CDebugWinDlg::charValueToDlgItem(int dialogID,char *p_outMsgStr) {
	long unsigned longVal;
	CString strVal;
	CEdit* editControl = (CEdit*) GetDlgItem(dialogID);
//	editControl->GetWindowText(strVal);
	longVal = p_outMsgStr[0]; //convert to long (why? I don't know---historical i guess)
	longVal&=(long unsigned)0x0ff; //make sure it's a 8 bit value
	if (longVal<16) {
		strVal.Format("0x0%1x",(int)longVal); //Set string to what parameter ended up
	} else {
	strVal.Format("0x%2x",(int)longVal&(int)0x0ff); //Set string to what parameter ended up
	}
	editControl->SetWindowText(strVal);
}
void CDebugWinDlg::threeByteValueFromDlgItem(int dialogID,unsigned long *longVal) {
	long unsigned longVal2;
	CString strVal;
	CEdit* editControl = (CEdit*) GetDlgItem(dialogID);
	editControl->GetWindowText(strVal);
	longVal2 = strtol(strVal, 0, 0); //convert to long
	if (longVal2>0x0fff) longVal2=0x0fff;
//	longVal2 =(char)(longVal2&(long unsigned)0x0fff);
	if (longVal2<0x00f) {
		strVal.Format("0x00%1lx",longVal2); //Set string to what parameter ended up
	} else if (longVal2<0x0ff) {
		strVal.Format("0x0%2lx",longVal2); //Set string to what parameter ended up
	} else  {
		strVal.Format("0x%3lx",longVal2); //Set string to what parameter ended up
	}
	editControl->SetWindowText(strVal);
	*longVal = longVal2;
}

void CDebugWinDlg::OnBnClickedRestoreOsc()
{
//	outMsgStr[0]=restoreOscCtrlCmdStr[0];
//	outMsgStr[1]=restoreOscCtrlCmdStr[1]; 

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CR Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_RESTORE_OSC_CTRL_LEN);


#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_READ_OSC_CTRL_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SQ Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

	charValueToDlgItem(IDC_OSC1_CONTROL1,inMsgParams);
	charValueToDlgItem(IDC_OSC1_CONTROL2,inMsgParams+1);
	charValueToDlgItem(IDC_OSC1_CONTROL3,inMsgParams+2);
	charValueToDlgItem(IDC_OSC1_NCOUNT1,inMsgParams+3);
	charValueToDlgItem(IDC_OSC1_NCOUNT2,inMsgParams+4);
	charValueToDlgItem(IDC_OSC1_NCOUNT3,inMsgParams+5);
	charValueToDlgItem(IDC_OSC1_RCOUNT1,inMsgParams+6);
	charValueToDlgItem(IDC_OSC1_RCOUNT2,inMsgParams+7);
	charValueToDlgItem(IDC_OSC1_RCOUNT3,inMsgParams+8);

	charValueToDlgItem(IDC_OSC2_CONTROL1,inMsgParams+9);
	charValueToDlgItem(IDC_OSC2_CONTROL2,inMsgParams+10);
	charValueToDlgItem(IDC_OSC2_CONTROL3,inMsgParams+11);
	charValueToDlgItem(IDC_OSC2_NCOUNT1,inMsgParams+12);
	charValueToDlgItem(IDC_OSC2_NCOUNT2,inMsgParams+13);
	charValueToDlgItem(IDC_OSC2_NCOUNT3,inMsgParams+14);
	charValueToDlgItem(IDC_OSC2_RCOUNT1,inMsgParams+15);
	charValueToDlgItem(IDC_OSC2_RCOUNT2,inMsgParams+16);
	charValueToDlgItem(IDC_OSC2_RCOUNT3,inMsgParams+17);
#endif
}

//extern void sigProcCmd();

//int band_sw1_flag=0;
//int band_sw1_flag=0;

void CDebugWinDlg::OnBnClickedBandSw0()
{
/*	if (m_band_sw0->GetCheck()==BST_CHECKED) {
		m_band_sw0->SetCheck(BST_UNCHECKED);
	}
	else {
		m_band_sw0->SetCheck(BST_CHECKED);
	}*/
	setBandSWCmd();
}

void CDebugWinDlg::OnBnClickedBandSw1() {
/*	if (m_band_sw1->GetCheck()==BST_CHECKED) {
		m_band_sw1->SetCheck(BST_UNCHECKED);
	} else { 
		m_band_sw1->SetCheck(BST_CHECKED);
	}*/
	setBandSWCmd();
}

void CDebugWinDlg::setBandSWCmd() {
//	outMsgStr[0]=setBandSWCmdStr[0]; //"cv" command
//	outMsgStr[1]=setBandSWCmdStr[1]; // "cv" command
	outMsgStr[2]=0;


	if (m_band_sw0->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_BAND_SW0_MASK;
	if (m_band_sw1->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_BAND_SW1_MASK;


#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("--> Output Set Band SW Msg: Byte=0x%2x", (int)outMsgStr[2]&(int)0x0ff);
	CDebugWinDlg::DisplayData2(msgString);
#endif
//	CMainDlg::writeCmd(CMD_SET_BAND_SW_LEN);


#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_BAND_SW_LEN);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("<-- Input Band SW Resp: Byte=0x%2x",(int)inMsgParams[0]&(int)0x0ff);
	CDebugWinDlg::DisplayData2(msgString);
#endif

// Update band sw checks
	if (inMsgParams[0]&SIGPROC_BAND_SW0_MASK) m_band_sw0->SetCheck(BST_CHECKED);
	else m_band_sw0->SetCheck(BST_UNCHECKED);
	if (inMsgParams[0]&SIGPROC_BAND_SW1_MASK) m_band_sw1->SetCheck(BST_CHECKED);
	else m_band_sw1->SetCheck(BST_UNCHECKED);
#endif

}

void CDebugWinDlg::readBandSWCmd() {
	CButton* m_band_sw;	
//	outMsgStr[0]=readBandSWCmdStr[0]; //"cz" command
//	outMsgStr[1]=readBandSWCmdStr[1]; // "cz" command
	outMsgStr[2]=0;

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output Read BandSW ");
	CDebugWinDlg::DisplayData2(msgString);
#endif
//	CMainDlg::writeCmd(CMD_READ_BAND_SW_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_BAND_SW_LEN);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SV Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif

// Update band sw checks
	m_band_sw = (CButton*) GetDlgItem(IDC_BAND_SW0);
	if (inMsgParams[0]&SIGPROC_BAND_SW0_MASK) m_band_sw->SetCheck(BST_CHECKED);
	else m_band_sw->SetCheck(BST_UNCHECKED);
	m_band_sw = (CButton*) GetDlgItem(IDC_BAND_SW1);
	if (inMsgParams[0]&SIGPROC_BAND_SW1_MASK) m_band_sw->SetCheck(BST_CHECKED);
	else m_band_sw->SetCheck(BST_UNCHECKED);
#endif

}
/*
void CDebugWinDlg::OnNMReleasedcaptureSquelch(NMHDR *pNMHDR, LRESULT *pResult)
{
	setSquelchCmd();
}
*/
void CDebugWinDlg::setSquelchCmd() {
//	char value;
//	value=(char)(255-squelchSlider->GetPos());
//	outMsgStr[0]=setSquelchCmdStr[0]; //"cx" command
//	outMsgStr[1]=setSquelchCmdStr[1]; // "cx" command
//	outMsgStr[2]=value;

	CString intString;
	m_squelchOnValue->GetWindowText(intString); 
	unsigned long i = strtol(intString,0,0); //convert text to long (couldn't find 'int' version of function)
	if (i>255) i=255;
	outMsgStr[2]=(char)i;
	m_squelchOffValue->GetWindowText(intString); 
	i = strtol(intString,0,0);
	if (i>255) i=255;
	outMsgStr[3]=(char)i;
	m_hysterOnValue->GetWindowText(intString); 
	i = strtol(intString,0,0);
	if (i>255) i=255;
	outMsgStr[4]=(char)i;
	m_hysterOffValue->GetWindowText(intString); 
	i = strtol(intString,0,0);
	if (i>255) i=255;
	outMsgStr[5]=(char)i;

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CX Msg: Squelch Value=%2x", (0x0ff&outMsgStr[2]));
	CDebugWinDlg::DisplayData2(msgString);
#endif

//	CMainDlg::writeCmd(CMD_SET_SQUELCH_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_SQUELCH_LEN);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SX Msg: Squelch=%2x",0x0ff&inMsgParams[0]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
// Set slider to value that it ended up
//	squelchSlider->SetPos((int)255-(((int)0x0ff)&((int)inMsgParams[0])));

	sprintf(freqValChars,"%3d",(int)inMsgParams[0]&(int)0x0ff);
	m_squelchOnValue->SetWindowTextA(freqValChars);
	sprintf(freqValChars,"%3d",(int)inMsgParams[1]&(int)0x0ff);
	m_squelchOffValue->SetWindowTextA(freqValChars);
	sprintf(freqValChars,"%3d",(int)inMsgParams[2]&(int)0x0ff);
	m_hysterOnValue->SetWindowTextA(freqValChars);
	sprintf(freqValChars,"%3d",(int)inMsgParams[3]&(int)0x0ff);
	m_hysterOffValue->SetWindowTextA(freqValChars);
#endif
}

void CDebugWinDlg::readSquelchCmd() {
	char value;
//	outMsgStr[0]=readSquelchCmdStr[0]; //"cz" command
//	outMsgStr[1]=readSquelchCmdStr[1]; // "cz" command

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Output CZ Msg");
	CDebugWinDlg::DisplayData2(msgString);
#endif
//	CMainDlg::writeCmd(CMD_READ_SQUELCH_LEN);

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_SQUELCH_LEN);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input SX Msg: Squelch=%2x",0x0ff&inMsgParams[0]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
// Set slider to value that it ended up
//	squelchSlider->SetPos((int)255-(((int)0x0ff)&((int)inMsgParams[0])));
	sprintf(freqValChars,"%3d",(int)inMsgParams[0]&(int)0x0ff);
	m_squelchOnValue->SetWindowTextA(freqValChars);
	sprintf(freqValChars,"%3d",(int)inMsgParams[1]&(int)0x0ff);
	m_squelchOffValue->SetWindowTextA(freqValChars);
	sprintf(freqValChars,"%3d",(int)inMsgParams[2]&(int)0x0ff);
	m_hysterOnValue->SetWindowTextA(freqValChars);
	sprintf(freqValChars,"%3d",(int)inMsgParams[3]&(int)0x0ff);
	m_hysterOffValue->SetWindowTextA(freqValChars);
#endif
}
int numDisplayStringsXX=0;
#define MAX_NUM_DISPLAY_STRINGS_XX 100

//CEdit *displayMsgs;

extern	int debugWinFlag;

void CDebugWinDlg::DisplayData(CString cstrDataToDisplay) { // Always displays 
	USHORT	Index;
	if (debugWinFlag==0) return; // Dont do if debug window not created
	if (numDisplayStringsXX>MAX_NUM_DISPLAY_STRINGS_XX) {
		displayMsgs->DeleteString(0); // delete first entry if at maximum length
	} else {
		numDisplayStringsXX++;
	}
	Index=displayMsgs->InsertString(-1,(LPCTSTR)cstrDataToDisplay); // insert the string
	displayMsgs->SetCurSel( Index );
	displayMsgs->SetCurSel( -1 ); 
}

void CDebugWinDlg::DisplayData2(CString cstrDataToDisplay) // Only displays if print flag set
{
	USHORT	Index;
	
	if (debugWinFlag==0) return;
	if (printMsgsFlag==FALSE) {
		return;
	}

	if (numDisplayStringsXX>MAX_NUM_DISPLAY_STRINGS_XX) {
		displayMsgs->DeleteString(0);
	} else {
		numDisplayStringsXX++;
	}
	Index=displayMsgs->InsertString(-1,(LPCTSTR)cstrDataToDisplay);
	displayMsgs->SetCurSel( Index );
	displayMsgs->SetCurSel( -1 ); // set to one line before end
}


afx_msg void CDebugWinDlg::OnClose() {
	debugWinFlag=0;
	CDialog::OnClose();
}
void CDebugWinDlg::OnBnClickedContinuous()
{
	if (continuousFlag==FALSE) {
		continuousFlag=TRUE;
		continuousButton->SetWindowTextA("Pause");
	} else {
		continuousFlag=FALSE;
		continuousButton->SetWindowTextA("Continue");
	}

}


void CDebugWinDlg::OnBnClickedPrintMsgs()
{
	if (printMsgsFlag==FALSE) {
//		CMainDlg::SetTimer(ID_TIMER_CONTINUOUS, 10, NULL);
		printMsgsFlag=TRUE;
		printMsgsButton->SetWindowTextA("Stop Msg Print");
	} else {
//		CMainDlg::KillTimer(ID_TIMER_CONTINUOUS);
		printMsgsFlag=FALSE;
		printMsgsButton->SetWindowTextA("Print Msgs");
	}
}
//extern int SyncInputAndOutput();

void CDebugWinDlg::OnBnClickedResyncmsgs()
{
//	SyncInputAndOutput();
}
void CDebugWinDlg::OnBnClickedUpdateBandsw()
{
	readBandSWCmd();
}

void CDebugWinDlg::OnBnClickedReadSquelch() {
	readSquelchCmd();
}



void CDebugWinDlg::OnBnClickedUpdateCustomerid()
{
	threeByteValueFromDlgItem(IDC_STINGER_CUSTOMERID,&customerID);
}
extern CDialog *pDebugAGCWinDlg;
extern int debugAGCWinFlag;
void CDebugWinDlg::OnBnClickedDebugAgcWin2() {
	pDebugAGCWinDlg = new CDebugAGCWinDlg();
	BOOL ret=pDebugAGCWinDlg->Create(IDD_DEBUGAGCWINDOW,0);
	if(!ret)   //Create failed.
		AfxMessageBox("Error creating AGC Dialog");
    pDebugAGCWinDlg->ShowWindow(SW_SHOW);
	debugAGCWinFlag=1;
}

/* Added this stuff before Christmas... hope it works */
/* extern CDialog *pDebugOscWinDlg;
extern int debugAGCOscFlag;
void CDebugWinDlg::OnBnClickedDebugAgcWin2() {
	pDebugAGCWinDlg = new CDebugAGCWinDlg();
	BOOL ret=pDebugAGCWinDlg->Create(IDD_DEBUGAGCWINDOW,0);
	if(!ret)   //Create failed.
		AfxMessageBox("Error creating AGC Dialog");
  pDebugAGCWinDlg->ShowWindow(SW_SHOW);
	debugAGCWinFlag=1;
}
*/

//
//void CDebugWinDlg::OnLbnSelchangeSquelchValueTxt()
//{
//	// TODO: Add your control notification handler code here
//}

void CDebugWinDlg::OnBnClickedWriteSquelch() {
	setSquelchCmd();
}

void CDebugWinDlg::OnEnChangeSppaddr()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CDebugWinDlg::OnEnChangeSppdata()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CDebugWinDlg::OnBnClickedEepromPic1Write()
{
	CString strVal;
	double doubleVal;

	outMsgStr[0]=CMD_EEPROM_PIC1_SET_1; //"rc" command
	outMsgStr[1]=CMD_EEPROM_PIC1_SET_2; // "rc" command

	CEdit* editControl = (CEdit*) GetDlgItem(IDC_EEPROM_PIC1_ADDR);
	editControl->GetWindowText(strVal);
	doubleVal = strtod(strVal, 0); //convert to float
	outMsgStr[2]=(char)(doubleVal);
	strVal.Format("%d",(int)outMsgStr[2]); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

	charValueFromDlgItem(IDC_EEPROM_PIC1_DATA,outMsgStr+3);

	CMainDlg::writeCmd(CMD_EEPROM_PIC1_SET_LEN);

}

void CDebugWinDlg::OnBnClickedEepromPic1Read()
{
	CString strVal;
	double doubleVal;
	CEdit* editControl = (CEdit*) GetDlgItem(IDC_EEPROM_PIC1_ADDR);

	outMsgStr[0]=CMD_EEPROM_PIC1_REQ_1; //"rb" command
	outMsgStr[1]=CMD_EEPROM_PIC1_REQ_2; // "rb" command

	editControl->GetWindowText(strVal);
	doubleVal = strtod(strVal, 0); //convert to float
	outMsgStr[2]=(char)(doubleVal);

	strVal.Format("%d",outMsgStr[2]); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);

	CMainDlg::writeCmd(CMD_EEPROM_PIC1_REQ_LEN);
}
