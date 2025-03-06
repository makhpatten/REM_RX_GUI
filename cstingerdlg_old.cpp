#include "stdafx.h"
#include "ct148.h"
#include "ct148Dlg.h"
#include "cstingerdlg.h"
#include "msg_defs.h"
#include "led_defs.h"
#include "sys_clk.h"

CStingerDlg::CStingerDlg(CWnd* pParent /*=NULL*/) : CDialog(CStingerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}
extern int stingerStatus;

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
extern unsigned long stingerAddress;
CComboBox *m_dogLeashDays;
CDateTimeCtrl *m_dogLeashHrsMins;
CComboBox *m_autoOnRepeatDays;
CDateTimeCtrl *m_autoOnRepeatHrsMins;
CButton *m_stingerRecord;
//CButton *m_stingerRecorded;

extern CDC *drawingContextStinger;
BOOL CStingerDlg::OnInitDialog() {
	return(TRUE);
	int n;
	CString strVal;
	CTime x;
	drawingContextStinger=this->GetDC();
	m_stingerAddress=(CComboBox*)GetDlgItem(IDC_STINGER_ADDRESS);
	m_stingerAddress->ResetContent();
	//m_stingerAddress->SetItemHeight(0,900);

	m_offLine1=(CComboBox*)GetDlgItem(IDC_OFF_LINE1);
	m_onLine1=(CComboBox*)GetDlgItem(IDC_ON_LINE1);
	m_offLine2=(CComboBox*)GetDlgItem(IDC_OFF_LINE2);
	m_onLine2=(CComboBox*)GetDlgItem(IDC_ON_LINE2);
	m_offLine3=(CComboBox*)GetDlgItem(IDC_OFF_LINE3);
	m_onLine3=(CComboBox*)GetDlgItem(IDC_ON_LINE3);
	m_offLine4=(CComboBox*)GetDlgItem(IDC_OFF_LINE4);
	m_onLine4=(CComboBox*)GetDlgItem(IDC_ON_LINE4);
	m_offLine5=(CComboBox*)GetDlgItem(IDC_OFF_LINE5);
	m_onLine5=(CComboBox*)GetDlgItem(IDC_ON_LINE5);
	m_offLine6=(CComboBox*)GetDlgItem(IDC_OFF_LINE6);
	m_onLine6=(CComboBox*)GetDlgItem(IDC_ON_LINE6);
	m_offLine7=(CComboBox*)GetDlgItem(IDC_OFF_LINE7);
	m_onLine7=(CComboBox*)GetDlgItem(IDC_ON_LINE7);

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

// Set pointers to "On" and "Off" radio buttons
	m_offCmd=(CButton*)GetDlgItem(IDC_OFF_CMD);
	m_onCmd=(CButton*)GetDlgItem(IDC_ON_CMD);
	m_offCmdButton=(CButton*)GetDlgItem(IDC_STINGEROFF);
	m_onCmdButton=(CButton*)GetDlgItem(IDC_STINGERON);

// Set auto-on enable check to unchecked
	m_autoOnEnable=(CButton*)GetDlgItem(IDC_AUTO_ON_ENABLE);
	m_autoOnEnable->SetCheck(BST_UNCHECKED);

// Set dog leash enable check to unchecked
	m_dogLeashEnable=(CButton*)GetDlgItem(IDC_DOGLEASH_ENABLE);
	m_dogLeashEnable->SetCheck(BST_UNCHECKED);
	m_dogLeashEnable->EnableWindow(FALSE);

// Set auto on period to default value "1:00"
	m_autoOnPeriod=(CDateTimeCtrl*)GetDlgItem(IDC_AUTO_ON_PERIOD);
	m_autoOnPeriod->SetFormat(_T("HH:mm"));
    x=CTime(2007,1,1,1,0,0,-1); // Set time to 1/1/2007 at 1:00AM (only the 1:00 part will show)
	m_autoOnPeriod->SetTime(&x);

// Set auto on delay hrs:mins to default value "0:00"
	m_autoOnDelayHrsMins=(CDateTimeCtrl*)GetDlgItem(IDC_AUTO_ON_DELAY_HRS_MINS);
	m_autoOnDelayHrsMins->SetFormat(_T("HH:mm"));
	x=CTime(2007,1,1,0,0,0,-1); // Set time to 1/1/2007 at 0:00AM (only the 0:00 part will show)
	m_autoOnDelayHrsMins->SetTime(&x);

// Set auto on delay days to default value
	m_autoOnDelayDays=(CComboBox*)GetDlgItem(IDC_AUTO_ON_DELAY_DAYS);
	for (n=0;n<40;n++) {
		strVal.Format("%d",n);
		m_autoOnDelayDays->AddString(strVal);
	}
	m_autoOnDelayDays->SetCurSel(0);

// Set auto on repeat days to default value
	m_autoOnRepeatDays=(CComboBox*)GetDlgItem(IDC_AUTO_ON_REPEAT_DAYS);
	for (n=0;n<40;n++) {
		strVal.Format("%d",n);
		m_autoOnRepeatDays->AddString(strVal);
	}
	m_autoOnRepeatDays->SetCurSel(0);

// Set auto on repeat hrs:mins to default value "0:00"
	m_autoOnRepeatHrsMins=(CDateTimeCtrl*)GetDlgItem(IDC_AUTO_ON_REPEAT_HRS_MINS);
	m_autoOnRepeatHrsMins->SetFormat(_T("HH:mm"));
	x=CTime(2007,1,1,0,0,0,-1); // Set time to 1/1/2007 at 0:00AM (only the 0:00 part will show)
	m_autoOnRepeatHrsMins->SetTime(&x);

// Set dog leash days to default value
	m_dogLeashDays=(CComboBox*)GetDlgItem(IDC_DOGLEASH_DAYS);
	for (n=0;n<40;n++) {
		strVal.Format("%d",n);
		m_dogLeashDays->AddString(strVal);
	}
	m_dogLeashDays->SetCurSel(0);
	m_dogLeashDays->EnableWindow(FALSE);

// Set dog leash hrs:mins to default value "0:00"
	m_dogLeashHrsMins=(CDateTimeCtrl*)GetDlgItem(IDC_DOGLEASH_HRS_MINS);
	m_dogLeashHrsMins->SetFormat(_T("HH:mm"));
	x=CTime(2007,1,1,0,0,0,-1); // Set time to 1/1/2007 at 0:00AM (only the 0:00 part will show)
	m_dogLeashHrsMins->SetTime(&x);
//	m_dogLeashHrsMins->EnableWindow(FALSE);

// Set default stinger address
	if (stingerAddress<0x00f) {
		strVal.Format("0x00%1lx",stingerAddress);
	} else if (stingerAddress<0x0ff) {
		strVal.Format("0x0%2lx",stingerAddress);
	} else  {
		strVal.Format("0x%3lx",stingerAddress);
	}
	m_stingerAddress->SetWindowText(strVal);  //set edit section to what string ended up as
	m_stingerAddress->AddString(strVal); // add address to list
	strVal.ReleaseBuffer();

//
	m_stingerRecord=(CButton*)GetDlgItem(IDC_STINGER_RECORD);
//	m_stingerRecorded=(CButton*)GetDlgItem(IDC_STINGER_RECORDED);

// Disable auto-on stuff since box is not set
	m_autoOnDelayDays->EnableWindow(FALSE);
	m_autoOnDelayHrsMins->EnableWindow(FALSE);
	m_autoOnPeriod->EnableWindow(FALSE);
	m_autoOnRepeatDays->EnableWindow(FALSE);
	m_autoOnRepeatHrsMins->EnableWindow(FALSE);

// Initialize settings from configuration file
	readStingerCmdFile();

	return TRUE;
}


void CStingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
//	DDX_Control(pDX, IDC_STINGER_ADDRESS, m_stingerAddress);
}

BEGIN_MESSAGE_MAP(CStingerDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_MARK_PATTEN, &CStingerDlg::OnMarkPatten)
ON_WM_PAINT()
ON_WM_TIMER()
ON_CBN_SELCHANGE(IDC_ON_LINE1, &CStingerDlg::OnCbnSelchangeCombo5)
ON_CBN_EDITCHANGE(IDC_STINGER_ADDRESS, &CStingerDlg::OnCbnEditchangeStingerAddress)
ON_CBN_SELCHANGE(IDC_STINGER_ADDRESS, &CStingerDlg::OnCbnSelchangeStingerAddress)
ON_BN_CLICKED(IDC_ENTER_ADDRESS, &CStingerDlg::OnBnClickedEnterAddress)
ON_BN_CLICKED(IDC_STINGERBUTTON3, &CStingerDlg::OnBnClickedAddressDelete)
ON_BN_CLICKED(IDC_OFF_CMD, &CStingerDlg::OnBnClickedOffCmd)
ON_BN_CLICKED(IDC_ON_CMD, &CStingerDlg::OnBnClickedOnCmd)
ON_BN_CLICKED(IDC_AUTO_ON_ENABLE, &CStingerDlg::OnBnClickedAutoOnEnable)
ON_BN_CLICKED(IDC_STINGERON, &CStingerDlg::OnBnClickedStingerOn)
ON_BN_CLICKED(IDC_STINGEROFF, &CStingerDlg::OnBnClickedStingerOff)
ON_BN_CLICKED(IDC_STINGER_RECORD, &CStingerDlg::OnBnClickedStingerRecord)
//ON_BN_CLICKED(IDC_STINGER_REC_CLEAR, &CStingerDlg::OnBnClickedStingerRecClear)
ON_BN_CLICKED(IDC_STINGER_VIEWREC, &CStingerDlg::OnBnClickedStingerViewrec)
ON_BN_CLICKED(IDC_DOGLEASH_ENABLE, &CStingerDlg::OnBnClickedDogleashEnable)
ON_BN_CLICKED(IDC_DOGLEASH_VIEW, &CStingerDlg::OnBnClickedDogleashView)
ON_BN_CLICKED(IDC_SET_SYSTEM_CLK, &CStingerDlg::OnBnClickedSetSystemClk)
ON_BN_CLICKED(IDCANCEL, &CStingerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

extern int stingerWinFlag;
extern CButton m_stingerWinButton;
afx_msg void CStingerDlg::OnClose() {
	stingerWinFlag=0;
	writeStingerCmdFile();
//	CMainDlg::m_stingerWinButton.EnableWindow(TRUE);//re-enable button for Scan Window

	CDialog::OnClose();
}

void CStingerDlg::OnCbnSelchangeCombo5()
{
	// TODO: Add your control notification handler code here
}

afx_msg void CStingerDlg::OnPaint() {
	updateStingerStatusLED();
	CDialog::OnPaint();
}

void CStingerDlg::OnTimer(UINT nIDEvent) { //The timer event.
//	if (nIDEvent==ID_TIMER_STINGER_GENERIC) {
//		CStingerDlg::KillTimer(ID_TIMER_STINGER_GENERIC);
//		stingerStatus=STINGER_IDLE;
//		updateStingerStatusLED();
//		m_onCmd->EnableWindow(TRUE);
//		m_offCmd->EnableWindow(TRUE);
//		m_onCmdButton->EnableWindow(TRUE);
//		m_offCmdButton->EnableWindow(TRUE);
//	}
	CDialog::OnTimer(nIDEvent);
}


void CStingerDlg::OnCbnEditchangeStingerAddress()
{
//int n=1;
//   CString str;
// TODO: Add your control notification handler code here
//n = m_stingerAddress->GetLBTextLen( 0 );
//      m_stingerAddress->GetLBText( 0, str.GetBuffer(n) );

//   m_stingerAddress->AddString("Hello");
//      str.ReleaseBuffer();
//m_stingerAddress->GetLBText(
}

void CStingerDlg::OnCbnSelchangeStingerAddress()
{
	CString strVal;
	m_stingerAddress->GetWindowTextA(strVal);
	stingerAddress = strtol(strVal, 0, 0); //convert to long
	if (stingerAddress>0x0fff) stingerAddress=0x0fff;
// TODO: Add your control notification handler code here
}

void CStingerDlg::OnBnClickedEnterAddress()
{
	int n;
	CString strVal;

	m_stingerAddress->GetWindowTextA(strVal);
	stingerAddress = strtol(strVal, 0, 0); //convert to long
	if (stingerAddress>0x0fff) stingerAddress=0x0fff;
	if (stingerAddress<0x00f) {
		strVal.Format("0x00%1lx",stingerAddress);
	} else if (stingerAddress<0x0ff) {
		strVal.Format("0x0%2lx",stingerAddress);
	} else  {
		strVal.Format("0x%3lx",stingerAddress);
	}
	m_stingerAddress->SetWindowText(strVal);  //set edit section to what string ended up as
	n=m_stingerAddress->FindStringExact(-1,strVal); // see if this address has been entered already
	if (n==CB_ERR) { // if not, add it
		n=m_stingerAddress->AddString(strVal); // add address to list
	}
	strVal.ReleaseBuffer();
}

void CStingerDlg::OnBnClickedAddressDelete()
{
   CString str;
	m_stingerAddress->GetWindowTextA(str);
//	int n;
	int nIndex = 0;
	while ((nIndex=m_stingerAddress->FindStringExact(nIndex, str))!=CB_ERR) {
		m_stingerAddress->DeleteString( nIndex );
	}
}

void CStingerDlg::OnBnClickedOffCmd() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
// 	    CStingerDlg::SetTimer(ID_TIMER_STINGER_GENERIC, 4000, NULL); // set timer for 4.0 seconds
		stingerStatus=STINGER_TXMITTING;
		updateStingerStatusLED();
	}
}

