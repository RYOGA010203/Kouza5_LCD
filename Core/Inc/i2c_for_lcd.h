//
// LCDを使用するためのヘッダファイル
//

#include "main.h"

extern I2C_HandleTypeDef hi2c2;		//I2Cで使用する構造体、このファイルの外部で宣言されている

//#define CONTRAST   0x18    // for 5.0V
#define CONTRAST   0x30    // for 3.3V

//HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)

// 液晶へコマンド出力
void lcd_cmd(uint8_t Data);

// 初期化関数
void lcd_init(void);

// 液晶へ１文字表示データ出力
void lcd_data(uint8_t Data);

// 文字列表示関数
void lcd_str(char* ptr);

// アイコン表示制御関数
void lcd_icon(uint8_t num, uint8_t onoff);

// 全消去関数
void lcd_clear();

// 改行関数
void lcd_enter(void);

// int整数からASCII文字に変換し、文字列に代入
// intstring(数字文字数,intデータ,数字文字の始めの位置-1)
// 使わないが、一応残しておく
/*
void intstring(char digit, int data, char *buffer);
*/
