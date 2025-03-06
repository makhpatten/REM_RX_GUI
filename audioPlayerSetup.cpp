#include "stdafx.h"
#include "audioPlayerPath.h"
#include "infinityDlg.h"

CAudioPlayerPathDlg::CAudioPlayerPathDlg(CWnd* pParent /*=NULL*/) : CDialog(CAudioPlayerPathDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

char audioPlayerPathStr[200];
CComboBox *m_audioPort;
CComboBox *m_audioPath;
CEdit *m_audioPlayerPath;

extern int audioPort;
extern CString audioPath;

BOOL CAudioPlayerPathDlg::OnInitDialog() {
	m_audioPlayerPath = (CEdit*) GetDlgItem(IDC_AUDIO_PLAYER_PATH);
//	CMainDlg::readFileNameCmd();
	m_audioPlayerPath->SetWindowText(audioPlayerPathStr); 

	m_audioPort= (CComboBox*)GetDlgItem(IDC_AUDIO_PORT);
	m_audioPath= (CComboBox*)GetDlgItem(IDC_AUDIO_PATH);

    char tempString2[100];
	sprintf(tempString2,"%d",audioPort);
	m_audioPort->SetWindowTextA(tempString2);
	m_audioPath->SetWindowTextA(audioPath);


	return TRUE;
}


void CAudioPlayerPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAudioPlayerPathDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CANCEL_AUDIOSETUP, &CAudioPlayerPathDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SET_AUDIO_PLAYER_PATH, &CAudioPlayerPathDlg::OnBnClickedSetAudioPlayer)
END_MESSAGE_MAP()

int audioPlayerWinFlag;
CDialog *pAudioPlayerWinDlg;

afx_msg void CAudioPlayerPathDlg::OnClose() {
	audioPlayerWinFlag=0;
//	CMainDlg::m_stingerWinButton.EnableWindow(TRUE);//re-enable button for Scan Window

	CDialog::OnClose();
}
void CAudioPlayerPathDlg::OnOK() {
	OnBnClickedSetAudioPlayer();
//	CDialog::OnOK();
}


void CAudioPlayerPathDlg::OnBnClickedCancel() {
	audioPlayerWinFlag=0;
//Kill stinger window manually
	pAudioPlayerWinDlg->DestroyWindow();
//re-enable button for Channels Window
//	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}

afx_msg void CAudioPlayerPathDlg::OnPaint() {
	CDialog::OnPaint();
}


void CAudioPlayerPathDlg::OnBnClickedSetAudioPlayer() {
	CString strVal;
	m_audioPlayerPath->GetWindowTextA(strVal);
	int i=0;
	int j=0;
	while (i<strlen(strVal)) { // turn single backslashes into double backslashes
		if (strVal[i]=='\\') {
			if (strVal[i+1]=='\\') {
				audioPlayerPathStr[j++]=strVal[i++];
				audioPlayerPathStr[j++]=strVal[i++];
			} else {
				audioPlayerPathStr[j++]=strVal[i];
				audioPlayerPathStr[j++]=strVal[i++];
			}
		} else {
			audioPlayerPathStr[j++]=strVal[i++];
		}
	}
	audioPlayerPathStr[j]=0;
	m_audioPlayerPath->SetWindowText(audioPlayerPathStr);
    CString tempString2;
	m_audioPort->GetWindowTextA(tempString2);
	sscanf(tempString2,"%d",&audioPort);
	m_audioPath->GetWindowTextA(audioPath);



	CMainDlg::saveConfigToFile();

}
