#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
#include "cStingerDlg.h"
#include "msg_defs.h"
#include "led_defs.h"
#include "sys_clk.h"
#include "CDogLeashView.h"
#include "CStingerRecCmdDlg.h"
#include "config.h"

long unsigned stingerAddress=0x006;
extern CDC* drawingContextStinger;

CStingerDlg::CStingerDlg(CWnd* pParent /*=NULL*/) : CDialog(CStingerDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

//Global variables for stinger stuff
CComboBox *m_stingerAddress;
CComboBox *m_offLine1;
CComboBox *m_onLine1;
CComboBox *m_offLine2;
CComboBox *m_onLine2;
CComboBox *m_offLine3;
CComboBox *m_onLine3;
CComboBox *m_offLine4;
CComboBox *m_onLine4;
CComboBox *m_offLine5;
CComboBox *m_onLine5;
CComboBox *m_offLine6;
CComboBox *m_onLine6;
CComboBox *m_offLine7;
CComboBox *m_onLine7;
CButton *m_onCmd;
CButton *m_offCmd;
CButton *m_onCmdButton;
CButton *m_offCmdButton;
CButton *m_autoOnEnable;
CButton *m_dogLeashEnable;
CDateTimeCtrl *m_autoOnPeriod;
CComboBox *m_autoOnDelayDays;
CDateTimeCtrl *m_autoOnDelayHrsMins;
CDateTimeCtrl *m_dogLeashHrsMins;
CComboBox *m_dogLeashDays;
CDateTimeCtrl *m_autoOnRepeatHrsMins;
CComboBox *m_autoOnRepeatDays;
CSetSysClkDlg *pSetSysClkDlg=(CSetSysClkDlg*)0;
CButton *m_stingerRecord;
//CDogleashCmdDlg *pDogleashWinDlg=(CDogleashCmdDlg*)0;
extern int stingerOnFlag;
int stingerWinFlag;

BOOL CStingerDlg::OnInitDialog() {
	CString strVal;
	int n;
	CTime x;

// Set up drawing context
	drawingContextStinger=GetDC();

// Set up pointers to buttons, combo boxes
//	m_stingerAddress=(CComboBox*)GetDlgItem(IDC_STINGER_ADDRESS);
	m_offLine1=(CComboBox*)GetDlgItem(IDC_WASP_OFF_LINE1);
	m_onLine1=(CComboBox*)GetDlgItem(IDC_WASP_ON_LINE1);
	m_offLine2=(CComboBox*)GetDlgItem(IDC_WASP_OFF_LINE2);
	m_onLine2=(CComboBox*)GetDlgItem(IDC_WASP_ON_LINE2);
	m_offLine3=(CComboBox*)GetDlgItem(IDC_WASP_OFF_LINE3);
	m_onLine3=(CComboBox*)GetDlgItem(IDC_WASP_ON_LINE3);
	m_offLine4=(CComboBox*)GetDlgItem(IDC_WASP_OFF_LINE4);
	m_onLine4=(CComboBox*)GetDlgItem(IDC_WASP_ON_LINE4);
	m_offLine5=(CComboBox*)GetDlgItem(IDC_WASP_OFF_LINE5);
	m_onLine5=(CComboBox*)GetDlgItem(IDC_WASP_ON_LINE5);
	m_offLine6=(CComboBox*)GetDlgItem(IDC_WASP_OFF_LINE6);
	m_onLine6=(CComboBox*)GetDlgItem(IDC_WASP_ON_LINE6);
	m_offLine7=(CComboBox*)GetDlgItem(IDC_WASP_OFF_LINE7);
	m_onLine7=(CComboBox*)GetDlgItem(IDC_WASP_ON_LINE7);

// Set pointers to "On" and "Off" radio buttons
	m_offCmd=(CButton*)GetDlgItem(IDC_WASP_OFF_RADIOBUTTON);
	m_onCmd=(CButton*)GetDlgItem(IDC_WASP_ON_RADIOBUTTON);
	m_offCmdButton=(CButton*)GetDlgItem(IDC_WASP_OFF_BUTTON);
	m_onCmdButton=(CButton*)GetDlgItem(IDC_WASP_ON_BUTTON);


// Set "On" or "Off" radion buttons to current stinger setting
	if (stingerOnFlag==TRUE) {
		m_onCmd->SetCheck(BST_CHECKED);
		m_offCmd->SetCheck(BST_UNCHECKED);
	} else {
		m_onCmd->SetCheck(BST_UNCHECKED);
		m_offCmd->SetCheck(BST_CHECKED);
	}

// Set up selections for on and off positions for all seven switches
	n=m_offLine1->AddString("Ground");
	n=m_offLine1->AddString("Battery");
	n=m_offLine1->AddString("Logic Low");
	n=m_offLine1->AddString("Open");
	n=m_onLine1->AddString("Ground");
	n=m_onLine1->AddString("Battery");
	n=m_onLine1->AddString("Logic Low");
	n=m_onLine1->AddString("Open");
	n=m_offLine2->AddString("Ground");
	n=m_offLine2->AddString("Battery");
	n=m_offLine2->AddString("Logic Low");
	n=m_offLine2->AddString("Open");
	n=m_onLine2->AddString("Ground");
	n=m_onLine2->AddString("Battery");
	n=m_onLine2->AddString("Logic Low");
	n=m_onLine2->AddString("Open");
	n=m_offLine3->AddString("Ground");
	n=m_offLine3->AddString("Battery");
	n=m_offLine3->AddString("Logic Low");
	n=m_offLine3->AddString("Logic High");
	n=m_offLine3->AddString("Input");
	n=m_onLine3->AddString("Ground");
	n=m_onLine3->AddString("Battery");
	n=m_onLine3->AddString("Logic Low");
	n=m_onLine3->AddString("Logic High");
	n=m_onLine3->AddString("Input");
	n=m_offLine4->AddString("Ground");
	n=m_offLine4->AddString("Battery");
	n=m_offLine4->AddString("Logic Low");
	n=m_offLine4->AddString("Logic High");
	n=m_offLine4->AddString("Input");
	n=m_onLine4->AddString("Ground");
	n=m_onLine4->AddString("Battery");
	n=m_onLine4->AddString("Logic Low");
	n=m_onLine4->AddString("Logic High");
	n=m_onLine4->AddString("Input");
	n=m_offLine5->AddString("Ground");
	n=m_offLine5->AddString("Logic Low");
	n=m_offLine5->AddString("Logic High");
	n=m_offLine5->AddString("Input");
	n=m_onLine5->AddString("Ground");
	n=m_onLine5->AddString("Logic Low");
	n=m_onLine5->AddString("Logic High");
	n=m_onLine5->AddString("Input");
	n=m_offLine6->AddString("Ground");
	n=m_offLine6->AddString("Battery");
	n=m_offLine6->AddString("Logic Low");
	n=m_offLine6->AddString("Logic High");
	n=m_offLine6->AddString("Input");
	n=m_onLine6->AddString("Ground");
	n=m_onLine6->AddString("Battery");
	n=m_onLine6->AddString("Logic Low");
	n=m_onLine6->AddString("Logic High");
	n=m_onLine6->AddString("Input");
//	n=m_offLine7->AddString("Ground");
//	n=m_offLine7->AddString("Logic Low");
//	n=m_offLine7->AddString("Logic High");
//	n=m_offLine7->AddString("Battery");
	n=m_offLine7->AddString("Input");
//	n=m_onLine7->AddString("Ground");
//	n=m_onLine7->AddString("Logic Low");
//	n=m_onLine7->AddString("Logic High");
//	n=m_onLine7->AddString("Battery");
	n=m_onLine7->AddString("Input");

// Set default selection settings
	m_offLine1->SetCurSel(0);
	m_onLine1->SetCurSel(3);
	m_offLine2->SetCurSel(0);
	m_onLine2->SetCurSel(3);
	m_offLine3->SetCurSel(0);
	m_onLine3->SetCurSel(3);
	m_offLine4->SetCurSel(0);
	m_onLine4->SetCurSel(3);
	m_offLine5->SetCurSel(0);
	m_onLine5->SetCurSel(3);
	m_offLine6->SetCurSel(0);
	m_onLine6->SetCurSel(3);
	m_offLine7->SetCurSel(0);
	m_onLine7->SetCurSel(0);

/*
// Initialize address display
	m_stingerAddress->ResetContent();
	// Set default stinger address
	if (stingerAddress<0x00f) {
		strVal.Format("00%1lx",stingerAddress);
	} else if (stingerAddress<0x0ff) {
		strVal.Format("0%2lx",stingerAddress);
	} else  {
		strVal.Format("%3lx",stingerAddress);
	}
	m_stingerAddress->SetWindowText(strVal);  //set edit section to what string ended up as
	m_stingerAddress->AddString(strVal); // add address to list
	strVal.ReleaseBuffer();
*/

// Set auto-on enable check to unchecked
	m_autoOnEnable=(CButton*)GetDlgItem(IDC_AUTO_ON_ENABLE);
	m_autoOnEnable->SetCheck(BST_UNCHECKED);

// Set dog leash enable check to unchecked
	m_dogLeashEnable=(CButton*)GetDlgItem(IDC_DOGLEASH_ENABLE);
	m_dogLeashEnable->SetCheck(BST_UNCHECKED);
	m_dogLeashEnable->EnableWindow(FALSE);

// Set auto on period to default value "1:00"
	m_autoOnPeriod=(CDateTimeCtrl*)GetDlgItem(IDC_WASP_AUTO_ON_PERIOD);
	m_autoOnPeriod->SetFormat(_T("HH:mm"));
    x=CTime(2007,1,1,1,0,0,-1); // Set time to 1/1/2007 at 1:00AM (only the 1:00 part will show)
	m_autoOnPeriod->SetTime(&x);

// Set auto on delay hrs:mins to default value "0:00"
	m_autoOnDelayHrsMins=(CDateTimeCtrl*)GetDlgItem(IDC_WASP_AUTO_ON_DELAY_HRS_MINS);
	m_autoOnDelayHrsMins->SetFormat(_T("HH:mm"));
	x=CTime(2007,1,1,0,0,0,-1); // Set time to 1/1/2007 at 0:00AM (only the 0:00 part will show)
	m_autoOnDelayHrsMins->SetTime(&x);

// Set auto on delay days to default value
	m_autoOnDelayDays=(CComboBox*)GetDlgItem(IDC_WASP_AUTO_ON_DELAY_DAYS);
	for (n=0;n<40;n++) {
		strVal.Format("%d",n);
		m_autoOnDelayDays->AddString(strVal);
	}
	m_autoOnDelayDays->SetCurSel(0);

// Set auto on repeat days to default value
	m_autoOnRepeatDays=(CComboBox*)GetDlgItem(IDC_WASP_AUTO_ON_REPEAT_DAYS);
	for (n=0;n<40;n++) {
		strVal.Format("%d",n);
		m_autoOnRepeatDays->AddString(strVal);
	}
	m_autoOnRepeatDays->SetCurSel(0);

// Set auto on repeat hrs:mins to default value "0:00"
	m_autoOnRepeatHrsMins=(CDateTimeCtrl*)GetDlgItem(IDC_WASP_AUTO_ON_REPEAT_HRS_MINS);
	m_autoOnRepeatHrsMins->SetFormat(_T("HH:mm"));
	x=CTime(2007,1,1,0,0,0,-1); // Set time to 1/1/2007 at 0:00AM (only the 0:00 part will show)
	m_autoOnRepeatHrsMins->SetTime(&x);

// Set dog leash days to default value
	m_dogLeashDays=(CComboBox*)GetDlgItem(IDC_WASP_DOGLEASH_DAYS);
	for (n=0;n<40;n++) {
		strVal.Format("%d",n);
		m_dogLeashDays->AddString(strVal);
	}
	m_dogLeashDays->SetCurSel(0);
	m_dogLeashDays->EnableWindow(FALSE);

// Set dog leash hrs:mins to default value "0:00"
	m_dogLeashHrsMins=(CDateTimeCtrl*)GetDlgItem(IDC_WASP_DOGLEASH_HRS_MINS);
	m_dogLeashHrsMins->SetFormat(_T("HH:mm"));
	x=CTime(2007,1,1,0,0,0,-1); // Set time to 1/1/2007 at 0:00AM (only the 0:00 part will show)
	m_dogLeashHrsMins->SetTime(&x);
	m_dogLeashHrsMins->EnableWindow(FALSE);

/*
// Set default stinger address
	if (stingerAddress<0x00f) {
		strVal.Format("00%1lx",stingerAddress);
	} else if (stingerAddress<0x0ff) {
		strVal.Format("0%2lx",stingerAddress);
	} else  {
		strVal.Format("%3lx",stingerAddress);
	}
//	m_stingerAddress->SetWindowText(strVal);  //set edit section to what string ended up as
	m_stingerAddress->AddString(strVal); // add address to list
*/
	strVal.ReleaseBuffer();

//
	m_stingerRecord=(CButton*)GetDlgItem(IDC_WASP_RECORD);
//	m_stingerRecorded=(CButton*)GetDlgItem(IDC_STINGER_RECORDED);

// Disable auto-on stuff since box is not set
	m_autoOnDelayDays->EnableWindow(FALSE);
	m_autoOnDelayHrsMins->EnableWindow(FALSE);
	m_autoOnPeriod->EnableWindow(FALSE);
	m_autoOnRepeatDays->EnableWindow(FALSE);
	m_autoOnRepeatHrsMins->EnableWindow(FALSE);

// Initialize settings from configuration file
	stingerWinFlag=1;
//	readStingerCmdFile();



	return TRUE;
}


void CStingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStingerDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_MARK_PATTEN, &CStingerDlg::OnMarkPatten)
ON_WM_SYSCOMMAND()
ON_WM_CLOSE()
ON_WM_PAINT()
//xyz:ON_WM_TIMER()
//xyz:ON_CBN_SELCHANGE(IDC_ON_LINE1, &CStingerDlg::OnCbnSelchangeCombo5)
//	ON_CBN_EDITCHANGE(IDC_STINGER_ADDRESS, &CStingerDlg::OnCbnEditchangeStingerAddress)
//	ON_CBN_SELCHANGE(IDC_STINGER_ADDRESS, &CStingerDlg::OnCbnSelchangeStingerAddress)
//	ON_BN_CLICKED(IDC_ENTER_ADDRESS, &CStingerDlg::OnBnClickedEnterAddress)
//xyz:ON_BN_CLICKED(IDC_STINGERBUTTON3, &CStingerDlg::OnBnClickedAddressDelete)
	ON_BN_CLICKED(IDC_WASP_OFF_RADIOBUTTON, &CStingerDlg::OnBnClickedOffCmd)
	ON_BN_CLICKED(IDC_WASP_ON_RADIOBUTTON, &CStingerDlg::OnBnClickedOnCmd)
	ON_BN_CLICKED(IDC_AUTO_ON_ENABLE, &CStingerDlg::OnBnClickedAutoOnEnable)
	ON_BN_CLICKED(IDC_WASP_ON_BUTTON, &CStingerDlg::OnBnClickedStingerOn)
	ON_BN_CLICKED(IDC_WASP_OFF_BUTTON, &CStingerDlg::OnBnClickedStingerOff)
    ON_BN_CLICKED(IDC_WASP_RECORD, &CStingerDlg::OnBnClickedStingerRecord)
