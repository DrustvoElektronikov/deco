/**
  ******************************************************************************
  * @file    audio.h
  * @brief   Audio module header file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 S54MTB</center></h2>
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "stm32f0xx.h"                  // Device header

void Audio_Init(void);
void Audio_Play(uint16_t frequency);
uint16_t MIDI2Hz(uint8_t note);
void Audio_PlayMidiNote(uint8_t note);
void Audio_Volume(uint16_t vol);


#endif /* __AUDIO_H__ */

/************************ (C) COPYRIGHT S54MTB *****END OF FILE****/
