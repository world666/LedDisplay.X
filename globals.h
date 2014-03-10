/* 
 * File:   globals.h
 * Author: andrey
 *
 * Created on 24 ?????? 2014, 10:43
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

int _nodeId;
float _distancePerMarks; //mm
long _highEdge;
long _lowEdge;
int _synchronization;
int _synchZone;
int _overRiseControl = 1;
int _kolibrovka = 1;
int _overRizeZoneHigh;
int _overRizeZoneLow;
int _buffer;
long overSpeedS[20];
int overSpeedV[20];
long overSpeedIS[120];
int overSpeedIV[120];

//parameters ids
#define ENCODER_COUNTER 0x2001
#define NODE_ID 0x2002
#define DISTANCE_PER_MARKS 0x2003
#define HIGH_EDGE 0x2004
#define LOW_EDGE 0x2005
#define SYNCHRONIZATION 0x2006
#define SYNCH_ZONE 0x2007
#define OVER_RIZE_ZONE_HIGH 0x2008
#define OVER_RIZE_ZONE_LOW 0x2009
#define DEFENCE_DIAGRAM 0x200A

void ReadConfig()
{   
    ReadParameterValue(NODE_ID,&_nodeId);
    ReadParameterValue(DISTANCE_PER_MARKS,&_distancePerMarks);
    ReadParameterValue(HIGH_EDGE,&_highEdge);
    ReadParameterValue(LOW_EDGE,&_lowEdge);
    ReadParameterValue(SYNCHRONIZATION,&_synchronization);
    ReadParameterValue(SYNCH_ZONE,&_synchZone);
    ReadParameterValue(OVER_RIZE_ZONE_HIGH,&_overRizeZoneHigh);
    ReadParameterValue(OVER_RIZE_ZONE_LOW,&_overRizeZoneLow);
    char codtDomain[120];
    char count = ReadParameterValue(DEFENCE_DIAGRAM,codtDomain);
    int i=0;
    long* s;
    int* v;
    for(i;i<20;i++)
    {
        s = (codtDomain + i*6);
        v = (codtDomain + i*6 + 4);
        overSpeedS[i] = *s;
        overSpeedV[i] = *v;
    }
    OverSpeedInterpolation(overSpeedS,overSpeedV,overSpeedIS,overSpeedIV);
}

#endif	/* GLOBALS_H */

