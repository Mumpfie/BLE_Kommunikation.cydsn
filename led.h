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

/* Include guard */
#ifndef LED_H
#define LED_H
    
/* Header file includes */
#include <project.h>
    
/* Data-type of status LED indication for BLE */
typedef enum
{
    NO_INDICATION,
    INDICATE_ADVERTISEMENT,
    INDICATE_CONNECTION,
}   led_indication_status_t;

/* Macros */
#define TurnOnLed Cy_GPIO_Write(LED_PORT, LED_NUM, 0);
#define TurnOffLed Cy_GPIO_Write(LED_PORT, LED_NUM, 1);
#define ToggleLed Cy_GPIO_Inv(LED_PORT, LED_NUM);

/* Set LED to current indication status
   NO_INDICATION: LED off
   INDICATE_ADVERTISEMENT: LED blinking
   INDICATE_CONNECTION: LED on */
void UpdateStatusLed(led_indication_status_t indication);

/* Called in ISR to enable blinking */
void ServiceStatusLed(void);

/* Check whether LED needs MCWDT*/
bool IsLedToggleActive(void);

#endif /* LED_H */
/* [] END OF FILE */
