#include <math.h>
#include "Fat.h"
#include "Parameters.h"



char AddParameter(char* name, char type, char* data, unsigned int dataLength)
{
    Boot boot;
    ReadBootSector(&boot);
    ParamDescriptor paramDescriptor;
    paramDescriptor.parameterType = type;
    double clustersCount = (double)dataLength/4.0;
    clustersCount = ceil(clustersCount);
    unsigned int clusterNum = AllocateClustersSequence(clusterCount);
}
