# Pico USB Camera
Project Link https://github.com/mxyxbb/rp2040_ov7670_usb_camera/tree/main

Introduction Video Link https://www.bilibili.com/video/BV123e5ehEis/?spm_id_from=333.999.0.0&vd_source=6e817c3943bff9f1749caaa76f60e5dc

Pico-SDK-v1.5.1 is used.
## Description
Hello everyone, I made a USB camera and would like to share it with you.
In this project, I used the Raspberry Pi's RP2040 microcontroller to drive the OV7670 camera and captured images in YUV422 format with a resolution of 320x240. Then I used the TinyUSB USB protocol stack to transfer the image data to the computer in the form of a USB Video Class (UVC) Device through the 12Mbps full-speed USB interface integrated on the RP2040. The current frame rate is only 5, and there is still room for optimization（To do）.

大家好啊，我制作了一个USB摄像头，向大家分享一下。
这个项目中使用树莓派家的RP2040微控制器驱动OV7670摄像头，捕获到了320x240分辨率的YUV422格式的图像。然后我通过RP2040上集成的12Mbps的全速USB接口，使用TinyUSB的USB协议栈，以USB视频类设备，也就是 USB Video Class（UVC）Device的形式，将图像数据传输到了电脑上面。目前的帧率只有5，还有优化空间。

## Wiring
Wire the following Raspberry Pi Pico pins to an OV7670 board.

| Raspberry Pi Pico | OV2640            |
| ----------------- | ----------------- |
| GND               | GND               |
| 3V3(OUT)          | VCC (3.3)         |
| GP3               | XCLK              |
| GP4  (I2C0 SDA)   | SDA[^i2c_pullups] |
| GP6               | D0                |
| GP7               | D1                |
| GP8               | D2                |
| GP9               | D3                |
| GP10              | D4                |
| GP11              | D5                |
| GP12              | D6                |
| GP13              | D7                |
| GP14              | PCLK              |
| GP15              | HREF              |
| GP16              | VSYNC             |
| GP17              | RST               |
| GP21 (I2C0 SCL)   | SCL[^i2c_pullups] |


[^i2c_pullups]: Likely require I2C pullups unless breakout board provides them. Even so, adding a 10k pullup won't hurt.

![image](https://github.com/user-attachments/assets/db7764c1-1aeb-4732-9a20-e14c4e68baef)

![976c8a1f9cd98b5f3ae1b843d843040](https://github.com/user-attachments/assets/b8ef82da-4ef2-45a2-b333-1fa82be0545a)

### Reference link
https://github.com/usedbytes/camera-pico-ov7670

https://github.com/the6p4c/rp2040_ov2640

### Reference Docs 
OV7670/OV7171 CMOS VGA (640x480) CameraChip™ Implementation Guide

OV7670 Datasheet
