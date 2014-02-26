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
int _overRizeZoneHigh;
int _overRizeZoneLow;
int _buffer;

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
#define DEFENCE_DIAGREM 0x2010

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
}

#endif	/* GLOBALS_H */

