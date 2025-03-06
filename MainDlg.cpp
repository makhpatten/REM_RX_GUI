#define YES_DISPLAY_EM 3
#define NOPE_DONT_DISPLAY_EM 4 //just some unique numbers
#define DISPLAY_MESSAGES YES_DISPLAY_EM
#define junk 1
#if junk==0
 ssdfwlkjelkj
#endif
// MainDlg.cpp : implementation file
/*
Project: ct148.cpp
Version	 1.26e	10/24/19 A2100519 Adds DPI setting on settings window to adjust LED positions
Version	 1.26d	05/03/19 A2100517 Takes out unsupported record menu item
Version	 1.26c	07/12/18 A2100515 Fixes "All Off" problem reported by customer (GUI needs reset after ALL OFF to work), also corrects reversed Mono L and R transmit commands
Version	 1.26b	05/21/18 Changed "Ladybug" references to "RD-1200"; also fixed "Close" button on password protected screen
Version	 1.26a	04/10/18 Added "All Off" and audio gain controls; removed Flyron pane
Version	 1.25v2	11/03/17 Worked on COM blinking 
Version	 1.25v	09/18/17 Adjust COM parameters even more to try to stop blinking
Version	 1.25u	07/13/17 Only dim "playing" and "card present" lights, not whole panel, also adjust COM parameters to try to stop blinking
Version	 1.25t	06/22/17 Add tics on audio levels; remove number field showing audio levels; change label to "Recorder Select"
Version	 1.25s	06/14/17 Make playing and card present buttons reflect actual subchannel status (instead of using lock)
Version	 1.25r	05/03/17 Make record response buttons dim if no valid subchannel record info; rescale VU meters to Bill's specs; very slight fixes to labels
Version	 1.25q	04/17/17 Fix labels, make only responses dim (not buttons)
Version	 1.25p	03/24/17 Dim "Card Present" and "Play" when no connection to LB, also change VU meter limits
Version	 1.25o	03/07/17 Relaxed requirement that stop must be executed after any play, record, or fast forward/backward command
Version	 1.25n	11/10/16 Added delete file, fast forward, and fast backward
Version	 1.25m	10/06/16 Added ability to set playback volume on special stealth rec screen
Version	 1.25l	10/01/16 Flyron recorder supports playback; stinger address read correctly on startup
Version	 1.25k	09/29/16 Flyron recorder supports audio source, AD control, reloads log file on restart of GUI, add special stealth rec window
Version	 1.25j	09/24/16 Version for use with Flyron recorder
Version	 1.25i	06/15/16 New format for stealth command with command in nibble three
Version	 1.25h	05/08/16 Version with special stinger command window and stealth record button window
Version	 1.25b	01/14/14 A2100475 Added "Play audio" button
Version	 1.24f	10/30/13 Was A2100475 Fixed filter names
Version	 1.24e	10/30/13 Was A2100475, Card Present now reads "No Card" when card not present; fix internet configuration; hi/lo transmit power on controller initialized properly, also fixed sleeper power initialization problem (high power button selected when program first started, but was actually low power until toggled at least once)
Version	 1.24d	06/26/13 Change spectrum scan to -110 dBm, add Ladybug serial number to plot
Version	 1.24c	05/01/13 A2100449 Change bargraph scaling for non-dBm so that non-dBm and dBm are the same scale; also added audio menu item and changed "Ports" to "Ports/IP"
Version	 1.24b	04/29/13 Telnet stuff finally works
Version	 1.24a	04/26/13 Version for RD-1100, A2100446
Version	 1.23h	09/05/12 Changed "Enter Password" menu item to "Password Protected Window" and removed SD encryption key entry stuff on Password Window
Version	 1.23g	08/14/12 Still moving things around per Bill's preferences
Version	 1.23f	08/13/12 Moving things around per Bill's preferences
Version	 1.23e	08/10/12 Got playback to work
Version	 1.23d	08/04/12 Still working on playback
Version	 1.23c	08/01/12 Still working on playback, added TX id and TX voltage, Version for RD-1000
Version	 1.23b	07/31/12 Still working on playback, added record on/off and overwrite when full switches, Version for RD-1000
Version	 1.23a	07/25/12 Working on playback, Version for RD-1000
Version	 1.22a	06/29/12 Version for RD-1000, A2100402
Version	 1.21b	03/20/12 Fixed stinger schedule message length problem
Version	 1.21a	03/19/12 Fixed FM Transmitter and Control Transmitter labels, added Stinger Window
Version	 1.20a	03/15/12 Changed references back to CT-148 with FM transmitter, removed Tactical Repeater logo
Version	 1.10e	11/15/11 Removed last references to CT-148 and FM Transmitter
Version	 1.10d	11/14/11 Added "yellow" status to Tx status light indicating desired on, but no lock so turned off
Version	 1.10c	11/7/11 Fixing bytes per cluster reset when card swapped
Version	 1.10b	11/2/11 Fixing Tone No Lock--Cal Tone conflict (and also graph X-axis gridlines lie on even values)
Version	 1.10a	10/31/11 Released GUI A2100381
Version	 1.01d	10/31/11 Still fixing spectrum and SD card related issues
Version	 1.01c	10/28/11 Fixing spectrum and SD card related issues
Version	 1.01b	10/24/11 Cleaning up tactical repeater GUI; adding password menu
Version	 1.01a	10/20/11 Version for tactical repeater
Version	 1.00n	6/20/11 Fixed returning to proper channel after spectrum and channels; switched max range and low noise labels to the proper places, and fixed filter labels and selections
Version	 1.00m	6/20/11 Removed CT-148 reference that showed up in directory listings
Version	 1.00l	6/17/11 Rearranged order of filters and frequencies top to bottom
Version	 1.00k	6/17/11 Changed COM so going out of sync doesn't cause yellow light
Version	 1.00j	6/15/11 Prevented frequency from inserting itself into a button
Version	 1.00i	6/14/11 Close to final version---added retune after spectrum scan, fixed spectrum to scan when window brough up, added diag info to about window
Version	 1.00h	6/13/11 Yet another backup
Version	 1.00g	6/13/11 Yet another backup
Version	 1.00f	6/10/11 Yet another backup
Version	 1.00e	6/10/11 Just a backup Now that 1.00d works, I'm saving it much more
Version	 1.00d	6/10/11 Previous version broke hopelessly---that immpossible "Debug Assertion Failed!"---starting again
Version	 1.00c	6/8/11 Using CT-148 version for RD-1001
Version	 1.00b	5/6/11 Moved around display; moved "reset state" and "set clock" to password window
Version	 1.00a	5/5/11 This will be the first release
Version	 0.49d	5/4/11 Still working on USB/COM version
Version	 0.49c	5/3/11 Finally getting USB to work with COM---added select between USB and COM
Version	 0.49b	4/29/11 Trying to get debugger to work with USB
Version	 0.49a	4/??/11 Baseline that works with RS232 and USB
Version	 0.47b	3/28/11 Trying to get debugger to work
Version	 0.47a	3/25/11 Converted to Ladybug compatible commands
Version	 0.46a	3/14/11 Implemented COM port communication instead of USB
Version	 0.44e	3/5/08  No real change, just replaced "wasp" back with "Stinger" in variable names
Version	 0.44d	3/3/08  Fixed some stuff in reading from stinger file, etc
Version	 0.44c	2/26/08 Tried to fix Stinger stuff like address not initializing propery, etc
Version	 0.44b	2/25/08 Made clock increment automatically, added 'Windows" and 'CT-148' modes to clock time
Version	 0.44a	2/20/08 Fixed window captions, added channel mono/stereo scan, fixed blowup on stinger file missing, etc.
Version  0.42x  02/6/08 Attempting to get stinger window working in release mode
Version  0.41   02/4/08 Re-added check on Tx & Rx freq limits, changed door open light to yellow
Version  0.40   02/4/08 Removed check on Tx freq limits
Version  0.39j1 02/4/08 Fixed error in readResp() for RESP_READ_BYTES_PER_CLUSTER_LEN
Version  0.39j  02/1/08 Added SD error code windows (added a byte to ST response; up to 25 bytes)
Version  0.39d  01/31/08 Continued fixing bytes remaining
Version  0.39c  01/29/08 Continued fixing bytes remaining, added next file name
Version  0.39b  01/24/08 Fixed bytes remaining meters
Version  0.39   12/21/07 Fixed hysteresis stuff on debug window
Version  0.39   12/18/07 Added hysteresis stuff on debug, reversed filter buttons, added squelch (declick) button
Version  0.38d  12/4/07 Added minimize button
Version  0.38   10/17/07 Added clock stuff
Version  0.37   10/2/07  Added stinger record stuff
Version: 0.36h  10/2/07 (added schedule information)
Version: 0.36g  10/1/07 (added schedule information)
Version: 0.36f  9/25/07 (stinger generic control fleshed out)
Version: 0.36e  9/21/07 (more stinger fixes, started adding stinger status led)
Version: 0.36d  9/21/07 (fixed stinger on-off settings)
Version: 0.36c  9/20/07 (reversed order of customer ID nibbles)
Version: 0.36b  9/20/07 (fixed customer ID second nibble)
Version: 0.36a  9/20/07 (pre-set stinger address to BCD "6" for testing)
Version: 0.36  9/18/07 (some stinger additions)
Version: 0.35b  9/17/07 (added stinger ON/OFF switch)
Version: 0.35a  9/17/07 (stinger receiver ID set to 0x021, cust ID=006)
Version: 0.35  9/11/07 (adds stinger echo command)
Version: 0.34b 8/31/07 (re-activate stinger window)
Version: 0.34a 8/30/07(fixes LED locations, press Return on AGC window)
Version: 0.34  8/29/07 (fixes AGC local and remote)

by Mark Patten --- Tektron Micro Electronics

From Project: Main.cpp
Version: 3.0
Date: 7/18/05
by Jan Axelson (jan@Lvr.com)

Purpose: demonstrates USB communications with a HID-class device.

Description: 
	Finds an attached HID-class device that matches a specified Vendor ID and Product ID.
	Retrieves the HID's capabilities.
	Sends a report to the HID and receives a report from the HID.
	A list box displays a log of activity.
	A list box displays the most recent received report bytes.
	Clicking the Once button causes the application to exchange one set of reports.
	
This application was created with Visual C++ 6's AppWizard as a dialog-based application.

Companion firmware and other sample code is available from www.Lvr.com.

Send comments, questions, bug reports, etc. to jan@Lvr.com.

About overlapped I/O

The API function ReadFile retrieves Input reports from the HID driver's buffer. 
Non-overlapped ReadFile is a blocking call. 
If a report isn't available, the function waits.

With overlapped I/O, the call to ReadFile returns immediately. The application then calls 
WaitForSingleObject, which returns when either the data has arrived or the specified timeout has elapsed.

This application has been tested on Windows 98 SE, Windows 2000, and Windows XP.
*/

#include "stdafx.h"

#include "infinity.h"
#include "infinityDlg.h"
#include "cscanDlg.h"
#include "cPlaybackDlg.h"
#include "cdxCRotBevelLine.h"
#include "crc_ccitt.h"

#include <wtypes.h>
#include <initguid.h>
#include <windows.h>
#include "sys_clk.h"
#include "led_defs.h"
#include "cDebugWinDlg.h"
#include "cDebugAGCWinDlg.h"
#include "CChannelsDlg.h"
#include "CStingerDlg.h"
#include "settingsComDlg.h"
#include "msg_defs.h"
#include "oper_params.h"
#include "editFileName.h"
#include "com_port.h"
#include "config.h"
#include "julianTimeFunctions.h"
#include <afxsock.h>
#include "audioPlayerPath.h"
#include "specialStingerCmdDlg.h"
#include "stealthRecSpecialWindow.h"

#define MAX_LOADSTRING 256
#define INPUT_MSG_SYNC_TIMEOUT_MS (DWORD)2000


//#define INVALID_HANDLE_VALUE 9876;


extern "C" {

// This file is in the Windows DDK available from Microsoft.
#include "C:\WINDDK\3790.1830\inc\wxp\hidsdi.h"

#include <setupapi.h>
#include <dbt.h>
}

#include "afxwin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//function prototypes

void readFreqFile();
BOOL DeviceNameMatch(LPARAM lParam);
bool FindTheHID();
LRESULT Main_OnDeviceChange(WPARAM wParam, LPARAM lParam);
void CloseHandles();
void DisplayCurrentTime();
void DisplayFeatureReport();
void DisplayInputReport();
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	void DisplayLastError(CString Operation);
#endif
void GetDeviceCapabilities();
void PrepareForOverlappedTransfer();
void ScrollToBottomOfListBox(USHORT idx);
void ReadAndWriteToDevice();
void ReadInputReport();
void RegisterForDeviceNotifications();
void WriteOutputReport();
void statusReqCmd();
void updateStingerAddress(); // changed to static function 10/01/16

void writeCmd(int);
#if INTERFACE_USB==1
int readResp(int);
#endif

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	CString msgString;
#endif
float convert_AD_to_dBm(char);
unsigned int convert_AD_to_mag(char);
int convert_dBm_to_barGraph(float);
int convert_dBm_to_specGraph(float);
int limitFreqValRange(ULONG *freqVal);
int limitTxFreqValRange(ULONG *freqVal);
ULONG freq_3bytes_to_value(char*);

int calToneMode=0;
int	muteToneMode=0;
CButton *m_squelchOff;
//CButton *m_calToneOn;
CButton *m_calToneNoLockOff;
CButton *m_calToneNoLockOn;
CButton *m_stingerCmd;

void freqKHzToMHzString(ULONG,char *);
int	monoStereoSwapLRToggleFlag=0;
bool ComGood = FALSE; 
int	squelchMode=1;
int declickMode=1;

//Application global variables 
DWORD								ActualBytesRead;
DWORD								BytesRead;
DWORD								cbBytesRead;
DWORD								dwError;
bool								MyCOMDeviceDetected=FALSE; 
bool								MyUSBDeviceDetected = FALSE; 

DWORD								NumberOfBytesRead;
char								outMsgStr[256];
char								inMsgParams[256];
DWORD								ReportType;
int									msgFlag;
ULONG								setFreqKHz[8];
char freqValChars[50];
ULONG tuneFreqKHz=(long unsigned)333333;
ULONG txFreqKHz=0; //initialize to 0 indicating not set yet
ULONG respFreqKHz;
CButton *m_stereoOn;
void writeStingerCmdFile();


int txOnFlag=FALSE;

int audioFilterNum=5;
int inMsgType;
CString	strBytesWritten = "";
CScanDlg *pscanWinDlg;
CPlaybackDlg *playbackWinDlg;
CDialog *pDebugWinDlg;
CDialog *pDebugAGCWinDlg;
CDialog *pChannelsWinDlg;
CDialog *pStingerWinDlg;
CDialog *pEditFileNameWinDlg;
CBitmap Bmp1, Bmp2;
int doorOpenFlag=FALSE;
int cardDetectFlag=FALSE;
int sdErrorFlag=FALSE;
int writeProtectFlag=FALSE;
int antAActiveFlag=FALSE;
int antBActiveFlag=FALSE;
int msgStatus;
CString freqValString;
double freqValDouble;
CListBox	m_ResultsList;
CButton m_usbStatusButton;
int channelsWinFlag=0;
int debugWinFlag=0;
int debugAGCWinFlag=0;
int scanWinFlag=0;
int playbackWinFlag=0;
int playbackWinJustOpenned=0;
long unsigned playbackJulianVal=0;
int timerCountPlaybackStart=0;

int editFileNameWinFlag=0;
CButton		m_channelsWin;
CButton		m_scanWin;
//CButton		m_playbackWin;
CButton		m_stingerWinButton;
int chanNumLoop=0;
int bytesPerClusterDiv512=0;
CListBox *pnextFileNameText;
//CListBox *pRxVoltageText;
CButton *m_preemphasis;
CButton *m_agcLocal;
CButton *m_agcRemote;
CButton *m_ancRemote;
CStatic *m_timeStringText;
CStatic *m_stealthRecInfoText;
CStatic *m_dateStringText;
CStatic *m_rssiLeftLabelText;
CStatic *m_rssiRightLabelText;
CStatic *m_playbackModeStringText;
CButton	*m_txPower;
CButton *m_txFm;
CButton *m_txFmEnc;
CButton *m_txDst;
CStatic *m_msgSentCountTxt;
CStatic *m_msgSTRcvdCountTxt;
CStatic *m_msgSlipsTxt;
CStatic *m_stMsgRcvdCountTxt;
CDialog *pSettingsComDlg;
int ignoreNextSeveralSTResponses=0;
CListBox *m_txid;
CListBox *m_txVoltage;
//CListBox *m_audioLevels;
int ctrlTxMode=0; // initialize control TX mode to stereo
int resendPlaybackCommandCounter=0;

int stingerStatus=STINGER_IDLE;
int COMStatus;

//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
const char g_szClassName[] = "myWindowClass";
//extern HINSTANCE hInstanceMHP;

extern int continuousFlag;
int	prevContinuousFlag;
CButton *m_playbackButton;
CButton *m_recordButton;





/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


CStatic *m_minFreqTxt;
CStatic *m_maxFreqTxt;
CStatic *m_serialNumberTxt;
CStatic *m_RxVersionTxt;
CStatic *m_RxVoltageTxt;
int aboutWinFlag=0;
CListBox *m_recFileNumText;


BOOL CAboutDlg::OnInitDialog()
{
	m_minFreqTxt = (CStatic*)GetDlgItem(IDC_MIN_FREQ);
	m_maxFreqTxt = (CStatic*)GetDlgItem(IDC_MAX_FREQ);
	m_serialNumberTxt = (CStatic*)GetDlgItem(IDC_SERIAL_NUMBER);
	m_RxVersionTxt = (CStatic*)GetDlgItem(IDC_RECEIVER_FIRMWARE_VERSION);
	m_RxVoltageTxt = (CStatic*)GetDlgItem(IDC_RECEIVER_VOLTAGE);

//	aboutWinFlag=1;
	CDialog::OnInitDialog();
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
	return(TRUE);
}

void CAboutDlg::OnClose()
{
	aboutWinFlag=0;
	CDialog::OnClose();
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//}}AFX_DATA_INIT
}



#define IN_MSG_ST 1
#define IN_MSG_SA 2


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_FilterSelect, m_FilterSelect);
	DDX_Control(pDX, IDC_CHANNELSWINBUTTON, m_channelsWin);
	DDX_Control(pDX, IDC_SCANWINBUTTON, m_scanWin);
	DDX_Control(pDX, IDC_DECLICK, m_declick);
	DDX_Control(pDX, IDC_AntennaA, m_antennaA);
	DDX_Control(pDX, IDC_AntennaB, m_antennaB);
	DDX_Control(pDX, IDC_LeftAudio, m_leftAudio);
	DDX_Control(pDX, IDC_RightAudio, m_rightAudio);
	DDX_Control(pDX, IDC_USB_STATUS, m_usbStatusButton);
	DDX_Control(pDX, IDC_SDMemUsedBargraph, m_SDMemUsedBargraph);
	DDX_Control(pDX, IDC_RAMMemUsedBargraph, m_RAMMemUsedBargraph);
	DDX_Control(pDX, IDC_SERIAL_NUM, m_serialNumber);
//	DDX_Control(pDX, IDC_SUPPLYVOLTAGE, m_supplyVoltage);
	DDX_Control(pDX, IDC_VOLTAGE_READOUT_TEXT, m_voltageReadout);
	DDX_Control(pDX, IDC_SDMEMTOTAL, m_SDMemTotalTxt);
	DDX_Control(pDX, IDC_SDMEMUSED, m_SDMemUsedTxt);
	DDX_Control(pDX, IDC_TIME_REMAIN, m_timeRemain);
	DDX_Control(pDX, IDC_TIME_USED, m_timeUsed);
	DDX_Control(pDX, IDC_ANT_A_TEXT, m_antAText);
	DDX_Control(pDX, IDC_ANT_B_TEXT, m_antBText);
	DDX_Control(pDX, IDC_SQUELCH_ON, m_squelchOn);
	DDX_Control(pDX, IDC_CALTONE_ON, m_calToneCtrl);
//	DDX_Control(pDX, IDC_STINGERWINBUTTON, m_stingerWinButton);
	DDX_Control(pDX, IDC_SD_ERROR_TEXT, m_sdErrorText);
//	DDX_Control(pDX, IDC_REC_FILE_NUM_TEXT, m_recFileNumText);
	DDX_Control(pDX, IDC_MEMUSEDTEXT, m_memUsedText);
//	DDX_Control(pDX, IDC_PLAYBACKWINBUTTON, m_playbackWin);

}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	//ON_WM_PAINT()
 
	ON_BN_CLICKED(IDC_TX_POWER,OnBnClickedTxPower)
	ON_BN_CLICKED(IDC_CHANNELSWINBUTTON, OnBnClickedchannelswindow)
	ON_BN_CLICKED(IDC_SCANWINBUTTON, OnBnClickedscanwindow)


	ON_EN_CHANGE(IDC_Results, OnChangeResults)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_USB_STATUS, On_cmdFindMyDevice)
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_DEVICECHANGE, Main_OnDeviceChange)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FilterSelect, &CMainDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_FilterSelect, &CMainDlg::OnNMReleasedcaptureSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_FreqSelect, &CMainDlg::OnNMReleasedcaptureFreqselect)
	ON_BN_CLICKED(IDC_SetFreq, &CMainDlg::OnBnClickedSetfreq)
	ON_BN_CLICKED(IDC_LoadFreqs, &CMainDlg::OnBnClickedLoadfreqs)
	ON_BN_CLICKED(IDC_SaveFreqs, &CMainDlg::OnBnClickedSavefreqs)
	ON_BN_CLICKED(IDC_Filt400HzVerySharp, &CMainDlg::OnBnClickedFilt400HzVerySharp)
	ON_BN_CLICKED(IDC_Filt200HzVerySharp, &CMainDlg::OnBnClickedFilt200HzVerySharp)
//	ON_BN_CLICKED(IDC_Filt200HzVerySharpX, &CMainDlg::OnBnClickedFilt200HzVerySharpX)
	ON_BN_CLICKED(IDC_Filt200HzSharp, &CMainDlg::OnBnClickedFilt200HzSharp)
	ON_BN_CLICKED(IDC_Filt200Hz, &CMainDlg::OnBnClickedFilt200Hz)
	ON_BN_CLICKED(IDC_Filt100Hz, &CMainDlg::OnBnClickedFilt100Hz)
	ON_BN_CLICKED(IDC_FiltFlat, &CMainDlg::OnBnClickedFiltFlat)
	ON_BN_CLICKED(IDC_FreqVal1, &CMainDlg::OnBnClickedfreqval1)
	ON_BN_CLICKED(IDC_FreqVal2, &CMainDlg::OnBnClickedfreqval2)
	ON_BN_CLICKED(IDC_FreqVal3, &CMainDlg::OnBnClickedfreqval3)
	ON_BN_CLICKED(IDC_FreqVal4, &CMainDlg::OnBnClickedfreqval4)
	ON_BN_CLICKED(IDC_FreqVal5, &CMainDlg::OnBnClickedfreqval5)
	ON_BN_CLICKED(IDC_FreqVal6, &CMainDlg::OnBnClickedfreqval6)
	ON_BN_CLICKED(IDC_FreqVal7, &CMainDlg::OnBnClickedfreqval7)
	ON_BN_CLICKED(IDC_FreqVal8, &CMainDlg::OnBnClickedfreqval8)
	ON_BN_CLICKED(IDC_STEREO1, &CMainDlg::OnBnClickedStereo1)
	ON_BN_CLICKED(IDC_PREEMPHASIS, &CMainDlg::OnBnClickedPreemphasis)
	ON_BN_CLICKED(IDC_AGC_LOCAL, &CMainDlg::OnBnClickedAgcLocal)
	ON_BN_CLICKED(IDC_AGC_REMOTE, &CMainDlg::OnBnClickedAgcRemote)
	ON_BN_CLICKED(IDC_ANC_REMOTE, &CMainDlg::OnBnClickedAncRemote)
	ON_BN_CLICKED(IDC_LOCALRECORDBUTTON, &CMainDlg::OnBnClickedLocalRec)
//	ON_BN_CLICKED(IDC_STINGERWINBUTTON, &CMainDlg::OnBnClickedStingerwinbutton)
	ON_BN_CLICKED(IDC_TXSETFREQ, &CMainDlg::OnBnClickedTxsetfreq)
ON_EN_UPDATE(IDC_FMTRANSMITFREQ, &CMainDlg::OnEnUpdateFmtransmitfreq)
ON_BN_CLICKED(IDC_SWAP_LR, &CMainDlg::OnBnClickedSwapLr)
ON_BN_CLICKED(IDC_MONO_ON, &CMainDlg::OnBnClickedMonoOn)
ON_BN_CLICKED(IDC_SQUELCH_OFF, &CMainDlg::OnBnClickedSquelchoff)
ON_BN_CLICKED(IDC_CALTONE_OFF, &CMainDlg::OnBnClickedCalToneNotLockedOff)
ON_BN_CLICKED(IDC_CALTONE_NOLOCK, &CMainDlg::OnBnClickedCalToneNotLockedOn)
//ON_BN_CLICKED(IDC_CALTONE_ON, &CMainDlg::OnBnClickedCaltoneOn)
ON_BN_CLICKED(IDC_SQUELCH_ON, &CMainDlg::OnBnClickedSquelchOn)
ON_BN_CLICKED(IDC_Filt400HzVerySharp, &CMainDlg::OnBnClickedFilt400HzVerySharp)
//ON_BN_CLICKED(IDC_Filt200HzVerySharp, &CMainDlg::OnBnClickedFilt200HzVerySharp)
ON_BN_CLICKED(IDC_Filt400HzSharp, &CMainDlg::OnBnClickedFilt400HzSharp)
ON_BN_CLICKED(IDC_Filt200HzSharp, &CMainDlg::OnBnClickedFilt200HzSharp)
//ON_BN_CLICKED(IDC_Filt400HzShallow, &CMainDlg::OnBnClickedFilt200Hz)
//ON_BN_CLICKED(IDC_Filt200HzShallow, &CMainDlg::OnBnClickedFilt200HzShallow)
ON_BN_CLICKED(IDC_FiltFlat, &CMainDlg::OnBnClickedFiltFlat)
ON_BN_CLICKED(IDC_STINGER_CMD, &CMainDlg::OnBnClickedStingerCmd)
ON_BN_CLICKED(IDC_STINGER_ON, &CMainDlg::OnBnClickedStingerOn)
ON_BN_CLICKED(IDC_STINGER_OFF, &CMainDlg::OnBnClickedStingerOff)
ON_BN_CLICKED(IDC_STINGER_ALLOFF, &CMainDlg::OnBnClickedStingerAllOff)
ON_BN_CLICKED(IDC_EDITFILENAME, &CMainDlg::OnBnClickedEditfilename)
ON_BN_CLICKED(IDC_DECLICK, &CMainDlg::OnBnClickedDeclick)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_FreqSelect, &CMainDlg::OnNMCustomdrawFreqselect)
ON_COMMAND(ID_PROCESS_FILE, &CMainDlg::OnMenuProcessFile)
ON_COMMAND(ID_OPTIONS_PASSWORD, &CMainDlg::OnMenuPassword)
//ON_COMMAND(ID_OPTIONS_SPECIAL_STINGER_CMD, &CMainDlg::OnMenuSpecialStingerCmd)
ON_COMMAND(ID_STEALTH_REC_SPECIAL_FUNCTIONS, &CMainDlg::OnMenuStealthRecSpecialFunctions)
ON_LBN_SELCHANGE(IDC_FILENAME, &CMainDlg::OnLbnSelchangeFilename)
ON_LBN_SELCHANGE(IDC_VOLTAGE_READOUT_TEXT, &CMainDlg::OnLbnSelchangeVoltageReadoutText)
ON_EN_CHANGE(IDC_FREQ_VAL_TEXT, &CMainDlg::OnEnChangeFreqValText)
ON_BN_CLICKED(IDC_TRANSMITTER_FM, &CMainDlg::OnBnClickedTransmitterFm)
ON_BN_CLICKED(IDC_TRANSMITTER_FMENC, &CMainDlg::OnBnClickedTransmitterFmenc)
ON_BN_CLICKED(IDC_TRANSMITTER_DST, &CMainDlg::OnBnClickedTransmitterDst)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_LeftAudio, &CMainDlg::OnNMCustomdrawLeftaudio)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_AntennaA, &CMainDlg::OnNMCustomdrawAntennaa)
ON_BN_CLICKED(IDC_USE_USB, &CMainDlg::OnBnClickedUseUsb)
ON_BN_CLICKED(IDC_USE_COM, &CMainDlg::OnBnClickedUseCom)
ON_BN_CLICKED(IDC_TX_RESTORE_DEFAULT, &CMainDlg::OnBnClickedTxRestoreDefault)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_RAMMemUsedBargraph, &CMainDlg::OnNMCustomdrawRammemusedbargraph)
ON_LBN_SELCHANGE(IDC_SDMEMTOTAL, &CMainDlg::OnLbnSelchangeSdmemtotal)

