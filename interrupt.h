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

/* Include Guard */
#ifndef INTERRUPT_H
#define INTERRUPT_H
    
/* Header file includes */
#include <project.h>

/* Initializes ISR */
void InitISR(void);

/* Checks if interrupts are needed and disables MCDWT if that is the case */
void UpdateISR(void);

void setNotificationFlag(void);

void clearNotificationFlag(void);

bool getNotificationFlag(void);

#endif /* INTERRUPT_H */
/* [] END OF FILE */
