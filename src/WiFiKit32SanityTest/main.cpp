#include <ESP32HAL/ESP32HAL.h>
#include <ESP32HAL/InitConfig.h>
#include <heltec.h>
#include <SSD1306Images/BadgerosSplashScreen.h>

void setup()
{
	// Initialise common stuff
	ESP32HAL::InitConfig config;
	ESP32HAL::initialise(config);

	// Initialise Heltec-specific stuff
	Heltec.display->init();
	Heltec.display->flipScreenVertically();
	Heltec.display->setFont(ArialMT_Plain_10);
	Heltec.display->clear();

	ESP32HAL::Serial.println("WiFiKit32 initialised.");
}

void loop()
{
	static bool drawn = false;

	if ( !drawn )
	{
		using namespace Image_BadgerosSplashScreen;
		Heltec.display->drawFastImage(0, 0, WIDTH, HEIGHT, DATA);
		Heltec.display->display();
		drawn = true;
	}
}
