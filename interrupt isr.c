
#include <pic16f1459.h>
#include "config.h"
#include "main.h"
#include "clear_OLED.h"
#include "OLED_write.h"

#include "set_page_address.h"
#include "set_columns.h"
#include "match_digit.h"
#include "split_time.h"
#include "PCF8583_read.h"
#include <stdio.h>

void interrupt isr (void)
{
    uchar x,i;
    
    if(INTCONbits.TMR0IF == 1)
    {
        //if(overflow >=123)      // 2 sec refresh of sensor reading
        if(overflow >=10)
        {
            //read the sensor data
         /*   PCF8583_read(0x0a, 0x01);   //slave_addr,reg_addr
            split_time();               // splits read byte into lo and hi
           
            match_digit(date_msb, 0x09, 0x15, 0x06);
            match_digit(date_lsb, 0x16, 0x22, 0x06);*/
            RA5 = ~RA5;
            for (x = 0x02; x < 0x05; x++)   // read seconds, minutes and hours
            {
                PCF8583_read(0xa0,x);  
                
                split_time();               // split seconds, mins and hrs into msb and lsb
    
                // set_columns(0x21, 0x3f, 0x4f);
                match_digit(hours_msb, 0x09, 0x15, 0x03);
                // set_columns(0x21, 0x48, 0x50);
                match_digit(hours_lsb, 0x16, 0x22, 0x03);
                // set_columns(0x21, 0x51, 0x59);
                
                set_columns(0x21,0x23, 0x2f);
                set_page_address(0x78, 0x00, 0x04);
                ptr = &colon[0];
                for (i = 0; i < 8; i++)        
                {
                    OLED_write(OLED_ADDR, 0x40,*ptr);
                    ptr++;
                }
                match_digit(mins_msb, 0x30,0x3c, 0x03);
                // set_columns(0x21, 0x5a, 0x62);
                match_digit(mins_lsb, 0x3d,0x49, 0x03);
                
                set_columns(0x21,0x4a, 0x56);
                set_page_address(0x78, 0x00, 0x04);
                ptr = &colon[0];
                for (i = 0; i < 8; i++)        
                {
                    OLED_write(OLED_ADDR, 0x40,*ptr);
                    ptr++;
                }
                match_digit(secs_msb, 0x57, 0x63, 0x03);
            
                match_digit(secs_lsb, 0x64, 0x70, 0x03);
                
                
            
            }
            PORTCbits.RC7 = ~PORTCbits.RC7;
            overflow = 0;
        }
        overflow++;
        TMR0 = 0x00;  
        INTCONbits.TMR0IF = 0;
    }
}
