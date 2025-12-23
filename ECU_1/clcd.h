#ifndef LCD_H
#define LCD_H



#define CLCD_PORT			PORTD   // Data lines D0?D7 connected to PORTD
#define CLCD_EN				RC2     // Enable pin
#define CLCD_RS				RC1     // Register Select pin
#define CLCD_RW				RC0     // Read/Write pin
#define CLCD_BUSY			RD7     // Busy flag (D7)
#define PORT_DIR			TRISD7  // Direction control for D7 (input when reading busy flag)


#define HI					1
#define LO                  0

#define INPUT				0xFF
#define OUTPUT				0x00

#define DATA_COMMAND				1
#define INSTRUCTION_COMMAND			0
#define _XTAL_FREQ                  20000000
#define LINE0(x)                    (0x80 + (x))// Address for line 1

#define LINE1(x)					(0xC0 + (x))// Address for line 2


#define TWO_LINE_5x8_MATRIX_8_BIT			clcd_write(0x38, INSTRUCTION_COMMAND)// 0x38 ? 2-line, 5x8 font, 8-bit mode
#define CLEAR_DISP_SCREEN				    clcd_write(0x01, INSTRUCTION_COMMAND)// 0x01 ? Clear display
#define CURSOR_HOME							clcd_write(0x02, INSTRUCTION_COMMAND)// 0x02 ? Return home
#define DISP_ON_AND_CURSOR_OFF				clcd_write(0x0C, INSTRUCTION_COMMAND)//- 0x0C ? Display ON, cursor OFF
#define EIGHT_BIT_MODE   0x33   //0x33 ? Often used as part of initialization sequence

void init_clcd(void); // Initializes LCD
void clcd_print(const unsigned char *data, unsigned char addr);// Print string
void clcd_putch(const unsigned char data, unsigned char addr);// Print single char
void clcd_write(unsigned char bit_values, unsigned char control_bit);// Low-level write
void clcd_fun_clear(void);
void clcd_clear(void);

#endif
