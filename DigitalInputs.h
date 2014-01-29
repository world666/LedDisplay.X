/* 
 * File:   DigitalInputs.h
 * Author: andrey
 *
 * Created on 31 ?????? 2013, 9:15
 */
char ReadDigitalInputs()
{
    TRISDbits.TRISD1 = 0;//output OE
    TRISDbits.TRISD2 = 0;//output LE

    //read input digit (RB8-RB15)
    TRISB |= 0xFF00;//input
    LATDbits.LATD2 = 0;
    LATDbits.LATD1 = 0; //clr OE (D16 save data)
    delay(25);
    int raData = PORTB;


    LATDbits.LATD1 = 1;
    TRISB &= 0x00FF;//output
    PORTB = raData;
    LATDbits.LATD2 = 1;//set LE (D17 save data)
    delay(25);
    return ~(raData>>8);
}

void DigitalInputsToString(char *str,char signals)
{
    str[8]=0;
    int i=0;
    for(i;i<8;i++)
    {
        str[i]=signals&1;
        str[i]+=0x30;
        signals=signals>>1;
    }
}

