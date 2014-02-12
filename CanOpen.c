#include "Can.h"
#include "CanOpen.h"
#include "Configuration.h"

void SendTPDO(unsigned char pdoNumber, unsigned char nodeId, char* data, unsigned char bufNumber)
{
 unsigned int sId;
 sId = 0x80 + pdoNumber * 0x100;
 sId += nodeId;
 Can1SendData(sId, data, bufNumber);
}
void SendCurrentObjectState(long s1, long s2, int v, int a)
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