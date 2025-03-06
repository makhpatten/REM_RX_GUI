#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CStingerRecCmdDlg dialog

class CStingerRecCmdDlg : public CDialog
{
public:
	CStingerRecCmdDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CStingerRecCmdDlg)
	enum { IDD = IDD_STINGERRECWIN };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStingerRecCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);


	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CStingerRecCmdDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
//public:
//	afx_msg void OnBnClickedStingerRecRefresh();
public:
	afx_msg void OnBnClickedStingerRecEraseall();
};

