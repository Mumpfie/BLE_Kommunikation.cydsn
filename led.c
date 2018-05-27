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
#include "led.h"

/* Flags */
bool static toggleLedFlag = false;

/* Function definations */
void UpdateStatusLed (led_indication_status_t indication){
    switch (indication)
    {
        case NO_INDICATION:
            TurnOffLed;
            toggleLedFlag = false;
            break;
        case INDICATE_ADVERTISEMENT:
            TurnOnLed;
            toggleLedFlag = true;
            break;
        case INDICATE_CONNECTION:
            TurnOnLed;
            toggleLedFlag = false;
            break;
    }
}

void ServiceStatusLed (void){
    static bool toggleLedStatusFlag = false;
    if (toggleLedFlag)
    {
        if (toggleLedStatusFlag)
        {
            TurnOffLed;
            toggleLedStatusFlag = false;
        }
        else
        {
            TurnOnLed;
            toggleLedStatusFlag = true;
        }
    }
}

bool IsLedToggleActive(void){
    return toggleLedFlag;
}

/* [] END OF FILE */
