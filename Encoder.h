/**
 * @author Kyrylov Andrii
 * @todo read F1 with program filter
 */
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
/**
 * @author Kyrylov Andrii
 * @todo read F2 with program filter
 */
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
char EncF3Counter = -1;
char EncF3State = 0; //prev F3 state

/**
 * @author Kyrylov Andrii
 * @todo scan f1, f2, f3 signals and count current position in ticks
 */
void EncoderScan(void)
{
    TRISBbits.TRISB0=1;//input F1.1
    TRISBbits.TRISB1=1;//input F1.2
    /*TRISDbits.TRISD3=1;//input F1.3
    if(PORTDbits.RD3 == 1)
    {
        if(EncF3State==0)
        {
          if(EncF3Counter == -1)
              EncPositionCounter = 0;
          EncF3Counter++;
        }
    }
    EncF3State = PORTDbits.RD3;*/
    
char New;
New = PORTB & 0x03;
//impuls investigation
switch(EncState)
	{
	case 2:
		{
		if(New == 3) EncPositionCounter--;
		if(New == 0) EncPositionCounter++;
		break;
		}

	case 0:
		{
		if(New == 2) EncPositionCounter--;
		if(New == 1) EncPositionCounter++;
		break;
		}
	case 1:
		{
		if(New == 0) EncPositionCounter--;
		if(New == 3) EncPositionCounter++;
		break;
		}
	case 3:
		{
		if(New == 1) EncPositionCounter--;
		if(New == 2) EncPositionCounter++;
		break;
		}
	}
EncState = New;		// ?????????? ????? ????????
				// ??????????? ?????????
}

long EncStartVcounter = 0;
int Vvalue = 0;

/**
 * @author Kyrylov Andrii
 * @todo count speed from position
 */
void EncCountV()
{
    Vvalue= EncPositionCounter - EncStartVcounter;
    EncStartVcounter = EncPositionCounter;
}

/**
 * @author Kyrylov Andrii
 * @param *str pointer to output string
 * @todo convert current distance to string
 * @return offset in str
 */
char EncGetDistanceStr(char *str)
{
    long marks = (EncPositionCounter>>2);
    long distance = marks*DISTANCE_PER_MARKS;//travel distance
    char offset = LongToString(distance,str);//view distance
    return offset;
}

/**
 * @author Kyrylov Andrii
 * @todo convert current counter to distance in mm
 * @return distance in mm
 */
long EncGetDistanceLong()
{
    long marks = (EncPositionCounter>>2);
    long distance = marks*DISTANCE_PER_MARKS;//travel distance
    return distance;
}

int EncGetV()
{
    int speed = Vvalue>>2;
    speed*=DISTANCE_PER_MARKS;
    return Vvalue/1.07;
}