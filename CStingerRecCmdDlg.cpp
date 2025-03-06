#include <stdafx.h>
#include "CStingerRecCmdDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CStingerRecCmdDlg dialog used for App About

class CStingerRecCmdDlg : public CDialog
{
public:
	CStingerRecCmdDlg();

// Dialog Data
	//{{AFX_DATA(CStingerRecCmdDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStingerRecCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CStingerRecCmdDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

CStingerRecCmdDlg::CStingerRecCmdDlg() : CDialog(CStingerRecCmdDlg::IDD)
{
	//{{AFX_DATA_INIT(CStingerRecCmdDlg)
	//}}AFX_DATA_INIT
}

void CStingerRecCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStingerRecCmdDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStingerRecCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CStingerRecCmdDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_MARK_PATTEN, &CStingerRecCmdDlg::OnMarkPatten)
END_MESSAGE_MAP()


