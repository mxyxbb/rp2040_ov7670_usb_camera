#include "ov7670.h"
#include "ov7670_init.h"
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "image.pio.h"
#include <stdio.h>

void OV7670_set_size(struct ov2640_config *platform, OV7670_size size);

static const uint8_t OV2640_ADDR = 0x42 >> 1;

void ov2640_init(struct ov2640_config *config) {
	// XCLK generation (~20.83 MHz)
	gpio_set_function(config->pin_xclk, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(config->pin_xclk);
	// 6 cycles (0 to 5), 125 MHz / 6 = ~20.83 MHz wrap rate
	pwm_set_wrap(slice_num, 4);
	pwm_set_gpio_level(config->pin_xclk, 2);
	pwm_set_enabled(slice_num, true);

	// SCCB I2C @ 100 kHz
	gpio_set_function(config->pin_sioc, GPIO_FUNC_I2C);
	gpio_set_function(config->pin_siod, GPIO_FUNC_I2C);
	i2c_init(config->sccb, 10 * 1000);
	gpio_pull_up(config->pin_sioc);
    gpio_pull_up(config->pin_siod);

	// Initialise reset pin
	gpio_init(config->pin_resetb);
	gpio_set_dir(config->pin_resetb, GPIO_OUT);

	// Reset camera, and give it some time to wake back up
	gpio_put(config->pin_resetb, 0);
	sleep_ms(100);
	gpio_put(config->pin_resetb, 1);
	sleep_ms(100);
	ov2640_reg_write(config, OV7670_REG_COM7, OV7670_COM7_RESET); // soft reset regs
	sleep_ms(100);
	ov2640_reg_write(config, OV7670_REG_CLKRC, 1);
	ov2640_reg_write(config, OV7670_REG_DBLV, 1<<6);
	ov2640_regs_write(config, OV7670_yuv); // set format OV7670_yuv // OV7670_rgb
	ov2640_regs_write(config, OV7670_init);
	OV7670_set_size(config, OV7670_SIZE_DIV2);
	sleep_ms(300);
	// ov2640_regs_write(config, OV7670_Reg1);//OV_reg
	// ov2640_regs_write(config, ov7670_qvga_yuv422);
	//ov2640_regs_write(config, ov7670_qqvga_yuv422);
	

	// Enable image RX PIO
	uint offset = pio_add_program(config->pio, &image_program);
	image_program_init(config->pio, config->pio_sm, offset, config->pin_y2_pio_base);
}

void ov2640_capture_frame(struct ov2640_config *config) {
	dma_channel_config c = dma_channel_get_default_config(config->dma_channel);
	channel_config_set_read_increment(&c, false);
	channel_config_set_write_increment(&c, true);
	channel_config_set_dreq(&c, pio_get_dreq(config->pio, config->pio_sm, false));
	channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
	
	dma_channel_configure(
		config->dma_channel, &c,
		config->image_buf,
		&config->pio->rxf[config->pio_sm],
		config->image_buf_size,
		false
	);

	// Wait for vsync rising edge to start frame
	while (gpio_get(config->pin_vsync) == true);
	while (gpio_get(config->pin_vsync) == false);
	
	// pio_sm_set_enabled(config->pio, config->pio_sm, true);
	//pio_sm_set_enabled(config->pio, config->pio_sm, true);
	// while (gpio_get(15) == true);
	// while (gpio_get(15) == false);
	// while (gpio_get(15) == true);
	// while (gpio_get(15) == false);
	dma_channel_start(config->dma_channel);
	dma_channel_wait_for_finish_blocking(config->dma_channel);
}

void ov2640_reg_write(struct ov2640_config *config, uint8_t reg, uint8_t value) {
	uint8_t data[] = {reg, value};
	i2c_write_blocking(config->sccb, OV2640_ADDR, data, sizeof(data), false);
}

uint8_t ov2640_reg_read(struct ov2640_config *config, uint8_t reg) {
	i2c_write_blocking(config->sccb, OV2640_ADDR, &reg, 1, false);

	uint8_t value;
	i2c_read_blocking(config->sccb, OV2640_ADDR, &value, 1, false);

	return value;
}

void ov2640_regs_write(struct ov2640_config *config, const uint8_t (*regs_list)[2]) {
	uint16_t count=0;
	while (1) {
		uint8_t reg = (*regs_list)[0];
		uint8_t value = (*regs_list)[1];

		if (reg == 0xff && value == 0xff) {
			break;
		}
		ov2640_reg_write(config, reg, value);

		regs_list++;
		count++;
		sleep_ms(1);
	}
}

// 设置图像输出窗口
// 对QVGA设置。
// https://github.com/jinhaotutu/stm32f4-bmp-onenet/ov7670/ov7670.c
void OV7670_Window_Set(struct ov2640_config *config, uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	uint16_t endx;
	uint16_t endy;
	uint8_t temp; 
	
	if ((sx+width) > 320)
	{
		width = 320 - sx;
	}
	
	if ((sy+height) > 240)
	{
		height = 240 - sy;
	}
	
	sx += 176;
	sy += 12;
	
	endx=sx+width*2;	//HREF
 	endy=sy+height*2;	//VREF
	if(endx>784)
	{
		endx-=784;
	}
	
	temp=ov2640_reg_read(config,0X32);				//读取Href之前的值
	temp&=0XC0;
	temp|=((endx&0X07)<<3)|(sx&0X07);
	ov2640_reg_write(config,0X32,temp);
	ov2640_reg_write(config,0X17,sx>>3);			//设置Href的start高8位
	ov2640_reg_write(config,0X18,endx>>3);			//设置Href的end的高8位
	
	temp=ov2640_reg_read(config,0X03);				//读取Vref之前的值
	temp&=0XF0;
	temp|=((endy&0X03)<<2)|(sy&0X03);
	ov2640_reg_write(config,0X03,temp);				//设置Vref的start和end的最低2位
	ov2640_reg_write(config,0X19,sy>>2);			//设置Vref的start高8位
	ov2640_reg_write(config,0X1A,endy>>2);			//设置Vref的end的高8位

}

// Sets up PCLK dividers and sets H/V start/stop window. Rather than
// rolling this into OV7670_set_size(), it's kept separate so test code
// can experiment with different settings to find ideal defaults.
void OV7670_frame_control(struct ov2640_config *platform, uint8_t size, uint8_t vstart,
                          uint16_t hstart, uint8_t edge_offset,
                          uint8_t pclk_delay) {
  uint8_t value;

  // Enable downsampling if sub-VGA, and zoom if 1:16 scale
  value = (size > OV7670_SIZE_DIV1) ? OV7670_COM3_DCWEN : 0;
  if (size == OV7670_SIZE_DIV16)
    value |= OV7670_COM3_SCALEEN;
  ov2640_reg_write(platform, OV7670_REG_COM3, value);

  // Enable PCLK division if sub-VGA 2,4,8,16 = 0x19,1A,1B,1C
  value = (size > OV7670_SIZE_DIV1) ? (0x18 + size) : 0;
  ov2640_reg_write(platform, OV7670_REG_COM14, value);

  // Horiz/vert downsample ratio, 1:8 max (H,V are always equal for now)
  value = (size <= OV7670_SIZE_DIV8) ? size : OV7670_SIZE_DIV8;
  ov2640_reg_write(platform, OV7670_REG_SCALING_DCWCTR, value * 0x11);

  // Pixel clock divider if sub-VGA
  value = (size > OV7670_SIZE_DIV1) ? (0xF0 + size) : 0x08;
  ov2640_reg_write(platform, OV7670_REG_SCALING_PCLK_DIV, value);

  // Apply 0.5 digital zoom at 1:16 size (others are downsample only)
  value = (size == OV7670_SIZE_DIV16) ? 0x40 : 0x20; // 0.5, 1.0
  // Read current SCALING_XSC and SCALING_YSC register values because
  // test pattern settings are also stored in those registers and we
  // don't want to corrupt anything there.
  uint8_t xsc = ov2640_reg_read(platform, OV7670_REG_SCALING_XSC);
  uint8_t ysc = ov2640_reg_read(platform, OV7670_REG_SCALING_YSC);
  xsc = (xsc & 0x80) | value; // Modify only scaling bits (not test pattern)
  ysc = (ysc & 0x80) | value;
  // Write modified result back to SCALING_XSC and SCALING_YSC
  ov2640_reg_write(platform, OV7670_REG_SCALING_XSC, xsc);
  ov2640_reg_write(platform, OV7670_REG_SCALING_YSC, ysc);

  // Window size is scattered across multiple registers.
  // Horiz/vert stops can be automatically calc'd from starts.
  uint16_t vstop = vstart + 480;
  uint16_t hstop = (hstart + 640) % 784;
  ov2640_reg_write(platform, OV7670_REG_HSTART, hstart >> 3);
  ov2640_reg_write(platform, OV7670_REG_HSTOP, hstop >> 3);
  ov2640_reg_write(platform, OV7670_REG_HREF,
                        (edge_offset << 6) | ((hstop & 0b111) << 3) |
                            (hstart & 0b111));
  ov2640_reg_write(platform, OV7670_REG_VSTART, vstart >> 2);
  ov2640_reg_write(platform, OV7670_REG_VSTOP, vstop >> 2);
  ov2640_reg_write(platform, OV7670_REG_VREF,
                        ((vstop & 0b11) << 2) | (vstart & 0b11));

  ov2640_reg_write(platform, OV7670_REG_SCALING_PCLK_DELAY, pclk_delay);
}

void OV7670_set_size(struct ov2640_config *platform, OV7670_size size) {
  // Array of five window settings, index of each (0-4) aligns with the five
  // OV7670_size enumeration values. If enum changes, list must change!
  static struct {
    uint8_t vstart;
    uint8_t hstart;
    uint8_t edge_offset;
    uint8_t pclk_delay;
  } window[] = {
      // Window settings were tediously determined empirically.
      // I hope there's a formula for this, if a do-over is needed.
      {9, 162, 2, 2},  // SIZE_DIV1  640x480 VGA
      {10, 174, 4, 2}, // SIZE_DIV2  320x240 QVGA
      {11, 186, 2, 2}, // SIZE_DIV4  160x120 QQVGA
      {12, 210, 0, 2}, // SIZE_DIV8  80x60   ...
      {15, 252, 3, 2}, // SIZE_DIV16 40x30
  };

  OV7670_frame_control(platform, size, window[size].vstart, window[size].hstart,
                       window[size].edge_offset, window[size].pclk_delay);
}
