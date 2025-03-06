#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
#include "com_port.h"
#include "CChannelsDlg.h"
#include "CDebugWinDlg.h"
#include "CScanDlg.h"
#include "CStingerDlg.h"
//#include "ControlTxDlg.h"
#include <afxsock.h>
#include "msg_defs.h"
#include "config.h"

bool testForValidChecksum();

HANDLE   m_hCom;
bool comPortOpen=FALSE;
int comPortNumber=0;
int comPortBaud=0;
//CString comPortString[6]={"COM1","COM2","COM3","COM4","COM5","TELNET"};
DWORD oneComWord;
DWORD iBytesRead;

#define IN_COM_BUFFER_SIZE 50
int inComBuffer[IN_COM_BUFFER_SIZE];
int inComBufferIndex=0;

//LPOVERLAPPED_COMPLETION_ROUTINE 
void CALLBACK ReadFileCompleted(DWORD errorCode,
                                DWORD bytesCopied,
                                OVERLAPPED* overlapped);

DWORD buffer = 0;
OVERLAPPED ovlp = { 0 };
OVERLAPPED ovlpRead = { 0 };
LPOVERLAPPED overlapped=&ovlp;
LPOVERLAPPED overlappedRead=&ovlpRead;
DWORD status = ERROR_SUCCESS;

SOCKET mySock; //Socket handle
int sockStatus=0;
extern int portType;
extern CString ipAddress;
extern int telnetPort;

