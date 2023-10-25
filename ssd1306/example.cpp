/* Library to control an Adafruit display */
/* example for control */
#include <stdio.h>
#include "ssd1306/ssd1306.h"

void TEST(void)

int main(void) {
	// ssd1306_TestAll();
	ssd1306_Init(&I2C_MASTER_OLED);//library of ARM
	while(1U)
	{
		TEST();
	}
}

void TEST(void)
{
	ssd1306_Fill(Black);
	/* String setzen */
	ssd1306_SetCursor(55, 13);
	ssd1306_WriteString("FOR", Font_11x18, White);
	ssd1306_SetCursor(4, 33);
	ssd1306_WriteString("EXAMPLE", Font_11x18, White);
	ssd1306_UpdateScreen(&I2C_MASTER_OLED);  //here the I2C Library of ARM
}