void CStingerDlg::OnBnClickedOnCmd() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
// 	    CStingerDlg::SetTimer(ID_TIMER_STINGER_GENERIC, 4000, NULL); // set timer for 4.0 seconds
		stingerStatus=STINGER_TXMITTING;
		updateStingerStatusLED();
	}
}
//extern void setIndicatorLight(int ,int, CDC*);

void CStingerDlg::updateStingerStatusLED() {
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

void CStingerDlg::OnBnClickedStingerOn() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_offCmd->SetCheck(BST_UNCHECKED);
		m_onCmd->SetCheck(BST_CHECKED);
		m_offCmdButton->SetCheck(BST_UNCHECKED);
		m_onCmdButton->SetCheck(BST_CHECKED);
		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		m_onCmdButton->EnableWindow(FALSE);
		m_offCmdButton->EnableWindow(FALSE);
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
 //	    CStingerDlg::SetTimer(ID_TIMER_STINGER_GENERIC, 4000, NULL); // set timer for 4.0 seconds
		stingerStatus=STINGER_TXMITTING;
		updateStingerStatusLED();
	}
}

void CStingerDlg::OnBnClickedStingerOff() {
	if (stingerStatus!=STINGER_TXMITTING) {
		m_offCmd->SetCheck(BST_CHECKED);
		m_onCmd->SetCheck(BST_UNCHECKED);
		m_offCmdButton->SetCheck(BST_CHECKED);
		m_onCmdButton->SetCheck(BST_UNCHECKED);
		m_onCmd->EnableWindow(FALSE);
		m_offCmd->EnableWindow(FALSE);
		m_onCmdButton->EnableWindow(FALSE);
		m_offCmdButton->EnableWindow(FALSE);
		CMainDlg::outputStingerCmd(STINGER_GENERIC);
// 	    CStingerDlg::SetTimer(ID_TIMER_STINGER_GENERIC, 4000, NULL); // set timer for 4.0 seconds
		stingerStatus=STINGER_TXMITTING;
		updateStingerStatusLED();
	}
}

void CStingerDlg::OnBnClickedStingerRecord() {
	if (m_stingerRecord->GetCheck()==BST_CHECKED) {
//		m_stingerRecord->SetCheck(BST_UNCHECKED);
		stingerRecordCmd(1); // The 0 indicates turn record on
	} else {
//		m_stingerRecord->SetCheck(BST_CHECKED);
		stingerRecordCmd(0); // The 1 indicates turn record off
	}
}
extern char outMsgStr[];
extern char inMsgParams[];

