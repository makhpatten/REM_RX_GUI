#include "stdafx.h"
#include "stealthRecSpecialWindow.h"
#include "CStingerDlg.h"
#include "infinityDlg.h"


void CStealthRecSpecialWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecialStingerCmdDlg)
	//}}AFX_DATA_MAP
}

extern int stealthRecMode;
extern char displayString[40];
CButton *m_stealthRecPlaybackVolume;
CButton *m_stealthRecDeleteFileNum;
int playbackVolume;

BOOL CStealthRecSpecialWinDlg::OnInitDialog() {

	CButton *xx;
	if (stealthRecMode==0) {
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_MIC);
		xx->SetCheck(BST_CHECKED);
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_LINE);
		xx->SetCheck(BST_UNCHECKED);
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_AUX);
		xx->SetCheck(BST_UNCHECKED);
	} else if (stealthRecMode==1) {
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_MIC);
		xx->SetCheck(BST_UNCHECKED);
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_LINE);
		xx->SetCheck(BST_CHECKED);
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_AUX);
		xx->SetCheck(BST_UNCHECKED);
	} else {
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_MIC);
		xx->SetCheck(BST_UNCHECKED);
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_LINE);
		xx->SetCheck(BST_UNCHECKED);
		xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_AUX);
		xx->SetCheck(BST_CHECKED);
	}

	m_stealthRecPlaybackVolume=(CButton*)GetDlgItem(IDC_STEALTHREC_PLAYBACK_VOL);
	sprintf(displayString,"%d",playbackVolume);
	m_stealthRecPlaybackVolume->SetWindowTextA(displayString);

	m_stealthRecDeleteFileNum=(CButton*)GetDlgItem(IDC_STEALTHREC_DELETEFILE_NUM);
	sprintf(displayString,"%d",1);
	m_stealthRecDeleteFileNum->SetWindowTextA(displayString);



	return TRUE;
}



BEGIN_MESSAGE_MAP(CStealthRecSpecialWinDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_CANCEL_STEALTHRECWIN, &CStealthRecSpecialWinDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_STEALTHREC_SOURCE_MIC, &CStealthRecSpecialWinDlg::OnStealthRecSourceMic)
	ON_BN_CLICKED(IDC_STEALTHREC_SOURCE_LINE, &CStealthRecSpecialWinDlg::OnStealthRecSourceLine)
	ON_BN_CLICKED(IDC_STEALTHREC_SOURCE_AUX, &CStealthRecSpecialWinDlg::OnStealthRecSourceAux)
	ON_BN_CLICKED(ID_STEALTHREC_CLEARLOG, &CStealthRecSpecialWinDlg::OnStealthRecClearLog)
	ON_BN_CLICKED(ID_STEALTHREC_GET_VOLUME, &CStealthRecSpecialWinDlg::OnStealthRecGetVolume)
	ON_BN_CLICKED(ID_STEALTHREC_GET_WORK_STATUS, &CStealthRecSpecialWinDlg::OnStealthRecGetWorkStatus)
	ON_BN_CLICKED(ID_STEALTHREC_GET_NUM_FILES, &CStealthRecSpecialWinDlg::OnStealthRecGetNumFiles)
	ON_BN_CLICKED(ID_STEALTHREC_GET_SOUND_FILE, &CStealthRecSpecialWinDlg::OnStealthRecGetSoundFile)
	ON_BN_CLICKED(ID_STEALTHREC_GET_CONN_STATUS, &CStealthRecSpecialWinDlg::OnStealthRecGetConnStatus)
	ON_BN_CLICKED(ID_STEALTHREC_GET_SPACE, &CStealthRecSpecialWinDlg::OnStealthRecGetSpace)
	ON_BN_CLICKED(ID_STEALTHREC_DELETEFILE, &CStealthRecSpecialWinDlg::OnBnClickedStealthrecDeletefile)
	ON_BN_CLICKED(ID_STEALTHREC_FASTFWD, &CStealthRecSpecialWinDlg::OnBnClickedStealthrecFastfwd)
	ON_BN_CLICKED(ID_STEALTHREC_FASTBKWD, &CStealthRecSpecialWinDlg::OnBnClickedStealthrecFastbkwd)

END_MESSAGE_MAP()

extern int stealthRecSpecialWinFlag;

void CStealthRecSpecialWinDlg::OnClose() 
{
	stealthRecSpecialWinFlag=0;
	CDialog::OnClose();
}

extern CMenu *pSysMenu;
CStealthRecSpecialWinDlg* pStealthRecSpecialWinDlg;
extern void writeStealthRecStatusFile();

