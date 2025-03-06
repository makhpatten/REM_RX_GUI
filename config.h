#define XINTERFACE_USB 0 // set this to other than 1 for RS-232
#define STATUS_UPDATE_TIME 100 // time in milisecs between "rs" request for status commands

#define CHANNELS_CYCLE_TIME 200 // time in milisecs between each tune step of the channels window

#define COM_INIT_TIMER 20
#define USB_INIT_TIMER 20
#define USB_UPDATE_TIME 10
#define COM_TIMEOUT_MS 1000
#define RESEND_PLAYBACK_TIMEOUT_MS 2000 // time in milisecs before a playback time is resent
#define MAX_COM_PORT_NUMBER 99
#define PORT_TYPE_RS232 0
#define PORT_TYPE_TCPIP 1

#define SIMPLE_GUI 1 // 1 indicates no audio control or control transmitter, 0 otherwise

#define PLAYBACK_START_TIME 1000 // time in miliseconds to wait for playback start before reissuing command

#define CT148_MODE 0 // so far only used to redefine "tp" command as either playback or set crypto key