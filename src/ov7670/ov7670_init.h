#ifndef OV7670_INIT_H
#define OV7670_INIT_H
#include <stdint.h>

// https://blog.csdn.net/zdzh1/article/details/21739589
const uint8_t OV7670_Reg1[][2]=
{
  {0x12, 0x80},
  //Frame Rate Adjustment for 24Mhz input clock
  //30fps PCLK=24MHz
  {0x11, 0x80},//软件应用手册上设置的是0x80，例程设置的是0x00
  {0x6b, 0x0a},//PLL控制,软件应用手册上设置的是0x0a,例程设置的是0x40,将PLL调高的话就会产生花屏
  {0x2a, 0x00},
  {0x2b, 0x00},
  {0x92, 0x00},
  {0x93, 0x00},
  {0x3b, 0x0a},

  //Output format
  {0x12, 0x14},//QVGA(320*240)、RGB
  //{0x12, 0x0},//VGA(640*480)、RGB
  //RGB555/565 option(must set COM7[2] = 1 and COM7[0] = 0)
  //{0x40, 0x10},//RGB565,effective only when RGB444[1] is low
  {0x40, 0xd0}, // 0b11010000 11: Output range: [00] to [FF], 01: RGB 565, effective only when RGB444[1] is low
  {0x8c, 0x00},

  //Special effects - 特效 
  //normal
  {0x3a, 0x00}, //0x04
  {0x67, 0x80},
  {0x68, 0x80},

  //Mirror/VFlip Enable - 水平镜像/竖直翻转使能
  {0x1e, 0x37},//修改配置值将产生图像显示上下或左右颠倒

  //Banding Filter Setting for 24Mhz Input Clock - 条纹滤波器
  //30fps for 60Hz light frequency
  {0x13, 0xe7},//banding filer enable
  {0x9d, 0x98},//50Hz banding filer
  {0x9e, 0x7f},//60Hz banding filer
  {0xa5, 0x02},//3 step for 50Hz
  {0xab, 0x03},//4 step for 60Hz
  {0x3b, 0x02},//select 60Hz banding filer

  //Simple White Balance - 白平衡
  {0x13, 0xe7},//AWB、AGC、AGC Enable and ...
  {0x6f, 0x9f},//simple AWB

  //AWBC - 自动白平衡控制(Automatic white balance control) 
  {0x43, 0x14},//用户手册里这些寄存器的值都是保留(Reserved),不用设置的呀？
  {0x44, 0xf0},
  {0x45, 0x34},        
  {0x46, 0x58},
  {0x47, 0x28},
  {0x48, 0x3a},

  //AWB Control
  {0x59, 0x88},//用户手册连寄存器都是保留，初始值都没提供
  {0x5a, 0x88},        
  {0x5b, 0x44},
  {0x5c, 0x67},
  {0x5d, 0x49},
  {0x5e, 0x0e},

  //AWB Control
  {0x6c, 0x0a},
  {0x6d, 0x55},       
  {0x6e, 0x11},
  {0x6f, 0x9f},
  
//   AGC/AEC - Automatic Gain Control自动增益补偿/Automatic exposure Control自动曝光控制
//   {0x00, 0x00},
//   {0x14, 0x20},
//   {0x24, 0x75},
//   {0x25, 0x63},
//   {0x26, 0xA5},

  //AEC algorithm selection - AEC公式选择    
  {0xaa, 0x94},//基于平均值的AEC算法Average-based AEC algorithm/基于直方图的AEC算法Histogram-based AEC algorithm  

  //基于直方图的AGC/AEC的控制
  {0x9f, 0x78},
  {0xa0, 0x68},       
  {0xa6, 0xdf},
  {0xa7, 0xdf},
  {0xa8, 0xf0},
  {0xa9, 0x90},

  //Fix Gain Control - 固定增益控制    
  {0x69, 0x5d},//Fix gain for Gr channel/for Gb channel/for R channel/for B channel

  //Color saturation 颜色饱和度 + 0
  {0x4f, 0x80},
  {0x50, 0x80},
  {0x51, 0x00},
  {0x52, 0x22},
  {0x53, 0x5e},
  {0x54, 0x80},
  {0x58, 0x9e},

  //Brightness - 亮度 + 0
  //{0x55, 0x00},

  //Contrast - 对比度 + 0
  {0x56, 0x40},

  //Gamma Curve - 伽马曲线
  {0x7a, 0x20},
  {0x7b, 0x1c},
  {0x7c, 0x28},        
  {0x7d, 0x3c},
  {0x7e, 0x55},
  {0x7f, 0x68},
  {0x80, 0x76},
  {0x81, 0x80},        
  {0x82, 0x88},
  {0x83, 0x8f},
  {0x84, 0x96},
  {0x85, 0xa3},
  {0x86, 0xaf},        
  {0x87, 0xc4},
  {0x88, 0xd7},
  {0x89, 0xe8},

  //Matrix Coefficient - 色彩矩阵系数            
  {0x4f, 0x80},
  {0x50, 0x80},
  {0x51, 0x00},
  {0x52, 0x22},
  {0x53, 0x5e},
  {0x54, 0x80},

  //Lens Correction Option - 镜头补偿选项
  {0x62, 0x00},       
  {0x63, 0x00},
  {0x64, 0x04},
  {0x65, 0x20},        
  {0x66, 0x05},
  {0x94, 0x04},//effective only when LCC5[2] is high
  {0x95, 0x08},//effective only when LCC5[2] is high


  //注释这些配置的话，就倾斜显示，并显示多块，这到底是控制什么的？跟时序图有关？
  {0x17, 0x16},//行频Horizontal Frame开始高八位(低三位在HREF[2：0])       
  {0x18, 0x04},//行频Horizontal Frame结束高八位(低三位在HREF[5：3])
  {0x19, 0x02},//场频Vertical Frame开始高八位(低二位在VREF[1：0])
  {0x1a, 0x7b},//场频Vertical Frame结束高八位(低二位在VREF[3：2])
  {0x32, 0x80},//HREF
  {0x03, 0x06},//VREF

  //注释这个配置的话，就显示花屏了
  {0x15, 0x02},//配置PCLK、HREF、VSYNC相关

  //Automatic black Level Compensation - 自动黑电平校正
  {0xb0, 0x84},//调试时注释这项配置时，颜色显示不正常了，红色练绿色，绿色变红色，但用户手册对这寄存器是保留RSVD
  //{0xb1, 0x0c},
  //{0xb2, 0x0e},      
  //{0xb3, 0x82},
  //{0xb8, 0x0a},

  //SCALING_xx寄存器
  {0x70, 0x00},
  {0x71, 0x00},
  {0x72, 0x11},
  {0x73, 0x08},
  {0x3e, 0x00},

  //ADC
  {0x37, 0x1d},//ADC控制ADC Control
  {0x38, 0x71},//ADC和模拟共模控制ADC and Analog Common Mode Control
  {0x39, 0x2a},//ADC偏移控制ADC Offset Control

  //零杂的寄存器
  {0x92, 0x00},//空行低八位Dummy Line low 8 bits
  {0xa2, 0x02},//像素时钟延时
  {0x0c, 0x0c},
  {0x10, 0x00},
  {0x0d, 0x01},
  {0x0f, 0x4b},
  {0x3c, 0x78},
  {0x74, 0x19},

  //用户手册里这几个寄存器都是保留RSVD
  {0x0e, 0x61},
  {0x16, 0x02},
  {0x21, 0x02},
  {0x22, 0x91},
  {0x29, 0x07},
  {0x33, 0x0b},
  {0x35, 0x0b},
  {0x4d, 0x40},
  {0x4e, 0x20},
  {0x8d, 0x4f},        
  {0x8e, 0x00},
  {0x8f, 0x00},
  {0x90, 0x00},
  {0x91, 0x00},
  {0x96, 0x00},
  {0x9a, 0x80},     
  {0xff, 0xff}                       
};

