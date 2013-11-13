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
void FramWrite(unsigned int address,unsigned char data)
{
    FramWriteEnable();
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 0; // check fram
    spi2_write(WRITE_MEMORY_DATA);
    spi2_write(address>>8);
    spi2_write(address & 0x00FF);
    spi2_write(data);
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 1; // uncheck fram
}
unsigned char FramRead(unsigned int address)
{
    TRISGbits.TRISG12 = 0; // CS_FR out
    LATGbits.LATG12 = 0; // check fram
    unsigned char fram_data;
    spi2_write(READ_MEMORY_DATA);
    spi2_write(address>>8);
    spi2_write(address & 0x00FF);
    fram_data = spi2_read();
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