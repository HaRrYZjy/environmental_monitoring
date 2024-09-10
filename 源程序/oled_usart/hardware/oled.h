#ifndef OLED_H__
#define OLED_H__

#include "main.h"	//链接HAL库
/* BMP图片声明 
	图片格式为二位数组，下标分别对应图片的宽和高：
		BMP_xx[H/8][L];
*/
//2:x=0~15*8,y=0~3*16//1:x=0~20*6,y=0~7*8
#define line1_1 0
#define line2_1 1*8
#define line3_1 2*8
#define line4_1 3*8
#define line5_1 4*8
#define line6_1 5*8
#define line7_1 6*8
#define line8_1 7*8
#define line1_2 0
#define line2_2 1*16
#define line3_2 2*16
#define line4_2 3*16



extern const uint8_t BMP_Picture[64/8][64];


/* 设置坐标点的状态 */
typedef enum 
{
	SET_PIXEL = 0x01,
  RESET_PIXEL = 0x00, 
} PixelStatus;


/* 功能函数声明 */
//写数据，硬件IIC使用
void HAL_I2C_WriteByte(uint8_t addr,uint8_t data);
//写命令
void WriteCmd(uint8_t IIC_Command);
//写数据
void WriteDat(uint8_t IIC_Data);
//初始化OLED
void OLED_Init(void);
//开启电荷泵
void OLED_ON(void);
//关闭电荷泵
void OLED_OFF(void);
//刷新缓冲区数据到GDDRAM
void OLED_RefreshRAM(void);
//清除数据缓冲区OLED_RAM buffer
void OLED_ClearRAM(void);
//全屏填充
void OLED_FullyFill(uint8_t fill_Data);
//清屏
void OLED_FullyClear(void);
//设置坐标像素点数据
void OLED_SetPixel(int16_t x, int16_t y, uint8_t set_pixel);
//获得坐标像素点数据
PixelStatus OLED_GetPixel(int16_t x, int16_t y);

/* 显示指定字符和图片时需要手动刷新缓冲区到GDDRAM 
* function list: OLED_ShowStr\OLED_ShowCN\OLED_Show_MixedCH\OLED_DrawBMP
*/
//显示英文字符串//2:x=0~15*8,y=0~3*16//1:x=0~20*6,y=0~7*8
void OLED_ShowStr(int16_t x, int16_t y, uint8_t ch[], uint8_t TextSize);
//显示中文字符串
void OLED_ShowCN(int16_t x, int16_t y, uint8_t* ch);
//显示中英文混合文字
void OLED_ShowMixedCH(int16_t x, int16_t y, uint8_t* ch);
//显示图片
void OLED_DrawBMP(int16_t x0,int16_t y0,int16_t L,int16_t H,const uint8_t BMP[]);

//区域填充
void OLED_AreaFill(int16_t x0,int16_t y0,int16_t L,int16_t H, uint8_t fill_data);
//区域清除
void OLED_AreaClear(int16_t x0,int16_t y0,int16_t L,int16_t H);
//全屏切换显示
void OLED_FullyToggle(void);
//区域切换显示
void OLED_AreaToggle(int16_t x0,int16_t y0,int16_t L,int16_t H);
//全屏垂直滚动播放
void OLED_VerticalShift(void);
//全屏水平滚动播放
void OLED_HorizontalShift(uint8_t direction);
//全屏同时垂直和水平滚动播放
void OLED_VerticalAndHorizontalShift(uint8_t direction);
//屏幕内容取反显示
void OLED_DisplayMode(uint8_t mode);
//屏幕亮度调节
void OLED_IntensityControl(uint8_t intensity);


#endif



