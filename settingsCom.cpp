/////////////////////////////////////////////////////////////////////////////
// CChannelsDlg dialog used to display channels

#include "stdafx.h"
#include "settingsComDlg.h"
#include "infinityDlg.h"
#include "resource.h"
#include "com_port.h"
#include <afxsock.h>
#include "config.h"

extern int portType;

BEGIN_MESSAGE_MAP(CSettingsComDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDCANCEL, &CChannelsDlg::OnBnClickedChannelsOk)
//ON_WM_INITDIALOG()
ON_WM_SYSCOMMAND()
ON_WM_CLOSE()
ON_WM_PAINT()
ON_CBN_SELCHANGE(IDC_PORT_NUMBER, &CSettingsComDlg::OnCbnSelchangePortNumber)
//ON_CBN_EDITCHANGE(IDC_IP_ADDRESS, &CSettingsComDlg::OnCbnSelchangeIPAddress)
//ON_CBN_EDITCHANGE(IDC_TELNET_PORT, &CSettingsComDlg::OnCbnSelchangeTelnetPort)
ON_CBN_KILLFOCUS(IDC_IP_ADDRESS, &CSettingsComDlg::OnCbnSelchangeIPAddress)
ON_CBN_KILLFOCUS(IDC_TELNET_PORT, &CSettingsComDlg::OnCbnSelchangeTelnetPort)
ON_BN_CLICKED(ID_SETTINGS_COM_CLOSE, &CSettingsComDlg::OnBnClickedSettingsComClose)
ON_BN_CLICKED(IDC_BAUD_300, &CSettingsComDlg::OnBnClickedBaud300)
ON_BN_CLICKED(IDC_BAUD_9600, &CSettingsComDlg::OnBnClickedBaud9600)
ON_BN_CLICKED(IDC_PORT_TYPE_TCPIP, &CSettingsComDlg::OnBnClickedPortTypeTCPIP)
ON_BN_CLICKED(IDC_PORT_TYPE_RS232, &CSettingsComDlg::OnBnClickedPortTypeRS232)
ON_BN_CLICKED(IDC_DPI_96, &CSettingsComDlg::OnBnClickedDPI96)
ON_BN_CLICKED(IDC_DPI_120, &CSettingsComDlg::OnBnClickedDPI120)

ON_CBN_SELCHANGE(IDC_TELNET_PORT, &CSettingsComDlg::OnCbnSelchangeTelnetPort)
//ON_CBN_SELCHANGE(IDC_COM_PORT_NUMBER2, &CSettingsComDlg::OnCbnSelchangeComPortNumber)
ON_BN_CLICKED(ID_LAUNCH_COM_PORT_ENUM, &CSettingsComDlg::OnBnClickedLaunchComPortEnum)
//ON_CBN_CLOSEUP(IDC_COM_PORT_NUMBER2, &CSettingsComDlg::OnCbnCloseupComPortNumber2)
//ON_CBN_EDITCHANGE(IDC_COM_PORT_NUMBER2, &CSettingsComDlg::OnCbnEditchangeComPortNumber2)
END_MESSAGE_MAP()


CSettingsComDlg::CSettingsComDlg(CWnd* pParent /*=NULL*/) : CDialog(CSettingsComDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

void CSettingsComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelsDlg)
	//}}AFX_DATA_MAP
}


afx_msg void CSettingsComDlg::OnPaint() {
	CDialog::OnPaint();
}

CSettingsMiscDlg::CSettingsMiscDlg(CWnd* pParent /*=NULL*/) : CDialog(CSettingsMiscDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
}

void CSettingsMiscDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelsDlg)
	//}}AFX_DATA_MAP
}

void CSettingsMiscDlg::OnClose() 
{
	//Anything that needs to occur on closing the application goes here.
	//Free any resources used by previous API calls and still allocated.

	CDialog::OnClose();
}

afx_msg void CSettingsMiscDlg::OnPaint() {
	CDialog::OnPaint();
}
int settingsMiscWinFlag;
extern int settingsComWinFlag;

CComboBox *m_ipAddress;
CComboBox *m_telnetPort;
extern CString ipAddress;
extern int telnetPort;
extern int audioPort;
extern CString audioPath;

//CComboBox *m_comPortNumber;

//extern CAsyncSocket sockClient;

afx_msg void CSettingsComDlg::OnClose() {
/*
	int bRet;
	int iErr;

	CString tempString;

	m_ipAddress->GetWindowTextA(ipAddress);
	m_telnetPort->GetWindowTextA(tempString);
	sscanf(tempString,"%d\n",&telnetPort);

//	m_comPortNumber->GetWindowTextA(tempString);

	m_audioPort->GetWindowTextA(tempString);
	sscanf(tempString,"%d\n",&audioPort);
	m_audioPath->GetWindowTextA(audioPath);
*/

	CMainDlg::saveConfigToFile() ;
	settingsComWinFlag=0;


	CDialog::OnClose();
}