ON_COMMAND(ID_SETTINGS_ABOUT, &CMainDlg::OnSettingsAbout)
ON_COMMAND(ID_PLAY_AUDIO, &CMainDlg::OnSettingsPlayAudio)
ON_COMMAND(IDC_PLAY_AUDIO, &CMainDlg::OnSettingsPlayAudio)
ON_COMMAND(ID_SETTINGS_AUDIO, &CMainDlg::OnBnClickedAudioSetupWin)

ON_COMMAND(ID_DB_USEDBM, &CMainDlg::OnBnClickedDbmMode)
ON_COMMAND(ID_PORT_TELNET, &CMainDlg::OnSettingsCom)
ON_COMMAND(ID_MISC_FULLSCALETONE, &CMainDlg::OnMiscFullscaletone)
ON_BN_CLICKED(IDC_POWER,OnBnClickedRxPower)

ON_COMMAND(ID_WINDOWS_REMOTEPLAYER, &CMainDlg::OnWindowsRemoteplayer)
ON_COMMAND(ID_WINDOWS_CHANNELS, &CMainDlg::OnWindowsChannels)
//ON_COMMAND(ID_WINDOWS_CONTROLTX, &CMainDlg::OnBnClickedStingerwinbutton)
ON_COMMAND(ID_WINDOWS_SCAN, &CMainDlg::OnWindowsScan)
ON_STN_CLICKED(IDC_ST_MSG_RCVD_COUNT, &CMainDlg::OnStnClickedStMsgRcvdCount)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SDMemUsedBargraph, &CMainDlg::OnNMCustomdrawSdmemusedbargraph)
ON_LBN_SELCHANGE(IDC_SERIAL_NUM, &CMainDlg::OnLbnSelchangeSerialNum)
ON_BN_CLICKED(IDC_CTL_TX_PWR_LOW, &CMainDlg::OnBnClickedCtlTxPwrLow)
ON_BN_CLICKED(IDC_CTL_TX_PWR_HI, &CMainDlg::OnBnClickedCtlTxPwrHi)
ON_BN_CLICKED(IDC_SLEEPER2_PWR_HI, &CMainDlg::OnBnClickedSleeper2PwrHi)
ON_BN_CLICKED(IDC_SLEEPER2_PWR_LOW, &CMainDlg::OnBnClickedSleeper2PwrLow)
ON_BN_CLICKED(IDC_PLAYBACK_MODE_PLAYBACK, &CMainDlg::OnBnClickedPlaybackwinbutton)
ON_LBN_SELCHANGE(IDC_SD_ERROR_TEXT, &CMainDlg::OnLbnSelchangeSdErrorText)
ON_BN_CLICKED(IDC_RECORDMODE, &CMainDlg::OnBnClickedRecordmode)
ON_BN_CLICKED(IDC_OVERWRITEWHENFULL, &CMainDlg::OnBnClickedOverwriteWhenFull)
ON_BN_CLICKED(IDC_CTRL_TX_STEREO, &CMainDlg::OnBnClickedCtrlTxStereo)
ON_BN_CLICKED(IDC_CTRL_TX_MONO_L, &CMainDlg::OnBnClickedCtrlTxMonoL)
ON_BN_CLICKED(IDC_CTRL_TX_MONO_R, &CMainDlg::OnBnClickedCtrlTxMonoR)
ON_BN_CLICKED(IDC_OFF_STATE, &CMainDlg::OnBnClickedOffState)
ON_BN_CLICKED(IDC_ON_STATE, &CMainDlg::OnBnClickedOnState)
ON_COMMAND(ID_ADDRESSLIST_DELETECURRENTADDRESS, &CMainDlg::OnAddresslistDeletecurrentaddress)
ON_COMMAND(ID_ADDRESSLIST_DELETEALLADDRESSES, &CMainDlg::OnAddresslistDeletealladdresses)
ON_BN_CLICKED(IDC_PLAYBACK_MODE_LIVE, &CMainDlg::OnBnClickedPlaybackModeLive)
ON_BN_CLICKED(IDC_PLAYBACK_STOP, &CMainDlg::OnBnClickedPlaybackStop)
ON_BN_CLICKED(IDC_PLAYBACK_START, &CMainDlg::OnBnClickedPlaybackStart)
ON_STN_CLICKED(IDC_CARD_PRESENT_MSG, &CMainDlg::OnStnClickedCardPresentMsg)
ON_COMMAND(ID_SETSLEEPERMODE, &CMainDlg::OnModeSetSleepermode)
ON_COMMAND(ID_SETSTEALTHRECORDMODE, &CMainDlg::OnModeSetstealthrecordmode)
ON_BN_CLICKED(IDC_STEALTHREC_RECORD, &CMainDlg::OnStealthRecRecord)
ON_BN_CLICKED(IDC_STEALTHREC_STOP, &CMainDlg::OnStealthRecStop)
ON_BN_CLICKED(IDC_STEALTHREC_PLAY, &CMainDlg::OnStealthRecPlay)
ON_BN_CLICKED(IDC_STEALTHREC_REWIND, &CMainDlg::OnStealthRecRewind)
ON_BN_CLICKED(IDC_STEALTHREC_FF2END, &CMainDlg::OnStealthRecFF2End)
ON_BN_CLICKED(IDC_STEALTHREC_REPEAT, &CMainDlg::OnStealthRecRepeat)
ON_BN_CLICKED(IDC_STEALTHREC_QUAL_128KBPS, &CMainDlg::OnStealthRecQual128Kbps)
ON_BN_CLICKED(IDC_STEALTHREC_QUAL_96KBPS, &CMainDlg::OnStealthRecQual96Kbps)
ON_BN_CLICKED(IDC_STEALTHREC_QUAL_64KBPS, &CMainDlg::OnStealthRecQual64Kbps)
ON_BN_CLICKED(IDC_STEALTHREC_QUAL_32KBPS, &CMainDlg::OnStealthRecQual32Kbps)
ON_STN_CLICKED(IDC_RECORD_STATUS_MSG, &CMainDlg::OnStnClickedRecordStatusMsg)
ON_BN_CLICKED(IDC_STEALTHREC_MODE_STEREO, &CMainDlg::OnStealthRecModeStereo)
ON_BN_CLICKED(IDC_STEALTHREC_MODE_MONO, &CMainDlg::OnStealthRecModeMono)

ON_LBN_SELCHANGE(IDC_REC_FILE_NUM_TEXT, &CMainDlg::OnLbnSelchangeRecFileNumText)
ON_LBN_DBLCLK(IDC_REC_FILE_NUM_TEXT, &CMainDlg::OnLbnDblclkRecFileNumText)
ON_LBN_SETFOCUS(IDC_REC_FILE_NUM_TEXT, &CMainDlg::OnLbnSetfocusRecFileNumText)
ON_LBN_KILLFOCUS(IDC_REC_FILE_NUM_TEXT, &CMainDlg::OnLbnKillfocusRecFileNumText)
ON_BN_CLICKED(IDC_DPI_96, &CMainDlg::OnBnClickedDpi96)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

CDC *drawingContextMain;
CDC *drawingContextStinger;
CEdit *m_FreqValue;
CEdit *m_txFreqValue;
CButton *m_swapLr;
CSliderCtrl *m_FreqSelect;
CButton *m_stingerOn;
CButton *m_stingerOff;
CButton *m_monoOn;
CButton *m_useUSB;
CButton *m_useCOM;
CButton *m_Filt400HzVerySharp;
CButton *m_Filt200HzVerySharp;
CButton *m_Filt400HzSharp;
CButton *m_Filt200HzSharp;
CButton *m_Filt200Hz;
CButton *m_Filt100Hz;
CButton *m_FiltFlat;
CButton *m_setFreq;
CButton *m_FreqVal1;
CButton *m_FreqVal2;
CButton *m_FreqVal3;
CButton *m_FreqVal4;
CButton *m_FreqVal5;
CButton *m_FreqVal6;
CButton *m_FreqVal7;
CButton *m_FreqVal8;
CButton *m_rxPower;
CButton *m_recordmode;
CButton *m_overwriteWhenFull;
CButton *m_offState;
CButton *m_onState;
CButton	*p_liveButton;
CButton	*p_playbackButton;
CButton *m_stealthRecSourceMono;
CButton *m_stealthRecSourceStereo;


int	com_not_init_counter=0;
int	usb_not_init_counter=0;

void readStingerCmdFile();
CMenu *pSysMenu;
int dbmMode;
CMenu myMenu;
int controlTxPower=0; // initialize control transmitter to low power
int sleeper2Power=1; // initialize sharp end transmitter to high power
CComboBox *m_controlTxAddress;
void julianTest();
CStatic *m_playbackMsg;
CStatic *m_recStatusMsg;
CStatic *m_recCardPresentMsg;
CStatic *m_cardPresentMsg;
CStatic *m_recordStatusMsg;
CStatic *m_sdErrorMsg;
CStatic *m_txmtMsg;
CStatic *pStealthRecStartTimeText;
CEdit *m_stealthRecNextFileNum;


CDateTimeCtrl* pPlaybackTime;
CDateTimeCtrl* pStealthRecPlayTime;
int unknownPlaybackStatus=1;
int stealthRecPlayLiveStatus=0;
extern int stealthRecordWindowMode;
int stealthRecPlaybackStatus=0;
//int stealthRecInputMode=0;
int stealthRecSelInputMode=0;
int stealthRecSelQual=0;
extern int stealthRecQual;
extern int stealthRecMode;
char displayString[40];
extern long unsigned int recNextFileNum;
void setStealthRecStatusLED();
int stealthRecStatus=0;
int stealthRecMediumStatus=0;

afx_msg void CMainDlg::OnPaint() {
	CDialog::OnPaint();
	if (stealthRecordWindowMode==1) {
		if (stealthRecPlayLiveStatus==1) {
//			setIndicatorLight(STREC_PLAY_STATUS_LED,LED_GREEN,drawingContextMain);
//			setIndicatorLight(STREC_LIVE_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
		} else {
//			setIndicatorLight(STREC_PLAY_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
//			setIndicatorLight(STREC_LIVE_STATUS_LED,LED_GREEN,drawingContextMain);
		}
		if (stealthRecPlaybackStatus==1) {
			setIndicatorLight(STREC_RECORD_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
		} else {
			setIndicatorLight(STREC_RECORD_STATUS_LED,LED_DARK_RED,drawingContextMain);
		}
		if (stealthRecPlaybackStatus==2) {
			setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_GREEN,drawingContextMain);
		} else {
			setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
		}
		setStealthRecStatusLED();

	}
}

BOOL CMainDlg::OnInitDialog()
{
//    julianTest();

	msgString.GetBuffer(200); // Initialize message string
	m_monoOn = (CButton*) GetDlgItem(IDC_MONO_ON);
	m_stereoOn = (CButton*) GetDlgItem(IDC_STEREO1);
	m_useCOM = (CButton*) GetDlgItem(IDC_USE_COM);
	m_useUSB = (CButton*) GetDlgItem(IDC_USE_USB);
	m_useCOM->SetCheck(BST_CHECKED);
	m_useUSB->SetCheck(BST_UNCHECKED);
	m_setFreq = (CButton*) GetDlgItem(IDC_SetFreq);
	m_Filt200Hz = (CButton*)GetDlgItem(IDC_Filt200Hz);
	m_Filt100Hz = (CButton*)GetDlgItem(IDC_Filt100Hz);
	m_Filt200HzSharp = (CButton*)GetDlgItem(IDC_Filt200HzSharp);
	m_Filt400HzSharp = (CButton*)GetDlgItem(IDC_Filt400HzSharp);
	m_Filt200HzVerySharp = (CButton*)GetDlgItem(IDC_Filt200HzVerySharp);
	m_Filt400HzVerySharp = (CButton*)GetDlgItem(IDC_Filt400HzVerySharp);
	m_FiltFlat = (CButton*)GetDlgItem(IDC_FiltFlat);
	m_FreqVal1 = (CButton*)GetDlgItem(IDC_FreqVal1);
	m_FreqVal2 = (CButton*)GetDlgItem(IDC_FreqVal2);
	m_FreqVal3 = (CButton*)GetDlgItem(IDC_FreqVal3);
	m_FreqVal4 = (CButton*)GetDlgItem(IDC_FreqVal4);
	m_FreqVal5 = (CButton*)GetDlgItem(IDC_FreqVal5);
	m_FreqVal6 = (CButton*)GetDlgItem(IDC_FreqVal6);
	m_FreqVal7 = (CButton*)GetDlgItem(IDC_FreqVal7);
	m_FreqVal8 = (CButton*)GetDlgItem(IDC_FreqVal8);
	m_preemphasis = (CButton*)GetDlgItem(IDC_PREEMPHASIS);
	m_agcLocal = (CButton*)GetDlgItem(IDC_AGC_LOCAL);
	m_agcRemote = (CButton*)GetDlgItem(IDC_AGC_REMOTE);
	m_ancRemote = (CButton*)GetDlgItem(IDC_ANC_REMOTE);
	m_timeStringText = (CStatic*)GetDlgItem(IDC_TIMESTRING);
	m_dateStringText = (CStatic*)GetDlgItem(IDC_DATESTRING);
	m_rssiLeftLabelText = (CStatic*)GetDlgItem(IDC_RSSI_LEFTLABEL);
	m_rssiRightLabelText = (CStatic*)GetDlgItem(IDC_RSSI_RIGHTLABEL);
	m_playbackModeStringText = (CStatic*)GetDlgItem(IDC_PLAYBACKMODESTRING);
	m_txPower=(CButton*)GetDlgItem(IDC_TX_POWER);
	m_txFm=(CButton*)GetDlgItem(IDC_TRANSMITTER_FM);
	m_txFmEnc =(CButton*)GetDlgItem(IDC_TRANSMITTER_FMENC);
	m_txDst =(CButton*)GetDlgItem(IDC_TRANSMITTER_DST);
	m_rxPower =(CButton*)GetDlgItem(IDC_POWER);
	m_msgSentCountTxt = (CStatic*)GetDlgItem(IDC_MSG_SENT_COUNT);
	m_msgSTRcvdCountTxt = (CStatic*)GetDlgItem(IDC_ST_MSG_RCVD_COUNT);
	m_msgSlipsTxt = (CStatic*)GetDlgItem(IDC_MSG_SLIPS);
	m_stMsgRcvdCountTxt = (CStatic*)GetDlgItem(IDC_ST_MSG_RCVD_COUNT);
	pnextFileNameText = (CListBox*)GetDlgItem(IDC_FILENAME);
//	pRxVoltageText = (CListBox*)GetDlgItem(IDC_RECEIVER_VOLTAGE);
	m_FreqValue = (CEdit*) GetDlgItem(IDC_FREQ_VAL_TEXT);
	m_txFreqValue = (CEdit*) GetDlgItem(IDC_FMTRANSMITFREQ);
//	m_calToneNoLockOn = (CButton*) GetDlgItem(IDC_CALTONE_ON);
	m_calToneNoLockOff = (CButton*) GetDlgItem(IDC_CALTONE_OFF);
	m_calToneNoLockOn = (CButton*) GetDlgItem(IDC_CALTONE_NOLOCK);
	m_stingerCmd = (CButton*) GetDlgItem(IDC_STINGER_CMD);
	m_swapLr=(CButton*) GetDlgItem(IDC_SWAP_LR);
	m_FreqSelect=(CSliderCtrl *) GetDlgItem(IDC_FreqSelect);
	m_stingerOn=(CButton*)GetDlgItem(IDC_STINGER_ON);
	m_stingerOff=(CButton*)GetDlgItem(IDC_STINGER_OFF);
	m_controlTxAddress=(CComboBox*)GetDlgItem(IDC_STINGER_ADDRESS2);
	m_recordmode=(CButton*)GetDlgItem(IDC_RECORDMODE);
	m_overwriteWhenFull=(CButton*)GetDlgItem(IDC_OVERWRITEWHENFULL);
	m_txid=(CListBox*)GetDlgItem(IDC_TXID);
	m_rawSubchBytes=(CListBox*)GetDlgItem(IDC_RAW_SUBCH_BYTES);
	m_txVoltage=(CListBox*)GetDlgItem(IDC_TXVOLTAGE);
//    m_audioLevels=(CListBox*)GetDlgItem(IDC_AudioLevels);

	m_playbackMsg = (CStatic*)GetDlgItem(IDC_PLAYBACK_MESSAGE);
    m_recStatusMsg = (CStatic*)GetDlgItem(IDC_RECORDER_MSG);
    m_recCardPresentMsg = (CStatic*)GetDlgItem(IDC_RECORDER_CARD_PRESENT);

	m_cardPresentMsg = (CStatic*)GetDlgItem(IDC_CARD_PRESENT_MSG);
	m_recordStatusMsg = (CStatic*)GetDlgItem(IDC_RECORD_STATUS_MSG);
	m_sdErrorMsg = (CStatic*)GetDlgItem(IDC_SDERROR_MSG);
	m_txmtMsg = (CStatic*)GetDlgItem(IDC_TXMT_MSG);
//    pStealthRecStartTimeText = (CStatic*)GetDlgItem(IDC_STEALTH_REC_TIME_TEXT);
	m_playbackMsg->SetWindowTextA(" ");

//	pStealthRecStartTimeText->SetWindowTextA(" ");
	pPlaybackTime=(CDateTimeCtrl *)GetDlgItem(IDC_PLAYBACK_TIME);
	pPlaybackTime->SetFormat(_T("dd-MMM-yyyy   hh:mm:ss tt "));
	p_liveButton=(CButton*)GetDlgItem(IDC_PLAYBACK_MODE_LIVE);
	p_playbackButton=(CButton*)GetDlgItem(IDC_PLAYBACK_MODE_PLAYBACK);

    controlTxPower=0; // make sure initialized to low power

	m_offState=(CButton*)GetDlgItem(IDC_OFF_STATE);
	m_onState=(CButton*)GetDlgItem(IDC_ON_STATE);

	
	CButton *m_temp;
	m_temp=(CButton*)GetDlgItem(IDC_CTL_TX_PWR_LOW);
	m_temp->SetCheck(BST_CHECKED); // start out low power

	m_temp=(CButton*)GetDlgItem(IDC_CTL_TX_PWR_HI);
	m_temp->SetCheck(BST_UNCHECKED); // start out low power

	sleeper2Power=1; // make sure initialized to high power
 	m_temp=(CButton*)GetDlgItem(IDC_SLEEPER2_PWR_HI);
	m_temp->SetCheck(BST_CHECKED); // start out high power

	m_temp=(CButton*)GetDlgItem(IDC_SLEEPER2_PWR_LOW);
	m_temp->SetCheck(BST_UNCHECKED); // start out high power

	m_controlTxAddress=(CComboBox*)GetDlgItem(IDC_STINGER_ADDRESS2);

	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_STEREO);
	m_temp->SetCheck(BST_CHECKED); // start out stereo mode
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_L);
	m_temp->SetCheck(BST_UNCHECKED); // start out stereo mode
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_R);
	m_temp->SetCheck(BST_UNCHECKED); // start out stereo mode



// Add Menu
	myMenu.LoadMenu(IDR_MENU2);
	BOOL result = SetMenu(&myMenu);

	drawingContextMain=this->GetDC();

	m_stealthRecNextFileNum = (CEdit*) GetDlgItem(IDC_STEALTH_REC_NEXT_FILE_NUM);
	m_stealthRecInfoText = (CStatic*)GetDlgItem(IDC_STEALTHRECINFO);
	m_recFileNumText=(CListBox*)GetDlgItem(IDC_REC_FILE_NUM_TEXT);
	InitStealthRecStatus();

	m_temp=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_128KBPS);
	if (stealthRecQual==0) {
		m_temp->SetCheck(BST_CHECKED);
	} else {
		m_temp->SetCheck(BST_UNCHECKED);
	}
	m_temp=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_96KBPS);
	if (stealthRecQual==1) {
		m_temp->SetCheck(BST_CHECKED);
	} else {
		m_temp->SetCheck(BST_UNCHECKED);
	}

	m_temp=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_64KBPS);
	if (stealthRecQual==2) {
		m_temp->SetCheck(BST_CHECKED);
	} else {
		m_temp->SetCheck(BST_UNCHECKED);
	}
	m_temp=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_32KBPS);
	if (stealthRecQual==3) {
		m_temp->SetCheck(BST_CHECKED);
	} else {
		m_temp->SetCheck(BST_UNCHECKED);
	}


	m_stealthRecSourceMono=(CButton*)GetDlgItem(IDC_STEALTHREC_MODE_MONO);
	if (stealthRecMode==1) {
		m_stealthRecSourceMono->SetCheck(BST_CHECKED);
	} else {
		m_stealthRecSourceMono->SetCheck(BST_UNCHECKED);
	}
	m_stealthRecSourceStereo=(CButton*)GetDlgItem(IDC_STEALTHREC_MODE_STEREO);
	if (stealthRecMode==2) {
		m_stealthRecSourceStereo->SetCheck(BST_CHECKED);
	} else {
		m_stealthRecSourceStereo->SetCheck(BST_UNCHECKED);
	}
	m_recordButton=(CButton*)GetDlgItem(IDC_STEALTHREC_RECORD);
	m_playbackButton=(CButton*)GetDlgItem(IDC_STEALTHREC_PLAY);

	
	sprintf(displayString,"%d",recNextFileNum);
	m_stealthRecNextFileNum->SetWindowTextA(displayString);

	setStealthRecordWindow();


	CDialog::OnInitDialog();


// Add option to system menu
	pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// check set sleeper mode by default
//	myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_CHECKED | MF_BYCOMMAND);
//	myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_UNCHECKED | MF_BYCOMMAND);

	restoreConfigFromFile();
	//My declares begin here

#if 1==0
	HWND hUpCtl;

	/* The button is control IDC_BUTTON2 */
	hUpCtl = (HWND)GetDlgItem( IDC_BUTTON2 );

	/* The icon is IDI_UP in the resource file */
	HICON hU = (HICON)::LoadImage( AfxGetResourceHandle(),
			MAKEINTRESOURCE( IDI_USBGOOD ),
			IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR );

	::SendMessage( hUpCtl, BM_SETIMAGE, IMAGE_ICON,
			(LPARAM) (DWORD) hU );
#endif


	Bmp1.LoadBitmap(IDB_BITMAP1);
	Bmp2.LoadBitmap(IDB_BITMAP2);

//	updateIndicatorLights();

	int		ByteToSend = 0;
	CString	strByteToSend = "";
	CString	strComboBoxText="";
	m_FilterSelect.SetRange(1, 7);
	m_FilterSelect.SetTicFreq(1);
	audioFilterNum=7-m_FilterSelect.GetPos();

	m_FreqSelect->SetRange(1, 8);
	m_FreqSelect->SetTicFreq(1);

   setFreqKHz[0]=MIN_FREQ_KHZ;
   setFreqKHz[1]=MIN_FREQ_KHZ+1*25;
   setFreqKHz[2]=MIN_FREQ_KHZ+2*25;
   setFreqKHz[3]=MIN_FREQ_KHZ+3*25;
   setFreqKHz[4]=MIN_FREQ_KHZ+4*25;
   setFreqKHz[5]=MIN_FREQ_KHZ+5*25;
   setFreqKHz[6]=MIN_FREQ_KHZ+6*25;
   setFreqKHz[7]=MAX_FREQ_KHZ;

