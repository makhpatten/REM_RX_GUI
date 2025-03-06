#include "resource.h"
extern int enterPasswordWinFlag;


class CSpecialStingerCmdDlg : public CDialog
{
public:
	CSpecialStingerCmdDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_STEALTHRECSPECIALWIN};
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

	afx_msg void OnBnClickedEnterStingerCmd();

	//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void OnClose();
};

