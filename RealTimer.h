#define CS 5
#define CLK 4
#define DATA 3
#define SECONDS_READ 0x0
#define SECONDS_WRITE 0x80
#define MINUTES_READ 0x1
#define MINUTES_WRITE 0x81
#define HOURS_READ 0x2
#define HOURS_WRITE 0x82
#define DAY_READ 0x3
#define DAY_WRITE 0x83
#define DATE_READ 0x4
#define DATE_WRITE 0x84
#define MONTH_READ 0x5
#define MONTH_WRITE 0x85
#define YEAR_READ 0x6
#define YEAR_WRITE 0x86
#define CONTROL_REG 0x8F

// rtc_settings - set parameters and time
void RtcSetTime(void)
{  
	rtc_write_byte(CONTROL_REG, 0x80); // ????????? ??????????? ??????????
        rtc_write_byte(DAY_WRITE, 0x3); //3
	rtc_write_byte(DATE_WRITE, 19); // 13
	rtc_write_byte(MONTH_WRITE, 17); // 11
	rtc_write_byte(YEAR_WRITE, 19); // 13
	rtc_write_byte(HOURS_WRITE, 19); // 13
	rtc_write_byte(MINUTES_WRITE, 0x48); // ????????? ?????
	rtc_write_byte(SECONDS_WRITE, 0); // 0
	rtc_write_byte(CONTROL_REG, 0x0); // ?????? ??????????? ??????????
        
}
void RtcInitialization()
{
    TRISGbits.TRISG13 = 0; // CS_RTC out
    ConfigurateSPI2();
}
// rtc_write - write byte to rtc

// rtc_write_byte - ??????? ?????? ?????? ? RTC
// address = 0xXX -> ????? ?????
// rtc_data = 0xXX -> ??????
void rtc_write_byte(unsigned char address, unsigned char rtc_data)
{
        TRISGbits.TRISG13 = 0; // CS_RTC out
	LATGbits.LATG13 = 1; // check rtc
        spi2_write(address);
        spi2_write(rtc_data);

        TRISGbits.TRISG13 = 0; // CS_RTC out
	LATGbits.LATG13 = 0; // clr rtc
}
// rtc_read_byte - read data from rtc
// address = 0xXX -> byte adress
unsigned char RtcRead(unsigned char address)
{
        TRISGbits.TRISG13 = 0; // CS_RTC out
	LATGbits.LATG13 = 1; // check rtc
	unsigned char rtc_data; // ??????
	spi2_write(address);//
	rtc_data=spi2_read(); // ?????? ??????

	TRISGbits.TRISG13 = 0; // CS_RTC out
	LATGbits.LATG13 = 0; // uncheck rtc
	return rtc_data; // ????? ?? ???????
}
unsigned char RtcReadSeconds()
{
    unsigned char buf = RtcRead(SECONDS_READ);
    unsigned char seconds = (buf&0x7F)>>4;
    seconds*=10;
    seconds+=buf&0x0F;
}
unsigned char RtcReadMinutes()
{
    unsigned char buf = RtcRead(MINUTES_READ);
    unsigned char seconds = (buf&0x7F)>>4;
    seconds*=10;
    seconds+=buf&0x0F;
}
unsigned char RtcReadHours()
{
    unsigned char buf = RtcRead(HOURS_READ);
    unsigned char seconds = (buf&0x3F)>>4;
    seconds*=10;
    seconds+=buf&0x0F;
}
unsigned char RtcReadDayOfWeek()
{
    unsigned char buf = RtcRead(DAY_READ);
    return buf;
}
unsigned char RtcReadDays()
{
    unsigned char buf = RtcRead(DATE_READ);
    unsigned char seconds = (buf&0x7F)>>4;
    seconds*=10;
    seconds+=buf&0x0F;
}
unsigned char RtcReadMonth()
{
    unsigned char buf = RtcRead(MONTH_READ);
    unsigned char seconds = (buf&0x7F)>>4;
    seconds*=10;
    seconds+=buf&0x0F;
}
unsigned char RtcReadYear()
{
    unsigned char buf = RtcRead(YEAR_READ);
    unsigned char seconds = (buf&0xFF)>>4;
    seconds*=10;
    seconds+=buf&0x0F;
}
void RtcWriteDateInString(char *str)
{
    char dayNames[7][10] = {"Monday",
                   "Tuesday",
                   "Wednesday", "Thursday","Friday","Saturday","Sunday"};
    char digit[12];
    char seconds = RtcReadSeconds();
    char minutes = RtcReadMinutes();
    char hours = RtcReadHours();
    int year = RtcReadYear();
    char month = RtcReadMonth();
    char day = RtcReadDays();
    char day_of_week = RtcReadDayOfWeek();

    char offset = LongToString(year+2000,digit);
    strcat(str, (digit+offset));
    strcat(str, ".");
    offset = LongToString(month,digit);
    strcat(str, (digit+offset));
    strcat(str, ".");
    offset = LongToString(day,digit);
    strcat(str, (digit+offset));
    strcat(str, " ");
    offset = LongToString(hours,digit);
    strcat(str, (digit+offset));
    strcat(str, ":");
    offset = LongToString(minutes,digit);
    strcat(str, (digit+offset));
    strcat(str, ":");
    offset = LongToString(seconds,digit);
    strcat(str, (digit+offset));
    strcat(str, " ");
    strcat(str, dayNames[day_of_week-1]);
}