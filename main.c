/*
 * File:   main.c
 * Author: Phil Glazzard
 *
 * Created on 25 January 2019, 20:52
 */


#include <xc.h>
#include "config_osc.h"
#include "setup_ports.h"
#include "config_TMR0.h"
#include "config_usart.h"
#include "i2c_start.h"
#include "i2c_write.h"
#include "i2c_stop.h"
#include "OLED_write.h"
#include "config_i2c.h"
#include "set_page_address.h"
#include "set_columns.h"
#include "config_OLED.h"
#include "clear_OLED.h"
#include <stdio.h>
#include "split_time.h"
#include "PCF8583_read.h"
#include "PCF8583_write.h"
#include "match_digit.h"
#include "dec_to_bcd.h"
void main(void) 
{
    unsigned int result = 2359;
  
    uchar x;
    config_osc();
    setup_ports();
    config_TMR0();
    config_usart();
    config_i2c();
    config_OLED();
    clear_OLED();
    //PCF8583_write(0xa0, 0x04,0x21);
   // PCF8583_write(0xa0, 0x03,0x22);
    /*set_page_address(0x78, 0x00, 0x03);
    
    set_columns(0x21, 0x00, 0x08);
    for(x = 0; x < 8; x++)
    {
       OLED_write(OLED_ADDR, 0x40,t[x]) ;
    }
    
    set_columns(0x21, 0x09, 0x11);
    for(x = 0; x < 8; x++)
    {
       OLED_write(OLED_ADDR, 0x40,i[x]);
    }
    
    set_columns(0x21, 0x12, 0x1a);
    for(x = 0; x < 8; x++)
    {
       OLED_write(OLED_ADDR, 0x40,m[x]);
    }
    
   
    set_columns(0x21, 0x1b, 0x23);
    for(x = 0; x < 8; x++)
    {
       OLED_write(OLED_ADDR, 0x40,e[x]);
    }*/
    
    while(1)
    {
       if(PORTAbits.RA4 == 0 && set_hrs < 23)
        {
           //GIE = 0;
            __delay_ms(5);
            set_hrs = set_hrs + 1;           
            dec_to_bcd(set_hrs);
            PCF8583_write(0xa0, 0x04,bcd);
            __delay_ms(250);
            
        }
         
        if(PORTCbits.RC5 == 0 && set_mins < 59)
        {
           // GIE = 0;
            __delay_ms(5);       
            set_mins = set_mins + 1;
            dec_to_bcd(set_mins);
            PCF8583_write(0xa0, 0x03,bcd);
            __delay_ms(250);
            
        }
       if(set_hrs == 23 || set_mins == 59)
       {
           set_hrs = 0;
           set_mins = 0;
       }
       
         
    }       
         
}
