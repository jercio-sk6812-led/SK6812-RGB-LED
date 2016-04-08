/*
 SK6812_Driver.cpp
 
 Driving the Adafruit Neopixel
 
 Created: 08.04.2016 19:02:56
 Author: Arthur Palmer
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

inline void send_bit(char c)
{
	if (c == 0)
	{
		PORTD = 0x80;
		_delay_us(0.10);	// actually: 0.3탎
		PORTD = 0x00;
		_delay_us(0.30);	// actually: 0.9탎
	}
	else
	{
		PORTD = 0x80;
		_delay_us(0.2);		// actually: 0.6탎
		PORTD = 0x00;
		_delay_us(0.2);		// actually: 0.6탎
	}
}

int main(void)
{
	DDRD = 0x80;					// PORTD.7 = Output
	const char leds_count = 12;		// Ring with 12 LEDs
	char RGB[leds_count * 3];		// Array with 12 LEDs * 3 Colors
	char bit_shift;					// char for bit shifting
	
	// color flow table
	char color_flow[16] = {1, 32, 64, 128, 196, 235, 255, 235, 196, 128, 64, 32, 16, 8, 4, 1};
	
	// create array with the colors
	for (char led = 0; led < leds_count; led++)
		for (char c_idx = 0; c_idx < 3; c_idx++)
		{
			RGB[led * 3 + c_idx] = color_flow[(led*3 + c_idx * 5) & 0x0f];
		}
	
	// reset the leds before sending the data
	PORTD = 0;
	_delay_us(50);
	
	// send color-array to the leds
	for (char led = 0; led < leds_count; led++)
		for (char c_idx = 0; c_idx < 3; c_idx++)
		{
			bit_shift = RGB[c_idx + led * 3];
			for (char x = 0; x < 8; x++)
			{
				send_bit(bit_shift & 0x80);
				bit_shift = bit_shift << 1;
			}
		}

	// we are done, do nothing till the end of time
	while(1)
	{
	}
}