#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


volatile unsigned char led_state = LED_OFF, status = e_ind_off;

void handle_speed_data(uint8_t *data, uint8_t len) 
{
    if(len < 3)
        return;

    data[3] = '\0'; // terminate string
    clcd_print((char *)data, LINE2(5)); // display below SPD
}


void handle_gear_data(uint8_t *data, uint8_t len) 
{
    if(len < 1)
        return;

    unsigned char gear = data[0];  // actual gear value

    /*--------- DISPLAY ---------*/
    switch(gear)
    {
        case 0: clcd_print("N", LINE2(10)); break;
        case 1: clcd_print("1", LINE2(10)); break;
        case 2: clcd_print("2", LINE2(10)); break;
        case 3: clcd_print("3", LINE2(10)); break;
        case 4: clcd_print("4", LINE2(10)); break;
        case 5: clcd_print("5", LINE2(10)); break;
        case 6: clcd_print("R", LINE2(10)); break;
        default: clcd_print("-", LINE2(10)); break;
    }
}


void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    if (len >= 4)
    {
        data[4] = '\0';               // terminate string
        clcd_print((char *)data, LINE2(0));  // display below RPM label
    }
}


void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len)
{
    if (len != 1)
        return;

    IndicatorStatus ind = (IndicatorStatus)data[0];

    /* Clear LCD indicator area */
    clcd_print("    ", LINE2(12));

    /* Turn OFF all indicators first */
    LEFT_IND_OFF();
    RIGHT_IND_OFF();

    switch(ind)
    {
        case e_ind_left:
            clcd_print(" <--", LINE2(12));
            LEFT_IND_ON();
            break;

        case e_ind_right:
            clcd_print(" -->", LINE2(12));
            RIGHT_IND_ON();
            break;

        case e_ind_blink:
            clcd_print("<-->", LINE2(12));
            LEFT_IND_ON();
            RIGHT_IND_ON();
            break;

        case e_ind_off:
        default:
            /* All OFF already */
            break;
    }
}



void process_canbus_data() 
{   
    //process the CAN bus data
   clcd_print("RPM  SPD GER IND", LINE1(0));

    uint16_t rx_msg_id;
    uint8_t rx_data[8];
    uint8_t rx_len = 0;

    can_receive(&rx_msg_id, rx_data, &rx_len);

    if (rx_len == 0)
        return;

    switch (rx_msg_id)
    {
        case SPEED_MSG_ID:
            handle_speed_data(rx_data, rx_len);
            break;

        case GEAR_MSG_ID:
            handle_gear_data(rx_data, rx_len);
            break;

        case RPM_MSG_ID:
            handle_rpm_data(rx_data, rx_len);
            break;

        case ENG_TEMP_MSG_ID:
            handle_engine_temp_data(rx_data, rx_len);
            break;

        case INDICATOR_MSG_ID:
            handle_indicator_data(rx_data, rx_len);
            break;

        //default:
            /* Unknown ID ? ignore */
         //   break;
    }
}

