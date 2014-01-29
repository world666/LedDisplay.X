/* 
 * File:   LowVoltageDetect.h
 * Author: andrey
 *
 * Created on 15 ????????? 2013, 13:56
 */

void LVDinitialization()
{
    RCONbits.LVDL = 0xE;//<4.6V
    _LVDIE = 0; //LVD interrupt disable
    _LVDEN = 1; //LVD modul enable
    while(!_BGST); // wait while voltage stabilize
    _LVDIF = 0; //clear interrupt flag
    _LVDIP = 6; //interrupt priority
    _LVDIE = 1; //LVD interrupt enable
}