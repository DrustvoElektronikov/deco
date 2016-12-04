/**
  ******************************************************************************
  * File Name          : audio.c
  * Description        : Audio init and play


         o      ooooo  oooo ooooooooo   ooooo   ooooooo   
        888      888    88   888    88o  888  o888   888o 
       8  88     888    88   888    888  888  888     888 
      8oooo88    888    88   888    888  888  888o   o888 
    o88o  o888o   888oo88   o888ooo88   o888o   88ooo88   


				This is free and unencumbered software released into the public domain.

			Anyone is free to copy, modify, publish, use, compile, sell, or
			distribute this software, either in source code form or as a compiled
			binary, for any purpose, commercial or non-commercial, and by any
			means.

			In jurisdictions that recognize copyright laws, the author or authors
			of this software dedicate any and all copyright interest in the
			software to the public domain. We make this dedication for the benefit
			of the public at large and to the detriment of our heirs and
			successors. We intend this dedication to be an overt act of
			relinquishment in perpetuity of all present and future rights to this
			software under copyright law.

			THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
			EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
			MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
			IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
			OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
			ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
			OTHER DEALINGS IN THE SOFTWARE.

			For more information, please refer to <http://unlicense.org>
			
  ******************************************************************************
  */


#include "stm32f0xx.h"                  // Device header
#include "audio.h" 
#include <math.h>

extern TIM_HandleTypeDef htim3;

static uint16_t AudioVolume = 500;

const uint16_t MidiFrequencies[128-24] = 
{
		33,    // Midi Note: 24
		35,    // Midi Note: 25
		37,    // Midi Note: 26
		39,    // Midi Note: 27
		41,    // Midi Note: 28
		44,    // Midi Note: 29
		46,    // Midi Note: 30
		49,    // Midi Note: 31
		52,    // Midi Note: 32
		55,    // Midi Note: 33
		58,    // Midi Note: 34
		62,    // Midi Note: 35
		65,    // Midi Note: 36
		69,    // Midi Note: 37
		73,    // Midi Note: 38
		78,    // Midi Note: 39
		82,    // Midi Note: 40
		87,    // Midi Note: 41
		92,    // Midi Note: 42
		98,    // Midi Note: 43
		104,    // Midi Note: 44
		110,    // Midi Note: 45
		117,    // Midi Note: 46
		123,    // Midi Note: 47
		131,    // Midi Note: 48
		139,    // Midi Note: 49
		147,    // Midi Note: 50
		156,    // Midi Note: 51
		165,    // Midi Note: 52
		175,    // Midi Note: 53
		185,    // Midi Note: 54
		196,    // Midi Note: 55
		208,    // Midi Note: 56
		220,    // Midi Note: 57
		233,    // Midi Note: 58
		247,    // Midi Note: 59
		262,    // Midi Note: 60
		277,    // Midi Note: 61
		294,    // Midi Note: 62
		311,    // Midi Note: 63
		330,    // Midi Note: 64
		349,    // Midi Note: 65
		370,    // Midi Note: 66
		392,    // Midi Note: 67
		415,    // Midi Note: 68
		440,    // Midi Note: 69
		466,    // Midi Note: 70
		494,    // Midi Note: 71
		523,    // Midi Note: 72
		554,    // Midi Note: 73
		587,    // Midi Note: 74
		622,    // Midi Note: 75
		659,    // Midi Note: 76
		698,    // Midi Note: 77
		740,    // Midi Note: 78
		784,    // Midi Note: 79
		831,    // Midi Note: 80
		880,    // Midi Note: 81
		932,    // Midi Note: 82
		988,    // Midi Note: 83
		1047,    // Midi Note: 84
		1109,    // Midi Note: 85
		1175,    // Midi Note: 86
		1245,    // Midi Note: 87
		1319,    // Midi Note: 88
		1397,    // Midi Note: 89
		1480,    // Midi Note: 90
		1568,    // Midi Note: 91
		1661,    // Midi Note: 92
		1760,    // Midi Note: 93
		1865,    // Midi Note: 94
		1976,    // Midi Note: 95
		2093,    // Midi Note: 96
		2217,    // Midi Note: 97
		2349,    // Midi Note: 98
		2489,    // Midi Note: 99
		2637,    // Midi Note: 100
		2794,    // Midi Note: 101
		2960,    // Midi Note: 102
		3136,    // Midi Note: 103
		3322,    // Midi Note: 104
		3520,    // Midi Note: 105
		3729,    // Midi Note: 106
		3951,    // Midi Note: 107
		4186,    // Midi Note: 108
		4435,    // Midi Note: 109
		4699,    // Midi Note: 110
		4978,    // Midi Note: 111
		5274,    // Midi Note: 112
		5588,    // Midi Note: 113
		5920,    // Midi Note: 114
		6272,    // Midi Note: 115
		6645,    // Midi Note: 116
		7040,    // Midi Note: 117
		7459,    // Midi Note: 118
		7902,    // Midi Note: 119
		8372,    // Midi Note: 120
		8870,    // Midi Note: 121
		9397,    // Midi Note: 122
		9956,    // Midi Note: 123
		10548,    // Midi Note: 124
		11175,    // Midi Note: 125
		11840,    // Midi Note: 126
		12544,    // Midi Note: 127
};



/* 

     /\       _| .  _    |  _  . |_ 
    /--\ |_| (_| | (_)   | | ) | |_ 
                                    
*/
void Audio_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

	
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 48;                            // 1MHz timer clock3
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 1000; 	// 1kHz
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

  HAL_TIM_PWM_Init(&htim3);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = AudioVolume ; // 
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);

}



void Audio_Play(uint16_t frequency)	
{
	TIM_OC_InitTypeDef sConfigOC;
	if (frequency>0) 
	{
		htim3.Init.Period = 1000000 / frequency; 	// set period value
		HAL_TIM_PWM_Init(&htim3);
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
		sConfigOC.Pulse = AudioVolume ; // 
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
    // start timer
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	}
	else
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
	}
}

/* convert MIDI note 0...127 to approx frequency in Hz */ 
uint16_t MIDI2Hz(uint8_t note)
{
	return ((note>=24) & (note<=127))	? MidiFrequencies[note-24] : 0;
}


void Audio_PlayMidiNote(uint8_t note)
{
	Audio_Play(MIDI2Hz(note));
}



void Audio_Volume(uint16_t vol)
{
	AudioVolume = vol;
}
