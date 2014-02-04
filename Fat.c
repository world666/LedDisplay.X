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
unsigned int ReadNextFat(unsigned int currentFat)
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int nextFat;
    unsigned int adress = boot.BootSectorSize + currentFat*2 + 2;
    FramRead(adress, &nextFat, sizeof(unsigned int));
    return nextFat;
}
void WriteToFat(unsigned int clusterNum, unsigned int data)
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int adress = boot.BootSectorSize + clusterNum*2 + 2;
    FramWrite(adress,&data, sizeof(int));
}
unsigned int FindFreeClusterNum()
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int freeClusterNum = 0xFFFF;//there are no free cluster
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
unsigned int FindFreeDescriptorNum()
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int freeDescriptorNum = 0xFFFF;//there are no free descriptor
    char descriptorFirstByte;
    int adr = boot.BootSectorSize + boot.FatSectorSize;
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize + boot.DescriptorSectorSize; adr += sizeof(ParamDescriptor))
    {
        FramRead(adr, &descriptorFirstByte, sizeof(char));
        if(descriptorFirstByte == 0)
        {
            freeDescriptorNum = adr;
            break;
        }
    }
    return freeDescriptorNum;
}
void WriteDescriptorByAdress(unsigned int adress, char* data)
{
    FramWrite(adress, &data, sizeof(ParamDescriptor));
}
void ReadDescriptorByAdress(unsigned int adress, char* data)
{
    FramRead(adress, &data, sizeof(ParamDescriptor));
}
unsigned char DescriptorsDefragmentation()
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int freeDescriptorAdr = 0xFFFF;
    unsigned int busyDescriptorAdr = 0xFFFF;
    char descriptorFirstByte;
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
        ReadDescriptorByAdress(busyDescriptorAdr, bufDescriptor);
        if(bufDescriptor[0] == 0)
            return 1;
        WriteDescriptorByAdress(freeDescriptorAdr, bufDescriptor);
        FramWrite(busyDescriptorAdr, 0, sizeof(char));
        busyDescriptorAdr += sizeof(ParamDescriptor);
        freeDescriptorAdr += sizeof(ParamDescriptor);
    }
    return 1;
}