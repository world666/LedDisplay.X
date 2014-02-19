#include "Can.h"
#include "CanOpen.h"
#include "Configuration.h"

char canOpenCodtDomainBlock[200];
unsigned int canOpenCodtDomainLength;
unsigned int canOpenCodtDomainCurrentPosition = 0;

void SendTPDO(unsigned char pdoNumber, unsigned char nodeId, char* data, unsigned char bufNumber)
{
 unsigned int sId;
 sId = 0x80 + pdoNumber * 0x100;
 sId += nodeId;
 Can1SendData(sId, data, bufNumber);
}
void SendTSDO(unsigned char nodeId, char* data, unsigned char bufNumber)
{
 unsigned int sId;
 sId = 0x580;
 sId += nodeId;
 Can1SendData(sId, data, bufNumber);
}
void CanOpenSendCurrentObjectState(long s1, long s2, int v, int a)
{
    unsigned char nodeID = NODE_ID;
    char data1[8] = {0, 0, 0 ,0, 0, 0, 0 ,0};
    char* buf = &s1;
    data1[0] = buf[0]; data1[1] = buf[1]; data1[2] = buf[2];
    buf = &s2;
    data1[3] = buf[0]; data1[4] = buf[1]; data1[5] = buf[2];
    SendTPDO(1, nodeID, data1,0);
    char data2[8] = {0, 0, 0 ,0, 0, 0, 0 ,0};
    v=-v;
    buf = &v;
    data2[0] = buf[0]; data2[1] = buf[1];
    v =-v;
    buf = &v;
    data2[2] = buf[0]; data2[3] = buf[1];
    buf = &a;
    data2[6] = buf[0]; data2[7] = buf[1];
    SendTPDO(2, nodeID, data2,1);
    char data3[8] = {0, 0, 0 ,0, 0, 0, 0 ,0};
    SendTPDO(3, nodeID, data3,2);
}
void CanOpenParseReceivedData(char *data)
{
    if(data[0] == 0x40)//read query
        SendDictionaryElement(data);
    else if((data[0]&0xF3) == 0x22)
        EditDictionaryElement(data);
    else if(data[0] == 0x60 || data[0] == 0x70)
        CanOpenSendCodtDomainMsg();
}
void EditDictionaryElement(char* data)
{
    unsigned char nodeID = NODE_ID;
    unsigned char objSubIndex = data[3];
    unsigned int objIndex = data[1] + (data[2]<<8);
        switch(objSubIndex)
        {
            case 2:
                EditParameterValue(objIndex, data + 4,4);
                break;
            case 4:
                CanOpenEditName(data);
                break;
            default:
                return;
        }
    char sendBuf[8];
    sendBuf[0] = 0x60;
    sendBuf[1] = data[1];
    sendBuf[2] = data[2];
    sendBuf[3] = data[3];
    SendTSDO(nodeID, sendBuf,0);
}
void SendDictionaryElement(char* data)
{   
    unsigned char objSubIndex = data[3];    
        switch(objSubIndex)
        {
            case 1:
                SendParameterType(data);
                break;
            case 2:
                SendValue(data);
                break;
            case 4:
                SendName(data);
                break;
        }
}
void SendValue(char* data)
{
    unsigned char nodeID = NODE_ID;
    char sendBuf[8] = {0,0,0,0,0,0,0,0};
    char valueArray[150];
    unsigned int objIndex = data[1] + (data[2]<<8);
    char objType = ReadParameterType(objIndex);
    unsigned int byteCount = ReadParameterValue(objIndex,valueArray);
    if(byteCount == 0)
        return;
    sendBuf[1] = data[1];
    sendBuf[2] = data[2];
    sendBuf[3] = data[3];
    if(byteCount>4)//codtDomain
    {
        sendBuf[0] = 0x41;
        sendBuf[4] = byteCount&0x00FF; //low part
        sendBuf[5] = (byteCount>>8)&0x00FF; //high part
        int i=0;
        for(i=0;i<byteCount;i++)
            canOpenCodtDomainBlock[i] = valueArray[i];
        canOpenCodtDomainCurrentPosition = 0;
        canOpenCodtDomainLength = byteCount;
    }
    else
    {
        switch(objType)
        {
            case 0xF://codtDomain
                break;
            case 0x10://sint24
                sendBuf[0] = 0x47;
                break;
            case 0x8://real32
                sendBuf[0] = 0x43;
                break;
            case 0x3://sin16
                sendBuf[0] = 0x4B;
                break;
            case 0x6://sint16
                sendBuf[0] = 0x4B;
                break;
        }
        sendBuf[4] = valueArray[0];
        sendBuf[5] = valueArray[1];
        sendBuf[6] = valueArray[2];
        sendBuf[7] = valueArray[3];
    }
    SendTSDO(nodeID, sendBuf,0);
}
void SendParameterType(char* data)
{
    unsigned char nodeID = NODE_ID;
    char sendBuf[8];
    unsigned int objIndex = data[1] + (data[2]<<8);
    char objType = ReadParameterType(objIndex);
    if(objType == -1)//there are no parameter with such index
        return;
    sendBuf[0] = 0x4B; //1 byte usage
    sendBuf[1] = data[1];
    sendBuf[2] = data[2];
    sendBuf[3] = data[3];
    sendBuf[4] = objType;
    sendBuf[5] = 0x0;
    SendTSDO(nodeID, sendBuf,0);
}
void SendName(char* data)
{
    unsigned char nodeID = NODE_ID;
    char sendBuf[8] = {0,0,0,0,0,0,0,0};
    char valueArray[30]; //max name is 29 symbols
    unsigned int objIndex = data[1] + (data[2]<<8);
    unsigned char byteCount = ReadParameterName(objIndex,valueArray);
    if(byteCount == 0)
        return;
    sendBuf[1] = data[1];
    sendBuf[2] = data[2];
    sendBuf[3] = data[3];
    if(byteCount<=4)//short msg
    {
        sendBuf[0] = 0x43 + ((4-byteCount)<<2);
        sendBuf[4] = valueArray[0];
        sendBuf[5] = valueArray[1];
        sendBuf[6] = valueArray[2];
        sendBuf[7] = valueArray[3];
    }
    else //codtdomain
    {
        sendBuf[0] = 0x41;
        sendBuf[4] = byteCount&0x00FF; //low part
        sendBuf[5] = (byteCount>>8)&0x00FF; //high part
        canOpenCodtDomainBlock[0] = 0;
        strcat(canOpenCodtDomainBlock,valueArray);
        canOpenCodtDomainCurrentPosition = 0;
        canOpenCodtDomainLength = byteCount;
    }
    SendTSDO(nodeID, sendBuf,0);
}
void CanOpenEditName(char* data)
{
    unsigned int objIndex = data[1] + (data[2]<<8);
    char newName[5];
    unsigned char unusedBytes = (data[0]&0xC)>>2;
    int i=0;
    for(i;i<4-unusedBytes;i++)
        newName[0] = data[i+4];
    newName[4-unusedBytes] = 0;
    EditParameterName(objIndex,newName);
}
void CanOpenSendCodtDomainMsg()
{
    unsigned char nodeID = NODE_ID;
    char sendBuf[8] = {0,0,0,0,0,0,0,0};
    if(canOpenCodtDomainCurrentPosition + 8> canOpenCodtDomainLength) // last block
    {
        sendBuf[0] = 1;//lastblock flag
        unsigned char unusedBytes = 7-(canOpenCodtDomainLength-canOpenCodtDomainCurrentPosition);
        sendBuf[0]+=(unusedBytes<<1);
    }
    else
        sendBuf[0] = 0;
    //write data
    int i=1;
    for(i;i<8;i++)
        sendBuf[i] = canOpenCodtDomainBlock[canOpenCodtDomainCurrentPosition++];
    SendTSDO(nodeID, sendBuf,0);
}