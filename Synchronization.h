/* 
 * File:   Synchronization.h
 * Author: andrey
 *
 * Created on 25 ?????? 2014, 13:31
 */
char TrySynchronization(char inputSignals)
{
    if(!_synchronization)
        return 0;
    long currentDistance = EncGetDistanceLong();
    if(inputSignals&0x01)//???
    {
        if(currentDistance>_lowEdge+_synchZone)
            return 0;
        EncPositionCounter = EncDistanceToCounter(_lowEdge);
        return 1;
    }
    else if(inputSignals&0x02)
    {
        if(currentDistance<_highEdge-_synchZone)
            return 0;
        EncPositionCounter = EncDistanceToCounter(_highEdge);
        return 1;
    }
    return 0;
}

