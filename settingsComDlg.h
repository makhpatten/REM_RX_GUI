#include "resource.h"

class CSettingsComDlg : public CDialog
{
public:
	CSettingsComDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CToneWarningDlg)
	enum { IDD = IDD_SETTINGS_COM };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToneWarningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnBnClickedSettingsComClose();
	//}}AFX_VIRTUAL

// Implementation
//protected:
public:
	//{{AFX_MSG(CToneWarningDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangePortNumber();
	afx_msg void OnCbnSelchangeIPAddress();
	afx_msg void OnCbnSelchangeTelnetPort();
public:
	afx_msg void OnBnClickedBaud300();
public:
	afx_msg void OnBnClickedBaud9600();
public:
	afx_msg void OnBnClickedPortTypeTCPIP();
public:
	afx_msg void OnBnClickedPortTypeRS232();
public:
	afx_msg void OnBnClickedDPI96();
public:
	afx_msg void OnBnClickedDPI120();


public:
	afx_msg void OnCbnSelchangeComPortNumber();
public:
	afx_msg void OnBnClickedLaunchComPortEnum();
public:
	afx_msg void OnCbnCloseupComPortNumber2();
public:
	afx_msg void OnCbnEditchangeComPortNumber2();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnOK();


};
/*
CSettingsComDlg::CSettingsComDlg(CWnd*) : CDialog(CSettingsComDlg::IDD)
{
	//{{AFX_DATA_INIT(CToneWarningDlg)
	//}}AFX_DATA_INIT
}
*/
/*
void CSettingsComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToneWarningDlg)
	//}}AFX_DATA_MAP
}*/
/*
BEGIN_MESSAGE_MAP(CSettingsComDlg, CDialog)
	//{{AFX_MSG_MAP(CToneWarningDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

*/

class CSettingsMiscDlg : public CDialog
{
public:
	CSettingsMiscDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CToneWarningDlg)
	enum { IDD = IDD_SETTINGS_MISC };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToneWarningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnBnClickedSettingsMiscClose();
	//}}AFX_VIRTUAL

// Implementation
//protected:
public:
	//{{AFX_MSG(CToneWarningDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern int portType;
