#include "stdafx.h"
#include "infinity.h"
#include "infinityDlg.h"
extern "C" {

// This file is in the Windows DDK available from Microsoft.
#include "C:\WINDDK\3790.1830\inc\wxp\hidsdi.h"

#include <setupapi.h>
#include <dbt.h>
}
#include "cDebugWinDlg.h"
#include "msg_defs.h"

#define VENDOR_ID 0x0461
#define PRODUCT_ID 0x0020
#define INPUT_MSG_TIMEOUT_MS (DWORD)2000


/*
My routines (routines specific to this application) start here.
*/

HANDLE								DeviceHandle=INVALID_HANDLE_VALUE;
HANDLE								ReadHandle=INVALID_HANDLE_VALUE;
HANDLE								WriteHandle=INVALID_HANDLE_VALUE;
CString								MyDevicePathName;
HIDP_CAPS							Capabilities;
char								FeatureReport[256];
char								InputReport[256];
ULONG								Length;
PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
GUID								HidGuid;
OVERLAPPED							HIDOverlapped;
LPOVERLAPPED						lpOverLap;
HANDLE								hDevInfo;
ULONG								Required;
CString								ValueToDisplay;
HANDLE								hEventObject;
char								OutputReport[256];
int recursionFlag=0;

extern	int debugWinFlag;
extern bool MyUSBDeviceDetected;
extern char outMsgStr[];
extern DWORD NumberOfBytesRead;
extern char inMsgChars[];
extern int inMsgType;
extern int inMsgLengthActual;
extern char inMsgParams[];

void decodeReceivedCommand();


void CMainDlg::CloseHandles()
	{
	//Close open handles.
	
	if (DeviceHandle != INVALID_HANDLE_VALUE)
		{
		CloseHandle(DeviceHandle);
		DeviceHandle=INVALID_HANDLE_VALUE;
		}

	if (ReadHandle != INVALID_HANDLE_VALUE)
		{
		CloseHandle(ReadHandle);
		ReadHandle=INVALID_HANDLE_VALUE;
		}

	if (WriteHandle != INVALID_HANDLE_VALUE)
		{
		CloseHandle(WriteHandle);
		WriteHandle=INVALID_HANDLE_VALUE;
		}
	}


BOOL CMainDlg::DeviceNameMatch(LPARAM lParam)
	{

	// Compare the device path name of a device recently attached or removed 
	// with the device path name of the device we want to communicate with.
	
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	CDebugWinDlg::DisplayData2("MyDevicePathName = " + MyDevicePathName);
#endif

	if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) 
	{
		
		PDEV_BROADCAST_DEVICEINTERFACE lpdbi = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;

		
		CString DeviceNameString;

		//The dbch_devicetype parameter indicates that the event applies to a device interface.
		//So the structure in LParam is actually a DEV_BROADCAST_INTERFACE structure, 
		//which begins with a DEV_BROADCAST_HDR.

		//The dbcc_name parameter of DevBroadcastDeviceInterface contains the device name. 
 
		//Compare the name of the newly attached device with the name of the device 
		//the application is accessing (myDevicePathName).

		DeviceNameString = lpdbi->dbcc_name;

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
		CDebugWinDlg::DisplayData2("DeviceNameString = " + DeviceNameString);
#endif

		if ((DeviceNameString.CompareNoCase(MyDevicePathName)) == 0)

		{
			//The name matches.

            return true;
		}
		else
		{
            //It's a different device.

            return false;
    	}
		
	}
		else
		{
			return false;
		}	
}

void CMainDlg::DisplayCurrentTime()
{
	//Get the current time and date and display them in the log List Box.

	CTime curTime = CTime::GetCurrentTime();
	CString CurrentTime = curTime.Format( "%H:%M:%S, %B %d, %Y" );
	CDebugWinDlg::DisplayData2(CurrentTime);
}


CString msgStringLine1="";
CString msgStringLine2="";
CString msgStringLine3="";
CString msgStringLine4="";
int numDisplayStrings=0;
#define MAX_NUM_DISPLAY_STRINGS 25

