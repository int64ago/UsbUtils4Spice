#ifndef _USBUTILS_H
#define _USBUTILS_H

#define MAX_LEN_ 256
typedef struct{
	char desc[MAX_LEN_];
	int pid;
	int vid;
	int clas;
}UsbInfo;
extern "C" _declspec (dllexport)
int getUsbList(UsbInfo usbInfo[]);
#endif