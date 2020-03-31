#include <ESP.h>

void setup()
{
	// Initialise common stuff
	Serial.begin(115200);
	Serial.flush();

	// Serial.println("Initialised!");
}

void loop()
{
	static int loop = 0;
	Serial.printf("This is loop %d.\n", ++loop);
	delay(1000);
}
