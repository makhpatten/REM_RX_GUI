/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog used to display channels

/*class CScanView : public CView {
}
*/
#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
#include "cDebugWinDlg.h"
#include "cscandlg.h"
#include "led_defs.h"
#include "msg_defs.h"
#include "oper_params.h"
#include "config.h"

#define SCAN_X_ORIGIN 66
#define SCAN_X_SIZE 532
#define SCAN_Y_ORIGIN 308
#define SCAN_Y_SIZE 240


ULONG nScanSteps;
//int firstPointFlag=0;
CRgn *graphRegion;


int scanTracer[300];
int scanTracerCount=0;

ULONG startFreqKHz;
ULONG stopFreqKHz;
ULONG stepFreqKHz;

#define MAX_STEPS 2000

BEGIN_MESSAGE_MAP(CScanDlg, CDialog)
//{{AFX_MSG_MAP(CScanDlg)
//		ON_WM_TIMER()
		ON_WM_CLOSE()
	// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_SCAN, &CScanDlg::OnBnClickedScan)
	ON_BN_CLICKED(ID_SCANCLOSE, &CScanDlg::OnBnClickedScanClose)
	ON_BN_CLICKED(ID_CLEARSCAN, &CScanDlg::OnBnClickedClearscan)
END_MESSAGE_MAP()


CScanDlg::CScanDlg() : CDialog(CScanDlg::IDD)
{
}

void CScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCANAREA, m_scanArea);
}

CButton *m_scanButton;
CStatic *m_startText2;
CStatic *m_stopText;
CStatic *m_stepText;
CStatic *m_subTitleText;

CDC *scanDrawingContext;
extern CScanDlg *pscanWinDlg;
CListBox *m_ScanFreqText;
// Debug text box on scan window
// CListBox *m_xAndYTextDebug;
extern char freqValChars[];
extern void freqKHzToMHzString(ULONG,char *);
extern int scanWinFlag;
extern long unsigned minFreq, maxFreq;

BOOL CScanDlg::OnInitDialog() {
	int i;
	scanWinFlag=1;			// Set flag
	// Initialize start frequency
	startFreqKHz=minFreq;
	CEdit* m_FreqValueTemp = (CEdit*) GetDlgItem(IDC_START_FREQ);
    freqKHzToMHzString(startFreqKHz,freqValChars); // Convert to string
	m_FreqValueTemp->SetWindowText(freqValChars);  // Set text back to what value ended up
// also set text on graph
//	m_FreqValue = (CEdit*) GetDlgItem(IDC_START_FREQ_TEXT);
//	m_FreqValue->SetWindowText(freqValChars);  // Set text back to what value ended up
	m_startText2 = (CStatic*) GetDlgItem(IDC_START_FREQ_TEXT);
	strcat(freqValChars," MHz");
	m_startText2->SetWindowTextA(CString(freqValChars));

	// Initialize stop frequency
	stopFreqKHz=maxFreq;
	m_FreqValueTemp = (CEdit*) GetDlgItem(IDC_STOP_FREQ);
    freqKHzToMHzString(stopFreqKHz,freqValChars); // Convert to string
	m_FreqValueTemp->SetWindowText(freqValChars);  // Set text back to what value ended up
	m_stopText = (CStatic*) GetDlgItem(IDC_STOP_FREQ_TEXT);
	strcat(freqValChars," MHz");
	m_stopText->SetWindowTextA(CString(freqValChars));

	// Initialize step frequency
	stepFreqKHz=(ULONG)500;  //0.5 MHz default stpe frequency
	m_FreqValueTemp = (CEdit*) GetDlgItem(IDC_STEP_FREQ);
    freqKHzToMHzString(stepFreqKHz,freqValChars); // Convert to string
	m_FreqValueTemp->SetWindowText(freqValChars);  // Set text back to what value ended up

	m_stepText = (CStatic*) GetDlgItem(IDC_FREQ_PER_DIV_TEXT);
	m_stepText->SetWindowTextA("");

	m_subTitleText = (CStatic*) GetDlgItem(IDC_SPEC_SUBTITLE);
    extern CString globalSerNum;
	if (strlen(globalSerNum)==0) {
	   m_subTitleText->SetWindowTextA("");
	} else {
		m_subTitleText->SetWindowTextA("Serial Number: "+globalSerNum);
	}

	m_scanButton=(CButton*)GetDlgItem(ID_SCAN);
	m_scanButton->SetWindowTextA("Restart Scan");

	m_ScanFreqText = (CListBox*) GetDlgItem(IDC_SCAN_FREQ_TEXT);

// Text display for debugging
//	m_xAndYTextDebug = (CListBox*) GetDlgItem(IDC_X_AND_Y_TEXT_DEBUG);
	

	scanDrawingContext = new CDC();
	scanDrawingContext=pscanWinDlg->GetDC();

	graphRegion=new CRgn();
	graphRegion->CreateRectRgn(SCAN_X_ORIGIN+1,SCAN_Y_ORIGIN+1,
		SCAN_X_ORIGIN+SCAN_X_SIZE+1,SCAN_Y_ORIGIN-SCAN_Y_SIZE+3);
	drawGraphGrid();

	scanDrawingContext->MoveTo(SCAN_X_ORIGIN,SCAN_Y_ORIGIN);

	OnBnClickedClearscan();
	OnBnClickedScan();

	
	for (i=0;i<300;i++) {
		scanTracer[i]=0;	
	}

	return TRUE;
}

