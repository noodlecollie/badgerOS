#include <HeltecESP32WiFiKit32.h>
#include <SSD1306Images/BadgerosSplashScreen.h>

void setup()
{
	HeltecESP32WiFiKit32::initialiseHardware();
	HeltecESP32WiFiKit32::Serial.println("WiFiKit32 initialised.");
}

void loop()
{
	static bool drawn = false;

	if ( !drawn )
	{
		using namespace Image_BadgerosSplashScreen;
		HeltecESP32WiFiKit32::Display->drawFastImage(0, 0, WIDTH, HEIGHT, DATA);
		HeltecESP32WiFiKit32::Display->display();
		drawn = true;
	}
}
