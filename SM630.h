#ifndef SM630_H
#define SM630_H

#endif // SM630_H

//The necessary header files...

#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/types.h>

//Change the device name here if you want to...

#define DEVICE "/dev/ttySAC1";
#define FALSE 0
#define TRUE 1

//Command MACROS


#define PKT_HEAD_1 0x4D
#define PKT_HEAD_2 0x58

#define ADD_FINGERPRINT 0x40
#define DEL_FINGERPRINT 0x42
#define SEARCH_FINGERPRINT 0x44
#define EMPTY_DATABASE 0x46
#define SEARCH_DATABASE 0x4B
#define DOWNLOAD_TEMPLATE 0x50
#define UPLOAD_TEMPLATE 0x52
#define READ_ID 0x60
#define READ_USER_FLASH 0x62
#define WRITE_USER_FLASH 0x64
#define READ_LOGO 0x80

//Response Code

#define RECV_CORRECT 0x01
#define RECV_ERROR 0x02
#define OP_SUCCESS 0x31
#define FINGER_DETECT 0x32
#define TIME_OUT 0x33
#define FINGER_FALIURE 0x34
#define PARAM_ERROR 0x35
#define FINGER_MATCH_ID 0x37
#define NO_FINGER_MATCH_ID 0x38
#define FINGER_FOUND 0x39
#define FINGER_NOT_FOUND 0x3A

//Packet Flag

#define COMMAND_PKT 0x10
#define DATA_PKT 0x20
#define RESPONSE_PKT 0x30
#define LAST_PKT 0x21


// the required global variables

FILE* output;                                   //Handler for output terminal
char devicename[80] = DEVICE;                   //Name of the serial device
int status;
int wait_flag=TRUE;
unsigned char rec[300];
int fd, tty, c, res, i, error;                  //tty is the user console
char In1, Key;



long BAUD;
long DATABITS;
long PARITYON;
long STOPBITS;
long PARITY;

struct termios newtio,oldtio;
struct sigaction saio;


int bytes_expected;