void CStealthRecSpecialWinDlg::OnBnClickedCancel() {
	m_stealthRecPlaybackVolume->GetWindowText(displayString,3);
	playbackVolume = strtol(displayString, 0, 0); //convert to long
	if (playbackVolume>31) {
		playbackVolume=31;
	}
	if (playbackVolume<0) {
		playbackVolume=0;
	}
	writeStealthRecStatusFile();

	stealthRecSpecialWinFlag=0;
	pSysMenu->EnableMenuItem(ID_STEALTH_REC_SPECIAL_FUNCTIONS,	MF_ENABLED);

//	writeStingerCmdFile();
//Kill stinger window manually
	pStealthRecSpecialWinDlg->DestroyWindow();
//re-enable button for Channels Window
//	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}


CStealthRecSpecialWinDlg::CStealthRecSpecialWinDlg(CWnd* pParent /*=NULL*/) : CDialog(CStealthRecSpecialWinDlg::IDD, pParent)
{
}

void CStealthRecSpecialWinDlg::OnOK() {
	int x;
	x=3; // just a place to break
	m_stealthRecPlaybackVolume->GetWindowText(displayString,3);
	playbackVolume = strtol(displayString, 0, 0); //convert to long
	if (playbackVolume>31) {
		playbackVolume=31;
	}
	if (playbackVolume<0) {
		playbackVolume=0;
	}
	writeStealthRecStatusFile();
	stealthRecSpecialWinFlag=0;
	CDialog::OnOK();
}

int stealthRecSpecialWinFlag=0;
extern CButton *m_stealthRecSourceMono;
extern CButton *m_stealthRecSourceStereo;
extern void writeStealthRecStatusFile();

void CStealthRecSpecialWinDlg::OnStealthRecSourceMic(){
	CButton *xx;
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_MIC);
	xx->SetCheck(BST_CHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_LINE);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_AUX);
	xx->SetCheck(BST_UNCHECKED);

	m_stealthRecSourceMono->SetCheck(BST_UNCHECKED);
	m_stealthRecSourceStereo->SetCheck(BST_UNCHECKED);

	stealthRecMode=0;
	writeStealthRecStatusFile();
}

void CStealthRecSpecialWinDlg::OnStealthRecSourceLine(){
	CButton *xx;
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_MIC);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_LINE);
	xx->SetCheck(BST_CHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_AUX);
	xx->SetCheck(BST_UNCHECKED);

	m_stealthRecSourceMono->SetCheck(BST_CHECKED);
	m_stealthRecSourceStereo->SetCheck(BST_UNCHECKED);

	stealthRecMode=1;
	writeStealthRecStatusFile();
}
void CStealthRecSpecialWinDlg::OnStealthRecSourceAux(){
	CButton *xx;
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_MIC);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_LINE);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_SOURCE_AUX);
	xx->SetCheck(BST_CHECKED);

	m_stealthRecSourceMono->SetCheck(BST_UNCHECKED);
	m_stealthRecSourceStereo->SetCheck(BST_CHECKED);

	stealthRecMode=2;
	writeStealthRecStatusFile();

}

extern CListBox *m_recFileNumText;

void CStealthRecSpecialWinDlg::OnStealthRecClearLog() {
	m_recFileNumText->ResetContent();
	FILE *fp=fopen("RecFileLog.txt","w");
	fprintf(fp," ");
	fclose(fp);

}

extern char specialStingerCmdChar;
extern char specialStingerStrVal[];


void CStealthRecSpecialWinDlg::OnStealthRecGetVolume() {
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=1;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}
void CStealthRecSpecialWinDlg::OnStealthRecGetWorkStatus(){
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=2;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}
void CStealthRecSpecialWinDlg::OnStealthRecGetNumFiles(){
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=3;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}
void CStealthRecSpecialWinDlg::OnStealthRecGetSoundFile(){
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=5;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}
void CStealthRecSpecialWinDlg::OnStealthRecGetConnStatus(){
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=5;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}
void CStealthRecSpecialWinDlg::OnStealthRecGetSpace(){
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=6;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}

void CStealthRecSpecialWinDlg::OnBnClickedStealthrecDeletefile()
{
	char displayStringx[80];
	long unsigned int deleteFileNum=0;
	m_stealthRecDeleteFileNum->GetWindowText(displayStringx,3);
	deleteFileNum = strtol(displayStringx, 0, 0); //convert to long
	if (deleteFileNum>999) {
		deleteFileNum=1;
	}
	sprintf(displayStringx,"%d",deleteFileNum);
	m_stealthRecDeleteFileNum->SetWindowTextA(displayStringx);

	specialStingerCmdChar='D';
	specialStingerStrVal[0]=(char)((deleteFileNum>>8)& (long unsigned)0x0ff);
	specialStingerStrVal[1]=(char)((deleteFileNum)& (long unsigned)0x0ff);
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}

void CStealthRecSpecialWinDlg::OnBnClickedStealthrecFastfwd() {
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=7;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}

void CStealthRecSpecialWinDlg::OnBnClickedStealthrecFastbkwd() {
	specialStingerCmdChar='S';
	specialStingerStrVal[0]=8;
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);
}
