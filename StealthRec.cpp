#include "stdafx.h"

#include "infinity.h"
#include "infinityDlg.h"
#include "led_defs.h"
#include "julianTimeFunctions.h"
#include "CStingerDlg.h"

int stealthRecordWindowMode=1;
void timeToMeynMinutes(TIME_REC_STRUCT *dayxx, unsigned int32 *meinMinutes);
void meynMinutesToTime(unsigned int32 *meinMinutes, TIME_REC_STRUCT *dayxx);

extern CDC *drawingContextMain;
extern int stealthRecPlayLiveStatus;
extern int stealthRecPlaybackStatus;
extern int stealthRecQual;
extern int stealthRecMode;
void writeStealthRecStatusFile();

void CMainDlg::setStealthRecordWindow() {
	CWnd *xx;
	int hideOrShow;
	if (stealthRecordWindowMode==1) {
		hideOrShow=SW_HIDE;
	} else {
		hideOrShow=SW_SHOW;
	}
	xx=(CWnd*)GetDlgItem(IDC_SDMemUsedBargraph);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RAMMemUsedBargraph);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_SDMEMUSED);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_SDMEMTOTAL);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_TIME_REMAIN);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_TIME);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_FILENAME);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_EDITFILENAME);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_TIME_USED);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_SD_ERROR_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RECORDMODE);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_OVERWRITEWHENFULL);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAY_AUDIO);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_MODE_LIVE);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_MODE_PLAYBACK);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_START);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_STOP);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_CARD_PRESENT_MSG);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_SDERROR_MSG);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RECORD_STATUS_MSG);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RECEIVER_SD_CARD_SECTION);
	if (stealthRecordWindowMode==1) {
		xx->SetWindowTextA("Sleeper (Stealth) Recorder");
	} else {
		xx->SetWindowTextA("RD-1200 Receiver Record");
	}
	xx=(CWnd*)GetDlgItem(IDC_MEMUSEDTEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RAM_USED_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_MBYTES_OF);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_MBYTES_TOTAL);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_TIME_REMAIN_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_TIME_USED_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_NEXT_SD_FILENAME_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_MESSAGE_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_MODE_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_TIME_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PRESS_STOP_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_PLAYBACK_MESSAGE);
	xx->ShowWindow(hideOrShow);


	if (stealthRecordWindowMode==0) {
		hideOrShow=SW_HIDE;
	} else {
		hideOrShow=SW_SHOW;
	}
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_RECORD);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_STOP);
	xx->ShowWindow(hideOrShow);
//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_REWIND);
//	xx->ShowWindow(hideOrShow);
//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_FF2END);
//	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_REC_FILE_NUM_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_REPEAT);
	xx->ShowWindow(hideOrShow);
//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_STARTDATE);
//	xx->ShowWindow(hideOrShow);
//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_STARTTIME);
//	xx->ShowWindow(hideOrShow);
//	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_ONPERIOD);
//	xx->ShowWindow(hideOrShow);

	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_128KBPS);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_96KBPS);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_64KBPS);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_QUAL_32KBPS);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STATICREC_QUALTEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_REC_NEXT_FILE_NUM);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_NEXT_FILE_NUM_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHRECINFO);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_FILE_NUM_LOG_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTH_FILE_LOG_HDR_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_MODE_MONO);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_MODE_STEREO);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STATICREC_MODE_TEXT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_STEALTHREC_PLAY);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RECORDER_MSG);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RECORDER_CARD_PRESENT);
	xx->ShowWindow(hideOrShow);
	xx=(CWnd*)GetDlgItem(IDC_RECEIVER_SD_CARD_SECTION2);
	xx->ShowWindow(hideOrShow);

//	xx=(CWnd*)GetDlgItem(IDC_RECORDER_USB_PRESENT);
//	xx->ShowWindow(hideOrShow);



//	xx=(CWnd*)GetDlgItem(IDC_STEALTH_REC_TIME_TEXT);
//	xx->ShowWindow(hideOrShow);

	::InvalidateRect(m_hWnd,NULL,TRUE);
	this->UpdateWindow();

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
	}

}

CTime startRecTime;
long unsigned int recFileNum=0;
//int recBitRate;
long unsigned int recNextFileNum=1;
extern CEdit *m_stealthRecNextFileNum;
extern CStatic *m_stealthRecInfoText;
extern CMenu myMenu;
extern CListBox *m_recFileNumText;
extern int stealthRecMode;
extern int stealthRecSelInputMode;
extern int stealthRecSelQual;
char modeString[10];
extern int playbackVolume;

