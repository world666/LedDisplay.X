/* 
 * File:   FRAM.h
 * Author: andrey
 *
 * Created on 13 ????????? 2013, 14:15
 */
#define WRITE_ENABLE      0b00000110
#define WRITE_MEMORY_DATA 0b00000010
#define READ_MEMORY_DATA  0b00000011
#define READ_STATUS_REGISTER 0b00000101
void FramInitialization()
{
    TRISGbits.TRISG12 = 0; // CS_FR out
    ConfigurateSPI2();
}
void FramWriteEnable()
{
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 0; // check fram
    spi2_write(WRITE_ENABLE);
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 1; // uncheck fram
}
void FramWrite(unsigned int address,char *data, int length)
{
    FramWriteEnable();
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 0; // check fram
    spi2_write(WRITE_MEMORY_DATA);
    spi2_write(address>>8);
    spi2_write(address & 0x00FF);
    int i;
    for(i=0; i<length;i++)
    {
        spi2_write(*data++);
    }
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 1; // uncheck fram
}
void FramRead(unsigned int address,char *data, int length)
{
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 0; // check fram
    unsigned char fram_data;
    spi2_write(READ_MEMORY_DATA);
    spi2_write(address>>8);
    spi2_write(address & 0x00FF);
    int i;
    for(i=0; i<length;i++)
    {
        *data++ = spi2_read();
    }
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 1; // uncheck fram
    return fram_data;
}
unsigned char FramReadStatus()
{
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 0; // check fram
    unsigned char fram_data;
    spi2_write(READ_STATUS_REGISTER);
    fram_data = spi2_read();
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 1; // uncheck fram
    return fram_data;
}
long FramReadPositionCounter()
{
    char data[4];
    FramRead(0x0, data, 4);
    long *rezult = &data[0];
    return *rezult;
}