//ON_BN_CLICKED(IDC_STINGER_REC_CLEAR, &CStingerDlg::OnBnClickedStingerRecClear)
	ON_BN_CLICKED(IDC_STINGER_VIEWREC, &CStingerDlg::OnBnClickedStingerViewrec)
	ON_BN_CLICKED(IDC_DOGLEASH_ENABLE, &CStingerDlg::OnBnClickedDogleashEnable)
    ON_BN_CLICKED(IDC_WASP_DOGLEASH_VIEW, &CStingerDlg::OnBnClickedDogleashView)
//	ON_BN_CLICKED(IDC_SET_SYSTEM_CLK, &CStingerDlg::OnBnClickedSetSystemClk)
	ON_BN_CLICKED(ID_CANCEL_STINGERWIN, &CStingerDlg::OnBnClickedCancel)
//	ON_BN_CLICKED(IDC_STINGER_ADDRESS_ENTER, &CStingerDlg::OnBnClickedWaspAddressEnter)
	ON_BN_CLICKED(IDC_WASP_ADDRESS_DELETE, &CStingerDlg::OnBnClickedWaspAddressDelete)
	ON_BN_CLICKED(IDC_WASP_SET_SYSTEM_CLK, &CStingerDlg::OnBnClickedWaspSetSystemClk)
	ON_BN_CLICKED(IDC_WASP_ADDRESS_DELETEALL, &CStingerDlg::OnBnClickedWaspDeleteAllAddresses)
