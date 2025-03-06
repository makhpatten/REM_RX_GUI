void init_com_port();
extern 	HANDLE   m_hCom;
extern 	BOOL     bWriteRC;
extern 	DWORD iBytesWritten;
extern 	DWORD iBytesRead;
extern 	BOOL   bReadRC;

#define COM_STATUS_OK 0
#define COM_STATUS_UNINITIALIZED 1
#define COM_STATUS_CANT_OPEN 2
#define COM_STATUS_CANT_WRITE	3
#define COM_STATUS_CANT_READ 4
#define COM_STATUS_BAD_SYNC 5
#define COM_STATUS_CANT_GET_STATE	6
#define COM_STATUS_CANT_SET_STATE	7
#define COM_STATUS_CANT_GET_TIMEOUTS	8
#define COM_STATUS_CANT_SET_TIMEOUTS	9
#define COM_STATUS_CANT_SET_BUFFER	10
#define	COM_STATUS_NO_RESPONSE	11
#define COM_STATUS_DEVICE_FOUND 88

#define COM_STATUS_WEIRD_ERROR 99

