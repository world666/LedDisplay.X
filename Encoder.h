char EncoderReadF1()
{
    char in;
    TRISBbits.TRISB0=1;//input
    in = 0;
    in+=PORTBbits.RB0; delay(1);
    in+=PORTBbits.RB0; delay(1);
    in+=PORTBbits.RB0; delay(1);
    if(in>=2)
        return 1;
    else
        return 0;
}
char EncoderReadF2()
{
    char in;
    TRISBbits.TRISB1=1;
    in = 0;
    in+=PORTBbits.RB1; delay(1);
    in+=PORTBbits.RB1; delay(1);
    in+=PORTBbits.RB1; delay(1);
    if(in>=2)
        return 1;
    else
        return 0;
}
long EncPositionCounter = 0;//position counter
char EncState = -1;//encoder prev state
void EncoderScan(void)
{
    TRISBbits.TRISB0=1;//input F1.1
    TRISBbits.TRISB1=1;//input F1.2
char New;
New = PORTB & 0x03;
//impuls investigation
switch(EncState)
	{
	case 2:
		{
		if(New == 3) EncPositionCounter++;
		if(New == 0) EncPositionCounter--;
		break;
		}

	case 0:
		{
		if(New == 2) EncPositionCounter++;
		if(New == 1) EncPositionCounter--;
		break;
		}
	case 1:
		{
		if(New == 0) EncPositionCounter++;
		if(New == 3) EncPositionCounter--;
		break;
		}
	case 3:
		{
		if(New == 1) EncPositionCounter++;
		if(New == 2) EncPositionCounter--;
		break;
		}
	}
EncState = New;		// ?????????? ????? ????????
				// ??????????? ?????????
}

long EncStartVcounter = 0;
long Vvalue = 0;
long EncCountV()
{
    Vvalue= EncPositionCounter - EncStartVcounter;
    EncStartVcounter = EncPositionCounter;
    return Vvalue;
}
char EncGetDistance(char *str)
{
    long marks = (EncPositionCounter>>2);
    long distance = marks*DISTANCE_PER_MARKS;//travel distance
    char offset = LongToString(distance,str);//view distance
    return offset;
}