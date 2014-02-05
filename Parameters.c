#include "Parameters.h"
#include "Fat.h"

char AddParameter(char* name, char type, char* data, unsigned int dataLength)
{
    Boot boot;
    ReadBootSector(&boot);
    ParamDescriptor paramDescriptor;
    paramDescriptor.parameterType = type;

}
