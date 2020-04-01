#include <SPI.h>
#include <Wire.h>
#include <Esp.h>

#include <SSD1351/CustomDriver/OLEDDriver.h>

SSD1351::OLEDDriver driver;

void setup()
{
	SSD1351::OLEDDriver::Config config;
	config.chipSelectPin = 5;
	config.clockPin = 18;
	config.dataCommandPin = 16;
	config.dataInPin = 17;
	config.resetPin = 27;

	// Init GPIO pins.
	// The other SPI-related pins are handled by the SPI driver.
	pinMode(config.chipSelectPin, OUTPUT);
	pinMode(config.resetPin, OUTPUT);
	pinMode(config.dataCommandPin, OUTPUT);

	// Init UART.
	Serial.begin(115200);

	SPI.setDataMode(SPI_MODE0);
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.begin();

	digitalWrite(config.chipSelectPin, LOW);
	driver.initialise(config);
}

void loop()
{
	driver.clearScreen(0x0000);
	delay(500);
	driver.clearScreen(0xFF00);
	delay(500);
	driver.clearScreen(0x00FF);
	delay(500);
}