void init_com_port() {
//&&&&&&&&&&&&&&&&& Here's all the new stuff for the COM Port
// Taken from some website I got from googling "MFC Com port"
// http://ontrak.net/mfc.htm

// variables used with the com port
	BOOL     m_bPortReady;
	DCB      m_dcb;
	COMMTIMEOUTS m_CommTimeouts;

	CString  m_sComPort;
    char tempString[40];

	if (portType==PORT_TYPE_TCPIP) {


		WSADATA wsadata;
		if (sockStatus==1) {
			return;
		}
		if (mySock)
			closesocket(mySock);

		WSACleanup(); //Clean up Winsock


	    int error = WSAStartup(0x0202, &wsadata);
//		int PortNo=9000;

		//Did something happen?
		if (error!=0) {
			sockStatus=0;
	        return;
		}

		//Did we get the right Winsock version?
		if (wsadata.wVersion != 0x0202) {
			WSACleanup(); //Clean up Winsock
			sockStatus=0;
			return;
		}

		mySock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
		if (mySock == INVALID_SOCKET) {
			sockStatus=0;
	      return; //Couldn't create the socket
		}  

		u_long mode = 1;

		// Makes the socket non-blocking
		int ret = ioctlsocket(mySock, FIONBIO, &mode );


		SOCKADDR_IN target; //Socket address information
		target.sin_family = AF_INET; // address family Internet
		target.sin_port = htons (telnetPort); //Port to connect on

		int a1,a2,a3,a4;
		int x=sscanf(ipAddress,"%d.%d.%d.%d",&a1,&a2,&a3,&a4);
		if (x==4 && a1<256 && a2<256 &&a3<256 && a4<256) { // if this is true then its probably a valid IP address


			//Fill out the information needed to initialize a socket…
			target.sin_addr.s_addr = inet_addr (ipAddress); //Target IP

		} else { // it must be a host name

			struct addrinfo *result = NULL;
			x=getaddrinfo(ipAddress,0,0,&result);
			sockaddr *y;
			y=result->ai_addr;

		    struct hostent *he;
			struct in_addr **addr_list;

			he=gethostbyname(ipAddress);

		    addr_list = (struct in_addr **)he->h_addr_list;
			sprintf(tempString,"%s",inet_ntoa(*addr_list[0]));

			target.sin_addr.s_addr = inet_addr (tempString); //Target IP
		}
		//Try connecting...

		if (connect(mySock, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR) {
			sockStatus=0;
			return; //Couldn't connect
		} else {
			sockStatus=1;
			return; //Success
		}

	} else {
		//	m_sComPort = comPortString[comPortNumber];
		if (comPortNumber+1<10) {
			sprintf(tempString,"COM%1d",comPortNumber+1);
		} else {
			sprintf(tempString,"COM%2d",comPortNumber+1);
		}
		m_sComPort=tempString;
		if (comPortOpen) {
			CloseHandle(m_hCom);
			comPortOpen=FALSE;
		}
		m_hCom = CreateFile(m_sComPort, 
			GENERIC_READ | GENERIC_WRITE,
			0, // exclusive access
			NULL, // no security
			OPEN_EXISTING,
//	FILE_FLAG_OVERLAPPED, // overlapped I/O (formerly "0, // no overlapped I/O")
	        0,
			NULL); // null template 
		if (m_hCom==INVALID_HANDLE_VALUE) {
			CMainDlg::setCOMStatus(COM_STATUS_CANT_OPEN);
			return;
		}
		comPortOpen=TRUE;

//Check the returned handle for INVALID_HANDLE_VALUE and then set the buffer sizes.

		m_bPortReady = SetupComm(m_hCom, 128, 128); // set buffer sizes
		if (m_bPortReady!=1) {
			CMainDlg::setCOMStatus(COM_STATUS_CANT_SET_BUFFER);
			return;
		}

//Port settings are specified in a Data Communication Block (DCB). The easiest way to initialize a DCB is to call GetCommState to fill in its default values, override the values that you want to change and then call SetCommState to set the values.

		m_bPortReady = GetCommState(m_hCom, &m_dcb);
		if (m_bPortReady!=1) {
			CMainDlg::setCOMStatus(COM_STATUS_CANT_GET_STATE);
			return;
		}
		if (comPortBaud==0) {
			m_dcb.BaudRate = 9600;
		} else {
			m_dcb.BaudRate = 300;
		}
		m_dcb.ByteSize = 8;
		m_dcb.Parity = NOPARITY;
		m_dcb.StopBits = ONESTOPBIT;
		m_dcb.fAbortOnError = TRUE;

		m_bPortReady = SetCommState(m_hCom, &m_dcb);
		if (m_bPortReady!=1) {
			CMainDlg::setCOMStatus(COM_STATUS_CANT_SET_STATE);
			return;
		}

//Communication timeouts are optional but can be set similarly to DCB values:

		m_bPortReady = GetCommTimeouts (m_hCom, &m_CommTimeouts);
		if (m_bPortReady!=1) {
			CMainDlg::setCOMStatus(COM_STATUS_CANT_GET_TIMEOUTS);
			return;
		}


		m_CommTimeouts.ReadIntervalTimeout = 50;
		m_CommTimeouts.ReadTotalTimeoutConstant = 50;
		m_CommTimeouts.ReadTotalTimeoutMultiplier = 10;
		m_CommTimeouts.WriteTotalTimeoutConstant = 50;
		m_CommTimeouts.WriteTotalTimeoutMultiplier = 10;


		m_bPortReady = SetCommTimeouts (m_hCom, &m_CommTimeouts);
		if (m_bPortReady!=1) {
			CMainDlg::setCOMStatus(COM_STATUS_CANT_SET_TIMEOUTS);
			return;
		}
		CMainDlg::setCOMStatus(COM_STATUS_NO_RESPONSE); // initialize to no response to force message sync
	}

}

#define IN_MSG_BUF_SIZE 100
char inMsgBuf[IN_MSG_BUF_SIZE];
int inMsgBufIndex;
int expectedMsgLength=999;
void decodeMsg();
//void processMsg();
extern int COMStatus;
char testBuf[200];
int testBufIndex=0;
int inputDataTimeoutCounter;
extern char inMsgParams[];
extern char inMsgChars[2];
void decodeReceivedCommand();
extern int inMsgLengthActual;

extern int inMsgType;
extern bool MyCOMDeviceDetected;
int msgSlips=0;
int badCRCCount=0;
int prevInMsgType=0;
int goodComTimer=0;

//-------------------------------------------------------#####
#define IN_USB_BUFFER_LEN 100
int inUSBBufferIndex=0;
char inUSBBuffer0[IN_USB_BUFFER_LEN];
char inUSBBuffer1[IN_USB_BUFFER_LEN];
char inUSBBuffer2[IN_USB_BUFFER_LEN];
char inUSBBufferLength[IN_USB_BUFFER_LEN];
char inUSBBufferResult[IN_USB_BUFFER_LEN];
extern HANDLE ReadHandle;
extern OVERLAPPED HIDOverlapped;
extern DWORD NumberOfBytesRead;
extern char InputReport[];
void CMainDlg::readDataFromUSB() {
	int i;
	LONG Result;

	i=0;

// If invalid handle, return
	if (ReadHandle==INVALID_HANDLE_VALUE) {
		return;
	}

// Get first two bytes which are response message type
	InputReport[0]=0;	//The first byte is the report number.
	Result=1;
	NumberOfBytesRead=3;
	while (Result==1 && NumberOfBytesRead==3) {
		Result = ReadFile(ReadHandle,InputReport,3,&NumberOfBytesRead,
			(LPOVERLAPPED) &HIDOverlapped);
		if (NumberOfBytesRead!=0) {
			inUSBBuffer0[inUSBBufferIndex]=InputReport[0];
			inUSBBuffer1[inUSBBufferIndex]=InputReport[1];
			inUSBBuffer2[inUSBBufferIndex]=InputReport[2];
			inUSBBufferLength[inUSBBufferIndex]=NumberOfBytesRead;
			inUSBBufferResult[inUSBBufferIndex++]=Result;
			if (inUSBBufferIndex>=IN_USB_BUFFER_LEN) {
				inUSBBufferIndex=0;
			}
		}
	}

}
extern int com_not_init_counter;

//-------------------------------------------------------#####
int	firstConfigRespReceived=0;
extern CStatic *m_msgSlipsTxt;

void CMainDlg::readDataFromComPort() {
	int i;
    char tempString[30];

	iBytesRead=0;

    goodComTimer++; // increment counter everytime readDateFromComPort() called (i.e., once per CMainDlg::OnTimer())

	if (portType==PORT_TYPE_TCPIP) {
		iBytesRead=recv(mySock,(char*)&oneComWord,1,0);
	} else {
		ReadFile(m_hCom,(LPVOID)&oneComWord,1,(LPDWORD)&iBytesRead,overlappedRead);
	}

// while COM data is available
	while (iBytesRead==1) {

// read input COM byte
		inMsgBuf[inMsgBufIndex]=oneComWord;
		inMsgBufIndex++;
		if (inMsgBufIndex>=IN_MSG_BUF_SIZE) { // this should never happen since index is reset to zero when out of sync, but for safety's sake...
			inMsgBufIndex=0;
			COMStatus=COM_STATUS_BAD_SYNC;
		}

// save input COM data to test array
		if (testBufIndex<100) {
			testBuf[testBufIndex]=oneComWord;
			testBufIndex++;
		}

// if out of sync, read bytes until received an 's'
		if (COMStatus!=COM_STATUS_DEVICE_FOUND) {
			if (inMsgBuf[0]!='s') {
				inMsgBufIndex=0;
			}
		}

// if two bytes have been read, check for a valid response code
		if (inMsgBufIndex==2) {
			inMsgChars[0]=inMsgBuf[0]; // copy first two characters for this routine (originally written for USB version)
			inMsgChars[1]=inMsgBuf[1]; // copy first two characters for this routine (originally written for USB version)
			prevInMsgType=inMsgType;
		    decodeReceivedCommand();
			if (inMsgType!=CMD_UNKNOWN) {
				MyCOMDeviceDetected=TRUE;
				CMainDlg::setCOMStatus(COM_STATUS_DEVICE_FOUND);
				com_not_init_counter=0;
			} else {
				msgSlips++;
				// update RS status request counter at bottom of screen
				sprintf(tempString,"Slips:%5d, Prev:%2d, Next:%2d",msgSlips,prevInMsgType,inMsgType);
				m_msgSlipsTxt->SetWindowTextA(tempString);
// don't do anything to the com status just because it slipped
//				MyCOMDeviceDetected=TRUE;
//				CMainDlg::setCOMStatus(COM_STATUS_BAD_SYNC);
			}


			expectedMsgLength=inMsgLengthActual; // copy resulting length to this variable (original name in USB version)
		}

// if an entire response has been read, process message
		if (inMsgBufIndex==expectedMsgLength) {
			if (testForValidChecksum()) {
				for (i=2;i<expectedMsgLength;i++) {
					inMsgParams[i-2]=inMsgBuf[i];
				}
				goodComTimer=0; // reset counter whenever we get a good message
				processMsg();
			} else {
				badCRCCount++;
			}
			expectedMsgLength=999;  // reset expected message length to beyond possible
			inMsgBufIndex=0; // reset bytes read counter to 0
			inputDataTimeoutCounter=0; // reset input data timeout counter to stay in sync
		}

// try to read again from COM
		if (portType==PORT_TYPE_TCPIP) {
			iBytesRead=recv(mySock,(char*)&oneComWord,1,0);
		} else {
			ReadFile(m_hCom,(LPVOID)&oneComWord,1,(LPDWORD)&iBytesRead,overlappedRead);
		}

	}

	long xyz=(long)COM_TIMEOUT_MS/(long)STATUS_UPDATE_TIME;
	if (goodComTimer>xyz) {

		CMainDlg::setCOMStatus(COM_STATUS_NO_RESPONSE); // set to no response
		// blank display if device is not found
		CMainDlg::blankMainDisplayIndicators();
		firstConfigRespReceived=0;
	}
}

void appendCRC(char*,int);

bool testForValidChecksum() {
	char crc1,crc2;
	crc1=inMsgBuf[expectedMsgLength-2];
	crc2=inMsgBuf[expectedMsgLength-1];
	inMsgBuf[expectedMsgLength-2]=0xff;
	inMsgBuf[expectedMsgLength-1]=0xff;
	appendCRC(inMsgBuf,expectedMsgLength-2); // Add the CRC
	if (inMsgBuf[expectedMsgLength-2]==crc1 && inMsgBuf[expectedMsgLength-1]==crc2) {
		return (TRUE);
	} 
	return (FALSE);
}

extern int audioFilterNum;
extern CButton *m_stingerCmd;
extern int	monoStereoSwapLRToggleFlag;
extern int bytesPerClusterDiv512;
int	readBytesPerCluster=0;
int statusRespCount=0;
extern CStatic *m_msgSTRcvdCountTxt;
extern int scanWinFlag;
extern int stealthRecordWindowMode;

void CMainDlg::processMsg() {
	char tempString[10];
	switch(inMsgType) {
		case CMD_STATUS_REQ:
			statusRespUpdateControls();
			sprintf(tempString,"ST: %5d",statusRespCount++);
			m_msgSTRcvdCountTxt->SetWindowTextA(tempString);
			break;
		case CMD_CONFIG_REQ:
			configRespUpdateControls();
			if (firstConfigRespReceived==0) {
				firstConfigRespReceived=1;
				readFreqFile();
			}
			break;
		case CMD_CARD_STATUS_REQ:
			if (stealthRecordWindowMode==0) 
				cardStatusRespUpdateControls();
			break;
		case CMD_RECORD_STATUS_REQ:
			if (stealthRecordWindowMode==0) 
				recordStatusRespUpdateControls();
			break;
		case CMD_NEXT_FILE_NAME_REQ:
			if (stealthRecordWindowMode==0) 
				nextFileNameUpdate();
			break;
		case CMD_TX_FREQ_REQ:
			txFreqUpdate();
			break;
		case CMD_SIG_PROC_REQ:
			sigProcUpdate();
			break;
		case CMD_TX_STATUS_REQ:
			txStatusUpdate();
			break;
		case CMD_FPGA_REG_REQ:
			CDebugWinDlg::FPGARegUpdate();
			break;
		case CMD_EEPROM_PIC1_REQ:
			CDebugWinDlg::EepromPic1Update();
			break;
		case CMD_DATE_READ:
			dateUpdate();
			break;
		case CMD_TIME_READ:
			timeUpdate();
			break;
		case CMD_SWEEP:
			if (scanWinFlag==1) {
				CScanDlg::plotSweepPoint();
			}
			break;
		case CMD_ENCRYPT_SET:
			AfxMessageBox("Key Loaded");
			break;
		case CMD_PLAYBACK_STATUS:
			playbackUpdate();
			break;
		case CMD_RESP_MISC_INFO:
			miscInfoUpdate();
			break;

	}

}

