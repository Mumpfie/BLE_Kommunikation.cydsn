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

/* Header file includes */
#include <project.h>
#include "interrupt.h"
#include "led.h"
#include "ble_application.h"

bool notificationFlag = false;

void setNotificationFlag() {
    notificationFlag = true;
}

void clearNotificationFlag() {
    notificationFlag = false;
}

bool getNotificationFlag() {
    return notificationFlag;
}

/* Function definations */
void IsrMcwdt(void) {    
    /* Clear the MCWDT interrupt */
    Cy_MCWDT_ClearInterrupt(MCWDT_HW,CY_MCWDT_CTR0);
    NVIC_ClearPendingIRQ(isr_LED_cfg.intrSrc); 
    
    /* Update LED */
    ServiceStatusLed();
    
    /* Send Notifications */
    notificationFlag = true;
}

void InitISR(void) {
    /* Initialize MCDWT */
    Cy_MCWDT_Init(MCWDT_HW, &MCWDT_config);
    
    /* Enable the interrupts for MCDWT Counter1 only */
    Cy_MCWDT_SetInterruptMask(MCWDT_HW, CY_MCWDT_CTR0);
    
    /* Initialize and enable MCWDT interrupt */
    Cy_SysInt_Init	(&isr_LED_cfg, IsrMcwdt);	
    NVIC_ClearPendingIRQ(isr_LED_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)isr_LED_cfg.intrSrc);
    
    /* Start MCDWT Counter0 */
    Cy_MCWDT_Enable(MCWDT_HW, CY_MCWDT_CTR0,0u);
    
    /* Update GATT database*/
    UpdateCharacteristics();
}

/*Disable MCWDT?*/
void UpdateISR(void);

/* [] END OF FILE */
