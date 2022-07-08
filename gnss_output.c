#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include "i2c.h"
#include "SSD1306.h"

#define BUFFER_SIZE 256
#define BUAD 9600
#define BRC ((F_CPU/16/BUAD)-1)  // = 103.16 // 0110 0111

char scanned_message[BUFFER_SIZE+1]={'\0'}; // fill the buffer with null 

void display_init();
void Serial_Init(void);
unsigned char USART_Receive(void); //checks when the UDR0 has received all 8bits = 1 byte, then returns it
void receive_NMEA(void); 


int main()
{
    display_init();
    Serial_Init();
 
    while(1)
    {
        receive_NMEA();
    }
    return 0;
}

void display_init()
{
    OLED_Init();  //initialize the OLED
    OLED_SetCursor(0, 0);        //set the cursor position to (0 - move down, 0-move left)
    OLED_Printf("GNSS Scan Initialized");
}

void Serial_Init(void)
{
    UBRR0H = (BRC >> 8); // we need to shift 8 bits of 103 (0110 0111) to fill the lower register
    UBRR0L = BRC; //lower register
    UCSR0B = (1 << RXEN0); // Rx enable
    UCSR0C = (1 << UCSZ00)|(1 << UCSZ01)|(1 << USBS0); // 8 bit data format
}

unsigned char USART_Receive(void)
{
    while ( !(UCSR0A & (1 << RXC0)) ); //Wait for data to be received 
    return UDR0; // Get and return received data from buffer 
}

void receive_NMEA(void)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        scanned_message[i] = USART_Receive(); // data transfered from UDR0 reg to the buffer
        if((i > 0)&&(scanned_message[i-1]=='\r') && (scanned_message[i]=='\n')) //detecting the end of NMEA message
        {
            scanned_message[i-1]='\0'; // ends the message 
            // if(strncmp(scanned_message,"GGA",3)==0)  
            // {

            // }
            OLED_SetCursor(4,0);
            OLED_Printf("Data: %s", scanned_message);

        }
            
    }    
} 
