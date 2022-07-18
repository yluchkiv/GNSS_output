
#include "i2c.h"
#include "SSD1306.h"
#include "myserial.h"
#include "ring_buff.h"

char buffer[BUFFER_SIZE+1] = {'\0'};    //buffer filled with NUL 
int buffer_data_available = 0;          // the value that monitors how many cells are occupied and\or how many cells have beed read off                                             
                  
bool write_into_buffer(void)
{
    static int write_index = 0;  //index for placing into the cell

    if(buffer_data_available == BUFFER_SIZE)
    {
        return false;                     // if buff is full, quit the function
    }

    buffer[write_index] = USART_Receive(); // if USART resulr successfully assigned to buff cell
    
    write_index++;                    
    buffer_data_available++;     

    if(write_index == BUFFER_SIZE)    
        write_index = 0;
    read_from_buffer();  
    return true;
}

bool read_from_buffer(void)
{
    static int read_index = 0;  //index for reading from the cell

    if(buffer_data_available == 0) 
    {            
        return false; // at first need to check if the buffer in not empty
    }   

    else // we call the function and assign the result to the cell in buffer 
    {

        read_index++;                        // move the index to the next cell to read from
        buffer_data_available--;
        
        if(read_index == BUFFER_SIZE)
        {
            read_index = 0; // when the read pos reaches end of buffer, reset index to 0
        }   
        USART_Transmit(buffer[read_index]);
    }
    return true;
                                        
}
