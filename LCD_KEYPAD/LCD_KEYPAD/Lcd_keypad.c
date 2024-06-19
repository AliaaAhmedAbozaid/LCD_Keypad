/*
 * Leypad_lcd.c
 * Description: This program demonstrates interfacing a 4x3 keypad with an LCD using the ATmega16 microcontroller.
 */

#include <mega16.h>
#include <alcd.h>
#include <delay.h>

// Function prototypes
char keypad();


// Global variables
int cnt = 0, y = 0, i = 0, cpy = 0;

void main(void)
{
	int x1 = 0;
	DDRC = 0b00000111;  // Configure the lower 3 bits of PORTC as outputs for the keypad
	PORTC = 0b11111000; // Enable pull-up resistors for the upper 5 bits of PORTC
	lcd_init(16);       // Initialize the LCD with 16 columns

	while (1)
		{
		lcd_puts("Hello!");
		delay_ms(300);
		lcd_clear();

		while (1)
			{
			x1 = keypad();
			lcd_gotoxy(i, y);
			lcd_printf("%d", x1);
			if(x1 == 10 || x1 == 11)
				i = i + 1;
			i = i + 1;

			if (i == 16 || i == 17)
				{
				cpy = i;
				i = 0;
				if(cpy == 17)
					{
					i = i + 1;
					cpy = 0;
					}
				y = 1;
				cnt = cnt + 1;
				}

			if (cnt == 2)
				{
				i = 0;
				y = 0;
				cnt = 0;
				delay_ms(200);
				lcd_clear();
				}
			}

		lcd_clear();
		}
}

// Function to read keypress from the keypad
char keypad()
{
	while (1)
		{
		PORTC.0 = 0;
		PORTC.1 = 1;
		PORTC.2 = 1;
		// Only C1 is activated
		switch (PINC)
			{
			case 0b11110110:
				while (PINC.3 == 0);
				return 1;
				break;

			case 0b11101110:
				while (PINC.4 == 0);
				return 4;
				break;

			case 0b11011110:
				while (PINC.5 == 0);
				return 7;
				break;

			case 0b10111110:
				while (PINC.6 == 0);
				return 10;
				break;
			}

		PORTC.0 = 1;
		PORTC.1 = 0;
		PORTC.2 = 1;
		// Only C2 is activated
		switch (PINC)
			{
			case 0b11110101:
				while (PINC.3 == 0);
				return 2;
				break;

			case 0b11101101:
				while (PINC.4 == 0);
				return 5;
				break;

			case 0b11011101:
				while (PINC.5 == 0);
				return 8;
				break;

			case 0b10111101:
				while (PINC.6 == 0);
				return 0;
				break;
			}

		PORTC.0 = 1;
		PORTC.1 = 1;
		PORTC.2 = 0;
		// Only C3 is activated
		switch (PINC)
			{
			case 0b11110011:
				while (PINC.3 == 0);
				return 3;
				break;

			case 0b11101011:
				while (PINC.4 == 0);
				return 6;
				break;

			case 0b11011011:
				while (PINC.5 == 0);
				return 9;
				break;

			case 0b10111011:
				while (PINC.6 == 0);
				return 11;
				break;
			}
		}
}
