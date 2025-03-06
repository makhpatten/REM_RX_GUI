#include "stdafx.h"
#include "passwordDlg.h"
#include "infinityDlg.h"
#include "sys_clk.h"
#include "msg_defs.h"
#include "specialStingerCmdDlg.h"


CEnterPasswordDlg *pEnterPasswordWinDlg;
CPasswordDlg* pPasswordWinDlg;
CChangePasswordDlg* pChangePasswordWinDlg;
//CSpecialStingerCmdDlg* pSpecialStingerCmdWinDlg;
CButton *pw_setFreq;
CButton *pw_FreqVal1;
CButton *pw_FreqVal2;
CButton *pw_FreqVal3;
CButton *pw_FreqVal4;
CButton *pw_FreqVal5;
CButton *pw_FreqVal6;
CButton *pw_FreqVal7;
CButton *pw_FreqVal8;
CSliderCtrl *pw_FreqSelect;
CEdit *pw_FreqValue;
CString freqpwValString;
CEdit *pw_EncWrd1;
CEdit *pw_EncWrd2;
CEdit *pw_EncWrd3;
CEdit *pw_EncWrd4;
CEdit *pw_LoadGood;
double freqpwValDouble;
char freqpwValChars[50];

extern ULONG tuneFreqKHz;
extern ULONG setFreqKHz[];
extern void freqKHzToMHzString(ULONG,char *);
extern CButton *m_stingerCmd;
extern int limitFreqValRange(ULONG *freqVal);
extern void insertTextIntoFreqButton(int,char*);
extern char outMsgStr[];
extern char inMsgParams[];
extern int continuousFlag;

int enterPasswordWinFlag;
CString currentPassword;
void CEnterPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterPasswordDlg)
	//}}AFX_DATA_MAP
}
BYTE decodeByte(BYTE);
BYTE encodeByte(BYTE);
void scrambleByte(BYTE *,BYTE *);
int readPasswordFile();
int writePasswordFile();

BOOL CEnterPasswordDlg::OnInitDialog() {
	BYTE oneByte;
	oneByte='P';
	BYTE key='x';
    scrambleByte(&oneByte,&key);
	key='x';
    scrambleByte(&oneByte,&key);

	oneByte='P';
	oneByte=encodeByte(oneByte);
	oneByte=decodeByte(oneByte);
	oneByte='a';
	oneByte=encodeByte(oneByte);
	oneByte=decodeByte(oneByte);

	if (readPasswordFile()==0) {
		writePasswordFile();
	}

//    m_sdFileName = (CEdit*) GetDlgItem(IDC_NEXT_FILE_NAME_TEXT);
//	CMainDlg::readFileNameCmd();
//	m_sdFileName->SetWindowText(SDFileNameStr); 

	return TRUE;
}


BYTE decodeByte(BYTE x) {
	BYTE y=0;
	int bit[8];
	int i;
	for (i=0;i<8;i++) {
		if (((0x01<<i)&(x))==0) bit[i]=0;
		else bit[i]=1;
	}
	if (bit[3]==1) y|=0x01 ;
	if (bit[0]==1) y|=0x02 ;
	if (bit[1]==1) y|=0x04 ;
	if (bit[6]==1) y|=0x08 ;
	if (bit[5]==1) y|=0x10 ;
	if (bit[7]==1) y|=0x20 ;
	if (bit[2]==1) y|=0x40 ;
	if (bit[4]==1) y|=0x80 ;

	return(y);
}

BYTE encodeByte(BYTE x) {
	BYTE y=0;
	int bit[8];
	int i;
	for (i=0;i<8;i++) {
		if (((0x01<<i)&(x))==0) bit[i]=0;
		else bit[i]=1;
	}
	if (bit[1]==1) y|=0x01 ;
	if (bit[2]==1) y|=0x02 ;
	if (bit[6]==1) y|=0x04 ;
	if (bit[0]==1) y|=0x08 ;
	if (bit[7]==1) y|=0x10 ;
	if (bit[4]==1) y|=0x20 ;
	if (bit[3]==1) y|=0x40 ;
	if (bit[5]==1) y|=0x80 ;

	return(y);
}
#include <math.h>
void scrambleByte(BYTE *x,BYTE *key) {
	float floatVal=(int)*key;
	floatVal=sqrt(floatVal+(float)5.8);
	int intVal=(int)floatVal;
	floatVal-=(float)intVal;
	floatVal*=100;
	intVal=(int)floatVal;
	floatVal-=(float)intVal;
	floatVal*=100;
	intVal=(int)floatVal;
//	floatVal-=(float)intVal;
//	intVal=(int)floatVal;
	*key=(BYTE)intVal;
	*x = *x ^ *key;
}