void CStingerDlg::stingerRecordCmd(int mode) { // The mode indicates turn record on or off
	outMsgStr[0]=stingerRecordCmdStr[0]; //"dg" command
	outMsgStr[1]=stingerRecordCmdStr[1]; // "dg" command
	outMsgStr[2]=mode; //Indicates turn record on or off
	CMainDlg::writeCmd(CMD_STINGER_RECORD_LEN);  //Write out DG msg of length 3
	CMainDlg::readResp(RESP_STINGER_RECORD_LEN);  //Read in TG msg of length 4
	if (inMsgParams[0]==0) m_stingerRecord->SetCheck(BST_UNCHECKED);
	else  m_stingerRecord->SetCheck(BST_CHECKED);
//	if (inMsgParams[1]==0) m_stingerRecorded->SetCheck(BST_UNCHECKED);
//	else m_stingerRecorded->SetCheck(BST_CHECKED);
}

//void CStingerDlg::OnBnClickedStingerRecClear() {
//	stingerRecordCmd(2); // The 2 indicates erase current stinger command
//}

/////////////////////////////////////////////////////////////////////////////
// CStingerRecCmdDlg dialog

class CStingerRecCmdDlg : public CDialog
{
public:
	CStingerRecCmdDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CStingerRecCmdDlg)
	enum { IDD = IDD_STINGERRECWIN };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStingerRecCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CStingerRecCmdDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnBnClickedStingerRecRefresh();
public:
	afx_msg void OnBnClickedStingerRecEraseall();
};

CStingerRecCmdDlg::CStingerRecCmdDlg(CWnd* pParent /*=NULL*/):CDialog(CStingerRecCmdDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}



CStingerRecCmdDlg *pStingerRecWinDlg=(CStingerRecCmdDlg*)0;