/*
void CDebugWinDlg::DisplayData2(CString cstrDataToDisplay)
{
	USHORT	Index;

	if (numDisplayStrings>MAX_NUM_DISPLAY_STRINGS) {
		m_ResultsList.DeleteString(0);
	} else {
		numDisplayStrings++;
	}
	Index=m_ResultsList.InsertString(-1,(LPCTSTR)cstrDataToDisplay);
	ScrollToBottomOfListBox(Index);
}
*/


void CMainDlg::DisplayFeatureReport()
{
	USHORT	ByteNumber;
	CHAR	ReceivedByte;
	
	//Display the received data in the log and the Bytes Received List boxes.
	//Start at the top of the List Box.

//	m_BytesReceived.ResetContent();
	
	//Step through the received bytes and display each.

	for (ByteNumber=0; ByteNumber < Capabilities.FeatureReportByteLength; ByteNumber++)
	{
		//Get a byte.

		ReceivedByte = FeatureReport[ByteNumber];

		//Display it.

//		DisplayReceivedData(ReceivedByte);
	}
}


void CMainDlg::DisplayInputReport()
{
	USHORT	ByteNumber;
	CHAR	ReceivedByte;
	
	//Display the received data in the log and the Bytes Received List boxes.
	//Start at the top of the List Box.

//	m_BytesReceived.ResetContent();
	
	//Step through the received bytes and display each.

	for (ByteNumber=0; ByteNumber < Capabilities.InputReportByteLength; ByteNumber++)
	{
		//Get a byte.

		ReceivedByte = InputReport[ByteNumber];

		//Display it.

//		DisplayReceivedData(ReceivedByte);
	}
}


#if DISPLAY_MESSAGES==YES_DISPLAY_EM
void CMainDlg::DisplayLastError(CString Operation)
{
	//Display a message and the last error in the log List Box.
	
	LPVOID lpMsgBuf;
	USHORT Index = 0;
	CString	strLastError = "";

	if (debugWinFlag==0) return;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	//Display the last error.

	strLastError = Operation + (LPCTSTR)lpMsgBuf; 

	//Trim CR/LF from the error message.

	strLastError.TrimRight(); 
	CDebugWinDlg::DisplayData2(strLastError);
	LocalFree(lpMsgBuf); 
}
#endif


//void CMainDlg::DisplayReceivedData(char ReceivedByte)
//{
	//Display data received from the device.

//	CString	strByteRead;

	//Convert the value to a 2-character Cstring.

//	strByteRead.Format("%02X", ReceivedByte);
//	strByteRead = strByteRead.Right(2); 

	//Display the value in the Bytes Received List Box.

//	m_BytesReceived.InsertString(-1, strByteRead);

	//Display the value in the log List Box (optional).
	//MessageToDisplay.Format("%s%s", "Byte 0: ", strByteRead); 
	//CDebugWinDlg::DisplayData2(MessageToDisplay);	
	//UpdateData(false);
//}


