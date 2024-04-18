/*
 * ControllerCAN.cpp
 *
 *  Created on: April 12, 2024
 *      Author: @JorgePerC
 */
#include "ControllerCAN.hpp"

//Remember MSB: Most significant bit

// This is a function that will be called in case something failed
//TODO: make it global but put it somewhere usefull
static void Error_Handler(void)
{
  while (1)
  {
  }
}

ControllerCAN::ControllerCAN(CAN_HandleTypeDef* handler, int id){
  // Check there are no duplicate IDs
  hcan = handler;
  //Turn off interruption mode
  // HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
  // HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);

  // HAL_CAN_DeactivateNotification(hcan, );
  // Check that the handler has been initialized
  if (! HAL_CAN_GetState(hcan) != CAN_INITSTATUS_SUCCESS){
    Error_Handler();
  }
  
}

void ControllerCAN::updateMessage(uint8_t cntrlId, uint8_t motorId,  uint16_t value){

  // Set postion to be written
  uint8_t writePos = motorId == CAN_ID_4 ? 6 : (motorId%4-1)*2;

  // Define canId message to send
    // Specifies the standard identifier
  TxHeader->StdId = cntrlId;
    // Specifies the type of identifier for the message
  TxHeader->IDE = CAN_ID_STD;
    // Specifies the length of the frame that will be transmitted
  TxHeader->DLC = RM_DLC;
    // Specifies the type of frame for the message
  TxHeader->RTR = CAN_RTR_DATA;
    // To avoid overriding the last values
  TxHeader->TransmitGlobalTime = DISABLE;

  TxData[writePos] = value;
}

void ControllerCAN::sendMessage(){
  
    // Prior to sending the message, we must 
    // check that all prev messages have been sent
    // we do so wit the tx boxes
    uint32_t selectedMailBox = NULL;
    // Monitor the Tx mailboxes availability until at least one Tx mailbox is free
    if ((hcan->Instance->TSR & CAN_TSR_TME0) != 0U) {
      selectedMailBox = CAN_TX_MAILBOX0;
    } else if ((hcan->Instance->TSR & CAN_TSR_TME1) != 0U) {
      selectedMailBox = CAN_TX_MAILBOX1;
    } else if ((hcan->Instance->TSR & CAN_TSR_TME2) != 0U) {
      selectedMailBox = CAN_TX_MAILBOX2;
    }
    if (selectedMailBox != NULL){
      if (HAL_CAN_AddTxMessage(hcan, TxHeader, TxData, &selectedMailBox) != HAL_OK) {
        //uart_buf_len = sprintf(uart_buf, "Error");
        //HAL_UART_Transmit(&huart3, (uint8_t *)uart_buf, uart_buf_len, HAL_MAX_DELAY);
        Error_Handler();
      } 
    }   
}

/* This method is configured to read messages through polling.
Note that the implementation is rather different from using interrupts
Since these functions NEED TO BE CONSTANTLY CALLED. 
On one side, this is easier, since will be using RTOS later
*/
void ControllerCAN::readMessagePolling(){
  
  // Check there's a message on the fifo 
  if (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_FILTER_FIFO0) > 1) {

      /* Get RX message */
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, RxHeader, RxData) != HAL_OK){
      /* Reception Error */
      Error_Handler();
    }
  }
  
}

//TODO: Complete
void ControllerCAN::getMotorInfo(uint8_t feedbackID, uint8_t motorId) {
  // Decode message
      RxHeader->StdId = FEEDBACK_ID + motorId;
}

void ControllerCAN::setChannelFilter(){

  //TODO: FIGURE OUT HOW THIS WORKS
  // Use interrtuptions or no 
//   HAL_CAN_ActivateNotification()

//   // Filter messages and freq
//   HAL_CAN_ConfigFilter();
}

