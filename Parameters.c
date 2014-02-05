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
    double clustersCount = (double)dataLength/boot.ClusterSize;
    clustersCount = ceil(clustersCount);
    //fat (clusters sequence)
    unsigned int clusterNum = AllocateClustersSequence(clustersCount);
    if(clusterNum==0xFFFF)
        return 0;
    paramDescriptor.startCluster = clusterNum;
    //data area
    int i=0;
    for(i;i<dataLength;i+=boot.ClusterSize)
    {
        WriteDataToCluster(clusterNum,data+i);
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
    double buf = (double)(strlen(name) + 1)/sizeof(ExtendedParamDescriptor);
    unsigned int extendedDescriptorsCount = (int)ceil(buf);
    paramDescriptor.paramName[0] = (char *)(extendedDescriptorsCount)[0];
    paramDescriptor.paramName[1] = (char *)(extendedDescriptorsCount)[1];
    WriteDescriptorByAddress(freeDescriptorAdr,&paramDescriptor);
    i=0;
    ExtendedParamDescriptor extendedDescriptor;
    for(i;i<extendedDescriptorsCount;i++)
    {
        freeDescriptorAdr = FindFreeDescriptorAdr();
        int j=0;
        for(j;j<sizeof(ExtendedParamDescriptor);j++)
            extendedDescriptor.paramName[j] = name[i*j];
        WriteDescriptorByAddress(freeDescriptorAdr,&extendedDescriptor);
    }
    return 1;
}