bool CMainDlg::FindTheHID()
{
	//Use a series of API calls to find a HID with a specified Vendor IF and Product ID.

	HIDD_ATTRIBUTES						Attributes;
	DWORD								DeviceUsage;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	int									MemberIndex = 0;
	LONG								Result;	
	CString								UsageDescription;
static int flag=0;

	Length = 0;
	detailData = NULL;
	DeviceHandle=INVALID_HANDLE_VALUE;

	/*
	API function: HidD_GetHidGuid
	Get the GUID for all system HIDs.
	Returns: the GUID in HidGuid.
	*/

	HidD_GetHidGuid(&HidGuid);	
	
	/*
	API function: SetupDiGetClassDevs
	Returns: a handle to a device information set for all installed devices.
	Requires: the GUID returned by GetHidGuid.
	*/
	
	hDevInfo=SetupDiGetClassDevs 
		(&HidGuid, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		
	devInfoData.cbSize = sizeof(devInfoData);

	//Step through the available devices looking for the one we want. 
	//Quit on detecting the desired device or checking all available devices without success.

	MemberIndex = 0;
	LastDevice = FALSE;

	do
	{
		/*
		API function: SetupDiEnumDeviceInterfaces
		On return, MyDeviceInterfaceData contains the handle to a
		SP_DEVICE_INTERFACE_DATA structure for a detected device.
		Requires:
		The DeviceInfoSet returned in SetupDiGetClassDevs.
		The HidGuid returned in GetHidGuid.
		An index to specify a device.
		*/

		Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo, 
			0, 
			&HidGuid, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{
			//A device has been detected, so get more information about it.

			/*
			API function: SetupDiGetDeviceInterfaceDetail
			Returns: an SP_DEVICE_INTERFACE_DETAIL_DATA structure
			containing information about a device.
			To retrieve the information, call this function twice.
			The first time returns the size of the structure in Length.
			The second time returns a pointer to the data in DeviceInfoSet.
			Requires:
			A DeviceInfoSet returned by SetupDiGetClassDevs
			The SP_DEVICE_INTERFACE_DATA structure returned by SetupDiEnumDeviceInterfaces.
			
			The final parameter is an optional pointer to an SP_DEV_INFO_DATA structure.
			This application doesn't retrieve or use the structure.			
			If retrieving the structure, set 
			MyDeviceInfoData.cbSize = length of MyDeviceInfoData.
			and pass the structure's address.
			*/
			
			//Get the Length value.
			//The call will return with a "buffer too small" error which can be ignored.

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				NULL, 
				0, 
				&Length, 
				NULL);

			//Allocate memory for the hDevInfo structure, using the returned Length.

			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
			
			//Set cbSize in the detailData structure.

			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//Call the function again, this time passing it the returned buffer size.

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				detailData, 
				Length, 
				&Required, 
				NULL);

			// Open a handle to the device.
			// To enable retrieving information about a system mouse or keyboard,
			// don't request Read or Write access for this handle.

			/*
			API function: CreateFile
			Returns: a handle that enables reading and writing to the device.
			Requires:
			The DevicePath in the detailData structure
			returned by SetupDiGetDeviceInterfaceDetail.
			*/

			DeviceHandle=CreateFile 
				(detailData->DevicePath, 
				0, 
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING, 
				0, 
				NULL);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
			DisplayLastError("CreateFile: ");
#endif
			/*
			API function: HidD_GetAttributes
			Requests information from the device.
			Requires: the handle returned by CreateFile.
			Returns: a HIDD_ATTRIBUTES structure containing
			the Vendor ID, Product ID, and Product Version Number.
			Use this information to decide if the detected device is
			the one we're looking for.
			*/

			//Set the Size to the number of bytes in the structure.

			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes 
				(DeviceHandle, 
				&Attributes);
			
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
			DisplayLastError("HidD_GetAttributes: ");
#endif			
			//Is it the desired device?

	setUSBStatus(0); // Set USB indicators to not attached


			if (Attributes.VendorID == VENDOR_ID)
			{
				if (Attributes.ProductID == PRODUCT_ID)
				{
					//Both the Vendor ID and Product ID match.

					setUSBStatus(1); // Set USB indicators to Attached

					MyDevicePathName = detailData->DevicePath;
					//Register to receive device notifications.

					RegisterForDeviceNotifications();

					//Get the device's capablities.

					GetDeviceCapabilities();

					// Find out if the device is a system mouse or keyboard.
					
					DeviceUsage = (Capabilities.UsagePage * 256) + Capabilities.Usage;

					if (DeviceUsage == 0x102)
						{
						UsageDescription = "mouse";
						}
				
					if (DeviceUsage == 0x106)
						{
						UsageDescription = "keyboard";
						}

					if ((DeviceUsage == 0x102) | (DeviceUsage == 0x106)) 
						{
/*
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
						CDebugWinDlg::DisplayData2("");
						CDebugWinDlg::DisplayData2("*************************");
						CDebugWinDlg::DisplayData2("The device is a system " + UsageDescription + ".");
						CDebugWinDlg::DisplayData2("Windows 2000 and Windows XP don't allow applications");
						CDebugWinDlg::DisplayData2("to directly request Input reports from or "); 
						CDebugWinDlg::DisplayData2("write Output reports to these devices.");
						CDebugWinDlg::DisplayData2("*************************");
						CDebugWinDlg::DisplayData2("");
#endif
*/

					}

					// Get a handle for writing Output reports.

					WriteHandle=CreateFile 
						(detailData->DevicePath, 
						GENERIC_WRITE, 
						FILE_SHARE_READ|FILE_SHARE_WRITE, 
						(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING, 
						0, 
						NULL);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
					DisplayLastError("CreateFile: ");
#endif
					// Prepare to read reports using Overlapped I/O.

					PrepareForOverlappedTransfer();

				} //if (Attributes.ProductID == ProductID)

				else
					//The Product ID doesn't match.

					CloseHandle(DeviceHandle);

			} //if (Attributes.VendorID == VendorID)

			else
				//The Vendor ID doesn't match.

				CloseHandle(DeviceHandle);

		//Free the memory used by the detailData structure (no longer needed).

		free(detailData);

		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.

			LastDevice=TRUE;

		//If we haven't found the device yet, and haven't tried every available device,
		//try the next one.

		MemberIndex = MemberIndex + 1;

	} //do

	while ((LastDevice == FALSE) && (MyUSBDeviceDetected == FALSE));

//	if (MyUSBDeviceDetected == FALSE)
//		CDebugWinDlg::DisplayData("Device not detected");
//	else
//		CDebugWinDlg::DisplayData("Device detected");

	//Free the memory reserved for hDevInfo by SetupDiClassDevs.

	SetupDiDestroyDeviceInfoList(hDevInfo);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("SetupDiDestroyDeviceInfoList");
#endif
	return MyUSBDeviceDetected;
}


void CMainDlg::GetDeviceCapabilities()
{
	//Get the Capabilities structure for the device.

	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	API function: HidD_GetPreparsedData
	Returns: a pointer to a buffer containing the information about the device's capabilities.
	Requires: A handle returned by CreateFile.
	There's no need to access the buffer directly,
	but HidP_GetCaps and other API functions require a pointer to the buffer.
	*/

	HidD_GetPreparsedData 
		(DeviceHandle, 
		&PreparsedData);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("HidD_GetPreparsedData: ");
#endif

	/*
	API function: HidP_GetCaps
	Learn the device's capabilities.
	For standard devices such as joysticks, you can find out the specific
	capabilities of the device.
	For a custom device, the software will probably know what the device is capable of,
	and the call only verifies the information.
	Requires: the pointer to the buffer returned by HidD_GetPreparsedData.
	Returns: a Capabilities structure containing the information.
	*/
	
	HidP_GetCaps 
		(PreparsedData, 
		&Capabilities);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("HidP_GetCaps: ");

	//Display the capabilities

	ValueToDisplay.Format("%s%X", "Usage Page: ", Capabilities.UsagePage);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Input Report Byte Length: ", Capabilities.InputReportByteLength);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Output Report Byte Length: ", Capabilities.OutputReportByteLength);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Feature Report Byte Length: ", Capabilities.FeatureReportByteLength);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Link Collection Nodes: ", Capabilities.NumberLinkCollectionNodes);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Input Button Caps: ", Capabilities.NumberInputButtonCaps);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of InputValue Caps: ", Capabilities.NumberInputValueCaps);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of InputData Indices: ", Capabilities.NumberInputDataIndices);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Button Caps: ", Capabilities.NumberOutputButtonCaps);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Value Caps: ", Capabilities.NumberOutputValueCaps);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Data Indices: ", Capabilities.NumberOutputDataIndices);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Button Caps: ", Capabilities.NumberFeatureButtonCaps);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Value Caps: ", Capabilities.NumberFeatureValueCaps);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Data Indices: ", Capabilities.NumberFeatureDataIndices);
	CDebugWinDlg::DisplayData2(ValueToDisplay);
