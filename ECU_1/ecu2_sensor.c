#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "digital_keypad.h"
#define _XTAL_FREQ 20000000
  unsigned short adc_value, scaled_value;
  unsigned char  count=0;
uint16_t get_speed()
{
   
    // Implement the speed function
    adc_value = read_adc(CHANNEL4);

     
        scaled_value = (adc_value ) / 10.23;

        return scaled_value;
    
}

unsigned char get_gear_pos(void)
{
    unsigned char key;

    key = read_digital_keypad(STATE_CHANGE);

    if (key == SWITCH1)          // Gear UP
    {
        if (count < 6)
            count++;
    }
    else if (key == SWITCH2)     // Gear DOWN
    {
        if (count > 0)
            count--;
    }

    return count;
}