BEGIN_MESSAGE_MAP(CEnterPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_CANCEL_ENTERPASSWORD, &CEnterPasswordDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ENTERPASSWORD, &CEnterPasswordDlg::OnBnClickedEnterPassword)

END_MESSAGE_MAP()


void CEnterPasswordDlg::OnClose() 
{
	//Anything that needs to occur on closing the application goes here.
	//Free any resources used by previous API calls and still allocated.

	CDialog::OnClose();
}

extern CMenu *pSysMenu;
void CEnterPasswordDlg::OnBnClickedCancel() {
	enterPasswordWinFlag=0;
	pSysMenu->EnableMenuItem(ID_OPTIONS_PASSWORD,	MF_ENABLED);

//	writeStingerCmdFile();
//Kill stinger window manually
	pEnterPasswordWinDlg->DestroyWindow();
//re-enable button for Channels Window
//	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}

void CEnterPasswordDlg::OnBnClickedEnterPassword() {
	CString strVal;
	CEdit *x = (CEdit *)GetDlgItem(IDC_PASSWORD_TEXT);
	x->GetWindowTextA(strVal);
	if (strVal==currentPassword) {
		pPasswordWinDlg = new CPasswordDlg(this);
		BOOL ret=pPasswordWinDlg->Create(IDD_PASSWORDWIN,0);
		if(!ret)   //Create failed.
			AfxMessageBox("Error creating Password Protected Dialog");
		pPasswordWinDlg->ShowWindow(SW_SHOW);
//		pEnterPasswordWinDlg->ShowWindow(SW_HIDE);
		pEnterPasswordWinDlg->DestroyWindow();
	} else {
		AfxMessageBox("Incorrect Password");
//		enterPasswordWinFlag=0;
//		pEnterPasswordWinDlg->DestroyWindow();
//		CDialog::OnClose();
	}
}

CEnterPasswordDlg::CEnterPasswordDlg(CWnd* pParent /*=NULL*/) : CDialog(CEnterPasswordDlg::IDD, pParent)
{
}

void CEnterPasswordDlg::OnOK() {
	int x;
	x=3; // just a place to break
	OnBnClickedEnterPassword();
//	if (m_FreqValue->GetFocus()==NULL) {
//		x=1;
//	} else {
//		x=2;
//	}
//	CDialog::OnOK();
}

//================================================================
// Password Protected Window
//================================================================

CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/) : CDialog(CPasswordDlg::IDD, pParent)
{
//	pPasswordWinDlg = new CPasswordDlg(this);
//	BOOL ret=pPasswordWinDlg->Create(IDD_PASSWORDWIN,0);
//	if(!ret)   //Create failed.
//		AfxMessageBox("Error creating Password Protected Dialog");
//	pEnterPasswordWinDlg->ShowWindow(SW_HIDE);
//	pPasswordWinDlg->ShowWindow(SW_SHOW);
}

BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDPW_SETCLOCK, &CPasswordDlg::OnBnClickedSetClockMain)
//	ON_BN_CLICKED(IDPW_RESTORE_STATE, &CPasswordDlg::OnBnClickedRestoreState)
	ON_EN_CHANGE(IDPW_ENCWRD2, &CPasswordDlg::OnEnChangeEncwrd2)


	ON_NOTIFY(NM_RELEASEDCAPTURE, IDPW_FreqSelect, &CPasswordDlg::OnNMReleasedcapturePwFreqselect)
	ON_BN_CLICKED(IDPW_SetFreq, &CPasswordDlg::OnBnClickedPwSetfreq)
	ON_BN_CLICKED(IDPW_FreqVal1, &CPasswordDlg::OnBnClickedPwfreqval1)
	ON_BN_CLICKED(IDPW_FreqVal2, &CPasswordDlg::OnBnClickedPwfreqval2)
	ON_BN_CLICKED(IDPW_FreqVal3, &CPasswordDlg::OnBnClickedPwfreqval3)
	ON_BN_CLICKED(IDPW_FreqVal4, &CPasswordDlg::OnBnClickedPwfreqval4)
	ON_BN_CLICKED(IDPW_FreqVal5, &CPasswordDlg::OnBnClickedPwfreqval5)
	ON_BN_CLICKED(IDPW_FreqVal6, &CPasswordDlg::OnBnClickedPwfreqval6)
	ON_BN_CLICKED(IDPW_FreqVal7, &CPasswordDlg::OnBnClickedPwfreqval7)
	ON_BN_CLICKED(IDPW_FreqVal8, &CPasswordDlg::OnBnClickedPwfreqval8)
	ON_BN_CLICKED(IDPW_LoadFreqs, &CPasswordDlg::OnBnClickedPwLoadfreqs)
	ON_BN_CLICKED(IDPW_SaveFreqs, &CPasswordDlg::OnBnClickedPwSavefreqs)
	ON_BN_CLICKED(ID_CANCEL_PPWINDOW, &CPasswordDlg::OnBnClickedCancel)
	ON_COMMAND(ID_OPTIONS_CHANGEPASSWORD, &CPasswordDlg::OnMenuChangePassword)
	ON_BN_CLICKED(IDPW_PROCESS, &CPasswordDlg::OnBnClickedPwProcessSDEncWrd)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()




END_MESSAGE_MAP()

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordDlg)
	//}}AFX_DATA_MAP
}
int	passwordWinFlag=0;
BOOL CPasswordDlg::OnInitDialog() {
	pw_FreqVal1 = (CButton*)GetDlgItem(IDPW_FreqVal1);
	pw_FreqVal2 = (CButton*)GetDlgItem(IDPW_FreqVal2);
	pw_FreqVal3 = (CButton*)GetDlgItem(IDPW_FreqVal3);
	pw_FreqVal4 = (CButton*)GetDlgItem(IDPW_FreqVal4);
	pw_FreqVal5 = (CButton*)GetDlgItem(IDPW_FreqVal5);
	pw_FreqVal6 = (CButton*)GetDlgItem(IDPW_FreqVal6);
	pw_FreqVal7 = (CButton*)GetDlgItem(IDPW_FreqVal7);
	pw_FreqVal8 = (CButton*)GetDlgItem(IDPW_FreqVal8);
	pw_setFreq = (CButton*) GetDlgItem(IDPW_SetFreq);
	pw_FreqValue = (CEdit*) GetDlgItem(IDPW_FREQ_VAL_TEXT);

	pw_FreqSelect = (CSliderCtrl*)GetDlgItem(IDPW_FreqSelect);
	pw_FreqSelect->SetRange(1, 8);
	pw_FreqSelect->SetTicFreq(1);
	CPasswordDlg::LoadFreqButtons();

	// Add Menu
	passwordWinFlag=1;
	CMenu myMenu;
	myMenu.LoadMenu(IDR_PASSWORDWINMENU);
	BOOL result = SetMenu(&myMenu);

	return TRUE;
}
////////////////////////////////////////////////////////////////
//Routines for using the Freq Select slider and buttons Follow
////////////////////////////////////////////////////////////////

/* CMainDlg::OnNMReleasedcaptureFreqselect does the following:
	Sets the slider focus on a freq key
	gets the tuneFreqKHz from the setFreqKHz array
	puts the frequency in text window
	sends freq. to Tactical Repeater
	*/

