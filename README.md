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
