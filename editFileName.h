#include "afxwin.h"
class CEditFileNameDlg : public CDialog
{
public:
	CEditFileNameDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_EDITFILENAMEWIN };
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
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
public:



	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedSetnextfilename();
};