extern char outMsgStr[];
extern char inMsgParams[];
extern int inMsgType;
extern ULONG tuneFreqKHz;
extern ULONG respFreqKHz;
extern CString msgString;
extern ULONG freq_3bytes_to_value(char*);
extern ULONG paramValueLong;
extern float paramValueFloat;
extern float convert_AD_to_dBm(char);
extern int paramValueInt;
extern int convert_dBm_to_specGraph(float);

extern char outMsgStr[];


void CScanDlg::OnBnClickedScan()
{
	getStartStopStepFreqs();

	outMsgStr[0]=CMD_SWEEP_REQ_1;
	outMsgStr[1]=CMD_SWEEP_REQ_2; 
	outMsgStr[2]=(char)((startFreqKHz>>16)&(long int)0x0ff); //High byte
	outMsgStr[3]=(char)((startFreqKHz>>8) &(long int)0x0ff); //Mid byte
	outMsgStr[4]=(char)((startFreqKHz>>0) &(long int)0x0ff); //Low byte
	outMsgStr[5]=(char)((stopFreqKHz>>16)&(long int)0x0ff); //High byte
	outMsgStr[6]=(char)((stopFreqKHz>>8) &(long int)0x0ff); //Mid byte
	outMsgStr[7]=(char)((stopFreqKHz>>0) &(long int)0x0ff); //Low byte
	outMsgStr[8]=(char)((stepFreqKHz>>16)&(long int)0x0ff); //High byte
	outMsgStr[9]=(char)((stepFreqKHz>>8) &(long int)0x0ff); //Mid byte
	outMsgStr[10]=(char)((stepFreqKHz>>0) &(long int)0x0ff); //Low byte
	CMainDlg::writeCmd(CMD_SWEEP_REQ_LEN);

}
extern int limitFreqValRange(ULONG *freqVal);

