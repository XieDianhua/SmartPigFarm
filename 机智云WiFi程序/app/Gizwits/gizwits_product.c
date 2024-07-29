/**
************************************************************
* @file         gizwits_product.c
* @brief        Control protocol processing, and platform-related hardware initialization
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
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "driver/hal_key.h"
#include "driver/uart.h"

/** User area The current device state structure */
dataPoint_t currentDataPoint;// 设备当前值

sendDataPoint_t sendData;
unsigned char* sendDataPointer=&sendData;
sendDataPoint_t* updata=(sendDataPoint_t*)dataBuffer;

//大小端转换函数
unsigned int BLEndianUint32(unsigned int value)
{
    return ((value & 0x000000FF) << 24) |  ((value & 0x0000FF00) << 8) |  ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000) >> 24);
}
/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t ICACHE_FLASH_ATTR gizwitsEventProcess(eventInfo_t *info, uint8_t *data, uint32_t len)
{
    uint8_t i = 0;
    dataPoint_t * dataPointPtr = (dataPoint_t *)data;
    moduleStatusInfo_t * wifiData = (moduleStatusInfo_t *)data;

    if((NULL == info) || (NULL == data))
    {
        GIZWITS_LOG("!!! gizwitsEventProcess Error \n");
        return -1;
    }

    for(i = 0; i < info->num; i++)
    {
        switch(info->event[i])
        {
        case EVENT_fan :
            currentDataPoint.valuefan = dataPointPtr->valuefan;
            GIZWITS_LOG("Evt: EVENT_fan %d \n", currentDataPoint.valuefan);
            if(0x01 == currentDataPoint.valuefan)
            {
                sendData.valuefan=1;
            }
            else
            {
                sendData.valuefan=0;
            }
            sendToMcu();
            break;
        case EVENT_spray :
            currentDataPoint.valuespray = dataPointPtr->valuespray;
            GIZWITS_LOG("Evt: EVENT_spray %d \n", currentDataPoint.valuespray);
            if(0x01 == currentDataPoint.valuespray)
            {
                sendData.valuespray=1;
            }
            else
            {
            	sendData.valuespray=0;
            }
            sendToMcu();
            break;
        case EVENT_sun_louver :
            currentDataPoint.valuesun_louver = dataPointPtr->valuesun_louver;
            GIZWITS_LOG("Evt: EVENT_sun_louver %d \n", currentDataPoint.valuesun_louver);
            if(0x01 == currentDataPoint.valuesun_louver)
            {
                sendData.valuesun_louver=1;
            }
            else
            {
            	sendData.valuesun_louver=0;
            }
            sendToMcu();
            break;
        case EVENT_exhaust_air :
            currentDataPoint.valueexhaust_air = dataPointPtr->valueexhaust_air;
            GIZWITS_LOG("Evt: EVENT_exhaust_air %d \n", currentDataPoint.valueexhaust_air);
            if(0x01 == currentDataPoint.valueexhaust_air)
            {
                sendData.valueexhaust_air=1;
            }
            else
            {
            	sendData.valueexhaust_air=0;
            }
            sendToMcu();
            break;
        case EVENT_clean :
            currentDataPoint.valueclean = dataPointPtr->valueclean;
            GIZWITS_LOG("Evt: EVENT_clean %d \n", currentDataPoint.valueclean);
            if(0x01 == currentDataPoint.valueclean)
            {
                sendData.valueclean=1;
            }
            else
            {
            	sendData.valueclean=0;
            }
            sendToMcu();
            break;

        case WIFI_SOFTAP:
            break;
        case WIFI_AIRLINK:
            break;
        case WIFI_STATION:
            break;
        case WIFI_CON_ROUTER:
            GIZWITS_LOG("@@@@ connected router\n");
 
            break;
        case WIFI_DISCON_ROUTER:
            GIZWITS_LOG("@@@@ disconnected router\n");
 
            break;
        case WIFI_CON_M2M:
            GIZWITS_LOG("@@@@ connected m2m\n");
			setConnectM2MStatus(0x01);
 
            break;
        case WIFI_DISCON_M2M:
            GIZWITS_LOG("@@@@ disconnected m2m\n");
			setConnectM2MStatus(0x00);
 
            break;
        case WIFI_RSSI:
            GIZWITS_LOG("@@@@ RSSI %d\n", wifiData->rssi);
            break;
        case TRANSPARENT_DATA:
            GIZWITS_LOG("TRANSPARENT_DATA \n");
            //user handle , Fetch data from [data] , size is [len]
            break;
        case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
            break;
            
        default:
            break;
        }
    }
    system_os_post(USER_TASK_PRIO_2, SIG_UPGRADE_DATA, 0);
    
    return 0; 
}


/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void ICACHE_FLASH_ATTR userHandle(void)
{
	if(updataFlag) {
			currentDataPoint.valuetemp=updata->valuetemp;
			currentDataPoint.valuehumidity=updata->valuehumidity;
			currentDataPoint.valueco2_ppm=updata->valueco2_ppm;
			currentDataPoint.valuenh3_ppm=updata->valuenh3_ppm;
			currentDataPoint.valuelight=updata->valuelight;
		}

    system_os_post(USER_TASK_PRIO_2, SIG_UPGRADE_DATA, 0);
}


/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void ICACHE_FLASH_ATTR userInit(void)
{
    gizMemset((uint8_t *)&currentDataPoint, 0, sizeof(dataPoint_t));

 	/** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
   		currentDataPoint.valuefan = 0;
   		currentDataPoint.valuespray = 0;
   		currentDataPoint.valuesun_louver = 0;
   		currentDataPoint.valueexhaust_air = 0;
   		currentDataPoint.valueclean = 0;
   		currentDataPoint.valuetemp = 0;
   		currentDataPoint.valuehumidity = 0;
   		currentDataPoint.valueco2_ppm = 0;
   		currentDataPoint.valuenh3_ppm = 0;
   		currentDataPoint.valuelight = 0;
}
