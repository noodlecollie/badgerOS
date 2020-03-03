#include "HeltecESP32WifiKit32/WiFiKit32.h"
#include "SSD1306Images/BadgerosSplashScreen.h"

namespace Project_WiFiKit32SanityTest
{
	void setup()
	{
		WifiKit32::initialiseHardware();
		WifiKit32::Serial.println("WiFiKit32 initialised.");
	}

	void loop()
	{
		static bool drawn = false;

		if ( !drawn )
		{
			using namespace Image_BadgerosSplashScreen;
			WifiKit32::Display->drawFastImage(0, 0, WIDTH, HEIGHT, DATA);
			WifiKit32::Display->display();
			drawn = true;
		}
	}
}
