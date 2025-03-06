#include "afxwin.h"
#include "infinity.h"

class CStingerDlg : public CDialog
{
public:
	CStingerDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_STINGERWINDOW };
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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose( );
	virtual void OnOK();

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//afx_msg void OnBnClickedSanok();
//	void getStartStopStepFreqs();
//	void drawGraphTrace();
//	CDC *scanDrawingContext;
//	void setIndicatorLight(int, int);
//	void readStingerCmdFile();
public:
//	CEdit m_startFreqTxt;
//	CEdit m_stopFreqTxt;
//	CEdit m_stepFreqTxt;
//	ULONG startFreqKHz;
//	ULONG stopFreqKHz;
//	ULONG stepFreqKHz;

public:
	afx_msg void OnCbnSelchangeCombo5();
//public:
	afx_msg void OnCbnEditchangeStingerAddress();
public:
	afx_msg void OnCbnSelchangeStingerAddress();
//public:
//	afx_msg void OnBnClickedEnterAddress();
//public:
//	afx_msg void OnBnClickedAddressDelete();
public:
	afx_msg void OnBnClickedOffCmd();
public:
	afx_msg void OnBnClickedOnCmd();
//	void updateStingerStatusLED2();
	static void stingerRecordCmd(int);
//	afx_msg void OnClose();


public:
	afx_msg void OnBnClickedAutoOnEnable();
public:
	afx_msg void OnBnClickedStingerOn();
public:
	afx_msg void OnBnClickedStingerOff();
public:
	afx_msg void OnBnClickedStingerRecord();
public:
	afx_msg void OnBnClickedStingerRecClear();
public:
	afx_msg void OnBnClickedStingerViewrec();
public:
	afx_msg void OnBnClickedDogleashEnable();
public:
	afx_msg void OnBnClickedDogleashView();
public:
	afx_msg void OnBnClickedSetSystemClk();
private:
	afx_msg void OnBnClickedCancel();
//	afx_msg void OnBnClickedWaspAddressEnter();
	afx_msg void OnBnClickedWaspAddressDelete();
	afx_msg void OnBnClickedWaspSetSystemClk();
	afx_msg void OnBnClickedWaspDeleteAllAddresses();
};

#define STINGER_TX_SPECIFIC 0
#define STINGER_GENERIC 1
#define STINGER_SPECIAL 2

