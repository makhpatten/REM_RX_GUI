#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
#include "msg_defs.h"
#include "led_defs.h"
#include "CStingerDlg.h"
#include "cdebugwindlg.h"
#include "config.h"

extern CButton *m_stingerCmd;
extern int stingerStatus;
extern CDC *drawingContextMain;
char stinger8bytes[8];
extern CButton *m_stereoOn;
extern CButton *m_swapLr;
extern CSliderCtrl *m_FreqSelect;
int stingerOnFlag=FALSE;
extern char outMsgStr[];
extern CString msgString;
extern char inMsgParams[];
extern CButton *m_stingerOn;
extern CButton *m_stingerOff;
extern CDateTimeCtrl *m_autoOnPeriod;
extern CComboBox *m_autoOnRepeatDays;
extern CComboBox *m_dogLeashDays;
extern CDateTimeCtrl *m_autoOnRepeatHrsMins;

extern CButton *m_onCmd;
extern CButton *m_offCmd;
extern CButton *m_onCmdButton;
extern CButton *m_offCmdButton;

void readStingerCmdFile();
void writeStingerCmdFile();

extern char specialStingerCmdChar;

void CMainDlg::OnBnClickedStingerCmd()
{
	if (m_stingerCmd->GetCheck()==BST_CHECKED)
		m_stingerCmd->SetCheck(BST_UNCHECKED);
	else
		m_stingerCmd->SetCheck(BST_CHECKED);
}

extern CEdit *m_FreqValue;
extern int stingerWinFlag;
//extern CDC *drawingContextWasp;
extern CButton *m_monoOn;
extern CButton *m_setFreq;
extern CButton *m_Filt400HzVerySharp;
extern CButton *m_Filt200HzVerySharp;
extern CButton *m_Filt400HzSharp;
extern CButton *m_Filt200HzSharp;
extern CButton *m_Filt200Hz;
extern CButton *m_Filt100Hz;
extern CButton *m_FiltFlat;
extern CButton *m_FreqVal1;
extern CButton *m_FreqVal2;
extern CButton *m_FreqVal3;
extern CButton *m_FreqVal4;
extern CButton *m_FreqVal5;
extern CButton *m_FreqVal6;
extern CButton *m_FreqVal7;
extern CButton *m_FreqVal8;
extern CDC* drawingContextStinger;

#if TACTICAL_REPEATER_MODE==2
void CMainDlg::updateStingerStatusLED() {
   if (stingerStatus==STINGER_TXMITTING) {
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_BRIGHT_RED,drawingContextMain);

// If stinger window open, set its transmitting indicator to red also
		if (stingerWinFlag==1) {
			CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_BRIGHT_RED,drawingContextStinger);
			m_onCmdButton->EnableWindow(FALSE);
			m_offCmdButton->EnableWindow(FALSE);
			m_onCmd->EnableWindow(FALSE);
			m_offCmd->EnableWindow(FALSE);
		}
		m_stingerOn->EnableWindow(FALSE);
		m_stingerOff->EnableWindow(FALSE);
		if (m_stingerCmd->GetCheck()==BST_CHECKED) {
			m_FreqValue->EnableWindow(FALSE);
			m_swapLr->EnableWindow(FALSE);
			m_FreqSelect->EnableWindow(FALSE);
			m_setFreq->EnableWindow(FALSE);
			m_FreqVal1->EnableWindow(FALSE);
			m_FreqVal2->EnableWindow(FALSE);
			m_FreqVal3->EnableWindow(FALSE);
			m_FreqVal4->EnableWindow(FALSE);
			m_FreqVal5->EnableWindow(FALSE);
			m_FreqVal6->EnableWindow(FALSE);
			m_FreqVal7->EnableWindow(FALSE);
			m_FreqVal8->EnableWindow(FALSE);
			m_stereoOn->EnableWindow(FALSE);
			m_monoOn->EnableWindow(FALSE);
		}
   } else { // Not transmitting
		setIndicatorLight(TRANSMITTER_STATUS_LED,LED_DARK_RED,drawingContextMain);
// If stinger window open, set its transmitting indicator to green also
		if (stingerWinFlag==1) {
			CMainDlg::setIndicatorLight(STINGER_GENERIC_STATUS_LED,LED_DARK_RED,drawingContextStinger);
			m_onCmd->EnableWindow(TRUE);
			m_offCmd->EnableWindow(TRUE);
			m_onCmdButton->EnableWindow(TRUE);
			m_offCmdButton->EnableWindow(TRUE);
		}
		m_FreqValue->EnableWindow(TRUE);
		m_swapLr->EnableWindow(TRUE);
		m_FreqSelect->EnableWindow(TRUE);
		m_stingerOn->EnableWindow(TRUE);
		m_stingerOff->EnableWindow(TRUE);
		m_setFreq->EnableWindow(TRUE);
		m_stereoOn->EnableWindow(TRUE);
		m_monoOn->EnableWindow(TRUE);
		m_FreqVal1->EnableWindow(TRUE);
		m_FreqVal2->EnableWindow(TRUE);
		m_FreqVal3->EnableWindow(TRUE);
		m_FreqVal4->EnableWindow(TRUE);
		m_FreqVal5->EnableWindow(TRUE);
		m_FreqVal6->EnableWindow(TRUE);
		m_FreqVal7->EnableWindow(TRUE);
		m_FreqVal8->EnableWindow(TRUE);
   }
}
#endif

