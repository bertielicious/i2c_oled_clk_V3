#include "config.h"
void split_time(void)
{
    
    secs_lsb = seconds%10;
    secs_msb = seconds/10;
    mins_lsb = minutes%10;
    mins_msb = minutes/10;
    hours_lsb = hours%10;
    hours_msb = hours/10;
    
    date_lsb = date%10;
    date_msb = date/10;
   /* thous = time/1000;
    huns = (time % 1000)/100;
    tens = (time % 100)/10;
    units = time % 10;  */
}
