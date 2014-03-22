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
int _kolibrovka = 0;
int _overRizeZoneHigh;
int _overRizeZoneLow;
int _buffer;

long overSpeedIS1[120]; int overSpeedIV1[120];
long overSpeedIS2[120]; int overSpeedIV2[120];
long overSpeedIS3[120]; int overSpeedIV3[120];
long overSpeedIS4[120]; int overSpeedIV4[120];
int _buffer2;

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
#define DEFENCE_DIAGRAM1 0x200A
#define DEFENCE_DIAGRAM2 0x200B
#define DEFENCE_DIAGRAM3 0x200C
#define DEFENCE_DIAGRAM4 0x200D

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
    ReadCodtDomainValue(DEFENCE_DIAGRAM1,overSpeedIS1,overSpeedIV1);
    ReadCodtDomainValue(DEFENCE_DIAGRAM2,overSpeedIS2,overSpeedIV2);
    ReadCodtDomainValue(DEFENCE_DIAGRAM3,overSpeedIS3,overSpeedIV3);
    ReadCodtDomainValue(DEFENCE_DIAGRAM4,overSpeedIS4,overSpeedIV4);
}
void ReadCodtDomainValue( int parameterId, char* overSpeedIS, char* overSpeedIV)
{
    char codtDomain[120];
    long overSpeedS[20];
    int overSpeedV[20];
    ReadParameterValue(parameterId,codtDomain);
    int i=0;
    long* s;
    int* v;
    for(i;i<20;i++)
    {
        s = (codtDomain + i*6); v = (codtDomain + i*6 + 4);
        overSpeedS[i] = *s; overSpeedV[i] = *v;
    }
    OverSpeedInterpolation(overSpeedS,overSpeedV,overSpeedIS,overSpeedIV);
}
void UpdateConfig(int parameterId)
{
    switch(parameterId)
    {
        case ENCODER_COUNTER:
            break;
        case NODE_ID:
            ReadParameterValue(NODE_ID,&_nodeId);
            break;
        case DISTANCE_PER_MARKS:
            ReadParameterValue(DISTANCE_PER_MARKS,&_distancePerMarks);
            break;
        case HIGH_EDGE:
            ReadParameterValue(HIGH_EDGE,&_highEdge);
            break;
        case LOW_EDGE:
            ReadParameterValue(LOW_EDGE,&_lowEdge);
            break;
        case SYNCHRONIZATION:
            ReadParameterValue(SYNCHRONIZATION,&_synchronization);
            break;
        case SYNCH_ZONE:
            ReadParameterValue(SYNCH_ZONE,&_synchZone);
            break;
        case OVER_RIZE_ZONE_HIGH:
            ReadParameterValue(OVER_RIZE_ZONE_HIGH,&_overRizeZoneHigh);
            break;
        case OVER_RIZE_ZONE_LOW:
            ReadParameterValue(OVER_RIZE_ZONE_LOW,&_overRizeZoneLow);
            break;
        case DEFENCE_DIAGRAM1:
            ReadCodtDomainValue(DEFENCE_DIAGRAM1,overSpeedIS1,overSpeedIV1);
            break;
        case DEFENCE_DIAGRAM2:
            ReadCodtDomainValue(DEFENCE_DIAGRAM2,overSpeedIS2,overSpeedIV2);
            break;
        case DEFENCE_DIAGRAM3:
            ReadCodtDomainValue(DEFENCE_DIAGRAM3,overSpeedIS3,overSpeedIV3);
            break;
        case DEFENCE_DIAGRAM4:
            ReadCodtDomainValue(DEFENCE_DIAGRAM4,overSpeedIS4,overSpeedIV4);
            break;
    }
}
#endif	/* GLOBALS_H */