const uint8_t ov7670_qqvga_yuv422[][2] = {
{0x11,0x01},{0x12,0x00},{0x0c,0x04},{0x3e,0x1a},
{0x70,0x3a},{0x71,0x35},{0x72,0x22},{0x73,0xf2},{0xa2,0x02},
// some extra settings
// {0x0c,0x04|0x40},    //Output data MSB and LSB swap
// {0x3a,0x00|0x40}, //tslb  bit[3]
//{0x3d,0x80}, //com13 bit[0]
{0x41,0x18},//{0x42,0x08}
{0xff,0xff},//{0x42,0x08}

};

const uint8_t ov7670_qvga_yuv422[][2] = 
{
	/*	配置为RGB565 QVGA */
	//  {0x3a, 0x04},
	//	{0x40, 0x10},
	//	{0x12, 0x14},  以上是正点原子关于RGB565的配置，如果要配置为YUV422则应将其注释掉
/*	配置为QVGA YUV422 */
	{0x12, 0x10},   //QVGA YUV422
	{0x3d, 0x80},   //输出格式为YUYV
 
	{0x32, 0x80},
	{0x17, 0x16},         
	{0x18, 0x04},//5
	{0x19, 0x02},
	{0x1a, 0x7a},//0x7a,
	{0x03, 0x0a},//0x0a,


	{0x0c, 0x0c},
	{0x15, 0x00},
	{0x3e, 0x00},//10
	{0x70, 0x00},
	{0x71, 0x01},
	{0x72, 0x11},
	{0x73, 0x09},//
				
	{0xa2, 0x02},//15
	{0x11, 0x00},
	{0x7a, 0x20},
	{0x7b, 0x1c},
	{0x7c, 0x28},
				
	{0x7d, 0x3c},//20
	{0x7e, 0x55},
	{0x7f, 0x68},
	{0x80, 0x76},
	{0x81, 0x80},
				
	{0x82, 0x88},
	{0x83, 0x8f},
	{0x84, 0x96},
	{0x85, 0xa3},
	{0x86, 0xaf},
				
	{0x87, 0xc4},//30
	{0x88, 0xd7},
	{0x89, 0xe8},
	{0x13, 0xe0},
	//{0x00, 0x00},//AGC
				
	{0x10, 0x00},
	{0x0d, 0x00}, 
	{0x14, 0x20},//0x38, limit the max gain
	{0xa5, 0x05},
	{0xab, 0x07},
				
	{0x24, 0x75},//40
	{0x25, 0x63},
	{0x26, 0xA5},
	{0x9f, 0x78},
	{0xa0, 0x68},
				
	{0xa1, 0x03},//0x0b,
	{0xa6, 0xdf},//0xd8,
	{0xa7, 0xdf},//0xd8,
	{0xa8, 0xf0},
	{0xa9, 0x90},
				
	{0xaa, 0x94},//50
	{0x13, 0xe5}, //0xe5 add at 20240815
	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},
				
	{0x1e, 0x27},
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},
				
	{0x35, 0x0b},//60
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},
	{0x3c, 0x78},
				
	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x5d},
	{0x6b, 0x40},//PLL*4=48Mhz
	{0x74, 0x19},
	{0x8d, 0x4f},
				
	{0x8e, 0x00},//70
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x92, 0x00},//0x19,//0x66
				
	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},
				
	{0xb3, 0x82},//80
	{0xb8, 0x0a},
	{0x43, 0x14},
	{0x44, 0xf0},
	{0x45, 0x34},
				
	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},
				
	{0x5b, 0x44},//90
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x64, 0x04},
	{0x65, 0x20},
				
	{0x66, 0x05},
	{0x94, 0x04},
	{0x95, 0x08},
	{0x6c, 0x0a},
	{0x6d, 0x55},
				
				
	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},
				
	//{0x54, 0x40},//110
				
				
	{0x09, 0x03},//

	{0x6e, 0x11},//100
	{0x6f, 0x9f},//0x9e for advance AWB
	{0x55, 0x00},//
	{0x56, 0xf0},//
	{0x57, 0x80},//0x40,  change according to Jim's request
  {0xff, 0xff},
};