long unsigned customerID=0x021;
extern long unsigned stingerAddress;

extern CComboBox *m_offLine1;
extern CComboBox *m_onLine1;
extern CComboBox *m_offLine2;
extern CComboBox *m_onLine2;
extern CComboBox *m_offLine3;
extern CComboBox *m_onLine3;
extern CComboBox *m_offLine4;
extern CComboBox *m_onLine4;
extern CComboBox *m_offLine5;
extern CComboBox *m_onLine5;
extern CComboBox *m_offLine6;
extern CComboBox *m_onLine6;
extern CComboBox *m_offLine7;
extern CComboBox *m_onLine7;
extern CButton *m_onCmd;
extern CButton *m_offCmd;
extern CButton *m_autoOnEnable;
extern CButton *m_dogLeashEnable;
extern CComboBox *m_autoOnDelayDays;
extern CDateTimeCtrl *m_autoOnDelayHrsMins;
extern CDateTimeCtrl *m_dogLeashHrsMins;
extern int controlTxPower;
extern int sleeper2Power;
extern int ctrlTxMode;

int desiredFreqNum;
extern char specialStingerStrVal[];
void updateStingerAddress();
int stingerAllOff=0;

void CMainDlg::outputStingerCmd(int mode) {

	/* mode=STINGER_TX_SPECIFIC for transmitter specific Stinger command,
   mode=STINGER_GENERIC for generic stinger command */
   int i;
   CString strVal;
	CTime timeValue;


	//	stingerStatus=STINGER_TXMITTING;
	updateStingerAddress();

	if (stingerAllOff==1) {
// byte 0, nibbles 0 & 1: Stinger address (least sig. hex char first) */
		stinger8bytes[0]=(char)(0);
// byte 1, nibble 0: Stinger address (most sig. hex char) */
		stinger8bytes[1]=(char)(0);
	} else {
/*
// byte 0, nibbles 0 & 1: Stinger address (least sig. hex char first) */
		stinger8bytes[0]=(char)(stingerAddress&0x00f);
		stinger8bytes[0]<<=4;
		stinger8bytes[0]|=(char)((stingerAddress>>4)&0x00f);
// byte 1, nibble 0: Stinger address (most sig. hex char) */
		stinger8bytes[1]=(char)((stingerAddress>>8)&0x00f);
		stinger8bytes[1]<<=4;
	}
// byte 1: nibble 1: set lines 7--5 to 0 indicating lines are outputs
	stinger8bytes[1]|=(char)0;
// byte 2: nibble 0: set lines 4--1 to 0 indicating lines are outputs
	stinger8bytes[2]=0;
// byte 6: nibble 0 is Type of message (I'm assuming this is zero)
	stinger8bytes[6]=0;
// byte 6: nibble 1 is the high part of customer ID
	stinger8bytes[6]|=(char)((customerID&0x00f));
// byte 7: nibble 0 is the low part of customer ID
	stinger8bytes[7]=(char)((customerID)&0x0f0);
	if (controlTxPower==1) {
		  stinger8bytes[7]|=0x01; // OR in a "1" for high control tx power
	}

	if (mode==STINGER_GENERIC) {
		if (m_offLine1->GetCurSel()==0) stinger8bytes[2]|=0; //Line 1 OFF=Gnd (00xx)
		else if (m_offLine1->GetCurSel()==1) stinger8bytes[2]|=4;//Line 1 OFF=Bat (01xx)
		else if (m_offLine1->GetCurSel()==2) stinger8bytes[2]|=8;//Line 1 OFF=Lo (10xx)
		else if (m_offLine1->GetCurSel()==3) stinger8bytes[2]|=12;//Line 1 OFF=Hi/Open (11xx)
		if (m_onLine1->GetCurSel()==0) stinger8bytes[2]|=0; //Line 1 ON=Gnd (xx00)
		else if (m_onLine1->GetCurSel()==1) stinger8bytes[2]|=1;//Line 1 ON=Bat (xx01)
		else if (m_onLine1->GetCurSel()==2) stinger8bytes[2]|=2;//Line 1 ON=Lo (xx10)
		else if (m_onLine1->GetCurSel()==3) stinger8bytes[2]|=3;//Line 1 ON=Hi/Open (xx11)
		stinger8bytes[3]=0;
		if (m_offLine2->GetCurSel()==0) stinger8bytes[3]|=0; //Line 2 OFF=Gnd (00xx)
		else if (m_offLine2->GetCurSel()==1) stinger8bytes[3]|=64;//Line 2 OFF=Bat (01xx)
		else if (m_offLine2->GetCurSel()==2) stinger8bytes[3]|=128;//Line 2 OFF=Lo (10xx)
		else if (m_offLine2->GetCurSel()==3) stinger8bytes[3]|=192;//Line 2 OFF=Hi/Open (11xx)
		if (m_onLine2->GetCurSel()==0) stinger8bytes[3]|=0; //Line 2 ON=Gnd (00xx)
		else if (m_onLine2->GetCurSel()==1) stinger8bytes[3]|=16;//Line 2 ON=Bat (xx01)
		else if (m_onLine2->GetCurSel()==2) stinger8bytes[3]|=32;//Line 2 ON=Lo (xx10)
		else if (m_onLine2->GetCurSel()==3) stinger8bytes[3]|=48;//Line 1 ON=Hi/Open (xx11)
		if (m_offLine3->GetCurSel()==0) stinger8bytes[3]|=0; //Line 3 OFF=Gnd (00xx)
		else if (m_offLine3->GetCurSel()==1) stinger8bytes[3]|=4;//Line 3 OFF=Bat (01xx)
		else if (m_offLine3->GetCurSel()==2) stinger8bytes[3]|=8;//Line 3 OFF=Lo (10xx)
		else if (m_offLine3->GetCurSel()==3) stinger8bytes[3]|=12;//Line 3 OFF=Hi (11xx)
		else if (m_offLine3->GetCurSel()==4) {//Line 3=input
			m_onLine3->SetCurSel(4); // Line 3 ON should show input as well
			stinger8bytes[2]|=64;//Line 3 input
		}
		if (m_onLine3->GetCurSel()==0) stinger8bytes[3]|=0; //Line 3 ON=Gnd (00xx)
		else if (m_onLine3->GetCurSel()==1) stinger8bytes[3]|=1;//Line 3 ON=Bat (xx01)
		else if (m_onLine3->GetCurSel()==2) stinger8bytes[3]|=2;//Line 3 ON=Lo (xx10)
		else if (m_onLine3->GetCurSel()==3) stinger8bytes[3]|=3;//Line 3 ON=Hi (xx11)
		else if (m_onLine3->GetCurSel()==4) {//Line 3=input
			m_offLine3->SetCurSel(4); // Line 3 OFF should show input as well
			stinger8bytes[2]|=64;//Line 3 input
		}
		stinger8bytes[4]=0;
		if (m_offLine4->GetCurSel()==0) stinger8bytes[4]|=0; //Line 4 OFF=Gnd (00xx)
		else if (m_offLine4->GetCurSel()==1) stinger8bytes[4]|=64;//Line 4 OFF=Bat (01xx)
		else if (m_offLine4->GetCurSel()==2) stinger8bytes[4]|=128;//Line 4 OFF=Lo (10xx)
		else if (m_offLine4->GetCurSel()==3) stinger8bytes[4]|=192;//Line 4 OFF=Hi (11xx)
		else if (m_offLine4->GetCurSel()==4) {//Line 4=input
			m_onLine4->SetCurSel(4); // Line 4 ON should show input as well
			stinger8bytes[2]|=128;//Line 4 input
		}
		if (m_onLine4->GetCurSel()==0) stinger8bytes[4]|=0; //Line 4 ON=Gnd (00xx)
		else if (m_onLine4->GetCurSel()==1) stinger8bytes[4]|=16;//Line 4 ON=Bat (xx01)
		else if (m_onLine4->GetCurSel()==2) stinger8bytes[4]|=32;//Line 4 ON=Lo (xx10)
		else if (m_onLine4->GetCurSel()==3) stinger8bytes[4]|=48;//Line 4 ON=Hi (xx11)
		else if (m_onLine4->GetCurSel()==4) {//Line 4=input
			m_offLine4->SetCurSel(4); // Line 4 OFF should show input as well
			stinger8bytes[2]|=128;//Line 4 input
		}
		if (m_offLine5->GetCurSel()==0) stinger8bytes[4]|=0; //Line 5 OFF=Gnd (00xx)
		else if (m_offLine5->GetCurSel()==1) stinger8bytes[4]|=8;//Line 5 OFF=Lo (10xx)
		else if (m_offLine5->GetCurSel()==2) stinger8bytes[4]|=12;//Line 5 OFF=Hi (11xx)
		else if (m_offLine5->GetCurSel()==3) {//Line 5=input
			m_onLine5->SetCurSel(3); // Line 5 ON should show input as well
			stinger8bytes[1]|=1;//Line 5 input
		}
		if (m_onLine5->GetCurSel()==0) stinger8bytes[4]|=0; //Line 5 ON=Gnd (00xx)
		else if (m_onLine5->GetCurSel()==1) stinger8bytes[4]|=2;//Line 5 ON=Lo (xx10)
		else if (m_onLine5->GetCurSel()==2) stinger8bytes[4]|=3;//Line 5 ON=Hi (xx11)
		else if (m_onLine5->GetCurSel()==3) {//Line 5=input
			m_offLine5->SetCurSel(3); // Line 5 OFF should show input as well
			stinger8bytes[1]|=1;//Line 5 input
		}
		stinger8bytes[5]=0;
		if (m_offLine6->GetCurSel()==0) stinger8bytes[5]|=0; //Line 6 OFF=Gnd (00xx)
		else if (m_offLine6->GetCurSel()==1) stinger8bytes[5]|=64;//Line 6 OFF=Bat (01xx)
		else if (m_offLine6->GetCurSel()==2) stinger8bytes[5]|=128;//Line 6 OFF=Lo (10xx)
		else if (m_offLine6->GetCurSel()==3) stinger8bytes[5]|=192;//Line 6 OFF=Hi (11xx)
		else if (m_offLine6->GetCurSel()==4) {//Line 6=input
			m_onLine6->SetCurSel(4); // Line 6 ON should show input as well
			stinger8bytes[1]|=2;//Line 6 input
		}
		if (m_onLine6->GetCurSel()==0) stinger8bytes[5]|=0; //Line 6 ON=Gnd (00xx)
		else if (m_onLine6->GetCurSel()==1) stinger8bytes[5]|=16;//Line 6 ON=Bat (xx01)
		else if (m_onLine6->GetCurSel()==2) stinger8bytes[5]|=32;//Line 6 ON=Lo (xx10)
		else if (m_onLine6->GetCurSel()==3) stinger8bytes[5]|=48;//Line 6 ON=Hi (xx11)
		else if (m_onLine6->GetCurSel()==4) {//Line 6=input
			m_offLine6->SetCurSel(4); // Line 6 OFF should show input as well
			stinger8bytes[1]|=2;//Line 6 input
		}
		stinger8bytes[1]|=4;//Line 7 always an input
// byte 7: nibble 1 is action (1000b for ON, 0000b for OFF)
		if (m_onCmd->GetCheck()==BST_CHECKED)  stinger8bytes[7]|=0x08; // or in ON cmd if thats what it is


	} else if (mode==STINGER_SPECIAL) {
		stinger8bytes[1]&=(char)0xf0; // mask out lowest 4 bits
		stinger8bytes[1]|=(char)0x08; // set bit 3 to indicate special command
		switch(specialStingerCmdChar) {
			case 'S': // Stop
			default:
				stinger8bytes[1]|=0;
				break;
			case 'P': // Play
				stinger8bytes[1]|=1;
				break;
			case 'L': // Live
				stinger8bytes[1]|=2;
				break;
			case 'R': // Record
				stinger8bytes[1]|=3;
				break;
			case 'V': // VOX
				stinger8bytes[1]|=4;
				break;
			case 'N': // Now
				stinger8bytes[1]|=5;
				break;
			case 'D': // delete
				stinger8bytes[1]|=6;
				break;
			case 'X': // generic special stinger command
				stinger8bytes[1]|=7;
				break;
		}
		for (i=2;i<7;i++) {
			if (i!=6) {
				stinger8bytes[i]=specialStingerStrVal[i-2];
			} else { // the 5th byte straddles the 13th and 16th nibble (because the customer ID gets punched in by the Ladybug into the 14th and 15th nibble)
				stinger8bytes[6]&=0x0f;
				stinger8bytes[6]|=specialStingerStrVal[4]&0xf0;;
				stinger8bytes[7]&=0xf0;
				stinger8bytes[7]|=specialStingerStrVal[4]&0x0f;;
			}
		}

	} else { // stinger command is Tx specific
// byte 2: nibble 1: set to binary 1001 indicating OFF=logic low (10) and ON=battery (01)
		stinger8bytes[2]|=9;

// byte 3: nibble 0 and 1 determine mono or stereo, left or right
/*
		if (m_stereoOn->GetCheck()==BST_CHECKED) { // If stereo mode
			stinger8bytes[2]|=0x20; // make line 2 an input (setting it high---line 2 is funny that way)
			stinger8bytes[3]=0xbb; // line 2: OFF/ON=1111b, line 3: OFF/ON=1111b (line 2 is an input so its ON/OFF portion is ignored)
		} else if (m_swapLr->GetCheck()==BST_CHECKED) { // if mono, swapped left and right
			stinger8bytes[2]|=0x20; // make line 2 an input (setting it high---line 2 is funny that way)
			stinger8bytes[3]=0xb8; // line 2: OFF/ON=1111b, line 3: OFF/ON=0000b
		} else { // else mono, left and right not swapped
			stinger8bytes[3]=0x8b; // line 2: OFF/ON=0000b, line 3: OFF/ON=1111b
		}
*/
		if (ctrlTxMode==0) { // If stereo mode
//			stinger8bytes[2]|=0x20; // make line 2 an input (setting it high---line 2 is funny that way)
			stinger8bytes[3]=0xbb; // line 2: OFF/ON=1111b, line 3: OFF/ON=1111b (line 2 is an input so its ON/OFF portion is ignored)
		} else if (ctrlTxMode==1) { // if mono left
			stinger8bytes[3]=0x8b; // line 2: OFF/ON=0000b, line 3: OFF/ON=1111b
		} else { // else mono right
			stinger8bytes[3]=0xb8; // line 2: OFF/ON=1111b, line 3: OFF/ON=0000b
		}

// byte 4 and byte 5 determine frequency channel number
// old way:		int freqPos=m_FreqSelect->GetPos();
// new way:
		switch(desiredFreqNum) {
			case 1:
				stinger8bytes[4]=0xbb; // line 4: OFF/ON=1111b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 2:
				stinger8bytes[4]=0x8b; // line 4: OFF/ON=0000b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 3:
				stinger8bytes[4]=0xb8; // line 4: OFF/ON=1111b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 4:
				stinger8bytes[4]=0x88; // line 4: OFF/ON=0000b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0xbb; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 5:
				stinger8bytes[4]=0xbb; // line 4: OFF/ON=1111b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
			case 6:
				stinger8bytes[4]=0x8b; // line 4: OFF/ON=0000b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
			case 7:
				stinger8bytes[4]=0xb8; // line 4: OFF/ON=1111b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
			case 8:
			default:
				stinger8bytes[4]=0x88; // line 4: OFF/ON=0000b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0x8b; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
/*
			case 1:
				stinger8bytes[4]=0xff; // line 4: OFF/ON=1111b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0xff; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 2:
				stinger8bytes[4]=0x0f; // line 4: OFF/ON=0000b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0xff; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 3:
				stinger8bytes[4]=0xf0; // line 4: OFF/ON=1111b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0xff; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 4:
				stinger8bytes[4]=0x00; // line 4: OFF/ON=0000b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0xff; // line 6: OFF/ON=1111b, line 7: OFF/ON=1111b
				break;
			case 5:
				stinger8bytes[4]=0xff; // line 4: OFF/ON=1111b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0x0f; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
			case 6:
				stinger8bytes[4]=0x0f; // line 4: OFF/ON=0000b, line 5: OFF/ON=1111b
				stinger8bytes[5]=0x0f; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
			case 7:
				stinger8bytes[4]=0xf0; // line 4: OFF/ON=1111b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0x0f; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
			case 8:
			default:
				stinger8bytes[4]=0x00; // line 4: OFF/ON=0000b, line 5: OFF/ON=0000b
				stinger8bytes[5]=0x0f; // line 6: OFF/ON=0000b, line 7: OFF/ON=1111b
				break;
*/
		} // end switch
	stinger8bytes[5]&=0xf0;
		if (sleeper2Power==1) {
			stinger8bytes[5]|=0x08; // hi power: lowest nibble of 6th byte in Stinger msg is 0x8 (this has been reversed from original spec, so that cmd tx's without power control will select high power by default)
	   } else {
			stinger8bytes[5]|=0x0b; // lo power: lowest nibble of 6th byte in Stinger msg is 0xB (this has been reversed from original spec, so that cmd tx's without power control will select high power by default)
		}

	// byte 7: nibble 1 is action (1000b for ON, 0000b for OFF)
		if (stingerOnFlag==TRUE) {
			stinger8bytes[7]|=0x08;
		}
	} // end else mode==STINGER_TX_SPECIFIC

// Is it a schedule message?
	if (mode==STINGER_GENERIC && (m_autoOnEnable->GetCheck()==BST_CHECKED)) {
		outMsgStr[0]=CMD_STINGER_SCHEDULE_1; //"rz" command
		outMsgStr[1]=CMD_STINGER_SCHEDULE_2; // "rz" command
		stinger8bytes[7]|=0x02; // OR in schedule bit
		for (i=0;i<8;i++) {
			outMsgStr[i+2]=stinger8bytes[i]; // copy 8 bytes to outMsg
		}

// Add schedule info: Delay time
		m_autoOnDelayDays->GetWindowTextA(strVal);
	    unsigned long timeMinutes = strtol(strVal, 0, 0); //convert to long
		timeMinutes*=24; // convert days to hours
		m_autoOnDelayHrsMins->GetTime(timeValue); // get delay time value
		timeMinutes+=(long unsigned)timeValue.GetHour(); // add in delay hours
		timeMinutes*=(long unsigned)60; // convert to minutes
		timeMinutes+=(long unsigned)timeValue.GetMinute(); // add in minutes
		if (timeMinutes>(long unsigned)0x0ffffff) timeMinutes=0x0ffffff;
		outMsgStr[10]=(char)((timeMinutes>>16)&(long unsigned)0x0ff);
		outMsgStr[11]=(char)((timeMinutes>>8)&(long unsigned)0x0ff);
		outMsgStr[12]=(char)((timeMinutes>>0)&(long unsigned)0x0ff);

// Add schedule info: Repeat time
		if (m_dogLeashEnable->GetCheck()==BST_UNCHECKED) {
			m_autoOnRepeatDays->GetWindowTextA(strVal); // use repeat time value
			m_autoOnRepeatHrsMins->GetTime(timeValue); // get delay time value
		} else {
			m_dogLeashDays->GetWindowTextA(strVal); // Use dog leash value
			m_dogLeashHrsMins->GetTime(timeValue); // get delay time value
		}
		timeMinutes = strtol(strVal, 0, 0); //convert to long
		timeMinutes*=24; // convert days to hours
		timeMinutes+=(long unsigned)timeValue.GetHour(); // add in delay hours
		timeMinutes*=(long unsigned)60; // convert to minutes
		timeMinutes+=(long unsigned)timeValue.GetMinute(); // add in minutes
		if (timeMinutes>(long unsigned)0x0ffffff) timeMinutes=0x0ffffff;
		outMsgStr[13]=(char)((timeMinutes>>16)&(long unsigned)0x0ff);
		outMsgStr[14]=(char)((timeMinutes>>8)&(long unsigned)0x0ff);
		outMsgStr[15]=(char)((timeMinutes>>0)&(long unsigned)0x0ff);
		unsigned long repeatTimeMinutes=timeMinutes;
// Add schedule info: on period
		m_autoOnPeriod->GetTime(timeValue); // get delay time value
		timeMinutes=(long unsigned)timeValue.GetHour();
		timeMinutes*=(long unsigned)60;
		timeMinutes+=(long unsigned)timeValue.GetMinute();
		if (timeMinutes>(long unsigned)0x0ffff) timeMinutes=0x0ffff;
		if (m_dogLeashEnable->GetCheck()==BST_CHECKED) {
			timeMinutes=(long unsigned)0; // If dog leash, set to 0
		}
		outMsgStr[16]=(char)((timeMinutes>>8)&(long unsigned)0x0ff);
		outMsgStr[17]=(char)((timeMinutes>>0)&(long unsigned)0x0ff);

		if (m_dogLeashEnable->GetCheck()==BST_CHECKED) { // its a dog leash so make period zero
			outMsgStr[16]=(char)0;
			outMsgStr[17]=(char)0;
			if (repeatTimeMinutes==(long unsigned)0) { // Insure that repeat time is greater than zero
				outMsgStr[15]=(char)1;
				timeValue=CTime(2007,1,1,0,0,1,-1); // Set time to 1/1/2007 at 12:01AM (to display 00:01)
				m_autoOnRepeatHrsMins->SetTime(&timeValue); // Set display to one
			}
		} else { // Its not a dog leash
			if (timeMinutes==(long unsigned)0) { // if period is zero make it one
				outMsgStr[17]=(char)1;
//				timeValue=CTime(2007,1,1,0,0,1); // Set time to 1/1/2007 at 12:01AM (to display 00:01)
				timeValue=CTime(2007,1,1,0,1,0,-1); // Set to one minute (year-month-day is irrelevant here
				m_autoOnPeriod->SetTime(&timeValue); // set delay time value
			}
		}


		msgString.Format("Output DF Cmd (write stinger schedule):");
		for (i=0;i<8;i++) {
			if ((outMsgStr[i+2]&0xf0)==0) msgString.Format("%s 0%1x",msgString,(outMsgStr[i+2]&0x0ff));
			else msgString.Format("%s %2x",msgString,(outMsgStr[i+2]&0x0ff));
    		if (i!=7) msgString.Format("%s,",msgString); // add comma to all but last
		}
		CDebugWinDlg::DisplayData(msgString);
		msgString.Format("Output DF Cmd (continued):");
		for (i=0;i<8;i++) {
			if ((outMsgStr[i+10]&0xf0)==0) msgString.Format("%s 0%1x",msgString,(outMsgStr[i+10]&0x0ff));
			else msgString.Format("%s %2x",msgString,(outMsgStr[i+10]&0x0ff));
    		if (i!=7) msgString.Format("%s,",msgString); // add comma to all but last
		}
		CDebugWinDlg::DisplayData(msgString);
		writeCmd(CMD_WRITE_STINGER_SCHEDULE_LEN);  //Write out rz msg of length 20
	} else {
		outMsgStr[0]=CMD_STINGER_1; //"rx" command
		outMsgStr[1]=CMD_STINGER_2; // "rx" command
		for (i=0;i<8;i++) {
			outMsgStr[i+2]=stinger8bytes[i]; // copy 8 bytes to outMsg
		}
		writeCmd(CMD_WRITE_STINGER_LEN);  //Write out rx msg of length 12
	}
}