void CMainDlg::InitStealthRecStatus() {
	char displayStringx[80];
	char oneLine[85];
	FILE *fp=fopen("RecFileStatus.txt","r");
	char oneChar;
	int len;
	int recBitRate;
	int month,day,year,hours,minutes,seconds;
	if (fp!=0) {
		fscanf(fp,"%c",&oneChar);
		if (oneChar=='R') {
			stealthRecPlaybackStatus=1;
			fscanf(fp,"ecording File T%03d: %d/%d/%d %d:%d:%d  %d Kbps ",&recFileNum,&month,&day,&year,&hours,&minutes,&seconds,&recBitRate);
			if (recBitRate==128) stealthRecSelQual=0;
			else if (recBitRate==128) stealthRecSelQual=1;
			else if (recBitRate==128) stealthRecSelQual=2;
			else stealthRecSelQual=3;

			fscanf(fp,"%c",&oneChar);
			if (oneChar=='M') {
				fscanf(fp,"%c",&oneChar);
				if (oneChar=='i') {
					fscanf(fp,"c\n");
					stealthRecSelInputMode=0;
				} else {
					fscanf(fp,"no\n");
					stealthRecSelInputMode=1;
				}
			} else {
				fscanf(fp,"tereo\n");
				stealthRecSelInputMode=2;
			}
			startRecTime=CTime(year+2000,month,day,hours,minutes,seconds);
			CString s = startRecTime.Format( "%m/%d/%y %H:%M:%S");
			if (stealthRecSelInputMode==0) sprintf(modeString,"Mic");
			else if (stealthRecSelInputMode==1) sprintf(modeString,"Mono");
			else sprintf(modeString,"Stereo");
			sprintf(displayStringx,"Recording File T%03d: %s  %d Kbps %s",recFileNum,s,recBitRate,modeString);
			m_stealthRecInfoText->SetWindowTextA(displayStringx);
			stealthRecordWindowMode=1;
			myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_UNCHECKED | MF_BYCOMMAND);
			myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_CHECKED | MF_BYCOMMAND);

		} else if (oneChar=='P') {
			stealthRecPlaybackStatus=2;
			fgets(oneLine,80,fp);
			len=strlen(oneLine);
			if (len>5) {
				oneLine[len-1]=0;
			}
			sprintf(displayStringx,"P%s",oneLine);
			m_stealthRecInfoText->SetWindowTextA(displayStringx);
			stealthRecordWindowMode=1;
			myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_UNCHECKED | MF_BYCOMMAND);
			myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_CHECKED | MF_BYCOMMAND);

		} else {
			stealthRecPlaybackStatus=0;
			fscanf(fp,"topped\n");
			stealthRecordWindowMode=1;
			myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_UNCHECKED | MF_BYCOMMAND);
			myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_CHECKED | MF_BYCOMMAND);
		}
		fscanf(fp,"Next File Number: %d\n",&recNextFileNum);

		int xx;
		fscanf(fp,"Bit Rate: %d Kbps\n",&xx);
		if (xx==128) stealthRecQual=0;
		else if (xx==96) stealthRecQual=1;
		else if (xx==64) stealthRecQual=2;
		else stealthRecQual=3;

		fscanf(fp,"Record Mode: %c",&oneChar);
		if (oneChar=='M') {
			fscanf(fp,"%c",&oneChar);
			if (oneChar=='i') {
				stealthRecMode=0;
				fscanf(fp,"c\n");
			} else {
				fscanf(fp,"no\n");
				stealthRecMode=1;
			}
		} else {
			stealthRecMode=2;
			fscanf(fp,"tereo\n");
		}
		fscanf(fp,"Playback Volume: %d",&playbackVolume);
		if (playbackVolume>31) playbackVolume=31;
		if (playbackVolume<0) playbackVolume=0;

		fclose(fp);
	}
	fp=fopen("RecFileLog.txt","r");
	if (fp!=0) {
		while (TRUE) {
			oneLine[0]=0;
			fgets(oneLine,80,fp);
			len=strlen(oneLine);
			if (len>5) {
				oneLine[len-1]=0;
				m_recFileNumText->AddString(oneLine);
			} else {
				break;
			}
		}
		fclose(fp);
	}
}

