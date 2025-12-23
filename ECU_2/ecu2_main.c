#include "adc.h"
#include "can.h"
#include "ecu2_sensor.h"
#include "msg_id.h"
//#include "clcd.h"
#include <xc.h>
#include <string.h>
#include "digital_keypad.h"
#define _XTAL_FREQ 20000000

uint16_t rpm;
char rpm_str[5];

uint16_t rx_id;
uint8_t rx_data[8];
uint8_t rx_len;

int main()
{
    init_adc();
    init_can();
   
    

    while (1)
    {
       

        /* ---------- RPM READ ---------- */
        rpm = get_rpm();   // returns 0?6000


        rpm_str[0] = (rpm / 1000) + '0';
        rpm_str[1] = ((rpm / 100) % 10) + '0';
        rpm_str[2] = ((rpm / 10) % 10) + '0';
        rpm_str[3] = (rpm % 10) + '0';
        rpm_str[4] = '\0';

        can_transmit(RPM_MSG_ID, (uint8_t*)rpm_str, 4);

        __delay_ms(50);

        /* ========== RECEIVING RPM ========== */
       /* can_receive(&rx_id, rx_data, &rx_len);

        if (rx_id == RPM_MSG_ID && rx_len >= 4)
        {
            rx_data[4] = '\0';
            clcd_print((char *)rx_data, LINE1(0));
        }*/

        /* ---------- SEND INDICATOR ---------- */
       IndicatorStatus ind_tx = process_indicator();
        can_transmit(INDICATOR_MSG_ID, &ind_tx, 1);
        __delay_ms(50);

/* ---------- RECEIVE INDICATOR ---------- */
/*can_receive(&rx_id, rx_data, &rx_len);   // <-- REQUIRED

if (rx_id == INDICATOR_MSG_ID && rx_len == 1)
{
    IndicatorStatus ind = rx_data[0];

    switch(ind)
    {
        case e_ind_left:
           
            clcd_print("    ", LINE1(5));
            clcd_print("<--", LINE1(5));
            break;

        case e_ind_right:
            
            clcd_print("    ", LINE1(5));
            clcd_print("-->", LINE1(5));
            break;

        case e_ind_blink:
           
         clcd_print("<-->", LINE1(5));
        break;

        case e_ind_off:
            clcd_print("    ", LINE1(5));
            break;
    }
}*/

}


}