extern CButton *m_onState;
extern CButton *m_offState;

void CMainDlg::OnBnClickedStingerOn() {
	stingerOnFlag=TRUE;
	stingerAllOff=0;
	m_onState->SetCheck(BST_CHECKED);
	m_offState->SetCheck(BST_UNCHECKED);
	if (stingerWinFlag==1) {
		m_onCmd->SetCheck(BST_CHECKED);
		m_offCmd->SetCheck(BST_UNCHECKED);
	}
	outputStingerCmd(STINGER_TX_SPECIFIC);
}

void CMainDlg::OnBnClickedStingerOff() {
	stingerOnFlag=FALSE;
	stingerAllOff=0;
	m_onState->SetCheck(BST_UNCHECKED);
	m_offState->SetCheck(BST_CHECKED);
	if (stingerWinFlag==1) {
		m_onCmd->SetCheck(BST_CHECKED);
		m_offCmd->SetCheck(BST_UNCHECKED);
	}
	outputStingerCmd(STINGER_TX_SPECIFIC);
}


void CMainDlg::OnBnClickedStingerAllOff() {
	stingerOnFlag=FALSE;
	stingerAllOff=1;
	m_onState->SetCheck(BST_UNCHECKED);
	m_offState->SetCheck(BST_CHECKED);
	if (stingerWinFlag==1) {
		m_onCmd->SetCheck(BST_CHECKED);
		m_offCmd->SetCheck(BST_UNCHECKED);
	}
	outputStingerCmd(STINGER_TX_SPECIFIC);
}


