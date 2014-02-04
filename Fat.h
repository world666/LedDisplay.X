/*
 * File:   Fat.h
 * Author: andrey
 *
 * Created on 29 ????? 2014, 13:32
 */
typedef struct Boot
{
    unsigned int BootSectorSize; //16
    unsigned int FatSectorSize; // 1524 bytes (count = 762)
    unsigned int DescriptorSectorSize; //3600 bytes (count = 400)
    unsigned int DataSectorSize; //3048 bytes (count = 762)
    char Rezerved[8];
} Boot;

typedef struct FatDescriptor
{
    unsigned int  NumCluster;
} FatDescriptor;

typedef struct ParamDescriptor
{
     char  paramName[4];
     unsigned int index;
     unsigned int startCluster;
     char parameterType;
} ParamDescriptor;

typedef struct ExtendedParamDescriptor
{
     char  paramName[9];
} ExtendedParamDescriptor;

typedef enum {
    codtDomain
} ParameterType;

void WriteBootSector();
void ReadBootSector();
unsigned int ReadNextFat(unsigned int);
void WriteToFat(unsigned int, unsigned int);
unsigned int FindFreeClusterNum();
unsigned int FindFreeDescriptorNum();
void WriteDescriptorByAdress(unsigned int, char*);
void ReadDescriptorByAdress(unsigned int, char*);
unsigned char DescriptorsDefragmentation();