END_MESSAGE_MAP()

extern int stingerWinFlag;
extern CDialog *pStingerWinDlg;
extern CButton		m_stingerWinButton;

void CStingerDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	CDialog::OnSysCommand(nID, lParam);
}

void CStingerDlg::OnBnClickedCancel() {
	stingerWinFlag=0;
//	writeStingerCmdFile();
//Kill stinger window manually
	pStingerWinDlg->DestroyWindow();
//re-enable button for Channels Window
	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}

afx_msg void CStingerDlg::OnClose() {
	stingerWinFlag=0;
	m_stingerWinButton.EnableWindow(TRUE);//re-enable button for Channels Window

	CDialog::OnClose();
}



afx_msg void CStingerDlg::OnPaint() {
// 	CMainDlg::updateStingerStatusLED();
	CDialog::OnPaint();
}

void CStingerDlg::OnBnClickedDogleashEnable()
{
	int val;
	if (m_dogLeashEnable->GetCheck()==BST_CHECKED) {
		m_dogLeashDays->EnableWindow(TRUE);
		m_dogLeashHrsMins->EnableWindow(TRUE);
		m_autoOnPeriod->EnableWindow(FALSE);
		m_autoOnRepeatDays->EnableWindow(FALSE);
		m_autoOnRepeatHrsMins->EnableWindow(FALSE);
	} else {
		m_dogLeashDays->EnableWindow(FALSE);
		m_dogLeashHrsMins->EnableWindow(FALSE);
		m_autoOnPeriod->EnableWindow(TRUE);
		m_autoOnRepeatDays->EnableWindow(TRUE);
		m_autoOnRepeatHrsMins->EnableWindow(TRUE);
	}

}