extern CComboBox *m_controlTxAddress;

int currentAddressIndex=0;

void updateStingerAddress() {
	int n,addflag;
	CString strVal;

	m_controlTxAddress->GetWindowTextA(strVal);
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
	m_controlTxAddress->SetWindowText(strVal);  //set edit section to what string ended up as
	n=m_controlTxAddress->FindStringExact(-1,strVal); // see if this address has been entered already
	addflag=0;
	if (n==CB_ERR) {
		n=m_controlTxAddress->AddString(strVal); // add address to list
		addflag=1;
	}
	n=m_controlTxAddress->FindStringExact(-1,strVal); // see if this address has been entered already
	if (n!=currentAddressIndex || addflag==1) { // if not, add it
		if (n>=0) {
			currentAddressIndex=n;
			m_controlTxAddress->SetCurSel(currentAddressIndex);
		}
		writeStingerCmdFile(); // update file
	}
	strVal.ReleaseBuffer();
}

void writeStingerCmdFile() {
	FILE *fp;
	ULONG value;
	int success,i,j,k;
	CComboBox *p_combobox;
	CString p_string,strVal;
	CTime x;

	fp=fopen("stingercmd.txt","w");
	if (fp) { //write stinger config file
		j=m_controlTxAddress->GetCount();
		fprintf(fp,"%d ",j);
		i=m_controlTxAddress->GetCurSel();
		if (i<0) i=0;
//		currentAddressIndex=i;
		fprintf(fp,"%d ",i);
		for (i=0;i<j;i++) { // Save all stinger addresses
			m_controlTxAddress->GetLBText(i,p_string);
			p_string.Insert(0,"0x");
			value = strtol(p_string, 0, 0); //convert to long
			if (value>0x0fff) value=0x0fff;
			if (value<0x0010) {
				strVal.Format("00%1lx",value);
			} else if (value<0x0100) {
				strVal.Format("0%2lx",value);
			} else  {
				strVal.Format("%3lx",value);
			}
			fprintf(fp," %s",strVal);
		}
		fprintf(fp,"\n");

/*		if (m_onCmd->GetCheck()==BST_CHECKED) {
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
//				k=stingerArray[][];
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
*/
		fclose(fp);
	} else {
	}
}


