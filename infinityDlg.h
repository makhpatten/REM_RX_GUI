// MainDlg.h : header file
//

#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_MainDLG_H__0B2AAA84_F5A9_11D3_9F47_0050048108EA__INCLUDED_)
#define AFX_MainDLG_H__0B2AAA84_F5A9_11D3_9F47_0050048108EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CDialog
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_MAIN_DIALOG };
//	CEdit	m_VendorID;
//	CEdit	m_ProductID;

//	CButton	m_Continuous;
//	CButton	m_cbutAutoIncrement;
//	CComboBox	m_cboByteToSend1;
//	CComboBox	m_cboByteToSend0;
//	CListBox	m_BytesReceived;
//#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//#endif
//	CButton	m_txPower;
//	BOOL	m_AutoIncrement;
//	CString	m_ResultsString;
//	CString	m_strBytesReceived;
//	CString	m_strByteToSend0;
//	CString	m_strByteToSend1;
//	int		m_ReportType;
//	BOOL	m_UseControlTransfersOnly;
//	CString	m_ProductIDString;
//	CString	m_VendorIDString;
//	CString	m_InputReportBufferSize;
	int		m_ReportType;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedTxPower();
	afx_msg void OnBnClickedchannelswindow();
	afx_msg	BOOL CMainDlg::PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedscanwindow();
	afx_msg void OnChangeResults();
//	afx_msg void OnContinuous();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void On_cmdFindMyDevice();
	afx_msg void CMainDlg::OnPaint();
//	afx_msg void OnChange_txtVendorID();
//	afx_msg void OnChange_txtProductID();
//	afx_msg void On_optExchangeInputAndOutputReports();
//	afx_msg void On_optExchangeFeatureReports();
//	afx_msg void On_chkUseControlTransfersOnly();
//	afx_msg void OnChange_txtInputReportBufferSize();
//	afx_msg void On_cmdInputReportBufferSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL DeviceNameMatch(LPARAM lParam);
	bool FindTheHID();
	LRESULT Main_OnDeviceChange(WPARAM wParam, LPARAM lParam);
	static void CloseHandles();
	void DisplayCurrentTime();
	void DisplayFeatureReport();
	void DisplayInputReport();
	void DisplayLastError(CString Operation);
//	void DisplayReceivedData(char ReceivedByte);
	void GetDeviceCapabilities();
	void PrepareForOverlappedTransfer();
	void ReadAndWriteToDevice();
	void ReadInputReport();
	void RegisterForDeviceNotifications();
	void WriteOutputReport();
	void readFreqCmd();
//	void setFilterCmd();
	void readOperCmd();
	void statusReqCmd();
	void cardStatusReqCmd();
	void readTxFreqCmd();
	void setTxFreqCmd();
	void readFreqFile();
    void statusRespUpdateControls();
	void configRespUpdateControls();
	void cardStatusRespUpdateControls();
	void recordStatusRespUpdateControls();
	void nextFileNameUpdate();
	void txFreqUpdate();
    void txStatusUpdate();

//	afx_msg void OnPaint();
	void channelScanCmd();
	void playbackStatusCmd();
	void recordModeSetCmd();

public:
//	afx_msg void OnEnChangetxtinputreportbuffersize2();
//	static void CDebugWinDlg::DisplayData2(CString cstrDataToDisplay);
	static void ScrollToBottomOfListBox(USHORT idx);
	void static writeCmd(int x);
	static void writeCmdUSB(int x);
	static void writeCmdCOM(int x);
	static void playbackStartCmd();
	int static readResp(int);
	void sigProcSet();
	void sigProcReq();
	void txStatusSet();
	void txStatusReq();
	void timeReqCmd();
	void dateReqCmd();
	void playbackUpdate();
	void miscInfoUpdate();
	static void setFreqOperCmd();
	void configReqCmd();
	void updatePlaybackWindow();

