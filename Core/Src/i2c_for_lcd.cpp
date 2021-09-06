//
// LCDを使用するためのソースコード
//

// ヘッダファイルのインクルード
#include "i2c_for_lcd.h"

// LCDで使えるアイコン
const unsigned char ICON[14][2] =
{
	{0x00, 0x10},   // アンテナ
	{0x02, 0x10},   // 電話
	{0x04, 0x10},   // 無線
	{0x06, 0x10},   // ジャック
	{0x07, 0x10},   // △
	{0x07, 0x08},   // ▽
	{0x07, 0x18},   // △▽
	{0x09, 0x10},   // 鍵
	{0x0B, 0x10},   // ピン
	{0x0D, 0x02},   // 電池無し
	{0x0D, 0x12},   // 容量少
	{0x0D, 0x1A},   // 容量中
	{0x0D, 0x1E},   // 容量大
	{0x0F, 0x10},   // 丸
};

// 液晶へコマンド出力する関数
void lcd_cmd(uint8_t Data)
{
	uint8_t txBuffer[2] = {0x00,0x00};		// デバイスIDと送信データ、いづれも1Byte
	txBuffer[1] = Data;						// データを代入
	// HAL関数、I2Cでデータを送信
	HAL_I2C_Master_Transmit(&hi2c2, 0x7c, txBuffer, 0x02, 10);

	// データの内容がClearかHomeか
	if(((Data) == 0x01)||((Data)== 0x02))
	{
		for(int i = 7200; i > 0; i--)		// 7200カウントで時間つぶし
		{

		}
	}

	else
	{
		for(int i = 3600; i > 0; i--)		// 3600カウントで時間つぶし
		{

		}
	}

}

// 初期化関数
void lcd_init(void)
{
	HAL_Delay(100);
	lcd_cmd(0x38);      // 8bit 2line Normal mode
	lcd_cmd(0x39);      // 8bit 2line Extend mode
	lcd_cmd(0x14);      // OSC 183Hz BIAS 1/5
	// コントラスト設定
	lcd_cmd(0x70 + (CONTRAST & 0x0F));
	lcd_cmd(0x5C + (CONTRAST >> 4));

	if(CONTRAST == 0x18)	// 5V用か？
	{
		lcd_cmd(0x6A);      // Follower for 5.0V
	}
	else
	{
		lcd_cmd(0x6B);      // Follower for 3.3V
	}

	HAL_Delay(300);
	lcd_cmd(0x38);      // Set Normal mode
	lcd_cmd(0x01);      // Display On
	lcd_cmd(0x0C);      // Clear Display
}

// 液晶へ１文字表示データ出力する関数
void lcd_data(uint8_t Data)
{
	uint8_t txBuffer[2] = {0x40,0x00};
	txBuffer[1] = Data;
	HAL_I2C_Master_Transmit(&hi2c2, 0x7c, txBuffer, 0x02, 10);
}

// 文字列表示関数
void lcd_str(char* ptr)
{
	while(*ptr != 0)
	lcd_data(*ptr++);
}

// アイコン表示制御関数
void lcd_icon(uint8_t num, uint8_t onoff){
	lcd_cmd(0x39);                  // Extend mode
	lcd_cmd(0x40 | ICON[num][0]);   // アイコンアドレス指定
	if(onoff)
	lcd_data(ICON[num][1]);			// アイコンオンデータ
	else
	lcd_data(0x00);					// アイコンオフデータ
	lcd_cmd(0x38);                  // Normal mode
}

//全消去関数
void lcd_clear(){
	lcd_cmd(0x01);					// 全消去、カーソルはホーム位置に戻す
}

// 改行関数
void lcd_enter(void){
	lcd_cmd(0xC0);					// 改行
}



// int整数からASCII文字に変換し、文字列に代入
// intstring(数字文字数,intデータ,数字文字の始めの位置-1)
// 使用しないが、一応残しておく
/*
void intstring(char digit, int data, char *buffer)
{
	char i;
	buffer = buffer + digit;					// 最後の数字位置
	int data_unsigned;							// 符号無し整数

	if( data < 0)								// -か+で符号なし整数に変換
	{
		data_unsigned = ~data + 1;
	}
	else
	{
		data_unsigned = data;
	}
	for(i=digit; i>0; i--)						// 変換は下位から上位へ
	{
		buffer--;								// ポインタ1
		*buffer = (data_unsigned % 10) + '0';	// ASCIIへ
		data_unsigned = data_unsigned/10;		// 次の桁へ
	}
	if( data < 0)								// 負の数なら数字の先頭を-に
	{
		*buffer = '-';
	}

}
*/
