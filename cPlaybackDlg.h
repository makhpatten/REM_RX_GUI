#include "afxwin.h"
class CPlaybackDlg : public CDialog
{
public:
	CPlaybackDlg();

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_PLAYBACKWINDOW };
	//}}AFX_DATA

public:
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
	afx_msg void OnClose();
	afx_msg void OnBnClickedPlaybackClose();

public:
public:
	afx_msg void OnBnClickedPlaybackstop();
public:
	afx_msg void OnBnClickedPlaybackstart();
public:
	afx_msg void OnDtnDatetimechangePlaybacktime(NMHDR *pNMHDR, LRESULT *pResult);
};


