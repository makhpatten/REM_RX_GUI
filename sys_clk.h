/////////////////////////////////////////////////////////////////////////////
// CSetSysClkDlg dialog
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"

class CSetSysClkDlg : public CDialog
{
public:
	CSetSysClkDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CSetSysClkDlg)
	enum { IDD = IDD_SYSCLK_WIN };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetSysClkDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedSysClkUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CSetSysClkDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnBnClickedSysClkSet();
public:
	afx_msg void OnBnClickedSysClkSetWintime();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
//	CDateTimeCtrl pTimeBoxDDE;

};