/*



*/
void CMainDlg::OnModeSetstealthrecordmode()
{
//	if (stealthRecordWindowMode==0) {
		stealthRecordWindowMode=1;
		myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_UNCHECKED | MF_BYCOMMAND);
		myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_CHECKED | MF_BYCOMMAND);
//	} else {
//		myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_CHECKED | MF_BYCOMMAND);
//		myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_UNCHECKED | MF_BYCOMMAND);
//	}
	setStealthRecordWindow();
}

void CMainDlg::OnModeSetSleepermode()
{
//	if (stealthRecordWindowMode!=0) {
		stealthRecordWindowMode=0;
		myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_CHECKED | MF_BYCOMMAND);
		myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_UNCHECKED | MF_BYCOMMAND);
//	} else {
//		myMenu.CheckMenuItem(ID_SETSLEEPERMODE, MF_UNCHECKED | MF_BYCOMMAND);
//		myMenu.CheckMenuItem(ID_SETSTEALTHRECORDMODE, MF_CHECKED | MF_BYCOMMAND);
//	}
	setStealthRecordWindow();
}

int stealthRecQual=0;
int stealthRecMode=1;
extern CString specialStingerCStrVal;
extern char specialStingerStrVal[];
extern CTime tempTime;
extern CStatic *pStealthRecStartTimeText;
char specialStingerCmdChar;
extern int stealthRecMode;
extern CString playFileString;
extern CButton *m_recordButton;
extern int stealthRecSpecialWinFlag;
extern CButton *m_stealthRecPlaybackVolume;

void CMainDlg::OnStealthRecPlay() {
	int x=1; // just a place to break
	char displayStringx[80];
	int fileNum;
//	if (stealthRecPlaybackStatus==0) {
		x=m_recFileNumText->GetCurSel();
		if (x>=0) {
			CString tempString;
			m_recFileNumText->GetText(x,tempString);
			sscanf(tempString,"T%d ",&fileNum);
			playFileString=tempString.Mid(0,24)+tempString.Mid(35,20);
			stealthRecPlaybackStatus=2;
			setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_GREEN,drawingContextMain);

			specialStingerCmdChar='P';

			if (stealthRecSpecialWinFlag==1) {
				m_stealthRecPlaybackVolume->GetWindowText(displayStringx,3);
				playbackVolume = strtol(displayStringx, 0, 0); //convert to long
				if (playbackVolume>31) {
					playbackVolume=31;
				}
				if (playbackVolume<0) {
					playbackVolume=0;
				}

				
				sprintf(displayStringx,"%d",playbackVolume);
				m_stealthRecPlaybackVolume->SetWindowTextA(displayStringx);
			}

			specialStingerStrVal[0]=(char)((fileNum>>8)& (long unsigned)0x0ff);
			specialStingerStrVal[1]=(char)((fileNum)& (long unsigned)0x0ff);
			specialStingerStrVal[2]=(char)playbackVolume;
			specialStingerStrVal[3]=(char)0;
			specialStingerStrVal[4]=(char)0;

		
			sprintf(displayStringx,"Playing File %s",playFileString);
			m_stealthRecInfoText->SetWindowTextA(displayStringx);

			writeStealthRecStatusFile();
			CMainDlg::outputStingerCmd(STINGER_SPECIAL);
		}
//	}
}


