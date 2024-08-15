/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"
#include "device/usbd.h"

//--------------------------------------------------------------------+
// USER 
//--------------------------------------------------------------------+
#include "ov7670.h"
#include "hardware/vreg.h"


const int PIN_LED = 25;

const int PIN_CAM_SIOC = 21; // I2C0 SCL
const int PIN_CAM_SIOD = 4; // I2C0 SDA
const int PIN_CAM_RESETB = 17;
const int PIN_CAM_XCLK = 3;
const int PIN_CAM_VSYNC = 16;
const int PIN_CAM_Y2_PIO_BASE = 6;

const uint8_t CMD_REG_WRITE = 0xAA;
const uint8_t CMD_REG_READ = 0xBB;
const uint8_t CMD_CAPTURE = 0xCC;
const uint8_t CMD_SET_WINDOW = 0xDD;
#define DUMMY_BYTE 2*4//2*4
static uint8_t frame_ov7670[FRAME_WIDTH * FRAME_HEIGHT * 2 + DUMMY_BYTE];

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void led_blinking_task(void);
void video_task(struct ov2640_config *config);

/*------------- MAIN -------------*/
int main(void)
{
  vreg_set_voltage(VREG_VOLTAGE_MAX);
  set_sys_clock_khz(120*1000, true);
  board_init();

  struct ov2640_config config;
	config.sccb = i2c0;
	config.pin_sioc = PIN_CAM_SIOC;
	config.pin_siod = PIN_CAM_SIOD;

	config.pin_resetb = PIN_CAM_RESETB;
	config.pin_xclk = PIN_CAM_XCLK;
	config.pin_vsync = PIN_CAM_VSYNC;
	config.pin_y2_pio_base = PIN_CAM_Y2_PIO_BASE;

	config.pio = pio0;
	config.pio_sm = 0;

	config.dma_channel = 0;
	config.image_buf = frame_ov7670;
	config.image_buf_size = sizeof(frame_ov7670);

	ov2640_init(&config);
	uint8_t midh = ov2640_reg_read(&config, 0x1C);
	uint8_t midl = ov2640_reg_read(&config, 0x1D);

  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);

  while (1)
  {

    tud_task(); // tinyusb device task
    led_blinking_task();
    video_task(&config);
  }

  return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}


//--------------------------------------------------------------------+
// USB Video
//--------------------------------------------------------------------+
static unsigned frame_num = 0;
static unsigned tx_busy = 0;
static unsigned interval_ms = 1000 / FRAME_RATE;

/* YUY2 frame buffer */
#ifdef CFG_EXAMPLE_VIDEO_TEST
static uint8_t frame_buffer[FRAME_WIDTH * FRAME_HEIGHT * 16 / 8];
static void fill_color_bar(uint8_t *buffer, unsigned start_position)
{
  /* EBU color bars
   * See also https://stackoverflow.com/questions/6939422 */
  static uint8_t const bar_color[8][4] = {
    /*  Y,   U,   Y,   V */
    { 235, 128, 235, 128}, /* 100% White */
    { 219,  16, 219, 138}, /* Yellow */
    { 188, 154, 188,  16}, /* Cyan */
    { 173,  42, 173,  26}, /* Green */
    {  78, 214,  78, 230}, /* Magenta */
    {  63, 102,  63, 240}, /* Red */
    {  32, 240,  32, 118}, /* Blue */
    {  16, 128,  16, 128}, /* Black */
  };
  uint8_t *p;

  /* Generate the 1st line */
  uint8_t *end = &buffer[FRAME_WIDTH * 2];
  unsigned idx = (FRAME_WIDTH / 2 - 1) - (start_position % (FRAME_WIDTH / 2));
  p = &buffer[idx * 4];
  for (unsigned i = 0; i < 8; ++i) {
    for (int j = 0; j < FRAME_WIDTH / (2 * 8); ++j) {
      memcpy(p, &bar_color[i], 4);
      p += 4;
      if (end <= p) {
        p = buffer;
      }
    }
  }
  /* Duplicate the 1st line to the others */
  p = &buffer[FRAME_WIDTH * 2];
  for (unsigned i = 1; i < FRAME_HEIGHT; ++i) {
    memcpy(p, buffer, FRAME_WIDTH * 2);
    p += FRAME_WIDTH * 2;
  }
}
#else
void fill_frame(struct ov2640_config *config)
{
  ov2640_capture_frame(config);
}
#endif

void video_task(struct ov2640_config *config)
{
  static unsigned start_ms = 0;
  static unsigned already_sent = 0;

  if (!tud_video_n_streaming(0, 0)) {
    already_sent  = 0;
    frame_num     = 0;
    return;
  }

  if (!already_sent) {
    already_sent = 1;
    tx_busy = 1;
    start_ms = board_millis();
#ifdef CFG_EXAMPLE_VIDEO_TEST
    fill_color_bar(frame_buffer, frame_num);
    tud_video_n_frame_xfer(0, 0, (void*)frame_buffer, FRAME_WIDTH * FRAME_HEIGHT * 16/8);
#else
    fill_frame(config);
    tud_video_n_frame_xfer(0, 0, (void*)((uint8_t*)frame_ov7670+DUMMY_BYTE), FRAME_WIDTH * FRAME_HEIGHT * 16/8);
#endif
  }

  unsigned cur = board_millis();
  if (cur - start_ms < interval_ms) return; // not enough time
  if (tx_busy) return;
  start_ms += interval_ms;
  tx_busy = 1;
#ifdef CFG_EXAMPLE_VIDEO_TEST
  fill_color_bar(frame_buffer, frame_num);
  tud_video_n_frame_xfer(0, 0, (void*)frame_buffer, FRAME_WIDTH * FRAME_HEIGHT * 16/8);
#else
    fill_frame(config);
    tud_video_n_frame_xfer(0, 0, (void*)((uint8_t*)frame_ov7670+DUMMY_BYTE), FRAME_WIDTH * FRAME_HEIGHT * 16/8);
#endif
}

void tud_video_frame_xfer_complete_cb(uint_fast8_t ctl_idx, uint_fast8_t stm_idx)
{
  (void)ctl_idx; (void)stm_idx;
  tx_busy = 0;
  /* flip buffer */
  ++frame_num;
}

int tud_video_commit_cb(uint_fast8_t ctl_idx, uint_fast8_t stm_idx,
			video_probe_and_commit_control_t const *parameters)
{
  (void)ctl_idx; (void)stm_idx;
  /* convert unit to ms from 100 ns */
  interval_ms = parameters->dwFrameInterval / 10000;
  return VIDEO_ERROR_NONE;
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}