#endif

	//No need for PreparsedData any more, so free the memory it's using.

	HidD_FreePreparsedData(PreparsedData);
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("HidD_FreePreparsedData: ") ;
#endif
}


LRESULT CMainDlg::Main_OnDeviceChange(WPARAM wParam, LPARAM lParam)  
	{
  
	//CDebugWinDlg::DisplayData2("Device change detected.");

	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;

	switch(wParam) 
		{
		// Find out if a device has been attached or removed.
		// If yes, see if the name matches the device path name of the device we want to access.

		case DBT_DEVICEARRIVAL:
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
			CDebugWinDlg::DisplayData2("A device has been attached.");
#endif
			if (DeviceNameMatch(lParam))
			{
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
				CDebugWinDlg::DisplayData2("My device has been attached.");
#endif
				setUSBStatus(1); // Set USB indicators to Attached
				FindTheHID();
			}
		
			return TRUE; 
	
		case DBT_DEVICEREMOVECOMPLETE:
//#if DISPLAY_MESSAGES==YES_DISPLAY_EM
//			CDebugWinDlg::DisplayData("A device has been removed.");
//#endif
			if (DeviceNameMatch(lParam)) {
				CDebugWinDlg::DisplayData("RD-1200 has been removed");
				setUSBStatus(0); // Set USB indicators to not attached
			}
			return TRUE; 
	
		default:
			return TRUE; 
		} 
  }



