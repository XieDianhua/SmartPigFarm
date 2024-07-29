#ifndef _HMI_H
#define _HMI_H

#define waterPump PGout(13) 
#define exhaust   PGout(14) 
#define aeration  PGout(15) 

//void hmiControlProcess(void);
void uploadToHmi(void);
void endBit(void);

#endif