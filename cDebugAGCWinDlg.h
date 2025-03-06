#include "afxwin.h"
#include "afxcmn.h"
class CDebugAGCWinDlg : public CDialog
{
public:
	CDebugAGCWinDlg();

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_DEBUGAGCWINDOW };
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
	virtual void OnOK();

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedLocalAgcRead();
public:
	afx_msg void OnBnClickedLocalAgcWrite();
public:
	afx_msg void OnBnClickedRemoteAgcWrite();
public:
	afx_msg void OnBnClickedRemoteAgcRead();
//	void writeRemoteAGCCmd();
//	void writeLocalAGCCmd();
//	void readRemoteAGCCmd();
//	void readLocalAGCCmd();

};