void CScanDlg::getStartStopStepFreqs() {
//	ULONG nSteps;

//&&&&
	CString freqValString;
	char freqValChars[20];

//	ULONG freqVal;
	int freqPos;
	double freqValDouble;

// Get start frequency
	CEdit* m_FreqValue = (CEdit*) GetDlgItem(IDC_START_FREQ);
	m_FreqValue->GetWindowText(freqValString); // get string text
	freqValDouble = strtod(freqValString, 0); //convert text to MHz float
	startFreqKHz=(ULONG)(1000.0*freqValDouble);  //convert to KHz integer
	limitFreqValRange(&startFreqKHz); // Apply frequency limits
    freqKHzToMHzString(startFreqKHz,freqValChars); // Convert to string
	m_FreqValue->SetWindowText(freqValChars);  // Set text back to what value ended up
	strcat(freqValChars," MHz");
	m_startText2->SetWindowTextA(CString(freqValChars));

// Get stop frequency
	m_FreqValue = (CEdit*) GetDlgItem(IDC_STOP_FREQ);
	m_FreqValue->GetWindowText(freqValString); // get string text
	freqValDouble = strtod(freqValString, 0); //convert text to MHz float
	stopFreqKHz=(ULONG)(1000.0*freqValDouble);  //convert to KHz integer
	limitFreqValRange(&stopFreqKHz); // Apply frequency limits
    freqKHzToMHzString(stopFreqKHz,freqValChars); // Convert to string
	m_FreqValue->SetWindowText(freqValChars);  // Set text back to what value ended up
	strcat(freqValChars," MHz");
	m_stopText->SetWindowTextA(CString(freqValChars));

// Get step frequency
	m_FreqValue = (CEdit*) GetDlgItem(IDC_STEP_FREQ);
	m_FreqValue->GetWindowText(freqValString); // get string text
	freqValDouble = strtod(freqValString, 0); //convert text to MHz float
	stepFreqKHz=(ULONG)(1000.0*freqValDouble);  //convert to KHz integer
    freqKHzToMHzString(stepFreqKHz,freqValChars); // Convert to string
	m_FreqValue->SetWindowText(freqValChars);  // Set text back to what value ended up

// Compute number of scan steps, adjust if greater than max
	if (stepFreqKHz>0) nScanSteps=(stopFreqKHz-startFreqKHz)/stepFreqKHz;
	else nScanSteps=1;
	if (nScanSteps>MAX_STEPS) {
		nScanSteps=MAX_STEPS;
		stepFreqKHz=(stopFreqKHz-startFreqKHz)/nScanSteps;
	    freqKHzToMHzString(stepFreqKHz,freqValChars); // Convert to string
		m_FreqValue->SetWindowText(freqValChars);  // Set text back to what value ended up
	}

}




void CScanDlg::freq24ValueFromDlgItem(int dialogID,char *p_outMsgStr) {
	long unsigned longVal;
	CString strVal;
	CEdit* editControl = (CEdit*) GetDlgItem(dialogID);
	editControl->GetWindowText(strVal);
	longVal = strtol(strVal, 0, 0); //convert to float
	if (longVal<MIN_FREQ_KHZ) longVal=MIN_FREQ_KHZ;
	if (longVal>MAX_FREQ_KHZ) longVal=MAX_FREQ_KHZ;
	p_outMsgStr[0]=(char)((longVal>>24)&(long unsigned)0x0ff);
	p_outMsgStr[1]=(char)((longVal>>16)&(long unsigned)0x0ff);
	p_outMsgStr[2]=(char)(longVal&(long unsigned)0x0ff);
	strVal.Format("%10d",(int)longVal); //Set string to what parameter ended up
	editControl->SetWindowText(strVal);
}


