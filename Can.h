//#include <can.h>

//unsigned int Speed;
//int ReadADC(unsigned int channel);

#define FCY 		24000000             		// 20 MHz
#define BITRATE 	50000			 			// 700kHz
#define NTQ 		16							// Number of Tq cycles which will make the
												//CAN Bit Timing .
#define BRP_VAL		((FCY/(2*NTQ*BITRATE))-1)  //Formulae used for C1CFG1bits.BRP
#define BAUD_RATE 3

/**
 * @author Kyrylov Andrii
 * @todo init can 1
 */
void Can1Initialization(void);

/**
 * @autor Kyrylov Andrii
 * @param unsigned int - message id
 * @param char* - data
 * @param unsigned char buf number
 * @todo Send data(8 byte) over can interface
 */
void Can1SendData(unsigned int, char*, unsigned char);

/**
 * @autor Kyrylov Andrii
 * @param char* - output buffer
 * @todo Read data(8 byte) over can interface
 */
void Can1ReceiveData(char*);