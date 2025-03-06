/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog used to display channels

/*class CScanView : public CView {
}
*/
#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
#include "cDebugWinDlg.h"
#include "cPlaybackDlg.h"
#include "msg_defs.h"
#include "julianTimeFunctions.h"


extern int playbackWinFlag;
//extern CButton m_playbackWin;
extern CPlaybackDlg *playbackWinDlg;

BEGIN_MESSAGE_MAP(CPlaybackDlg, CDialog)
//{{AFX_MSG_MAP(CScanDlg)
//		ON_WM_TIMER()
		ON_WM_CLOSE()
	// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_PLAYBACKCLOSE, &CPlaybackDlg::OnBnClickedPlaybackClose)
	ON_BN_CLICKED(ID_PLAYBACKSTOP, &CPlaybackDlg::OnBnClickedPlaybackstop)
	ON_BN_CLICKED(ID_PLAYBACKSTART, &CPlaybackDlg::OnBnClickedPlaybackstart)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_PLAYBACKTIME, &CPlaybackDlg::OnDtnDatetimechangePlaybacktime)
END_MESSAGE_MAP()


CPlaybackDlg::CPlaybackDlg() : CDialog(CPlaybackDlg::IDD)
{
}

void CPlaybackDlg::DoDataExchange(CDataExchange* pDX)
{
//	DDX_Control(pDX, IDC_PLAYBACK_MSG, m_playbackMsg);
	CDialog::DoDataExchange(pDX);
}

extern CDateTimeCtrl* pPlaybackTime;
extern CStatic *m_playbackMsg;

BOOL CPlaybackDlg::OnInitDialog() {
	playbackWinFlag=1;			// Set flag

	pPlaybackTime=(CDateTimeCtrl *)GetDlgItem(IDC_PLAYBACKTIME);
	pPlaybackTime->SetFormat(_T("dd-MMM-yyyy hh:mm:ss tt "));

	m_playbackMsg = (CStatic*)GetDlgItem(IDC_PLAYBACK_MSG);

	m_playbackMsg->SetWindowTextA("Starting playback...");

//	pPlaybackTime->EnableWindow(FALSE);
	return TRUE;
}




afx_msg void CPlaybackDlg::OnClose() {
//	playbackWinFlag=0;
//	m_playbackWin.EnableWindow(TRUE);//re-enable button for Scan Window
	OnBnClickedPlaybackClose();
//	CDialog::OnClose();
}

extern char outMsgStr[];
extern int desiredPlaybackMode;
extern int endPlaybackFlag;
extern int stopPlaybackFlag;

void CPlaybackDlg::OnBnClickedPlaybackClose()
{

	m_playbackMsg->SetWindowTextA("Ending playback...");
	desiredPlaybackMode=3;
	endPlaybackFlag=1;
	CMainDlg::playbackStartCmd();

//	CDialog::OnClose();
}


void timeToJulian(TIME_REC_STRUCT *timeVal, unsigned int32 *timeJulian) {
	unsigned int32 longTempVal;
   unsigned int8 tempVal;
   tempVal=(unsigned int8)(timeVal->dateYear);
   longTempVal=(unsigned int32)tempVal; // now equals number of years since 1/1/00
   longTempVal*=(unsigned int32)365; // now equals number of days since 1/1/00
   if (tempVal>(unsigned int8)1) {
      tempVal--;
      tempVal>>=2;
      tempVal++;
      longTempVal+=(unsigned int32)tempVal; // add leap days
   }

   tempVal=(unsigned int8)(timeVal->dateMonth);
   if (tempVal>1) {
      longTempVal+=(unsigned int32)31; // add days January
   }
   if (tempVal>2) {
      longTempVal+=(unsigned int32)28; // add Feburary
      if (((timeVal->dateYear)&0x03)==0) {
         longTempVal+=(unsigned int32)1; // add leap day
      }
   }
   if (tempVal>3) {
      longTempVal+=(unsigned int32)31;
   }
   if (tempVal>4) {
      longTempVal+=(unsigned int32)30;
   }
   if (tempVal>5) {
      longTempVal+=(unsigned int32)31;
   }
   if (tempVal>6) {
      longTempVal+=(unsigned int32)30;
   }
   if (tempVal>7) {
      longTempVal+=(unsigned int32)31;
   }
   if (tempVal>8) {
      longTempVal+=(unsigned int32)31;
   }
   if (tempVal>9) {
      longTempVal+=(unsigned int32)30;
   }
   if (tempVal>10) {
      longTempVal+=(unsigned int32)31;
   }
   if (tempVal>11) {
      longTempVal+=(unsigned int32)30;
   }
   longTempVal+=(unsigned int32)((timeVal->dateDay)-1);
   longTempVal*=(unsigned int32)24;
   longTempVal+=(unsigned int32)(timeVal->timeHour);
   longTempVal*=(unsigned int32)60;
   longTempVal+=(unsigned int32)(timeVal->timeMinute);
   longTempVal*=(unsigned int32)60;
   longTempVal+=(unsigned int32)(timeVal->timeSecond);
   (*timeJulian)=longTempVal;
}