void CPasswordDlg::OnNMReleasedcapturePwFreqselect(NMHDR *pNMHDR, LRESULT *pResult)
{
	int freqPos;
	
	freqPos=9-pw_FreqSelect->GetPos();
	switch(freqPos) {
		case 1:{pw_FreqVal1->SetFocus();break;}
		case 2:{pw_FreqVal2->SetFocus();break;}
		case 3:{pw_FreqVal3->SetFocus();break;}
		case 4:{pw_FreqVal4->SetFocus();break;}
		case 5:{pw_FreqVal5->SetFocus();break;}
		case 6:{pw_FreqVal6->SetFocus();break;}
		case 7:{pw_FreqVal7->SetFocus();break;}
		case 8:{pw_FreqVal8->SetFocus();break;}
	}
	tuneFreqKHz=setFreqKHz[freqPos-1];
    freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars); 
//	displayFreqKHz=tuneFreqKHz;

	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();

	
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

/* CMainDlg::OnBnClickedSetfreq does the following:
	Gets freq text from the text window
	converts to tuneFreqKHz
	stores in setFreqKHz
	inserts freq text into button
	sends freq command to Tactical Repeater
	*/

void CPasswordDlg::OnBnClickedPwSetfreq()
{
	// TODO: Add your control notification handler code here
	ULONG freqVal;
	int freqPos;
//	CEdit* m_FreqValue = (CEdit*) GetDlgItem(IDC_FREQ_VAL_TEXT);
	pw_FreqValue->GetWindowText(freqpwValString); 

		// Convert the string in the edit box to an integer.

	freqpwValDouble = strtod(freqpwValString, 0); //convert text to MHz float
	tuneFreqKHz=(ULONG)(1000.0*freqpwValDouble);  //convert to KHz integer

	limitFreqValRange(&tuneFreqKHz);
	freqPos=9-pw_FreqSelect->GetPos();
	setFreqKHz[freqPos-1]=tuneFreqKHz;
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	insertTextIntoPwFreqButton(freqPos,freqpwValChars);
	CMainDlg::insertTextIntoFreqButton(freqPos,freqpwValChars);

	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();

}

//void updateFreqTextDisplay() {
//	if (displayFreqKHz!=xx) {
//	freqKHzToMHzString(respFreqKHz,freqValChars);
//	m_FreqValue->SetWindowText(freqValChars);
//}

void CPasswordDlg::insertTextIntoPwFreqButton(int pos, char *text) {
	switch (pos) {
		case 1: {
			pw_FreqVal1->SetWindowText(text);break;}
		case 2: {
			pw_FreqVal2->SetWindowText(text); break;}
		case 3: {
			pw_FreqVal3->SetWindowText(text); break;}
		case 4: {
			pw_FreqVal4->SetWindowText(text);	break;}
		case 5: {
			pw_FreqVal5->SetWindowText(text); break;}
		case 6: {
			pw_FreqVal6->SetWindowText(text); break;}
		case 7: {
			pw_FreqVal7->SetWindowText(text); break;}
		case 8: {
			pw_FreqVal8->SetWindowText(text); break;}
	}
}
void CPasswordDlg::OnBnClickedPwLoadfreqs()
{
//	CMainDlg::readFreqFile();
	CPasswordDlg::LoadFreqButtons();
}

void CPasswordDlg::LoadFreqButtons()
{
	int i;
	ULONG value;
	int freqpos;

	for (i=0;i<8;i++) {
			  value=setFreqKHz[i];
			  freqKHzToMHzString(value,freqpwValChars);
			  if (i==0) pw_FreqVal1->SetWindowText(freqpwValChars);
			  if (i==1) pw_FreqVal2->SetWindowText(freqpwValChars);
			  if (i==2) pw_FreqVal3->SetWindowText(freqpwValChars);
			  if (i==3) pw_FreqVal4->SetWindowText(freqpwValChars);
			  if (i==4) pw_FreqVal5->SetWindowText(freqpwValChars);
			  if (i==5) pw_FreqVal6->SetWindowText(freqpwValChars);
			  if (i==6) pw_FreqVal7->SetWindowText(freqpwValChars);
			  if (i==7) pw_FreqVal8->SetWindowText(freqpwValChars);
			freqpos=i+1;
			  insertTextIntoPwFreqButton(freqpos,freqpwValChars);
			}
}

void writeScorpFreqFile();

