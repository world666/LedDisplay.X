#include <math.h>
#include <string.h>
#include "Fat.h"
#include "Parameters.h"



char AddParameter(char* name, char type, char* data, unsigned int dataLength)
{
    Boot boot;
    ReadBootSector(&boot);
    ParamDescriptor paramDescriptor;
    paramDescriptor.parameterType = type;
    paramDescriptor.index = FindMaxIndex()+1;
    double clustersCount = (double)dataLength/boot.ClusterSize;
    clustersCount = ceil(clustersCount);
    //fat (clusters sequence)
    unsigned int clusterNum = AllocateClustersSequence(clustersCount);
    if(clusterNum==0xFFFF)
        return 0;
    paramDescriptor.startCluster = clusterNum;
    //data area
    int i=0;
    for(i;i<clustersCount;i++)
    {
        WriteDataToCluster(clusterNum,data+i*boot.ClusterSize);
        clusterNum = ReadNextFat(clusterNum);
    }
    //find free descriptor adr
    unsigned int freeDescriptorAdr = FindFreeDescriptorAdr();
    if(freeDescriptorAdr == 0xFFFF)
        return 0;
    //name + write descriptor
    if(strlen(name)<4)//simple descriptor
    {
        paramDescriptor.paramName[0] = 0;
        strcat(paramDescriptor.paramName,name);
        WriteDescriptorByAddress(freeDescriptorAdr,&paramDescriptor);
        return 1;
    }
    //extended descriptors
    paramDescriptor.paramName[0] = 0x0F;//exteded descripto sign
    //count extended descriptors num
    double buf = (double)(strlen(name) + 1)/boot.DescriptorSize;
    unsigned int extendedDescriptorsCount = (int)ceil(buf);
    char *ch = &extendedDescriptorsCount;
    paramDescriptor.paramName[1] = ch[0];
    paramDescriptor.paramName[2] = ch[1];
    WriteDescriptorByAddress(freeDescriptorAdr,&paramDescriptor);
    i=0;
    ExtendedParamDescriptor extendedDescriptor;
    for(i;i<extendedDescriptorsCount;i++)
    {
        freeDescriptorAdr = FindFreeDescriptorAdr();
        int j=0;
        for(j;j<boot.DescriptorSize;j++)
            extendedDescriptor.paramName[j] = name[i*boot.DescriptorSize + j];
        WriteDescriptorByAddress(freeDescriptorAdr,&extendedDescriptor);
    }
    return 1;
}

unsigned int FindMaxIndex()
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int maxIndex = 0;
    ParamDescriptor descriptor;
    int adr = boot.BootSectorSize + boot.FatSectorSize;
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize + boot.DescriptorSectorSize;
            adr += boot.DescriptorSize)
    {
        ReadDescriptorByAddress(adr, &descriptor);
        if(descriptor.paramName[0] == 0)
            break;
        if(descriptor.paramName[0] !=0x0F)
        {
            if(maxIndex < descriptor.index)
                maxIndex = descriptor.index;
        }
    }
    if(maxIndex == 0)
        return 0x1FFF;
    return maxIndex;
}
unsigned int FindDescriptorAdrByIndex(unsigned int index)
{
    Boot boot;
    ReadBootSector(&boot);
    unsigned int descriptorAdr = 0xFFFF;//there are no descriptor with such index
    ParamDescriptor descriptor;
    int adr = boot.BootSectorSize + boot.FatSectorSize;
    for(adr; adr < boot.BootSectorSize + boot.FatSectorSize + boot.DescriptorSectorSize; adr += boot.DescriptorSize)
    {
        ReadDescriptorByAddress(adr, &descriptor);
        if(descriptor.paramName[0] == 0)
            break;
        if(descriptor.paramName[0] !=0x0F && descriptor.index == index)
        {
            descriptorAdr = adr;
            break;
        }
    }
    return descriptorAdr;
}