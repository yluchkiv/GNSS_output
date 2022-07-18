#include "i2c.h"
#include "SSD1306.h"
#include "ring_buff.h"
#include "myserial.h"


void display_init();

int main()
{
    //display_init();
    serial_setup();
    USART_Transmit_String("hello world!\r\n");
 
 
    while(1)
    {
        write_into_buffer();
        
        
    }
    return 0;
}

void display_init()
{
    OLED_Init();  //initialize the OLED
    OLED_SetCursor(0, 0);        //set the cursor position to (0 - move down, 0-move left)
    OLED_Printf("GNSS Scan Initialized");
}
