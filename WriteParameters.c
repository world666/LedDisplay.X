#include "CanOpen.h"
unsigned char WriteAllParameters()
{
    Formatting();

    char name[] = "inf";
    DeviceInformation deviceInformation;
    deviceInformation.ObjectCount = 7;
    deviceInformation.ParametersCount = 8;
    deviceInformation.SystemName[0] = 0;
    strcat(deviceInformation.SystemName, "don_avto_1");
     deviceInformation.DeviceName[0] = 0;
    strcat(deviceInformation.DeviceName,"os_3");
    deviceInformation.DeviceVersion[0] = 0;
    strcat(deviceInformation.DeviceVersion,"v1.0");
    deviceInformation.SoftVersion[0] = 0;
    strcat(deviceInformation.SoftVersion,"1.0");
    deviceInformation.CanVersion[0] = 0;
    strcat(deviceInformation.CanVersion,"can1");

    if(!AddParameter(name,0xF,&deviceInformation,28))
        return 0;

    char name1[] = "start_s";
    long value = 400000;
    if(!AddParameter(name1,0x10,&value,3))
        return 0;

    char name2[] = "node_id";
    value = 3;
    if(!AddParameter(name2,0x10,&value,3))
        return 0;

    char name3[] = "mark_distance";
    float fvalue = 0.5;
    if(!AddParameter(name3,0x8,&fvalue,4))
        return 0;

    char name4[] = "high_edge";
    value = 50000;
    if(!AddParameter(name4,0x10,&value,3))
        return 0;

    char name5[] = "low_edge";
    value = -250000;
    if(!AddParameter(name5,0x10,&value,3))
        return 0;

    char name6[] = "synchronization";
    value = 1;
    if(!AddParameter(name6,0x03,&value,2))
        return 0;

    char name7[] = "synch_zone";
    value = 10000;
    if(!AddParameter(name7,0x03,&value,2))
        return 0;

    char name8[] = "over_rise_zone_low";
    value = 500;
    if(!AddParameter(name8,0x03,&value,2))
        return 0;

    char name9[] = "over_rise_zone_high";
    value = 500;
    if(!AddParameter(name9,0x03,&value,2))
        return 0;

    char name10[] = "defence_diagram";
    char codtValue[120];
    if(!AddParameter(name10,0xF,codtValue,120))
        return 0;

    return 1;
}
