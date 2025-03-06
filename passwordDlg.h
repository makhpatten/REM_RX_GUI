#include "resource.h"
extern int enterPasswordWinFlag;


class CEnterPasswordDlg : public CDialog
{
public:
	CEnterPasswordDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_ENTERPASSWORDWIN };
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
	afx_msg void OnBnClickedEnterPassword();
	void readPassword(FILE *);

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void OnClose();
};

extern CEnterPasswordDlg* pEnterPasswordWinDlg;

class CChangePasswordDlg : public CDialog
{
public:
	CChangePasswordDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_CHANGEPASSWORDWIN };
	//}}AFX_DATA

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedChangePassword();
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
};

extern CChangePasswordDlg* pChangePasswordWinDlg;

class CPasswordDlg : public CDialog
{
public:
	CPasswordDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_PASSWORDWIN };
	//}}AFX_DATA

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedChange();
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	void OnMenuChangePassword();
//	afx_msg void OnBnClickedEnterPassword();
//	void readPassword(FILE *);



	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedRestoreState();
public:
	afx_msg void OnEnChangeEncwrd2();
public:
	afx_msg void OnNMReleasedcapturePwFreqselect(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedPwSetfreq();
public:
	afx_msg void OnBnClickedPwLoadfreqs();
public:
	 void insertTextIntoPwFreqButton(int,char*);
public:
afx_msg void OnBnClickedPwSavefreqs();
public:
	afx_msg void OnBnClickedPwfreqval1();
public:
	afx_msg void OnBnClickedPwfreqval2();
public:
	afx_msg void OnBnClickedPwfreqval3();
public:
	afx_msg void OnBnClickedPwfreqval4();
public:
	afx_msg void OnBnClickedPwfreqval5();
public:
	afx_msg void OnBnClickedPwfreqval6();
public:
	afx_msg void OnBnClickedPwfreqval7();
public:
	afx_msg void OnBnClickedPwfreqval8();
public:
	void LoadFreqButtons();
	void OnBnClickedPwProcessSDEncWrd();
public:
	afx_msg void OnBnClickedSetClockMain();
};

extern CPasswordDlg* pPasswordWinDlg;

