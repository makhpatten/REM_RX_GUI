#include "afxwin.h"
#include "afxcmn.h"
class CDebugWinDlg : public CDialog
{
public:
	CDebugWinDlg();

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_DEBUGWINDOW };
	//}}AFX_DATA

public:
//	CStatic m_scanArea;
//	int mhpxxx;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedScanok();
//	void getStartStopStepFreqs();
//	void drawGraphTrace();
//	CDC *scanDrawingContext;
//	void setIndicatorLight(int, int);

public:
//	CEdit m_startFreqTxt;
//	CEdit m_stopFreqTxt;
//	CEdit m_stepFreqTxt;
//	ULONG startFreqKHz;
//	ULONG stopFreqKHz;
//	ULONG stepFreqKHz;

public:
	void readSDRAMAudioCmd();
public:
	static void FPGARegUpdate();
	static void EepromPic1Update();
public:
	afx_msg void OnBnClickedSppwrite();
public:
	afx_msg void OnBnClickedSppread();
public:
	CEdit m_deviation;
public:
	CEdit m_centerFreq;
public:
	CEdit m_deltaPhase;
public:
	CEdit m_clocksPerFs;
public:
	afx_msg void OnBnClickedDeviationwrite();
public:
	afx_msg void OnBnClickedDeviationread();
public:
	afx_msg void OnBnClickedCenterfreqwrite();
public:
	afx_msg void OnBnClickedCenterfreqread();
public:
	afx_msg void OnBnClickedDeltaphasewrite();
public:
	afx_msg void OnBnClickedDeltaphaseread4();
public:
	afx_msg void OnBnClickedClksperfswrite();
public:
	afx_msg void OnBnClickedClksperfsread();
public:
	afx_msg void OnBnClickedBERRead();
public:
	afx_msg void OnBnClickedOsccontrolWrite();
public:
	afx_msg void OnBnClickedOsccontrolRead();
	void charValueFromDlgItem(int,char*);
	void charValueToDlgItem(int,char*);
	void threeByteValueFromDlgItem(int,unsigned long*);

public:
	afx_msg void OnBnClickedResyncmsgs();
public:
	afx_msg void OnBnClickedRestoreOsc();
public:
//	CButton m_band_sw1;
public:
//	CButton m_band_sw0;
public:
	afx_msg void OnBnClickedBandSw1();
	void   setBandSWCmd();
	void   readBandSWCmd();
public:
	afx_msg void OnBnClickedBandSw0();
public:
//	CSliderCtrl m_squelch;
	static void DisplayData(CString); // this one always prints
	static void DisplayData2(CString); // this one prints only if print flag is set
	afx_msg void OnClose();
	afx_msg void OnBnClickedContinuous();



//public:
//	afx_msg void OnNMReleasedcaptureSquelch(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedPrintMsgs();
public:
	afx_msg void OnBnClickedUpdateBandsw();
	void setSquelchCmd();
	void readSquelchCmd();
public:
	afx_msg void OnBnClickedReadSquelch();
	afx_msg void OnBnClickedWriteSquelch();

public:
	afx_msg void OnBnClickedUpdateCustomerid();
public:
	afx_msg void OnBnClickedDebugAgcWin2();
public:
//	afx_msg void OnLbnSelchangeSquelchValueTxt();
public:
	afx_msg void OnEnChangeSppaddr();
public:
	afx_msg void OnEnChangeSppdata();
public:
	afx_msg void OnBnClickedEepromPic1Write();
public:
	afx_msg void OnBnClickedEepromPic1Read();
};