CComboBox *m_portSelect;

CButton *m_baudSelect;
//CButton *m_dbmMode;
CButton *m_ledScreenCal;
CEdit *m_xCalFactor;
CEdit *m_yCalFactor;

float ledXcal=1.33;
float ledYcal=1.23;
extern int	useXYLedCal;


extern int comPortNumber;
extern int comPortBaud;
extern int dbmMode;
//extern CString comPortString[];
extern int DPI_setting;

BOOL CSettingsComDlg::OnInitDialog() {
	CButton *x;
	m_portSelect = (CComboBox*)GetDlgItem(IDC_PORT_NUMBER);

	m_baudSelect = (CButton*)GetDlgItem(IDC_BAUD_300);

	int n;
	int i;
	char tempString2[10];

	for (i=1;i<=MAX_COM_PORT_NUMBER;i++) {
		if (i<10) {
			sprintf(tempString2,"COM%1d",i);
		} else {
			sprintf(tempString2,"COM%2d",i);
		}
		n=m_portSelect->AddString(tempString2);
	}
//	n=m_portSelect->AddString(comPortString[0]);
//	n=m_portSelect->AddString(comPortString[1]);
//	n=m_portSelect->AddString(comPortString[2]);
//	n=m_portSelect->AddString(comPortString[3]);
//	n=m_portSelect->AddString(comPortString[4]);
//	n=m_portSelect->AddString(comPortString[5]);

	m_portSelect->SetCurSel(comPortNumber);
	if (comPortBaud==0) {
		m_baudSelect->SetCheck(BST_UNCHECKED);
		CButton *x=(CButton*)GetDlgItem(IDC_BAUD_9600);
		x->SetCheck(BST_CHECKED);
	} else {
		m_baudSelect->SetCheck(BST_CHECKED);
		CButton *x=(CButton*)GetDlgItem(IDC_BAUD_9600);
		x->SetCheck(BST_UNCHECKED);
	}

	m_ipAddress = (CComboBox*)GetDlgItem(IDC_IP_ADDRESS);
	m_telnetPort= (CComboBox*)GetDlgItem(IDC_TELNET_PORT);
//	m_comPortNumber= (CComboBox*)GetDlgItem(IDC_COM_PORT_NUMBER2);


	m_ipAddress->SetWindowTextA(ipAddress);
	CString tempString;
	sprintf(tempString2,"%d",telnetPort);
	m_telnetPort->SetWindowTextA(tempString2);

	if (portType==PORT_TYPE_TCPIP) {
		CButton *x=(CButton*)GetDlgItem(IDC_PORT_TYPE_RS232);
		x->SetCheck(BST_UNCHECKED);
		x=(CButton*)GetDlgItem(IDC_PORT_TYPE_TCPIP);
		x->SetCheck(BST_CHECKED);

		x=(CButton*)GetDlgItem(IDC_BAUD_300);
		x->EnableWindow(FALSE);
		x=(CButton*)GetDlgItem(IDC_BAUD_9600);
		x->EnableWindow(FALSE);
		x=(CButton*)GetDlgItem(IDC_PORT_NUMBER);
		x->EnableWindow(FALSE);
//		x=(CButton*)GetDlgItem(IDC_COM_PORT_NUMBER2);
//		x->EnableWindow(FALSE);
		x=(CButton*)GetDlgItem(IDC_IP_ADDRESS);
		x->EnableWindow(TRUE);
		x=(CButton*)GetDlgItem(IDC_TELNET_PORT);
		x->EnableWindow(TRUE);
	} else {
		CButton *x=(CButton*)GetDlgItem(IDC_PORT_TYPE_RS232);
		x->SetCheck(BST_CHECKED);
		x=(CButton*)GetDlgItem(IDC_PORT_TYPE_TCPIP);
		x->SetCheck(BST_UNCHECKED);
		x=(CButton*)GetDlgItem(IDC_BAUD_300);
		x->EnableWindow(TRUE);
		x=(CButton*)GetDlgItem(IDC_BAUD_9600);
		x->EnableWindow(TRUE);
		x=(CButton*)GetDlgItem(IDC_PORT_NUMBER);
		x->EnableWindow(TRUE);
//		x=(CButton*)GetDlgItem(IDC_COM_PORT_NUMBER2);
//		x->EnableWindow(TRUE);
		x=(CButton*)GetDlgItem(IDC_IP_ADDRESS);
		x->EnableWindow(FALSE);
		x=(CButton*)GetDlgItem(IDC_TELNET_PORT);
		x->EnableWindow(FALSE);
	}

	if (DPI_setting==0) {
		x=(CButton*)GetDlgItem(IDC_DPI_96);
		x->SetCheck(BST_CHECKED);
		x=(CButton*)GetDlgItem(IDC_DPI_120);
		x->SetCheck(BST_UNCHECKED);
	} else {
		x=(CButton*)GetDlgItem(IDC_DPI_96);
		x->SetCheck(BST_UNCHECKED);
		x=(CButton*)GetDlgItem(IDC_DPI_120);
		x->SetCheck(BST_CHECKED);
	}
	return TRUE;
}

