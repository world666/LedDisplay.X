#include "Fat.h"
void WriteBootSector()
{
    Boot boot;
    boot.BootSectorSize = 16;
    boot.FatSectorSize = 1524;
    boot.DescriptorSectorSize = 3600;
    boot.DataSectorSize = 3048;
    FramWrite(0,&boot, sizeof(Boot));
}
void ReadBootSector(Boot* boot)
{
     FramRead(0, boot, sizeof(Boot));
}
void Formatting()
{
    Boot boot;
    int dzero = 0;
    char zero = 0;
    WriteBootSector();
    ReadBootSector(&boot);
    int adr = boot.BootSectorSize;
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize; adr += 2)
    {
        FramWrite(adr,&dzero, sizeof(int));
    }
    adr = boot.BootSectorSize + boot.FatSectorSize;
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize + boot.DescriptorSectorSize; adr += sizeof(ParamDescriptor))
    {
        FramWrite(adr,&zero, sizeof(char));
    }
}
unsigned int ReadNextFat(unsigned int currentFat)
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int nextFat;
    unsigned int address = boot.BootSectorSize + currentFat*2 + 2;
    FramRead(address, &nextFat, sizeof(unsigned int));
    return nextFat;
}
void WriteToFat(unsigned int clusterNum, unsigned int data)
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int address = boot.BootSectorSize + clusterNum*2 + 2;
    FramWrite(address,&data, sizeof(int));
}
unsigned int FindFreeClusterNum()
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int freeClusterNum = 0xFFFF;//there are no free clusters
    unsigned int clusterMeaning;
    int adr = boot.BootSectorSize + 2;
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize; adr += 2)
    {
        FramRead(adr, &clusterMeaning, sizeof(unsigned int));
        if(clusterMeaning == 0)
        {
            freeClusterNum = (adr - boot.BootSectorSize)<<1;
            freeClusterNum--;
            break;
        }
    }
    return freeClusterNum;
}
unsigned int FindFreeDescriptorAdr()
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int freeDescriptorAdr = 0xFFFF;//there are no free descriptors
    char descriptorFirstByte;
    int adr = boot.BootSectorSize + boot.FatSectorSize;
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize + boot.DescriptorSectorSize; adr += sizeof(ParamDescriptor))
    {
        FramRead(adr, &descriptorFirstByte, sizeof(char));
        if(descriptorFirstByte == 0)
        {
            freeDescriptorAdr = adr;
            break;
        }
    }
    return freeDescriptorAdr;
}
void WriteDescriptorByAddress(unsigned int address, char* data)
{
    FramWrite(address, &data, sizeof(ParamDescriptor));
}
void ReadDescriptorByAddress(unsigned int address, char* data)
{
    FramRead(address, &data, sizeof(ParamDescriptor));
}
unsigned char DescriptorsDefragmentation()
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int freeDescriptorAdr = 0xFFFF;
    unsigned int busyDescriptorAdr = 0xFFFF;
    char descriptorFirstByte;
    char zero = 0;
    unsigned int adr = boot.BootSectorSize + boot.FatSectorSize;
    char  bufDescriptor[sizeof(ParamDescriptor)];
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize + boot.DescriptorSectorSize; adr += sizeof(ParamDescriptor))
    {
        FramRead(adr, &descriptorFirstByte, sizeof(char));
        if(descriptorFirstByte == 0 && freeDescriptorAdr == 0xFFFF)
        {
            freeDescriptorAdr = adr;
        }
        if(descriptorFirstByte != 0 && freeDescriptorAdr != 0xFFFF)
        {
            busyDescriptorAdr = adr;
            break;
        }
    }
    if(busyDescriptorAdr == 0xFFFF)//if all descriptors, finded after fist free descriptor, are free
        return 0;
    while(busyDescriptorAdr < (boot.BootSectorSize + boot.FatSectorSize + boot.DescriptorSectorSize))
    {
        ReadDescriptorByAddress(busyDescriptorAdr, bufDescriptor);
        if(bufDescriptor[0] == 0)
            return 1;
        WriteDescriptorByAddress(freeDescriptorAdr, bufDescriptor);
        FramWrite(busyDescriptorAdr, &zero, sizeof(char)); // 0
        busyDescriptorAdr += sizeof(ParamDescriptor);
        freeDescriptorAdr += sizeof(ParamDescriptor);
    }
    return 1;
}