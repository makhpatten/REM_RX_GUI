#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
#include "editFileName.h"

CEditFileNameDlg::CEditFileNameDlg(CWnd* pParent /*=NULL*/) : CDialog(CEditFileNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

extern char SDFileNameStr[];
CEdit *m_sdFileName;
BOOL CEditFileNameDlg::OnInitDialog() {
    m_sdFileName = (CEdit*) GetDlgItem(IDC_NEXT_FILE_NAME_TEXT);
	CMainDlg::readFileNameCmd();
	m_sdFileName->SetWindowText(SDFileNameStr); 

	return TRUE;
}


void CEditFileNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditFileNameDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CANCEL_EDITFILENAME, &CEditFileNameDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SETNEXTFILENAME, &CEditFileNameDlg::OnBnClickedSetnextfilename)
END_MESSAGE_MAP()

extern int editFileNameWinFlag;

afx_msg void CEditFileNameDlg::OnClose() {
	editFileNameWinFlag=0;
//	CMainDlg::m_stingerWinButton.EnableWindow(TRUE);//re-enable button for Scan Window

	CDialog::OnClose();
}
void CEditFileNameDlg::OnOK() {
	OnBnClickedSetnextfilename();
//	CDialog::OnOK();
}

extern CDialog *pEditFileNameWinDlg;

void CEditFileNameDlg::OnBnClickedCancel() {
	editFileNameWinFlag=0;
//Kill stinger window manually
	pEditFileNameWinDlg->DestroyWindow();
//re-enable button for Channels Window
//	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}

afx_msg void CEditFileNameDlg::OnPaint() {
	CDialog::OnPaint();
}


void CEditFileNameDlg::OnBnClickedSetnextfilename() {
	int goodNameFlag;
	int i;
	CString strVal;
	char tempChar[9];

	goodNameFlag=1;
	m_sdFileName->GetWindowTextA(strVal);
		for (i=0;i<8;i++) {
		if (i<strVal.GetLength()) {
			tempChar[i]=strVal[i];
		} else {
			goodNameFlag=0;
			break;
		}
	}
	if (goodNameFlag==1) {
		tempChar[8]=0;
		if (tempChar[0]>='a') { //Make first character uppercase
			tempChar[0]=tempChar[0]-'a';
			tempChar[0]=tempChar[0]+'A';
		}
		if (tempChar[0]>='A' && tempChar[0]<='Z') { // Check if first character is a valid letter
			for (i=1;i<8;i++) { // If so, then check all other characters to see if they are valid digits
				if (tempChar[i]<'0' || tempChar[i]>'9') {
					goodNameFlag=0;
					break;
				}
			}
		} else {
			goodNameFlag=0;
		}
	}
	if (goodNameFlag==1) { // If name was good, set SD variable and send command
		for (i=0;i<8;i++) {
			SDFileNameStr[i]=tempChar[i];
		}
		SDFileNameStr[8]=0;
		CMainDlg::setFileNameCmd();
//		CMainDlg::nextFileNameUpdate();

	}
	m_sdFileName->SetWindowText(SDFileNameStr); //Set display to what value ended up as
}