void CStingerDlg::OnBnClickedAutoOnEnable() {
	if (m_autoOnEnable->GetCheck()==BST_CHECKED) {
		m_dogLeashEnable->EnableWindow(TRUE);
		m_autoOnDelayDays->EnableWindow(TRUE);
		m_autoOnDelayHrsMins->EnableWindow(TRUE);
		m_autoOnPeriod->EnableWindow(TRUE);
		m_autoOnRepeatDays->EnableWindow(TRUE);
		m_autoOnRepeatHrsMins->EnableWindow(TRUE);
	} else {
		m_dogLeashEnable->SetCheck(BST_UNCHECKED);
		m_dogLeashEnable->EnableWindow(FALSE);
		m_dogLeashDays->EnableWindow(FALSE);
		m_dogLeashHrsMins->EnableWindow(FALSE);
		m_autoOnDelayDays->EnableWindow(FALSE);
		m_autoOnDelayHrsMins->EnableWindow(FALSE);
		m_autoOnPeriod->EnableWindow(FALSE);
		m_autoOnRepeatDays->EnableWindow(FALSE);
		m_autoOnRepeatHrsMins->EnableWindow(FALSE);
	}

}

extern CDogleashCmdDlg *pDogleashWinDlg;

void CStingerDlg::OnBnClickedDogleashView() {
		pDogleashWinDlg = new CDogleashCmdDlg((CDogleashCmdDlg *)this);
		BOOL ret=pDogleashWinDlg->Create(IDD_DOGLEASHWIN,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating Dogleash Command Dialog");
        pDogleashWinDlg->ShowWindow(SW_SHOW);
}

void CStingerDlg::OnCbnEditchangeStingerAddress()
{
}

/*
void CStingerDlg::OnBnClickedWaspAddressEnter()
{
	int n;
	CString strVal;

	m_stingerAddress->GetWindowTextA(strVal);
	strVal.Insert(0,"0x");
	stingerAddress = strtol(strVal, 0, 0); //convert to long
	if (stingerAddress>0x0fff) stingerAddress=0x0fff;
	if (stingerAddress<0x00f) {
		strVal.Format("00%1lx",stingerAddress);
	} else if (stingerAddress<0x0ff) {
		strVal.Format("0%2lx",stingerAddress);
	} else  {
		strVal.Format("%3lx",stingerAddress);
	}
	m_stingerAddress->SetWindowText(strVal);  //set edit section to what string ended up as
	n=m_stingerAddress->FindStringExact(-1,strVal); // see if this address has been entered already
	if (n==CB_ERR) { // if not, add it
		n=m_stingerAddress->AddString(strVal); // add address to list
	}
	strVal.ReleaseBuffer();
}
*/

extern CComboBox *m_controlTxAddress;
extern int currentAddressIndex;
extern void writeStingerCmdFile();

void CStingerDlg::OnBnClickedWaspAddressDelete()
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


void CStingerDlg::OnCbnSelchangeStingerAddress()
{
	CString strVal;
	m_stingerAddress->GetWindowTextA(strVal);
	stingerAddress = strtol(strVal, 0, 0); //convert to long
	if (stingerAddress>0x0fff) stingerAddress=0x0fff;
}
extern int stingerStatus;

void CStingerDlg::OnBnClickedOffCmd() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
	}
}

