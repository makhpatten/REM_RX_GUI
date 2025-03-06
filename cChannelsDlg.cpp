/////////////////////////////////////////////////////////////////////////////
// CChannelsDlg dialog used to display channels

#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
#include "CChannelsDlg.h"
#include "led_defs.h"

//ULONG nScanSteps;

//#define MAX_STEPS 100

// Global variables
int channel1ActiveFlag=0;
CProgressCtrl *ChanLevelBar1;
CProgressCtrl *ChanLevelBar2;
CProgressCtrl *ChanLevelBar3;
CProgressCtrl *ChanLevelBar4;
CProgressCtrl *ChanLevelBar5;
CProgressCtrl *ChanLevelBar6;
CProgressCtrl *ChanLevelBar7;
CProgressCtrl *ChanLevelBar8;
CListBox *pTuneFreqText;
CDC *channelsWinDrawingContext;
int paramValueIntTest=0;

// Externally defined global variables
extern CDialog *pChannelsWinDlg;
extern int channelsWinFlag;
extern CButton m_channelsWin;
extern char freqValChars[];



BEGIN_MESSAGE_MAP(CChannelsDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDCANCEL, &CChannelsDlg::OnBnClickedChannelsOk)
//ON_WM_INITDIALOG()
ON_WM_SYSCOMMAND()
ON_WM_CLOSE()
//ON_WM_PAINT()
//ON_BN_CLICKED(IDC_CHANBUTTON1, &CChannelsDlg::OnBnClickedDrawLines)
ON_BN_CLICKED(ID_CHANNELSCLOSE, &CChannelsDlg::OnBnClickedChannelsClose)
END_MESSAGE_MAP()


CChannelsDlg::CChannelsDlg(CWnd* pParent /*=NULL*/) : CDialog(CChannelsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

void CChannelsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelsDlg)
	//}}AFX_DATA_MAP
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL1, m_Channels_Level1);
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL2, m_Channels_Level2);
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL3, m_Channels_Level3);
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL4, m_Channels_Level4);
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL5, m_Channels_Level5);
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL6, m_Channels_Level6);
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL7, m_Channels_Level7);
	//	DDX_Control(pDX, IDC_CHANNELS_LEVEL8, m_Channels_Level8);
	DDX_Control(pDX, IDC_FREQ_LABEL1, m_freqLabel1);
//	DDX_Control(pDX, IDC_TUNE_FREQ_TEXT, m_tuneFreqText);
}


//afx_msg void CChannelsDlg::OnPaint() {
//	UpdateChannelIndicatorLights();
//	CDialog::OnPaint();
//}

extern ULONG setFreqKHz[];
extern ULONG tuneFreqKHz;
extern int saveFreqPos;
extern ULONG tuneFreqKHz;

afx_msg void CChannelsDlg::OnClose() {
	channelsWinFlag=0;
	m_channelsWin.EnableWindow(TRUE);//re-enable button for Channels Window

	tuneFreqKHz=setFreqKHz[8-saveFreqPos];
	CMainDlg::setFreqOperCmd();

	CDialog::OnClose();
}



CDC *drawingContextChannels;

BOOL CChannelsDlg::OnInitDialog() {
	CPen gridLinePen;

	ChanLevelBar1 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL1);
	ChanLevelBar2 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL2);
	ChanLevelBar3 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL3);
	ChanLevelBar4 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL4);
	ChanLevelBar5 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL5);
	ChanLevelBar6 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL6);
	ChanLevelBar7 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL7);
	ChanLevelBar8 = (CProgressCtrl*) GetDlgItem(IDC_CHANNELS_LEVEL8);

	ChanLevelBar1->SetRange(0,256);
	ChanLevelBar2->SetRange(0,256);
	ChanLevelBar3->SetRange(0,256);
	ChanLevelBar4->SetRange(0,256);
	ChanLevelBar5->SetRange(0,256);
	ChanLevelBar6->SetRange(0,256);
	ChanLevelBar7->SetRange(0,256);
	ChanLevelBar8->SetRange(0,256);

	pTuneFreqText= (CListBox *)GetDlgItem(IDC_TUNE_FREQ_TEXT);
	
	drawingContextChannels=pChannelsWinDlg->GetDC();
	gridLinePen.CreatePen(PS_DOT,1,RGB(127,127,127));
/*
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ1_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ2_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ3_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ4_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ5_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ6_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ7_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_NOSQ_FREQ8_LED,LED_DARK_GREEN,drawingContextChannels);

	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ1_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ2_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ3_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ4_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ5_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ6_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ7_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_NOSQ_FREQ8_LED,LED_DARK_GREEN,drawingContextChannels);

	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ1_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ2_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ3_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ4_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ5_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ6_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ7_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_MONO_FS_FREQ8_LED,LED_DARK_GREEN,drawingContextChannels);

	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ1_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ2_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ3_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ4_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ5_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ6_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ7_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FS_FREQ8_LED,LED_DARK_GREEN,drawingContextChannels);
*/
	CMainDlg::setIndicatorLight(LOCK_FREQ1_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_FREQ2_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_FREQ3_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_FREQ4_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_FREQ5_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_FREQ6_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_FREQ7_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_FREQ8_LED,LED_DARK_GREEN,drawingContextChannels);