void CStingerDlg::OnBnClickedStingerViewrec() {
//	stingerRecordCmd(3); // The 3 indicates just return current stinger cmd
//
//	inMsgParams[2]
//		CStingerRecCmdDlg dlgXXX;
//		dlgXXX.DoModal();
//		dlgXXX.ShowWindow();

		pStingerRecWinDlg = new CStingerRecCmdDlg((CStingerRecCmdDlg *)this);
		BOOL ret=pStingerRecWinDlg->Create(IDD_STINGERRECWIN,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating Stinger Record Command Dialog");
        pStingerRecWinDlg->ShowWindow(SW_SHOW);

}


/*CStingerRecCmdDlg::CStingerRecCmdDlg(CWnd* pParent) : CDialog(CStingerRecCmdDlg::IDD)
{
	//{{AFX_DATA_INIT(CStingerRecCmdDlg)
	//}}AFX_DATA_INIT
}*/

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
ON_BN_CLICKED(IDC_STINGER_REC_REFRESH, &CStingerRecCmdDlg::OnBnClickedStingerRecRefresh)
ON_BN_CLICKED(IDC_STINGER_REC_ERASEALL, &CStingerRecCmdDlg::OnBnClickedStingerRecEraseall)
END_MESSAGE_MAP()

void prepareStingerRecCmdTxt(CString*,int,int,int);
void updateStingerCmdTxt(CListBox*);
CListBox *pStingerCmdTxt;

BOOL CStingerRecCmdDlg::OnInitDialog() {
	CStingerDlg::stingerRecordCmd(3); // The 3 indicates return current stinger cmd
	pStingerCmdTxt=(CListBox*)GetDlgItem(IDC_STINGER_REC_CMD_TEXT);
	updateStingerCmdTxt(pStingerCmdTxt);
	return TRUE;
}

void updateStingerCmdTxt(CListBox *editText) {
	CString strval;
	editText->ResetContent();
	if (inMsgParams[1]==0) {
		editText->InsertString(0,"(no command)");
	} else {
		if ((inMsgParams[9]&0x08)!=0) {
			editText->InsertString(-1,"ON command---");
		} else {
			editText->InsertString(-1,"OFF command---");
		}
		strval.Format("Address: %1d%1d%1d",
			(int)((inMsgParams[3]>>4)&0x0f),
			(int)((inMsgParams[2]>>0)&0x0f),
			(int)((inMsgParams[2]>>4)&0x0f));
		editText->InsertString(0,strval);
		prepareStingerRecCmdTxt(&strval,(int)1,(int)(inMsgParams[4]&0x10),
			(int)(inMsgParams[4]&0x0f));
		editText->InsertString(-1,strval);
		prepareStingerRecCmdTxt(&strval,(int)2,(int)(inMsgParams[4]&0x20),
			(int)((inMsgParams[5]>>4)&0x0f));
		editText->InsertString(-1,strval);
		prepareStingerRecCmdTxt(&strval,(int)3,(int)(inMsgParams[4]&0x40),
			(int)(inMsgParams[5]&0x0f));
		editText->InsertString(-1,strval);
		prepareStingerRecCmdTxt(&strval,(int)4,(int)(inMsgParams[4]&0x80),
			(int)((inMsgParams[6]>>4)&0x0f));
		editText->InsertString(-1,strval);
		prepareStingerRecCmdTxt(&strval,(int)5,(int)(inMsgParams[3]&0x01),
			(int)(inMsgParams[6]&0x0f));
		editText->InsertString(-1,strval);
		prepareStingerRecCmdTxt(&strval,(int)6,(int)(inMsgParams[3]&0x02),
			(int)((inMsgParams[7]>>4)&0x0f));
		editText->InsertString(-1,strval);
		prepareStingerRecCmdTxt(&strval,(int)7,(int)(inMsgParams[3]&0x04),
			(int)(inMsgParams[7]&0x0f));
		editText->InsertString(-1,strval);
		if ((inMsgParams[9]&0x02)!=0) {
			editText->InsertString(-1,"Schedule: ");
			long unsigned numMinutes=inMsgParams[10];
			numMinutes<<=8;
			numMinutes+=inMsgParams[11];
			numMinutes<<=8;
			numMinutes+=inMsgParams[12];
			strval.Format("Start Delay: %ld minutes",numMinutes);
			editText->InsertString(-1,strval);
			numMinutes=inMsgParams[16];
			numMinutes<<=8;
			numMinutes+=inMsgParams[17];
			strval.Format("On Period: %ld minutes",numMinutes);
			editText->InsertString(-1,strval);
			numMinutes=inMsgParams[13];
			numMinutes<<=8;
			numMinutes+=inMsgParams[14];
			numMinutes<<=8;
			numMinutes+=inMsgParams[15];
			strval.Format("Repeat Period: %ld minutes",numMinutes);
			editText->InsertString(-1,strval);
		}
	}
}


void prepareStingerRecCmdTxt(CString *str,int lineNo,int inputFlag,int outputNibble) {
	str->Format("Line %1d:",lineNo);
	if (inputFlag!=0) {
		str->Format("%s Input",*str);
	} else {
		if (((outputNibble>>2)&0x03)==0)      str->Format("%s OFF:Ground  ",*str);
		else if (((outputNibble>>2)&0x03)==1) str->Format("%s OFF:Battery ",*str);
		else if (((outputNibble>>2)&0x03)==2) str->Format("%s OFF:LogicLo ",*str);
		else if (((outputNibble>>2)&0x03)==3) str->Format("%s OFF:LogicHi ",*str);
		if (((outputNibble)&0x03)==0)      str->Format("%s ON:Ground  ",*str);
		else if (((outputNibble)&0x03)==1) str->Format("%s ON:Battery ",*str);
		else if (((outputNibble)&0x03)==2) str->Format("%s ON:LogicLo ",*str);
		else if (((outputNibble)&0x03)==3) str->Format("%s ON:LogicHi ",*str);

	}
}
void CStingerRecCmdDlg::OnBnClickedStingerRecRefresh()
{
	CStingerDlg::stingerRecordCmd(3); // The 3 indicates return current stinger cmd
	updateStingerCmdTxt(pStingerCmdTxt);
}

void CStingerRecCmdDlg::OnBnClickedStingerRecEraseall()
{
	CStingerDlg::stingerRecordCmd(2); // The 2 indicates erase current stinger command
	updateStingerCmdTxt(pStingerCmdTxt);
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

/////////////////////////////////////////////////////////////////////////////
// CDogleashCmdDlg dialog

class CDogleashCmdDlg : public CDialog
{
public:
	CDogleashCmdDlg(CWnd*);
	void dogleashModeCmd(int);

// Dialog Data
	//{{AFX_DATA(CSDogleashCmdDlg)
	enum { IDD = IDD_DOGLEASHWIN };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogleashCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CDogleashCmdDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnBnClickedDogleashRefresh();
public:
	afx_msg void OnBnClickedDogleashErase();
};

CDogleashCmdDlg::CDogleashCmdDlg(CWnd* pParent /*=NULL*/):CDialog(CDogleashCmdDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}



//CDogleashCmdCmdDlg *pDogleashCmdWinDlg=(CDogleashCmdCmdDlg*)0;


void CDogleashCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStingerRecCmdDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDogleashCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CStingerRecCmdDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_MARK_PATTEN, &CStingerRecCmdDlg::OnMarkPatten)
ON_BN_CLICKED(IDC_DOGLEASH_REFRESH, &CDogleashCmdDlg::OnBnClickedDogleashRefresh)
ON_BN_CLICKED(IDC_DOGLEASH_ERASE, &CDogleashCmdDlg::OnBnClickedDogleashErase)
END_MESSAGE_MAP()

CListBox *pDogleashCmdTxt;
CListBox *pDogleashTimeRemain;
void updateDogleashWindow();
CDogleashCmdDlg *pDogleashWinDlg=(CDogleashCmdDlg*)0;
CSetSysClkDlg *pSetSysClkDlg=(CSetSysClkDlg*)0;

BOOL CDogleashCmdDlg::OnInitDialog() {
	dogleashModeCmd(0); // The 0 indicates return current dog leash
	pDogleashCmdTxt=(CListBox*)GetDlgItem(IDC_DOGLEASH_CMD_TEXT);
	pDogleashTimeRemain=(CListBox*)GetDlgItem(IDC_DOGLEASH_TIMEREMAIN);
	updateDogleashWindow();

	return TRUE;
}

void CDogleashCmdDlg::OnBnClickedDogleashRefresh() {
	dogleashModeCmd(0); // The 0 indicates return current dog leash
	updateDogleashWindow();
}

void CDogleashCmdDlg::OnBnClickedDogleashErase() {
	dogleashModeCmd(1); // The 1 indicates cancel current dog leash
	updateDogleashWindow();
}

void CDogleashCmdDlg::dogleashModeCmd(int mode) { // The mode indicates turn record on or off
	outMsgStr[0]=dogleashModeCmdStr[0]; //"dh" command
	outMsgStr[1]=dogleashModeCmdStr[1]; // "dh" command
	outMsgStr[2]=mode; // 0: return status, 1: erase dogleash
	CMainDlg::writeCmd(CMD_DOGLEASH_MODE_LEN);  //Write out DG msg of length 3
	CMainDlg::readResp(RESP_DOGLEASH_MODE_LEN);  //Read in TG msg of length 4
}

void updateDogleashWindow() {
	CString strval;
	long unsigned longVal;
// First update stinger command printout
	updateStingerCmdTxt(pDogleashCmdTxt);
// Now update seconds remaining
	pDogleashTimeRemain->ResetContent();
	if (inMsgParams[1]!=0) {

		longVal=(long unsigned)inMsgParams[18];
		longVal<<=8;
		longVal+=(long unsigned)inMsgParams[19];
		longVal<<=8;
		longVal+=(long unsigned)inMsgParams[20];

		strval.Format("%7ld",longVal);
		pDogleashTimeRemain->InsertString(-1,strval);
	}
}

void CStingerDlg::OnBnClickedDogleashView() {
		pDogleashWinDlg = new CDogleashCmdDlg((CDogleashCmdDlg *)this);
		BOOL ret=pDogleashWinDlg->Create(IDD_DOGLEASHWIN,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating Dogleash Command Dialog");
        pDogleashWinDlg->ShowWindow(SW_SHOW);
}

void CStingerDlg::OnBnClickedSetSystemClk() {
		pSetSysClkDlg = new CSetSysClkDlg((CSetSysClkDlg *)this);
		BOOL ret=pSetSysClkDlg->Create(IDD_SYSCLK_WIN,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating System Clock Set Dialog");
        pSetSysClkDlg->ShowWindow(SW_SHOW);
}

extern CDialog *pStingerWinDlg;

void CStingerDlg::OnBnClickedCancel() {
	stingerWinFlag=0;
	writeStingerCmdFile();
//Kill stinger window manually
	pStingerWinDlg->DestroyWindow();
//re-enable button for Channels Window
	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}

void CStingerDlg::readStingerCmdFile() {
	FILE *fp;
	ULONG value;
	CString strVal;
	CTime x;
//	char displayString[20];
	char oneChar;
	CComboBox *p_combobox;

	int success,i,j,numItems,selectedItem;
	fp=fopen("stingercmd.txt","r");
	if (fp) {
		success=fscanf(fp," %d",&numItems);
		if (!success) return;
		success=fscanf(fp," %d",&selectedItem);
		if (!success) return;
		if (numItems<0) numItems=0;
		if (numItems>20) numItems=20; // max 20 addresses
		if (selectedItem<0) selectedItem=0;
		if (selectedItem>=numItems) selectedItem=numItems-1;
		m_stingerAddress->ResetContent();
		for (i=0;i<numItems;i++) {
			success=fscanf(fp," %lx",&value);
			if (!success) return;
			if (value>0x0fff) value=0x0fff;
			if (value<0x00f) {
				strVal.Format("0x00%1lx",value);
			} else if (value<0x0ff) {
				strVal.Format("0x0%2lx",value);
			} else  {
				strVal.Format("0x%3lx",value);
			}
			m_stingerAddress->AddString(strVal); // add address to list
		}
		m_stingerAddress->SetCurSel(selectedItem);
		success=fscanf(fp," %c",&oneChar);
		if (!success) return;
		if (toupper(oneChar)=='O') {
			success=fscanf(fp," %c",&oneChar);
			if (!success) return;
			if (toupper(oneChar)=='N') { // ON command
			} else if (toupper(oneChar)=='F') { // OFF command
				success=fscanf(fp," %c",&oneChar); // scan in next F
				if (!success) return;
			} else return;
		} else return;
		for (i=0;i<7;i++) {
			for (j=0;j<2;j++) {
				if (j==0) { // Off commands
					switch(i) {
						case 0:{p_combobox=m_offLine1;break;}
						case 1:{p_combobox=m_offLine2;break;}
						case 2:{p_combobox=m_offLine3;break;}
						case 3:{p_combobox=m_offLine4;break;}
						case 4:{p_combobox=m_offLine5;break;}
						case 5:{p_combobox=m_offLine6;break;}
						case 6:{p_combobox=m_offLine7;break;}
					}
				} else { // On commands
					switch(i) {
						case 0:{p_combobox=m_onLine1;break;}
						case 1:{p_combobox=m_onLine2;break;}
						case 2:{p_combobox=m_onLine3;break;}
						case 3:{p_combobox=m_onLine4;break;}
						case 4:{p_combobox=m_onLine5;break;}
						case 5:{p_combobox=m_onLine6;break;}
						case 6:{p_combobox=m_onLine7;break;}
					}
				}
				success=fscanf(fp," %c",&oneChar);
				if (!success) return;
				if (toupper(oneChar)=='G') { //Ground
					p_combobox->SetCurSel(0);
				} else if (toupper(oneChar)=='B') { //Battery
					if (i==6) p_combobox->SetCurSel(0);
					else if (i==4) p_combobox->SetCurSel(2); // Line 5 use Logic Hi for battery
					else p_combobox->SetCurSel(1);
				} else if (toupper(oneChar)=='L') { //Logic Low
					if (i==6) p_combobox->SetCurSel(0);
					else if (i==4) p_combobox->SetCurSel(1); // Line 5 Logic Low is second item
					else p_combobox->SetCurSel(2);
				} else if (toupper(oneChar)=='H') { //Logic High
					if (i==6) p_combobox->SetCurSel(0);
					else if (i==0) p_combobox->SetCurSel(1); // Line 1 use Battery for Logic High 
					else if (i==1) p_combobox->SetCurSel(1); // Line 2 use Battery for Logic High 
					else if (i==4) p_combobox->SetCurSel(2); // Line 5 Logic High is third item
					else p_combobox->SetCurSel(3);
				} else if (toupper(oneChar)=='I') { //Input
					if (i==0) p_combobox->SetCurSel(3);
					else if (i==1) p_combobox->SetCurSel(3);
					else if (i==4) p_combobox->SetCurSel(3);
					else if (i==6) p_combobox->SetCurSel(0);
					else p_combobox->SetCurSel(4);
				} else if (toupper(oneChar)=='O') { //Open
					if (i==0) p_combobox->SetCurSel(3);
					else if (i==1) p_combobox->SetCurSel(3);
					else if (i==4) p_combobox->SetCurSel(3);
					else if (i==6) p_combobox->SetCurSel(0);
					else p_combobox->SetCurSel(4);
				} else return;
			}
		} //End loop for setting on-off logic
// Read "on" of "off" for schedule command
		success=fscanf(fp," %c",&oneChar);
		if (!success) return;
		if (toupper(oneChar)=='O') {
			success=fscanf(fp," %c",&oneChar);
			if (!success) return;
			if (toupper(oneChar)=='N') { // Schedule
				m_autoOnEnable->SetCheck(BST_CHECKED);
				m_dogLeashEnable->EnableWindow(TRUE);
				m_autoOnDelayDays->EnableWindow(TRUE);
				m_autoOnDelayHrsMins->EnableWindow(TRUE);
				m_autoOnPeriod->EnableWindow(TRUE);
				m_autoOnRepeatDays->EnableWindow(TRUE);
				m_autoOnRepeatHrsMins->EnableWindow(TRUE);
			} else { // Schedule disabled
				m_autoOnEnable->SetCheck(BST_UNCHECKED);
				m_dogLeashEnable->SetCheck(BST_UNCHECKED);
				m_dogLeashEnable->EnableWindow(FALSE);
				m_dogLeashDays->EnableWindow(FALSE);
				m_dogLeashHrsMins->EnableWindow(FALSE);
				m_autoOnDelayDays->EnableWindow(FALSE);
				m_autoOnDelayHrsMins->EnableWindow(FALSE);
				m_autoOnPeriod->EnableWindow(FALSE);
				m_autoOnRepeatDays->EnableWindow(FALSE);
				m_autoOnRepeatHrsMins->EnableWindow(FALSE);
				success=fscanf(fp," %c",&oneChar); // scan in next F
				if (!success) return;
			}
		} else return;
// start delay number of days
		success=fscanf(fp," %d",&i);
		if (!success) return;
		m_autoOnDelayDays->SetCurSel(i);
// start delay hours:minutes
		success=fscanf(fp," %d:",&i);
		if (!success) return;
		if (i>23) i=23;if (i<0) i=0;
		success=fscanf(fp," %d",&j);
		if (!success) return;
		if (j>59) j=59;if (j<0) j=0;
		x=CTime(2007,1,1,i,j,0,-1);
		m_autoOnDelayHrsMins->SetTime(&x);
// start on period hours:minutes
		success=fscanf(fp," %d:",&i);
		if (!success) return;
		if (i>23) i=23;if (i<0) i=0;
		success=fscanf(fp," %d",&j);
		if (!success) return;
		if (j>59) j=59;if (j<0) j=0;
		x=CTime(2007,1,1,i,j,0,-1);
		m_autoOnPeriod->SetTime(&x);
	}
// repeat time number of days
		success=fscanf(fp," %d",&i);
		if (!success) return;
		m_autoOnRepeatDays->SetCurSel(i);
// repeat time hours:minutes
		success=fscanf(fp," %d:",&i);
		if (!success) return;
		if (i>23) i=23;if (i<0) i=0;
		success=fscanf(fp," %d",&j);
		if (!success) return;
		if (j>59) j=59;if (j<0) j=0;
		x=CTime(2007,1,1,i,j,0,-1);
		m_autoOnRepeatHrsMins->SetTime(&x);
// Read "on" of "off" for dog leash command
		success=fscanf(fp," %c",&oneChar);
		if (!success) return;
		if (toupper(oneChar)=='O') {
			success=fscanf(fp," %c",&oneChar);
			if (!success) return;
			if (toupper(oneChar)=='N') { // Schedule
				m_dogLeashEnable->SetCheck(BST_CHECKED);
				m_dogLeashDays->EnableWindow(TRUE);
				m_dogLeashHrsMins->EnableWindow(TRUE);
				m_autoOnPeriod->EnableWindow(FALSE);
				m_autoOnRepeatDays->EnableWindow(FALSE);
				m_autoOnRepeatHrsMins->EnableWindow(FALSE);
			} else { // Schedule disabled
				m_dogLeashEnable->SetCheck(BST_UNCHECKED);
				m_dogLeashDays->EnableWindow(FALSE);
				m_dogLeashHrsMins->EnableWindow(FALSE);
				m_autoOnPeriod->EnableWindow(TRUE);
				m_autoOnRepeatDays->EnableWindow(TRUE);
				m_autoOnRepeatHrsMins->EnableWindow(TRUE);
				success=fscanf(fp," %c",&oneChar); // scan in next F
				if (!success) return;
			}
		} else return;
// dog leash number of days
		success=fscanf(fp," %d",&i);
		if (!success) return;
		m_dogLeashDays->SetCurSel(i);
// dog leash hours:minutes
		success=fscanf(fp," %d:",&i);
		if (!success) return;
		if (i>23) i=23;if (i<0) i=0;
		success=fscanf(fp," %d",&j);
		if (!success) return;
		if (j>59) j=59;if (j<0) j=0;
		x=CTime(2007,1,1,i,j,0,-1);
		m_dogLeashHrsMins->SetTime(&x);
}

void CStingerDlg::writeStingerCmdFile() {
	FILE *fp;
	ULONG value;
	int success,i,j,k;
	CComboBox *p_combobox;
	CString p_string,strVal;
	CTime x;

	fp=fopen("stingercmd.txt","w");
	if (fp) { //write stinger config file
		j=m_stingerAddress->GetCount();
		fprintf(fp,"%d ",j);
		i=m_stingerAddress->GetCurSel();
		if (i<0) i=0;
		fprintf(fp,"%d ",i);
		for (i=0;i<j;i++) { // Save all stinger addresses
			m_stingerAddress->GetLBText(i,p_string);
			value = strtol(p_string, 0, 0); //convert to long
			if (value>0x0fff) value=0x0fff;
			if (value<0x00f) {
				strVal.Format("0x00%1lx",value);
			} else if (value<0x0ff) {
				strVal.Format("0x0%2lx",value);
			} else  {
				strVal.Format("0x%3lx",value);
			}
			fprintf(fp," %s",strVal);
		}
		fprintf(fp,"\n");
		if (m_onCmd->GetCheck()==BST_CHECKED) {
			fprintf(fp,"ON\n");
		} else {
			fprintf(fp,"OFF\n");
		}
		for (i=0;i<7;i++) {
			for (j=0;j<2;j++) {
				if (j==0) { // Off commands
					switch(i) {
						case 0:{p_combobox=m_offLine1;break;}
						case 1:{p_combobox=m_offLine2;break;}
						case 2:{p_combobox=m_offLine3;break;}
						case 3:{p_combobox=m_offLine4;break;}
						case 4:{p_combobox=m_offLine5;break;}
						case 5:{p_combobox=m_offLine6;break;}
						case 6:{p_combobox=m_offLine7;break;}
					}
				} else { // On commands
					switch(i) {
						case 0:{p_combobox=m_onLine1;break;}
						case 1:{p_combobox=m_onLine2;break;}
						case 2:{p_combobox=m_onLine3;break;}
						case 3:{p_combobox=m_onLine4;break;}
						case 4:{p_combobox=m_onLine5;break;}
						case 5:{p_combobox=m_onLine6;break;}
						case 6:{p_combobox=m_onLine7;break;}
					}
				}
				k=p_combobox->GetCurSel();
				switch(k) {
					case 0:{fprintf(fp,"G");break;}
					case 1:{
						if (i==4) fprintf(fp,"L");
						else if (i==6) fprintf(fp,"I");
						else fprintf(fp,"B");break;
					}
					case 2:{
						if (i==4) fprintf(fp,"H");
						else if (i==6) fprintf(fp,"I");
						else fprintf(fp,"L");break;}
					case 3:{
						if (i==0 || i==1)fprintf(fp,"O");
						else if (i==4) fprintf(fp,"I");
						else if (i==6) fprintf(fp,"I");
						else fprintf(fp,"H");
						break;
					}
					case 4:{
						if (i==0 || i==1) fprintf(fp,"O");
						else fprintf(fp,"I");
						break;
					}
				}
				if (j==0) fprintf(fp,"   ");
				else fprintf(fp,"\n");
			} // end for j (off and on)
		} // end for i (lines number 1--7)
		if (m_autoOnEnable->GetCheck()==BST_CHECKED) {
			fprintf(fp,"ON\n");
		} else {
			fprintf(fp,"OFF\n");
		}
// Auto on delay
		m_autoOnDelayDays->GetWindowTextA(strVal);
	    value = strtol(strVal, 0, 0); //convert to long
		fprintf(fp,"%ld ",value);
		m_autoOnDelayHrsMins->GetTime(x); // get delay time value
		i=x.GetHour();
		j=x.GetMinute();
		if (j<10) {
			fprintf(fp,"%d:0%d\n",i,j);
		} else {
			fprintf(fp,"%d:%d\n",i,j);
		}
// Auto on period
		m_autoOnPeriod->GetTime(x); // get delay time value
		i=x.GetHour();
		j=x.GetMinute();
		if (j<10) {
			fprintf(fp,"%d:0%d\n",i,j);
		} else {
			fprintf(fp,"%d:%d\n",i,j);
		}
// Repeat time
		m_autoOnRepeatDays->GetWindowTextA(strVal);
	    value = strtol(strVal, 0, 0); //convert to long
		fprintf(fp,"%ld ",value);
		m_autoOnRepeatHrsMins->GetTime(x);
		i=x.GetHour();
		j=x.GetMinute();
		if (j<10) {
			fprintf(fp,"%d:0%d\n",i,j);
		} else {
			fprintf(fp,"%d:%d\n",i,j);
		}
		if (m_dogLeashEnable->GetCheck()==BST_CHECKED) {
			fprintf(fp,"ON\n");
		} else {
			fprintf(fp,"OFF\n");
		}
// Repeat time
		m_dogLeashDays->GetWindowTextA(strVal);
	    value = strtol(strVal, 0, 0); //convert to long
		fprintf(fp,"%ld ",value);
		m_dogLeashHrsMins->GetTime(x);
		i=x.GetHour();
		j=x.GetMinute();
		if (j<10) {
			fprintf(fp,"%d:0%d\n",i,j);
		} else {
			fprintf(fp,"%d:%d\n",i,j);
		}

		fclose(fp);
	} else {
	}
}


