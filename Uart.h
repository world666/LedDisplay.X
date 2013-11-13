/* 
 * File:   Uart.h
 * Author: andrey
 *
 * Created on 31 ?????? 2013, 14:23
 */

void OpenUART2()
{
    TRISF = 0x00;
    //LATF=0;
    U2MODEbits.STSEL = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.ABAUD = 0;
    U2BRG = 155;
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;
}
char BusyUART2(void)
{
    if(!IFS1bits.U2TXIF)
        return 1;
    else
    {
        IFS1bits.U2TXIF = 0;
        return 0;
    }
}
void WriteCharToUART2(unsigned char Data)
{
    U2TXREG = Data;
    while(BusyUART2());
}
void PrintStringUART2(unsigned char *String)
{
    while(*String)
    {
        WriteCharToUART2(*String++);
    }
}
void PrintDigitUART2(unsigned char *Data,int num)
{
    int j=0;
    for (j=0;j<num; j++)
        WriteCharToUART2(*Data++);
}

