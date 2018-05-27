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

#include "ble_application.h"
#include "led.h"
#include "interrupt.h"

/* Variables */
cy_stc_ble_conn_handle_t connectionHandle;

/* Functions */

void StackEventHandler(uint32_t event, void *eventParam) {
    switch(event){
        case CY_BLE_EVT_STACK_ON:
            /* Start advertising */
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            break;  
        case CY_BLE_EVT_GATT_CONNECT_IND:            
            /* Update attribute handle on GATT Connection */
            connectionHandle = *(cy_stc_ble_conn_handle_t *) eventParam;
            break;
        case CY_BLE_EVT_GAP_DEVICE_CONNECTED:
            break;
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
            /* Restart advertising if device disconnects*/
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            break;
        default:
            break;
    }
}

void InitBle(void) {
    /* Start the BLE component and register the stack event handler */
    Cy_BLE_Start(StackEventHandler);
}

void ProcessBleEvents(void) 
{  
    /* Process BLE events according to StackEventHandler()*/
    Cy_BLE_ProcessEvents();
    
    /* Variable used to control status LEDs */
    static led_indication_status_t bleStatusIndication = NO_INDICATION;

    /* BLE is connected */
	if(Cy_BLE_GetConnectionState(connectionHandle) == 
        CY_BLE_CONN_STATE_CONNECTED)
	{
        /* Update the status LEDs if they're not indicating the connection
        already */
        if(bleStatusIndication != INDICATE_CONNECTION)
        {
            bleStatusIndication = INDICATE_CONNECTION;
            UpdateStatusLed(bleStatusIndication);
        }
    }    
    /* BLE is advertising */
    else if (Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADVERTISING)
    {
        /* Update the status LEDs if they're not indicating the advertisement
        already */
        if(bleStatusIndication !=INDICATE_ADVERTISEMENT)
        {
            bleStatusIndication = INDICATE_ADVERTISEMENT;
            UpdateStatusLed(bleStatusIndication);
        }
    } 
    else
    {
        bleStatusIndication = NO_INDICATION;
        UpdateStatusLed(bleStatusIndication);
    }
}

void UpdateCharacteristics(void)
{
    /*Structure used to load values to GATT database*/
    cy_stc_ble_gatt_handle_value_pair_t	handleValuePair;
    
    /* Placeholder for GetValue functions that are to implement */
    float32_t testVoltage = 3.01;
    float32_t testCurrent = -1.23;
    uint16_t testSpeed = 5432;
    float32_t testTorque = 432.101;
    uint8_t testEfficiency = 65;
    
    handleValuePair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_VOLTAGE_CHAR_HANDLE;
    handleValuePair.value.val = (uint8_t*)&testVoltage;
    handleValuePair.value.len = sizeof(testVoltage);    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&handleValuePair);
    
    handleValuePair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_CURRENT_CHAR_HANDLE;
    handleValuePair.value.val = (uint8_t*)&testCurrent;
    handleValuePair.value.len = sizeof(testCurrent);    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&handleValuePair);
    
    handleValuePair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_SPEED_CHAR_HANDLE;
    handleValuePair.value.val = (uint8_t*)&testSpeed;
    handleValuePair.value.len = sizeof(testSpeed);    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&handleValuePair);
    
    handleValuePair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_TORQUE_CHAR_HANDLE;
    handleValuePair.value.val = (uint8_t*)&testTorque;
    handleValuePair.value.len = sizeof(testTorque);    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&handleValuePair);
    
    handleValuePair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_EFFICIENCY_CHAR_HANDLE;
    handleValuePair.value.val = (uint8_t*)&testEfficiency;
    handleValuePair.value.len = sizeof(testEfficiency);    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&handleValuePair);
}

void SendMeasurementNotificationSwitch() {
    if(Cy_BLE_GetConnectionState(connectionHandle) == CY_BLE_CONN_STATE_CONNECTED)
    {
         if (Cy_BLE_GATT_GetBusyStatus(connectionHandle.attId) == CY_BLE_STACK_STATE_FREE)
        {   
            int static c = 0;
            
            /* Test values */
            float32_t static testVoltage = 3.01;
            float32_t static testCurrent = -1.23;
            float32_t static testTorque = 432.101;            
            uint16_t static testSpeed = 5432;
            uint8_t static testEfficiency = 69;
            
            cy_stc_ble_gatts_handle_value_ntf_t proximityNotificationHandle;            
            proximityNotificationHandle.connHandle = connectionHandle;
            
            
            switch (c) {  
                case 0:
                case 1:
                /* Local variable that stores CapSense notification data parameters */                
                proximityNotificationHandle.handleValPair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_VOLTAGE_CHAR_HANDLE;
                proximityNotificationHandle.handleValPair.value.val = (uint8_t*)&testVoltage;
                proximityNotificationHandle.handleValPair.value.len = sizeof(testVoltage);
                testVoltage++;
                break;
                
                case 2:
                /* Local variable that stores CapSense notification data parameters */
                proximityNotificationHandle.handleValPair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_CURRENT_CHAR_HANDLE;
                proximityNotificationHandle.handleValPair.value.val = (uint8_t*)&testCurrent;
                proximityNotificationHandle.handleValPair.value.len = sizeof(testCurrent);
                break;
                
                case 3:
                /* Local variable that stores CapSense notification data parameters */
                proximityNotificationHandle.handleValPair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_TORQUE_CHAR_HANDLE;
                proximityNotificationHandle.handleValPair.value.val = (uint8_t*)&testTorque;
                proximityNotificationHandle.handleValPair.value.len = sizeof(testTorque); 
                break;
                 
                case 4:
                /* Local variable that stores CapSense notification data parameters */
                proximityNotificationHandle.handleValPair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_SPEED_CHAR_HANDLE;
                proximityNotificationHandle.handleValPair.value.val = (uint8_t*)&testSpeed;
                proximityNotificationHandle.handleValPair.value.len = sizeof(testSpeed);
                testSpeed--;
                break;
                
                case 5:
                /* Local variable that stores CapSense notification data parameters */
                proximityNotificationHandle.handleValPair.attrHandle = CY_BLE_MEASUREMENT_SERVICE_EFFICIENCY_CHAR_HANDLE;
                proximityNotificationHandle.handleValPair.value.val = (uint8_t*)&testEfficiency;
                proximityNotificationHandle.handleValPair.value.len = sizeof(testEfficiency); 
                c = 0;
                clearNotificationFlag();
                break;
            }
            
            c++;
                        
            /* Send the updated handle as part of attribute for notifications */
            Cy_BLE_GATTS_Notification(&proximityNotificationHandle);                  
        }
    }
}


/* [] END OF FILE */