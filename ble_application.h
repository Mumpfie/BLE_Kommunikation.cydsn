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
#ifndef BLE_APPLICATION_H
#define BLE_APPLICATION_H
    
#include "project.h"

/* Initalize BLE*/
void InitBle(void);

/* Processes BLE Events */
void ProcessBleEvents(void);

/* Updates Values */
void UpdateCharacteristics(void);

/* Send Notifications */
void SendMeasurementNotificationSwitch(void);

#endif /* #ifndef BLE_APPLICATION_H */
/* [] END OF FILE */