void CMainDlg::OnStealthRecRecord() {
	char displayStringx[80];
	int recBitRate;
	m_stealthRecNextFileNum->GetWindowText(displayStringx,3);
	recNextFileNum = strtol(displayStringx, 0, 0); //convert to long
	if (recNextFileNum>999) {
		recNextFileNum=1;
	}
    recFileNum=recNextFileNum;
	recNextFileNum++;
	sprintf(displayStringx,"%d",recNextFileNum);
	m_stealthRecNextFileNum->SetWindowTextA(displayStringx);

//	if (stealthRecPlaybackStatus==0) {
		stealthRecPlaybackStatus=1;
		specialStingerCmdChar='R';
		setIndicatorLight(STREC_RECORD_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);

		stealthRecSelInputMode=stealthRecMode;
		stealthRecSelQual=stealthRecQual;

		specialStingerStrVal[0]=(char)((recFileNum>>8)& (long unsigned)0x0ff);
		specialStingerStrVal[1]=(char)((recFileNum)& (long unsigned)0x0ff);
		specialStingerStrVal[2]=(char)stealthRecSelQual;
		specialStingerStrVal[3]=(char)stealthRecSelInputMode;
		specialStingerStrVal[4]=(char)0;
//		specialStingerStrVal[1]|=(char)(vox&0x01);

		startRecTime = CTime::GetCurrentTime();
		CString s = startRecTime.Format( "%m/%d/%y %H:%M:%S");
//    char * str = (LPCTSTR) s;

		if (stealthRecSelQual==0) recBitRate=128;
		else if (stealthRecSelQual==1) recBitRate=96;
		else if (stealthRecSelQual==2) recBitRate=64;
		else recBitRate=32;

		if (stealthRecSelInputMode==0) sprintf(modeString,"Mic");
		else if (stealthRecSelInputMode==1) sprintf(modeString,"Mono");
		else sprintf(modeString,"Stereo");
		sprintf(displayStringx,"Recording File T%03d: %s  %d Kbps %s",recFileNum,s,recBitRate,modeString);

		writeStealthRecStatusFile();
//	m_recFileNumText.InsertString(0,displayString);
		m_stealthRecInfoText->SetWindowTextA(displayStringx);

		CMainDlg::outputStingerCmd(STINGER_SPECIAL);
//	}
}


void writeStealthRecStatusFile() {
	int recBitRate;
	if (stealthRecSelInputMode==0) sprintf(modeString,"Mic");
	else if (stealthRecSelInputMode==1) sprintf(modeString,"Mono");
	else sprintf(modeString,"Stereo");
	if (stealthRecSelQual==0) recBitRate=128;
	else if (stealthRecSelQual==1) recBitRate=96;
	else if (stealthRecSelQual==2) recBitRate=64;
	else recBitRate=32;
	FILE *fp=fopen("RecFileStatus.txt","w");
	CString s = startRecTime.Format( "%m/%d/%y %H:%M:%S");
	if (stealthRecPlaybackStatus==1) {
		fprintf(fp,"Recording File T%03d: %s  %d Kbps %s\n",recFileNum,s,recBitRate,modeString);
	} else if (stealthRecPlaybackStatus==2) {
		fprintf(fp,"Playing File %s\n",playFileString);
	} else {
		fprintf(fp,"Stopped\n");
	}
	fprintf(fp,"Next File Number: %d\n",recNextFileNum);

	fprintf(fp,"Bit Rate: ");
	if (stealthRecQual==0)	fprintf(fp,"128 Kbps\n");
	else if (stealthRecQual==1) fprintf(fp,"96 Kbps\n");
	else if (stealthRecQual==2) fprintf(fp,"64 Kbps\n");
	else fprintf(fp,"32 Kbps\n");

	fprintf(fp,"Record Mode: ");
    if (stealthRecMode==0) fprintf(fp,"Mic\n");
    else if (stealthRecMode==1) fprintf(fp,"Mono\n");
    else fprintf(fp,"Stereo\n");
	fprintf(fp,"Playback Volume: %d\n",playbackVolume);
	fclose(fp);
}