//   readFreqFile();
   tuneFreqKHz=setFreqKHz[0];
	freqKHzToMHzString(respFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	/*
	My code begins here.
	Anything that needs to happen when the application starts goes in this routine.
	*/

	//Populate the combo boxes with values from 00 to FF.

#if XINTERFACE_USB==1
	setUSBStatus(0); // Set USB indicators to not attached
#else
//	setCOMStatus(COM_STATUS_UNINITIALIZED); // Set COM indicators to uninitialized
#endif

    m_antennaA.SetRange(0,255);
    m_antennaB.SetRange(0,255);
    m_leftAudio.SetRange(0,255);
	m_leftAudio.SetLayeredWindowAttributes(RGB(255,255,0),255,LWA_COLORKEY);

    m_rightAudio.SetRange(0,255);
	m_SDMemUsedBargraph.SetRange(0,255);
	m_RAMMemUsedBargraph.SetRange(0,255);
//	m_supplyVoltage.SetRange(0,100);
//	m_supplyVoltage.SetBkColor(RGB(255, 0, 0));
//	m_supplyVoltage.SetLayeredWindowAttributes(RGB(255,255,0),255,LWA_COLORKEY);

#if XINTERFACE_USB==1
	FindTheHID();
#else
	enableSetOperCmdButtons(FALSE);
	init_com_port();

// blank display
	CMainDlg::blankMainDisplayIndicators();


	if (ComGood) {
		enableSetOperCmdButtons(TRUE);
	} else {
		enableSetOperCmdButtons(FALSE);
	}

#endif

// Disable non-implemented buttons
	m_SDMemUsedBargraph.EnableWindow(TRUE);
	m_RAMMemUsedBargraph.EnableWindow(TRUE);
//	m_timeRemain.EnableWindow(FALSE);
	m_timeRemain.EnableWindow(TRUE);
	m_timeUsed.EnableWindow(TRUE);
	m_SDMemUsedTxt.EnableWindow(TRUE);
	m_SDMemTotalTxt.EnableWindow(TRUE);
//	m_stingerWinButton.EnableWindow(FALSE);

	// Set up dialog item pointer
//	m_squelchOn = (CButton*)GetDlgItem(IDC_SQUELCH_ON);
	m_squelchOff = (CButton*)GetDlgItem(IDC_SQUELCH_OFF);

// Initialize settings from configuration file
	readStingerCmdFile();  // since stingerWinFlag==0 this only reads current address address

// Start in continuous mode
	continuousFlag=1;
	prevContinuousFlag=continuousFlag;
	SetTimer(ID_TIMER_CONTINUOUS, STATUS_UPDATE_TIME, NULL);
#if USE_SEPARATE_USB_TIMER==1
	SetTimer(ID_TIMER_USB_READ, USB_UPDATE_TIME, NULL);
#endif


//	pStealthRecPlayTime=(CDateTimeCtrl *)GetDlgItem(IDC_STEALTHREC_STARTTIME);
//	pStealthRecPlayTime->SetFormat(_T("dd-MMM-yyyy   hh:mm tt "));


	//end my code

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
#if 1==0
void CMainDlg::OnPaint() {
/* //start new code
  Graphics *g = pe->Graphics;
   g->Clear(Color::AntiqueWhite);

   Rectangle rect = Form::ClientRectangle;
   Rectangle smallRect;
   smallRect.X = rect.X + rect.Width / 4;
   smallRect.Y = rect.Y + rect.Height / 4;
   smallRect.Width = rect.Width / 2;
   smallRect.Height = rect.Height / 2;

   Pen* redPen = gcnew Pen(Color::Red);
   redPen->Width = 4;
   g->DrawLine(redPen, 0, 0, rect.Width, rect.Height);

   Pen* bluePen = gcnew Pen(Color::Blue);
   bluePen->Width = 10;
   g->DrawArc( bluePen, smallRect, 90, 270 );
//end new code */

/*
CPaintDC dc(this); // device context for painting
	CBitmap BmpLady;
	CDC MemDCLady;
		// Load the bitmap from the resource
	BmpLady.LoadBitmap(IDB_BITMAP4);
	// Create a memory device compatible with the above CPaintDC variable
	MemDCLady.CreateCompatibleDC(&dc);
	// Select the new bitmap
	CBitmap *BmpPrevious = MemDCLady.SelectObject(&BmpLady);

	// Copy the bits from the memory DC into the current dc
	dc.BitBlt(200, 555, 436, 364, &MemDCLady, 0, 0, SRCCOPY);

	// Restore the old bitmap
//	dc.SelectObject(BmpPrevious);
	// Do not call CView::OnPaint() for painting messages
*/

    updateIndicatorLights();
//	updateStingerStatusLED();
/*
	if (stingerStatus==STINGER_IDLE) {
		if (m_stingerCmd->GetCheck()==BST_CHECKED) {
			setIndicatorLight(STINGER_TX_STATUS_LED,LED_GREEN,drawingContextMain);
		} else {
//			setIndicatorLight(STINGER_STATUS_LED,LED_DARK_RED,drawingContextMain);
			setIndicatorLight(STINGER_TX_STATUS_LED,LED_GREEN,drawingContextMain);
		}
	} else if (stingerStatus==STINGER_TXMITTING) {
		setIndicatorLight(STINGER_TX_STATUS_LED,LED_YELLOW,drawingContextMain);
	} else	setIndicatorLight(STINGER_TX_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
*/

//	if (continuousFlag!=prevContinuousFlag) {
//		if (continuousFlag=1) SetTimer(ID_TIMER_CONTINUOUS, 10, NULL);
//		else KillTimer(ID_TIMER_CONTINUOUS);
//		prevContinuousFlag=continuousFlag;
//	}

	if (IsIconic())	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else	{
		CDialog::OnPaint();
	}
}
#endif

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CMainDlg::OnClose() 
{
	//Anything that needs to occur on closing the application goes here.
	//Free any resources used by previous API calls and still allocated.

	CDialog::OnClose();
}


void CMainDlg::On_cmdFindMyDevice()  {

// Formerly a compiler directive; now initialize both USB and COM
//#if XINTERFACE_USB==1
	CMainDlg::FindTheHID();
//	if (prevContinuousFlag!=continuousFlag) {
//		if (continuousFlag=1) SetTimer(ID_TIMER_CONTINUOUS, 10, NULL);
//		else KillTimer(ID_TIMER_CONTINUOUS);
//		prevContinuousFlag=continuousFlag;
//	}
//#else
	init_com_port();
// blank display
	CMainDlg::blankMainDisplayIndicators();

//#endif
}



void CMainDlg::OnOK() {
	int x;
	CWnd *focus;
	focus=GetFocus();
	if (focus==m_FreqValue) {
		CMainDlg::OnBnClickedSetfreq();
	} else if (focus==m_txFreqValue) {
		CMainDlg::OnBnClickedTxsetfreq();
	}
}


void CMainDlg::OnBnClickedTxPower() 
{
	//Click the Power button to toggle power

	if (txOnFlag==FALSE) {
		txOnFlag=TRUE;
//		m_txPower.SetWindowTextA("Tx On");
	} else {
		txOnFlag=FALSE;
//		m_txPower.SetWindowTextA("Tx Off");
	}
	txStatusSet();
}

//extern CDialog *pChannelsWinDlg;
int saveFreqPos;

void CMainDlg::OnBnClickedchannelswindow() 
{
	if (channelsWinFlag==0) {

//create the channels window.
		channelsWinFlag=1;
		pChannelsWinDlg = new CChannelsDlg(this);
		CStatic x;
		BOOL ret=pChannelsWinDlg->Create(IDD_CHANNELSWINDOW,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating Dialog");
        pChannelsWinDlg->ShowWindow(SW_SHOW);

// Dim Channels Window button
		m_channelsWin.EnableWindow(FALSE);

// Save current frequency for reseting after closing channels window
		saveFreqPos=m_FreqSelect->GetPos();
// Start timer for cycling through channels

		SetTimer(ID_TIMER_CHANNELS, CHANNELS_CYCLE_TIME, NULL);
		chanNumLoop=0;

	}
}

void CMainDlg::OnBnClickedscanwindow() 
{
	if (scanWinFlag==0) {
		pscanWinDlg = new CScanDlg();
//		scanDrawingContext = new CDC();

		BOOL ret=pscanWinDlg->Create(IDD_SCANWINDOW,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating Dialog");
        pscanWinDlg->ShowWindow(SW_SHOW);

// Dim Channels Window button
		m_scanWin.EnableWindow(FALSE);
		scanWinFlag=1;
// Save current frequency for reseting after closing channels window
		saveFreqPos=m_FreqSelect->GetPos();

	}

}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg) {
	int retuneFlag=0;
	int freqPos;
	if(pMsg->message == WM_KEYDOWN) {
/*		if(pMsg->wParam == VK_DOWN) {
			freqPos=m_FreqSelect->GetPos();
			if (freqPos<8) {
				freqPos++;
				retuneFlag=1;
			}
		} else if (pMsg->wParam == VK_UP) {
			freqPos=m_FreqSelect->GetPos();
			if (freqPos>1) {
				freqPos--;
				retuneFlag=1;
			}
		} else */
		if (pMsg->wParam == 0x046) { // an 'f' pressed
			freqPos=m_FreqSelect->GetPos();
			freqPos--;
			if (freqPos<1) {
				freqPos=8;
			}
			retuneFlag=1;
		}
		if (retuneFlag==1) {
			switch(9-freqPos) {
				case 1:{m_FreqVal1->SetFocus();break;}
				case 2:{m_FreqVal2->SetFocus();break;}
				case 3:{m_FreqVal3->SetFocus();break;}
				case 4:{m_FreqVal4->SetFocus();break;}
				case 5:{m_FreqVal5->SetFocus();break;}
				case 6:{m_FreqVal6->SetFocus();break;}
				case 7:{m_FreqVal7->SetFocus();break;}
				case 8:{m_FreqVal8->SetFocus();break;}
			}
			tuneFreqKHz=setFreqKHz[8-freqPos];
			setFreqOperCmd();
		}
	}
	return CDialog::PreTranslateMessage(pMsg);  
}



int scanLoopCtr=0;
int timerCommandCounter=0;
char SDFileNameStr[9]={'!','!','!','!','!','!','!','!',0};
char prevSDFileNameStr[9]={'x','x','x','x','x','x','x','x',0};
//char prevSDFileNameStr[9];
extern int COMStatus;
int msgSentCount=0;
extern int startPlayingFlag;
int playbackCmdCounter=0;

void CMainDlg::OnTimer(UINT nIDEvent) 
{
    char tempString[10];
	//The timer event.
	//Read and Write one pair of reports.

	readDataFromComPort();

//	readDataFromUSB();

	if (COMStatus!=COM_STATUS_DEVICE_FOUND) {
		// blank display
		CMainDlg::blankMainDisplayIndicators();
		com_not_init_counter++;
		if (com_not_init_counter>COM_INIT_TIMER) {
			init_com_port();
		}
	}
	if (MyUSBDeviceDetected!=TRUE) {
		usb_not_init_counter++;
		if (usb_not_init_counter>USB_INIT_TIMER) {
			CMainDlg::FindTheHID();
		}
	}


	if (nIDEvent==ID_TIMER_CONTINUOUS) {

		if (channelsWinFlag==0 && scanWinFlag==0) {

			timerCommandCounter++;
			if (timerCommandCounter>9) {
				timerCommandCounter=0;
			}

			if (playbackWinFlag!=0) {
					playbackStatusCmd();
			}

			miscInfoCmd(); // get subchannel all the time
			switch (timerCommandCounter) {

				case 0:
				case 2:
				case 4:
				case 6:
				case 8:
					statusReqCmd();
					// update RS status request counter at bottom of screen
					sprintf(tempString,"RS:%5d",msgSentCount++);
					m_msgSentCountTxt->SetWindowTextA(tempString);
					timeReqCmd();  // try reading time just as often
					break;
				case 1:
					// Read file name
					if (playbackWinFlag==0 && unknownPlaybackStatus==0) { // don't send this command if in playback mode (or program just started and don't know if we are playing)---it messes up playback
						readFileNameCmd();
					}
					configReqCmd();
//					if (playbackWinFlag==0) {
						recordStatusCmd();
//					}
					break;
				case 3:
					// Read file name
					cardStatusReqCmd();
					if (playbackWinFlag==0) {
						playbackStatusCmd();
					}
					break;
				case 5:
//					if (playbackWinFlag==0) {
						recordStatusCmd();
//					}
//					sigProcReq();
					txStatusReq();
					break;
				case 7:
//					timeReqCmd();
					playbackStatusCmd();
					dateReqCmd();
					break;
				case 9:
//					if (playbackWinFlag==0) {
						recordStatusCmd();
//					}
					miscInfoCmd();
					break;

			} // End do every xth time

			if (continuousFlag==0) {
				CMainDlg::KillTimer(ID_TIMER_CONTINUOUS);
			} else {
//				SetTimer(ID_TIMER_CONTINUOUS, STATUS_UPDATE_TIME, NULL);
			}
		}


/*
		if (playbackWinFlag!=0) {
			playbackStatusCmd();
			timeReqCmd();
			playbackCmdCounter++;
			switch (playbackCmdCounter) {
				case 0:
					cardStatusReqCmd();
					break;
				case 1:
					miscInfoCmd();
					dateReqCmd();
					break:
				case 2:
					statusReqCmd();
					break;
				case 3:
					statusReqCmd();
					break;
				case 4:
					statusReqCmd();
					break;
				case 5:
					statusReqCmd();
					break;
			}
			if (playbackCmdCounter>=2) {
				playbackCmdCounter=0;
			}
		}

*/

#if USE_SEPARATE_USB_TIMER==1
	} else if (nIDEvent==ID_TIMER_USB_READ) {
		readDataFromUSB();
		SetTimer(ID_TIMER_USB_READ, USB_UPDATE_TIME, NULL);
#endif
	} else if (nIDEvent==ID_TIMER_CHANNELS) {
		if (channelsWinFlag==0) {
			// Stop timer messages for channel scan
			CMainDlg::KillTimer(ID_TIMER_CHANNELS);
		} else {
			//setFreqKHz[chanNumLoop];
			tuneFreqKHz=setFreqKHz[chanNumLoop];
//			setFreqOperCmd();
//			channelScanCmd();
//			CChannelsDlg::UpdateChannelIndicatorLights();
			chanNumLoop++;
			if (chanNumLoop>7) chanNumLoop=0;
			setFreqOperCmd();
		}
	/*} else if (nIDEvent==ID_TIMER_STINGER) {
		CMainDlg::KillTimer(ID_TIMER_STINGER);
		m_FreqValue->EnableWindow(TRUE);
		m_swapLr->EnableWindow(TRUE);
		m_FreqSelect->EnableWindow(TRUE);
		m_stingerPower->EnableWindow(TRUE);
		m_setFreq.EnableWindow(TRUE);
		m_stereoOn->EnableWindow(TRUE);
		m_monoOn.EnableWindow(TRUE);
		m_FreqVal1.EnableWindow(TRUE);
		m_FreqVal2.EnableWindow(TRUE);
		m_FreqVal3.EnableWindow(TRUE);
		m_FreqVal4.EnableWindow(TRUE);
		m_FreqVal5.EnableWindow(TRUE);
		m_FreqVal6.EnableWindow(TRUE);
		m_FreqVal7.EnableWindow(TRUE);
		m_FreqVal8.EnableWindow(TRUE);
		if (stingerStatus!=STINGER_COLLISION) {
			stingerStatus=STINGER_IDLE;
			setIndicatorLight(STINGER_TX_STATUS_LED,LED_GREEN,drawingContextMain);
		} else { // collision--indicate that it timed out
			stingerStatus=STINGER_COLLIDED_TIMED_OUT;
		} */
	}


// resend Playback command if too much time has elapsed
	resendPlaybackCommandCounter++; 
	if (resendPlaybackCommandCounter>RESEND_PLAYBACK_TIMEOUT_MS/STATUS_UPDATE_TIME) {
		resendPlaybackCommandCounter=0;
		if (startPlayingFlag==1) {
			playbackStartCmd();
		}
	}

	if (COMStatus==COM_STATUS_DEVICE_FOUND) {
		enableSetOperCmdButtons(TRUE);
	} else {
		enableSetOperCmdButtons(FALSE);
	}


	CDialog::OnTimer(nIDEvent);
}


void CMainDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMainDlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CString	strBytesWritten = "";
	audioFilterNum=7-m_FilterSelect.GetPos();
	switch(audioFilterNum) {
		case 0:{m_FiltFlat->SetFocus();break;}
		case 1:{m_Filt100Hz->SetFocus();break;}
		case 2:{m_Filt200Hz->SetFocus();break;}
		case 3:{m_Filt200HzSharp->SetFocus();break;}
		case 4:{m_Filt400HzSharp->SetFocus();break;}
		case 5:{m_Filt200HzVerySharp->SetFocus();break;}
		case 6:{m_Filt400HzVerySharp->SetFocus();break;}
	}


	setFreqOperCmd();
}


int usbResponseFlag=0;
void CMainDlg::writeCmd(int outCmdLen) {
	usbResponseFlag=0;
	if (m_useUSB->GetCheck()==BST_CHECKED) {
		writeCmdUSB((int) outCmdLen);
		if (readResp(100)==1) {
			usbResponseFlag=1;
		}
	} else {
		writeCmdCOM((int) outCmdLen);
	}
}

void CMainDlg::processUSBResponse() {
	if (usbResponseFlag==1) {
		processMsg();
	}
}

extern SOCKET mySock;

void CMainDlg::writeCmdCOM(int outCmdLen) {
	BOOL     bWriteRC;
	DWORD iBytesWritten;
	BOOL     bReadRC;

//	bool successWriteRead=FALSE;
	int iBytesToRead;
	int i;
	long unsigned loopCount;
	char *inPtr;

#define TESTING 0
#if TESTING==1
	outMsgStr[0]=0x72;
	outMsgStr[1]=0x78;
	outMsgStr[2]=0x12;
	outMsgStr[3]=0x00;
	outMsgStr[4]=0x09;
	outMsgStr[5]=0xBB;
	outMsgStr[6]=0xBB;
	outMsgStr[7]=0x8B;
	outMsgStr[8]=0x00;
	outMsgStr[9]=0x08;
	outCmdLen=12;

	int j,k,l,m,n;
	for (n=0;n<2;n++) {
		for (l=1;l<8;l++) {
			switch(l) {
				case 1:
					outMsgStr[5]=0xbb; // line 4: OFF/ON=1111b, line 5: OFF/ON=1111b
					outMsgStr[6]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
					break;
				case 2:
					outMsgStr[5]=0x8b; // line 4: OFF/ON=0000b, line 5: OFF/ON=1111b
					outMsgStr[6]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
					break;
				case 3:
					outMsgStr[5]=0xb8; // line 4: OFF/ON=1111b, line 5: OFF/ON=0000b
					outMsgStr[6]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
					break;
				case 4:
					outMsgStr[5]=0x88; // line 4: OFF/ON=0000b, line 5: OFF/ON=0000b
					outMsgStr[6]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
					break;
				case 5:
					outMsgStr[5]=0xbb; // line 4: OFF/ON=1111b, line 5: OFF/ON=1111b
					outMsgStr[6]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
					break;
				case 6:
					outMsgStr[5]=0x8b; // line 4: OFF/ON=0000b, line 5: OFF/ON=1111b
					outMsgStr[6]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
					break;
				case 7:
					outMsgStr[5]=0xb8; // line 4: OFF/ON=1111b, line 5: OFF/ON=0000b
					outMsgStr[6]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
					break;
				case 8:
				default:
					outMsgStr[5]=0x88; // line 4: OFF/ON=0000b, line 5: OFF/ON=0000b
					outMsgStr[6]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
					break;
			}
			for (m=0;m<3;m++) {
				if (m==0) { // If stereo mode
//				stinger8bytes[2]|=0x20; // make line 2 an input (setting it high---line 2 is funny that way)
					outMsgStr[7]=0xbb; // line 2: OFF/ON=1111b, line 3: OFF/ON=1111b (line 2 is an input so its ON/OFF portion is ignored)
				} else if (m==1) { // if mono left
					outMsgStr[7]=0xb8; // line 2: OFF/ON=1111b, line 3: OFF/ON=0000b
				} else { // else mono right
					outMsgStr[7]=0x8b; // line 2: OFF/ON=0000b, line 3: OFF/ON=1111b
				}	
				outMsgStr[7]&=0xf0;
				if (n==1) {
					outMsgStr[7]|=(char)0x0F;
				}

				for (i=0;i<10;i++) {
					for (j=0;j<10;j++) {
						for (k=0;k<10;k++) {
							outMsgStr[2]=16*i+j;
							outMsgStr[3]=16*k;
#endif


							appendCRC(outMsgStr,outCmdLen-2); // Add the CRC
#if TESTING==1
							if (outMsgStr[10]==(char)0xff) {

								int l=12; // just a place to break
							}
						}
					}
				}
			}
		}
	}
#endif

	if (ComGood==TRUE) {
	
		extern LPOVERLAPPED overlapped;

		if (portType==PORT_TYPE_TCPIP) {
			send(mySock,outMsgStr,outCmdLen,0);
		} else {
			WriteFile(m_hCom,outMsgStr,outCmdLen,&iBytesWritten,overlapped);
		}
	}
}

void decodeReceivedCommand();
char inMsgChars[2];
#define MAX_WAIT_TIME_INMESSAGE_MSECS 100
int miscCounter=0;
int inMsgLengthActual=0;


/*void CMainDlg::setMsgStatus(int newStatus) {
	msgStatus=newStatus;
	if (newStatus==MSG_STATUS_OK) {
		setIndicatorLight(MSG_STATUS_LED,LED_GREEN,drawingContextMain);
	} else if (newStatus==MSG_STATUS_TRANSMITTING) {
		setIndicatorLight(MSG_STATUS_LED,LED_YELLOW,drawingContextMain);
	} else if (newStatus==MSG_STATUS_RECEIVING) {
		setIndicatorLight(MSG_STATUS_LED,LED_YELLOW,drawingContextMain);
	} else if (newStatus==MSG_STATUS_BAD) {
		setIndicatorLight(MSG_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
	} else {
		setIndicatorLight(MSG_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
	}
}*/

void decodeReceivedCommand() {
	if ((inMsgChars[0]==RESP_STATUS_REQ_1) && (inMsgChars[1]==RESP_STATUS_REQ_2)){
		inMsgType=CMD_STATUS_REQ;
		inMsgLengthActual=RESP_STATUS_REQ_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_CONFIG_REQ_1) && (inMsgChars[1]==RESP_CONFIG_REQ_2)){
		inMsgType=CMD_CONFIG_REQ;
		inMsgLengthActual=RESP_CONFIG_REQ_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_CARD_STATUS_REQ_1) && (inMsgChars[1]==RESP_CARD_STATUS_REQ_2)){
		inMsgType=CMD_CARD_STATUS_REQ;
		inMsgLengthActual=RESP_CARD_STATUS_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_RECORD_STATUS_REQ_1) && (inMsgChars[1]==RESP_RECORD_STATUS_REQ_2)){
		inMsgType=CMD_RECORD_STATUS_REQ;
		inMsgLengthActual=RESP_RECORD_STATUS_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_NEXT_FILE_NAME_REQ_1) && (inMsgChars[1]==RESP_NEXT_FILE_NAME_REQ_2)){
		inMsgType=CMD_NEXT_FILE_NAME_REQ;
		inMsgLengthActual=RESP_NEXT_FILE_NAME_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_TX_FREQ_1) && (inMsgChars[1]==RESP_TX_FREQ_2)){
		inMsgType=CMD_TX_FREQ_REQ;
		inMsgLengthActual=RESP_TX_FREQ_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_SIG_PROC_1) && (inMsgChars[1]==RESP_SIG_PROC_2)){
		inMsgType=CMD_SIG_PROC_REQ;
		inMsgLengthActual=RESP_SIG_PROC_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_TX_STATUS_1) && (inMsgChars[1]==RESP_TX_STATUS_2)){
		inMsgType=CMD_TX_STATUS_REQ;
		inMsgLengthActual=RESP_TX_STATUS_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_FPGA_REG_1) && (inMsgChars[1]==RESP_FPGA_REG_2)){
		inMsgType=CMD_FPGA_REG_REQ;
		inMsgLengthActual=RESP_FPGA_REG_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_EEPROM_PIC1_1) && (inMsgChars[1]==RESP_EEPROM_PIC1_2)){
		inMsgType=CMD_EEPROM_PIC1_REQ;
		inMsgLengthActual=RESP_EEPROM_PIC1_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_TIME_1) && (inMsgChars[1]==RESP_TIME_2)){
		inMsgType=CMD_TIME_READ;
		inMsgLengthActual=RESP_TIME_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_DATE_1) && (inMsgChars[1]==RESP_DATE_2)){
		inMsgType=CMD_DATE_READ;
		inMsgLengthActual=RESP_DATE_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_DEFAULT_STATE_SET_1) && (inMsgChars[1]==RESP_DEFAULT_STATE_SET_2)){
		inMsgType=CMD_DEFAULT_STATE_SET;
		inMsgLengthActual=RESP_DEFAULT_STATE_SET_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_MISC_INFO_1) && (inMsgChars[1]==RESP_MISC_INFO_2)){
		inMsgType=CMD_RESP_MISC_INFO;
		inMsgLengthActual=RESP_MISC_INFO_LEN;
		return;
	}
	if ((inMsgChars[0]==RESP_SWEEP_RESP_1) && (inMsgChars[1]==RESP_SWEEP_RESP_2)){
		inMsgType=CMD_SWEEP;
		inMsgLengthActual=RESP_SWEEP_LEN;
		return;
	}
#if CT148_MODE==1
if ((inMsgChars[0]==RESP_LOAD_SD_ENCRYPT_KEY_1) && (inMsgChars[1]==RESP_LOAD_SD_ENCRYPT_KEY_2)){
		inMsgType=CMD_ENCRYPT_SET;
		inMsgLengthActual=RESP_LOAD_SD_ENCRYPT_LEN;
		return;
	}
#else
	if ((inMsgChars[0]==RESP_PLAYBACK_STATUS_1) && (inMsgChars[1]==RESP_PLAYBACK_STATUS_2)){
		inMsgType=CMD_PLAYBACK_STATUS;
		inMsgLengthActual=RESP_PLAYBACK_STATUS_LEN;
		return;
	}
#endif
	/*
	if ((inMsgChars[0]==channelScanRespStr[0]) && (inMsgChars[1]==channelScanRespStr[1])){
		inMsgType=CMD_CHANNEL_SCAN;
		inMsgLengthActual=RESP_CHANNEL_SCAN_LEN;
		return;
	}
	if ((inMsgChars[0]==freqRespStr[0]) && (inMsgChars[1]==freqRespStr[1])){
		inMsgType=CMD_SET_FREQ;
		inMsgLengthActual=RESP_FREQ_LEN;
		return;
	}
	if ((inMsgChars[0]==filterRespStr[0]) && (inMsgChars[1]==filterRespStr[1])){
		inMsgType=CMD_SET_FILTER;
		inMsgLengthActual=RESP_FILTER_LEN;
		return;
	}
	if ((inMsgChars[0]==sweepRespStr[0]) && (inMsgChars[1]==sweepRespStr[1])){
		inMsgType=CMD_SWEEP;
		inMsgLengthActual=RESP_SWEEP_LEN;
		return;
	}
	if ((inMsgChars[0]==configSetRespStr[0]) && (inMsgChars[1]==configSetRespStr[1])){
		inMsgType=CMD_CONFIG_SET;
		inMsgLengthActual=RESP_CONFIG_SET_LEN;
		return;
	}
	if ((inMsgChars[0]==configReqRespStr[0]) && (inMsgChars[1]==configReqRespStr[1])){
		inMsgType=CMD_CONFIG_REQ;
		inMsgLengthActual=RESP_CONFIG_REQ_LEN;
		return;
	}
	if ((inMsgChars[0]==readFileNameRespStr[0]) && (inMsgChars[1]==readFileNameRespStr[1])) {
		inMsgType=CMD_FILE_NAME_READ;
		inMsgLengthActual=RESP_READ_FILE_NAME_LEN;
		return;
	}
	if ((inMsgChars[0]==readSDRAMAudioRespStr[0]) && (inMsgChars[1]==readSDRAMAudioRespStr[1])) {
		inMsgType=CMD_SDRAM_AUDIO_READ;
		inMsgLengthActual=RESP_READ_SDRAM_AUDIO_LEN;
		return;
	}
	if ((inMsgChars[0]==miscInstRespStr[0]) && (inMsgChars[1]==miscInstRespStr[1])){
		inMsgType=CMD_MISC_INST;
		inMsgLengthActual=RESP_MISC_INST_LEN;
		return;
	}
	if ((inMsgChars[0]==sigProcRespStr[0]) && (inMsgChars[1]==sigProcRespStr[1])){
		inMsgType=CMD_SIG_PROC;
		inMsgLengthActual=RESP_SIG_PROC_LEN;
		return;
	}
	if ((inMsgChars[0]==setTxFreqRespStr[0]) && (inMsgChars[1]==setTxFreqRespStr[1])){
		inMsgType=CMD_SET_TX_FREQ;
		inMsgLengthActual=RESP_SET_TX_FREQ_LEN;
		return;
	}
	if ((inMsgChars[0]==setFPGARespStr[0]) && (inMsgChars[1]==setFPGARespStr[1])){
		inMsgType=CMD_SET_FPGA_REG;
		inMsgLengthActual=RESP_SET_FPGA_REG_LEN;
		return;
	}
	if ((inMsgChars[0]==readFPGARespStr[0]) && (inMsgChars[1]==readFPGARespStr[1])){
		inMsgType=CMD_READ_FPGA_REG;
		inMsgLengthActual=RESP_READ_FPGA_REG_LEN;
		return;
	}
	if ((inMsgChars[0]==setDevRespStr[0]) && (inMsgChars[1]==setDevRespStr[1])){
		inMsgType=CMD_SET_DEV;
		inMsgLengthActual=RESP_SET_DEV_LEN;
		return;
	}
	if ((inMsgChars[0]==readDevRespStr[0]) && (inMsgChars[1]==readDevRespStr[1])){
		inMsgType=CMD_READ_DEV;
		inMsgLengthActual=RESP_READ_DEV_LEN;
		return;
	}
	if ((inMsgChars[0]==setTxFreqRespStr[0]) && (inMsgChars[1]==setTxFreqRespStr[1])){
		inMsgType=CMD_SET_TX_FREQ;
		inMsgLengthActual=RESP_SET_TX_FREQ_LEN;
		return;
	}
	if ((inMsgChars[0]==readTxFreqRespStr[0]) && (inMsgChars[1]==readTxFreqRespStr[1])){
		inMsgType=CMD_READ_TX_FREQ;
		inMsgLengthActual=RESP_READ_TX_FREQ_LEN;
		return;
	}
	if ((inMsgChars[0]==setDeltaPhaseRespStr[0]) && (inMsgChars[1]==setDeltaPhaseRespStr[1])){
		inMsgType=CMD_SET_DELTA_PHASE;
		inMsgLengthActual=RESP_SET_DELTA_PHASE_LEN;
		return;
	}
	if ((inMsgChars[0]==readDeltaPhaseRespStr[0]) && (inMsgChars[1]==readDeltaPhaseRespStr[1])){
		inMsgType=CMD_READ_DELTA_PHASE;
		inMsgLengthActual=RESP_READ_DELTA_PHASE_LEN;
		return;
	}
	if ((inMsgChars[0]==setClksPerFsRespStr[0]) && (inMsgChars[1]==setClksPerFsRespStr[1])){
		inMsgType=CMD_SET_CLKS_PER_FS;
		inMsgLengthActual=RESP_SET_CLKS_PER_FS_LEN;
		return;
	}
	if ((inMsgChars[0]==readClksPerFsRespStr[0]) && (inMsgChars[1]==readClksPerFsRespStr[1])){
		inMsgType=CMD_READ_CLKS_PER_FS;
		inMsgLengthActual=RESP_READ_CLKS_PER_FS_LEN;
		return;
	}
	if ((inMsgChars[0]==readBERRespStr[0]) && (inMsgChars[1]==readBERRespStr[1])){
		inMsgType=CMD_READ_BER;
		inMsgLengthActual=RESP_READ_BER_LEN;
		return;
	}
	if ((inMsgChars[0]==setOscCtrlRespStr[0]) && (inMsgChars[1]==setOscCtrlRespStr[1])){
		inMsgType=CMD_SET_OSC_CTRL;
		inMsgLengthActual=RESP_SET_OSC_CTRL_LEN;
		return;
	}
	if ((inMsgChars[0]==readOscCtrlRespStr[0]) && (inMsgChars[1]==readOscCtrlRespStr[1])) {
		inMsgType=CMD_READ_OSC_CTRL;
		inMsgLengthActual=RESP_READ_OSC_CTRL_LEN;
		return;
	}
	if ((inMsgChars[0]==squelchRespStr[0]) && (inMsgChars[1]==squelchRespStr[1])) {
		inMsgType=CMD_SET_SQUELCH;
		inMsgLengthActual=RESP_SQUELCH_LEN;
		return;
	}
	if ((inMsgChars[0]==remoteAGCRespStr[0]) && (inMsgChars[1]==remoteAGCRespStr[1])) {
		inMsgType=CMD_WRITE_REMOTE_AGC;
		inMsgLengthActual=RESP_REMOTE_AGC_LEN;
		return;
	}
	if ((inMsgChars[0]==localAGCRespStr[0]) && (inMsgChars[1]==localAGCRespStr[1])) {
		inMsgType=CMD_WRITE_LOCAL_AGC;
		inMsgLengthActual=RESP_LOCAL_AGC_LEN;
		return;
	}
	if ((inMsgChars[0]==writeStingerRespStr[0]) && (inMsgChars[1]==writeStingerRespStr[1])) {
		inMsgType=CMD_WRITE_STINGER;
		inMsgLengthActual=RESP_WRITE_STINGER_LEN;
		return;
	}
	if ((inMsgChars[0]==writeStingerSchedRespStr[0]) && (inMsgChars[1]==writeStingerSchedRespStr[1])) {
		inMsgType=CMD_WRITE_STINGER_SCHED;
		inMsgLengthActual=RESP_WRITE_STINGER_SCHED_LEN;
		return;
	}
	if ((inMsgChars[0]==stingerRecordRespStr[0]) && (inMsgChars[1]==stingerRecordRespStr[1])) {
		inMsgType=CMD_STINGER_RECORD;
		inMsgLengthActual=RESP_STINGER_RECORD_LEN;
		return;
	}
	if ((inMsgChars[0]==dogleashModeRespStr[0]) && (inMsgChars[1]==dogleashModeRespStr[1])) {
		inMsgType=CMD_DOGLEASH_MODE;
		inMsgLengthActual=RESP_DOGLEASH_MODE_LEN;
		return;
	}
	if ((inMsgChars[0]==timeDateRespStr[0]) && (inMsgChars[1]==timeDateRespStr[1])) {
		inMsgType=CMD_TIME_DATE_READ;
		inMsgLengthActual=RESP_TIME_DATE_LEN;
		return;
	}
	if ((inMsgChars[0]==readSDRAMAudioRespStr[0]) && (inMsgChars[1]==readSDRAMAudioRespStr[1])) {
		inMsgType=CMD_SDRAM_AUDIO_READ;
		inMsgLengthActual=RESP_READ_SDRAM_AUDIO_LEN;
		return;
	}
	if ((inMsgChars[0]==readBytesPerClusterRespStr[0]) && (inMsgChars[1]==readBytesPerClusterRespStr[1])) {
		inMsgType=CMD_BYTES_PER_CLUSTER_READ;
		inMsgLengthActual=RESP_READ_BYTES_PER_CLUSTER_LEN;
		return;
	}
*/

	inMsgType=CMD_UNKNOWN;
	inMsgLengthActual=2; //Take a guess
	return;
}

