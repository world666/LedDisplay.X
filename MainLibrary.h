/* 
 * File:   MainLibrary.h
 * Author: andrey
 *
 * Created on 31 ?????? 2013, 15:35
 */
void delay(long time)
{
    long i=0;
    for(i=0;i<time;i++);
}

unsigned int LongToString(long digit,char *result)
{
    result[11]=0;
    char sign = 0;//+
    long buf;
    int i =10;
    if(digit==0)
        result[i--]=0x30;
    if(digit<0)
    {
        digit=(~digit)+1;
        sign=-1;//-
    }
    while(digit>0)
    {
        buf = digit;
        buf%=10;
        result[i--] = buf + 0x30;
        digit/=10;
    }
    if(sign==-1)
        result[i--]='-';
    return (i+1);
}
void LongToCharArray(long digit,char *result)
{
    char *ch = &digit;
    result[0] = *(ch+0);
    result[1] = *(ch+1);
    result[2] = *(ch+2);
    result[3] = *(ch+3);
}
