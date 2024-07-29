#ifndef _WIFI_H_
#define _WIFI_H_

#include "sys.h"

typedef unsigned char bool;//定义布尔类型

#pragma pack(1) //使结构体字节对齐方式为一字节对齐

typedef struct { 
	  bool valuefan;
	  bool valuespray;
	  bool valuesun_louver;
	  bool valueexhaust_air;
	  bool valueclean;
	  uint32_t valuetemp;
	  uint32_t valuehumidity;
	  uint32_t valueco2_ppm;
	  uint32_t valuenh3_ppm;
	  uint32_t valuelight;
} dataPoint;

#pragma pack()

typedef struct {
	 bool valuefan;
	 bool valuespray;
	 bool valuesun_louver;
	 bool valueexhaust_air;
	 bool valueclean;
}	lastDataPoint;

extern dataPoint* getDataStructure;
extern lastDataPoint lastDataStructure;

void gizwitsControlProcess(void);
void getSensorData(void);
void dataConver(void);
void uploadToServer(void);

#endif