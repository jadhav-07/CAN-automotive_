#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "isr.h"
#include "timer0.h"

static void init_leds(void)
{
    /* RB0, RB1, RB6, RB7 as OUTPUT (indicators) */
    TRISB &= ~0xC3;   // Set as output

    /* Ensure CAN RX (RB3) stays INPUT */
    TRISB |= 0x08;    

    /* Turn OFF all indicators initially (active LOW) */
    PORTB |= 0xC3;    // Set bits HIGH to turn LEDs OFF
}



static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();

    /* ECU1 main loop */
    while (1) 
    {
        // Read CAN Bus data and handle it
        process_canbus_data();
    }

    return;
}