void CMainDlg::setUSBStatus(int USBStatus) {
	if (USBStatus==0) {
		MyUSBDeviceDetected=FALSE;
//		m_usbStatusButton.SetWindowTextA("Not Attached");
		setIndicatorLight(USB_STATUS_LED,LED_YELLOW,drawingContextMain);
	} else {
		MyUSBDeviceDetected=TRUE;
//		m_usbStatusButton.SetWindowTextA("Attached");
		setIndicatorLight(USB_STATUS_LED,LED_GREEN,drawingContextMain);
	}
}
//void updateFreqTextDisplay(ULONG);
bool powerOn=TRUE;

void CMainDlg::setFreqOperCmd() {
	int i;
	int filtNumUse;
	outMsgStr[0]=CMD_SET_FREQ_OPER_1; //"cs" command
	outMsgStr[1]=CMD_SET_FREQ_OPER_2; // "cs" command
	outMsgStr[2]=(char)((tuneFreqKHz&(long int)0xFF0000)>>16); //High byte
	outMsgStr[3]=(char)((tuneFreqKHz&(long int)0x00FF00)>>8); //Mid byte
	outMsgStr[4]=(char)(tuneFreqKHz&(long int)0x0000FF); //Low byte

// Set up status byte 1
    filtNumUse=audioFilterNum;


switch (audioFilterNum) {
		case 0:
		case 3:
		case 4:
		default:
			filtNumUse=audioFilterNum;
			break;
		case 1:
			filtNumUse=2;
			break;
		case 2:
			filtNumUse=5;
			break;
		case 5:
			filtNumUse=6;
			break;
		case 6:
			filtNumUse=7;
			break;
	}

	
	outMsgStr[5]=filtNumUse;
	if (powerOn==TRUE) {
		outMsgStr[5]|=CMDBYTE1_POWER_ON_MASK;
	}
	if (m_monoOn->GetCheck()!=BST_CHECKED) outMsgStr[5]|=CMDBYTE1_STEREO_ON_MASK;
	if (squelchMode==0) outMsgStr[5]|=CMDBYTE1_EXT_RANGE_MASK;
	if (calToneMode&0x01) outMsgStr[5]|=CMDBYTE1_CALTONE_MASK;
//	if (m_declick.GetCheck()==BST_CHECKED) outMsgStr[6]|=CMDBYTE2_DECLICK_MASK;

//	if (m_preemphasis.GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_PREEMPH_MASK;
//	if (m_agcLocal.GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_AGC_LOCAL_MASK;
//	if (m_agcRemote.GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_AGC_REMOTE_MASK;
//	if (m_ancRemote.GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_ANC_REMOTE_MASK;
//	if (m_swapLr->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_SWAPLR_MASK;

	outMsgStr[6]=0x80;
	if (calToneMode&0x02) outMsgStr[6]|=CMDBYTE2_TONE_NO_LOCK_MASK;
	if (declickMode==1) outMsgStr[6]|=CMDBYTE2_DECLICK_MASK;
//	if (m_audioMute.GetCheck()==BST_CHECKED) outMsgStr[3]|=SIGPROC_ANALOG_MUTE_MASK;


#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//	msgString.Format("Output CA Msg --- StatByte: %2x", outMsgStr[2]);
//	CDebugWinDlg::DisplayData2(msgString);
#endif

    ignoreNextSeveralSTResponses=1; // new!! a way to stop the "blink" caused when you select something (like "noise reduce" for instance), and the value "blinks" back before assuming the actual value
	writeCmd(CMD_SET_FREQ_OPER_LEN);  //Write out CS msg of length 9

#if INTERFACE_USB==1
	readResp(RESP_FREQ_LEN);  //Read in SS msg of length 5
	displayFreqResp();
#endif

//	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
//		outputStingerCmd(STINGER_TX_SPECIFIC);
//	}

}

void CMainDlg::readFreqCmd() {
//	long respFreqKHz;
	int i;
//	outMsgStr[0]=readFreqCmdStr[0]; //"ds" command
//	outMsgStr[1]=readFreqCmdStr[1]; // "ds" command
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//	msgString.Format("Output DS Msg (read freq)");
//	CDebugWinDlg::DisplayData2(msgString);
#endif
//	writeCmd(CMD_READ_FREQ_LEN);  //Write out DS msg of length 2

#if INTERFACE_USB==1
	readResp(RESP_FREQ_LEN);  //Read in SS msg of length 5

	respFreqKHz=freq_3bytes_to_value(inMsgParams);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	if (inMsgType==CMD_SET_FREQ) {
		msgString="Input SS Msg: Freq =";
	} else {
		msgString="Input Unknown Msg: Freq =";
	}
	msgString.Format("%s %ld kHz",msgString,respFreqKHz);
	CDebugWinDlg::DisplayData2(msgString);
#endif

	if (MyDeviceDetected==TRUE && tuneFreqKHz!=respFreqKHz) {
		freqKHzToMHzString(respFreqKHz,freqValChars);
		m_FreqValue->SetWindowText(freqValChars);
	}
#endif
}

/*
void CMainDlg::setFilterCmd() {
	int i;
//	outMsgStr[0]=setFilterCmdStr[0]; //"es" command
//	outMsgStr[1]=setFilterCmdStr[1]; // "es" command
//	outMsgStr[2]=(char)(audioFilterNum);			 //0--7: Audio filter number
//	outMsgStr[3]=0;
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//	msgString.Format("Output ES Msg (set flter) Filter:%d", audioFilterNum);
//	CDebugWinDlg::DisplayData2(msgString);
#endif


//	writeCmd(CMD_SET_FILTER_LEN);  //Write out ES msg of length 4

#if INTERFACE_USB==1
	readResp(RESP_FILTER_LEN);  //Read in TS msg of length 4
#if DISPLAY_MESSAGES==YES_DISPLAY_EM

	if (inMsgType==CMD_SET_FILTER) {
		msgString="Input TS Msg:";
	} else {
		msgString="Input Unknown Msg:";
	}
	msgString.Format("%s %2x %2x",msgString,0x0ff&inMsgParams[0],0x0ff&inMsgParams[1]);
	CDebugWinDlg::DisplayData2(msgString);
#endif
	audioFilterNum=(int)0x0ff&(int)inMsgParams[0];
#endif
}
*/

void CMainDlg::statusReqCmd() {
	outMsgStr[0]=CMD_STATUS_REQ_1; //"rs" command
	outMsgStr[1]=CMD_STATUS_REQ_2; // "rs" command
	writeCmd(CMD_STATUS_REQ_LEN);   //Write out RS msg of length 4
	CMainDlg:processUSBResponse();

}

void CMainDlg::configReqCmd() {
	outMsgStr[0]=CMD_CONFIG_REQ_1; //"cd" command
	outMsgStr[1]=CMD_CONFIG_REQ_2; // "cd" command
	writeCmd(CMD_CONFIG_REQ_LEN);   //Write out CD msg of length 4
	CMainDlg:processUSBResponse();
}

void CMainDlg::cardStatusReqCmd() {
	outMsgStr[0]=CMD_CARD_STATUS_REQ_1; //"cg" command
	outMsgStr[1]=CMD_CARD_STATUS_REQ_2; // "cg" command
	writeCmd(CMD_CARD_STATUS_REQ_LEN);   //Write out CD msg of length 4
	CMainDlg:processUSBResponse();
}

void CMainDlg::readFileNameCmd() {
	outMsgStr[0]=CMD_NEXT_FILE_NAME_REQ_1; //"ch" command
	outMsgStr[1]=CMD_NEXT_FILE_NAME_REQ_2; // "ch" command
	CMainDlg::writeCmd(CMD_NEXT_FILE_NAME_REQ_LEN);
//	CMainDlg:processUSBResponse();
}

void CMainDlg::channelScanCmd() {
	int i;
//	outMsgStr[0]=channelScanCmdStr[0]; //"ry" command
//	outMsgStr[1]=channelScanCmdStr[1]; // "ry" command
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//	msgString.Format("Output Channel Scan (ry)");
//	CDebugWinDlg::DisplayData2(msgString);
//	if (debugWinFlag==1) {
//		CDebugWinDlg::DisplayData2(msgString);
//	}
#endif
//	writeCmd(CMD_CHANNEL_SCAN_LEN);   //Write out RS msg of length 2

#if INTERFACE_USB==1
	readResp(RESP_CHANNEL_SCAN_LEN); //Read in ST msg of length 6
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
 	msgString="Input SY Msg:";
	for (i=0;i<4;i++) {
		msgString.Format("%s %2x",msgString,(inMsgParams[i]&0x0ff));
    	if (i!=3) msgString.Format("%s,",msgString);
	}
	CDebugWinDlg::DisplayData2(msgString);
#endif
#endif
}

void CMainDlg::sigProcReq() {
	outMsgStr[0]=CMD_SIG_PROC_REQ_1; //"ac" command
	outMsgStr[1]=CMD_SIG_PROC_REQ_2; // "ac" command
	writeCmd(CMD_SIG_PROC_REQ_LEN);
}

