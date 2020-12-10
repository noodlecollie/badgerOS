Pimoroni Inky Driver Details
============================

This document corresponds to the [Pimoroni Inky Impression](https://shop.pimoroni.com/products/inky-impression), which may be a good e-ink display for us to use.

The attributes of this display are:

* 600x448 pixels
* 5.7"
* 125x100mm overall screen area (115x86mm active)

The official Python driver for the display can be found [on GitHub](https://github.com/pimoroni/inky). We will need to port this to C++.

The display itself uses a UC8159 controller, whose data sheet can be found here: https://www.buydisplay.com/download/ic/UC8159C.pdf

## Definitions

The following table lists the different variants of display that the Python driver supports, along with their corresponding IDs (see Display Identification).

| Value | Description           |
| :---- | :-------------------- |
| 1     | Red pHAT (High-Temp)  |
| 2     | Yellow wHAT           |
| 3     | Black wHAT            |
| 4     | Black pHAT            |
| 5     | Yellow pHAT           |
| 6     | Red wHAT              |
| 7     | Red wHAT (High-Temp)  |
| 8     | Red wHAT              |
| 10    | Black pHAT (SSD1608)  |
| 11    | Red pHAT (SSD1608)    |
| 12    | Yellow pHAT (SSD1608) |
| 14    | 7-Colour (UC8159)     |

The SPI chunk size is 4096 bytes. The data/command pin should be held low if sending a command to the display over SPI, or high if sending data.

The rest of the definitions apply to the UC8159 (7-colour) display.

### Colour Bit Constants

| Value | Colour |
| :---- | :----- |
| 0     | Black  |
| 1     | White  |
| 2     | Green  |
| 3     | Blue   |
| 4     | Red    |
| 5     | Yellow |
| 6     | Orange |
| 7     | Clean  |

### Resolution

| Dimension | Length |
| :-------- | :----- |
| Width     | 600    |
| Height    | 448    |

### Pin Config

| Type               | GPIO Pin |
| :----------------- | :------- |
| Chip Select (SPI)  | 8        |
| Data/Command (SPI) | 22       |
| Reset              | 27       |
| Busy               | 17       |

### Chip Select Channel

| Pin | Channel |
| :-- | :------ |
| 8   | 0       |
| 7   | 1       |

## Display Identification

To identify the display, the Python driver writes an I2C zero byte to address `0x50`, and then reads 29 little-endian I2C bytes from address `0x50`.

The data structure of the bytes read is:

* `uint16` [0-1]: Width of display in pixels
* `uint16` [2-3]: Height of display in pixels
* `uint8` [4]: Colour support
* `uint8` [5]: PCB variant
* `uint8` [6]: Display variant (see the Display Variants table)
* `uint8` [7]: Length of Pascal string indicating EEPROM write time
* `char[]` [8-28]: Chatacters of Pascal string indicating EEPROM write time

We would expect our display to be variant 14, which the Python driver describes within `inky_uc8159.py`.

## Display Helper Functions

The following helper functions exist within `inky_uc8159.py` to aid communications with the display.

### _busy_wait()

Busy waiting is performed by polling the busy GPIO pin and waiting for it to go high. If a timeout expires before this happens, a runtime error is raised.

### _send_command()

This function sends a command to the display (the DC pin is low). If some data is also provided as the final optional argument, a `_send_data()` call is subsequently made after the command has been sent.

This function calls through to the more generic `_spi_write()`.

### _send_data()

This function sends data to the display (the DC pin is high). It calls through to the more generic `_spi_write()`.

### `_spi_write()`

This function actually deals with sending the bits over SPI. It performs the following steps:

1. Sets the chip select low.
2. Sets the DC pin high (if sending a command) or low (if sending data).
3. Transfers data in chunks (at most 4KB each).
4. Sets the chip select high.

## Display Setup

The display setup function is called to initialise the display any time its contents are updated. This does mean that its refresh rate is quite slow.

### Initial Comms
If GPIO has not yet been set up, the function sets the following initial states for pins:

| Pin Type     | I/O    | Initial State | Pull Up/Down |
| :----------- | :----- | :------------ | :----------- |
| Chip select  | Output | High          | Off          |
| Data/Command | Output | Low           | Off          |
| Reset        | Output | High          | Off          |
| Busy         | Input  | N/A           | Off          |

Finally, the SPI bus max speed is set to `3000000` (3MHz).

### Display Pre-Update

To reset the display, the reset pin is held low for 0.1 seconds, then held high for 0.1 seconds. After this, `_busy_wait()` is called to wait for the display to be ready.

Following this, several commands are sent to the display:

``` python
	# Resolution Setting
	# 10bit horizontal followed by a 10bit vertical resolution
	# we'll let struct.pack do the work here and send 16bit values
	# life is too short for manual bit wrangling
	self._send_command(
		UC8159_TRES, # 0x61
		struct.pack(">HH", self.width, self.height))

	# Panel Setting
	# 0b11000000 = Resolution select, 0b00 = 640x480, our panel is 0b11 = 600x448
	# 0b00100000 = LUT selection, 0 = ext flash, 1 = registers, we use ext flash
	# 0b00010000 = Ignore
	# 0b00001000 = Gate scan direction, 0 = down, 1 = up (default)
	# 0b00000100 = Source shift direction, 0 = left, 1 = right (default)
	# 0b00000010 = DC-DC converter, 0 = off, 1 = on
	# 0b00000001 = Soft reset, 0 = Reset, 1 = Normal (Default)
	self._send_command(
		UC8159_PSR, # 0x00
		[
			0b11101111,  # See above for more magic numbers
			0x08         # display_colours == UC8159_7C
		]
	)

	# Power Settings
	self._send_command(
		UC8159_PWR, # 0x01
		[
			(0x06 << 3) |  # ??? - not documented in UC8159 datasheet
			(0x01 << 2) |  # SOURCE_INTERNAL_DC_DC
			(0x01 << 1) |  # GATE_INTERNAL_DC_DC
			(0x01),        # LV_SOURCE_INTERNAL_DC_DC
			0x00,          # VGx_20V
			0x23,          # UC8159_7C
			0x23           # UC8159_7C
		]
	)

	# Set the PLL clock frequency to 50Hz
	# 0b11000000 = Ignore
	# 0b00111000 = M
	# 0b00000111 = N
	# PLL = 2MHz * (M / N)
	# PLL = 2MHz * (7 / 4)
	# PLL = 2,800,000 ???
	self._send_command(UC8159_PLL, # 0x30
		[0x3C])  # 0b00111100

	# Send the TSE register to the display
	self._send_command(UC8159_TSE, # 0x41
		[0x00])  # Colour

	# VCOM and Data Interval setting
	# 0b11100000 = Vborder control (0b001 = LUTB voltage)
	# 0b00010000 = Data polarity
	# 0b00001111 = Vcom and data interval (0b0111 = 10, default)
	self._send_command(UC8159_CDI, # 0x50
		[0x37])  # 0b00110111

	# Gate/Source non-overlap period
	# 0b11110000 = Source to Gate (0b0010 = 12nS, default)
	# 0b00001111 = Gate to Source
	self._send_command(UC8159_TCON, # 0x60
		[0x22])  # 0b00100010

	# Disable external flash
	self._send_command(UC8159_DAM, # 0x65
		[0x00])

	# UC8159_7C
	self._send_command(UC8159_PWS, # 0xE3
		[0xAA])

	# Power off sequence
	# 0b00110000 = power off sequence of VDH and VDL, 0b00 = 1 frame (default)
	# All other bits ignored?
	self._send_command(UC8159_PFS, # 0x03
		[0x00])  # PFS_1_FRAME
```
It would be interesting to see whether we can trim this process down.

## Display Update

To send pixels to the display, the above setup function is called. Once complete, the following commands are executed:

``` python
	# DTM = Data Start Transmission
	# Each byte is masked 0b01110111, with the higher trio of bits
	# corresponding to the first pixel, and the lower trio of bits
	# corresponding to the second pixel.
	self._send_command(UC8159_DTM1, buf)
	self._busy_wait()

	# PON = Power On
	self._send_command(UC8159_PON)
	self._busy_wait()

	# DRF = Display Refresh
	self._send_command(UC8159_DRF)
	self._busy_wait()

	# POF = Power Off
	self._send_command(UC8159_POF)
	self._busy_wait()
```

As the display is e-ink, the power does not need to be left on.

## Raspberry Pi Pinouts

https://pinout.xyz/pinout/inky_phat has a useful diagram of the Raspberry Pi GPIO pins used by the Inky pHAT (which the 7-colour display should also use). Note that these pinouts are consequently mirrored horizontally when looking at the underside of the Inky.

SPI0 is used to send commands to the display. I2C is not applicable to this display. 3.3v and 5v are both required.

The full set of pins used is:

| Type               | Pi Pinout                            | Heltec Pinout   |
| :----------------- | :----------------------------------- | :-------------- |
| 3.3v               | 1                                    | 3.3v            |
| 5v                 | 2                                    | 5v              |
| Ground             | One of: 6, 9, 14, 20, 25, 30, 34, 39 | Ground          |
| SPI0 Chip Select 0 | GPIO 8                               | GPIO 5          |
| SPI0 MISO          | GPIO 9                               | GPIO 19         |
| SPI0 MOSI          | GPIO 10                              | GPIO 23         |
| SPI0 SCLK          | GPIO 11                              | GPIO 18         |
| Busy               | GPIO 17                              | GPIO 35         |
| Data/Command       | GPIO 22                              | GPIO 16         |
| Reset              | GPIO 27                              | GPIO 27         |