void CStingerDlg::OnBnClickedOnCmd() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
	}
}
void CStingerDlg::OnBnClickedStingerOn() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_offCmd->SetCheck(BST_UNCHECKED);
		m_onCmd->SetCheck(BST_CHECKED);
		m_offCmdButton->SetCheck(BST_UNCHECKED);
		m_onCmdButton->SetCheck(BST_CHECKED);
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
	}
}

void CStingerDlg::OnBnClickedStingerOff() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_offCmd->SetCheck(BST_CHECKED);
		m_onCmd->SetCheck(BST_UNCHECKED);
		m_offCmdButton->SetCheck(BST_CHECKED);
		m_onCmdButton->SetCheck(BST_UNCHECKED);
/*
		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		m_onCmdButton->EnableWindow(FALSE);
		m_offCmdButton->EnableWindow(FALSE);
*/
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
	}
}


/*
void CStingerDlg::updateStingerStatusLED2() {
   if (stingerStatus==STINGER_COLLISION) { //	red if it collided
	   CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_BRIGHT_RED,this->GetDC());
   } else if (stingerStatus==STINGER_TXMITTING) { // yellow for transmitting
	   CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_YELLOW,this->GetDC());
   		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		m_onCmdButton->EnableWindow(FALSE);
		m_offCmdButton->EnableWindow(FALSE);
   } else { // Green otherwise
	   CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_GREEN,this->GetDC());
   		m_onCmd->EnableWindow(TRUE);
		m_offCmd->EnableWindow(TRUE);
		m_onCmdButton->EnableWindow(TRUE);
		m_offCmdButton->EnableWindow(TRUE);

   }
}
*/

