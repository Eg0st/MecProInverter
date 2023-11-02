#include "ssd1306.h"

// Screenbuffer
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Screen object
static SSD1306_t SSD1306;

// Send a byte to the command register
static uint8_t ssd1306_WriteCommand(I2C_MASTER_t* handle, uint8_t byte) {

	uint8_t status=0;
	static uint8_t var = 0x00;
	status+=I2C_MASTER_Transmit(handle, true, SSD1306_I2C_ADDR, &var, 1, false);
	while(I2C_MASTER_IsTxBusy(handle));
    status+=I2C_MASTER_Transmit(handle, false, SSD1306_I2C_ADDR, &byte,1, true);
    while(I2C_MASTER_IsTxBusy(handle));
    return status;
    // HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x00, 1, &byte, 1, HAL_MAX_DELAY);
}

// Initialize the oled screen
uint8_t ssd1306_Init(I2C_MASTER_t* handle) {

    // Wait for the screen to boot
    // HAL_Delay(100);
	for(uint32_t counter = 0; counter < 5000000; counter++) {	//Zeit muss solange sein, damit er sich initialisiert, im normalen Modus
		__NOP();
	}
	uint8_t status=0;

	// Init OLED
    status +=ssd1306_WriteCommand(handle,0xAE); //display off
    status +=ssd1306_WriteCommand(handle,0x20); //Set Memory Addressing Mode
    status +=ssd1306_WriteCommand(handle,0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode; 10b,Page Addressing Mode (RESET); 11b,Invalid
    status +=ssd1306_WriteCommand(handle,0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    status +=ssd1306_WriteCommand(handle,0xC8); //Set COM Output Scan Direction
    status +=ssd1306_WriteCommand(handle,0x00); //---set low column address
    status +=ssd1306_WriteCommand(handle,0x10); //---set high column address
    status +=ssd1306_WriteCommand(handle,0x40); //--set start line address - CHECK
    status +=ssd1306_WriteCommand(handle,0xFF);
    status +=ssd1306_WriteCommand(handle,0xA1); //--set segment re-map 0 to 127 - CHECK
    status +=ssd1306_WriteCommand(handle,0xA6); //--set normal color, not inverse

    status +=ssd1306_WriteCommand(handle,0xA8); //--set multiplex ratio(1 to 64) - CHECK
    status +=ssd1306_WriteCommand(handle,0x3F); // SSD1306_HEIGHT - 1

    status +=ssd1306_WriteCommand(handle,0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    status +=ssd1306_WriteCommand(handle,0xD3); //-set display offset - CHECK
    status +=ssd1306_WriteCommand(handle,0x00); //-not offset
    status +=ssd1306_WriteCommand(handle,0xD5); //--set display clock divide ratio/oscillator frequency
    status +=ssd1306_WriteCommand(handle,0xF0); //--set divide ratio
    status +=ssd1306_WriteCommand(handle,0xD9); //--set pre-charge period
    status +=ssd1306_WriteCommand(handle,0x22); //

    status +=ssd1306_WriteCommand(handle,0xDA); //--set com pins hardware configuration - CHECK
    status +=ssd1306_WriteCommand(handle,0x12);

    status +=ssd1306_WriteCommand(handle,0xDB); //--set vcomh
    status +=ssd1306_WriteCommand(handle,0x20); //0x20,0.77xVcc
    status +=ssd1306_WriteCommand(handle,0x8D); //--set DC-DC enable
    status +=ssd1306_WriteCommand(handle,0x14); //
    status +=ssd1306_WriteCommand(handle,0xAF);//--turn on SSD1306 panel

    if (status != 0) {
    	return 1;
    }
    // Clear screen
    ssd1306_Fill(Black);
    
    // Flush buffer to screen
    ssd1306_UpdateScreen(handle);
    
    // Set default values for screen object
    SSD1306.CurrentX = 0;
    SSD1306.CurrentY = 0;
    
    SSD1306.Initialized = 1;

    return 0;
}

// Fill the whole screen with the given color, other word for clear screen
void ssd1306_Fill(SSD1306_COLOR color) {
    /* Set memory */
    uint32_t i;

    for(i = 0; i < sizeof(SSD1306_Buffer); i++) {
        SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
    }
}

// Write the screenbuffer with changed to the screen
void ssd1306_UpdateScreen(I2C_MASTER_t* handle) {
    // Write data to each page of RAM. Number of pages
    // depends on the screen height:
    //
    //  * 32px   ==  4 pages
    //  * 64px   ==  8 pages
    //  * 128px  ==  16 pages
    for(uint8_t i = 0; i < SSD1306_HEIGHT/8; i++) {
        ssd1306_WriteCommand(handle,0xB0 + i); // Set the current RAM page address.
        ssd1306_WriteCommand(handle,0x00);
        ssd1306_WriteCommand(handle,0x10);

        static uint8_t var = 0x40;
        I2C_MASTER_Transmit(handle, true, SSD1306_I2C_ADDR, &var, 1, false);
        while(I2C_MASTER_IsTxBusy(handle));
        I2C_MASTER_Transmit(handle, false, SSD1306_I2C_ADDR, &SSD1306_Buffer[SSD1306_WIDTH*i], SSD1306_WIDTH, true);
        while(I2C_MASTER_IsTxBusy(handle));
    }
}

//    Draw one pixel in the screenbuffer
//    X => X Coordinate
//    Y => Y Coordinate
//    color => Pixel color
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }
    
    // Check if pixel should be inverted
    if(SSD1306.Inverted) {
        color = (SSD1306_COLOR)!color;
    }
    
    // Draw in the right color
    if(color == White) {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else { 
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

// Draw 1 char to the screen buffer
// ch       => char write to buffer
// Font     => Font waarmee we gaan schrijven
// color    => Black or White
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color) {
    uint32_t i, b, j;
    
    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;
    
    // Check remaining space on current line
    if (SSD1306_WIDTH < (SSD1306.CurrentX + Font.FontWidth) ||
        SSD1306_HEIGHT < (SSD1306.CurrentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }
    
    // Use the font to write
    // Buffer der Fonts aufgeteilt in die Width (Hex-Zahl) / Weite (Stelle im Array)
    // geht hier durch
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
                ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR) color);
            } else {
                ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR)!color);
            }
        }
    }
    
    // The current space is now taken
    SSD1306.CurrentX += Font.FontWidth;
    
    // Return written char for validation
    return ch;
}

// Write full string to screenbuffer
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color) {
    // Write until null-byte
	while (*str)
	{
		if (ssd1306_WriteChar(*str, Font, color) != *str) {
			// Char could not be written
			return *str;
		}

		// Next char
		str++;
	}

	// Everything ok
	return *str;
}

void ssd1306_InvertColors(void)
{
    SSD1306.Inverted = !SSD1306.Inverted;
}

// Position the cursor
void ssd1306_SetCursor(uint8_t x, uint8_t y) {
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}