void CMainDlg::sigProcSet() { //Sets Pre-emphasis, AGC, and ANC status bits
	outMsgStr[0]=CMD_SIG_PROC_SET_1; //"ad" command
	outMsgStr[1]=CMD_SIG_PROC_SET_2; // "ad" command

	outMsgStr[2]=0;

// Set up control byte
	if (m_preemphasis->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_PREEMPH_MASK;
	if (m_agcLocal->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_AGC_LOCAL_MASK;
	if (m_agcRemote->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_AGC_REMOTE_MASK;
	if (m_ancRemote->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_ANC_REMOTE_MASK;
	if (m_swapLr->GetCheck()==BST_CHECKED) outMsgStr[2]|=SIGPROC_SWAPLR_MASK;

	writeCmd(CMD_TX_STATUS_SET_LEN);
}

void CMainDlg::txStatusReq() {
	outMsgStr[0]=CMD_TX_STATUS_REQ_1; //"ae" command
	outMsgStr[1]=CMD_TX_STATUS_REQ_2; // "ae" command
	writeCmd(CMD_TX_STATUS_REQ_LEN);
}

void CMainDlg::txStatusSet() { //Sets transmitter on/off
	outMsgStr[0]=CMD_TX_STATUS_SET_1; //"af" command
	outMsgStr[1]=CMD_TX_STATUS_SET_2; // "af" command

	outMsgStr[2]=0;

// Set up control byte
	if (txOnFlag==TRUE) outMsgStr[2]|=0x01;
#if DST_MODE_ONLY==1
		outMsgStr[2]|=0x04;
#else
	if (m_txDst->GetCheck()==BST_CHECKED) {
		outMsgStr[2]|=0x04;
	} else {
		if (m_txFmEnc->GetCheck()==BST_CHECKED) outMsgStr[2]|=0x02;
	}
#endif
		writeCmd(CMD_TX_STATUS_SET_LEN);
}

void CMainDlg::playbackStatusCmd() {
	outMsgStr[0]=CMD_PLAYBACK_STATUS_REQ_1; //"rq" command
	outMsgStr[1]=CMD_PLAYBACK_STATUS_REQ_2; // "rq" command
	writeCmd(CMD_PLAYBACK_STATUS_REQ_LEN);   //Write out RQ msg of length 4
	CMainDlg:processUSBResponse();

}
int desiredPlaybackMode=0;
int startPlayingFlag=0;
int endPlaybackFlag=0;
int stopPlaybackFlag=0;

void CMainDlg::playbackStartCmd() {
	outMsgStr[0]=CMD_PLAYBACK_START_REQ_1; //"rp" command
	outMsgStr[1]=CMD_PLAYBACK_START_REQ_2; // "rp" command
	outMsgStr[2]=desiredPlaybackMode;
	outMsgStr[3]=(playbackJulianVal>>24)&0x0FF;
	outMsgStr[4]=(playbackJulianVal>>16)&0x0FF;
	outMsgStr[5]=(playbackJulianVal>>8)&0x0FF;
	outMsgStr[6]=playbackJulianVal&0x0FF;
	writeCmd(CMD_PLAYBACK_START_REQ_LEN);   //Write out RP msg of length 9
//	CMainDlg:processUSBResponse();

}


void CMainDlg::recordModeSetCmd() {
	outMsgStr[0]=CMD_RECORD_SET_1; //"cq" command
	outMsgStr[1]=CMD_RECORD_SET_2; // "cq" command
	if (m_recordmode->GetCheck()==BST_CHECKED) {
		outMsgStr[2]=1;
	} else {
		outMsgStr[2]=0;
	}
	if (m_overwriteWhenFull->GetCheck()!=BST_CHECKED) {
		outMsgStr[2]|=2;
	}
	writeCmd(CMD_RECORD_SET_LEN);   //Write out CQ msg of length 5
	CMainDlg:processUSBResponse();
}

void CMainDlg::recordStatusCmd() {
	outMsgStr[0]=CMD_RECORD_STATUS_REQ_1; //"cp" command
	outMsgStr[1]=CMD_RECORD_STATUS_REQ_2; // "cp" command
	writeCmd(CMD_RECORD_STATUS_REQ_LEN);   //Write out CP msg of length 4
	CMainDlg:processUSBResponse();
}

void CMainDlg::miscInfoCmd() {
	outMsgStr[0]=CMD_MISC_INFO_1; //"ct" command
	outMsgStr[1]=CMD_MISC_INFO_2; // "ct" command
	outMsgStr[2]=0; // insure reporting interval field is zero, indicating no auto reporting
	outMsgStr[3]=0;
	outMsgStr[4]=0;
	outMsgStr[5]=0;
	outMsgStr[6]=0;
	outMsgStr[7]=0;
	outMsgStr[8]=0;
	outMsgStr[9]=0;
	writeCmd(CMD_MISC_INFO_LEN);   //Write out CT msg of length 12
	CMainDlg:processUSBResponse();
}

void CMainDlg::sigProcUpdate() {
	if ((inMsgParams[0]&SIGPROC_PREEMPH_MASK)!=0) m_preemphasis->SetCheck(BST_CHECKED);
	else  m_preemphasis->SetCheck(BST_UNCHECKED);
	if ((inMsgParams[0]&SIGPROC_AGC_LOCAL_MASK)!=0) m_agcLocal->SetCheck(BST_CHECKED);
	else  m_agcLocal->SetCheck(BST_UNCHECKED);
	if ((inMsgParams[0]&SIGPROC_AGC_REMOTE_MASK)!=0) m_agcRemote->SetCheck(BST_CHECKED);
	else  m_agcRemote->SetCheck(BST_UNCHECKED);
	if ((inMsgParams[0]&SIGPROC_ANC_REMOTE_MASK)!=0) m_ancRemote->SetCheck(BST_CHECKED);
	else  m_ancRemote->SetCheck(BST_UNCHECKED);
	if ((inMsgParams[0]&SIGPROC_SWAPLR_MASK)!=0) m_swapLr->SetCheck(BST_CHECKED);
	else  m_swapLr->SetCheck(BST_UNCHECKED);
}

void CMainDlg::timeReqCmd() {
	outMsgStr[0]=CMD_TIME_REQ_1; //"ck" command
	outMsgStr[1]=CMD_TIME_REQ_2; // "ck" command
	writeCmd(CMD_TIME_REQ_LEN);
}

void CMainDlg::dateReqCmd() {
	outMsgStr[0]=CMD_DATE_REQ_1; //"cm" command
	outMsgStr[1]=CMD_DATE_REQ_2; // "cm" command
	writeCmd(CMD_DATE_REQ_LEN);
}

unsigned int pbyear;
unsigned int pbmonth;
unsigned int pbday;
unsigned int pbhour;
unsigned int pbmin;
unsigned int pbsec;
extern CDateTimeCtrl* pPlaybackTime;
extern CStatic* m_playbackMsg;
CTime displayedPlaybackTime;

void CMainDlg::playbackUpdate() {
	char tempChar[20];
	CButton *m_temp;

	unknownPlaybackStatus=0;

	sprintf(tempChar,"Mode: %2d",inMsgParams[0]);
//	m_playbackModeStringText->SetWindowTextA(tempChar);
	playbackJulianVal=((unsigned long)inMsgParams[1]&(unsigned long)0x000000ff);
	playbackJulianVal<<=8;
	playbackJulianVal|=((unsigned long)inMsgParams[2]&(unsigned long)0x000000ff);
	playbackJulianVal<<=8;
	playbackJulianVal|=((unsigned long)inMsgParams[3]&(unsigned long)0x000000ff);
	playbackJulianVal<<=8;
	playbackJulianVal|=((unsigned long)inMsgParams[4]&(unsigned long)0x000000ff);
	TIME_REC_STRUCT playbackTimeDate;
	julianToTime(&playbackJulianVal,&playbackTimeDate);

	if ((inMsgParams[0]&0x01)!=0) {

		p_liveButton->SetCheck(BST_UNCHECKED);
		p_playbackButton->SetCheck(BST_CHECKED);
		m_temp=(CButton*)GetDlgItem(IDC_PLAYBACK_STOP);
		m_temp->EnableWindow(TRUE);
		m_temp=(CButton*)GetDlgItem(IDC_PLAYBACK_START);
		m_temp->EnableWindow(TRUE);
		pPlaybackTime->EnableWindow(TRUE);

		if (playbackWinFlag==0) {
/*
			playbackWinDlg = new CPlaybackDlg();
			BOOL ret=playbackWinDlg->Create(IDD_PLAYBACKWINDOW,0);
			if(!ret)   //Create failed.
				AfxMessageBox("Error creating Dialog");
			playbackWinDlg->ShowWindow(SW_SHOW);
//			m_playbackWin.EnableWindow(FALSE); // Dim Playback Window button
*/
			playbackWinFlag=1;

		} else {
			CTime tempPlaybackTime=CTime(playbackTimeDate.dateYear+2000,playbackTimeDate.dateMonth,playbackTimeDate.dateDay,
				playbackTimeDate.timeHour,playbackTimeDate.timeMinute,playbackTimeDate.timeSecond,-1);
			if (displayedPlaybackTime!=tempPlaybackTime) {
				pPlaybackTime->SetTime(&tempPlaybackTime);
				displayedPlaybackTime=tempPlaybackTime;
			}

		}
	} else {
		endPlaybackFlag=0;
		p_liveButton->SetCheck(BST_CHECKED);
		p_playbackButton->SetCheck(BST_UNCHECKED);
		m_playbackMsg->SetWindowTextA(" ");
		m_temp=(CButton*)GetDlgItem(IDC_PLAYBACK_STOP);
		m_temp->EnableWindow(FALSE);
		m_temp=(CButton*)GetDlgItem(IDC_PLAYBACK_START);
		m_temp->EnableWindow(FALSE);
		pPlaybackTime->EnableWindow(FALSE);

		if (playbackWinFlag!=0) {
			playbackWinFlag=0;
/*
			playbackWinDlg->DestroyWindow(); //Kill playback window manually
//			m_playbackWin.EnableWindow(TRUE); //re-enable button for Channels Window
			CDialog::OnClose();
*/

		}
	}

	if (inMsgParams[0]==1) {
		if (desiredPlaybackMode==1 && startPlayingFlag==1) { // if just entered playback, but desired to start playing...
			desiredPlaybackMode=2; // send message to actually start playing
			m_playbackMsg->SetWindowTextA("Starting playback...");
			resendPlaybackCommandCounter=0;
			playbackStartCmd();
		} else if (desiredPlaybackMode==3 && endPlaybackFlag==1) { // if in playback, but desired to leave playback...
			m_playbackMsg->SetWindowTextA("Ending playback...");
			desiredPlaybackMode=0;
			resendPlaybackCommandCounter=0;
			playbackStartCmd();
		} else if (desiredPlaybackMode==3 && stopPlaybackFlag==1) { // if in playback, but desired to stop
			m_playbackMsg->SetWindowTextA("Stopped.");
			stopPlaybackFlag=0;
		} else if (desiredPlaybackMode==0) {
			m_playbackMsg->SetWindowTextA("Stopped.");
		}
	} else if (inMsgParams[0]==2) {
		if (desiredPlaybackMode==3 && endPlaybackFlag==1) { // if in playback, but desired to leave playback...
			m_playbackMsg->SetWindowTextA("Ending playback...");
			desiredPlaybackMode=0;
			resendPlaybackCommandCounter=0;
			playbackStartCmd();
		} else if (desiredPlaybackMode==0 && endPlaybackFlag==1) { // if done with playback...
			endPlaybackFlag==1;
			if (playbackWinFlag!=0) {
				playbackWinFlag=0;
				playbackWinDlg->DestroyWindow(); //Kill playback window manually
//				m_playbackWin.EnableWindow(TRUE); //re-enable button for Channels Window
				CDialog::OnClose();
			}
		}
	} else if (inMsgParams[0]==3) {
		if (startPlayingFlag==1) { // started playing so clear flag
			startPlayingFlag=0;
		}
		if (endPlaybackFlag==0) {
			m_playbackMsg->SetWindowTextA("Playing.");
		}

	} else if (inMsgParams[0]==0) {
		m_playbackMsg->SetWindowTextA(" ");
	}

}

void CMainDlg::updatePlaybackWindow() {

}


unsigned int year,month,day,hour,min,sec;

extern CDateTimeCtrl* pTimeBox;
extern CTime tempTime;
int setSysClkWinFlag=0;

long unsigned timePrev=99999;
long unsigned timeNow=0;
char timeString[10]={' ',' ',' ',' ',' ',' ',' ',' ',' ',0};
char dateString[10]={' ',' ',' ',' ',' ',' ',' ',' ',' ',0};

void CMainDlg::timeUpdate() {

	timeString[0]=0;

	hour=((unsigned int)inMsgParams[0]&0x0ff);
	if (hour>23) hour=23;
	min=((unsigned int)inMsgParams[1]&0x0ff);
	if (min>59) min=59;
	sec=((unsigned int)inMsgParams[2]&0x0ff);
	if (sec>59) sec=59;

	if (hour==0) {
		sprintf(timeString,"%2d:",12);
	} else if (hour>12) {
		sprintf(timeString,"%2d:",hour-12);
	} else {
		sprintf(timeString,"%2d:",hour);
	}

	if (min<10) {
		sprintf(timeString,"%s0%1d:",timeString,min);
	} else {
		sprintf(timeString,"%s%2d:",timeString,min);
	}
	if (sec<10) {
		sprintf(timeString,"%s0%1d",timeString,sec);
	} else {
		sprintf(timeString,"%s%2d",timeString,sec);
	}
	if (hour>11) {
		sprintf(timeString,"%s PM",timeString);
	} else {
		sprintf(timeString,"%s AM",timeString);
	}

	m_timeStringText->SetWindowTextA(timeString);


    timePrev=timeNow;
	timeNow=hour;
	timeNow*=60;
	timeNow+=min;
	timeNow*=60;
	timeNow+=sec;

	if (timePrev>timeNow) {
		FILE *fp=fopen("timelog.txt","a");
		fprintf(fp,"TIME RESET:\n");
		fprintf(fp,"PrevTime: %ld, NowTime:  %ld,  ",timePrev,timeNow);
		fprintf(fp,"FileName: %s\n",SDFileNameStr);
		fclose(fp);
	}

}

void CMainDlg::dateUpdate() {
	dateString[0]=0;


	year=((unsigned int)inMsgParams[2]&0x0ff)+2000;
	if (year>3000) year=2999;
	month=((unsigned int)inMsgParams[1]&0x0ff);
	if (month>12 || month<1) month=12;
	day=((unsigned int)inMsgParams[0]&0x0ff);
	if (day>31 || day<1) day=31;

/*
	sprintf(dateString,"%2d/",inMsgParams[1]);
	if (inMsgParams[0]<10) {
		sprintf(dateString,"%s%1d/",dateString,inMsgParams[0]);
	} else {
		sprintf(dateString,"%s%2d/",dateString,inMsgParams[0]);
	}
	if (inMsgParams[2]<10) {
		sprintf(dateString,"%s0%1d",dateString,inMsgParams[2]);
	} else {
		sprintf(dateString,"%s%2d",dateString,inMsgParams[2]);
	}
*/
	sprintf(dateString,"%2d-",day);
	switch (month) {
		case 1:
			sprintf(dateString,"%sJan-",dateString);
			break;
		case 2:
			sprintf(dateString,"%sFeb-",dateString);
			break;
		case 3:
			sprintf(dateString,"%sMar-",dateString);
			break;
		case 4:
			sprintf(dateString,"%sApr-",dateString);
			break;
		case 5:
			sprintf(dateString,"%sMay-",dateString);
			break;
		case 6:
			sprintf(dateString,"%sJun-",dateString);
			break;
		case 7:
			sprintf(dateString,"%sJul-",dateString);
			break;
		case 8:
			sprintf(dateString,"%sAug-",dateString);
			break;
		case 9:
			sprintf(dateString,"%sSep-",dateString);
			break;
		case 10:
			sprintf(dateString,"%sOct-",dateString);
			break;
		case 11:
			sprintf(dateString,"%sNov-",dateString);
			break;
		case 12:
			sprintf(dateString,"%sDec-",dateString);
			break;
	}
	sprintf(dateString,"%s%4d",dateString,year);
	m_dateStringText->SetWindowTextA(dateString);


//	if (setSysClkWinFlag==1) {
//		tempTime=CTime(year,month,day,hour,min,sec,-1);
//		pTimeBox->SetFormat(_T("dd-MMM-yyyy hh:mm:ss tt '(CT-148)'"));
//		pTimeBox->SetTime(&tempTime);
//		CSetSysClkDlg::pTimeBoxDDE.SetFormat(_T("dd-MMM-yyyy hh:mm:ss tt '(CT-148)'"));
//		CSetSysClkDlg::pTimeBoxDDE.SetTime(&tempTime);
//	}

}
extern int stingerWinFlag;
extern CButton *m_onCmd;
extern CButton *m_offCmd;
extern CButton *m_onCmdButton;
extern CButton *m_offCmdButton;

void CMainDlg::txStatusUpdate() {
	txOnFlag=FALSE;
#if TACTICAL_REPEATER_MODE==1
	if ((inMsgParams[0]&0x08)!=0) {
		txOnFlag=TRUE;
		m_txPower->SetWindowTextA("Tx On");
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
	} else {
		if ((inMsgParams[0]&0x01)!=0) {
			txOnFlag=TRUE;
			m_txPower->SetWindowTextA("Tx Standby");
			setIndicatorLight(TRANSMITTER_STATUS_LED,LED_YELLOW,drawingContextMain);
		} else {
			m_txPower->SetWindowTextA("Tx Off");
			setIndicatorLight(TRANSMITTER_STATUS_LED,LED_DARK_RED,drawingContextMain);
		}
	}
#elif TACTICAL_REPEATER_MODE==2
	if ((inMsgParams[0]&0x08)!=0) {
		txOnFlag=TRUE;
		m_txPower->SetWindowTextA("Tx On");
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
	} else {
		if ((inMsgParams[0]&0x01)!=0) {
			txOnFlag=TRUE;
			m_txPower->SetWindowTextA("Tx Standby");
			setIndicatorLight(TRANSMITTER_STATUS_LED,LED_YELLOW,drawingContextMain);
		} else {
			m_txPower->SetWindowTextA("Tx Off");
			setIndicatorLight(TRANSMITTER_STATUS_LED,LED_DARK_RED,drawingContextMain);
		}
	}
#else
	if ((inMsgParams[0]&0x01)!=0) {
		txOnFlag=TRUE;
		m_txPower->SetWindowTextA("Tx On");
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
		if (stingerWinFlag==1) {
			CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_BRIGHT_RED,drawingContextStinger);
		}
	} else {
		m_txPower->SetWindowTextA("Tx Off");
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_DARK_RED,drawingContextMain);
		if (stingerWinFlag==1) {
			CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_DARK_RED,drawingContextStinger);
		}

	}

#endif

	if ((inMsgParams[0]&0x04)!=0) {
		m_txFm->SetCheck(BST_UNCHECKED);
		m_txFmEnc->SetCheck(BST_UNCHECKED);
		m_txDst->SetCheck(BST_CHECKED);
	} else {
	   	if ((inMsgParams[0]&0x02)!=0) {
			m_txFm->SetCheck(BST_UNCHECKED);
			m_txFmEnc->SetCheck(BST_CHECKED);
			m_txDst->SetCheck(BST_UNCHECKED);
		} else {
			m_txFm->SetCheck(BST_CHECKED);
			m_txFmEnc->SetCheck(BST_UNCHECKED);
			m_txDst->SetCheck(BST_UNCHECKED);
		}
	}
}

void CMainDlg::updateStatusResponseParams(char latch0, char latch1) {

	if ((latch1&CMDBYTE2_DECLICK_MASK)!=0) {
		m_declick.SetCheck(BST_CHECKED);
		declickMode=1;
	} else {
		m_declick.SetCheck(BST_UNCHECKED);
		declickMode=0;
	}

	if ((latch0&CMDBYTE1_STEREO_ON_MASK)!=0) { // If Stereo on bit set in latch
		m_monoOn->SetCheck(BST_UNCHECKED);
		m_stereoOn->SetCheck(BST_CHECKED);
	} else  {
		m_monoOn->SetCheck(BST_CHECKED);
		m_stereoOn->SetCheck(BST_UNCHECKED);
	}
// If squelch bit set
	if ((latch0&CMDBYTE1_EXT_RANGE_MASK)!=0) {
		m_squelchOn.SetCheck(BST_UNCHECKED);
		m_squelchOff->SetCheck(BST_CHECKED);
		squelchMode=0;
	} else {
		m_squelchOn.SetCheck(BST_CHECKED);
		m_squelchOff->SetCheck(BST_UNCHECKED);
		squelchMode=1;
	}

if ((latch0&CMDBYTE1_STINGER_TX_MASK)!=0) {
		stingerStatus=STINGER_TXMITTING;
	} else {
		stingerStatus=STINGER_IDLE;
	}
//	updateStingerStatusLED();


//	if ((latch1&OPERLATCH1_ANALOG_MUTE_MASK)!=0) {
//		if ((inMsgParams[1]&OPERLATCH1_HEADPH_MUTE_MASK)!=0) {
/*		   m_hpMuteOn->SetCheck(BST_UNCHECKED);
		   m_analogMuteOn->SetCheck(BST_CHECKED);
		   m_muteOff->SetCheck(BST_UNCHECKED);*/
//		} else {
/*		   m_hpMuteOn->SetCheck(BST_CHECKED);
		   m_analogMuteOn->SetCheck(BST_UNCHECKED);
		   m_muteOff->SetCheck(BST_UNCHECKED);*/
//		}
//	} else {
/*	   m_hpMuteOn->SetCheck(BST_UNCHECKED);
	   m_analogMuteOn->SetCheck(BST_UNCHECKED);
	   m_muteOff->SetCheck(BST_CHECKED);*/
//	}

	if ((latch1&CMDBYTE2_TONE_NO_LOCK_MASK)!=0) {
		m_calToneNoLockOn->SetCheck(BST_CHECKED);
		m_calToneNoLockOff->SetCheck(BST_UNCHECKED);
//		m_calToneOn->SetCheck(BST_UNCHECKED);
	} else {
		m_calToneNoLockOn->SetCheck(BST_UNCHECKED);
		m_calToneNoLockOff->SetCheck(BST_CHECKED);
	}
	if ((latch0&CMDBYTE1_CALTONE_MASK)!=0) {
		myMenu.CheckMenuItem(ID_MISC_FULLSCALETONE, MF_CHECKED | MF_BYCOMMAND);
	} else {
		myMenu.CheckMenuItem(ID_MISC_FULLSCALETONE, MF_UNCHECKED | MF_BYCOMMAND);
	}

//	if ((latch1&OPERLATCH1_TX_ON_MASK)!=0) {
//		txOnFlag=TRUE;
//		m_txPower.SetWindowTextA("Tx On");
//	} else {
//		txOnFlag=FALSE;
//		m_txPower.SetWindowTextA("Tx Off");
//	}

}

void CMainDlg::setTxFreqCmd() {
	int i;
	outMsgStr[0]=CMD_TX_FREQ_SET_1; //"ab" command
	outMsgStr[1]=CMD_TX_FREQ_SET_2; // "ab" command
	outMsgStr[2]=(char)((txFreqKHz&(long int)0xFF0000)>>16); //High byte
	outMsgStr[3]=(char)((txFreqKHz&(long int)0x00FF00)>>8); //Mid byte
	outMsgStr[4]=(char)(txFreqKHz&(long int)0x0000FF); //Low byte
	writeCmd(CMD_TX_FREQ_SET_LEN);
}

void CMainDlg::readTxFreqCmd() {
	int i;
	outMsgStr[0]=CMD_TX_FREQ_REQ_1; //"aa" command
	outMsgStr[1]=CMD_TX_FREQ_REQ_2; // "aa" command
	writeCmd(CMD_TX_FREQ_REQ_LEN);
}


//I measured 11.72 volts at pin 1 U9 (after diode)
//The ADC was reading 119 (77 hex)
#define VOLTS_PER_ADCVALUE (float)11.72*(float)1.000/(float)119.0
#define DIODE_VOLTAGE (float)0.34 //Diode voltage offset
#define DISPLAY_MAX_VOLTAGE (double)15.0 //max value on display
#define VOLTAGE_CAL_SLOPE (float)0.975
#define VOLTAGE_CAL_OFFSET (float)0.344
#define SAMPLES_PER_SECOND (float)32000.0

int paramValueInt;
float paramValueFloat;
ULONG paramValueLong;
char prevSDErrorCode;
long unsigned sdRamLongValue;
long unsigned minFreq;
long unsigned maxFreq;
extern float convert_AD_to_dBm(char);
unsigned int convert_AD_to_mag(char);
int channelNumber=0;
extern CProgressCtrl *ChanLevelBar1;
extern CProgressCtrl *ChanLevelBar2;
extern CProgressCtrl *ChanLevelBar3;
extern CProgressCtrl *ChanLevelBar4;
extern CProgressCtrl *ChanLevelBar5;
extern CProgressCtrl *ChanLevelBar6;
extern CProgressCtrl *ChanLevelBar7;
extern CProgressCtrl *ChanLevelBar8;
int rssiA;
int rssiB;
extern CDC *drawingContextChannels;
extern CListBox *pTuneFreqText;
extern int desiredFreqNum;
int goodRecordDataInSubchannel=0;

void CMainDlg::statusRespUpdateControls() {

	int i,freqPos;
	int ledColor;
	int filterNumberRead;
	int prevChannelNumber;
	int paramValueInt2;

//	CEdit* m_FreqValue = (CEdit*) GetDlgItem(IDC_FREQ_VAL_TEXT);

// Process parameter 0--2 and set freq text

//	if (MyDeviceDetected==FALSE) return;

	if (ignoreNextSeveralSTResponses>0 && channelsWinFlag==0) {
		ignoreNextSeveralSTResponses--;
	} else {
	
	// Set response frequency from return message
		respFreqKHz=freq_3bytes_to_value(inMsgParams);



//	if (respFreqKHz!=tuneFreqKHz) { // If its not the current displayed freq
		prevChannelNumber=channelNumber;
		channelNumber=0; // initialize to invalid
		for (i=0;i<8;i++) { // Scan all 8 buttons, mabye it's one of these
			if (respFreqKHz==setFreqKHz[i]) {
				channelNumber=i+1;
				m_FreqSelect->SetPos(8-i);
				desiredFreqNum=9-m_FreqSelect->GetPos();
				tuneFreqKHz=respFreqKHz;
				if (channelNumber!=prevChannelNumber) {
					freqKHzToMHzString(respFreqKHz,freqValChars);
					m_FreqValue->SetWindowText(freqValChars);
					switch(channelNumber) {
						case 1:{m_FreqVal1->SetFocus();break;}
						case 2:{m_FreqVal2->SetFocus();break;}
						case 3:{m_FreqVal3->SetFocus();break;}
						case 4:{m_FreqVal4->SetFocus();break;}
						case 5:{m_FreqVal5->SetFocus();break;}
						case 6:{m_FreqVal6->SetFocus();break;}
						case 7:{m_FreqVal7->SetFocus();break;}
						case 8:{m_FreqVal8->SetFocus();break;}
					}
				}
				break;
			}
		}
		if (i==8) { // It's not one of the preset buttons, so set it to the button at the current position

/*
		// only do it if parameter is in valid range
		if (respFreqKHz>=MIN_FREQ_KHZ && respFreqKHz<=MAX_FREQ_KHZ) {
			freqPos=m_FreqSelect->GetPos();
			setFreqKHz[freqPos-1]=respFreqKHz;
			tuneFreqKHz=respFreqKHz;
			freqKHzToMHzString(respFreqKHz,freqValChars);
			m_FreqValue->SetWindowText(freqValChars);
			insertTextIntoFreqButton(freqPos,freqValChars);
		} else { 
			// Think of something to do here (when freq read back is out of valid frequency range)
		}
*/

		}

	//	}


// Process parameter 3 and 4 (sig proc settings)
		updateStatusResponseParams(inMsgParams[3],inMsgParams[4]);

// Update filter setting (param 3, bits 0-2)
		filterNumberRead=(int)inMsgParams[3]&(int)0x07;

		audioFilterNum=filterNumberRead;


switch (filterNumberRead) {
		case 0:
			audioFilterNum=0;
			break;
		case 1:
			audioFilterNum=0;
			break;
		case 2:
			audioFilterNum=1;
			break;
		case 3:
			audioFilterNum=3;
			break;
		case 4:
			audioFilterNum=4;
			break;
		case 5:
			audioFilterNum=2;
			break;
		case 6:
			audioFilterNum=5;
			break;
		case 7:
		default:
			audioFilterNum=6;
			break;
	}


		m_FilterSelect.SetPos(7-audioFilterNum);
	} // end of "ignoreNextSeveralSTResponses==0"

// process parameter 6 (RSSI A)
// First convert AD value to dBm value
	paramValueFloat=convert_AD_to_dBm(inMsgParams[6]);
	paramValueInt=convert_dBm_to_barGraph(paramValueFloat);
// set RSSI A text value display
	if (dbmMode==1) {
		sprintf(freqValChars,"%6.0f dBm",paramValueFloat);
		m_rssiLeftLabelText->SetWindowTextA("-100 dBm");
		m_rssiRightLabelText->SetWindowTextA("-40 dBm");
	} else {
		paramValueFloat=(float)paramValueInt;
		paramValueFloat*=(float)100.0;
		paramValueFloat/=(float)255.0;
		paramValueInt2=(int)paramValueFloat;
		sprintf(freqValChars,"   %6d",paramValueInt2);
		m_rssiLeftLabelText->SetWindowTextA("  0");
		m_rssiRightLabelText->SetWindowTextA("       100");
	}

// plot RSSI A dBm value in bargraph
	rssiA=paramValueInt;
	m_antAText.ResetContent();
	m_antAText.InsertString(0,freqValChars);
	m_antennaA.SetPos(rssiA);

// update antenna A locked indicator
	if (inMsgParams[6]&(int)0x080) {
		antAActiveFlag=FALSE;
		setIndicatorLight(ANT_A_ACTIVE_LED ,LED_DARK_GREEN,drawingContextMain);
	} else { 
		antAActiveFlag=TRUE;
		setIndicatorLight(ANT_A_ACTIVE_LED ,LED_GREEN,drawingContextMain);
	}
	
// process parameter 7 (RSSI B)
// First convert AD value to dBm value
	paramValueFloat=convert_AD_to_dBm(inMsgParams[7]);
	paramValueInt=convert_dBm_to_barGraph(paramValueFloat);
// set RSSI A text value display
	if (dbmMode==1) {
		sprintf(freqValChars,"%6.0f dBm",paramValueFloat);
	} else {
		paramValueFloat=(float)paramValueInt;
		paramValueFloat*=(float)100.0;
		paramValueFloat/=(float)255.0;
		paramValueInt2=(int)paramValueFloat;
		sprintf(freqValChars,"   %6d",paramValueInt2);
	}

// plot RSSI B dBm value in bargraph
	rssiB=paramValueInt;
	m_antBText.ResetContent();
	m_antBText.InsertString(0,freqValChars);
	m_antennaB.SetPos(rssiB);

/*-----------------------------------------------------------
// old way of processing parameter 6 and 7:
// process parameter 7 (RSSI B)
	if (dbmMode==1) {
// First convert AD value to dBm value
		paramValueFloat=convert_AD_to_dBm(inMsgParams[7]);

// set RSSI B value display
		sprintf(freqValChars,"%6.0f dBm",paramValueFloat);
		paramValueInt=convert_dBm_to_barGraph(paramValueFloat);
	} else {
		paramValueInt=convert_AD_to_mag(inMsgParams[7]);
		sprintf(freqValChars,"   %6d",paramValueInt);
		paramValueInt*=2;
	}
	rssiB=paramValueInt;
	m_antBText.ResetContent();
	m_antBText.InsertString(0,freqValChars);

// plot RSSI B dBm value in bargraph
	m_antennaB.SetPos(rssiB);
*/

// update antenna B locked indicator
	if (inMsgParams[7]&(int)0x080) {
		antBActiveFlag=FALSE;
		setIndicatorLight(ANT_B_ACTIVE_LED ,LED_DARK_GREEN,drawingContextMain);
	} else { 
		antBActiveFlag=TRUE;
		setIndicatorLight(ANT_B_ACTIVE_LED ,LED_GREEN,drawingContextMain);
	}

// process parameter 8 (Audio Level Left)
	paramValueInt=(unsigned int)inMsgParams[8]&(unsigned int)0x0ff;
	paramValueFloat=(float)paramValueInt;
	paramValueFloat-=81.0;
	paramValueFloat*=(255.0/(240.0-81.0));
	paramValueInt=(int)paramValueFloat; //back to integer for meter
	int result1=paramValueInt;
	m_leftAudio.SetPos(paramValueInt);

// process parameter 9 (Audio Level Right)
	paramValueInt=(unsigned int)inMsgParams[9]&(unsigned int)0x0ff;
	paramValueFloat=(float)paramValueInt;
	paramValueFloat-=81.0;
	paramValueFloat*=(255.0/(240.0-81.0));
	paramValueInt=(int)paramValueFloat; //back to integer for meter
	int result2=paramValueInt;
	m_rightAudio.SetPos(paramValueInt);

//	sprintf(freqValChars,"%3d (%3d), %3d (%3d)",(unsigned int)inMsgParams[8], (unsigned int)result1, (unsigned int)inMsgParams[9], (unsigned int)result2);
//	m_audioLevels->ResetContent();
//	m_audioLevels->InsertString(0,freqValChars);


	CWnd *xx;
	int trueOrFalse;
	trueOrFalse=1;
	if (stealthRecordWindowMode==1) {
//		if ((antAActiveFlag==FALSE) && (antBActiveFlag==FALSE)) { // if neither antenna locked
		if (goodRecordDataInSubchannel==0) {
			trueOrFalse=0;
			m_recStatusMsg->SetWindowTextA(" ");
			m_recCardPresentMsg->SetWindowTextA(" ");
			CMainDlg::setIndicatorLight(REC_CARD_PRESENT_LED,LED_BLACK,drawingContextMain);
			CMainDlg::setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_BLACK,drawingContextMain);
		}
	}
	xx=(CWnd*)GetDlgItem(IDC_RECEIVER_SD_CARD_SECTION2);
	xx->EnableWindow(trueOrFalse);


//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_RECORD);
//	xx->EnableWindow(trueOrFalse);
//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_STOP);
//	xx->EnableWindow(trueOrFalse);
//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_PLAY);
//	xx->EnableWindow(trueOrFalse);

/*
    xx=(CWnd*)GetDlgItem(IDC_REC_FILE_NUM_TEXT);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_REPEAT);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_128KBPS);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_96KBPS);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_64KBPS);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_32KBPS);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STATICREC_QUALTEXT);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_REC_NEXT_FILE_NUM);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_NEXT_FILE_NUM_TEXT);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHRECINFO);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_FILE_NUM_LOG_TEXT);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_FILE_LOG_HDR_TEXT);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_MODE_MONO);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_MODE_STEREO);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_STATICREC_MODE_TEXT);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_RECORDER_MSG);
	xx->EnableWindow(trueOrFalse);
	xx=(CWnd*)GetDlgItem(IDC_RECORDER_CARD_PRESENT);
	xx->EnableWindow(trueOrFalse);
*/

//	::InvalidateRect(m_hWnd,NULL,TRUE);
	this->UpdateWindow();

	
// if channels window exists then update proper bargraph
	if (channelsWinFlag!=0) {

		sprintf(freqValChars,"Ch#%1d%: %8.3f MHz",channelNumber,(float)respFreqKHz*(float)0.001);
		pTuneFreqText->ResetContent();
		pTuneFreqText->InsertString(0,freqValChars);

		if (rssiA>rssiB) { // use the larger rssi
			paramValueInt=rssiA;
		} else {
			paramValueInt=rssiB;
		}
		ledColor=LED_DARK_GREEN; // initialize to unlocked
		if ((antAActiveFlag==TRUE) || (antBActiveFlag==TRUE)) { // if either antenna locked
			ledColor=LED_GREEN; // indicate that the channel has a lock
		}
		switch (channelNumber) {
			case 1:
				ChanLevelBar1->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ1_LED,ledColor,drawingContextChannels);
				break;
			case 2:
				ChanLevelBar2->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ2_LED,ledColor,drawingContextChannels);
				break;
			case 3:
				ChanLevelBar3->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ3_LED,ledColor,drawingContextChannels);
				break;
			case 4:
				ChanLevelBar4->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ4_LED,ledColor,drawingContextChannels);
				break;
			case 5:
				ChanLevelBar5->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ5_LED,ledColor,drawingContextChannels);
				break;
			case 6:
				ChanLevelBar6->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ6_LED,ledColor,drawingContextChannels);
				break;
			case 7:
				ChanLevelBar7->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ7_LED,ledColor,drawingContextChannels);
				break;
			case 8:
				ChanLevelBar8->SetPos(paramValueInt);
				setIndicatorLight(LOCK_FREQ8_LED,ledColor,drawingContextChannels);
				break;
		}
	}


	if ((inMsgParams[3]&0x08)!=0) {
		m_txmtMsg->SetWindowTextA("Trans- mitting");
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
 		if (stingerWinFlag==1) {
			CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_BRIGHT_RED,drawingContextStinger);
		}

	} else {
		m_txmtMsg->SetWindowTextA(" ");
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_DARK_RED,drawingContextMain);
 		if (stingerWinFlag==1) {
			CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_DARK_RED,drawingContextStinger);
		}
	}
}

CString globalSerNum;

void CMainDlg::configRespUpdateControls() {
	int i;
	CString strval;
	char tempString[20];
	strval.Preallocate(20);

	if ((int)inMsgParams[0]==0) {
		strval.Format("0");
	} else if (inMsgParams[0]<=9) {
		strval.Format("%1d",(int)inMsgParams[0]);
	}
	if ((int)inMsgParams[1]==0) {
		strval.Format("%s0",strval);
	} else if ((int)inMsgParams[1]<=9) {
		strval.Format("%s%1d",strval,(int)inMsgParams[1]);
	}
	if ((int)inMsgParams[2]==0) {
		strval.Format("%s0",strval);
	} else if ((int)inMsgParams[2]<=9) {
		strval.Format("%s%1d",strval,(int)inMsgParams[2]);
	}
	globalSerNum=strval;

	m_serialNumber.ResetContent();
	m_serialNumber.InsertString(0,strval);

	
	
// process parameter 5 (voltage)
	paramValueInt=(int)inMsgParams[13]&(int)0x0ff;

	paramValueFloat=(float)paramValueInt;

#if 1==0 // adjust receiver voltage readout
	paramValueFloat*=VOLTS_PER_ADCVALUE;  //Scale ADC reading as volts
	paramValueFloat+=DIODE_VOLTAGE; //Add in the diode offset
	paramValueFloat*=VOLTAGE_CAL_SLOPE; //Calibrate after the fact
	paramValueFloat+=VOLTAGE_CAL_OFFSET; //Calibrate after the fact
#else
	paramValueFloat*=(float)0.1;  //Scale reading for each tic equal to 0.1 volt
#endif

// Adjust integer value for meter display
	paramValueInt=(int)(paramValueFloat*100.0/DISPLAY_MAX_VOLTAGE);

	// Set the voltage meter
//	m_supplyVoltage.SetPos(paramValueInt); // set the meter
// Set the voltage readout
	sprintf(displayString,"%5.1f V",paramValueFloat);
	m_voltageReadout.ResetContent();
	m_voltageReadout.InsertString(0,displayString);


	minFreq=(long unsigned)inMsgParams[7]&(long unsigned)0x0ff;
	minFreq<<=8;
	minFreq|=(long unsigned)inMsgParams[8]&(long unsigned)0x0ff;
	minFreq<<=8;
	minFreq|=(long unsigned)inMsgParams[9]&(long unsigned)0x0ff;

	maxFreq=(long unsigned)inMsgParams[10]&(long unsigned)0x0ff;
	maxFreq<<=8;
	maxFreq|=(long unsigned)inMsgParams[11]&(long unsigned)0x0ff;
	maxFreq<<=8;
	maxFreq|=(long unsigned)inMsgParams[12]&(long unsigned)0x0ff;


	if (aboutWinFlag==1) {
		// update about window information
		sprintf(tempString,"%8.3f",(float)minFreq*(float)0.001);
		m_minFreqTxt->SetWindowTextA(tempString);
		sprintf(tempString,"%8.3f",(float)maxFreq*(float)0.001);
		m_maxFreqTxt->SetWindowTextA(tempString);
		for (i=0;i<3;i++) {
			if (inMsgParams[i]<=9) {
				tempString[i]=inMsgParams[i]+'0';
			} else {
				tempString[i]='*';
			}
		}
		tempString[3]=0;
		m_serialNumberTxt->SetWindowTextA(tempString);


		int decimalFlag;
		decimalFlag=0;
		for (i=0;i<4;i++) {
			if (inMsgParams[i+3]<0x20) {
				tempString[i]=inMsgParams[i+3]+'0'; // if it's not a printing character, make it one
			} else {
				tempString[i]=inMsgParams[i+3]; // otherwise use it directly
			}
			if (tempString[i]=='.') {
				decimalFlag=1;
			}
		}
		tempString[4]=0;
		if (decimalFlag==0) {
			for (i=5;i>1;i--) {
				tempString[i]=tempString[i-1];
			}
			tempString[1]='.';
		}
		m_RxVersionTxt->SetWindowTextA(tempString);



		paramValueInt=(int)inMsgParams[13]&(int)0x0ff;
		paramValueFloat=(float)paramValueInt;
		paramValueFloat*=(float)0.1;  //Scale reading for each tic equal to 0.1 volt

		sprintf(tempString,"%5.1f V",paramValueFloat);
		m_RxVoltageTxt->SetWindowTextA(tempString);

	}


}

