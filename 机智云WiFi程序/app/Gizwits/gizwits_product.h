/**
************************************************************
* @file         gizwits_product.h
* @brief        Corresponding gizwits_product.c header file (including product hardware and software version definition)
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         鏈烘櫤浜�.鍙负鏅鸿兘纭欢鑰岀敓
*               Gizwits Smart Cloud  for Smart Products
*               閾炬帴|澧炲�贾祙寮�鏀緗涓珛|瀹夊叏|鑷湁|鑷敱|鐢熸��
*               www.gizwits.com
*
***********************************************************/
#ifndef _GIZWITS_PRODUCT_H_
#define _GIZWITS_PRODUCT_H_

#include "gizwits_protocol.h"

/**
* MCU software version number
*/
#define SOFTWARE_VERSION                        "03030000"

/**
* MCU hardware version number
*/
#define HARDWARE_VERSION                        "03000001"


/**
* Gagent minor version number for OTA upgrade
* OTA hardware version number: 00ESP826
* OTA software version number: 040206xx // "xx" is version number defaults to "25", consistent with the Gagent library version
*/
#define SDK_VERSION                             "25"    

#ifndef SOFTWARE_VERSION
    #error "no define SOFTWARE_VERSION"
#endif

#ifndef HARDWARE_VERSION
    #error "no define HARDWARE_VERSION"
#endif


/** User area The current device state structure */
extern dataPoint_t currentDataPoint;
extern sendDataPoint_t sendData;
extern unsigned char* sendDataPointer;
/** User area data point initialization */
void userInit(void);

/** User area device status detection */
void userHandle(void);
void sendToMcu(void);
/** User zone event handling */
int8_t gizwitsEventProcess(eventInfo_t * info, uint8_t * data, uint32_t len);

#endif