void CMainDlg::OnStealthRecStop(){
	char displayStringx[80];
	int recBitRate;
	specialStingerCmdChar='S';
	if (stealthRecPlaybackStatus==2) {
		specialStingerStrVal[0]=0xff;
	} else {
		specialStingerStrVal[0]=0;
	}
	specialStingerStrVal[1]=(char)0;
	specialStingerStrVal[1]|=(char)0;

	specialStingerStrVal[2]=(char)0;
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);

	if (stealthRecPlaybackStatus==1) {
		stealthRecPlaybackStatus=0;
		setIndicatorLight(STREC_RECORD_STATUS_LED,LED_DARK_RED,drawingContextMain);
		sprintf(displayStringx," ");
		m_stealthRecInfoText->SetWindowTextA(displayStringx);
		tempTime = CTime::GetCurrentTime();
		CString s = startRecTime.Format( "%m/%d/%y %H:%M:%S" );
		CTimeSpan elapsedTime=tempTime-startRecTime;
		long int totalDays=elapsedTime.GetDays();
		long int totalHours=elapsedTime.GetHours();
		totalHours+=totalDays*24;


		if (stealthRecSelInputMode==0) sprintf(modeString,"Mic");
		else if (stealthRecSelInputMode==1) sprintf(modeString,"Mono");
		else sprintf(modeString,"Stereo");
		CString ss=elapsedTime.Format("%M:%S");
		if (stealthRecSelQual==0) recBitRate=128;
		else if (stealthRecSelQual==1) recBitRate=96;
		else if (stealthRecSelQual==2) recBitRate=64;
		else recBitRate=32;

		sprintf(displayStringx,"T%03d  %s  %03d:%s  %d Kbps %s",recFileNum,s,totalHours,ss,recBitRate,modeString);
		int recFileLineCount=m_recFileNumText->GetCount();
		m_recFileNumText->AddString(displayStringx);
	
		FILE *fp=fopen("RecFileLog.txt","a");
		fprintf(fp,"T%03d   %s  %03d:%s  %d KBps %s\n",recFileNum,s,totalHours,ss,recBitRate,modeString);
		fclose(fp);

		writeStealthRecStatusFile();

	}
	if (stealthRecPlaybackStatus==2) {
		stealthRecPlaybackStatus=0;
		setIndicatorLight(STREC_PLAYBACK_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
		sprintf(displayStringx," ");
		m_stealthRecInfoText->SetWindowTextA(displayStringx);

		writeStealthRecStatusFile();

	}

}

extern CDateTimeCtrl* pStealthRecPlayTime;
/*
void CMainDlg::OnStealthRecPlay() {
	stealthRecPlayLiveStatus=1;
//	setIndicatorLight(STREC_PLAY_STATUS_LED,LED_GREEN,drawingContextMain);
//	setIndicatorLight(STREC_LIVE_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
	specialStingerCmdChar='P';
//	specialStingerStrVal[0]=' ';
//	specialStingerStrVal[1]=(char)((recQual&0x03)<<1);
//	specialStingerStrVal[1]|=(char)(vox&0x01);

	CTime tempPlaybackTime;
	pStealthRecPlayTime->GetTime(tempPlaybackTime);

	TIME_REC_STRUCT sealthRecordPlaybackTimeDate;
	sealthRecordPlaybackTimeDate.dateYear=tempPlaybackTime.GetYear()-2000;
	sealthRecordPlaybackTimeDate.dateMonth=tempPlaybackTime.GetMonth();
	sealthRecordPlaybackTimeDate.dateDay=tempPlaybackTime.GetDay();
	sealthRecordPlaybackTimeDate.timeHour=tempPlaybackTime.GetHour();
	sealthRecordPlaybackTimeDate.timeMinute=tempPlaybackTime.GetMinute();
	sealthRecordPlaybackTimeDate.timeSecond=tempPlaybackTime.GetSecond();

	long unsigned stealthRecMeinMinutesVal;
	timeToMeynMinutes(&sealthRecordPlaybackTimeDate,&stealthRecMeinMinutesVal);
	specialStingerStrVal[0]=(char)((stealthRecMeinMinutesVal>>16)&0x0ff);
	specialStingerStrVal[1]=(char)((stealthRecMeinMinutesVal>>8)&0x0ff);
	specialStingerStrVal[2]=(char)(stealthRecMeinMinutesVal&0x0ff);
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;
	CMainDlg::outputStingerCmd(STINGER_SPECIAL);

}
*/