void CMainDlg::recordStatusRespUpdateControls() {
	if ((inMsgParams[0]&0x01)!=0) { // if recording
		m_recordmode->SetCheck(BST_CHECKED);
		if ((inMsgParams[0]&0x04)!=0) {
			setIndicatorLight(RECORD_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
			m_recordStatusMsg->SetWindowTextA("Recording");

		} else {
			setIndicatorLight(RECORD_STATUS_LED,LED_YELLOW,drawingContextMain);
			m_recordStatusMsg->SetWindowTextA("Rec On No Sig");
		}
	} else {
		setIndicatorLight(RECORD_STATUS_LED,LED_DARK_RED,drawingContextMain);
		m_recordmode->SetCheck(BST_UNCHECKED);
		m_recordStatusMsg->SetWindowTextA("Record Off");
	}
	if ((inMsgParams[0]&0x02)!=0) {
		m_overwriteWhenFull->SetCheck(BST_UNCHECKED);
	} else {
		m_overwriteWhenFull->SetCheck(BST_CHECKED);
	}
}

void CMainDlg::cardStatusRespUpdateControls() {
	float MBytesRemainFloat;
	float MBytesTotalFloat;
	float MBytesUsedFloat;

	// process bytes per cluster divided by 512
	bytesPerClusterDiv512=inMsgParams[8];

// process parameter 0--3: Compute bytes remaining (i.e., size of unused memory)
	paramValueLong=(ULONG)inMsgParams[0]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[1]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[2]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[3]&(ULONG)0x0ff;
	MBytesRemainFloat=(float)paramValueLong; //Set to number of clusters
	if (bytesPerClusterDiv512!=0) {
		MBytesRemainFloat*=(float)bytesPerClusterDiv512; // Convert to bytes per cluster/512
		MBytesRemainFloat*=(float)512.0;
	}
	MBytesRemainFloat/=(float)1024.0; //Convert to kBytes
	MBytesRemainFloat/=(float)1024.0; //Convert to MBytes

// process parameter 4--7: Calculate total bytes
	paramValueLong=(ULONG)inMsgParams[4]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[5]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[6]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[7]&(ULONG)0x0ff;
	MBytesTotalFloat=(float)paramValueLong; //Set to number of clusters
	if (bytesPerClusterDiv512!=0) {
		MBytesTotalFloat*=(float)bytesPerClusterDiv512; // Convert to clusters/512
		MBytesTotalFloat*=(float)512.0;
	}
	MBytesTotalFloat/=(float)1024.0; //Convert to kBytes
	MBytesTotalFloat/=(float)1024.0; //Convert to MBytes


// Uisplay total bytes readout
	if (bytesPerClusterDiv512!=0) {
  		sprintf(displayString,"%9.3f MB",MBytesTotalFloat);
	} else {
  		sprintf(displayString," ");
	}
	m_SDMemTotalTxt.ResetContent();
	m_SDMemTotalTxt.InsertString(0,displayString);
	

// Update bytes used readout
	MBytesUsedFloat=MBytesTotalFloat-MBytesRemainFloat;
	if (MBytesUsedFloat<0.0) MBytesUsedFloat=0.0;
	if (bytesPerClusterDiv512!=0) {
  		sprintf(displayString,"%9.3f MB",MBytesUsedFloat);
	} else {
  		sprintf(displayString," ");
	}
	m_SDMemUsedTxt.ResetContent();
	m_SDMemUsedTxt.InsertString(0,displayString);


	// Process parameter 13:  Set SD indicators
	// check SD door open
//	if (inMsgParams[13]&0x01) {
//		doorOpenFlag=TRUE;
//		setIndicatorLight(DOOR_OPEN_LED,LED_BRIGHT_RED,drawingContextMain);

//	} else {
//		setIndicatorLight(DOOR_OPEN_LED,LED_DARK_RED,drawingContextMain);
//		doorOpenFlag=FALSE;
//		setIndicatorLight(DOOR_OPEN_LED,LED_DARK_RED,drawingContextMain);
//	}

// check SD card present on byte 13
	if (inMsgParams[13]&0x02) { // Should be bit 1 (i.e. AND with 0x02) but due to error in connector, its temporarilly bit 2 until new circuit board
		cardDetectFlag=TRUE;
		setIndicatorLight(CARD_DETECT_LED,LED_GREEN,drawingContextMain);
		m_cardPresentMsg->SetWindowTextA("Card Present");
	} else {
		setIndicatorLight(CARD_DETECT_LED,LED_DARK_GREEN,drawingContextMain);
		cardDetectFlag=FALSE;
		bytesPerClusterDiv512=0; // Since card is missing, set this to zero as a flag to indicate values are bad
		m_cardPresentMsg->SetWindowTextA("No Card");
	}

#define COULD_NOT_OPEN_FILE		1	// Bad SD Card?
#define COULD_NOT_APPEND_AUDIO	2	// Issue a long time ago, shouldn't show up unless bad sectors maybe
#define	BUFFER_OVERFLOW			4	// Door was open too long
#define	DISK_FULL				8	// I've started erasing files
#define READ_PNTR_ERROR			16	// Bug I noticed once, see if it happens again
#define	SDRAM_ERROR				32	// failed SDRAM self-test
#define RTC_OscStopFlag			64	// Real time clock data is invalid

// check NIOS errors on byte 14
	m_sdErrorText.ResetContent();

// Mask out "Buffer overflow" error since it asserts after SD card is inserted
	paramValueInt=(int)(inMsgParams[14]&= ~0x04);
	
	if (paramValueInt!=0) {
		sdErrorFlag=TRUE;
		setIndicatorLight(SD_ERROR_LED,LED_BRIGHT_RED,drawingContextMain);
		m_sdErrorMsg->SetWindowTextA("SD Error");

		if (inMsgParams[14]&0x01) {
			sprintf(displayString,"Cannot open file (%d)",(int)inMsgParams[19]);
		}
		if (inMsgParams[14]&0x02) {
			sprintf(displayString,"Cannot append audio (%d)",(int)inMsgParams[19]);
		}
//		if (inMsgParams[14]&0x04) {
//			sprintf(displayString,"Buffer overflow (%d)",(int)inMsgParams[19]);
//		}
		if (inMsgParams[14]&0x08) {
			sprintf(displayString,"Disk full (%d)",(int)inMsgParams[19]);
		}
		if (inMsgParams[14]&0x10) {
			sprintf(displayString,"Read Pntr Error (%d)",(int)inMsgParams[19]);
		}
		if (inMsgParams[14]&0x20) {
			sprintf(displayString,"SD Ram Error (%d)",(int)inMsgParams[19]);
		}
		if (inMsgParams[14]&0x40) {
			sprintf(displayString,"RTC clock bad (%d)",(int)inMsgParams[19]);
		}
		m_sdErrorText.InsertString(0,displayString);
	} else {
		setIndicatorLight(SD_ERROR_LED,LED_DARK_RED,drawingContextMain);
		sdErrorFlag=FALSE;
		m_sdErrorText.ResetContent();
		m_sdErrorMsg->SetWindowTextA("No SD Error");
	}

	if ((MBytesTotalFloat==0.0) && ((inMsgParams[13]&0x04)==0)) { // if card detected...
		sprintf(displayString,"Reading card...");
		m_sdErrorText.InsertString(0,displayString);
	} else {
//		m_sdErrorText.ResetContent();
	}



// This is for debugging Pic minute counter tics
//	paramValueLong=(ULONG)inMsgParams[10]&(int)0x0ff;
//	paramValueLong<<=8;
//	paramValueLong+=(ULONG)inMsgParams[11]&(int)0x0ff;
//	sprintf(displayString,"%ld",paramValueLong); //print number of tics
//	m_SDMemUsed2.ResetContent();
//	m_SDMemUsed2.InsertString(0,displayString);

// Set the SD bytes used bargraph
	paramValueFloat=MBytesUsedFloat*(float)255.0/MBytesTotalFloat;
	paramValueInt=(int)paramValueFloat;
	m_SDMemUsedBargraph.SetPos(paramValueInt);

// process parameter 9--12: Set the RAM bytes used bargraph
	paramValueLong=(ULONG)inMsgParams[9]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[10]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[11]&(ULONG)0x0ff;
	paramValueLong<<=8;
	paramValueLong+=(ULONG)inMsgParams[12]&(ULONG)0x0ff;

#define TOTAL_RAM_CLUSTERS 0xfafffc

// Set the RAM bytes used bargraph
	paramValueFloat=(float)paramValueLong*(float)255.0/(float)TOTAL_RAM_CLUSTERS;
	paramValueInt=(int)paramValueFloat;
	m_RAMMemUsedBargraph.SetPos(paramValueInt);

//compute the time remaining
	paramValueFloat=MBytesRemainFloat*(float)1024.0*(float)1024.0;
	paramValueFloat/=(SAMPLES_PER_SECOND); // Used to be divided by an additional factor of 2, but I took it out since I think that was just a fudge factor

	if (m_monoOn->GetCheck()!=BST_CHECKED) { // If Stereo then two channels
		paramValueFloat/=(float)2.0;
	}
	paramValueLong=(ULONG)paramValueFloat; //total seconds;
	paramValueInt=(int)(paramValueLong/(ULONG)3600); //compute hours
	sprintf(displayString,"%4d:",paramValueInt); //print hours to string
	paramValueLong-=(ULONG)paramValueInt*(ULONG)3600; //subtract out hours
	paramValueInt=(int)(paramValueLong/(ULONG)60); //compute residue minutes
	if (paramValueInt<(int)10) {
		sprintf(displayString,"%s0%1d:",displayString,paramValueInt); //print minutes to string
	} else {
		sprintf(displayString,"%s%2d:",displayString,paramValueInt); //print minutes to string
	}
	paramValueLong-=(ULONG)paramValueInt*(ULONG)60; //subtract out minutes
	if (paramValueLong<(ULONG)10) {
		sprintf(displayString,"%s0%1ld",displayString,paramValueLong); //print seconds to string
	} else {
		sprintf(displayString,"%s%2ld",displayString,paramValueLong); //print seconds to string
	}
	m_timeRemain.ResetContent();
	m_timeRemain.InsertString(0,displayString);

//compute the time used
	paramValueFloat=MBytesUsedFloat*(float)1024.0*(float)1024.0;
	paramValueFloat/=(SAMPLES_PER_SECOND); // Used to be divided by an additional factor of 2, but I took it out since I think that was just a fudge factor

	if (m_monoOn->GetCheck()!=BST_CHECKED) { // If Stereo then two channels
		paramValueFloat/=(float)2.0;
	}
	paramValueLong=(ULONG)paramValueFloat; //total seconds;
	paramValueInt=(int)(paramValueLong/(ULONG)3600); //compute hours
	sprintf(displayString,"%4d:",paramValueInt); //print hours to string
	paramValueLong-=(ULONG)paramValueInt*(ULONG)3600; //subtract out hours
	paramValueInt=(int)(paramValueLong/(ULONG)60); //compute residue minutes
	if (paramValueInt<(int)10) {
		sprintf(displayString,"%s0%1d:",displayString,paramValueInt); //print minutes to string
	} else {
		sprintf(displayString,"%s%2d:",displayString,paramValueInt); //print minutes to string
	}
	paramValueLong-=(ULONG)paramValueInt*(ULONG)60; //subtract out minutes
	if (paramValueLong<(ULONG)10) {
		sprintf(displayString,"%s0%1ld",displayString,paramValueLong); //print seconds to string
	} else {
		sprintf(displayString,"%s%2ld",displayString,paramValueLong); //print seconds to string
	}
	m_timeUsed.ResetContent();
	m_timeUsed.InsertString(0,displayString);

}


void CMainDlg::txFreqUpdate() {
	// Process transmit frequency value
	paramValueLong=freq_3bytes_to_value(inMsgParams);
	if (paramValueLong!=txFreqKHz) {
		txFreqKHz=paramValueLong;
		freqKHzToMHzString(paramValueLong,freqValChars);
		m_txFreqValue->SetWindowText(freqValChars); 
	}
}

int lockedButNoIDCounter=0;

void CMainDlg::miscInfoUpdate() {
	// Process transmit frequency value

	if ((inMsgParams[2]^inMsgParams[3])==inMsgParams[4]) {
		if ((inMsgParams[2]&0x80)!=0) {
			goodRecordDataInSubchannel=12; // if this subchannel frame contains good record data, set counter to 12---must have 12 non-record data subchannel frames to disable
			stealthRecStatus=(int)inMsgParams[3]&(int)0x07;
			stealthRecMediumStatus=(inMsgParams[3]>>4)&0x03;
		} else {
			if (goodRecordDataInSubchannel>0) {
				goodRecordDataInSubchannel--;
			} else {
				stealthRecStatus=0;
				stealthRecMediumStatus=3;
			}
		}
		if ((antAActiveFlag!=TRUE) && (antBActiveFlag!=TRUE)) { // if neither antenna locked
			stealthRecStatus=0;
			stealthRecMediumStatus=3;
		}
		if (stealthRecordWindowMode==1 && goodRecordDataInSubchannel>0) {
			setStealthRecStatusLED();
		}

		sprintf(freqValChars,"%2x %2x %2x %2x",inMsgParams[2]&0x0ff,inMsgParams[3]&0x0ff,inMsgParams[4]&0x0ff,inMsgParams[5]&0x0ff);
		m_rawSubchBytes->ResetContent();
		m_rawSubchBytes->InsertString(0,freqValChars);

		if ((antAActiveFlag==TRUE) || (antBActiveFlag==TRUE)) { // if either antenna locked
			long unsigned txidval=((long unsigned)inMsgParams[2]&(long unsigned)0x0ff);
			txidval<<=8;
			txidval|=((long unsigned)inMsgParams[3]&(long unsigned)0x0ff);
			sprintf(freqValChars,"%4ld",txidval);
			if (txidval!=0) {
				lockedButNoIDCounter=0;
				if (txidval<(long unsigned)0x7FF) {
					m_txid->ResetContent();
					m_txid->InsertString(0,freqValChars);
				}
				sprintf(freqValChars,"%5.1f",(float)inMsgParams[5]/(float)10.0);
				m_txVoltage->ResetContent();
				m_txVoltage->InsertString(0,freqValChars);
			} else {
				lockedButNoIDCounter++;
				if (lockedButNoIDCounter>3) {
					m_txVoltage->ResetContent();
					m_txid->ResetContent();
				}
			}
		} else {
			m_txVoltage->ResetContent();
			m_txid->ResetContent();
		}
	}
}

void setStealthRecStatusLED() {
	switch(stealthRecStatus) {
		case 0:
		default:
			m_recStatusMsg->SetWindowTextA(" ");
			CMainDlg::setIndicatorLight(REC_STATUS_LED,LED_BLACK,drawingContextMain);
			break;
		case 1:
			m_recStatusMsg->SetWindowTextA("Playing");
			CMainDlg::setIndicatorLight(REC_STATUS_LED,LED_GREEN,drawingContextMain);
			CMainDlg::setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_GREEN,drawingContextMain);
			break;
		case 2:
			m_recStatusMsg->SetWindowTextA("Stopped");
			CMainDlg::setIndicatorLight(REC_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
			CMainDlg::setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
			break;
		case 3:
			m_recStatusMsg->SetWindowTextA("Paused");
			CMainDlg::setIndicatorLight(REC_STATUS_LED,LED_YELLOW,drawingContextMain);
			CMainDlg::setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
			break;
		case 4:
			m_recStatusMsg->SetWindowTextA("Recording");
			CMainDlg::setIndicatorLight(REC_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
			CMainDlg::setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
			break;
		case 5:
			m_recStatusMsg->SetWindowTextA("Fast Fwd/Bkwd");
			CMainDlg::setIndicatorLight(REC_STATUS_LED,LED_ORANGE,drawingContextMain);
			CMainDlg::setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_ORANGE,drawingContextMain);
			break;
	}
	switch(stealthRecMediumStatus) {
		case 0:
		default:
			m_recCardPresentMsg->SetWindowTextA("Card Present");
			CMainDlg::setIndicatorLight(REC_CARD_PRESENT_LED,LED_GREEN,drawingContextMain);
//			CMainDlg::setIndicatorLight(REC_USB_PRESENT_LED,LED_GREEN,drawingContextMain);
			break;
		case 1:
			m_recCardPresentMsg->SetWindowTextA("Card Present");
			CMainDlg::setIndicatorLight(REC_CARD_PRESENT_LED,LED_GREEN,drawingContextMain);
//			CMainDlg::setIndicatorLight(REC_USB_PRESENT_LED,LED_DARK_GREEN,drawingContextMain);
			break;
		case 2:
			m_recCardPresentMsg->SetWindowTextA("No Card");
			CMainDlg::setIndicatorLight(REC_CARD_PRESENT_LED,LED_DARK_GREEN,drawingContextMain);
//			CMainDlg::setIndicatorLight(REC_USB_PRESENT_LED,LED_GREEN,drawingContextMain);
			break;
		case 3:
			m_recCardPresentMsg->SetWindowTextA("No Card");
			CMainDlg::setIndicatorLight(REC_CARD_PRESENT_LED,LED_DARK_GREEN,drawingContextMain);
//			CMainDlg::setIndicatorLight(REC_USB_PRESENT_LED,LED_DARK_GREEN,drawingContextMain);
			break;
	}
}

// These values are computed as slope-intercept fit values to measured data
#define AD_VOLTAGE_REF (float)3.3
#define DBM_PER_VOLT (float)48.8
#define DBM_OFFSET (float)-117.1
#define BARGRAPH_LOWVALUE (float)-100.0 // dBm value of bargraph at low value
#define BARGRAPH_HIVALUE (float)-40.0 //dBm value at top
#define SPECGRAPH_LOWVALUE (float)-110.0 // dBm value of bargraph at low value
#define SPECGRAPH_HIVALUE (float)-40.0 //dBm value at top

float convert_AD_to_dBm(char inChar) {
// new way: scorpion type response
	float outFloat;
	if ((inChar&0x80)==0) {
		outFloat=(float)(inChar)-(float)127.0;
	} else {
		outFloat= (float)-1.0*(float)(inChar&0x7f);
	}
	
// old way: calibrated response
//	outFloat=(float)(inChar&(char)0x7f)/(float)256.0;//Mask out lock bit
//	outFloat*=AD_VOLTAGE_REF;//convert AD value to voltage
//	outFloat*=DBM_PER_VOLT; //Multiply by slope of dBm per volt curve
//	outFloat+=DBM_OFFSET; //add in offset of dBm per volt curve
	return (outFloat);
}


unsigned int convert_AD_to_mag(char inChar) {
	float tempFloat;
	unsigned int mag;
	mag=(unsigned int)(inChar&(char)0x7f);
	if (inChar&(char)0x80) {
    	mag=129-mag; // you would think this should be 128, but 129 seems to be right
	} else {
    	mag=mag;
	}

	// the following is to make the scale of the magnitude mode equal to the scale of the dBm mode
	tempFloat=(float)mag;
	tempFloat-=(float)27;
	tempFloat*=(float)127/(float)100;
	if (tempFloat<(float)0.0) tempFloat=(float)0.0;
	tempFloat+=(float)0.50;
	mag=(unsigned int)tempFloat;
	if (mag>127) mag=127;
	return (mag);
}

int convert_dBm_to_barGraph(float inFloat) {
	int outInt;
	inFloat-=BARGRAPH_LOWVALUE;//subtract off bargraph offset
	inFloat/=(BARGRAPH_HIVALUE-BARGRAPH_LOWVALUE); //divide by bargraph range
	inFloat*=(float)255.0; //range now scaled from 0.0--255.0
	outInt=(int)inFloat; //back to integer for bargraph
	return(outInt);
}


int convert_dBm_to_specGraph(float inFloat) {
	int outInt;
	inFloat-=SPECGRAPH_LOWVALUE;//subtract off spectrum graph offset
	inFloat/=(SPECGRAPH_HIVALUE-SPECGRAPH_LOWVALUE); //divide by spectrum graph range
	inFloat*=(float)255.0; //range now scaled from 0.0--255.0
	outInt=(int)inFloat; //back to integer for spectrum graph
	return(outInt);
}

void CMainDlg::OnNMReleasedcaptureFreqselect(NMHDR *pNMHDR, LRESULT *pResult)
{
	int freqPos;
	
	freqPos=m_FreqSelect->GetPos();
	switch(freqPos) {
		case 1:{m_FreqVal1->SetFocus();break;}
		case 2:{m_FreqVal2->SetFocus();break;}
		case 3:{m_FreqVal3->SetFocus();break;}
		case 4:{m_FreqVal4->SetFocus();break;}
		case 5:{m_FreqVal5->SetFocus();break;}
		case 6:{m_FreqVal6->SetFocus();break;}
		case 7:{m_FreqVal7->SetFocus();break;}
		case 8:{m_FreqVal8->SetFocus();break;}
	}
	tuneFreqKHz=setFreqKHz[8-freqPos];
    freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars); 
//	displayFreqKHz=tuneFreqKHz;

	setFreqOperCmd();
	
}


/*void CMainDlg::OnEnChangetxtfreqvalue()
{
	int freqPos;
	freqPos=m_FreqSelect->GetPos();
//	tuneFreqKHz=setFreqKHz[freqPos-1];
  //  freqKHzToMHzString(tuneFreqKHz,freqValChars);
//	m_FreqValue->SetWindowText(freqValChars); 
//	setFreqCmd();
}*/

//Just some values for example


void CMainDlg::OnBnClickedSetfreq()
{
	// TODO: Add your control notification handler code here
	ULONG freqVal;
	int freqPos;
//	CEdit* m_FreqValue = (CEdit*) GetDlgItem(IDC_FREQ_VAL_TEXT);
	m_FreqValue->GetWindowText(freqValString); 

		// Convert the string in the edit box to an integer.

	freqValDouble = strtod(freqValString, 0); //convert text to MHz float
	tuneFreqKHz=(ULONG)(1000.0*freqValDouble);  //convert to KHz integer

	limitFreqValRange(&tuneFreqKHz);
	freqPos=m_FreqSelect->GetPos();
	setFreqKHz[8-freqPos]=tuneFreqKHz;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	insertTextIntoFreqButton(freqPos,freqValChars);

	setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();

}

//void updateFreqTextDisplay() {
//	if (displayFreqKHz!=xx) {
//	freqKHzToMHzString(respFreqKHz,freqValChars);
//	m_FreqValue->SetWindowText(freqValChars);
//}


void CMainDlg::insertTextIntoFreqButton(int pos, char *text) {
	switch (pos) {
		case 1: {
			m_FreqVal1->SetWindowText(text);break;}
		case 2: {
			m_FreqVal2->SetWindowText(text); break;}
		case 3: {
			m_FreqVal3->SetWindowText(text); break;}
		case 4: {
			m_FreqVal4->SetWindowText(text);	break;}
		case 5: {
			m_FreqVal5->SetWindowText(text); break;}
		case 6: {
			m_FreqVal6->SetWindowText(text); break;}
		case 7: {
			m_FreqVal7->SetWindowText(text); break;}
		case 8: {
			m_FreqVal8->SetWindowText(text); break;}
	}
}


#if 1==1
/*extern CButton *m_FreqVal1;
extern CButton *m_FreqVal2;
extern CButton *m_FreqVal3;
extern CButton *m_FreqVal4;
extern CButton *m_FreqVal5;
extern CButton *m_FreqVal6;
extern CButton *m_FreqVal7;
extern CButton *m_FreqVal8;
*/
void CMainDlg::readFreqFile() {
	FILE *fp;
	ULONG value;
	BYTE oneByte;
	long unsigned luValue;
	int success,i,j,freqSet,useThisFreqSet;

//	minFreq=360000;
//	maxFreq=400000;
	fp=fopen("ScorpFreqChart.srp","rb");
	if (fp) { //Read frequency file
		freqSet=0;
		useThisFreqSet=0;
		while (freqSet<10) {
			i=0;
			while (i<8) {
				success=1;
				if (fread(&luValue,4,1,fp)!=1) {
					success=0;
					j=99;i=99;freqSet=99; // break out of all loops
				}
				if (i==0) {
					if (luValue>=minFreq && luValue<=maxFreq) {
						useThisFreqSet=1;
					}
				}
				if (useThisFreqSet==1 & i<8) {
					setFreqKHz[i]=luValue;
					freqKHzToMHzString(luValue,freqValChars);
					if (i==0) m_FreqVal1->SetWindowText(freqValChars);
					if (i==1) m_FreqVal2->SetWindowText(freqValChars);
					if (i==2) m_FreqVal3->SetWindowText(freqValChars);
					if (i==3) m_FreqVal4->SetWindowText(freqValChars);
					if (i==4) m_FreqVal5->SetWindowText(freqValChars);
					if (i==5) m_FreqVal6->SetWindowText(freqValChars);
					if (i==6) m_FreqVal7->SetWindowText(freqValChars);
					if (i==7) m_FreqVal8->SetWindowText(freqValChars);
				}
				i++;
			}
			if (useThisFreqSet==1) {
				freqSet=99;
			} else {
				freqSet++;
			}
		}
		fclose(fp);
		if (success==0) {
			AfxMessageBox("Could not read data from ScorpFreqChart.srp");
		}
		if (useThisFreqSet==0) {
			AfxMessageBox("Could not find frequency set for freq range");
		}
	} else {
		AfxMessageBox("Could not find file ScorpFreqChart.srp");
	}
}

#else
void CMainDlg::readFreqFile() {
	FILE *fp;
	ULONG value;
	int success,i;
	fp=fopen("freqs.txt","r");
	if (fp) { //Read frequency file
		for (i=0;i<8;i++) {
			success=fscanf(fp," %d",&value);
			if (success==1) {
				limitFreqValRange(&value);
			  if (value>MAX_FREQ_KHZ) value=MAX_FREQ_KHZ;
			  if (value<MIN_FREQ_KHZ) value=MIN_FREQ_KHZ;
			  freqKHzToMHzString(value,freqValChars);
			  setFreqKHz[i]=value;
			  if (i==0) m_FreqVal1->SetWindowText(freqValChars);
			  if (i==1) m_FreqVal2->SetWindowText(freqValChars);
			  if (i==2) m_FreqVal3->SetWindowText(freqValChars);
			  if (i==3) m_FreqVal4->SetWindowText(freqValChars);
			  if (i==4) m_FreqVal5->SetWindowText(freqValChars);
			  if (i==5) m_FreqVal6->SetWindowText(freqValChars);
			  if (i==6) m_FreqVal7->SetWindowText(freqValChars);
			  if (i==7) m_FreqVal8->SetWindowText(freqValChars);
			}

		}
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
		msgString.Format("Read %d lines from freqs.txt", i); 
		CDebugWinDlg::DisplayData2(msgString);
#endif
		fclose(fp);
	} else {
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
		CDebugWinDlg::DisplayData2("Could not read freqs.txt");
#endif
	}

}
#endif

void writeScorpFreqFile() {
	FILE *fp;
	ULONG value;
	int success,i;
	fp=fopen("ScorpFreqChart1.SRP","wb");
	if (fp) { //Read frequency file
		for (i=0;i<8;i++) { // fill one line with data
		    value=setFreqKHz[i];
			fwrite(&value,1,sizeof(value),fp);
		}
		for (i=0;i<72;i++) { // fill next 9 lines with zeros
		    value=0;
			fwrite(&value,1,sizeof(value),fp);
		}
		fclose(fp);
	} else {
	}
}
void CMainDlg::OnBnClickedLoadfreqs()
{
	readFreqFile();
}

void CMainDlg::OnBnClickedSavefreqs()
{
	writeScorpFreqFile();
}


int limitFreqValRange(ULONG *freqVal) {
// Fixes tx frequency inregards to limits, excluded freqs
// Returns 1 if freq value adjusted (for displaying in red to indicate change for user)
	if (*freqVal<MIN_FREQ_KHZ) {
		*freqVal=MIN_FREQ_KHZ; //fix underflow
		return(1);
	}
	if (*freqVal>MAX_FREQ_KHZ) {
		*freqVal=MAX_FREQ_KHZ; //fix overflow
		return(1);
	}
	return 0;
}

#define TX_FREQ_BW_KHZ 25
#define TX_FREQ_REJECT_PERIOD_KHZ 625
#define TX_FREQ_REJECT1_OFFSET_KHZ 0
#define TX_FREQ_REJECT2_OFFSET_KHZ 100
#define TX_FREQ_REJECT3_OFFSET_KHZ 525

int limitTxFreqValRange(ULONG *freqVal) {
// Fixes tx frequency inregards to limits, excluded freqs
// Returns non-zero if freq value adjusted (for displaying in red to indicate change for user)
	int returnval;
	int n;
	ULONG freqCheckVal;
	returnval=0;
	if (*freqVal<MIN_TX_FREQ_KHZ) {
		*freqVal=MIN_TX_FREQ_KHZ; //fix underflow
		returnval=1;
	}
	if (*freqVal>MAX_TX_FREQ_KHZ) {
		*freqVal=MAX_TX_FREQ_KHZ; //fix overflow
		returnval=2;
	}
	// compute position in cycle of rejected frequencies
	freqCheckVal= *freqVal;
	freqCheckVal-=MIN_TX_FREQ_KHZ;
	n=freqCheckVal/TX_FREQ_REJECT_PERIOD_KHZ;
	freqCheckVal-=(n*TX_FREQ_REJECT_PERIOD_KHZ);
	// Check to see if it is one of the rejected frequencies
	if (freqCheckVal==TX_FREQ_REJECT1_OFFSET_KHZ ||
		freqCheckVal==TX_FREQ_REJECT2_OFFSET_KHZ ||
		freqCheckVal==TX_FREQ_REJECT3_OFFSET_KHZ) {
		*freqVal-=TX_FREQ_BW_KHZ;
		if (*freqVal<=MIN_TX_FREQ_KHZ) *freqVal=MIN_TX_FREQ_KHZ+TX_FREQ_BW_KHZ;
		returnval=3;
	}
	return returnval;

}



void freqKHzToMHzString(ULONG freqVal,char *freqText) {
	float freqValFloat;
//	*freqVal *=(ULONG)4; //convert to multiple of 25KHz
//	*freqVal = *freqVal/(ULONG)100;
//	*freqVal *=(ULONG)25;
	freqValFloat=(float)freqVal * (float)0.001; //convert kHz integer to MHz float
//	sprintf(freqText,"%10.3f",freqValFloat); //convert MHz float to text
	sprintf(freqText,"%10.3f",freqValFloat); //convert MHz float to text
}


ULONG freq_3bytes_to_value(char *in) {
	ULONG returnVal;
	returnVal=((long)in[0])&((long)0x0ff);
	returnVal<<=8;
	returnVal+=((long)in[1])&((long)0x0ff);
	returnVal<<=8;
	returnVal+=((long)in[2])&((long)0x0ff);
	return(returnVal);
}




/*void CMainDlg::OnBnClickedNoisereduce()
{
	extendRangeFlag=0;
	setFreqOperCmd();
	// TODO: Add your control notification handler code here
}*/

/*void CMainDlg::OnBnClickedHdphone()
{
    toneOnFlag=0;
	muteAnalogFlag=0;
	muteHeadphoneFlag=1;
	setOperCmd();
	// TODO: Add your control notification handler code here
}
*/
/*void CMainDlg::OnBnClickedAnaloghdphone()
{
    toneOnFlag=0;
	muteAnalogFlag=1;
	muteHeadphoneFlag=1;
	setOperCmd();
/*	//New Code here
   WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstanceMHP;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
 //       MessageBox(NULL, "Window Registration Failed!", "Error!",
 //           MB_ICONEXCLAMATION | MB_OK);
 //       return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstanceMHP, NULL);

    if(hwnd == NULL)
    {
 //       MessageBox(NULL, "Window Creation Failed!", "Error!",
 //           MB_ICONEXCLAMATION | MB_OK);
 //       return 0;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
// End new code */

	// TODO: Add your control notification handler code here
/* } */

/*void CMainDlg::OnBnClickedCaltone() {
    toneOnFlag=1;
	muteAnalogFlag=1;
	muteHeadphoneFlag=1;
	setOperCmd();
	// TODO: Add your control notification handler code here
}*/

extern int desiredFreqNum;
extern int stingerOnFlag;