/*
void CStingerDlg::OnBnClickedEnterAddress() {
	int n;
	CString strVal;

	m_stingerAddress->GetWindowTextA(strVal);
	stingerAddress = strtol(strVal, 0, 0); //convert to long
	if (stingerAddress>0x0fff) stingerAddress=0x0fff;
	if (stingerAddress<0x00f) {
		strVal.Format("00%1lx",stingerAddress);
	} else if (stingerAddress<0x0ff) {
		strVal.Format("0%2lx",stingerAddress);
	} else  {
		strVal.Format("%3lx",stingerAddress);
	}
	m_stingerAddress->SetWindowText(strVal);  //set edit section to what string ended up as
	n=m_stingerAddress->FindStringExact(-1,strVal); // see if this address has been entered already
	if (n==CB_ERR) { // if not, add it
		n=m_stingerAddress->AddString(strVal); // add address to list
	}
	strVal.ReleaseBuffer();
}
*/
void CStingerDlg::OnBnClickedStingerRecord() {
	if (m_stingerRecord->GetCheck()==BST_CHECKED) {
//		m_stingerRecord->SetCheck(BST_UNCHECKED);
		stingerRecordCmd(1); // The 0 indicates turn record on
	} else {
//		m_stingerRecord->SetCheck(BST_CHECKED);
		stingerRecordCmd(0); // The 1 indicates turn record off
	}
}
extern CStingerRecCmdDlg *pStingerRecWinDlg;

