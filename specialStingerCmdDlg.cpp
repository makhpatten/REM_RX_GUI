#include "stdafx.h"
#include "specialStingerCmdDlg.h"
#include "CStingerDlg.h"
#include "infinityDlg.h"


void CSpecialStingerCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecialStingerCmdDlg)
	//}}AFX_DATA_MAP
}

BOOL CSpecialStingerCmdDlg::OnInitDialog() {
	BYTE oneByte;
	oneByte='P';
	BYTE key='x';

	return TRUE;
}



BEGIN_MESSAGE_MAP(CSpecialStingerCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_CANCEL_SPECIALSTINGERWIN, &CSpecialStingerCmdDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDPW_SENDSTINGERCMD, &CSpecialStingerCmdDlg::OnBnClickedEnterStingerCmd)

END_MESSAGE_MAP()


void CSpecialStingerCmdDlg::OnClose() 
{
	CDialog::OnClose();
}

extern CMenu *pSysMenu;
CSpecialStingerCmdDlg* pSpecialStingerCmdWinDlg;
extern int specialStingerCmdWinFlag;

void CSpecialStingerCmdDlg::OnBnClickedCancel() {
	specialStingerCmdWinFlag=0;
	pSysMenu->EnableMenuItem(ID_OPTIONS_SPECIAL_STINGER_CMD,	MF_ENABLED);

//	writeStingerCmdFile();
//Kill stinger window manually
	pSpecialStingerCmdWinDlg->DestroyWindow();
//re-enable button for Channels Window
//	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}

CString specialStingerCStrVal;
char specialStingerStrVal[10];
extern char specialStingerCmdChar;


void CSpecialStingerCmdDlg::OnBnClickedEnterStingerCmd() {
	CEdit *x = (CEdit *)GetDlgItem(IDPW_SPECIAL_STINGER_COMMAND);
	x->GetWindowTextA(specialStingerCStrVal);

	int i;
	int len=specialStingerCStrVal.GetLength();
	if (len>5) len=5;
	for (i=0;i<len;i++) {
		specialStingerStrVal[i] = specialStingerCStrVal[i];
	}
	specialStingerStrVal[len]=0;
	specialStingerCmdChar='X';
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}

CSpecialStingerCmdDlg::CSpecialStingerCmdDlg(CWnd* pParent /*=NULL*/) : CDialog(CSpecialStingerCmdDlg::IDD, pParent)
{
}

void CSpecialStingerCmdDlg::OnOK() {
	int x;
	x=3; // just a place to break
	CDialog::OnOK();
}

int specialStingerCmdWinFlag=0;