/*
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ1_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ2_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ3_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ4_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ5_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ6_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ7_LED,LED_DARK_GREEN,drawingContextChannels);
	CMainDlg::setIndicatorLight(LOCK_STEREO_FEC_FREQ8_LED,LED_DARK_GREEN,drawingContextChannels);
*/

	return TRUE;
}



void CChannelsDlg::OnBnClickedChannelsOk()
{
}


//static CDC *channelsscanDrawingContext;
extern int chanNumLoop;
//extern CProgressCtrl m_Channels_Level1;
extern char inMsgParams[];
extern float convert_AD_to_dBm(char);
extern int convert_dBm_to_barGraph(float);
extern ULONG respFreqKHz;
extern ULONG freq_3bytes_to_value(char*);
extern int paramValueInt;

#if 1==0
void CChannelsDlg::UpdateChannelIndicatorLights() {
//	int paramValueInt;
	int antNumberUse;
	int antLocked;
	float paramValueFloat;

	int monoFrameSyncA_notSquelched=0;
	int monoFrameSyncA=0;
	int monoFecSyncA=0;
	int monoFrameSyncB_notSquelched=0;
	int monoFrameSyncB=0;
	int monoFecSyncB=0;

	int stereoFrameSyncA_notSquelched=0;
	int stereoFrameSyncA=0;
	int stereoFecSyncA=0;
	int stereoFrameSyncB_notSquelched=0;
	int stereoFrameSyncB=0;
	int stereoFecSyncB=0;

	if ((inMsgParams[2]&0x01)!=0) {
  		monoFrameSyncA_notSquelched=1;
	}
	if ((inMsgParams[2]&0x02)!=0) {
  		monoFrameSyncA=1;
	}
	if ((inMsgParams[2]&0x02)!=0) {
  		monoFecSyncA=1;
	}
	if ((inMsgParams[2]&0x04)!=0) {
  		monoFrameSyncB_notSquelched=1;
	}
	if ((inMsgParams[2]&0x08)!=0) {
  		monoFrameSyncB=1;
	}
	if ((inMsgParams[2]&0x10)!=0) {
  		monoFecSyncB=1;
	}

	if ((inMsgParams[3]&0x01)!=0) {
  		stereoFrameSyncA_notSquelched=1;
	}
	if ((inMsgParams[3]&0x02)!=0) {
  		stereoFrameSyncA=1;
	}
	if ((inMsgParams[3]&0x02)!=0) {
  		stereoFecSyncA=1;
	}
	if ((inMsgParams[3]&0x04)!=0) {
  		stereoFrameSyncB_notSquelched=1;
	}
	if ((inMsgParams[3]&0x08)!=0) {
  		stereoFrameSyncB=1;
	}
	if ((inMsgParams[3]&0x10)!=0) {
  		stereoFecSyncB=1;
	}

	int monoLockA=0;
	int monoLockB=0;
	if (monoFrameSyncA_notSquelched+monoFrameSyncA+monoFecSyncA>0) {
		monoLockA=1;
	}
	if (monoFrameSyncB_notSquelched+monoFrameSyncB+monoFecSyncB>0) {
		monoLockB=1;
	}
	int stereoLockA=0;
	int stereoLockB=0;
	if (stereoFrameSyncA_notSquelched+stereoFrameSyncA+stereoFecSyncA>0) {
		stereoLockA=1;
	}
	if (stereoFrameSyncB_notSquelched+stereoFrameSyncB+stereoFecSyncB>0) {
		stereoLockB=1;
	}
	int monoLock=0;
	int stereoLock=0;
	if (monoLockA+monoLockB>0) monoLock=1;
	if (stereoLockA+stereoLockB>0) stereoLock=1;

/*// If both antennas are locked then find antenna with greatest signal
	if (!(inMsgParams[6]&0x80)&& !(inMsgParams[7]&0x80)) {
	  antLocked=1;
	  if (inMsgParams[6]>inMsgParams[7]) antNumberUse=0;
	  else antNumberUse=1;
// If only antenna A locked, use it
	} else if (!(inMsgParams[6]&0x80)) {
  		antLocked=1;
		antNumberUse=0;
// If only antenna B locked, use it
	} else if (!(inMsgParams[7]&0x80)) {
  		antLocked=1;
		antNumberUse=1;
// If neither antenna locked, indicate that
	} else {
		antNumberUse=0;
		antLocked=0;
	}
*/
// Plot antenna with greatest value
	antNumberUse=0;
	if ((inMsgParams[0]&0x7f)>(inMsgParams[1]&0x7f)) {
		antNumberUse=1;
	}

// Compute dBm value
	paramValueFloat=convert_AD_to_dBm(inMsgParams[antNumberUse]);

// set frequency text value display
//	respFreqKHz=freq_3bytes_to_value(inMsgParams);
	sprintf(freqValChars,"Ch#%1d%: %6.1f MHz",chanNumLoop,(float)tuneFreqKHz*(float).001);
	pTuneFreqText->ResetContent();
	pTuneFreqText->InsertString(0,freqValChars);

	// compute value for bargraph
	paramValueInt=convert_dBm_to_barGraph(paramValueFloat);
//	paramValueInt=(int)rand()&(int)(0x0ff);

#if 1==0
	int ledLockMonoFSNoSq;
	int ledLockMonoFS;
	int	ledLockMonoFEC;
	int	ledLockStereoFSNoSq;
	int	ledLockStereoFS;
	int	ledLockStereoFEC;

	switch(chanNumLoop) {
		case 0: {
			ChanLevelBar1->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ1_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ1_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ1_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ1_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ1_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ1_LED;
			break;
		} case 1: {
			ChanLevelBar2->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ2_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ2_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ2_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ2_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ2_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ2_LED;
			break;
		} case 2: {
			ChanLevelBar3->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ3_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ3_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ3_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ3_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ3_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ3_LED;
			break;
		} case 3: {
			ChanLevelBar4->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ4_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ4_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ4_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ4_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ4_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ4_LED;
			break;
		} case 4: {
			ChanLevelBar5->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ5_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ5_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ5_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ5_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ5_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ5_LED;
			break;
		} case 5: {
			ChanLevelBar6->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ6_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ6_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ6_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ6_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ6_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ6_LED;
			break;
		} case 6: {
			ChanLevelBar7->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ7_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ7_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ7_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ7_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ7_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ7_LED;
			break;
		} case 7: {
			ChanLevelBar8->SetPos(paramValueInt);
//			ledLockMonoFSNoSq=LOCK_MONO_FS_NOSQ_FREQ8_LED;
//			ledLockMonoFS=LOCK_MONO_FS_FREQ8_LED;
			ledLockMonoFEC=LOCK_MONO_FEC_FREQ8_LED;
//			ledLockStereoFSNoSq=LOCK_STEREO_FS_NOSQ_FREQ8_LED;
//			ledLockStereoFS=LOCK_STEREO_FS_FREQ8_LED;
			ledLockStereoFEC=LOCK_STEREO_FEC_FREQ8_LED;
			break;
		}
	}

/*
// update mono Frame Sync Not Squelched locked indicator
	if (monoFrameSyncA_notSquelched==1 || monoFrameSyncB_notSquelched==1) {
		CMainDlg::setIndicatorLight(ledLockMonoFSNoSq,LED_GREEN,drawingContextChannels);
	} else { 
		CMainDlg::setIndicatorLight(ledLockMonoFSNoSq,LED_DARK_GREEN,drawingContextChannels);
	}
// update mono Frame Sync locked indicator
	if (monoFrameSyncA==1 || monoFrameSyncB==1) {
		CMainDlg::setIndicatorLight(ledLockMonoFS,LED_GREEN,drawingContextChannels);
	} else { 
		CMainDlg::setIndicatorLight(ledLockMonoFS,LED_DARK_GREEN,drawingContextChannels);
	}
*/
// update mono FEC locked indicator
	if (monoFecSyncA==1 || monoFecSyncB==1) {
		CMainDlg::setIndicatorLight(ledLockMonoFEC,LED_GREEN,drawingContextChannels);
	} else { 
		CMainDlg::setIndicatorLight(ledLockMonoFEC,LED_DARK_GREEN,drawingContextChannels);
	}
/*
//
	update stereo Frame Sync Not Squelched locked indicator
	if (stereoFrameSyncA_notSquelched==1 || stereoFrameSyncB_notSquelched==1) {
		CMainDlg::setIndicatorLight(ledLockStereoFSNoSq,LED_GREEN,drawingContextChannels);
	} else { 
		CMainDlg::setIndicatorLight(ledLockStereoFSNoSq,LED_DARK_GREEN,drawingContextChannels);
	}
// update stereo Frame Sync locked indicator
	if (stereoFrameSyncA==1 || stereoFrameSyncB==1) {
		CMainDlg::setIndicatorLight(ledLockStereoFS,LED_GREEN,drawingContextChannels);
	} else { 
		CMainDlg::setIndicatorLight(ledLockStereoFS,LED_DARK_GREEN,drawingContextChannels);
	}
*/
// update stereo FEC locked indicator
	if (stereoFecSyncA==1 || stereoFecSyncB==1) {
		CMainDlg::setIndicatorLight(ledLockStereoFEC,LED_GREEN,drawingContextChannels);
	} else { 
		CMainDlg::setIndicatorLight(ledLockStereoFEC,LED_DARK_GREEN,drawingContextChannels);
	}

#endif

}
#endif

void CChannelsDlg::OnBnClickedChannelsClose()
{
	channelsWinFlag=0;
//Kill channels window manually
	pChannelsWinDlg->DestroyWindow();
//re-enable button for Channels Window
	m_channelsWin.EnableWindow(TRUE);
// Restore tuning to previous setting
	tuneFreqKHz=setFreqKHz[8-saveFreqPos];
	CMainDlg::setFreqOperCmd();

	
//	KillTimer(ID_TIMER_CHANNELS);
	CDialog::OnClose();
}