void CStingerDlg::OnBnClickedStingerViewrec() {
	pStingerRecWinDlg = new CStingerRecCmdDlg((CStingerRecCmdDlg *)this);
	BOOL ret=pStingerRecWinDlg->Create(IDD_STINGERRECWIN,0);
	if(!ret)   //Create failed.
    AfxMessageBox("Error creating Stinger Record Command Dialog");
	pStingerRecWinDlg->ShowWindow(SW_SHOW);
}



void CStingerDlg::OnBnClickedWaspSetSystemClk()
{
		pSetSysClkDlg = new CSetSysClkDlg((CSetSysClkDlg *)this);
		BOOL ret=pSetSysClkDlg->Create(IDD_SYSCLK_WIN,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating System Clock Set Dialog");
        pSetSysClkDlg->ShowWindow(SW_SHOW);
}
extern char outMsgStr[];
extern char inMsgParams[];


void CStingerDlg::stingerRecordCmd(int mode) { // The mode indicates turn record on or off
//	outMsgStr[0]=stingerRecordCmdStr[0]; //"dg" command
//	outMsgStr[1]=stingerRecordCmdStr[1]; // "dg" command
//	outMsgStr[2]=mode; //Indicates turn record on or off
//	CMainDlg::writeCmd(CMD_STINGER_RECORD_LEN);  //Write out DG msg of length 3

#if INTERFACE_USB==1
	CMainDlg::readResp(RESP_STINGER_RECORD_LEN);  //Read in TG msg of length 4
	if (inMsgParams[0]==0) m_stingerRecord->SetCheck(BST_UNCHECKED);
	else  m_stingerRecord->SetCheck(BST_CHECKED);
//	if (inMsgParams[1]==0) m_stingerRecorded->SetCheck(BST_UNCHECKED);
//	else m_stingerRecorded->SetCheck(BST_CHECKED);
#endif
}

void CStingerDlg::OnOK() {
}
void CStingerDlg::OnBnClickedWaspDeleteAllAddresses()
{
	int n;

	currentAddressIndex=0;
	m_controlTxAddress->ResetContent();
	writeStingerCmdFile(); // update file
}
