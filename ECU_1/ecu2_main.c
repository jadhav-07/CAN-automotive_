#include "adc.h"
#include "can.h"
#include "ecu2_sensor.h"
#include "msg_id.h"
#include <xc.h>
#include <string.h>
#include "digital_keypad.h"

#define _XTAL_FREQ 20000000

uint16_t speed;
char speed_str[4];

uint16_t rx_id;
uint8_t rx_data[8];
uint8_t rx_len;

int main()
{
    init_adc();
    init_can();      // only once!
    
    init_digital_keypad();
    while (1)
    {
        
       speed = get_speed();

        speed_str[0] = (speed / 100) + '0';
        speed_str[1] = ((speed / 10) % 10) + '0';
        speed_str[2] = (speed % 10) + '0';
        speed_str[3] = '\0';
        
        can_transmit(SPEED_MSG_ID, speed_str, 4);
        
        __delay_ms(50);
         
       /* can_receive(&rx_id, rx_data, &rx_len);
       
            rx_data[rx_len]='\0';
         
        if(rx_id == SPEED_MSG_ID) 
        {
            
            clcd_print((char *)rx_data, LINE1(0));
        }

       // __delay_ms(50);*/
        
        
         unsigned char gear = get_gear_pos();
        can_transmit(GEAR_MSG_ID, &gear, 1);

        __delay_ms(50);

        /*--------- RECEIVE ---------*/
      /*  can_receive(&rx_id, rx_data, &rx_len);

        if (rx_len > 0)
            rx_data[rx_len] = '\0';

        
       if (rx_id == GEAR_MSG_ID && rx_len == 1)
{
    unsigned char gear = rx_data[0];  // actual gear value

    switch(gear)
    {
        case 0:
            clcd_print("N", LINE1(5)); 
            break;

        case 1:
            clcd_print("1", LINE1(5));
            break;

        case 2:
            clcd_print("2", LINE1(5));
            break;

        case 3:
            clcd_print("3", LINE1(5));
            break;

        case 4:
            clcd_print("4", LINE1(5));  
            break;

        case 5:
            clcd_print("5", LINE1(5));  
            break;

        case 6:
            clcd_print("R", LINE1(5));  
            break;

        default:
            clcd_print("-", LINE1(5));
            break;
    }
  __delay_ms(50);*/
   
}

    } 


    