void CScanDlg::drawGraphGrid() {
	int i;
	int numXGridLines=5;
	int numYGridLines=7;
	int coordVal;
	CPen gridLinePen;
	CPen erasePen;
	CPen blackPen;

// determine number and location of X axis grid lines
    ULONG freqSpanKHz=stopFreqKHz-startFreqKHz;
	float xaxisGridSpan=(float)freqSpanKHz/(float)4.0;

	int powerShift=0;
	while (xaxisGridSpan>10.0) {
		xaxisGridSpan/=10.0;
		powerShift+=1;
	}
	while (xaxisGridSpan<1.0) {
		xaxisGridSpan*=10.0;
		powerShift-=1;
	}
    int xaxisGridSpanFloor = (int)xaxisGridSpan;
	if (xaxisGridSpanFloor>5) xaxisGridSpanFloor=5;
	else if (xaxisGridSpanFloor>2) xaxisGridSpanFloor=2;
	else xaxisGridSpanFloor=1;

	xaxisGridSpan = (float)xaxisGridSpanFloor;
	while (powerShift>0) {
		xaxisGridSpan*=10.0;
		powerShift-=1;
	}
	while (powerShift<0) {
		xaxisGridSpan/=10.0;
		powerShift+=1;
	}
    float firstGridLine=(float)startFreqKHz/xaxisGridSpan;
	int firstGridLineFloor= (int)firstGridLine;
	firstGridLine=(float)(firstGridLineFloor+1)*xaxisGridSpan;

    freqKHzToMHzString((ULONG)xaxisGridSpan,freqValChars); // Convert to string
	strcat(freqValChars," MHz/Div");
	m_stepText->SetWindowTextA(CString(freqValChars));


// Erase region
	erasePen.CreatePen(PS_DOT,1,RGB(240,240,240));
	scanDrawingContext->SelectObject(&erasePen);
	scanDrawingContext->PaintRgn(graphRegion);

// Draw border
	blackPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	scanDrawingContext->SelectObject(&blackPen);
	scanDrawingContext->MoveTo(SCAN_X_ORIGIN,SCAN_Y_ORIGIN);
	scanDrawingContext->LineTo(SCAN_X_ORIGIN,SCAN_Y_ORIGIN-SCAN_Y_SIZE+2);
	scanDrawingContext->LineTo(SCAN_X_ORIGIN+SCAN_X_SIZE+1,SCAN_Y_ORIGIN-SCAN_Y_SIZE+2);
	scanDrawingContext->LineTo(SCAN_X_ORIGIN+SCAN_X_SIZE+1,SCAN_Y_ORIGIN);
	scanDrawingContext->LineTo(SCAN_X_ORIGIN,SCAN_Y_ORIGIN);


	gridLinePen.CreatePen(PS_DOT,1,RGB(127,127,127));
	scanDrawingContext->SelectObject(&gridLinePen);
	i=0;
	float gridLineKHz=firstGridLine+i*xaxisGridSpan;
	while (gridLineKHz<(float)stopFreqKHz) {
		coordVal=SCAN_X_ORIGIN+(int)((gridLineKHz-(float)startFreqKHz)*(float)SCAN_X_SIZE/(float)freqSpanKHz);
		scanDrawingContext->MoveTo(coordVal,SCAN_Y_ORIGIN);
		scanDrawingContext->LineTo(coordVal,SCAN_Y_ORIGIN-SCAN_Y_SIZE);
		i++;
		gridLineKHz=firstGridLine+i*xaxisGridSpan;

	}
	for (i=1;i<numYGridLines;i++) {
		coordVal=SCAN_Y_ORIGIN-i*SCAN_Y_SIZE/numYGridLines;
		scanDrawingContext->MoveTo(SCAN_X_ORIGIN,coordVal);
		scanDrawingContext->LineTo(SCAN_X_ORIGIN+SCAN_X_SIZE,coordVal);
	}

}


extern CButton m_scanWin;
extern int saveFreqPos;
extern ULONG setFreqKHz[];

afx_msg void CScanDlg::OnClose() {
	scanWinFlag=0;
	m_scanWin.EnableWindow(TRUE);//re-enable button for Scan Window

	tuneFreqKHz=setFreqKHz[8-saveFreqPos]; // Tune to previous frequency

	CMainDlg::setFreqOperCmd();
// important enough to do twice
	CMainDlg::setFreqOperCmd();
//	fatRedPen.DeleteObject();

	CDialog::OnClose();
}
//extern CDialog *pscanWinDlg;
void CScanDlg::OnBnClickedScanClose()
{
	scanWinFlag=0;
//Kill channels window manually
	pscanWinDlg->DestroyWindow();
//re-enable button for Channels Window
	m_scanWin.EnableWindow(TRUE);
// Restore tuning to previous setting
	tuneFreqKHz=setFreqKHz[8-saveFreqPos];
	CMainDlg::setFreqOperCmd();
// important enough to do twice
	CMainDlg::setFreqOperCmd();
//	fatRedPen.DeleteObject();
	
//	KillTimer(ID_TIMER_CHANNELS);
	CDialog::OnClose();
}








