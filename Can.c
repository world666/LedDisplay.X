#include <can.h>
#include "Configuration.h"
#include "Can.h"

void Can1Initialization(void)
{
//Set request for configuration Mode
	CAN1SetOperationMode(CAN_IDLE_CON & CAN_MASTERCLOCK_1 & CAN_REQ_OPERMODE_CONFIG & CAN_CAPTURE_DIS);
	while(C1CTRLbits.OPMODE<=3);

//Load Configuration register

	CAN1Initialize(CAN_SYNC_JUMP_WIDTH1 & CAN_BAUD_PRE_SCALE(BAUD_RATE),CAN_WAKEUP_BY_FILTER_DIS & CAN_PHASE_SEG2_TQ(6) & CAN_PHASE_SEG1_TQ(8) &
					CAN_PROPAGATIONTIME_SEG_TQ(1) & CAN_SEG2_FREE_PROG & CAN_SAMPLE1TIME);

        // Set interrupts
   ConfigIntCAN1(CAN_INDI_INVMESS_DIS &
             CAN_INDI_WAK_DIS &
             CAN_INDI_ERR_DIS &
             CAN_INDI_TXB2_DIS &
             CAN_INDI_TXB1_DIS &
             CAN_INDI_TXB0_DIS &
             CAN_INDI_RXB1_EN &
             CAN_INDI_RXB0_EN ,
             CAN_INT_PRI_5 &
             CAN_INT_ENABLE);
//Set Filters
    long node_id = NODE_ID;
    CAN1SetFilter(0, CAN_FILTER_SID(0x600+node_id) & CAN_RX_EID_DIS, CAN_FILTER_EID(00000));
    CAN1SetMask(0, CAN_MASK_SID(0x7FF) & CAN_MATCH_FILTER_TYPE, CAN_MASK_EID(00000));
    CAN1SetFilter(1, CAN_FILTER_SID(0x600+node_id) & CAN_RX_EID_DIS, CAN_FILTER_EID(00000));
    CAN1SetMask(1, CAN_MASK_SID(0x7FF) & CAN_MATCH_FILTER_TYPE, CAN_MASK_EID(00000));
    CAN1SetFilter(2, CAN_FILTER_SID(0x600+node_id) & CAN_RX_EID_DIS, CAN_FILTER_EID(00000));
    CAN1SetMask(2, CAN_MASK_SID(0x7FF) & CAN_MATCH_FILTER_TYPE, CAN_MASK_EID(00000));
//Set transmitter and receiver mode
    CAN1SetTXMode(0, CAN_TX_STOP_REQ & CAN_TX_PRIORITY_HIGH);
    CAN1SetRXMode(0, CAN_RXFUL_CLEAR & CAN_BUF0_DBLBUFFER_EN);
    CAN1SetTXMode(1, CAN_TX_STOP_REQ & CAN_TX_PRIORITY_HIGH);
    CAN1SetRXMode(1, CAN_RXFUL_CLEAR & CAN_BUF0_DBLBUFFER_EN);
    CAN1SetTXMode(2, CAN_TX_STOP_REQ & CAN_TX_PRIORITY_HIGH);
    CAN1SetRXMode(2, CAN_RXFUL_CLEAR & CAN_BUF0_DBLBUFFER_EN);

//Set request for normal mode

	CAN1SetOperationMode(CAN_IDLE_STOP & CAN_CAPTURE_EN & CAN_MASTERCLOCK_1 & CAN_REQ_OPERMODE_NOR);
	while(C1CTRLbits.OPMODE != 0);
}

void Can1SendData(unsigned int sid, char* data, unsigned char bufNumber)
{
	//Load message ID, Data into transmit buffer and set transmit request bit
	CAN1SendMessage((CAN_TX_SID(sid)) & (CAN_TX_EID_DIS) & (CAN_SUB_NOR_TX_REQ), (CAN_TX_EID(1)) & (CAN_NOR_TX_REQ), data, 8, bufNumber);
}

void Can1ReceiveData(char* data)
{
    CAN1ReceiveMessage(data, 8, 0);
}
