/* 
 * File:   MainLibrary.h
 * Author: andrey
 *
 * Created on 31 ?????? 2013, 15:35
 */
void delay(int time)
{
    int i=0;
    for(i=0;i<time;i++);
}

unsigned int LongToString(long digit,char *result)
{
    result[31]=0;
    long buf;
    int i =30;
    if(digit==0)
        result[i--]=0x30;
    while(digit>0)
    {
        buf = digit;
        buf%=10;
        result[i--] = buf + 0x30;
        digit/=10;
    }
    return (i +1);
}
void LongToCharArray(long digit,char *result)
{
    result[4]=0;
    char *ch = &digit;
    result[0] = *(ch+0);
    result[1] = *(ch+1);
    result[2] = *(ch+2);
    result[3] = *(ch+3);
}