extern CComboBox *m_stingerAddress;

void readStingerCmdFile() {
	FILE *fp;
	ULONG value;
	CString strVal;
	CTime x;
//	char displayString[20];
	char oneChar;
	CComboBox *p_combobox;

	int success,i,j,numItems,selectedItem;
	fp=fopen("stingercmd.txt","r");
	if (fp==0) {
		return;
	} else {
		success=fscanf(fp," %d",&numItems);
		if (!success) return;
		success=fscanf(fp," %d",&selectedItem);
		if (!success) return;
		if (numItems<0) numItems=0;
		if (numItems>20) numItems=20; // max 20 addresses
		if (selectedItem<0) selectedItem=0;
		if (selectedItem>=numItems) selectedItem=numItems-1;
		currentAddressIndex=selectedItem;
		m_controlTxAddress->ResetContent();
		if (stingerWinFlag==1) m_stingerAddress->ResetContent(); // Only if Stinger window is up
		for (i=0;i<numItems;i++) {
			success=fscanf(fp," %lx",&value);
			if (!success) return;
			if (value>0x0fff) value=0x0fff;
//			if (stingerWinFlag==1) { // If stinger window up then build stinger addresses
				if (value<0x00f) {
					strVal.Format("00%1lx",value);
				} else if (value<0x0ff) {
					strVal.Format("0%2lx",value);
				} else  {
					strVal.Format("%3lx",value);
				}
				m_controlTxAddress->AddString(strVal); // add address to list
				if (stingerWinFlag==1) m_stingerAddress->AddString(strVal); // Only if Stinger window is up
//			} else { // If stinger window not up then only save selected address then return
//				if (i==selectedItem) {
//					stingerAddress=value;
//					return;
//				}
//			}
		}
		m_controlTxAddress->SetCurSel(selectedItem);
		if (stingerWinFlag==1) m_stingerAddress->SetCurSel(selectedItem); // Only if Stinger window is up

/*		if (stingerWinFlag==0) return; // The rest is only if Stinger window is up
		

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
			} else { // Dogleash disabled
				m_dogLeashEnable->SetCheck(BST_UNCHECKED);
				m_dogLeashDays->EnableWindow(FALSE);
				m_dogLeashHrsMins->EnableWindow(FALSE);
				if (m_autoOnEnable->GetCheck()==BST_CHECKED) { // schedule enabled
					m_autoOnPeriod->EnableWindow(TRUE);
					m_autoOnRepeatDays->EnableWindow(TRUE);
					m_autoOnRepeatHrsMins->EnableWindow(TRUE);
				} else { // schedule disabled
					m_autoOnPeriod->EnableWindow(FALSE);
					m_autoOnRepeatDays->EnableWindow(FALSE);
					m_autoOnRepeatHrsMins->EnableWindow(FALSE);
				}
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
*/
	}
}