void CScanDlg::OnBnClickedClearscan()
{
	drawGraphGrid();
}

unsigned int convert_AD_to_mag(char);
extern int rssiA,rssiB;
int prevXcoordValA=999; // initialize to impossibly high value
int prevYcoordValA=999; // initialize to impossibly high value
int prevXcoordValB=999; // initialize to impossibly high value
int prevYcoordValB=999; // initialize to impossibly high value

char tempCharXXX=0;

void CScanDlg::plotSweepPoint() {
	int xcoordVal,ycoordVal;
	float floatVal;

	CPen fatRedPen;
	fatRedPen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen fatBluePen;
	fatBluePen.CreatePen(PS_SOLID,2,RGB(0,0,255));

	scanDrawingContext->SelectObject(&fatRedPen);

	scanDrawingContext=pscanWinDlg->GetDC();

	respFreqKHz=freq_3bytes_to_value(inMsgParams);

// Update scan freq text
    freqKHzToMHzString(respFreqKHz,freqValChars);
	m_ScanFreqText->ResetContent();
	m_ScanFreqText->InsertString(0,freqValChars);


// calculate x coordinate
	floatVal=(float)(respFreqKHz-startFreqKHz);
	floatVal*=(float)SCAN_X_SIZE;
	floatVal/=(float)(stopFreqKHz-startFreqKHz);
	xcoordVal=SCAN_X_ORIGIN+(int)floatVal;

// read and plot RSSI value for antenna A

//	tempCharXXX++;
//	inMsgParams[3]=tempCharXXX;
	paramValueFloat=convert_AD_to_dBm(inMsgParams[3]);
	paramValueInt=convert_dBm_to_specGraph(paramValueFloat);
	if (paramValueInt>=252) paramValueInt=252;
	if (paramValueInt<0) paramValueInt=0;

	floatVal=(float)paramValueInt/(float)255.0;
	floatVal*=SCAN_Y_SIZE;
	ycoordVal=SCAN_Y_ORIGIN-(int)floatVal;

	scanDrawingContext->SelectObject(&fatRedPen);
	if (respFreqKHz==startFreqKHz) {
	// try drawing graph grid here
		drawGraphGrid();
		xcoordVal=SCAN_X_ORIGIN; // set up for first point
		scanDrawingContext->MoveTo(SCAN_X_ORIGIN,ycoordVal);
		prevXcoordValA=xcoordVal;
		prevYcoordValA=ycoordVal;
	} else {
		if (scanTracerCount<300) {
			scanTracer[scanTracerCount]=33;
			scanTracerCount++;
		}
		scanDrawingContext->MoveTo(prevXcoordValA,prevYcoordValA);
		scanDrawingContext->LineTo(xcoordVal,ycoordVal);
		prevXcoordValA=xcoordVal;
		prevYcoordValA=ycoordVal;
	}



// read and plot RSSI value for antenna B
	paramValueFloat=convert_AD_to_dBm(inMsgParams[4]);
	paramValueInt=convert_dBm_to_specGraph(paramValueFloat);
	if (paramValueInt>=252) paramValueInt=252;
	if (paramValueInt<0) paramValueInt=0;
	floatVal=(float)paramValueInt/(float)255.0;
	floatVal*=SCAN_Y_SIZE;
	ycoordVal=SCAN_Y_ORIGIN-(int)floatVal;

	scanDrawingContext->SelectObject(&fatBluePen);
	if (respFreqKHz==startFreqKHz) {
		drawGraphGrid();
		xcoordVal=SCAN_X_ORIGIN; // set up for previous 
		scanDrawingContext->MoveTo(SCAN_X_ORIGIN,ycoordVal);
		prevXcoordValB=xcoordVal;
		prevYcoordValB=ycoordVal;
	} else {
		scanDrawingContext->MoveTo(prevXcoordValB,prevYcoordValB);
		scanDrawingContext->LineTo(xcoordVal,ycoordVal);
		prevXcoordValB=xcoordVal;
		prevYcoordValB=ycoordVal;
	}

}
