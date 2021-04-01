
#include "configuration.h"

/*----------------------------------------------------------------------------
 
 u16 TimeXMicroSeconds(u16 u16DesiredTime)
 Sets Timer0 to count u16Microseconds_
 
 Requires:
 -Timer0 configured such that each timer tick is 1 microsecond
 -u16DesiredTime is the value in microseconds to time from 1 to 65535
 
 Promises:
 -Pre-loads TMROH:L to clock out desired period
 -TMR0IF clearer
 -Timer0 enabled
 -returns a value of 1 if something weird happens when clearing TMR0IF and a 0 if not.
 */


u16 TimeXMicroSeconds(u16 u16DesiredTime)
{
    
    
   
    
    //Stop the clock
    T0CON0 ^= 0b10000000;
  
    
    //Need to subtract number we want counted to from maximum number we could count to.
    u16 u16Time = 0xFFFF - u16DesiredTime;
    
    
    //Load the registers
    TMR0L =  u16Time & 0x00FF;          
    TMR0H =  (u16Time & 0xFF00) / 0x100;      
    
    PIR3 ^= 0b10000000;
    
    T0CON0 ^= 0b10000000;
    
   
    
    return 0;//u16SomethingWeirdIsHappening;
    
}
