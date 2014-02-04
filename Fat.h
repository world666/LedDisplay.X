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

/**
 * @author Liutyi Ievgen
 * @todo write a Boot structure data into flash memory
 */
void WriteBootSector();
/**
 * @author Liutyi Ievgen
 * @todo read a Boot structure data from flash memory
 */
void ReadBootSector();
/**
 * @author Liutyi Ievgen
 * @param unsigned int param is current cluster number
 * @todo find the next cluster number in Fat sector
 * @return next cluster number
 * @return if next cluster number = 0xFFFF => current cluster is last for current parameter
 */
unsigned int ReadNextFat(unsigned int);
/**
 * @author Liutyi Ievgen
 * @param unsigned int param1 is number of Fat sector element
 * @param unsigned int param2 is data
 * @todo write data to Fat sector element
 */
void WriteToFat(unsigned int, unsigned int);
/**
 * @author Liutyi Ievgen
 * @todo find the fist free cluster number
 * @return free cluster number
 * @return if free cluster number = 0xFFFF => there are no free clusters
 */
unsigned int FindFreeClusterNum();
/**
 * @author Liutyi Ievgen
 * @todo find the fist free descriptor number
 * @return free descriptor number
 * @return if free descriptor number = 0xFFFF => there are no free descriptors
 */
unsigned int FindFreeDescriptorNum();
/**
 * @author Liutyi Ievgen
 * @param unsigned int param1 is address
 * @param char* param2 is data
 * @todo write data into descriptor by address
 */
void WriteDescriptorByAddress(unsigned int, char*);
/**
 * @author Liutyi Ievgen
 * @param unsigned int param1 is address
 * @param char* param2 is data
 * @todo read descriptor data by address to param2
 */
void ReadDescriptorByAddress(unsigned int, char*);
/**
 * @author Liutyi Ievgen
 * @todo make defragmentation of Descriptors sector
 * @return 1 => defragmentation is succeed
 * @return 0 => defragmentation isn't necessary
 */
unsigned char DescriptorsDefragmentation();