// new functions for RS232 version
	void static setCOMStatus(int); // new for RS232 version
	void blankMainDisplayIndicators();
	void readDataFromComPort(); // new for RS232 version
	void readDataFromUSB();
	void displayRemoteAGCResp(); // new for RS232 version
	void displayLocalAGCResp(); // new for RS232 version
	void processMsg(); // new for RS232 version
//	void displaySDRAMAudioResp(); // new for RS232 version
	void displayDeviationResp();  // new for RS232 version
	void displayFreqResp();  // new for RS232 version
//	void displaySDRamAudioResp();

public:
//	CEdit mhp_testvar;
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CSliderCtrl m_FilterSelect;
public:
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	int m_deviceAttached;
public:
//	CButton m_deviceAttached;
public:
	afx_msg void OnNMReleasedcaptureFreqselect(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnEnChangeEdit1();
public:
//	afx_msg void OnEnChangetxtfreqvalue();
//public:
//	CEdit m_txtFreqValue;
public:
	afx_msg void OnBnClickedSetfreq();
public:
	afx_msg void OnBnClickedLoadfreqs();
public:
	afx_msg void OnBnClickedSavefreqs();
/*public:
	afx_msg void OnBnClickedNoiseReduce();*/
public:
	afx_msg void OnBnClickedNomute();
public:
	afx_msg void OnBnClickedHdphone();
public:
	afx_msg void OnBnClickedAnaloghdphone();
public:
	afx_msg void OnBnClickedCaltone();
	static void insertTextIntoFreqButton(int,char*);
	afx_msg void OnBnClickedAudioSetupWin();

public:
	int m_Audio;
public:
	afx_msg void OnBnClickedfreqval1();
public:
	afx_msg void OnBnClickedfreqval2();
public:
	afx_msg void OnBnClickedfreqval3();
public:
	afx_msg void OnBnClickedfreqval4();
public:
	afx_msg void OnBnClickedfreqval5();
public:
	afx_msg void OnBnClickedfreqval6();
public:
	afx_msg void OnBnClickedfreqval7();
public:
	afx_msg void OnBnClickedfreqval8();
//protected:
//	CDialog *pStingerWinDlg;
public:
	afx_msg void OnBnClickedNoiseReduce();
public:
	afx_msg void OnBnClickedRangeExtend();
public:
//	afx_msg void OnBnClickedMono1();
public:
	afx_msg void OnBnClickedStereo1();
public:
	CProgressCtrl m_antennaA;
	CProgressCtrl m_antennaB;
	CProgressCtrl m_leftAudio;
	CProgressCtrl m_rightAudio;

public:
//	CButton m_preemphasis;
	CButton m_declick;

public:
//	CButton m_agcLocal;
//	CButton m_agcRemote;
//	CButton m_ancRemote;
public:
//	CButton m_txFm;
//	CButton m_txFmEnc;
//	CButton m_txDst;
public:
	afx_msg void OnBnClickedPreemphasis();
public:
	afx_msg void OnBnClickedAgcRemote();
	afx_msg void OnBnClickedAgcLocal();
public:
	afx_msg void OnBnClickedAncRemote();
public:
	afx_msg void OnBnClickedStingerwinbutton();
//public:
//	CBitmapButton m_usbIndicator;
public:
//	CStatic m_usbStatus;
public:
private:
	CBitmap Bmp1, Bmp2;

//public:
//	CStatic m_usbPictureMHP;
public:
//	CButton m_continuous;
//	afx_msg void OnBnClickedContinuous();
public:
	CProgressCtrl m_SDMemUsedBargraph;
	CProgressCtrl m_RAMMemUsedBargraph;
	CListBox m_serialNumber;
//public:
//	CProgressCtrl m_supplyVoltage;
public:
	CListBox m_voltageReadout;
public:
//	CStatic m_anotherPic;
public:
	CListBox m_SDMemTotalTxt;
public:
	CListBox m_SDMemUsedTxt;
public:
	afx_msg void OnStnClickedUsbstatus();
	void static setIndicatorLight(int ,int, CDC*);
//	void updateIndicatorLights();

public:
	afx_msg void OnEnChangeFmtransmitfreq();
public:
//	CEdit m_fmTxFreq;
public:
	void updateStatusResponseParams(char,char);
	void static sigProcUpdate();
	void static timeUpdate();
	void static dateUpdate();

	afx_msg void OnBnClickedTxsetfreq();
	static void setUSBStatus(int);
//	static void setMsgStatus(int);
	CListBox m_timeRemain;
	CListBox m_timeUsed;
	afx_msg void OnEnUpdateFmtransmitfreq();
	CListBox m_antAText;
	CListBox m_antBText;
	CListBox *m_rawSubchBytes;
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedSwapLr();
	afx_msg void OnBnClickedMonoOn();
	afx_msg void OnBnClickedCalTone();
	CButton m_squelchOn;
	CButton m_calTone;
	afx_msg void OnBnClickedSquelchoff();
	afx_msg void OnBnClickedCalToneNotLockedOn();
	afx_msg void OnBnClickedCalToneNotLockedOff();
//	afx_msg void OnBnClickedCaltoneOn();
	CButton m_calToneCtrl;
	afx_msg void OnBnClickedSquelchOn();
//public:
//	CButton m_stingerWinButton;
public:
	afx_msg void OnBnClickedFilt400HzSharp();
	afx_msg void OnBnClickedFilt200HzVerySharp();
	afx_msg void OnBnClickedFilt400HzVerySharp();
	afx_msg void OnBnClickedFilt200HzSharp();
	afx_msg void OnBnClickedFilt200Hz();
	afx_msg void OnBnClickedFilt100Hz();
	afx_msg void OnBnClickedFiltFlat();
public:
	afx_msg void OnBnClickedStingerCmd();
	static void outputStingerCmd(int);
	static void updateStingerStatusLED();

public:
	afx_msg void OnBnClickedStingerOn();
	afx_msg void OnBnClickedStingerOff();
	afx_msg void OnBnClickedStingerAllOff();
public:
//	afx_msg void OnBnClickedSquelch();
public:
	afx_msg void OnBnClickedEditfilename();
	static void setFileNameCmd();
	void static readFileNameCmd();
	void recordStatusCmd();
	void miscInfoCmd();

//	CListBox m_nextFileNameText;
	CListBox m_sdErrorText;
	void bytesPerClusterCmd();
public:
	afx_msg void OnBnClickedDeclick();
public:
	CStatic m_memUsedText;
//	CStatic m_timeStringText;
//	CStatic m_dateStringText;
public:
	afx_msg void OnNMCustomdrawFreqselect(NMHDR *pNMHDR, LRESULT *pResult);
	void OnMenuProcessFile();
	void OnMenuPassword();
	void OnMenuSpecialStingerCmd();
	void OnMenuStealthRecSpecialFunctions();
public:
	afx_msg void OnLbnSelchangeFilename();
public:
	afx_msg void OnLbnSelchangeVoltageReadoutText();
public:
	afx_msg void OnEnChangeFreqValText();
public:
	afx_msg void OnBnClickedTransmitterFm();
public:
	afx_msg void OnBnClickedTransmitterFmenc();
public:
	afx_msg void OnBnClickedTransmitterDst();
public:
	afx_msg void OnNMCustomdrawLeftaudio(NMHDR *pNMHDR, LRESULT *pResult);

public:
	afx_msg void OnNMCustomdrawAntennaa(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedUseUsb();
public:
	afx_msg void OnBnClickedUseCom();
public:
	void processUSBResponse();

public:
	afx_msg void OnBnClickedTxRestoreDefault();
public:
//	afx_msg void OnOptionsRestoredefaultsettings();
public:
	afx_msg void OnNMCustomdrawRammemusedbargraph(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnLbnSelchangeSdmemtotal();

	afx_msg void OnSettingsAbout();
	afx_msg void OnSettingsPlayAudio();
	afx_msg void CMainDlg::OnBnClickedDbmMode();
	afx_msg void CMainDlg::OnSettingsCom();
	afx_msg void CMainDlg::OnMiscFullscaletone();
	afx_msg void CMainDlg::OnBnClickedRxPower();
	static afx_msg void CMainDlg::saveConfigToFile();
	afx_msg void CMainDlg::restoreConfigFromFile();
	afx_msg void CMainDlg::OnBnClickedLocalRec();
public:
//	afx_msg void OnOptionsDiagnostics();
public:
	afx_msg void OnWindowsRemoteplayer();
public:
	afx_msg void OnWindowsChannels();
public:
	afx_msg void OnWindowsScan();
public:
	afx_msg void OnStnClickedStMsgRcvdCount();
public:
	afx_msg void OnNMCustomdrawSdmemusedbargraph(NMHDR *pNMHDR, LRESULT *pResult);
	void enableSetOperCmdButtons(int);

public:
	afx_msg void OnStnClickedTimestring();
public:
	afx_msg void OnStnClickedDatestring();
public:
	afx_msg void OnLbnSelchangeSerialNum();
public:
	afx_msg void OnBnClickedCtlTxPwrLow();
public:
	afx_msg void OnBnClickedCtlTxPwrHi();
public:
	afx_msg void OnBnClickedSleeper2PwrHi();
public:
	afx_msg void OnBnClickedSleeper2PwrLow();
public:
	afx_msg void OnBnClickedPlaybackwinbutton();
public:
	afx_msg void OnLbnSelchangeSdErrorText();
public:
	afx_msg void OnBnClickedRecordmode();
	afx_msg void OnBnClickedOverwriteWhenFull();
public:
	afx_msg void OnBnClickedCtrlTxStereo();
public:
	afx_msg void OnBnClickedCtrlTxMonoL();
public:
	afx_msg void OnBnClickedCtrlTxMonoR();
public:
	afx_msg void OnBnClickedOffState();
public:
	afx_msg void OnBnClickedOnState();
public:
	afx_msg void OnAddresslistDeletecurrentaddress();
public:
	afx_msg void OnAddresslistDeletealladdresses();
public:
	afx_msg void OnBnClickedPlaybackModeLive();
public:
	afx_msg void OnBnClickedPlaybackStop();
public:
	afx_msg void OnBnClickedPlaybackStart();
public:
	afx_msg void OnStnClickedCardPresentMsg();
public:
	void setStealthRecordWindow();
public:
	afx_msg void OnModeSetstealthrecordmode();
	afx_msg void OnModeSetSleepermode();
	afx_msg void CMainDlg::InitStealthRecStatus();
	afx_msg void CMainDlg::OnStealthRecRecord();
	afx_msg void CMainDlg::OnStealthRecStop();
	afx_msg void CMainDlg::OnStealthRecPlay();
	afx_msg void CMainDlg::OnStealthRecLive();
	afx_msg void CMainDlg::OnStealthRecRewind();
	afx_msg void CMainDlg::OnStealthRecFF2End();
	afx_msg void CMainDlg::OnStealthRecRepeat();
	afx_msg void CMainDlg::OnStealthRecQual128Kbps();
	afx_msg void CMainDlg::OnStealthRecQual96Kbps();
	afx_msg void CMainDlg::OnStealthRecQual64Kbps();
	afx_msg void CMainDlg::OnStealthRecQual32Kbps();
	afx_msg void CMainDlg::OnStealthRecModeMono();
	afx_msg void CMainDlg::OnStealthRecModeStereo();
	afx_msg void CMainDlg::OnStealthRecCal();
	afx_msg void CMainDlg::OnStealthRecNow();
	afx_msg void CMainDlg::OnStealthRecVox();

public:
	afx_msg void OnStnClickedRecordStatusMsg();
public:
	afx_msg void OnLbnSelchangeRecFileNumText();
public:
	afx_msg void OnLbnDblclkRecFileNumText();
public:
	afx_msg void OnLbnSetfocusRecFileNumText();
public:
	afx_msg void OnLbnKillfocusRecFileNumText();
public:
	afx_msg void OnBnClickedDpi96();
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MainDLG_H__0B2AAA84_F5A9_11D3_9F47_0050048108EA__INCLUDED_)


