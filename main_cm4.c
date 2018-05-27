/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "ble_application.h"
#include "interrupt.h"

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Initialising BLE*/
    InitBle();
    
    /* Set up MCWDT and ISR*/
    InitISR();
    
    

    for(;;)
    {
        /* Process BLE Events */
        ProcessBleEvents();
        
        /* Send data to central device */
        if(getNotificationFlag()){
            SendMeasurementNotificationSwitch();            
        }
    }
}

/* [] END OF FILE */
