#include "OverRiseZone.h"

extern long _highEdge;
extern long _lowEdge;
extern int _overRizeZoneHigh;
extern int _overRizeZoneLow;
extern int _overRiseControl;
char OverRiseZoneControl(long currentS)
{
    if(!_overRiseControl)
        return;
    if(currentS < _lowEdge - _overRizeZoneLow) //overise low
        WriteDigitalOutputs(2);
    else if(currentS > _highEdge + _overRizeZoneHigh)
        WriteDigitalOutputs(1);
    else
        WriteDigitalOutputs(3);
}
