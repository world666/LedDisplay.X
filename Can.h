//#include <can.h>

//unsigned int Speed;
//int ReadADC(unsigned int channel);

#define FCY 		24000000             		// 20 MHz
#define BITRATE 	50000			 			// 700kHz
#define NTQ 		15							// Number of Tq cycles which will make the
												//CAN Bit Timing .
#define BRP_VAL		((FCY/(2*NTQ*BITRATE))-1)  //Formulae used for C1CFG1bits.BRP
#define BAUD_RATE 17 

void Can1Initialization(void);

void Can1SendData(unsigned int, char*, unsigned char);