#include <xc.h>
#include "can.h"

/* CAN operation mode values */
typedef enum {
    e_can_op_mode_normal = 0x00,
    e_can_op_mode_config = 0x80
} CanOpMode;

/* Initialize CAN for RECEIVE */
void init_can(void)
{
    TRISB2 = 0;
    TRISB3 = 1;

    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_config);
    while (CANSTAT != 0x80);

    ECANCON = 0x00;

    BRGCON1 = 0xE1;
    BRGCON2 = 0x1B;
    BRGCON3 = 0x03;

    /* Receive ALL messages (for testing) */
    RXB0CONbits.RXM0 = 1;
    RXB0CONbits.RXM1 = 1;

    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal);
}

/* Get standard ID */
static uint16_t get_msg_id_std(void)
{
    return ((RXB0SIDL >> 5) & 0x07) | (RXB0SIDH << 3);
}

/* Receive CAN data */
void can_receive(uint16_t *msg_id, uint8_t *data, uint8_t *len)
{
    if (RXB0FUL)
    {
        *msg_id = get_msg_id_std();
        *len = RXB0DLC;

        uint8_t *ptr = (uint8_t *)&RXB0D0;
        for (uint8_t i = 0; i < *len; i++)
        {
            data[i] = ptr[i];
        }

        RXB0FUL = 0;   // Clear buffer
        RXB0IF  = 0;   // Clear interrupt flag
    }
    else
    {
        *len = 0;      // No data received
    }
}