void CMainDlg::OnBnClickedfreqval1() {
//	m_FreqSelect->SetPos(1);
	m_FreqVal1->SetFocus();
	tuneFreqKHz=setFreqKHz[0];
	desiredFreqNum=1;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedfreqval2() {
//	m_FreqSelect->SetPos(2);
	m_FreqVal2->SetFocus();
	tuneFreqKHz=setFreqKHz[1];
	desiredFreqNum=2;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedfreqval3() {
//	m_FreqSelect->SetPos(3);
	m_FreqVal3->SetFocus();
	tuneFreqKHz=setFreqKHz[2];
	desiredFreqNum=3;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedfreqval4() {
//	m_FreqSelect->SetPos(4);
	m_FreqVal4->SetFocus();
	tuneFreqKHz=setFreqKHz[3];
	desiredFreqNum=4;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedfreqval5() {
//	m_FreqSelect->SetPos(5);
	m_FreqVal5->SetFocus();
	tuneFreqKHz=setFreqKHz[4];
	desiredFreqNum=5;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedfreqval6() {
//	m_FreqSelect->SetPos(6);
	m_FreqVal6->SetFocus();
	tuneFreqKHz=setFreqKHz[5];
	desiredFreqNum=6;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedfreqval7() {
//	m_FreqSelect->SetPos(7);
	m_FreqVal7->SetFocus();
	tuneFreqKHz=setFreqKHz[6];
	desiredFreqNum=7;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedfreqval8() {
//	m_FreqSelect->SetPos(8);
	m_FreqVal8->SetFocus();
	tuneFreqKHz=setFreqKHz[7];
	desiredFreqNum=8;
	freqKHzToMHzString(tuneFreqKHz,freqValChars);
	m_FreqValue->SetWindowText(freqValChars);
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

//void CMainDlg::OnBnClickedNoiseReduce()
//{
//	m_FreqSelect->SetPos(5);
//	tuneFreqKHz=setFreqKHz[4];
//	extendRangeFlag=0;
//	setOperCmd();
//}

//void CMainDlg::OnBnClickedRangeExtend()
//{
//	extendRangeFlag=1;
//	setOperCmd();
//
//}

//void CMainDlg::OnBnClickedMono1()
//{
//	stereoFlag=0;
//	setOperCmd();
//}



void CMainDlg::OnBnClickedPreemphasis()
{
	if (m_preemphasis->GetCheck()==BST_CHECKED)
		m_preemphasis->SetCheck(BST_UNCHECKED);
	else
		m_preemphasis->SetCheck(BST_CHECKED);
	sigProcSet();

}

void CMainDlg::OnBnClickedAgcLocal() {
	if (m_agcLocal->GetCheck()==BST_CHECKED)
		m_agcLocal->SetCheck(BST_UNCHECKED);
	else
		m_agcLocal->SetCheck(BST_CHECKED);
	sigProcSet();
}

void CMainDlg::OnBnClickedAgcRemote() {
	if (m_agcRemote->GetCheck()==BST_CHECKED)
		m_agcRemote->SetCheck(BST_UNCHECKED);
	else
		m_agcRemote->SetCheck(BST_CHECKED);
	sigProcSet();
}


void CMainDlg::OnBnClickedAncRemote() {
	if (m_ancRemote->GetCheck()==BST_CHECKED)
		m_ancRemote->SetCheck(BST_UNCHECKED);
	else
		m_ancRemote->SetCheck(BST_CHECKED);
	sigProcSet();
}

void CMainDlg::OnBnClickedSwapLr() {
	if (m_swapLr->GetCheck()==BST_CHECKED)
		m_swapLr->SetCheck(BST_UNCHECKED);
	else
		m_swapLr->SetCheck(BST_CHECKED);
	monoStereoSwapLRToggleFlag=1; // Indicate that SwapLR toggled for Stinger Cmd
	sigProcSet();
}

//int stingerWinFlag=0;
#if STINGER_WINDOW==1
void CMainDlg::OnBnClickedStingerwinbutton() {
	//create the stinger window.
	if (stingerWinFlag==0) {

		pStingerWinDlg = new CStingerDlg(this);

		BOOL ret=pStingerWinDlg->Create(IDD_STINGERWINDOW,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating Stinger Dialog");
		pStingerWinDlg->ShowWindow(SW_SHOW);
		m_stingerWinButton.EnableWindow(FALSE);//disable button for Stinger Window
		stingerWinFlag=1; // here it's really too late for this...so it's done in CStingerDlg::oninitdialog()
//		stingerWinFlag=1;
	}
}
#endif


//New globals
CPen fatBlackPen;
CBrush redBrush,dimRedBrush,greenBrush,blackBrush,yellowBrush,dimGreenBrush,orangeBrush;
int penFlag=0;
extern int stealthRecordWindowMode;
int DPI_setting=0;

void CMainDlg::setIndicatorLight(int indicatorNumber,int setValue, CDC *mydc) {
/*  This routine pretty much draws a circle of the desired color
    at a hardcoded location by index number (i.e. LED number)

	Not the most elegant way to simulate an LED, but nothing else worked

indicatorNumber --- number of desired LED
setValue --- color value:
			0 for black, 
			1 for dark red,
			2 for bright red,
			3 for green
*/

#if SIMPLE_GUI==1 // don't show these leds for the simple screen
//	if (indicatorNumber==DOOR_OPEN_LED) return;
//	if (indicatorNumber==CARD_DETECT_LED) return;
//	if (indicatorNumber==SD_ERROR_LED) return;
	if (indicatorNumber==USB_STATUS_LED) return;
	if (indicatorNumber==STINGER_TX_STATUS_LED) return;
//	if (indicatorNumber==STINGER_GENERIC_STATUS_LED) return;
//	if (indicatorNumber==TRANSMITTER_STATUS_LED) return;
#endif


	int x,y,size;
	switch (indicatorNumber) {
		case DOOR_OPEN_LED: {//LED 1
			if (stealthRecordWindowMode==1) 
				return;
			x=LED_SD_GROUP_XORIGIN;y=LED_SD_GROUP_YORIGIN;size=15;
			break;
		}
		case CARD_DETECT_LED: { //
			if (stealthRecordWindowMode==1) 
				return;
			x=LED_SD_GROUP_XORIGIN;y=LED_SD_GROUP_YORIGIN+LED_SD_GROUP_YSPACING;size=15;
			break;
		}
		case SD_ERROR_LED: {
			if (stealthRecordWindowMode==1) 
				return;
			x=LED_SD_GROUP_XORIGIN;y=LED_SD_GROUP_YORIGIN+2*LED_SD_GROUP_YSPACING;size=15;
			break;
		}
		case RECORD_STATUS_LED: {
			if (stealthRecordWindowMode==1) 
				return;
			x=LED_SD_GROUP_XORIGIN;y=LED_SD_GROUP_YORIGIN+3*LED_SD_GROUP_YSPACING;size=15;
			break;
		}
		case ANT_A_ACTIVE_LED: {
//#if SIMPLE_GUI==1
//			x=413;y=178;size=15;
//#else
			x=LED_ANT_GROUP_XORIGIN;y=LED_ANT_GROUP_YORIGIN+0*LED_ANT_GROUP_YSPACING;size=15;
//#endif
			break;
		}
		case ANT_B_ACTIVE_LED: {
//#if SIMPLE_GUI==1
//			
//#else
			x=LED_ANT_GROUP_XORIGIN;y=LED_ANT_GROUP_YORIGIN+1*LED_ANT_GROUP_YSPACING;size=15;
//#endif
			break;
		}
		case USB_STATUS_LED: {
			x=LED_USB_GROUP_XORIGIN;y=LED_USB_GROUP_YORIGIN;size=15;
			break;
		}
		case COM_STATUS_LED: {
			x=LED_COM_GROUP_XORIGIN;y=LED_COM_GROUP_YORIGIN;size=15;
			break;
		}
		case STINGER_TX_STATUS_LED: {
			x=LED_TX_STINGER_XORIGIN;y=LED_TX_STINGER_YORIGIN;size=15;
			break;
		}
		case STINGER_GENERIC_STATUS_LED: {
			x=LED_GENERIC_STINGER_XORIGIN;y=LED_GENERIC_STINGER_YORIGIN;size=15;
			break;
		}
		case TRANSMITTER_STATUS_LED: {
			x=LED_TRANSMITTER_STATUS_XORIGIN;y=LED_TRANSMITTER_STATUS_YORIGIN;size=15;
			break;
		}
		case LOCK_FREQ1_LED: {
			x=LED_CHAN_GROUP_XORIGIN+0*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case LOCK_FREQ2_LED: {
			x=LED_CHAN_GROUP_XORIGIN+1*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case LOCK_FREQ3_LED: {
			x=LED_CHAN_GROUP_XORIGIN+2*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case LOCK_FREQ4_LED: {
			x=LED_CHAN_GROUP_XORIGIN+3*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case LOCK_FREQ5_LED: {
			x=LED_CHAN_GROUP_XORIGIN+4*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case LOCK_FREQ6_LED: {
			x=LED_CHAN_GROUP_XORIGIN+5*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case LOCK_FREQ7_LED: {
			x=LED_CHAN_GROUP_XORIGIN+6*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case LOCK_FREQ8_LED: {
			x=LED_CHAN_GROUP_XORIGIN+7*LED_CHAN_GROUP_XSPACING;y=LED_CHAN_GROUP_YORIGIN+4*LED_CHAN_GROUP_YSPACING;size=15;
			break;
		}
		case STREC_PLAY_STATUS_LED: {
			x=755;y=140;size=15;
			break;
		}
		case STREC_LIVE_STATUS_LED: {
			x=755;y=111;size=15;
			break;
		}
		case STREC_RECORD_STATUS_LED: {
			x=755;y=45;size=15;
			break;
		}
		case STREC_PLAYBACK_STATUS_LED: {
			x=755;y=97;size=15;
			break;
		}
		case REC_STATUS_LED: {
			x=875;y=117;size=15;
			break;
		}
		case REC_CARD_PRESENT_LED: {
			x=875;y=137;size=15;
			break;
		}
		case REC_USB_PRESENT_LED: {
			x=875;y=157;size=15;
			break;
		}

	}
	if (DPI_setting!=0) {
		x=(int)((float)x*1.32);
		y=(int)((float)y*1.24);
		size=(int)((float)size*1.25);
	}

	if (penFlag==0) {
		penFlag=1;
		fatBlackPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
		redBrush.CreateSolidBrush(RGB(255,0,0));
		dimRedBrush.CreateSolidBrush(RGB(100,0,0));
		dimGreenBrush.CreateSolidBrush(RGB(0,100,0));
		greenBrush.CreateSolidBrush(RGB(0,255,0));
		blackBrush.CreateSolidBrush(RGB(0,0,0));
		yellowBrush.CreateSolidBrush(RGB(255,255,0));
		orangeBrush.CreateSolidBrush(RGB(255,165,0));
	}
	if (mydc==0) {
		CDebugWinDlg::DisplayData2("We should never get here...");
	}

	mydc->SelectObject(&fatBlackPen);
	if (setValue==LED_DARK_RED) mydc->SelectObject(dimRedBrush);
	else if (setValue==LED_BRIGHT_RED) mydc->SelectObject(redBrush);
	else if (setValue==LED_GREEN) mydc->SelectObject(greenBrush);
	else if (setValue==LED_YELLOW) mydc->SelectObject(yellowBrush);
	else if (setValue==LED_DARK_GREEN) mydc->SelectObject(dimGreenBrush);
	else if (setValue==LED_ORANGE) mydc->SelectObject(orangeBrush);
	else mydc->SelectObject(blackBrush);
	mydc->Ellipse(x,y,x+size,y+size);
}





#if 1==0
void CMainDlg::updateIndicatorLights() {

// Door open indicator
//	if (doorOpenFlag==TRUE) setIndicatorLight(DOOR_OPEN_LED,LED_BRIGHT_RED,drawingContextMain);
//	else setIndicatorLight(DOOR_OPEN_LED,LED_DARK_RED,drawingContextMain);

// Card detect
	if (cardDetectFlag==TRUE) setIndicatorLight(CARD_DETECT_LED,LED_BRIGHT_RED,drawingContextMain);
	else setIndicatorLight(CARD_DETECT_LED,LED_DARK_RED,drawingContextMain);

// SD error indicator
	if (sdErrorFlag==TRUE) setIndicatorLight(SD_ERROR_LED,LED_BRIGHT_RED,drawingContextMain);
	else setIndicatorLight(SD_ERROR_LED,LED_DARK_RED,drawingContextMain);

// Transmit indicator
	if (txOnFlag==TRUE) setIndicatorLight(TRANSMITTER_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
	else setIndicatorLight(TRANSMITTER_STATUS_LED,LED_DARK_RED,drawingContextMain);

// Write protect indicator
	if (writeProtectFlag==TRUE) setIndicatorLight(WRITE_PROTECT_LED,LED_BRIGHT_RED,drawingContextMain);
	else setIndicatorLight(WRITE_PROTECT_LED,LED_DARK_RED,drawingContextMain);

// Antenna A active
	if (antAActiveFlag==TRUE) setIndicatorLight(ANT_A_ACTIVE_LED ,LED_GREEN,drawingContextMain);
	else setIndicatorLight(ANT_A_ACTIVE_LED ,LED_DARK_GREEN,drawingContextMain);

// Antenna B active
	if (antBActiveFlag==TRUE) setIndicatorLight(ANT_B_ACTIVE_LED,LED_GREEN,drawingContextMain);
	else setIndicatorLight(ANT_B_ACTIVE_LED,LED_DARK_GREEN,drawingContextMain);

// USB status active
	if (MyUSBDeviceDetected==TRUE) setIndicatorLight(USB_STATUS_LED,LED_GREEN,drawingContextMain);
	else setIndicatorLight(USB_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);

// COM status active
	if (MyCOMDeviceDetected==TRUE) setIndicatorLight(COM_STATUS_LED,LED_GREEN,drawingContextMain);
	else setIndicatorLight(COM_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);

	// Message status active
//	if (MyDeviceDetected==TRUE) setIndicatorLight(MSG_STATUS_LED,LED_GREEN,mydc);
//	else setIndicatorLight(MSG_STATUS_LED,LED_BRIGHT_RED,mydc);
//	if (msgStatus==MSG_STATUS_TRANSMITTING) setIndicatorLight(MSG_STATUS_LED,LED_YELLOW,drawingContextMain);
//	else if (msgStatus==MSG_STATUS_RECEIVING) setIndicatorLight(MSG_STATUS_LED,LED_YELLOW,drawingContextMain);
//	else if (msgStatus==MSG_STATUS_BAD) setIndicatorLight(MSG_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
//	else setIndicatorLight(MSG_STATUS_LED,LED_GREEN,drawingContextMain);

}
#endif

void CMainDlg::OnBnClickedTxsetfreq()
{
	ULONG tuneCmd;
	int returnval;
	CDC *textDC;

	m_txFreqValue->GetWindowText(freqValString); 
// Convert the string in the edit box to an integer.
	freqValDouble = strtod(freqValString, 0); //convert text to MHz float
	txFreqKHz=(ULONG)(1000.0*freqValDouble);  //convert to KHz integer

	returnval=limitTxFreqValRange(&txFreqKHz);
    freqKHzToMHzString(txFreqKHz,freqValChars);
	if (returnval!=0) {
// Tried to make text red if freq value changed, but doesnt work
//		textDC=m_FreqValue->GetDC();
//		textDC->SelectObject(redBrush);
// I'll add an asterisk to indicate changed freq val instead
		sprintf(freqValChars,"%s*",freqValChars);
	}
	m_txFreqValue->SetWindowText(freqValChars); 
//    textDC->SelectObject(blackBrush);

	setTxFreqCmd();  //Set TX freq message "ab"
}

void CMainDlg::OnEnUpdateFmtransmitfreq()
{
	m_txFreqValue->GetWindowText(freqValString);
	if (freqValString=="mhp123") {
		if (txFreqKHz==(ULONG)0) { //freq not set yet, reset string to blank
			m_txFreqValue->SetWindowText("");
		} else {
			limitTxFreqValRange(&txFreqKHz); // Check proper limits and excluded freqs
			freqKHzToMHzString(txFreqKHz,freqValChars); //immediately reset string to current tx frequency
			m_txFreqValue->SetWindowText(freqValChars);
		}

		pDebugWinDlg = new CDebugWinDlg();
//		scanDrawingContext = new CDC();

		BOOL ret=pDebugWinDlg->Create(IDD_DEBUGWINDOW,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating Dialog");
        pDebugWinDlg->ShowWindow(SW_SHOW);
		debugWinFlag=1;
	} else if (freqValString=="mhp456") {
		if (txFreqKHz==(ULONG)0) { //freq not set yet, reset string to blank
			m_txFreqValue->SetWindowText("");
		} else {
			limitTxFreqValRange(&txFreqKHz); // Check proper limits and excluded freqs
			freqKHzToMHzString(txFreqKHz,freqValChars); //immediately reset string to current tx frequency
			m_txFreqValue->SetWindowText(freqValChars);
		}

		pDebugAGCWinDlg = new CDebugAGCWinDlg();
//		scanDrawingContext = new CDC();

		BOOL ret=pDebugAGCWinDlg->Create(IDD_DEBUGAGCWINDOW,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating AGC Dialog");
        pDebugAGCWinDlg->ShowWindow(SW_SHOW);
		debugAGCWinFlag=1;
	}

}

/*void CMainDlg::OnBnClickedUpdate()
{
	statusReqCmd();
	statusRespUpdateControls();

}
*/
#define TX_REF (ULONG)10000  // 10.0 MHz
#define TX_LO	(ULONG)400000 // 400.0 MHz
#define TX_NUM_BITS 17
#define TX_R (ULONG)3

/*
ULONG  tuneCmdToTxFreq(ULONG tuneCmd) {
  ULONG n;
  ULONG txFreq;
  double tempDouble;

// Compute N
  tuneCmd=freqKHz;
  tuneCmd*=TX_R;
  tuneCmd/=TX_REF;
  n=(int)(tuneCmd);

// Compute RF_FN
  tuneCmd=freqKHz-TX_LO;
  tuneCmd*=TX_R;
  tempDouble=(double)tuneCmd;
  tempDouble/=(double)(TX_REF);
  tuneCmd=(ULONG)(tempDouble);
  tempDouble-=(double)(tuneCmd);
  tempDouble*=(double)((ULONG)0x01<<TX_NUM_BITS);
  tuneCmd=(ULONG)tempDouble;
  tuneCmd+=(n<<22);

  n=(tuneCmd>>22)&0x07f
  n*=TX_REF;
  tempDouble=(double)n/(double)TX_R;
  n=tuneCmd&0x03fffff;
  tempDouble2=(double)



  return tuneCmd;
}
*/

/*ULONG  txFreqToTuneCmd(ULONG freqKHz) {
  int n;
  ULONG tuneCmd;
  double tempDouble;

// Compute N
  tuneCmd=freqKHz;
  tuneCmd*=TX_R;
  tuneCmd/=TX_REF;
  n=(int)(tuneCmd);

// Compute RF_FN
  tuneCmd=freqKHz-TX_LO;
  tuneCmd*=TX_R;
  tempDouble=(double)tuneCmd;
  tempDouble/=(double)(TX_REF);
  tuneCmd=(ULONG)(tempDouble);
  tempDouble-=(double)(tuneCmd);
  tempDouble*=(double)((ULONG)0x01<<TX_NUM_BITS);
  tuneCmd=(ULONG)tempDouble;
  tuneCmd+=(n<<22);
  return tuneCmd;
}*/


/*void CMainDlg::OnBnClickedSquelchOn()
{
	m_squelchOn.SetCheck(BST_CHECKED);
	sigProcCmd();
}*/

void CMainDlg::OnBnClickedMonoOn() {
	m_monoOn->SetCheck(BST_CHECKED);
	m_stereoOn->SetCheck(BST_UNCHECKED);
	monoStereoSwapLRToggleFlag=1;  // Indicate that mono/stereo toggled for Stinger Cmd
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		desiredFreqNum=9-m_FreqSelect->GetPos();
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedStereo1() {
	m_monoOn->SetCheck(BST_UNCHECKED);
	m_stereoOn->SetCheck(BST_CHECKED);
	monoStereoSwapLRToggleFlag=1;  // Indicate that mono/stereo toggled for Stinger Cmd
	setFreqOperCmd();
	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
		desiredFreqNum=9-m_FreqSelect->GetPos();
		stingerOnFlag=TRUE; // always turn on when auto stinger command tx is set
		outputStingerCmd(STINGER_TX_SPECIFIC);
	}
}

void CMainDlg::OnBnClickedSquelchOn() {
	m_squelchOn.SetCheck(BST_CHECKED);
	squelchMode=1;
	setFreqOperCmd();
}
void CMainDlg::OnBnClickedSquelchoff() {
	m_squelchOn.SetCheck(BST_UNCHECKED);
	squelchMode=0;
	setFreqOperCmd();
}

void CMainDlg::OnBnClickedNomute() {
	muteToneMode=0;
	setFreqOperCmd();
}

void CMainDlg::OnBnClickedHdphone() {
	muteToneMode=1;
	sigProcSet();
}

void CMainDlg::OnBnClickedAnaloghdphone() {
	muteToneMode=3;
	sigProcSet();
}

void CMainDlg::OnBnClickedCalToneNotLockedOff() {
	int x=~2;
	calToneMode&=~2;
	setFreqOperCmd();
}

void CMainDlg::OnBnClickedCalToneNotLockedOn() {
	calToneMode|=2;
	setFreqOperCmd();
}


//void CMainDlg::OnBnClickedCaltoneOn() {
//	calToneMode=1;
//	setFreqOperCmd();
//}



void CMainDlg::OnBnClickedFilt400HzVerySharp() {
	audioFilterNum=6;
//	m_FilterSelect.SetPos(audioFilterNum+1);
	setFreqOperCmd();
//	if (MyDeviceDetected==TRUE) {
//		m_FilterSelect.SetPos(audioFilterNum+1);
//	}
}

void CMainDlg::OnBnClickedFilt400HzSharp() {
	audioFilterNum=5;
//	m_FilterSelect.SetPos(audioFilterNum+1);
	setFreqOperCmd();
//	if (MyDeviceDetected==TRUE) {
//		m_FilterSelect.SetPos(audioFilterNum+1);
//	}
}
void CMainDlg::OnBnClickedFilt200HzVerySharp() {
	audioFilterNum=4;
//	m_FilterSelect.SetPos(audioFilterNum+1);
	setFreqOperCmd();
//	if (MyDeviceDetected==TRUE) {
//		m_FilterSelect.SetPos(audioFilterNum+1);
//	}
}
void CMainDlg::OnBnClickedFilt200HzSharp() {
	audioFilterNum=3;
//	m_FilterSelect.SetPos(audioFilterNum+1);
	setFreqOperCmd();
//	if (MyDeviceDetected==TRUE) {
//		m_FilterSelect.SetPos(audioFilterNum+1);
//	}
}
void CMainDlg::OnBnClickedFilt200Hz() {
	audioFilterNum=2;
//	m_FilterSelect.SetPos(audioFilterNum+1);
	setFreqOperCmd();
//	if (MyDeviceDetected==TRUE) {
//		m_FilterSelect.SetPos(audioFilterNum+1);
//	}
}
void CMainDlg::OnBnClickedFilt100Hz() {
	audioFilterNum=1;
//	m_FilterSelect.SetPos(audioFilterNum+1);
	setFreqOperCmd();
//	if (MyDeviceDetected==TRUE) {
//		m_FilterSelect.SetPos(audioFilterNum+1);
//	}
}
void CMainDlg::OnBnClickedFiltFlat() {
	audioFilterNum=0;
//	m_FilterSelect.SetPos(audioFilterNum+1);
	setFreqOperCmd();
//	if (MyDeviceDetected==TRUE) {
//		m_FilterSelect.SetPos(audioFilterNum+1);
//	}
}

//void CAboutDlg::OnBnClickedDogleashRefresh()
//{
	// TODO: Add your control notification handler code here
//}

/* void CMainDlg::OnBnClickedSquelch() {
	if (m_squelchOn.GetCheck()==BST_CHECKED)
		m_squelch->SetCheck(BST_UNCHECKED);
	else
		m_squelch->SetCheck(BST_CHECKED);
	sigProcCmd();
}
*/

extern int audioPlayerWinFlag;
extern CDialog *pAudioPlayerWinDlg;

void CMainDlg::OnBnClickedAudioSetupWin() {
	if (audioPlayerWinFlag==0) {
		audioPlayerWinFlag=1;
		pAudioPlayerWinDlg = new CAudioPlayerPathDlg(this);

		BOOL ret=pAudioPlayerWinDlg->Create(IDD_AUDIOSETUPWIN,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating Audio Setup Dialog");
		pAudioPlayerWinDlg->ShowWindow(SW_SHOW);
//		m_EditFileNameWinButton.EnableWindow(FALSE);//disable button for Stinger Window
	}
}

void CMainDlg::OnBnClickedEditfilename() {
	if (editFileNameWinFlag==0) {
		editFileNameWinFlag=1;
		pEditFileNameWinDlg = new CEditFileNameDlg(this);

		BOOL ret=pEditFileNameWinDlg->Create(IDD_EDITFILENAMEWIN,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating Edit File Name Dialog");
		pEditFileNameWinDlg->ShowWindow(SW_SHOW);
//		m_EditFileNameWinButton.EnableWindow(FALSE);//disable button for Stinger Window
	}
}
void CMainDlg::setFileNameCmd() {
	int i;
	outMsgStr[0]=CMD_NEXT_FILE_NAME_SET_1; //"cj" command
	outMsgStr[1]=CMD_NEXT_FILE_NAME_SET_2; // "cj" command
	for (i=0;i<8;i++) {
		outMsgStr[i+2]=SDFileNameStr[i];
	}
	CMainDlg::writeCmd(CMD_NEXT_FILE_NAME_SET_LEN);
}

void CMainDlg::nextFileNameUpdate() {
	int i;
	char oneChar;
//	int updateFlag;
//	if (MyDeviceDetected==TRUE) {
		for (i=0;i<8;i++) {
			prevSDFileNameStr[i]=SDFileNameStr[i];
		}
		prevSDFileNameStr[8]=0;

		for (i=0;i<8;i++) {
			oneChar=inMsgParams[i];
			if (i==0) {
				if ((oneChar>='A' && oneChar<='Z') || (oneChar>='a' && oneChar<='z') || oneChar!='-' || oneChar!='*') {
					SDFileNameStr[i]=inMsgParams[i];
				} else {
					SDFileNameStr[i]='?';
				}
			} else {
				if ((oneChar>='0' && oneChar<='9') || oneChar!='-' || oneChar!='*') {
					SDFileNameStr[i]=inMsgParams[i];
				} else {
					SDFileNameStr[i]='?';
				}
			}
		}
		SDFileNameStr[8]=0; // Ensure a null for last character

		int diffFlag=0;
		for (i=0;i<8;i++) {
			if (prevSDFileNameStr[i]!=SDFileNameStr[i]) {
				diffFlag=1;
			}
		}
		if (diffFlag!=0) {
			FILE *fp=fopen("timelog.txt","a");
			fprintf(fp,"FILE NAME CHANGE:\n");
			fprintf(fp,"Prev FileName: %s,  Current Filename: %s,  ",prevSDFileNameStr,SDFileNameStr);
			fprintf(fp,"Date: %s, Time: %s\n",dateString,timeString);
			fclose(fp);

		}
		
//		updateFlag=0;
//		for (i=0;i<8;i++) {
//			if (prevSDFileNameStr[i]!=SDFileNameStr[i]) {
//				updateFlag=1;
//				break;
//			}
//		}
			
//		if (updateFlag==1) {
			pnextFileNameText->ResetContent();
			pnextFileNameText->InsertString(0,SDFileNameStr);
//		}

//		for (i=0;i<8;i++) {
//			prevSDFileNameStr[i]=SDFileNameStr[i];
//		}

//	}
}



void CMainDlg::OnBnClickedDeclick() {
	if (m_declick.GetCheck()==BST_CHECKED) {
		m_declick.SetCheck(BST_UNCHECKED);
	    declickMode=0;
	} else {
		m_declick.SetCheck(BST_CHECKED);
	    declickMode=1;
	}
	setFreqOperCmd();
}

int gotToHere=0;
void CMainDlg::bytesPerClusterCmd() {
	gotToHere++;
//	outMsgStr[0]=readBytesPerClusterCmdStr[0]; //"dn" command
//	outMsgStr[1]=readBytesPerClusterCmdStr[1];
//#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//	msgString.Format("Output DN Msg: Read bytes per cluster/512");
//	CDebugWinDlg::DisplayData2(msgString);
//#endif
//	writeCmd(CMD_READ_BYTES_PER_CLUSTER_LEN);

#if INTERFACE_USB==1
	readResp(RESP_READ_BYTES_PER_CLUSTER_LEN);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	msgString.Format("Input DN Msg: BPC/512=%2x",0x0ff&inMsgParams[0]);
	CDebugWinDlg::DisplayData2(msgString);
#endif

	bytesPerClusterDiv512=inMsgParams[0];
#endif
}

extern CSetSysClkDlg *pSetSysClkDlg;




void CMainDlg::OnNMCustomdrawFreqselect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

#include "processFile.h"


void CMainDlg::OnMenuProcessFile() {
	CFileDialog dlgFile(TRUE);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	dlgFile.GetOFN().nMaxFile = c_cMaxFiles;

	INT_PTR resultFileSearch;
	resultFileSearch=dlgFile.DoModal();
	if (resultFileSearch==IDOK) {

		FILE *fp;
		float sum;
		fp=fopen(fileName,"r");
		if (fp==0) {
			AfxMessageBox("Cannot open file");
		} else {
			sum=processFile(fp);
			fclose(fp);
			CString theSumIsString;
			theSumIsString.Format("The sum is %f",sum);

			AfxMessageBox(theSumIsString);
		}
	}
	fileName.ReleaseBuffer();
}

#include "passwordDlg.h"

void CMainDlg::OnMenuPassword() {
	if (enterPasswordWinFlag==0) {
		enterPasswordWinFlag=1;
//		CMenu x = m_hWnd->GetMenu(IDR_MENU2)
//		x->EnableMenuItem(ID_OPTIONS_PASSWORD,MF_GRAYED);
//		m_hWnd->EnableMenuItem(ID_OPTIONS_PASSWORD,MF_GRAYED);
//		EnableMenuItem(ID_OPTIONS_PASSWORD,MF_GRAYED);


		pEnterPasswordWinDlg = new CEnterPasswordDlg(this);
		BOOL ret=pEnterPasswordWinDlg->Create(IDD_ENTERPASSWORDWIN,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating Edit File Name Dialog");
		pEnterPasswordWinDlg->ShowWindow(SW_SHOW);

//		m_EditFileNameWinButton.EnableWindow(FALSE);//disable button for Stinger Window
	}

}

extern int specialStingerCmdWinFlag;
extern CSpecialStingerCmdDlg *pSpecialStingerCmdWinDlg;

void CMainDlg::OnMenuSpecialStingerCmd() {
	updateStingerAddress(); // take this opportunity to update stinger address from selection edit field
	if (specialStingerCmdWinFlag==0) {
		specialStingerCmdWinFlag=1;

		pSpecialStingerCmdWinDlg = new CSpecialStingerCmdDlg(this);
		BOOL ret=pSpecialStingerCmdWinDlg->Create(IDD_SPECIALSTINGERCMDWIN,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating Special Stinger Command Dialog");
		pSpecialStingerCmdWinDlg->ShowWindow(SW_SHOW);
	}

}

extern int stealthRecSpecialWinFlag;
extern CStealthRecSpecialWinDlg *pStealthRecSpecialWinDlg;


void CMainDlg::OnMenuStealthRecSpecialFunctions() {
	if (stealthRecSpecialWinFlag==0) {
		stealthRecSpecialWinFlag=1;

		pStealthRecSpecialWinDlg = new CStealthRecSpecialWinDlg(this);
		BOOL ret=pStealthRecSpecialWinDlg->Create(IDD_STEALTHRECSPECIALWIN,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating Stealth Record Special Dialog");
		pStealthRecSpecialWinDlg->ShowWindow(SW_SHOW);
	}

}

void CMainDlg::setCOMStatus(int xCOMStatus) {
// Sets Com status light and boolean values
// ComGood indicates that the COM port is initialized, so
//	 we should transmit and seek a response
// msgGood indicates that a successful write-read has been done and a good message received
//   so we should make the light green

	COMStatus=xCOMStatus; // Copy parameter COM status to global variable
	ComGood=FALSE;  // initialize to false

	if (COMStatus!=COM_STATUS_DEVICE_FOUND) {
//		firstConfigRespReceived=0; // reset so a config response is required to initialize
		switch (COMStatus) {
			case COM_STATUS_OK: { // means COM port is initialized and good message sync
				ComGood=TRUE;
				m_usbStatusButton.SetWindowTextA("COM Initialized");
				break;
			}
			case COM_STATUS_NO_RESPONSE: { // Means COM port initialized, but didn't get response from device
				ComGood=TRUE;
				m_usbStatusButton.SetWindowTextA("Looking for RD-1200");
				break;
			}
			case COM_STATUS_BAD_SYNC: { // We received an unexpected message, so message sync is off
				ComGood=TRUE;
				m_usbStatusButton.SetWindowTextA("Bad Msg Sync");
				break;
			}
	  // The remaining cases are all considered COM port initialization errors
			case COM_STATUS_UNINITIALIZED: {
				m_usbStatusButton.SetWindowTextA("COM Uninitialized");
				break;
			}
			case COM_STATUS_CANT_OPEN: {
				m_usbStatusButton.SetWindowTextA("Cannot Open COM");
				break;
			}
			case COM_STATUS_CANT_WRITE: {
				m_usbStatusButton.SetWindowTextA("Cannot Write COM");
				break;
			}
			case COM_STATUS_CANT_READ: {
				m_usbStatusButton.SetWindowTextA("No RD-1200 found");
				break;
			}
			case COM_STATUS_CANT_SET_BUFFER: {
				m_usbStatusButton.SetWindowTextA("Cannot Set Buffer");
				break;
			}
			case COM_STATUS_CANT_GET_STATE: {
				m_usbStatusButton.SetWindowTextA("Cannot Get State");
				break;
			}
			case COM_STATUS_CANT_SET_STATE: {
				m_usbStatusButton.SetWindowTextA("Cannot Set State");
				break;
			}
			case COM_STATUS_CANT_GET_TIMEOUTS: {
				m_usbStatusButton.SetWindowTextA("Cannot Get Timeout");
				break;
			}
			case COM_STATUS_CANT_SET_TIMEOUTS: {
				m_usbStatusButton.SetWindowTextA("Cannot Set Timeout");
				break;
			}
			default: {
				m_usbStatusButton.SetWindowTextA("Unknown Error");
				break;
			}
		}
		globalSerNum=""; // reset serial number
	} else { // The status was COM_STATUS_DEVICE_FOUND meaning we did a write-read and got a good message
		ComGood=TRUE;
		m_usbStatusButton.SetWindowTextA("RD-1200 Connected");
	}
	if (!powerOn) {
		setIndicatorLight(COM_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
	} else if (COMStatus==COM_STATUS_DEVICE_FOUND) {
		setIndicatorLight(COM_STATUS_LED,LED_GREEN,drawingContextMain);
	} else if (ComGood) {
		setIndicatorLight(COM_STATUS_LED,LED_YELLOW,drawingContextMain);
	} else {
		setIndicatorLight(COM_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);
	}

}

void CMainDlg::blankMainDisplayIndicators() {
	m_rightAudio.SetPos(0);
	m_leftAudio.SetPos(0);
	m_antennaA.SetPos(0);
	m_antennaB.SetPos(0);
//	m_supplyVoltage.SetPos(0);
	m_SDMemUsedBargraph.SetPos(0);
	m_RAMMemUsedBargraph.SetPos(0);

	m_voltageReadout.ResetContent();
	m_SDMemTotalTxt.ResetContent();
	m_SDMemUsedTxt.ResetContent();
	m_timeRemain.ResetContent();
	m_timeUsed.ResetContent();
	m_antAText.ResetContent();
	m_antBText.ResetContent();

	m_sdErrorText.ResetContent();
//	m_memUsedText.ResetContent();
	m_serialNumber.ResetContent();
	pnextFileNameText->ResetContent();
//	m_txFreqValue->ResetContent();

	setIndicatorLight(SD_ERROR_LED,LED_DARK_RED,drawingContextMain);
	setIndicatorLight(CARD_DETECT_LED,LED_DARK_GREEN,drawingContextMain);
	setIndicatorLight(RECORD_STATUS_LED,LED_DARK_RED,drawingContextMain);
//	setIndicatorLight(DOOR_OPEN_LED,LED_DARK_RED,drawingContextMain);

	setIndicatorLight(ANT_A_ACTIVE_LED,LED_DARK_GREEN,drawingContextMain);
	setIndicatorLight(ANT_B_ACTIVE_LED,LED_DARK_GREEN,drawingContextMain);
	setIndicatorLight(TRANSMITTER_STATUS_LED,LED_DARK_RED,drawingContextMain);

	m_calToneNoLockOff->SetCheck(BST_UNCHECKED);
	m_calToneNoLockOn->SetCheck(BST_UNCHECKED);
	m_monoOn->SetCheck(BST_UNCHECKED);
	m_stereoOn->SetCheck(BST_UNCHECKED);
	
	m_squelchOn.SetCheck(BST_UNCHECKED);
//	m_squelchOff->SetCheck(BST_UNCHECKED);
	m_declick.SetCheck(BST_UNCHECKED);

}

void CMainDlg::enableSetOperCmdButtons(int trueOrFalse) {
	CButton *x=(CButton*) GetDlgItem(IDC_POWER);
	x->EnableWindow(trueOrFalse);
	x=(CButton*) GetDlgItem(IDC_CHANNELSWINBUTTON);
	x->EnableWindow(trueOrFalse);
	x=(CButton*) GetDlgItem(IDC_SCANWINBUTTON);
	x->EnableWindow(trueOrFalse);
	x=(CButton*) GetDlgItem(IDC_STINGER_OFF);
	x->EnableWindow(trueOrFalse);
	x=(CButton*) GetDlgItem(IDC_STINGER_ON);
	x->EnableWindow(trueOrFalse);
/*
	CMenu *y;
	y=(CMenu*) GetDlgItem(IDR_MENU2);
	y->EnableMenuItem(ID_WINDOWS_SCAN,trueOrFalse);
	y=(CMenu*) GetDlgItem(ID_WINDOWS_CHANNELS);
	y->EnableMenuItem(ID_WINDOWS_CHANNELS,trueOrFalse);
	*/
	if (playbackWinFlag==1) {
		x=(CButton*) GetDlgItem(IDC_PLAYBACK_START);
		x->EnableWindow(trueOrFalse);
		x=(CButton*) GetDlgItem(IDC_PLAYBACK_STOP);
		x->EnableWindow(trueOrFalse);
	}

	if (stealthRecordWindowMode==1 && trueOrFalse==FALSE) {
		setIndicatorLight(STREC_RECORD_STATUS_LED,LED_DARK_RED,drawingContextMain);
		setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
		setIndicatorLight(REC_CARD_PRESENT_LED,LED_DARK_GREEN,drawingContextMain);
//		setIndicatorLight(STREC_PLAY_STATUS_LED,LED_DARK_RED,drawingContextMain);
//		setIndicatorLight(STREC_LIVE_STATUS_LED,LED_DARK_RED,drawingContextMain);
	}


	//	m_rightAudio.EnableWindow(trueOrFalse);
//	m_leftAudio.EnableWindow(trueOrFalse);
//	m_antennaA.EnableWindow(trueOrFalse);
//	m_antennaB.EnableWindow(trueOrFalse);
}

void CMainDlg::OnLbnSelchangeFilename()
{
	// TODO: Add your control notification handler code here
}

void CMainDlg::OnLbnSelchangeVoltageReadoutText()
{
	// TODO: Add your control notification handler code here
}

void CMainDlg::OnEnChangeFreqValText()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMainDlg::OnBnClickedTransmitterFm()
{
	txStatusSet();
}

void CMainDlg::OnBnClickedTransmitterFmenc()
{
	txStatusSet();
}

void CMainDlg::OnBnClickedTransmitterDst()
{
	txStatusSet();
}

void CMainDlg::OnNMCustomdrawLeftaudio(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMainDlg::OnNMCustomdrawAntennaa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMainDlg::OnBnClickedUseUsb()
{
	m_useUSB->SetCheck(BST_CHECKED);
	m_useCOM->SetCheck(BST_UNCHECKED);
//	setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) {
//		outputStingerCmd(STINGER_TX_SPECIFIC);
//	}
}

void CMainDlg::OnBnClickedUseCom()
{
	m_useUSB->SetCheck(BST_UNCHECKED);
	m_useCOM->SetCheck(BST_CHECKED);
}

void CMainDlg::OnBnClickedTxRestoreDefault()
{
// restore CT-48 to default settings
	outMsgStr[0]=CMD_DEFAULT_STATE_SET_1; //"cz" command
	outMsgStr[1]=CMD_DEFAULT_STATE_SET_2; // "cz" command
	writeCmd(CMD_DEFAULT_STATE_SET_LEN);
}


/*void CMainDlg::OnOptionsRestoredefaultsettings()
{
	outMsgStr[0]=CMD_DEFAULT_STATE_SET_1; //"cz" command
	outMsgStr[1]=CMD_DEFAULT_STATE_SET_2; // "cz" command
	writeCmd(CMD_DEFAULT_STATE_SET_LEN);
}
*/
void CMainDlg::OnNMCustomdrawRammemusedbargraph(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMainDlg::OnLbnSelchangeSdmemtotal()
{
	// TODO: Add your control notification handler code here
}

CDialog *pAboutDlg;
void CMainDlg::OnSettingsAbout() {

	if (aboutWinFlag==0) {
		pAboutDlg = new CAboutDlg();
		BOOL ret=pAboutDlg->Create(IDD_ABOUTBOX,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating About dialog");
	    pAboutDlg->ShowWindow(SW_SHOW);
		aboutWinFlag=1;
	}


//	CAboutDlg dlgAbout;
//	dlgAbout.DoModal();
}

extern HINSTANCE videoLanInstance;
extern char audioPlayerPathStr[];
extern CString ipAddress;
extern int audioPort;
extern CString audioPath;

void CMainDlg::OnSettingsPlayAudio() {
	int x=3; // just a place to break
//	videoLanInstance=ShellExecute(NULL, "open", "C:\\Progra~1\\VideoLAN\\VLC\\VLC", "http://10.30.30.11:9004/lb3", NULL, SW_SHOWNORMAL);
	char completeAudioPath[200];
	char tempString[10];
	completeAudioPath[0]=0;
	sprintf(completeAudioPath,"http://");
	strcat(completeAudioPath,ipAddress);
	sprintf(tempString,":%d",audioPort);
	strcat(completeAudioPath,tempString);
	strcat(completeAudioPath,audioPath);
	videoLanInstance=ShellExecute(NULL, "open", audioPlayerPathStr, completeAudioPath, NULL, SW_SHOWNORMAL);
	x=4; // another place to break
}

void CMainDlg::OnBnClickedDbmMode() {
	UINT state = myMenu.GetMenuState(ID_DB_USEDBM, MF_BYCOMMAND);
	ASSERT(state != 0xFFFFFFFF);
	if (state & MF_CHECKED) {
		dbmMode=0;
		myMenu.CheckMenuItem(ID_DB_USEDBM, MF_UNCHECKED | MF_BYCOMMAND);
	} else {
		dbmMode=1;
		myMenu.CheckMenuItem(ID_DB_USEDBM, MF_CHECKED | MF_BYCOMMAND);
	}
	CMainDlg::saveConfigToFile();
}

int settingsComWinFlag=0;

void CMainDlg::OnSettingsCom() {
	if (settingsComWinFlag==0) {
//create the settings com window.
		settingsComWinFlag=1;
		pSettingsComDlg = new CSettingsComDlg(this);
		CStatic x;
		BOOL ret=pSettingsComDlg->Create(IDD_SETTINGS_COM,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating Dialog");
        pSettingsComDlg->ShowWindow(SW_SHOW);
	}
}

void CMainDlg::OnMiscFullscaletone() {
	UINT state = myMenu.GetMenuState(ID_MISC_FULLSCALETONE, MF_BYCOMMAND);
	ASSERT(state != 0xFFFFFFFF);
	if (state & MF_CHECKED) {
		if (powerOn) {
			calToneMode&=~1; // Clear cal tone mode
			setFreqOperCmd();
		}
		myMenu.CheckMenuItem(ID_MISC_FULLSCALETONE, MF_UNCHECKED | MF_BYCOMMAND);
	} else {
		if (powerOn) {
			int x=AfxMessageBox("Warning: Tone Loud! Reduce Volume",MB_OKCANCEL);
			if (x==IDOK) {
				calToneMode|=1; // OR in bit 1
				setFreqOperCmd();
			}
		}
		myMenu.CheckMenuItem(ID_MISC_FULLSCALETONE, MF_CHECKED | MF_BYCOMMAND);
	}
}

extern int comPortNumber;
extern CMenu myMenu;
extern int comPortBaud;
int	useXYLedCal;
int controlTxModeDefault;
int controlTxDefaultIDCount;
int controlTxDefaultID[10];
//long int stingerAddress;
int stingerAddressIndex;
int stingerTxPowerLevel;
CString ipAddress;
int telnetPort;
int audioPort;
CString audioPath;
int portType=0;
extern char audioPlayerPathStr[];


void CMainDlg::restoreConfigFromFile() {

	int intVal;
	char tempString[200];
	FILE *fp=fopen("scorpion.cfg","r");
	int i;
	if (fp!=0) {
		intVal=0;
		fscanf(fp," %d",&intVal); // Look for dBm mode setting
		if (intVal==1) {
//			m_dBmMode->SetCheck(BST_CHECKED);
			dbmMode=1;
			myMenu.CheckMenuItem(ID_DB_USEDBM, MF_CHECKED | MF_BYCOMMAND);
		} else {
//			m_dBmMode->SetCheck(BST_UNCHECKED);
			dbmMode=0;
			myMenu.CheckMenuItem(ID_DB_USEDBM, MF_UNCHECKED | MF_BYCOMMAND);
		}
		fscanf(fp," %d",&comPortNumber); // Look for com port #
		if (comPortNumber>MAX_COM_PORT_NUMBER-1) comPortNumber=MAX_COM_PORT_NUMBER-1; // com port number is in range 0 to (MAX_COM_PORT_NUMBER-1)
		if (comPortNumber<0) comPortNumber=0;
		fscanf(fp," %d",&comPortBaud); // Look for baud # (0=9600, 1=300)
		if (comPortBaud>3) comPortBaud=1;
		if (comPortBaud<0) comPortBaud=0;
		fscanf(fp," %d",&useXYLedCal); // Look for LED calibration on or off setting
		if (useXYLedCal>1) useXYLedCal=1;
		if (useXYLedCal<0) useXYLedCal=0;
		fscanf(fp," %d",&controlTxModeDefault); // Look for Default setting for Control TX mode (i.e., mono l, mono r, stereo)
		if (controlTxModeDefault<0) controlTxModeDefault=0;
		if (controlTxModeDefault>2) controlTxModeDefault=2;
		fscanf(fp," %d",&controlTxDefaultIDCount); // Look for number of default control TX IDs
		if (controlTxDefaultIDCount<0) controlTxDefaultIDCount=0;
		if (controlTxDefaultIDCount>100) controlTxDefaultIDCount=100; // maximum of 100
		for (i=0;i<controlTxDefaultIDCount;i++) {
			fscanf(fp," %d",&controlTxDefaultID[i]); // Look for number of default control TX IDs
			if (controlTxDefaultID[i]<0) controlTxDefaultID[i]=0;
			if (controlTxDefaultID[i]>999) controlTxDefaultID[i]=999;
		}
		fscanf(fp," %d",&stingerAddressIndex);
		if (stingerAddressIndex<0) stingerAddressIndex=0;
		if (stingerAddressIndex>controlTxDefaultIDCount) stingerAddressIndex=controlTxDefaultIDCount;
		fscanf(fp," %d",&stingerTxPowerLevel);
		if (stingerTxPowerLevel<0) stingerTxPowerLevel=0;
		if (stingerTxPowerLevel>1) stingerTxPowerLevel=1;
		fscanf(fp,"%s\n",tempString);
		ipAddress=tempString;
		fscanf(fp,"%d",&telnetPort);
		fscanf(fp,"%d",&audioPort);
		fscanf(fp,"%s\n",tempString);
		audioPath=tempString;
		fscanf(fp,"%d\n",&portType);
		if (portType!=PORT_TYPE_RS232 && portType!=PORT_TYPE_TCPIP) {
			portType=PORT_TYPE_RS232;
		}
		if (fgets(tempString,198,fp)==0) {
			strcpy(audioPlayerPathStr,"wmplayer.exe");
		} else {
			int i=0;
			while (tempString[i]!=0 && tempString[i]!=0x0a) {
				audioPlayerPathStr[i]=tempString[i];
				i++;
			}
			audioPlayerPathStr[i]=0;
		}
		fscanf(fp,"%d\n",&DPI_setting);
		if (DPI_setting!=0 && DPI_setting!=1) {
			DPI_setting=0;
		}

		fclose(fp);

	} else { // if file doesn'e exist, make it
		dbmMode=0;
		comPortNumber=0;
		comPortBaud=0;
		useXYLedCal=0;
		controlTxModeDefault=0;
		controlTxDefaultIDCount=0;
		stingerAddressIndex=0;
		stingerTxPowerLevel=0;
		ipAddress="0.0.0.0";
		telnetPort=23;
		audioPort=88;
		audioPath="/lb3";
		portType=PORT_TYPE_RS232; 
		strcpy(audioPlayerPathStr,"wmplayer.exe");
		saveConfigToFile();
	}
}

void CMainDlg::saveConfigToFile() {
	int intVal;
	int i;
	FILE *fp=fopen("scorpion.cfg","w");
	if (fp!=0) {
		fprintf(fp,"%d\n",dbmMode);
		fprintf(fp,"%d\n",comPortNumber);
		fprintf(fp,"%d\n",comPortBaud);
		fprintf(fp,"%d\n",useXYLedCal);
		fprintf(fp,"%d\n",controlTxModeDefault);
		fprintf(fp,"%d\n",controlTxDefaultIDCount);
		for (i=0;i<controlTxDefaultIDCount;i++) {
			fprintf(fp,"%d\n",controlTxDefaultID[i]);
		}
		fprintf(fp,"%d\n",stingerAddressIndex);
		fprintf(fp,"%d\n",stingerTxPowerLevel);
		fprintf(fp,"%s\n",ipAddress);
		fprintf(fp,"%d\n",telnetPort);
		fprintf(fp,"%d\n",audioPort);
		fprintf(fp,"%s\n",audioPath);
		fprintf(fp,"%d\n",portType);
		fprintf(fp,"%s\n",audioPlayerPathStr);
		fprintf(fp,"%d\n",DPI_setting);
	}
	fclose(fp);
}


void CMainDlg::OnBnClickedRxPower() 
{
//	int i,j;
//	int x=AfxMessageBox("Do you want to reset RD-1000?",MB_OKCANCEL);
//	if (x==IDOK) {
	powerOn=TRUE;
	setFreqOperCmd(); 
	powerOn=FALSE;
	setFreqOperCmd(); 
	powerOn=TRUE;
}


HINSTANCE videoLanInstance;
void CMainDlg::OnBnClickedLocalRec()
{
	CString s;
	char tempString[10];

	sprintf(tempString,":%d",audioPort);
	s=ipAddress;
	s+=tempString;
	s+=audioPath;

//	videoLanInstance=ShellExecute(NULL, "open", "C:\\Progra~1\\VideoLAN\\VLC\\VLC", s, NULL, SW_SHOWNORMAL);
	videoLanInstance=ShellExecute(NULL, "open", "C:\\Progra~1\\VideoLAN\\VLC\\VLC", NULL, NULL, SW_SHOWNORMAL);
//	ShellExecute(NULL, "open", "C:\Program Files\VideoLAN\VLC\VLC", NULL, NULL, SW_SHOWNORMAL);
	int y=23; // just a place to break
	switch((int)videoLanInstance) {
		case 0:
			s="The operating system is out of memory or resources.";
			break;
		case ERROR_FILE_NOT_FOUND:
			s="The specified file was not found.";
			break;
		case ERROR_PATH_NOT_FOUND:
			s="The specified path was not found.";
			break;
		case ERROR_BAD_FORMAT:
			s="The .exe file is invalid (non-Win32 .exe or error in .exe image).";
			break;
		case SE_ERR_ACCESSDENIED:
			s="The operating system denied access to the specified file.";
			break;
		case SE_ERR_ASSOCINCOMPLETE:
			s="The file name association is incomplete or invalid.";
			break;
		case SE_ERR_DDEBUSY:
			s="The DDE transaction could not be completed because other DDE transactions were being processed.";
			break;
		case SE_ERR_DDEFAIL:
			s="The DDE transaction failed.";
			break;
		case SE_ERR_DDETIMEOUT:
			s="The DDE transaction could not be completed because the request timed out.";
			break;
		case SE_ERR_DLLNOTFOUND:
			s="The specified DLL was not found.";
			break;
//		case SE_ERR_FNF:
//			s="The specified file was not found.";
//			break;
		case SE_ERR_NOASSOC:
			s="There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.";
			break;
		case SE_ERR_OOM:
			s="There was not enough memory to complete the operation.";
			break;
//		case SE_ERR_PNF:
//			s="The specified path was not found.";
//			break;
		case SE_ERR_SHARE:
			s="A sharing violation occurred.";
			break;
	}
}

void CAboutDlg::OnBnClickedOk()
{
	aboutWinFlag=0;
	OnOK();
}

void CMainDlg::OnWindowsRemoteplayer()
{
	OnBnClickedLocalRec();
}

void CMainDlg::OnWindowsChannels()
{
	OnBnClickedchannelswindow();
}

void CMainDlg::OnWindowsScan()
{
	OnBnClickedscanwindow();
}

void CMainDlg::OnStnClickedStMsgRcvdCount()
{
	// TODO: Add your control notification handler code here
}

void CMainDlg::OnNMCustomdrawSdmemusedbargraph(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMainDlg::OnLbnSelchangeSerialNum()
{
	// TODO: Add your control notification handler code here
}


void CMainDlg::OnBnClickedCtlTxPwrLow()
{
	controlTxPower=0;
}

void CMainDlg::OnBnClickedCtlTxPwrHi()
{
	controlTxPower=1;
}

void CMainDlg::OnBnClickedSleeper2PwrHi()
{
	sleeper2Power=1;
}

void CMainDlg::OnBnClickedSleeper2PwrLow()
{
	sleeper2Power=0;
}

void CMainDlg::OnBnClickedPlaybackwinbutton()
{

	desiredPlaybackMode=1;
	startPlayingFlag=1;
	resendPlaybackCommandCounter=0;
	playbackStartCmd();

}


void CMainDlg::OnLbnSelchangeSdErrorText()
{
	// TODO: Add your control notification handler code here
}

void CMainDlg::OnBnClickedRecordmode()
{
	if (m_recordmode->GetCheck()==BST_CHECKED) {
		m_recordmode->SetCheck(BST_UNCHECKED);
	} else {
		m_recordmode->SetCheck(BST_CHECKED);
	}
	recordModeSetCmd();
}

void CMainDlg::OnBnClickedOverwriteWhenFull()
{
	if (m_overwriteWhenFull->GetCheck()==BST_CHECKED) {
		m_overwriteWhenFull->SetCheck(BST_UNCHECKED);
	} else {
		m_overwriteWhenFull->SetCheck(BST_CHECKED);
	}
	recordModeSetCmd();
}

void CMainDlg::OnBnClickedCtrlTxStereo()
{
    CButton *m_temp;
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_STEREO);
	m_temp->SetCheck(BST_CHECKED);
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_L);
	m_temp->SetCheck(BST_UNCHECKED);
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_R);
	m_temp->SetCheck(BST_UNCHECKED);
	ctrlTxMode=0;
}

void CMainDlg::OnBnClickedCtrlTxMonoL()
{
    CButton *m_temp;
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_STEREO);
	m_temp->SetCheck(BST_UNCHECKED);
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_L);
	m_temp->SetCheck(BST_CHECKED);
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_R);
	m_temp->SetCheck(BST_UNCHECKED);
	ctrlTxMode=1;
}

void CMainDlg::OnBnClickedCtrlTxMonoR()
{
    CButton *m_temp;
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_STEREO);
	m_temp->SetCheck(BST_UNCHECKED);
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_L);
	m_temp->SetCheck(BST_UNCHECKED);
	m_temp=(CButton*)GetDlgItem(IDC_CTRL_TX_MONO_R);
	m_temp->SetCheck(BST_CHECKED);
	ctrlTxMode=2;
}

void CMainDlg::OnBnClickedOffState()
{
	OnBnClickedStingerOff();
}

void CMainDlg::OnBnClickedOnState()
{
	OnBnClickedStingerOn();
}

extern int currentAddressIndex;

void CMainDlg::OnAddresslistDeletecurrentaddress()
{
	CString strVal;
	int n;

	m_controlTxAddress->GetWindowTextA(strVal);
	n=m_controlTxAddress->FindStringExact(-1,strVal); // see if this address has been entered already
	m_controlTxAddress->DeleteString(n);
	if (n=currentAddressIndex) {
		currentAddressIndex--;
	}
	writeStingerCmdFile(); // update file
}

void CMainDlg::OnAddresslistDeletealladdresses()
{
	int n;

	currentAddressIndex=0;
	m_controlTxAddress->ResetContent();
	writeStingerCmdFile(); // update file
}

void CMainDlg::OnBnClickedPlaybackModeLive()
{

	m_playbackMsg->SetWindowTextA("Ending playback...");
	desiredPlaybackMode=3;
	endPlaybackFlag=1;
	CMainDlg::playbackStartCmd();
}

void CMainDlg::OnBnClickedPlaybackStop()
{
	desiredPlaybackMode=3;
	stopPlaybackFlag=1;
	m_playbackMsg->SetWindowTextA("Stopping playback...");
	CMainDlg::playbackStartCmd();
}

void CMainDlg::OnBnClickedPlaybackStart()
{
	desiredPlaybackMode=2;
	startPlayingFlag=1;
	m_playbackMsg->SetWindowTextA("Starting playback...");

	CTime tempPlaybackTime;
	pPlaybackTime->GetTime(tempPlaybackTime);

	TIME_REC_STRUCT playbackTimeDate;
	playbackTimeDate.dateYear=tempPlaybackTime.GetYear()-2000;
	playbackTimeDate.dateMonth=tempPlaybackTime.GetMonth();
	playbackTimeDate.dateDay=tempPlaybackTime.GetDay();
	playbackTimeDate.timeHour=tempPlaybackTime.GetHour();
	playbackTimeDate.timeMinute=tempPlaybackTime.GetMinute();
	playbackTimeDate.timeSecond=tempPlaybackTime.GetSecond();

	timeToJulian(&playbackTimeDate,&playbackJulianVal);

	CMainDlg::playbackStartCmd();
}

void CMainDlg::OnStnClickedCardPresentMsg()
{
	// TODO: Add your control notification handler code here
}


void CMainDlg::OnStnClickedRecordStatusMsg()
{
	// TODO: Add your control notification handler code here
}

void CMainDlg::OnLbnSelchangeRecFileNumText()
{
	int x=1; // just a place to break
}

CString playFileString;
extern char specialStingerStrVal[];
extern char specialStingerCmdChar;

void writeStealthRecStatusFile();

void CMainDlg::OnLbnDblclkRecFileNumText()
{

	OnStealthRecPlay();

}

void CMainDlg::OnLbnSetfocusRecFileNumText()
{
	int x=1; // TODO: Add your control notification handler code here
}

void CMainDlg::OnLbnKillfocusRecFileNumText()
{
	int x=1; // TODO: Add your control notification handler code here
}

void CMainDlg::OnBnClickedDpi96()
{
	// TODO: Add your control notification handler code here
}
