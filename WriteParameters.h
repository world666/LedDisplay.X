/* 
 * File:   WriteParameters.h
 * Author: andrey
 *
 * Created on 21 ?????? 2014, 10:22
 */

unsigned char WriteAllParameters()
{
    Formatting();

    char name[] = "inf";
    DeviceInformation deviceInformation;
    deviceInformation.ObjectCount = 7;
    deviceInformation.ParametersCount = 6;
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

    char name2[] = "start_s";
    long value = 50000;
    if(!AddParameter(name2,0x10,&value,3))
        return 0;

    char name5[] = "node_id";
    value = 2;
    if(!AddParameter(name5,0x10,&value,3))
        return 0;

    char name6[] = "mark_distance";
    float fvalue = 0.5;
    if(!AddParameter(name6,0x8,&fvalue,4))
        return 0;

    char name3[] = "high_edge";
    value = 50000;
    if(!AddParameter(name3,0x10,&value,3))
        return 0;

    char name4[] = "low_edge";
    value = 850000;
    if(!AddParameter(name4,0x10,&value,3))
        return 0;

    char name7[] = "defence_diagram";
    char codtValue[120];
    if(!AddParameter(name6,0xF,codtValue,120))
        return 0;

    return 1;
}