void julianToTime(unsigned int32 *timeJulian,TIME_REC_STRUCT *timeVal) {
   double tempFloatVal;
   unsigned int32 numberDays,numberSecs;
   unsigned long tempLongVal;
   tempLongVal=(*timeJulian);
   tempFloatVal=(double)tempLongVal/(double)86400;
   numberDays=(unsigned int32)tempFloatVal;
   numberSecs=tempLongVal-(numberDays*(unsigned int32)86400);
   tempFloatVal=(double)numberSecs/(double)3600;
   timeVal->timeHour=(unsigned int8)tempFloatVal;
   numberSecs-=(unsigned int32)(timeVal->timeHour)*3600;
   tempFloatVal=(double)numberSecs/(double)60;
   timeVal->timeMinute=(unsigned int8)tempFloatVal;
   numberSecs-=(unsigned int32)(timeVal->timeMinute)*60;
   timeVal->timeSecond=numberSecs;
   tempFloatVal=(double)numberDays/((double)365*(double)4+(double)1);
   tempLongVal=(unsigned int32)tempFloatVal;
   numberDays-=(tempLongVal*((unsigned int32)365*(unsigned int32)4+(unsigned int32)1));
   timeVal->dateYear=(int8)4*(int8)tempLongVal;
   if (numberDays>=(unsigned int32)366) {
      numberDays-=(unsigned int32)366;
      (timeVal->dateYear)++;
      if (numberDays>=(unsigned int32)365) {
         numberDays-=(unsigned int32)365;
         (timeVal->dateYear)++;
         if (numberDays>=(unsigned int32)365) {
            numberDays-=(unsigned int32)365;
           (timeVal->dateYear)++;
         }
      }
   }
   timeVal->dateMonth=1;
   if (numberDays>=31) {
      (timeVal->dateMonth)++;
      numberDays-=31;
   }
   if (((timeVal->dateYear)&0x03)==0) {
      if (numberDays>=29) {
         (timeVal->dateMonth)++;
         numberDays-=29;
      }
   } else {
      if (numberDays>=28) {
         (timeVal->dateMonth)++;
         numberDays-=28;
      }
   }
   if (numberDays>=31) {
      (timeVal->dateMonth)++;
      numberDays-=31;
   }
   if (numberDays>=30) {
      (timeVal->dateMonth)++;
      numberDays-=30;
   }
   if (numberDays>=31) {
      (timeVal->dateMonth)++;
      numberDays-=31;
   }
   if (numberDays>=30) {
      (timeVal->dateMonth)++;
      numberDays-=30;
   }
   if (numberDays>=31) {
      (timeVal->dateMonth)++;
      numberDays-=31;
   }
   if (numberDays>=31) {
      (timeVal->dateMonth)++;
      numberDays-=31;
   }
   if (numberDays>=30) {
      (timeVal->dateMonth)++;
      numberDays-=30;
   }
   if (numberDays>=31) {
      (timeVal->dateMonth)++;
      numberDays-=31;
   }
   if (numberDays>=30) {
      (timeVal->dateMonth)++;
      numberDays-=30;
   }
   timeVal->dateDay=numberDays+1;
}
   
TIME_REC_STRUCT testDay;
long unsigned testJulian;

void julianTest() {
// Test Leap year from 2/27/08 to 3/1/08
	testJulian=0;
   testDay.dateMonth=1;testDay.dateDay=1;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   timeToJulian(&testDay,&testJulian);

   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

   testDay.dateMonth=2;testDay.dateDay=27;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

   testDay.dateMonth=2;testDay.dateDay=28;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

   testDay.dateMonth=2;testDay.dateDay=29;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

   testDay.dateMonth=3;testDay.dateDay=1;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

// test first day (1/1/00)
   testDay.dateMonth=1;testDay.dateDay=1;testDay.dateYear=0;
   testDay.timeHour=0;testDay.timeMinute=0;testDay.timeSecond=0;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);
   
// test non-leap year from 2/27/09 to 3/1/09
   testDay.dateMonth=2;testDay.dateDay=27;testDay.dateYear=9;
   testDay.timeHour=15;testDay.timeMinute=43;testDay.timeSecond=21;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

   testDay.dateMonth=2;testDay.dateDay=28;testDay.dateYear=9;
   testDay.timeHour=15;testDay.timeMinute=43;testDay.timeSecond=21;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

   testDay.dateMonth=3;testDay.dateDay=1;testDay.dateYear=9;
   testDay.timeHour=15;testDay.timeMinute=43;testDay.timeSecond=21;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

// test from 11:59:59 on 12/31/20 to 12:00:00 1/1/21
   testDay.dateMonth=12;testDay.dateDay=31;testDay.dateYear=20;
   testDay.timeHour=23;testDay.timeMinute=59;testDay.timeSecond=59;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);

   testDay.dateMonth=1;testDay.dateDay=1;testDay.dateYear=21;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   timeToJulian(&testDay,&testJulian);
   testDay.dateMonth=0;testDay.dateDay=0;testDay.dateYear=0;
   testDay.timeHour=00;testDay.timeMinute=00;testDay.timeSecond=00;
   julianToTime(&testJulian,&testDay);
}


void CPlaybackDlg::OnBnClickedPlaybackstop()
{
	desiredPlaybackMode=3;
	stopPlaybackFlag=1;
	m_playbackMsg->SetWindowTextA("Stopping playback...");
	CMainDlg::playbackStartCmd();



}
extern int startPlayingFlag;
extern CDateTimeCtrl* pPlaybackTime;
extern long unsigned playbackJulianVal;

void CPlaybackDlg::OnBnClickedPlaybackstart()
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

void CPlaybackDlg::OnDtnDatetimechangePlaybacktime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