void CPasswordDlg::OnBnClickedPwSavefreqs()
{
	writeScorpFreqFile();
}
void CPasswordDlg::OnBnClickedPwfreqval1() {
	pw_FreqSelect->SetPos(8);
	pw_FreqVal1->SetFocus();
	tuneFreqKHz=setFreqKHz[0];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedPwfreqval2() {
	pw_FreqSelect->SetPos(7);
	pw_FreqVal2->SetFocus();
	tuneFreqKHz=setFreqKHz[1];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedPwfreqval3() {
	pw_FreqSelect->SetPos(6);
	pw_FreqVal3->SetFocus();
	tuneFreqKHz=setFreqKHz[2];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedPwfreqval4() {
	pw_FreqSelect->SetPos(5);
	pw_FreqVal4->SetFocus();
	tuneFreqKHz=setFreqKHz[3];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedPwfreqval5() {
	pw_FreqSelect->SetPos(4);
	pw_FreqVal5->SetFocus();
	tuneFreqKHz=setFreqKHz[4];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedPwfreqval6() {
	pw_FreqSelect->SetPos(3);
	pw_FreqVal6->SetFocus();
	tuneFreqKHz=setFreqKHz[5];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedPwfreqval7() {
	pw_FreqSelect->SetPos(2);
	pw_FreqVal7->SetFocus();
	tuneFreqKHz=setFreqKHz[6];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedPwfreqval8() {
	pw_FreqSelect->SetPos(1);
	pw_FreqVal8->SetFocus();
	tuneFreqKHz=setFreqKHz[7];
	freqKHzToMHzString(tuneFreqKHz,freqpwValChars);
	pw_FreqValue->SetWindowText(freqpwValChars);
	CMainDlg::setFreqOperCmd();
//	if (m_stingerCmd->GetCheck()==BST_CHECKED) updateStingerStatusLED();
}

void CPasswordDlg::OnBnClickedCancel() {
	enterPasswordWinFlag=0;
//	writeStingerCmdFile();
//Kill stinger window manually
	pPasswordWinDlg->DestroyWindow();
//re-enable button for Channels Window
//	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}

afx_msg  void CPasswordDlg::OnClose() 
{
	//Anything that needs to occur on closing the application goes here.
	//Free any resources used by previous API calls and still allocated.
	continuousFlag=1; //re-activate updating signal and audio levels

	CDialog::OnClose();
}


void CPasswordDlg::OnMenuChangePassword() {
	pChangePasswordWinDlg = new CChangePasswordDlg(this);
	BOOL ret=pChangePasswordWinDlg->Create(IDD_CHANGEPASSWORDWIN,0);
	if(!ret)   //Create failed.
		AfxMessageBox("Error creating Change Password Dialog");
	pChangePasswordWinDlg->ShowWindow(SW_SHOW);

}
void CPasswordDlg::OnBnClickedPwProcessSDEncWrd() {

	char *end;
	CString strval;
	char strvalch;
	unsigned long int strvalul;

	outMsgStr[0]=CMD_LOAD_SD_ENCRYPT_KEY_1; //"dp" command
	outMsgStr[1]=CMD_LOAD_SD_ENCRYPT_KEY_2; // "dp" command

	pw_EncWrd1 = (CEdit*) GetDlgItem(IDPW_ENCWRD1);
	pw_EncWrd1->GetWindowText(strval);
	strvalul = strtoul(strval, &end, 16);
	if (strvalul!= ULONG_MAX ) {
		outMsgStr[2] = (char)(strvalul & 0x000000ff);
		outMsgStr[3] = (char)((strvalul & 0x0000ff00)>>8);
		outMsgStr[4] = (char)((strvalul & 0x00ff0000)>>16);
		outMsgStr[5] = (char)((strvalul & 0xff000000)>>24);
	} else 	AfxMessageBox("Entry error key 1");
/*	strvalul=(atol(outMsgStr[2])& 0x000000ff);
	strvalul+=(atol(outMsgStr[3])& 0x000000ff)<<8;
	strvalul+=(atol(outMsgStr[4])& 0x000000ff)<<16;
	strvalul+=(atol(outMsgStr[5])& 0x000000ff)<<24;
	strVal.Format("0x%8x",strvalul);
*/
	pw_EncWrd1->SetWindowText (strval);
	pw_EncWrd2 = (CEdit*) GetDlgItem(IDPW_ENCWRD2);
	pw_EncWrd2->GetWindowText(strval);
	if ((strvalul = strtoul(strval, &end, 16))!= ULONG_MAX ) {
		outMsgStr[6] = (char)(strvalul & 0x000000ff);
		outMsgStr[7] = (char)((strvalul & 0x0000ff00)>>8);
		outMsgStr[8] = (char)((strvalul & 0x00ff0000)>>16);
		outMsgStr[9] = (char)((strvalul & 0xff000000)>>24);
	} else AfxMessageBox("Entry error key 2");
	pw_EncWrd3 = (CEdit*) GetDlgItem(IDPW_ENCWRD3);
	pw_EncWrd3->GetWindowText(strval);
	if ((strvalul = strtoul(strval, &end, 16))!= ULONG_MAX ) {
		outMsgStr[10] = (char)(strvalul & 0x000000ff);
		outMsgStr[11] = (char)((strvalul & 0x0000ff00)>>8);
		outMsgStr[12] = (char)((strvalul & 0x00ff0000)>>16);
		outMsgStr[13] = (char)((strvalul & 0xff000000)>>24);
	} else AfxMessageBox("Entry error key 3");
	pw_EncWrd4 = (CEdit*) GetDlgItem(IDPW_ENCWRD4);
	pw_EncWrd4->GetWindowText(strval);
	if ((strvalul = strtoul(strval, &end, 16))!= ULONG_MAX ) {
		outMsgStr[14] = (char)(strvalul & 0x000000ff);
		outMsgStr[15] = (char)((strvalul & 0x0000ff00)>>8);
		outMsgStr[16] = (char)((strvalul & 0x00ff0000)>>16);
		outMsgStr[17] = (char)((strvalul & 0xff000000)>>24);
	} else AfxMessageBox("Entry error key 4");

	CMainDlg::writeCmd(CMD_LOAD_SD_ENCRYPT_LEN);

}


//================================================================
// Change Password Window
//================================================================

CChangePasswordDlg::CChangePasswordDlg(CWnd* pParent /*=NULL*/) : CDialog(CChangePasswordDlg::IDD, pParent)
{
//	pPasswordWinDlg = new CPasswordDlg(this);
//	BOOL ret=pPasswordWinDlg->Create(IDD_PASSWORDWIN,0);
//	if(!ret)   //Create failed.
//		AfxMessageBox("Error creating Password Protected Dialog");
//	pEnterPasswordWinDlg->ShowWindow(SW_HIDE);
//	pPasswordWinDlg->ShowWindow(SW_SHOW);
}
BEGIN_MESSAGE_MAP(CChangePasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CANCEL_CHANGEPASSWORD, &CChangePasswordDlg::OnBnClickedCancel)
//	ON_COMMAND(ID_OPTIONS_CHANGEPASSWORD, &CPasswordDlg::OnMenuChangePassword)
	ON_BN_CLICKED(IDC_CHANGEPASSWORD, &CChangePasswordDlg::OnBnClickedChangePassword)
END_MESSAGE_MAP()
int changePasswordWinFlag;
void CChangePasswordDlg::OnBnClickedCancel() {
	changePasswordWinFlag=0;
//	writeStingerCmdFile();
//Kill stinger window manually
	pChangePasswordWinDlg->DestroyWindow();
//re-enable button for Channels Window
//	m_stingerWinButton.EnableWindow(TRUE);

	CDialog::OnClose();
}
void CChangePasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordDlg)
	//}}AFX_DATA_MAP
}
CEdit *oldPW,*newPW,*newConfPW;
BOOL CChangePasswordDlg::OnInitDialog() {
	// Add Menu
//	CMenu myMenu;
//	myMenu.LoadMenu(IDR_PASSWORDWINMENU);
//	BOOL result = SetMenu(&myMenu);
	changePasswordWinFlag=0;
	oldPW = (CEdit*)GetDlgItem(IDC_OLD_PASSWORD_TEXT);
	newPW = (CEdit *)GetDlgItem(IDC_NEW_PASSWORD_TEXT);
	newConfPW = (CEdit *)GetDlgItem(IDC_REENTER_NEW_PASSWORD_TEXT);

	return TRUE;
}


int readPasswordFile() {
	FILE *fp=fopen("password.dat","r");
	BYTE oneByte,keyByte;
	int count,byteCount;

	if (fp!=0) {
		count=fread(&oneByte,1,1,fp);
		if (count==1) {
			oneByte=decodeByte(oneByte);
			currentPassword=(CString)((char)oneByte);
			keyByte=oneByte;
		}
		byteCount=1;
		while (count==1) {
			count=fread(&oneByte,1,1,fp);
			if (count==1) {
				byteCount++;
				scrambleByte(&oneByte,&keyByte);
				oneByte=decodeByte(oneByte);
				currentPassword+=(CString)((char)oneByte);
			}
		}
		if (byteCount!=16) {
			currentPassword=_T("xyzpdq");
			fclose(fp);
			return(0);
		}
		fclose(fp);
		return(1);
	} else {
		currentPassword=_T("xyzpdq");
		return(0);
	}
}

int writePasswordFile() {
	FILE *fp=fopen("password.dat","w");
	BYTE oneByte,keyByte;
	int count,byteCount;

	if (fp!=0) {
		oneByte=(BYTE)currentPassword.GetAt(0);
		keyByte=oneByte;
		oneByte=encodeByte(oneByte);
		count=fwrite(&oneByte,1,1,fp);
		if (count!=1) {
			fclose(fp);
			return(0);
		}
		byteCount=1;
		while (byteCount<16) {
			if (byteCount>currentPassword.GetLength()) {
				oneByte=0;
			} else {
				oneByte=(BYTE)currentPassword.GetAt(byteCount);
			}
			oneByte=encodeByte(oneByte);
			scrambleByte(&oneByte,&keyByte);
			count=fwrite(&oneByte,1,1,fp);
			if (count==1) {
				byteCount++;
			} else {
				fclose(fp);
				return(0);
			}
		}
		fclose(fp);
		return(1);
	}
	return(0);
}

afx_msg void CChangePasswordDlg::OnBnClickedChangePassword() {
	CString oldPassword;
	CString newPassword;
	CString newConfPassword;

	oldPW->GetWindowTextA(oldPassword);
	newPW->GetWindowTextA(newPassword);
	newConfPW->GetWindowTextA(newConfPassword);

	if (oldPassword!=currentPassword) {
		AfxMessageBox("Incorrect Password");
		return;
	}
	if (newPassword!=newConfPassword) {
		AfxMessageBox("New Passwords Do Not Match");
		return;
	}
	currentPassword=newPassword;
	writePasswordFile();
	AfxMessageBox("Password Changed");

	OnBnClickedCancel();
}

void CChangePasswordDlg::OnOK() {
	OnBnClickedChangePassword();
}


extern int setSysClkWinFlag;

extern char outMsgStr[];

void CPasswordDlg::OnBnClickedRestoreState()
{
	outMsgStr[0]=CMD_DEFAULT_STATE_SET_1; //"cz" command
	outMsgStr[1]=CMD_DEFAULT_STATE_SET_2; // "cz" command
	CMainDlg::writeCmd(CMD_DEFAULT_STATE_SET_LEN);
}

void CPasswordDlg::OnEnChangeEncwrd2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

extern CSetSysClkDlg *pSetSysClkDlg;
void CPasswordDlg::OnBnClickedSetClockMain(){
	    setSysClkWinFlag=1;
		pSetSysClkDlg = new CSetSysClkDlg((CSetSysClkDlg *)this);
		BOOL ret=pSetSysClkDlg->Create(IDD_SYSCLK_WIN,0);
		if(!ret)   //Create failed.
          AfxMessageBox("Error creating System Clock Set Dialog");
        pSetSysClkDlg->ShowWindow(SW_SHOW);
}


