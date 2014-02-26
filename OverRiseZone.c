#include "OverRiseZone.h"

extern long _highEdge;
extern long _lowEdge;
extern int _overRizeZoneHigh;
extern int _overRizeZoneLow;

char OverRiseZoneControl(long currentS)
{
    if(currentS < _lowEdge - _overRizeZoneLow) //overise low
        WriteDigitalOutputs(2);
    else if(currentS > _highEdge + _overRizeZoneHigh)
        WriteDigitalOutputs(1);
    else
        WriteDigitalOutputs(3);
}