extern CMenu myMenu;

BOOL CSettingsMiscDlg::OnInitDialog() {
	char tempString[20];
//	m_dbmMode = (CButton *)GetDlgItem(IDC_DBM_MODE);
	m_ledScreenCal = (CButton *)GetDlgItem(IDC_LED_CAL);
	m_xCalFactor = (CEdit*) GetDlgItem(IDC_LED_X_CAL);
	m_yCalFactor = (CEdit*) GetDlgItem(IDC_LED_Y_CAL);

	sprintf(tempString,"%8.3f",ledXcal);
	m_xCalFactor->SetWindowTextA(tempString);
	sprintf(tempString,"%8.3f",ledYcal);
	m_yCalFactor->SetWindowTextA(tempString);


//	if (dbmMode==0) {
//		myMenu.CheckMenuItem(ID_DB_USEDBM, MF_UNCHECKED | MF_BYCOMMAND);
//		m_dbmMode->SetCheck(BST_UNCHECKED);
//	} else {
//		m_dbmMode->SetCheck(BST_CHECKED);
//		myMenu.CheckMenuItem(ID_DB_USEDBM, MF_CHECKED | MF_BYCOMMAND);
//	}
	if (useXYLedCal==0) {
		m_ledScreenCal->SetCheck(BST_UNCHECKED);
	} else {
		m_ledScreenCal->SetCheck(BST_CHECKED);
	}
	return TRUE;
}



extern CDialog *pSettingsComDlg;

void CSettingsComDlg::OnBnClickedSettingsComClose() {
//	CSettingsComDlg::OnClose();
    settingsComWinFlag=0;
//Kill com window manually
	pSettingsComDlg->DestroyWindow();
	CMainDlg::saveConfigToFile();
//	CDialog::OnClose();
}

CDialog *pSettingsMiscDlg;
extern CDialog *pSettingsComDlg;

extern void init_com_port();
void CSettingsComDlg::OnCbnSelchangePortNumber()
{
	comPortNumber=m_portSelect->GetCurSel();
//	CMainDlg::saveConfigToFile();
	init_com_port();
}

void CSettingsComDlg::OnCbnSelchangeIPAddress()
{
	m_ipAddress->GetWindowTextA(ipAddress);
	init_com_port();
}


void CSettingsComDlg::OnCbnSelchangeTelnetPort() {
	CString tempString;
	char buff[50];
	m_telnetPort->GetWindowTextA(tempString);
	sscanf(tempString,"%d\n",&telnetPort);
	sprintf(buff,"%d",telnetPort);
	m_telnetPort->SetWindowTextA(buff);

//	CMainDlg::saveConfigToFile();
	init_com_port();

}

void CSettingsComDlg::OnOK() {
//	int x;
//	CWnd *focus;
//	focus=GetFocus();
//	if (focus==m_ipAddress) {
		CSettingsComDlg::OnCbnSelchangeIPAddress();
		CSettingsComDlg::OnCbnSelchangeTelnetPort();
//	} else if (focus==m_txFreqValue) {
//		CMainDlg::OnBnClickedTxsetfreq();
//	}
	CMainDlg::saveConfigToFile();

}


void CSettingsComDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}


void CSettingsComDlg::OnBnClickedBaud300() {
	comPortBaud=1;
//	CMainDlg::saveConfigToFile();
	init_com_port();
}

void CSettingsComDlg::OnBnClickedBaud9600() {
	comPortBaud=0;
//	CMainDlg::saveConfigToFile();
	init_com_port();
}

BEGIN_MESSAGE_MAP(CSettingsMiscDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDCANCEL, &CChannelsDlg::OnBnClickedChannelsOk)
//ON_WM_INITDIALOG()
ON_WM_SYSCOMMAND()
ON_WM_CLOSE()
ON_WM_PAINT()
ON_BN_CLICKED(ID_SETTINGS_MISC_CLOSE, &CSettingsMiscDlg::OnBnClickedSettingsMiscClose)
//ON_BN_CLICKED(IDC_DBM_MODE, &CSettingsMiscDlg::OnBnClickedDbmMode)
END_MESSAGE_MAP()

