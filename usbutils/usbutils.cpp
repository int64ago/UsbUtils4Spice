#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usbutils.h"
#include "libwdi.h"

int char2int(char ch)
{
	ch = tolower(ch);
	return ch >= '0' && ch <= '9'?(ch - '0'):(ch - 'a' + 10);
}
//USB\Class_08&SubClass_06&Prot_50
int getClass(char *comID)
{
	char *p = strstr(comID, "Class_");
	return (char2int(p[6]) << 4) + char2int(p[7]);
}

int getUsbList(UsbInfo usbInfo[])
{
	int usbNum = 0;
	struct wdi_device_info *device, *list;
	struct wdi_options_create_list ocl = { 0 };
	ocl.list_all = TRUE;
	ocl.list_hubs = FALSE;
	ocl.trim_whitespaces = FALSE;
	if (wdi_create_list(&list, &ocl) == WDI_SUCCESS){
		for (device = list; device != NULL; device = device->next){
			usbInfo[usbNum].pid = device->pid;
			usbInfo[usbNum].vid = device->vid;
			sprintf(usbInfo[usbNum].desc, "%s %s", 
				device->desc, wdi_get_vendor_name(device->vid));
			usbInfo[usbNum].clas = getClass(device->compatible_id);
			++ usbNum;
		}
		wdi_destroy_list(list);
	}
	return usbNum;
}
/*
int main()
{
	UsbInfo usbInfo[10];
	int num = getUsbList(usbInfo);
	for(int i = 0; i < num; ++i)
		printf("pid:%d vid:%d clas:%d desc:%s\n",
			usbInfo[i].pid,
			usbInfo[i].vid,
			usbInfo[i].clas,
			usbInfo[i].desc);
	return 0;
}*/
