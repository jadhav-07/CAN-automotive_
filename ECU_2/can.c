#include <xc.h>
#include "can.h"

typedef enum {
    e_can_op_mode_normal = 0x00,
    e_can_op_mode_config = 0x80
} CanOpMode;

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

    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal);
}

static void set_msg_id_std(uint16_t id)
{
    TXB0SIDH = (id >> 3);
    TXB0SIDL = (id & 0x07) << 5;
}

void can_transmit(uint16_t msg_id, const uint8_t *data, uint8_t len)
{
    uint8_t *ptr;

    TXB0EIDH = 0x00;
    TXB0EIDL = 0x00;

    set_msg_id_std(msg_id);
    TXB0DLC = len;

    ptr = (uint8_t *)&TXB0D0;
    for (uint8_t i = 0; i < len; i++)
    {
        ptr[i] = data[i];
    }

    TXB0REQ = 1;
}
