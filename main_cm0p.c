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

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    /* Start BLE */
    if(Cy_BLE_Start(NULL) == CY_BLE_SUCCESS){
        /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
        Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
        
    }
    else
    {      
        /* Halt the CPU if the BLE initialization failed */
        CY_ASSERT(0u != 0u);
    }

    for(;;)
    {
        /* Cy_Ble_ProcessEvents() allows the BLE stack to process pending events */
        Cy_BLE_ProcessEvents();
    }
}

/* [] END OF FILE */
