
#include "main.h"
#include <stdio.h>	// C言語でおなじみのライブラリ。sprintfを使うなら必要
#include "i2c_for_lcd.h"

// タイマ3割り込みにより、格納された文字は自動で表示される
char Msg1[16];	// LCDの１行目の文字列。一定時間ごとにMsg1の中身が表示される
char Msg2[16];	// LCDの２行目の文字列。一致時間ごとにMsg2の中身が表示される

// 外部宣言の関数などを参照する
extern "C"
{
	TIM_HandleTypeDef htim3;
}

// メイン関数
void main_cpp(void)
{
	lcd_init();		// LCD初期化

	HAL_TIM_Base_Start_IT(&htim3);		// タイマ3割り込みスタート

	while(1)
	{
		static int a = 0;
		static int b = 0;

		sprintf(Msg1,"Value1:%d",a);	// 文字列Msg1に文を代入
		sprintf(Msg2,"Value2:%d",b);	// 文字列Msg2に文を代入

		a = a + 1;		// aを1増やす
		b = b + 10;		// bを10増やす

		HAL_Delay(1000);				// 1000ms待機
	}

}
