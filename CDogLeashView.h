#include "infinity.h"
/////////////////////////////////////////////////////////////////////////////
// CDogleashCmdDlg dialog

class CDogleashCmdDlg : public CDialog
{
public:
	CDogleashCmdDlg(CWnd*);
	void dogleashModeCmd(int);

// Dialog Data
	//{{AFX_DATA(CSDogleashCmdDlg)
	enum { IDD = IDD_DOGLEASHWIN };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogleashCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CDogleashCmdDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnBnClickedDogleashRefresh();
public:
	afx_msg void OnBnClickedDogleashErase();
	afx_msg void OnTimer(UINT nIDEvent);
};

