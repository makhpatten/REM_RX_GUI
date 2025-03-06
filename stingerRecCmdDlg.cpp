#include "stdafx.h"
#include "CStingerDlg.h"
#include "CStingerRecCmdDlg.h"

CStingerRecCmdDlg *pStingerRecWinDlg=(CStingerRecCmdDlg*)0;

CStingerRecCmdDlg::CStingerRecCmdDlg(CWnd* pParent /*=NULL*/):CDialog(CStingerRecCmdDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CChannelsDlg)
	//}}AFX_DATA_INIT
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
//ON_BN_CLICKED(IDC_STINGER_REC_REFRESH, &CStingerRecCmdDlg::OnBnClickedStingerRecRefresh)
ON_BN_CLICKED(IDC_STINGER_REC_ERASEALL, &CStingerRecCmdDlg::OnBnClickedStingerRecEraseall)
ON_WM_TIMER()
END_MESSAGE_MAP()

void prepareStingerRecCmdTxt(/*CString* ,*/int,int,int);
void updateStingerCmdTxt(CListBox*);
CListBox *pStingerCmdTxt;

BOOL CStingerRecCmdDlg::OnInitDialog() {
	CStingerDlg::stingerRecordCmd(3); // The 3 indicates return current stinger cmd
	pStingerCmdTxt=(CListBox*)GetDlgItem(IDC_STINGER_REC_CMD_TEXT);
	updateStingerCmdTxt(pStingerCmdTxt);
	SetTimer(ID_TIMER_STINGER_RECORD, 1000, NULL);
	return TRUE;
}
extern char inMsgParams[];

CString stingerLineStr;
void updateStingerCmdTxt(CListBox *editText) {
	editText->ResetContent();
	if (inMsgParams[1]==0) {
		editText->InsertString(0,"(no command)");
	} else {
		if ((inMsgParams[9]&0x08)!=0) {
			editText->InsertString(-1,"ON command---");
		} else {
			editText->InsertString(-1,"OFF command---");
		}
		stingerLineStr.Format("Address: %1d%1d%1d",
			(int)((inMsgParams[3]>>4)&0x0f),
			(int)((inMsgParams[2]>>0)&0x0f),
			(int)((inMsgParams[2]>>4)&0x0f));
		editText->InsertString(0,stingerLineStr);
		prepareStingerRecCmdTxt(/*&strval,*/(int)1,(int)(inMsgParams[4]&0x10),
			(int)(inMsgParams[4]&0x0f));
		editText->InsertString(-1,stingerLineStr);
		prepareStingerRecCmdTxt(/*&strval,*/(int)2,(int)(inMsgParams[4]&0x20),
			(int)((inMsgParams[5]>>4)&0x0f));
		editText->InsertString(-1,stingerLineStr);
		prepareStingerRecCmdTxt(/*&strval,*/(int)3,(int)(inMsgParams[4]&0x40),
			(int)(inMsgParams[5]&0x0f));
		editText->InsertString(-1,stingerLineStr);
		prepareStingerRecCmdTxt(/*&strval,*/(int)4,(int)(inMsgParams[4]&0x80),
			(int)((inMsgParams[6]>>4)&0x0f));
		editText->InsertString(-1,stingerLineStr);
		prepareStingerRecCmdTxt(/*&strval,*/(int)5,(int)(inMsgParams[3]&0x01),
			(int)(inMsgParams[6]&0x0f));
		editText->InsertString(-1,stingerLineStr);
		prepareStingerRecCmdTxt(/*&strval,*/(int)6,(int)(inMsgParams[3]&0x02),
			(int)((inMsgParams[7]>>4)&0x0f));
		editText->InsertString(-1,stingerLineStr);
		prepareStingerRecCmdTxt(/*&strval,*/(int)7,(int)(inMsgParams[3]&0x04),
			(int)(inMsgParams[7]&0x0f));
		editText->InsertString(-1,stingerLineStr);
		if ((inMsgParams[9]&0x02)!=0) {
			editText->InsertString(-1,"Schedule: ");
			long unsigned numMinutes=(long unsigned)0x0ff&(long unsigned)inMsgParams[10];
			numMinutes<<=8;
			numMinutes+=(long unsigned)0x0ff&(long unsigned)inMsgParams[11];
			numMinutes<<=8;
			numMinutes+=(long unsigned)0x0ff&(long unsigned)inMsgParams[12];
			stingerLineStr.Format("Start Delay: %ld minutes",numMinutes);
			editText->InsertString(-1,stingerLineStr);
			numMinutes=inMsgParams[16];
			numMinutes<<=8;
			numMinutes+=inMsgParams[17];
			stingerLineStr.Format("On Period: %ld minutes",numMinutes);
			editText->InsertString(-1,stingerLineStr);
			numMinutes=(long unsigned)0x0ff&(long unsigned)inMsgParams[13];
			numMinutes<<=8;
			numMinutes+=(long unsigned)0x0ff&(long unsigned)inMsgParams[14];
			numMinutes<<=8;
			numMinutes+=(long unsigned)0x0ff&(long unsigned)inMsgParams[15];
			stingerLineStr.Format("Repeat Period: %ld minutes",numMinutes);
			editText->InsertString(-1,stingerLineStr);
		}
	}
}


void prepareStingerRecCmdTxt(/*CString *str,*/int lineNo,int inputFlag,int outputNibble) {
	CString *str;
	str=&stingerLineStr;
	str->Format("Line %1d:",lineNo);
	if (inputFlag!=0) {
		if (lineNo==1 || lineNo==2) {
			str->Format("%s Open",*str);
		} else {
			str->Format("%s Input",*str);
		}
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
void CStingerRecCmdDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ID_TIMER_STINGER_RECORD) {
		CStingerDlg::stingerRecordCmd(3); // The 3 indicates return current stinger cmd
		updateStingerCmdTxt(pStingerCmdTxt);
		SetTimer(ID_TIMER_STINGER_RECORD, 1000, NULL);
	} else {
		CDialog::OnTimer(nIDEvent);
	}
}
/* now done in onTimer()
void CStingerRecCmdDlg::OnBnClickedStingerRecRefresh()
{
	CStingerDlg::stingerRecordCmd(3); // The 3 indicates return current stinger cmd
	updateStingerCmdTxt(pStingerCmdTxt);
}
*/
void CStingerRecCmdDlg::OnBnClickedStingerRecEraseall()
{
	CStingerDlg::stingerRecordCmd(2); // The 2 indicates erase current stinger command
	updateStingerCmdTxt(pStingerCmdTxt);
}