void CMainDlg::OnChangeResults() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}



//void CMainDlg::OnChange_txtInputReportBufferSize() 
//{
//}


void CMainDlg::PrepareForOverlappedTransfer()
{
	//Get a handle to the device for the overlapped ReadFiles.

	ReadHandle=CreateFile 
		(detailData->DevicePath, 
		GENERIC_READ, 
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("CreateFile (ReadHandle): ");
#endif
	//Get an event object for the overlapped structure.

	/*API function: CreateEvent
	Requires:
	  Security attributes or Null
	  Manual reset (true). Use ResetEvent to set the event object's state to non-signaled.
	  Initial state (true = signaled) 
	  Event object name (optional)
	Returns: a handle to the event object
	*/

	if (hEventObject == 0)
	{
		hEventObject = CreateEvent 
			(NULL, 
			TRUE, 
			TRUE, 
			"");
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("CreateEvent: ") ;
#endif

	//Set the members of the overlapped structure.

	HIDOverlapped.hEvent = hEventObject;
	HIDOverlapped.Offset = 0;
	HIDOverlapped.OffsetHigh = 0;
	}
}


/*
void CMainDlg::ReadAndWriteToDevice()
{
	//If necessary, find the device and learn its capabilities.
	//Then send a report and request a report.

	//Clear the List Box (optional).
	//m_ResultsList.ResetContent();

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	CDebugWinDlg::DisplayData2("***HID Test Report***");
	DisplayCurrentTime();
#endif

	//If the device hasn't been detected already, look for it.

	if (MyDeviceDetected==FALSE)
		{
		MyDeviceDetected=FindTheHID();
		}
	
	// Do nothing if the device isn't detected.

	if (MyDeviceDetected==TRUE)
		{
				// Output and Input Reports

				//Write a report to the device.
				WriteOutputReport();
				//Read a report from the device.
				ReadInputReport();	
			
		} // else
}


void CMainDlg::ReadInputReport()
{

	// Retrieve an Input report from the device.

	CString	ByteToDisplay = "";

	DWORD	Result;
	
	//The first byte is the report number.
	InputReport[0]=0;

	// Find out if the "Use Control Transfers Only" check box is checked.

	UpdateData(true);

	//API call:ReadFile
	//Returns: the report in InputReport.
	//Requires: a device handle returned by CreateFile
	//(for overlapped I/O, CreateFile must be called with FILE_FLAG_OVERLAPPED),
	//the Input report length in bytes returned by HidP_GetCaps,
	//and an overlapped structure whose hEvent member is set to an event object.
	

	if (ReadHandle != INVALID_HANDLE_VALUE)
		{
		Result = ReadFile 
		(ReadHandle, 
		InputReport, 
		Capabilities.InputReportByteLength, 
		&NumberOfBytesRead,
		(LPOVERLAPPED) &HIDOverlapped); 
		}
 
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("ReadFile: ") ;
#endif
	//API call:WaitForSingleObject
	//Used with overlapped ReadFile.
	//Returns when ReadFile has received the requested amount of data or on timeout.
	//Requires an event object created with CreateEvent
	//and a timeout value in milliseconds.
	//

	Result = WaitForSingleObject 
		(hEventObject, 
		2000);

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("WaitForSingleObject: ") ;
#endif

	msgFlag=FALSE;
	switch (Result)  
	{
	case WAIT_OBJECT_0:
		{
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
		CDebugWinDlg::DisplayData2("Received Input report,");
#endif
		msgFlag=TRUE;
					
		break;
		}
	case WAIT_TIMEOUT:
		{
		//Cancel the Read operation.

		//API call: CancelIo
		//Cancels the ReadFile
        //Requires the device handle.
        //Returns non-zero on success.
		//
		
		Result = CancelIo(ReadHandle);
		
		//A timeout may mean that the device has been removed. 
		//Close the device handles and set MyDeviceDetected = False 
		//so the next access attempt will search for the device.
		CloseHandles();
		CDebugWinDlg::DisplayData("Can't read from device: Timeout");
		setUSBStatus(0); // Set USB indicators to not attached
		break;
		}
	default:
		{
		ValueToDisplay.Format("%s", "Undefined error");

		//Close the device handles and set MyDeviceDetected = False 
		//so the next access attempt will search for the device.

		CloseHandles();
		CDebugWinDlg::DisplayData("Can't read from device: Undefined error");
		setUSBStatus(0); // Set USB indicators to not attached
		break;
		}
	}

	//
	//API call: ResetEvent
	//Sets the event object to non-signaled.
	//Requires a handle to the event object.
	//Returns non-zero on success.
	//

//	ResetEvent(hEventObject);

	//Display the report data.

    DisplayInputReport();

}

//start new code
#define MAX_BTS_COUNTER 200
char bytesToSave[MAX_BTS_COUNTER];
int btsCounter=0;

int SyncInputAndOutput();
int SyncInputAndOutput() {
	DWORD elapsedMsec,startMsec;
	DWORD	Result;
	char randomByte;
	DWORD	BytesWritten = 0;

	if (ReadHandle==INVALID_HANDLE_VALUE) {
		CDebugWinDlg::DisplayData("Invalid Read Handle---Cannot resynchronize");
		return(0);
	}
	if (WriteHandle==INVALID_HANDLE_VALUE) {
		CDebugWinDlg::DisplayData("Invalid Write Handle---Cannot resynchronize");
		return(0);
	}
	CDebugWinDlg::DisplayData("Resynchronizing input and output...");
	Result=WAIT_OBJECT_0;
	InputReport[0]=0;	//The first byte is the report number.
	while (Result==WAIT_OBJECT_0) {//Clear out any input bytes by reading until timeout
		Result = ReadFile(ReadHandle,InputReport,Capabilities.InputReportByteLength, 
			&NumberOfBytesRead,(LPOVERLAPPED)&HIDOverlapped); 
		Result = WaitForSingleObject(hEventObject, INPUT_MSG_TIMEOUT_MS);
		if (Result==WAIT_OBJECT_0) { // Report on cleared-out bytes

// Bytes saved for debug purposes
			bytesToSave[btsCounter++]=InputReport[1];
			if (btsCounter>MAX_BTS_COUNTER) btsCounter=0;
			bytesToSave[btsCounter++]=InputReport[2];
			if (btsCounter>MAX_BTS_COUNTER) btsCounter=0;

			ValueToDisplay.Format("Cleared out bytes: 0x%2x 0x%2x",InputReport[1],InputReport[2]);
			CDebugWinDlg::DisplayData(ValueToDisplay);
		}
	}
	if (Result!=WAIT_TIMEOUT) {
		ValueToDisplay.Format("Error: Cannot resynchronize, WaitForSingleObject() returns %d",Result);
		CDebugWinDlg::DisplayData(ValueToDisplay);
		return(0);
	}
	startMsec=GetTickCount(); //Get a "random" byte by masking off last 8 bits of tick count
	randomByte=(char)(startMsec&(DWORD)0x0ff);
	OutputReport[0]=0;
	OutputReport[1]='X';
	OutputReport[2]=randomByte;
	Result = WriteFile(WriteHandle, OutputReport, Capabilities.OutputReportByteLength, 	&BytesWritten, 	NULL);
	if (!Result) {
		CDebugWinDlg::DisplayData("Cannot write to device---Cannot resynchronize");
		return(0);
	}
	InputReport[0]=0;	//The first byte is the report number.
	Result = ReadFile(ReadHandle,InputReport,Capabilities.InputReportByteLength, 
		&NumberOfBytesRead,(LPOVERLAPPED)&HIDOverlapped); 
	Result = WaitForSingleObject(hEventObject, INPUT_MSG_SYNC_TIMEOUT_MS);
	if (Result!=WAIT_OBJECT_0) {
		CDebugWinDlg::DisplayData("Error in reading data---Cannot resynchronize");
		return(0);
	}
	if (InputReport[1]!='X' || InputReport[2]!=randomByte) {
		CDebugWinDlg::DisplayData("Incorrect data read---Cannot resynchronize");
		return(0);
	}
	CDebugWinDlg::DisplayData("Successfully resynchronized");
//	CMainDlg::setUSBStatus(1);
	return(1);
}
*/

void CMainDlg::RegisterForDeviceNotifications()
{

	// Request to receive messages when a device is attached or removed.
	// Also see WM_DEVICECHANGE in BEGIN_MESSAGE_MAP(CMainDlg, CDialog).

	DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;
	HDEVNOTIFY DeviceNotificationHandle;

	DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
	DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;

	DeviceNotificationHandle =
		RegisterDeviceNotification(m_hWnd, &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);

}

/*

#if DISPLAY_MESSAGES==YES_DISPLAY_EM
void CMainDlg::ScrollToBottomOfListBox(USHORT Index)
{
	// 
	//Scroll to the bottom of the list box. 
	//To do so, add a line and set it as the current selection,
	//possibly scrolling the window.
	//Then deselect the line, 
	//leaving the list box scrolled to the bottom with nothing selected.
	//

	m_ResultsList.SetCurSel( Index );
	m_ResultsList.SetCurSel( -1 );
}
#endif



void CMainDlg::WriteOutputReport()
{
	//Send a report to the device.

	DWORD	BytesWritten = 0;
	INT		Index =0;
	ULONG	Result;

	UpdateData(true);

	//The first byte is the report number.

	OutputReport[0]=0;

	//
	//API Function: WriteFile
	//Sends a report to the device.
	//Returns: success or failure.
	//Requires:
	//A device handle returned by CreateFile.
	//A buffer that holds the report.
	//The Output Report length returned by HidP_GetCaps,
	//A variable to hold the number of bytes written.
	//

	if (WriteHandle != INVALID_HANDLE_VALUE)
		{
		Result = WriteFile 
		(WriteHandle, 
		OutputReport, 
		Capabilities.OutputReportByteLength, 
		&BytesWritten, 
		NULL);
	}

	//Display the result of the API call and the report bytes.
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
	DisplayLastError("WriteFile: ");
#endif

	if (!Result)
		{
		//The WriteFile failed, so close the handles, display a message,
		//and set MyDeviceDetected to FALSE so the next attempt will look for the device.

		CloseHandles();
		CDebugWinDlg::DisplayData("Can't write to device");
		setUSBStatus(0); // Set USB indicators to not attached
	} else {
#if DISPLAY_MESSAGES==YES_DISPLAY_EM
		CDebugWinDlg::DisplayData2("An Output report was written to the device.");
		strBytesWritten.Format("%s%d", "Bytes Written: ", BytesWritten); 
		CDebugWinDlg::DisplayData2(strBytesWritten);
#endif
	}
}
*/

bool MyDeviceDetected;
void CMainDlg::writeCmdUSB(int len) {
	int i;//,len;
	DWORD	BytesWritten = 0;
	CString	strBytesWritten = "";
	LONG Result;	

//	if (MyDeviceDetected==FALSE) return;
//	setMsgStatus(MSG_STATUS_TRANSMITTING); // Set Message indicators to bad
	
	//	len=(int)outMsgStr[0];
//	len=7; //only message implemented so far ("CS") length=7
	for (i=0;i<len;i+=2) {
		if (WriteHandle != INVALID_HANDLE_VALUE){
			OutputReport[0]=(char)0;
			OutputReport[1]=outMsgStr[i];
			OutputReport[2]=outMsgStr[i+1];

			Result = WriteFile(WriteHandle,OutputReport,
							Capabilities.OutputReportByteLength, 
							&BytesWritten,NULL);
			if (!Result){
			//The WriteFile failed, so close the handles, display a message,
			//and set MyDeviceDetected to FALSE so the next attempt will look for the device.

				CloseHandles();
				CDebugWinDlg::DisplayData("Can't write to device");
				setUSBStatus(0); // Set USB indicators to not attached
//				setMsgStatus(MSG_STATUS_BAD); // Set Message indicators to bad
				return;
			}
		}

	}

//	setMsgStatus(MSG_STATUS_OK); // Set Message indicators to good

//	strBytesWritten.Format("%s%c", "Message Written:",(char)outMsgStr[1]); 
//	CDebugWinDlg::DisplayData2(strBytesWritten);
}
int CMainDlg::readResp(int inMsgLengthExpected) {
	int i,len;
//	DWORD	BytesWritten = 0;
	CString	strBytesRead = "";
	LONG Result;
	DWORD elapsedMsec,startMsec;

	i=0;
//	setMsgStatus(MSG_STATUS_RECEIVING); // Set Message indicators to receiving

	len=999; //Bigger than the longest conceivable 

// If invalid handle, then just fill with ones (or random data depending on whats commented out)
	if (ReadHandle==INVALID_HANDLE_VALUE || MyDeviceDetected==FALSE) {
/*
for (i=2;i<inMsgLengthExpected;i++) {
//			inMsgParams[i-2]=(char)rand(); //Fill parameters with random values for testing
//			inMsgParams[i-2]=miscCounter++; //Fill parameters with counter value for testing
//			if (miscCounter>255) miscCounter=0;
			inMsgParams[i-2]=0x0; //Fill parameters with zeros
		}
*/

		return(0);
	}

// Get first two bytes which are response message type
	InputReport[0]=0;	//The first byte is the report number.
	Result = ReadFile(ReadHandle,InputReport,3,&NumberOfBytesRead,
		(LPOVERLAPPED) &HIDOverlapped);
	Result = WaitForSingleObject(hEventObject, INPUT_MSG_TIMEOUT_MS);
	if (Result!=WAIT_OBJECT_0) {
		CDebugWinDlg::DisplayData("Error: Could not read message type (first 2 bytes)");
		setUSBStatus(0);
		return(0);
	}

// Determine type of message from first two bytes
	inMsgChars[0]=InputReport[1];
	inMsgChars[1]=InputReport[2];
	decodeReceivedCommand();

	if (inMsgType==CMD_UNKNOWN) {
//		ValueToDisplay.Format("Unknown message %d% %d",inMsgChars[0],inMsgChars[1]);
//		CDebugWinDlg::DisplayData2(ValueToDisplay);
//	} else if (inMsgLengthActual!=inMsgLengthExpected) {
//		ValueToDisplay.Format("Incorrect length %d requested for message length %d",
//			inMsgLengthActual,inMsgLengthExpected);
//		CDebugWinDlg::DisplayData(ValueToDisplay);
//		inMsgLengthActual=inMsgLengthExpected;
		return(0);
	}

	for (i=2;i<inMsgLengthActual;i+=2) {
//		strBytesWritten.Format("%s%d", "working on byte ",i); 
//		CDebugWinDlg::DisplayData2(strBytesWritten);

		InputReport[0]=0;	//The first byte is the report number.
		Result = ReadFile(ReadHandle,InputReport,3,&NumberOfBytesRead,
			(LPOVERLAPPED) &HIDOverlapped);
		Result = WaitForSingleObject(hEventObject, INPUT_MSG_TIMEOUT_MS);
		if (Result!=WAIT_OBJECT_0) {
			ValueToDisplay.Format("Error in reading message: Byte %d of %d",i,inMsgLengthActual);
			CDebugWinDlg::DisplayData(ValueToDisplay);
			ValueToDisplay.Format("First two bytes: %c%c (0x%x,0x%x)",inMsgChars[0],inMsgChars[1],inMsgChars[0],inMsgChars[1]);
			CDebugWinDlg::DisplayData(ValueToDisplay);

// Just an experiment: try tr-transmitting a read status (RS) command
// (this will be calling readResp() recursively)
			if (debugWinFlag!=0 && recursionFlag==0) {
				recursionFlag=1;
				writeCmd(CMD_STATUS_REQ_LEN);   //Write out RS msg of length 2
				readResp(RESP_STATUS_REQ_LEN); //Read in ST msg of length 17
				recursionFlag=0;
			}
//			setMsgStatus(MSG_STATUS_BAD);
			setUSBStatus(0);
			return(0);
		}
		inMsgParams[i-2]=InputReport[1];
		inMsgParams[i-1]=InputReport[2];
//		strBytesWritten.Format("%s %d, %d", "read values ",InputReport[1],InputReport[2]); 
//		CDebugWinDlg::DisplayData2(strBytesWritten);
	}
//	setMsgStatus(MSG_STATUS_OK); // Set Message indicators to receiving
	return(1);
}
