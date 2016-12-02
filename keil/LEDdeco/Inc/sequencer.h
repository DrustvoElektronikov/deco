/**
  ******************************************************************************
  * @file    sequencer.h
  * @brief   Sequencer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 S54MTB</center></h2>
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SEQ_H__
#define __SEQ_H__

#include "stm32f0xx.h"                  // Device header

#ifdef __cplusplus
 extern "C" {
#endif

void Sequencer(void);
void Sequencer_Init(void);
void Sequencer_start(void);
void Sequencer_stop(void);


    
#ifdef __cplusplus
}
#endif

#endif /* __SEQ_H__ */

/************************ (C) COPYRIGHT S54MTB *****END OF FILE****/



