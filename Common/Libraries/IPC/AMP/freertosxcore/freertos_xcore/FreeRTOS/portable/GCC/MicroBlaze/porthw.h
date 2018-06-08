/*
    MicroBlaze(TM) GCC Port for FreeRTOS

    Copyright (C) 2010 Tethers Unlimited, Inc.

    This file is part of the MicroBlaze(TM) GCC port for FreeRTOS.

    The MicroBlaze(TM) GCC port for FreeRTOS is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The MicroBlaze(TM) GCC port for FreeRTOS is distributed in the hope
    that it will be useful, but WITHOUT ANY WARRANTY; without even
    the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the MicroBlaze(TM) GCC port for FreeRTOS. If not, see
    <http://www.gnu.org/licenses/>.
    
    MicroBlaze(TM) is a registered trademark of Xilinx, Inc.

    1 tab == 4 spaces!
*/

/**
 * @file porthw.h
 * @ingroup freertosmbport
 * @author Tyrel Newton <newton@tethers.com>, Tethers Unlimited, Inc.
 * @brief Functions that provide the kernel with an interface to the MicroBlaze peripherals.
 * @see porthw.c
 */

#ifndef PORTHW_H
#define PORTHW_H

#ifndef PORTMACRO_H
    #error portmacro.h must be included before porthw.h.
#endif

#include <xintc.h>
#include <xtmrctr.h>

/**
 * @ingroup freertosmbport
 *
 * Sets up the required MicroBlaze hardware drivers for minimum kernel
 * functionality. This includes enabling the instruction and data caches
 * (if configured) and initializing the interrupt controller driver.
 * 
 * @attention Should be called at the beginning of program execution.
 *
 * @return pdPASS if successful, pdFAIL otherwise.
 *
 * @par Example:
 * @code
    int main(void)
    {
        xPortSetupHardware();
        // create tasks
        vTaskStartScheduler();
    }
 * @endcode
 */
portBASE_TYPE xPortSetupHardware( void );

/**
 * @ingroup freertosmbport
 *
 * Initializes and configures the interrupt controller for the MicroBlaze
 * (an xps_intc instance). The definition portXPS_INTC_DEVICE_ID is used
 * to configure the device ID of the xps_intc instance.
 * 
 * @note Called by xPortSetupHardware.
 *
 * @return pdPASS if successful, pdFAIL otherwise.
 */
portBASE_TYPE xPortSetupInterruptController( void );

/**
 * @ingroup freertosmbport
 * 
 * Enables the processing of interrupts generated by the given source
 * by the interrupt controller (an xps_intc instance) managed by the
 * kernel via this port. Essentially a wrapper function around
 * XIntc_Disable.
 * 
 * @param ucInterruptID Identifier for the interrupt to enable. These
 * identifiers are defined in xparameters.h.
 */
void vPortEnableInterrupt(unsigned portCHAR ucInterruptID);

/**
 * @ingroup freertosmbport
 * 
 * Disables the processing of interrupts generated by the given source
 * by the interrupt controller (an xps_intc instance) managed by the
 * kernel via this port. Essentially a wrapper function around
 * XIntc_Disable.
 * 
 * @param ucInterruptID Identifier for the interrupt to disable. These
 * identifiers are defined in xparameters.h.
 */
void vPortDisableInterrupt(unsigned portCHAR ucInterruptID);

/**
 * @ingroup freertosmbport
 *
 * Connects an interrupt handler to the interrupt controller (an xps_intc
 * instance) managed by the kernel via this port. Once connected, the
 * associated interrupt is also enabled. Essentially a wrapper function
 * around XIntc_Connect and XIntc_Enable.
 * 
 * @note Used by xPortSetupTickTimer, which is called when the scheduler
 * is started.
 * 
 * @note The declaration for an interrupt handler, which is defined in
 * xbasic_types.h, looks like:
 * @code
    void myInterruptHandler( void *InstancePtr );
 * @endcode
 * 
 * @param ucInterruptID Identifier for the interrupt that
 * the given handler will be associated with. These
 * identifiers are defined in xparameters.h.
 * 
 * @param pxHandler Pointer to the interrupt handler that is
 * to be connected to the defined interrupt.
 * 
 * @param pvCallBackRef Pointer that will be passed to the
 * given interrupt handler when called. This is typically
 * a pointer to the hardware device driver instance whose
 * interrupt is to be serviced by the given interrupt handler.
 * 
 * @return pdPASS if successful, pdFAIL otherwise.
 * 
 * @par Example:
 * @code
    // device driver instances
    static XGpio myGpio0;
    static XGpio myGpio1;
 
    void myGpioInterruptHandler( void *pvInstance )
    {
        XGpio *pxGpio = (XGpio*)pvInstance;
 	
        // service the GPIO interrupt for the given GPIO instance
    }
 
    int main( void )
    {	
        // Initialize the basic hardware and interrupt controller.
        xPortSetupHardware();
	
        // Initialize the two GPIO device drivers.
        XGpio_Initialize(&myGpio0, MY_GPIO_0_DEVICE_ID);
        XGpio_Initialize(&myGpio1, MY_GPIO_1_DEVICE_ID);
	
        // Connect the same interrupt handler to both GPIO interrupts.
        xPortConnectInterruptHandler(MY_GPIO_0_INTERRUPT_ID, myGpioInterruptHandler, &myGpio0);
        xPortConnectInterruptHandler(MY_GPIO_1_INTERRUPT_ID, myGpioInterruptHandler, &myGpio1);
        
        // Perform other hardware intialization and task creation.
        // ...
        
        // Start the scheduler, which will enable the processing of interrupts.
        vTaskStartScheduler();
    }
 * @endcode
 */
portBASE_TYPE xPortConnectInterruptHandler( unsigned portCHAR ucInterruptID, XInterruptHandler pxHandler, void *pvCallBackRef );

/**
 * @ingroup freertosmbport
 * 
 * Disconnects the interrupt handler from the interrupt controller (an
 * xps_intc instance) manged by the kernel via this port. The interrupt
 * source is disabled first. Essentially a wrapper function around
 * XIntc_Disconnect.
 * 
 * @param ucInterruptID Identifier for the interrupt whose handler is to
 * be disconnected. These identifiers are defined in xparameters.h.
 */
void vPortDisconnectInterruptHandler(unsigned portCHAR ucInterruptID);

/**
 * @ingroup freertosmbport
 *
 * Configures a timer to generate a periodic tick to be used by the kernel.
 * The definition portXPS_TIMER_DEVICE_ID is used to configure the device ID
 * of the xps_timer instance that will be configured.
 * 
 * The timer configuration uses a single counter as a down counter in compare
 * mode with the interrupt and auto-reload options set. The counter number can
 * be controlled by re-defining portXPS_TIMER_COUNTER_NUMBER in the
 * FreeRTOSConfig. The interrupt number for this timer must also be defined
 * using portXPS_TIMER_INTERRUPT_ID.
 *
 * @note Should be called just before the scheduler starts the first task.
 * 
 * @param pxHandler Pointer to the function that will process the periodic
 * tick for the operating system.
 * 
 * @param xCounterValue The value that the timer will be reset to once it
 * reaches zero. Sets the period for the kernel's tick timer.
 * 
 * @return pdPASS if successful, pdFAIL otherwise.
 */
portBASE_TYPE xPortSetupTickTimer( XTmrCtr_Handler pxHandler, unsigned portLONG xCounterValue );


void vPortMemoryBarrier( void );

#endif /* PORTHW_H */
