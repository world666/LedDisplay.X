/* 
 * File:   CanOpen.h
 * Author: Æåíÿ
 *
 * Created on 11 ??????? 2014 ?., 9:55
 */
typedef struct DeviceInformation //28bytes
{
    unsigned char ObjectCount; 
    unsigned int ParametersCount; 
    char SystemName[10]; //3600 bytes (count = 400)
    char DeviceName[4]; //3048 bytes (count = 762)
    char DeviceVersion[4]; //4
    char SoftVersion[3]; //9
    char CanVersion[4];
} DeviceInformation;
/**
 * @autor Kyrylov Andrii
 * @param unsigned char - pdo number(1-4)
 * @param unsigned char - node id
 * @param char* - data
 * @param unsigned char - buffer number
 * @todo send tpdo over can interface
 */
void SendTPDO(unsigned char, unsigned char, char*, unsigned char);

/**
 * @autor Kyrylov Andrii
 * @param unsigned char - node id
 * @param char* - data
 * @param unsigned char - buffer number
 * @todo send tsdo over can inetface
 */
void SendTSDO(unsigned char, char* , unsigned char);

/**
 * @autor Kyrylov Andrii
 * @param long - s1
 * @param long - s2
 * @param int - speed(v)
 * @param int - a
 * @todo send current object state using tpdo over can bus
 */
void CanOpenSendCurrentObjectState(long, long, int, int);

