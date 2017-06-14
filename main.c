/* Robinson Paniagua
 * Lab 3 Hibernation Mode
 * May 27, 2017
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "utils/ustdlib.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"




int main(void) {

	//Configuration of the Hibernation Module
    unsigned long TimeStart,TimeEnd,Switch2,Clock;
    uint32_t Delay,Seconds;
    Seconds = 4;                   // Seconds of Delay that the User wants
    Delay = Seconds*(16*(10^6));  //Delay of the System Clock
    TimeStart = 0;                // Start of Hibernation
    TimeEnd = 5;                  //End of Hibernation in Seconds

    // Method of Wakeup, Can be Switch2, Clock, Or Both by using [ HibernateWakeSet(Switch2|Clock) ]
    Switch2 = HIBERNATE_WAKE_PIN;
    Clock = HIBERNATE_WAKE_RTC;

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);     //Initializes the board Clock
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                                           //Enables the GPIO Clock Gating Control
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);             //Set the GPIO Pin Direction
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);              //Turns on the Green LED
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);                                    // Enables the hibernation Module

	HibernateEnableExpClk(SysCtlClockGet());                                //Assigns the frequency of the clock, in this case it's 4 MHZ
	HibernateGPIORetentionEnable();                                        //Allows for retention of the current GPIO state during hibernation
	SysCtlDelay(Delay);                                                    //Time Delay Function, time = (wanted time in seconds *  (16*10^6)(16MHZ))
                                                                           //  64000000 = (4* (16*10^6)
	HibernateRTCSet(0);                                                   //Sets the Real Time Hibernation Clock
	HibernateRTCEnable();                                                //Acts like a timer, can be set to wake up on a specific time period
	HibernateRTCMatchSet(TimeStart,TimeEnd);                             //Wakes up from Hibernation after 5 seconds
	HibernateWakeSet(Switch2);                                           // Configures which conditions are used for wakeup, Pin 2
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0x00);                     //Turns off LED
	HibernateRequest();



	while(1)
	{

	}
	}


