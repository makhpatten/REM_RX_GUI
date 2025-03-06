#include "afxwin.h"
class CScanDlg : public CDialog
{
public:
	CScanDlg();

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_SCANWINDOW };
	//}}AFX_DATA

public:
	CStatic m_scanArea;
	int mhpxxx;

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
	afx_msg void OnBnClickedScan();
	void getStartStopStepFreqs();
	static void drawGraphGrid();
	void drawGraphTrace();
	afx_msg void OnClose();
	afx_msg void OnBnClickedScanClose();
//	CDC *scanDrawingContext;
//	void setIndicatorLight(int, int);

public:
//	CEdit m_startFreqTxt;
//	CEdit m_stopFreqTxt;
//	CEdit m_stepFreqTxt;
	void freq24ValueFromDlgItem(int,char*);

//public:
//	CListBox m_scanFreqText2;
//public:
//	CStatic m_startText;

public:
	afx_msg void OnBnClickedClearscan();
	static void CScanDlg::plotSweepPoint();
};