void CMainDlg::OnStealthRecLive(){
	stealthRecPlayLiveStatus=0;
	setIndicatorLight(STREC_PLAY_STATUS_LED,LED_DARK_GREEN,drawingContextMain);
	setIndicatorLight(STREC_LIVE_STATUS_LED,LED_GREEN,drawingContextMain);
	specialStingerCmdChar='L';
//	specialStingerStrVal[0]=' ';
//	specialStingerStrVal[1]=(char)((recQual&0x03)<<1);
//	specialStingerStrVal[1]|=(char)(vox&0x01);
	CTime tempPlaybackTime;
	pStealthRecPlayTime->GetTime(tempPlaybackTime);

	TIME_REC_STRUCT sealthRecordPlaybackTimeDate;
	sealthRecordPlaybackTimeDate.dateYear=tempPlaybackTime.GetYear()-2000;
	sealthRecordPlaybackTimeDate.dateMonth=tempPlaybackTime.GetMonth();
	sealthRecordPlaybackTimeDate.dateDay=tempPlaybackTime.GetDay();
	sealthRecordPlaybackTimeDate.timeHour=tempPlaybackTime.GetHour();
	sealthRecordPlaybackTimeDate.timeMinute=tempPlaybackTime.GetMinute();
	sealthRecordPlaybackTimeDate.timeSecond=tempPlaybackTime.GetSecond();

	long unsigned stealthRecMeinMinutesVal;
	timeToMeynMinutes(&sealthRecordPlaybackTimeDate,&stealthRecMeinMinutesVal);
	specialStingerStrVal[0]=(char)((stealthRecMeinMinutesVal>>16)&0x0ff);
	specialStingerStrVal[1]=(char)((stealthRecMeinMinutesVal>>8)&0x0ff);
	specialStingerStrVal[2]=(char)(stealthRecMeinMinutesVal&0x0ff);
	specialStingerStrVal[3]=(char)0;
	specialStingerStrVal[4]=(char)0;

	CMainDlg::outputStingerCmd(STINGER_SPECIAL);

}
void CMainDlg::OnStealthRecRewind(){}
void CMainDlg::OnStealthRecFF2End(){}
void CMainDlg::OnStealthRecRepeat(){}
void CMainDlg::OnStealthRecQual128Kbps(){
	CButton *xx;
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_128KBPS);
	xx->SetCheck(BST_CHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_96KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_64KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_32KBPS);
	xx->SetCheck(BST_UNCHECKED);
	stealthRecQual=0;
	writeStealthRecStatusFile();
}
void CMainDlg::OnStealthRecQual96Kbps(){
	CButton *xx;
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_128KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_96KBPS);
	xx->SetCheck(BST_CHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_64KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_32KBPS);
	xx->SetCheck(BST_UNCHECKED);
	stealthRecQual=1;
	writeStealthRecStatusFile();
}

void CMainDlg::OnStealthRecQual64Kbps(){
	CButton *xx;
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_128KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_96KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_64KBPS);
	xx->SetCheck(BST_CHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_32KBPS);
	xx->SetCheck(BST_UNCHECKED);
	stealthRecQual=2;
	writeStealthRecStatusFile();
}

void CMainDlg::OnStealthRecQual32Kbps(){
	CButton *xx;
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_128KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_96KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_64KBPS);
	xx->SetCheck(BST_UNCHECKED);
	xx=(CButton*)GetDlgItem(IDC_STEALTHREC_QUAL_32KBPS);
	xx->SetCheck(BST_CHECKED);
	stealthRecQual=3;
	writeStealthRecStatusFile();
}

extern CButton *m_stealthRecSourceMono;
extern CButton *m_stealthRecSourceStereo;

void CMainDlg::OnStealthRecModeMono() {
	m_stealthRecSourceMono->SetCheck(BST_CHECKED);
	m_stealthRecSourceStereo->SetCheck(BST_UNCHECKED);
	stealthRecMode=1;
	writeStealthRecStatusFile();
}
void CMainDlg::OnStealthRecModeStereo() {
	m_stealthRecSourceMono->SetCheck(BST_UNCHECKED);
	m_stealthRecSourceStereo->SetCheck(BST_CHECKED);
	stealthRecMode=2;
	writeStealthRecStatusFile();
}


TIME_REC_STRUCT meynEpochDay={1,1,16,0,0,0}; // January 1, 2016 12:00:00 AM

void timeToMeynMinutes(TIME_REC_STRUCT *dayxx, unsigned int32 *meinMinutes) {
	unsigned int32 testJulian;
	unsigned int32 meinEpochJulian;
	timeToJulian(dayxx,&testJulian);
	timeToJulian(&meynEpochDay,&meinEpochJulian);
	testJulian-=meinEpochJulian;
	*meinMinutes=testJulian/60;
}

void meynMinutesToTime(unsigned int32 *meinMinutes, TIME_REC_STRUCT *dayxx) {
	unsigned int32 testJulian;
	unsigned int32 meinEpochJulian;
	testJulian= *meinMinutes * 60;
	timeToJulian(&meynEpochDay,&meinEpochJulian);
	testJulian+=meinEpochJulian;
	julianToTime(&testJulian,dayxx);
}
void timeToMeynMinutes(TIME_REC_STRUCT *dayxx, unsigned int32 *meinMinutes);
void meynMinutesToTime(unsigned int32 *meinMinutes, TIME_REC_STRUCT *dayxx);
