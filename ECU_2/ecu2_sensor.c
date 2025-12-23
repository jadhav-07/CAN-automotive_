#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "digital_keypad.h"
#define _XTAL_FREQ 20000000
  unsigned short adc_value, scaled_value;
  unsigned char  count=0;
uint16_t get_rpm()
{
    //Implement the rpm function
    adc_value = read_adc(CHANNEL4);

     
        scaled_value = (adc_value) / 10.23 *60;


        return scaled_value;
}

IndicatorStatus process_indicator(void)
{
    static IndicatorStatus current = e_ind_off;
    unsigned char key;

    key = read_digital_keypad(STATE_CHANGE);   // ? MUST read key

    if (key == 0xFF)        // ? no key pressed
    {
        return current;    // keep previous state
    }

    switch (key)
    {
        case SW1:
            current = e_ind_left;
            break;

        case SW2:
            current = e_ind_right;
            break;

        case SW3:
            current = e_ind_blink;
            break;

        case SW4:
            current = e_ind_off;
            break;

        default:
            break;
    }

    return current;
}
