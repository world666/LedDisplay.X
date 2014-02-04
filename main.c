/* 
 * File:   main.c
 * Author: andrey
 *
 * Created on 30 ?????? 2013, 9:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>

#include "Configuration.h"
#include "LowVoltageDetect.h"
#include "MainLibrary.h"
#include "DigitalInputs.h"
#include "Uart.h"
#include "Timer.h"
#include "Encoder.h"
#include "Display.h"
#include "Spi.h"
#include "RealTimer.h"
#include "FRAM.h"
#include "Fat.h"
// FOSC
#pragma config FOSFPR = XT_PLL16             // Oscillator (XT)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_45            // Brown Out Voltage (4.5)
#pragma config BOREN = PBOR_OFF         // PBOR Enable (Disable)
#pragma config MCLRE = MCLR_EN         // Master Clear Enable (Enable)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)


// Function prototype for timer 1 ISR
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);
// Function prototype for timer 2 ISR
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void);
// Function prototype for timer 3 ISR
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void);

int main(int argc, char** argv) {
    ADPCFG = 0xFFFF;//RB only digit
    DisplayInitialization(); //lcd display init
    RtcInitialization(); //realtime counter init
    //RtcSetTime();
    FramInitialization(); //fram init
    //EncPositionCounter = FramReadPositionCounter(); //read position counter adr =0
    LVDinitialization(); //voltage detect interrupt
    
    OpenUART2();
    //StartTimer1();
    //StartTimer2();
    //StartTimer3();
    //PrintStringUART2("Start");

    DisplayView("start"); //lcd display write
    ReadBootSector();
    
    while(1)
    {


    }
    return (EXIT_SUCCESS);
}
// Timer 1 interrupt service write data to uart
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{
    // Clear Timer 1 interrupt flag
    _T1IF = 0;
    TRISCbits.TRISC13 = 0;
    // Toggle LED on RD1
    LATCbits.LATC13 = 1 - LATCbits.LATC13;

    TRISDbits.TRISD0 = 0;//out WDT
    LATDbits.LATD0 = 1 -  LATDbits.LATD0;

    char signals = ReadDigitalInputs();
    
    // write to uart encoder counter
    char str[60]="";
    char sDistance[12];
    char sSignals[9];
    
    RtcWriteDateInString(str); //time and date
    while(strlen(str)<32)
      strcat(str," ");

    char offset = EncGetDistance(sDistance);//distance in mm
    strcat(str, sDistance+offset);
    strcat(str, " ");
    offset = LongToString(EncF3Counter,sDistance);//f3 counter
    strcat(str, sDistance+offset);
    while(strlen(str)<48)
      strcat(str," ");

    DigitalInputsToString(sSignals,signals);//8 analog signals
    strcat(str,sSignals);
    while(strlen(str)<64)
      strcat(str," ");

    DisplayView(str);

    //LongToCharArray(140,sDistance);
    //PrintDigitUART2(sDistance,4);
  
 
   
    //LongToCharArray((Vvalue),str);
    //PrintDigitUART2(str,4);
}
// Timer 2 interrupt service count encoder signal f1 f2
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void)
{
    // Clear Timer 2 interrupt flag
    _T2IF = 0;
    EncoderScan();
}
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void)
{
    // Clear Timer 3 interrupt flag
    _T3IF = 0;

     TRISCbits.TRISC14 = 0;
    // Toggle LED on RD1
    LATCbits.LATC14 = 1 - LATCbits.LATC14;
    EncCountV();
}

void __attribute__((__interrupt__, __auto_psv__)) _LVDInterrupt(void) //low voltage detcetion
//save data in fram
{
    _LVDIF = 0; //clear interrupt flag
    //fram write position counter
    char data[4];
    LongToCharArray(EncPositionCounter,data);
    FramWrite(0x0,data,4); //adr=0
}