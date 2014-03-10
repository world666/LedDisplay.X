#include "OverSpeedControl.h"
#include <xc.h>
extern long _highEdge;
extern long _lowEdge;
extern long overSpeedIS[120];
extern int overSpeedIV[120];
void OverSpeedInterpolation(long* coordinate, int* speed, long* interCoordinate, int* interSpeed)
{
                    int vStep = -100; //0.1 m/sec
                    int k = 0;
                    int i;
                    for (i = 0; coordinate[i] != 2147483647; i++)
                    {
			interCoordinate[k] = coordinate[i];
                        interSpeed[k] = speed[i];
			k++;
                        int speed2 = speed[i + 1];
                        int speed1 = speed[i];
                        int vSub = speed2 - speed1;
                        int intervalsNum = abs(vSub/vStep);
                        if (intervalsNum == 0)
                        {
                            intervalsNum = 0;
                            continue;
                        }
                        long sStep;
                        if(coordinate[i+1] == 2147483647)
                            sStep = abs((_highEdge - coordinate[i])/intervalsNum);
                        else
                            sStep = abs((coordinate[i + 1] - coordinate[i])/intervalsNum);
                        int j=1;
                        for (j = 1; j < intervalsNum; j++)
                        {
                                interCoordinate[k] = coordinate[i] + j*sStep;
                                interSpeed[k] = speed[i] + j*vStep;
								k++;
                        }
                    }

                        interCoordinate[k] = _highEdge;
                        interSpeed[k] = speed[i];
}
int OverSpeedGetMaxV(long s,int speed)
{
    int i=0;
    if(speed<0)//move down
        s = _lowEdge + _highEdge - s;
    if(s>=_highEdge)
        s = _highEdge-1;
    for(i;;i++)
    {
        if(overSpeedIS[i]>s)
            break;
    }
    return overSpeedIV[i];
}

void OnBreak()
{
    TRISDbits.TRISD1 = 0;//output OE
    TRISDbits.TRISD2 = 0;//output LE
    //write output digit (RB8-RB15)
    TRISB |= 0xFF00;//input

    LATDbits.LATD2 = 0; //clr LE
    LATDbits.LATD1 = 1; //set OE
    TRISB &= 0x00FF;//output
    PORTB = PORTB&0xBFFF;
    LATDbits.LATD2 = 1;//set LE (D17 save data)
    delay(25);
    LATDbits.LATD2 = 0;//set LE (D17 save data)
    delay(25);
}