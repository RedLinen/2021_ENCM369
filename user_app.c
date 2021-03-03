/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    
    LATA = 0x00;
    
    //Activate clock in asynchronous mode. Use Fosc/4 as source. Set pre-scaler to 1:16 and post-scaler to 1:1
    T0CON0 = 0b10110000;
    T0CON1 = 0b01010100;
    TMR0L;
    TMR0H;
   
} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    //Set counters
    static u16 u16Counter = 0x00;
    static u16 u16LightPatternIncrementer = 0x00;
    
    //This is just here so I can run it with buttons.
    static u16 u16PowerSwitch = 0x00;
    //Button enable
    u8 u8YesIWouldLikeToUseTheButtons = 0x0;
    
    u8 au8LightPatterns[] = {0b00111111, 0b00001100, 0b00010010, 0b00110011, 0b000011110,0b00001100};
    
    u8 u8TempForLata = 0x0;
    
   
    
    //Please ignore these "if" statements. They are just so I can 
    //turn the LEDs of and on with the buttons.
    //This was so useful for testing that I did mot have the heart
    //to remove it.
    if(u8YesIWouldLikeToUseTheButtons)
    {
        if((PORTB & 0x20) == 0x20)
        {
            u16Counter = 0x00;
            u16PowerSwitch = 0x01;

        }
        if((PORTB & 0x08) == 0x08)
        {
            u16PowerSwitch = 0x00;
            LATA = 0x00;
            u16LightPatternIncrementer = 0x00;
        }
        if(u16PowerSwitch == 0x01)
        {
            u16Counter++;
        }
    }
    
    
    //Counter is updated here when buttons are not being used.
    if(u8YesIWouldLikeToUseTheButtons == 0x0)
    {
        u16Counter++;
    }
    //Update is set for one-half second
    if(u16Counter == 500)
    {
        
       u8TempForLata = 0x0;
       u8TempForLata = u8TempForLata | LATA;
       
       u8TempForLata ^= au8LightPatterns[u16LightPatternIncrementer];
       
       LATA = u8TempForLata;
        
        u16LightPatternIncrementer++;
        
        if(u16LightPatternIncrementer >= 6)
        {
            u16LightPatternIncrementer = 0x00;
        }
        
        u16Counter = 0;
    }
    
    
    
    
    
    
    
    

        

    
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
