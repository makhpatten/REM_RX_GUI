#include "resource.h"


class CStealthRecSpecialWinDlg : public CDialog
{
public:
	CStealthRecSpecialWinDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_SPECIALSTINGERCMDWIN};
	//}}AFX_DATA

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	virtual void OnOK();

//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	afx_msg void OnStealthRecSourceMic();
	afx_msg void OnStealthRecSourceAux();
	afx_msg void OnStealthRecSourceLine();

	afx_msg void OnStealthRecClearLog();


	afx_msg void OnStealthRecGetVolume();
	afx_msg void OnStealthRecGetWorkStatus();
	afx_msg void OnStealthRecGetNumFiles();
	afx_msg void OnStealthRecGetSoundFile();
	afx_msg void OnStealthRecGetConnStatus();
	afx_msg void OnStealthRecGetSpace();

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedStealthrecDeletefile();
public:
	afx_msg void OnBnClickedStealthrecFastfwd();
public:
	afx_msg void OnBnClickedStealthrecFastbkwd();
};

