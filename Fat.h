/* 
 * File:   Fat.h
 * Author: andrey
 *
 * Created on 29 ????? 2014, 13:32
 */
typedef struct Boot
{
    int BootSectorSize; //16
    int FatSectorSize; // 1524 bytes (count = 762)
    int DescriptorSectorSize; //3600 bytes (count = 400)
    int DataSectorSize; //3048 bytes (count = 762)
    char Rezerved[8];
};

typedef struct FatDescriptor
{
    int  NumKlaster;
};

typedef struct ParamDescriptor
{
     char  paramName[4];
     int index;
     int startKlaster;
     ParameterType parameterType;
};

typedef struct ExtendedParamDescriptor
{
     char  paramName[9];
};

typedef enum {} ParameterType;

void WriteBootSector()
{
    Boot boot;
    boot.BootSectorSize = 16;
    boot.FatSectorSize = 1524;
    boot.DescriptorSectorSize = 3600;
    boot.DataSectorSize = 3048;
    int size = sizeof(Boot);
    FramWrite(0,boot, size);
}