const uint8_t ov7670_init_reg_tbl[][2]=
{
    {0x3a, 0x04},
    {0x40, 0x10},
    {0x12, 0x14},
    {0x32, 0x80},
    {0x17, 0x17},
    {0x18, 0x05},
    {0x19, 0x02},
    {0x1a, 0x7b},//0x7a,
    {0x03, 0x0a},//0x0a,
    {0x0c, 0x0c},
    {0x3e, 0x00},//
    {0x70, 0x00},
    {0x71, 0x01},
    //{0x71, 0x80}, //0x80测试彩条
    {0x72, 0x11},
    {0x73, 0x09},//
    {0xa2, 0x02},
    {0x11, 0x00},
    {0x7a, 0x20},
    {0x7b, 0x1c},
    {0x7c, 0x28},
    {0x7d, 0x3c},
    {0x7e, 0x55},
    {0x7f, 0x68},
    {0x80, 0x76},
    {0x81, 0x80},
    {0x82, 0x88},
    {0x83, 0x8f},
    {0x84, 0x96},
    {0x85, 0xa3},
    {0x86, 0xaf},
    {0x87, 0xc4},
    {0x88, 0xd7},
    {0x89, 0xe8},
    {0x13, 0xe0},
    //{0x00, 0x00},
    {0x10, 0x00},
    {0x0d, 0x00},
    {0x14, 0x38},
    {0xa5, 0x05},
    {0xab, 0x07},
    {0x24, 0x75},
    {0x25, 0x63},
    {0x26, 0xA5},
    {0x9f, 0x78},
    {0xa0, 0x68},
    {0xa1, 0x03},//0x0b,
    {0xa6, 0xdf},//0xd8,
    {0xa7, 0xdf},//0xd8,
    {0xa8, 0xf0},
    {0xa9, 0x90},
    {0xaa, 0x94},
    {0x13, 0xe5},
    {0x0e, 0x61},
    {0x0f, 0x4b},
    {0x16, 0x02},
    {0x1e, 0x27},//0x07,
    {0x21, 0x02},
    {0x22, 0x91},
    {0x29, 0x07},
    {0x33, 0x0b},
    {0x35, 0x0b},
    {0x37, 0x1d},
    {0x38, 0x71},
    {0x39, 0x2a},
    {0x3c, 0x78},
    {0x4d, 0x40},
    {0x4e, 0x20},
    {0x69, 0x5d},
    {0x6b, 0x40},//PLL
    {0x74, 0x19},
    {0x8d, 0x4f},
    {0x8e, 0x00},
    {0x8f, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    {0x92, 0x00},//0x19,//0x66
    {0x96, 0x00},
    {0x9a, 0x80},
    {0xb0, 0x84},
    {0xb1, 0x0c},
    {0xb2, 0x0e},
    {0xb3, 0x82},
    {0xb8, 0x0a},
    {0x43, 0x14},
    {0x44, 0xf0},
    {0x45, 0x34},
    {0x46, 0x58},
    {0x47, 0x28},
    {0x48, 0x3a},
    {0x59, 0x88},
    {0x5a, 0x88},
    {0x5b, 0x44},
    {0x5c, 0x67},
    {0x5d, 0x49},
    {0x5e, 0x0e},
    {0x64, 0x04},
    {0x65, 0x20},
    {0x66, 0x05},
    {0x94, 0x04},
    {0x95, 0x08},
    {0x6c, 0x0a},
    {0x6d, 0x55},
    {0x6e, 0x11},
    {0x6f, 0x9f},
    {0x6a, 0x40},
    //{0x01, 0x60},
    //{0x02, 0x60},
    {0x13, 0xe7},
    {0x15, 0x00},
    {0x4f, 0x80},
    {0x50, 0x80},
    {0x51, 0x00},
    {0x52, 0x22},
    {0x53, 0x5e},
    {0x54, 0x80},
    {0x55, 0x00},//亮度
    {0x56, 0x60},//对比度
    {0x57, 0x90},
    {0x58, 0x9e},
    {0x41, 0x08},
    {0x3f, 0x05},//边缘增强调整
    {0x75, 0x05},
    {0x76, 0xe1},
    {0x4c, 0x0F},//噪声抑制强度
    {0x77, 0x0a},
    {0x3d, 0xc2},    //0xc0,
    {0x4b, 0x09},
    {0xc9, 0xc8},
    {0x41, 0x38},

    {0x34, 0x11},
    {0x3b, 0x02},//0x00,//0x02,
    {0xa4, 0x89},//0x88,
    {0x96, 0x00},
    {0x97, 0x30},
    {0x98, 0x20},
    {0x99, 0x30},
    {0x9a, 0x84},
    {0x9b, 0x29},
    {0x9c, 0x03},
    {0x9d, 0x4c},
    {0x9e, 0x3f},
    {0x78, 0x04},
    {0x79, 0x01},
    {0xc8, 0xf0},
    {0x79, 0x0f},
    {0xc8, 0x00},
    {0x79, 0x10},
    {0xc8, 0x7e},
    {0x79, 0x0a},
    {0xc8, 0x80},
    {0x79, 0x0b},
    {0xc8, 0x01},
    {0x79, 0x0c},
    {0xc8, 0x0f},
    {0x79, 0x0d},
    {0xc8, 0x20},
    {0x79, 0x09},
    {0xc8, 0x80},
    {0x79, 0x02},
    {0xc8, 0xc0},
    {0x79, 0x03},
    {0xc8, 0x40},
    {0x79, 0x05},
    {0xc8, 0x30},
    {0x69, 0xaa},//
    {0x09, 0x00},
    {0x3b, 0x42},
    {0x2d, 0x01},
    {0xff, 0xff}
};

// Not working
// reference to https://github.com/erikandre/stm32-ov7670/blob/master/src/OV7670_control.c
const uint8_t OV7670_reg2[][2] = { { 0x12, 0x80 },

// Image format
		{ 0x12, 0x8 },		// 0x14 = QVGA size, RGB mode; 0x8 = QCIF, YUV, 0xc = QCIF (RGB)
		{ 0xc, 0x8 }, //
		{ 0x11, 0b1000000 }, //

		{ 0xb0, 0x84 },		//Color mode (Not documented??)

		// Hardware window
		{ 0x11, 0x01 },		//PCLK settings, 15fps
		{ 0x32, 0x80 },		//HREF
		{ 0x17, 0x17 },		//HSTART
		{ 0x18, 0x05 },		//HSTOP
		{ 0x03, 0x0a },		//VREF
		{ 0x19, 0x02 },		//VSTART
		{ 0x1a, 0x7a },		//VSTOP

		// Scalling numbers
		{ 0x70, 0x3a },		//X_SCALING
		{ 0x71, 0x35 },		//Y_SCALING
		{ 0x72, 0x11 },		//DCW_SCALING
		{ 0x73, 0xf0 },		//PCLK_DIV_SCALING
		{ 0xa2, 0x02 },		//PCLK_DELAY_SCALING

		// Matrix coefficients
		{ 0x4f, 0x80 }, //
		{ 0x50, 0x80 }, //
		{ 0x51, 0x00 }, //
		{ 0x52, 0x22 }, //
		{ 0x53, 0x5e }, //
		{ 0x54, 0x80 }, //
		{ 0x58, 0x9e },

		// Gamma curve values
		{ 0x7a, 0x20 }, //
		{ 0x7b, 0x10 }, //
		{ 0x7c, 0x1e }, //
		{ 0x7d, 0x35 }, //
		{ 0x7e, 0x5a }, //
		{ 0x7f, 0x69 }, //
		{ 0x80, 0x76 }, //
		{ 0x81, 0x80 }, //
		{ 0x82, 0x88 }, //
		{ 0x83, 0x8f }, //
		{ 0x84, 0x96 }, //
		{ 0x85, 0xa3 }, //
		{ 0x86, 0xaf }, //
		{ 0x87, 0xc4 }, //
		{ 0x88, 0xd7 }, //
		{ 0x89, 0xe8 },

		// AGC and AEC parameters
		{ 0xa5, 0x05 }, //
		{ 0xab, 0x07 }, //
		{ 0x24, 0x95 }, //
		{ 0x25, 0x33 }, //
		{ 0x26, 0xe3 }, //
		{ 0x9f, 0x78 }, //
		{ 0xa0, 0x68 }, //
		{ 0xa1, 0x03 }, //
		{ 0xa6, 0xd8 }, //
		{ 0xa7, 0xd8 }, //
		{ 0xa8, 0xf0 }, //
		{ 0xa9, 0x90 }, //
		{ 0xaa, 0x94 }, //
		{ 0x10, 0x00 },

		// AWB parameters
		{ 0x43, 0x0a }, //
		{ 0x44, 0xf0 }, //
		{ 0x45, 0x34 }, //
		{ 0x46, 0x58 }, //
		{ 0x47, 0x28 }, //
		{ 0x48, 0x3a }, //
		{ 0x59, 0x88 }, //
		{ 0x5a, 0x88 }, //
		{ 0x5b, 0x44 }, //
		{ 0x5c, 0x67 }, //
		{ 0x5d, 0x49 }, //
		{ 0x5e, 0x0e }, //
		{ 0x6c, 0x0a }, //
		{ 0x6d, 0x55 }, //
		{ 0x6e, 0x11 }, //
		{ 0x6f, 0x9f }, //
		{ 0x6a, 0x40 }, //
		{ 0x01, 0x40 }, //
		{ 0x02, 0x60 }, //
		{ 0x13, 0xe7 },

		// Additional parameters
		{ 0x34, 0x11 }, //
		{ 0x3f, 0x00 }, //
		{ 0x75, 0x05 }, //
		{ 0x76, 0xe1 }, //
		{ 0x4c, 0x00 }, //
		{ 0x77, 0x01 }, //
		{ 0xb8, 0x0a }, //
		{ 0x41, 0x18 }, //
		{ 0x3b, 0x12 }, //
		{ 0xa4, 0x88 }, //
		{ 0x96, 0x00 }, //
		{ 0x97, 0x30 }, //
		{ 0x98, 0x20 }, //
		{ 0x99, 0x30 }, //
		{ 0x9a, 0x84 }, //
		{ 0x9b, 0x29 }, //
		{ 0x9c, 0x03 }, //
		{ 0x9d, 0x4c }, //
		{ 0x9e, 0x3f }, //
		{ 0x78, 0x04 }, //
		{ 0x0e, 0x61 }, //
		{ 0x0f, 0x4b }, //
		{ 0x16, 0x02 }, //
		{ 0x1e, 0x00 }, //
		{ 0x21, 0x02 }, //
		{ 0x22, 0x91 }, //
		{ 0x29, 0x07 }, //
		{ 0x33, 0x0b }, //
		{ 0x35, 0x0b }, //
		{ 0x37, 0x1d }, //
		{ 0x38, 0x71 }, //
		{ 0x39, 0x2a }, //
		{ 0x3c, 0x78 }, //
		{ 0x4d, 0x40 }, //
		{ 0x4e, 0x20 }, //
		{ 0x69, 0x00 }, //
		{ 0x6b, 0x3a }, //
		{ 0x74, 0x10 }, //
		{ 0x8d, 0x4f }, //
		{ 0x8e, 0x00 }, //
		{ 0x8f, 0x00 }, //
		{ 0x90, 0x00 }, //
		{ 0x91, 0x00 }, //
		{ 0x96, 0x00 }, //
		{ 0x9a, 0x00 }, //
		{ 0xb1, 0x0c }, //
		{ 0xb2, 0x0e }, //
		{ 0xb3, 0x82 }, //
		{ 0x4b, 0x01 },
    {0xff, 0xff}
     };



// reference to https://github.com/usedbytes/camera-pico-ov7670/blob/main/include/camera/ov7670.h

/** Supported sizes (VGA division factor) for OV7670_set_size() */
typedef enum {
  OV7670_SIZE_DIV1 = 0, ///< 640 x 480
  OV7670_SIZE_DIV2,     ///< 320 x 240
  OV7670_SIZE_DIV4,     ///< 160 x 120
  OV7670_SIZE_DIV8,     ///< 80 x 60
  OV7670_SIZE_DIV16,    ///< 40 x 30
} OV7670_size;

#define OV7670_REG_GAIN 0x00               //< AGC gain bits 7:0 (9:8 in VREF)
#define OV7670_REG_BLUE 0x01               //< AWB blue channel gain
#define OV7670_REG_RED 0x02                //< AWB red channel gain
#define OV7670_REG_VREF 0x03               //< Vert frame control bits
#define OV7670_REG_COM1 0x04               //< Common control 1
#define OV7670_COM1_R656 0x40              //< COM1 enable R656 format
#define OV7670_REG_BAVE 0x05               //< U/B average level
#define OV7670_REG_GbAVE 0x06              //< Y/Gb average level
#define OV7670_REG_AECHH 0x07              //< Exposure value - AEC 15:10 bits
#define OV7670_REG_RAVE 0x08               //< V/R average level
#define OV7670_REG_COM2 0x09               //< Common control 2
#define OV7670_COM2_SSLEEP 0x10            //< COM2 soft sleep mode
#define OV7670_REG_PID 0x0A                //< Product ID MSB (read-only)
#define OV7670_REG_VER 0x0B                //< Product ID LSB (read-only)
#define OV7670_REG_COM3 0x0C               //< Common control 3
#define OV7670_COM3_SWAP 0x40              //< COM3 output data MSB/LSB swap
#define OV7670_COM3_SCALEEN 0x08           //< COM3 scale enable
#define OV7670_COM3_DCWEN 0x04             //< COM3 DCW enable
#define OV7670_REG_COM4 0x0D               //< Common control 4
#define OV7670_REG_COM5 0x0E               //< Common control 5
#define OV7670_REG_COM6 0x0F               //< Common control 6
#define OV7670_REG_AECH 0x10               //< Exposure value 9:2
#define OV7670_REG_CLKRC 0x11              //< Internal clock
#define OV7670_CLK_EXT 0x40                //< CLKRC Use ext clock directly
#define OV7670_CLK_SCALE 0x3F              //< CLKRC Int clock prescale mask
#define OV7670_REG_COM7 0x12               //< Common control 7
#define OV7670_COM7_RESET 0x80             //< COM7 SCCB register reset
#define OV7670_COM7_SIZE_MASK 0x38         //< COM7 output size mask
#define OV7670_COM7_PIXEL_MASK 0x05        //< COM7 output pixel format mask
#define OV7670_COM7_SIZE_VGA 0x00          //< COM7 output size VGA
#define OV7670_COM7_SIZE_CIF 0x20          //< COM7 output size CIF
#define OV7670_COM7_SIZE_QVGA 0x10         //< COM7 output size QVGA
#define OV7670_COM7_SIZE_QCIF 0x08         //< COM7 output size QCIF
#define OV7670_COM7_RGB 0x04               //< COM7 pixel format RGB
#define OV7670_COM7_YUV 0x00               //< COM7 pixel format YUV
#define OV7670_COM7_BAYER 0x01             //< COM7 pixel format Bayer RAW
#define OV7670_COM7_PBAYER 0x05            //< COM7 pixel fmt proc Bayer RAW
#define OV7670_COM7_COLORBAR 0x02          //< COM7 color bar enable
#define OV7670_REG_COM8 0x13               //< Common control 8
#define OV7670_COM8_FASTAEC 0x80           //< COM8 Enable fast AGC/AEC algo,
#define OV7670_COM8_AECSTEP 0x40           //< COM8 AEC step size unlimited
#define OV7670_COM8_BANDING 0x20           //< COM8 Banding filter enable
#define OV7670_COM8_AGC 0x04               //< COM8 AGC (auto gain) enable
#define OV7670_COM8_AWB 0x02               //< COM8 AWB (auto white balance)
#define OV7670_COM8_AEC 0x01               //< COM8 AEC (auto exposure) enable
#define OV7670_REG_COM9 0x14               //< Common control 9 - max AGC value
#define OV7670_REG_COM10 0x15              //< Common control 10
#define OV7670_COM10_HSYNC 0x40            //< COM10 HREF changes to HSYNC
#define OV7670_COM10_PCLK_HB 0x20          //< COM10 Suppress PCLK on hblank
#define OV7670_COM10_HREF_REV 0x08         //< COM10 HREF reverse
#define OV7670_COM10_VS_EDGE 0x04          //< COM10 VSYNC chg on PCLK rising
#define OV7670_COM10_VS_NEG 0x02           //< COM10 VSYNC negative
#define OV7670_COM10_HS_NEG 0x01           //< COM10 HSYNC negative
#define OV7670_REG_HSTART 0x17             //< Horiz frame start high bits
#define OV7670_REG_HSTOP 0x18              //< Horiz frame end high bits
#define OV7670_REG_VSTART 0x19             //< Vert frame start high bits
#define OV7670_REG_VSTOP 0x1A              //< Vert frame end high bits
#define OV7670_REG_PSHFT 0x1B              //< Pixel delay select
#define OV7670_REG_MIDH 0x1C               //< Manufacturer ID high byte
#define OV7670_REG_MIDL 0x1D               //< Manufacturer ID low byte
#define OV7670_REG_MVFP 0x1E               //< Mirror / vert-flip enable
#define OV7670_MVFP_MIRROR 0x20            //< MVFP Mirror image
#define OV7670_MVFP_VFLIP 0x10             //< MVFP Vertical flip
#define OV7670_REG_LAEC 0x1F               //< Reserved
#define OV7670_REG_ADCCTR0 0x20            //< ADC control
#define OV7670_REG_ADCCTR1 0x21            //< Reserved
#define OV7670_REG_ADCCTR2 0x22            //< Reserved
#define OV7670_REG_ADCCTR3 0x23            //< Reserved
#define OV7670_REG_AEW 0x24                //< AGC/AEC upper limit
#define OV7670_REG_AEB 0x25                //< AGC/AEC lower limit
#define OV7670_REG_VPT 0x26                //< AGC/AEC fast mode op region
#define OV7670_REG_BBIAS 0x27              //< B channel signal output bias
#define OV7670_REG_GbBIAS 0x28             //< Gb channel signal output bias
#define OV7670_REG_EXHCH 0x2A              //< Dummy pixel insert MSB
#define OV7670_REG_EXHCL 0x2B              //< Dummy pixel insert LSB
#define OV7670_REG_RBIAS 0x2C              //< R channel signal output bias
#define OV7670_REG_ADVFL 0x2D              //< Insert dummy lines MSB
#define OV7670_REG_ADVFH 0x2E              //< Insert dummy lines LSB
#define OV7670_REG_YAVE 0x2F               //< Y/G channel average value
#define OV7670_REG_HSYST 0x30              //< HSYNC rising edge delay
#define OV7670_REG_HSYEN 0x31              //< HSYNC falling edge delay
#define OV7670_REG_HREF 0x32               //< HREF control
#define OV7670_REG_CHLF 0x33               //< Array current control
#define OV7670_REG_ARBLM 0x34              //< Array ref control - reserved
#define OV7670_REG_ADC 0x37                //< ADC control - reserved
#define OV7670_REG_ACOM 0x38               //< ADC & analog common - reserved
#define OV7670_REG_OFON 0x39               //< ADC offset control - reserved
#define OV7670_REG_TSLB 0x3A               //< Line buffer test option
#define OV7670_TSLB_NEG 0x20               //< TSLB Negative image enable
#define OV7670_TSLB_YLAST 0x04             //< TSLB UYVY or VYUY, see COM13
#define OV7670_TSLB_YFRST 0x00             //< TSLB YUYV or YVYU, see COM13
#define OV7670_TSLB_AOW 0x01               //< TSLB Auto output window
#define OV7670_REG_COM11 0x3B              //< Common control 11
#define OV7670_COM11_NIGHT 0x80            //< COM11 Night mode
#define OV7670_COM11_NMFR 0x60             //< COM11 Night mode frame rate mask
#define OV7670_COM11_HZAUTO 0x10           //< COM11 Auto detect 50/60 Hz
#define OV7670_COM11_BAND 0x08             //< COM11 Banding filter val select
#define OV7670_COM11_EXP 0x02              //< COM11 Exposure timing control
#define OV7670_REG_COM12 0x3C              //< Common control 12
#define OV7670_COM12_HREF 0x80             //< COM12 Always has HREF
#define OV7670_REG_COM13 0x3D              //< Common control 13
#define OV7670_COM13_GAMMA 0x80            //< COM13 Gamma enable
#define OV7670_COM13_UVSAT 0x40            //< COM13 UV saturation auto adj
#define OV7670_COM13_UVSWAP 0x01           //< COM13 UV swap, use w TSLB[3]
#define OV7670_REG_COM14 0x3E              //< Common control 14
#define OV7670_COM14_DCWEN 0x10            //< COM14 DCW & scaling PCLK enable
#define OV7670_REG_EDGE 0x3F               //< Edge enhancement adjustment
#define OV7670_REG_COM15 0x40              //< Common control 15
#define OV7670_COM15_RMASK 0xC0            //< COM15 Output range mask
#define OV7670_COM15_R10F0 0x00            //< COM15 Output range 10 to F0
#define OV7670_COM15_R01FE 0x80            //< COM15              01 to FE
#define OV7670_COM15_R00FF 0xC0            //< COM15              00 to FF
#define OV7670_COM15_RGBMASK 0x30          //< COM15 RGB 555/565 option mask
#define OV7670_COM15_RGB 0x00              //< COM15 Normal RGB out
#define OV7670_COM15_RGB565 0x10           //< COM15 RGB 565 output
#define OV7670_COM15_RGB555 0x30           //< COM15 RGB 555 output
#define OV7670_REG_COM16 0x41              //< Common control 16
#define OV7670_COM16_AWBGAIN 0x08          //< COM16 AWB gain enable
#define OV7670_REG_COM17 0x42              //< Common control 17
#define OV7670_COM17_AECWIN 0xC0           //< COM17 AEC window must match COM4
#define OV7670_COM17_CBAR 0x08             //< COM17 DSP Color bar enable
#define OV7670_REG_AWBC1 0x43              //< Reserved
#define OV7670_REG_AWBC2 0x44              //< Reserved
#define OV7670_REG_AWBC3 0x45              //< Reserved
#define OV7670_REG_AWBC4 0x46              //< Reserved
#define OV7670_REG_AWBC5 0x47              //< Reserved
#define OV7670_REG_AWBC6 0x48              //< Reserved
#define OV7670_REG_REG4B 0x4B              //< UV average enable
#define OV7670_REG_DNSTH 0x4C              //< De-noise strength
#define OV7670_REG_MTX1 0x4F               //< Matrix coefficient 1
#define OV7670_REG_MTX2 0x50               //< Matrix coefficient 2
#define OV7670_REG_MTX3 0x51               //< Matrix coefficient 3
#define OV7670_REG_MTX4 0x52               //< Matrix coefficient 4
#define OV7670_REG_MTX5 0x53               //< Matrix coefficient 5
#define OV7670_REG_MTX6 0x54               //< Matrix coefficient 6
#define OV7670_REG_BRIGHT 0x55             //< Brightness control
#define OV7670_REG_CONTRAS 0x56            //< Contrast control
#define OV7670_REG_CONTRAS_CENTER 0x57     //< Contrast center
#define OV7670_REG_MTXS 0x58               //< Matrix coefficient sign
#define OV7670_REG_LCC1 0x62               //< Lens correction option 1
#define OV7670_REG_LCC2 0x63               //< Lens correction option 2
#define OV7670_REG_LCC3 0x64               //< Lens correction option 3
#define OV7670_REG_LCC4 0x65               //< Lens correction option 4
#define OV7670_REG_LCC5 0x66               //< Lens correction option 5
#define OV7670_REG_MANU 0x67               //< Manual U value
#define OV7670_REG_MANV 0x68               //< Manual V value
#define OV7670_REG_GFIX 0x69               //< Fix gain control
#define OV7670_REG_GGAIN 0x6A              //< G channel AWB gain
#define OV7670_REG_DBLV 0x6B               //< PLL & regulator control
#define OV7670_REG_AWBCTR3 0x6C            //< AWB control 3
#define OV7670_REG_AWBCTR2 0x6D            //< AWB control 2
#define OV7670_REG_AWBCTR1 0x6E            //< AWB control 1
#define OV7670_REG_AWBCTR0 0x6F            //< AWB control 0
#define OV7670_REG_SCALING_XSC 0x70        //< Test pattern X scaling
#define OV7670_REG_SCALING_YSC 0x71        //< Test pattern Y scaling
#define OV7670_REG_SCALING_DCWCTR 0x72     //< DCW control
#define OV7670_REG_SCALING_PCLK_DIV 0x73   //< DSP scale control clock divide
#define OV7670_REG_REG74 0x74              //< Digital gain control
#define OV7670_REG_REG76 0x76              //< Pixel correction
#define OV7670_REG_SLOP 0x7A               //< Gamma curve highest seg slope
#define OV7670_REG_GAM_BASE 0x7B           //< Gamma register base (1 of 15)
#define OV7670_GAM_LEN 15                  //< Number of gamma registers
#define OV7670_R76_BLKPCOR 0x80            //< REG76 black pixel corr enable
#define OV7670_R76_WHTPCOR 0x40            //< REG76 white pixel corr enable
#define OV7670_REG_RGB444 0x8C             //< RGB 444 control
#define OV7670_R444_ENABLE 0x02            //< RGB444 enable
#define OV7670_R444_RGBX 0x01              //< RGB444 word format
#define OV7670_REG_DM_LNL 0x92             //< Dummy line LSB
#define OV7670_REG_LCC6 0x94               //< Lens correction option 6
#define OV7670_REG_LCC7 0x95               //< Lens correction option 7
#define OV7670_REG_HAECC1 0x9F             //< Histogram-based AEC/AGC ctrl 1
#define OV7670_REG_HAECC2 0xA0             //< Histogram-based AEC/AGC ctrl 2
#define OV7670_REG_SCALING_PCLK_DELAY 0xA2 //< Scaling pixel clock delay
#define OV7670_REG_BD50MAX 0xA5            //< 50 Hz banding step limit
#define OV7670_REG_HAECC3 0xA6             //< Histogram-based AEC/AGC ctrl 3
#define OV7670_REG_HAECC4 0xA7             //< Histogram-based AEC/AGC ctrl 4
#define OV7670_REG_HAECC5 0xA8             //< Histogram-based AEC/AGC ctrl 5
#define OV7670_REG_HAECC6 0xA9             //< Histogram-based AEC/AGC ctrl 6
#define OV7670_REG_HAECC7 0xAA             //< Histogram-based AEC/AGC ctrl 7
#define OV7670_REG_BD60MAX 0xAB            //< 60 Hz banding step limit
#define OV7670_REG_ABLC1 0xB1              //< ABLC enable
#define OV7670_REG_THL_ST 0xB3             //< ABLC target
#define OV7670_REG_SATCTR 0xC9             //< Saturation control
// reference to https://github.com/usedbytes/camera-pico-ov7670/blob/main/ov7670.c
const uint8_t OV7670_rgb[][2] =
        {
            // Manual output format, RGB, use RGB565 and full 0-255 output range
            {OV7670_REG_COM7, OV7670_COM7_RGB},
            {OV7670_REG_RGB444, 0},
            {OV7670_REG_COM15, OV7670_COM15_RGB565 | OV7670_COM15_R00FF},
            {0xFF, 0xFF}};
const uint8_t OV7670_yuv[][2] =
        {
            // Manual output format, YUV, use full output range
            {OV7670_REG_COM7, OV7670_COM7_YUV},
            {OV7670_REG_COM15, OV7670_COM15_R00FF},
            {0xFF, 0xFF}};
const uint8_t OV7670_init[][2] = {
        {OV7670_REG_TSLB, 0x0d},    // auto window
        {OV7670_REG_COM13,0x88},
        //{OV7670_REG_COM10, OV7670_COM10_VS_NEG}, // -VSYNC (req by SAMD PCC)
        {OV7670_REG_SLOP, 0x20},
        {OV7670_REG_GAM_BASE, 0x1C},
        {OV7670_REG_GAM_BASE + 1, 0x28},
        {OV7670_REG_GAM_BASE + 2, 0x3C},
        {OV7670_REG_GAM_BASE + 3, 0x55},
        {OV7670_REG_GAM_BASE + 4, 0x68},
        {OV7670_REG_GAM_BASE + 5, 0x76},
        {OV7670_REG_GAM_BASE + 6, 0x80},
        {OV7670_REG_GAM_BASE + 7, 0x88},
        {OV7670_REG_GAM_BASE + 8, 0x8F},
        {OV7670_REG_GAM_BASE + 9, 0x96},
        {OV7670_REG_GAM_BASE + 10, 0xA3},
        {OV7670_REG_GAM_BASE + 11, 0xAF},
        {OV7670_REG_GAM_BASE + 12, 0xC4},
        {OV7670_REG_GAM_BASE + 13, 0xD7},
        {OV7670_REG_GAM_BASE + 14, 0xE8},
        {OV7670_REG_COM8,
         OV7670_COM8_FASTAEC | OV7670_COM8_AECSTEP | OV7670_COM8_BANDING},
        {OV7670_REG_GAIN, 0x00},
        {OV7670_REG_COM2, 0x00},
        {OV7670_REG_COM4, 0x00},
        {OV7670_REG_COM9, 0x20}, // Max AGC value
        {OV7670_REG_COM11, (1 << 3)}, // 50Hz
        //{0x9D, 99}, // Banding filter for 50 Hz at 15.625 MHz
        {0x9D, 89}, // Banding filter for 50 Hz at 13.888 MHz
        {OV7670_REG_BD50MAX, 0x05},
        {OV7670_REG_BD60MAX, 0x07},
        {OV7670_REG_AEW, 0x75},
        {OV7670_REG_AEB, 0x63},
        {OV7670_REG_VPT, 0xA5},
        {OV7670_REG_HAECC1, 0x78},
        {OV7670_REG_HAECC2, 0x68},
        {0xA1, 0x03},              // Reserved register?
        {OV7670_REG_HAECC3, 0xDF}, // Histogram-based AEC/AGC setup
        {OV7670_REG_HAECC4, 0xDF},
        {OV7670_REG_HAECC5, 0xF0},
        {OV7670_REG_HAECC6, 0x90},
        {OV7670_REG_HAECC7, 0x94},
        {OV7670_REG_COM8, OV7670_COM8_FASTAEC | OV7670_COM8_AECSTEP |
                              OV7670_COM8_BANDING | OV7670_COM8_AGC |
                              OV7670_COM8_AEC | OV7670_COM8_AWB },
        {OV7670_REG_COM5, 0x61},
        {OV7670_REG_COM6, 0x4B},
        {0x16, 0x02},            // Reserved register?
        {OV7670_REG_MVFP, 0x07}, // 0x07,
        {OV7670_REG_ADCCTR1, 0x02},
        {OV7670_REG_ADCCTR2, 0x91},
        {0x29, 0x07}, // Reserved register?
        {OV7670_REG_CHLF, 0x0B},
        {0x35, 0x0B}, // Reserved register?
        {OV7670_REG_ADC, 0x1D},
        {OV7670_REG_ACOM, 0x71},
        {OV7670_REG_OFON, 0x2A},
        {OV7670_REG_COM12, 0x78},
        {0x4D, 0x40}, // Reserved register?
        {0x4E, 0x20}, // Reserved register?
        {OV7670_REG_GFIX, 0x5D},
        {OV7670_REG_REG74, 0x19},
        {0x8D, 0x4F}, // Reserved register?
        {0x8E, 0x00}, // Reserved register?
        {0x8F, 0x00}, // Reserved register?
        {0x90, 0x00}, // Reserved register?
        {0x91, 0x00}, // Reserved register?
        {OV7670_REG_DM_LNL, 0x00},
        {0x96, 0x00}, // Reserved register?
        {0x9A, 0x80}, // Reserved register?
        {0xB0, 0x84}, // Reserved register?
        {OV7670_REG_ABLC1, 0x0C},
        {0xB2, 0x0E}, // Reserved register?
        {OV7670_REG_THL_ST, 0x82},
        {0xB8, 0x0A}, // Reserved register?
        {OV7670_REG_AWBC1, 0x14},
        {OV7670_REG_AWBC2, 0xF0},
        {OV7670_REG_AWBC3, 0x34},
        {OV7670_REG_AWBC4, 0x58},
        {OV7670_REG_AWBC5, 0x28},
        {OV7670_REG_AWBC6, 0x3A},
        {0x59, 0x88}, // Reserved register?
        {0x5A, 0x88}, // Reserved register?
        {0x5B, 0x44}, // Reserved register?
        {0x5C, 0x67}, // Reserved register?
        {0x5D, 0x49}, // Reserved register?
        {0x5E, 0x0E}, // Reserved register?
        {OV7670_REG_LCC3, 0x04},
        {OV7670_REG_LCC4, 0x20},
        {OV7670_REG_LCC5, 0x05},
        {OV7670_REG_LCC6, 0x04},
        {OV7670_REG_LCC7, 0x08},
        {OV7670_REG_AWBCTR3, 0x0A},
        {OV7670_REG_AWBCTR2, 0x55},
        //{OV7670_REG_MTX1, 0x80},
        //{OV7670_REG_MTX2, 0x80},
        //{OV7670_REG_MTX3, 0x00},
        //{OV7670_REG_MTX4, 0x22},
        //{OV7670_REG_MTX5, 0x5E},
        //{OV7670_REG_MTX6, 0x80}, // 0x40?
        {OV7670_REG_AWBCTR1, 0x11},
        //{OV7670_REG_AWBCTR0, 0x9F}, // Or use 0x9E for advance AWB
        {OV7670_REG_AWBCTR0, 0x9E}, // Or use 0x9E for advance AWB
        {OV7670_REG_BRIGHT, 0x00},
        {OV7670_REG_CONTRAS, 0x40},
        {OV7670_REG_CONTRAS_CENTER, 0x80}, // 0x40?
        {0xff, 0xff},       // End-of-data marker
        };


#endif