void CSettingsMiscDlg::OnBnClickedSettingsMiscClose() {
	CString tempString;
	m_xCalFactor->GetWindowText(tempString); // get string text
	ledXcal = strtod(tempString, 0); //convert text to float
	m_yCalFactor->GetWindowText(tempString); // get string text
	ledYcal = strtod(tempString, 0); //convert text to float

	if (m_ledScreenCal->GetCheck()==BST_CHECKED) {
		if (useXYLedCal!=1) {
			useXYLedCal=1;
			CMainDlg::saveConfigToFile();
		}
	} else {
		if (useXYLedCal!=0) {
			useXYLedCal=0;
			CMainDlg::saveConfigToFile();

		}
	}

	settingsMiscWinFlag=0;
//Kill com window manually
	pSettingsMiscDlg->DestroyWindow();
	CDialog::OnClose();
}


void CSettingsComDlg::OnBnClickedPortTypeRS232()
{
	CButton *x=(CButton*)GetDlgItem(IDC_PORT_TYPE_RS232);
	x->SetCheck(BST_CHECKED);
	x=(CButton*)GetDlgItem(IDC_PORT_TYPE_TCPIP);
	x->SetCheck(BST_UNCHECKED);
	x=(CButton*)GetDlgItem(IDC_BAUD_300);
	x->EnableWindow(TRUE);
	x=(CButton*)GetDlgItem(IDC_BAUD_9600);
	x->EnableWindow(TRUE);
	x=(CButton*)GetDlgItem(IDC_PORT_NUMBER);
	x->EnableWindow(TRUE);
//	x=(CButton*)GetDlgItem(IDC_COM_PORT_NUMBER2);
//	x->EnableWindow(TRUE);
	x=(CButton*)GetDlgItem(IDC_IP_ADDRESS);
	x->EnableWindow(FALSE);
	x=(CButton*)GetDlgItem(IDC_TELNET_PORT);
	x->EnableWindow(FALSE);


	portType=PORT_TYPE_RS232;
}

void CSettingsComDlg::OnBnClickedPortTypeTCPIP()
{
	CButton *x=(CButton*)GetDlgItem(IDC_PORT_TYPE_RS232);
	x->SetCheck(BST_UNCHECKED);
	x=(CButton*)GetDlgItem(IDC_PORT_TYPE_TCPIP);
	x->SetCheck(BST_CHECKED);
	x=(CButton*)GetDlgItem(IDC_BAUD_300);
	x->EnableWindow(FALSE);
	x=(CButton*)GetDlgItem(IDC_BAUD_9600);
	x->EnableWindow(FALSE);
	x=(CButton*)GetDlgItem(IDC_PORT_NUMBER);
	x->EnableWindow(FALSE);
//	x=(CButton*)GetDlgItem(IDC_COM_PORT_NUMBER2);
//	x->EnableWindow(FALSE);
	x=(CButton*)GetDlgItem(IDC_IP_ADDRESS);
	x->EnableWindow(TRUE);
	x=(CButton*)GetDlgItem(IDC_TELNET_PORT);
	x->EnableWindow(TRUE);

	portType=PORT_TYPE_TCPIP;
}

void CSettingsComDlg::OnCbnSelchangeComPortNumber()
{
	// TODO: Add your control notification handler code here
}

void CSettingsComDlg::OnBnClickedLaunchComPortEnum()
{
	ShellExecute(NULL, "open", "SerialEnum.exe", NULL, NULL, SW_SHOWNORMAL);
}

void CSettingsComDlg::OnCbnCloseupComPortNumber2()
{
	int i;
	i=4;
	// TODO: Add your control notification handler code here
}

void CSettingsComDlg::OnCbnEditchangeComPortNumber2()
{
	int i;
	i=4;

	// TODO: Add your control notification handler code here
}

void CSettingsComDlg::OnBnClickedDPI96(){
	CButton *x;
	DPI_setting=0;
	x=(CButton*)GetDlgItem(IDC_DPI_96);
	x->SetCheck(BST_CHECKED);
	x=(CButton*)GetDlgItem(IDC_DPI_120);
	x->SetCheck(BST_UNCHECKED);
	CMainDlg::saveConfigToFile();
}

void CSettingsComDlg::OnBnClickedDPI120(){
	CButton *x;
	DPI_setting=1;
	x=(CButton*)GetDlgItem(IDC_DPI_96);
	x->SetCheck(BST_UNCHECKED);
	x=(CButton*)GetDlgItem(IDC_DPI_120);
	x->SetCheck(BST_CHECKED);
	CMainDlg::saveConfigToFile();
}

 