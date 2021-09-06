
#include "main.h"
#include "i2c_for_lcd.h"
//#include <stdio.h>	// sprintfを使わない限り必要ない

extern char Msg1[16];
extern char Msg2[16];

// タイマ割り込みハンドラ。
// タイマ3割り込みを有効にすると、一定時間ごとに以下が実行される
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		lcd_clear();		// LCD全消去
		lcd_str(Msg1);		// Msg1をLCDに表示

		lcd_enter();		// LCD改行
		lcd_str(Msg2);		// Msg2をLCDに表示
	}
}
