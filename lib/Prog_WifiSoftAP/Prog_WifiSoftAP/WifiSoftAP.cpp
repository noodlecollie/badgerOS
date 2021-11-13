#include <WiFi.h>
#include <PlatformConfig/PlatformConfigObject.h>
#include <PlatformConfig/Platform.h>
#include "WifiSoftAP.h"

namespace WifiSoftAP
{
	// Replace with your network credentials
	const char* ssid     = "ESP32-Access-Point";
	const char* password = "123456789";

	// Set web server port number to 80
	WiFiServer server(80);

	void getPlatformConfigArgs(PlatformConfig::ConfigArgs&)
	{
		// Nothing specific here
	}

	void setup()
	{
		using namespace PlatformConfig;
		const PlatformConfigObject* configObject = globalConfig();

		configObject->initialiseSubsystem<SerialConfig>([](const SerialConfig& config)
		{
			Serial.begin(config.baudRate);
			Serial.flush();
		});

		// Connect to Wi-Fi network with SSID and password
		Serial.print("Setting AP (Access Point)... ");

		// Remove the password parameter, if you want the AP (Access Point) to be open
		WiFi.softAP(ssid, password);

		IPAddress IP = WiFi.softAPIP();
		Serial.print("AP IP address: ");
		Serial.println(IP);

		server.begin();
	}

	void loop()
	{
		WiFiClient client = server.available();   // Listen for incoming clients

		if (client)
		{
			// If a new client connects,
			// print a message out in the serial port
			Serial.println("New Client.");

			// make a String to hold incoming data from the client
			String currentLine = "";

			while (client.connected())
			{
				// loop while the client's connected
				if (client.available())
				{
					// if there's bytes to read from the client,
					// read a byte, then
					// print it out the serial monitor
					char c = client.read();
					Serial.write(c);

					// if the byte is a newline character
					if (c == '\n')
					{
						// if the current line is blank, you got two newline characters in a row.
						// that's the end of the client HTTP request, so send a response:
						if (currentLine.length() == 0)
						{
							// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
							// and a content-type so the client knows what's coming, then a blank line:
							client.println("HTTP/1.1 200 OK");
							client.println("Content-type:text/html");
							client.println("Connection: close");
							client.println();

							// Display the HTML web page
							client.println("<!DOCTYPE html><html>");
							client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
							client.println("<link rel=\"icon\" href=\"data:,\">");

							// Web Page Heading
							client.println("<body><h1>ESP32 Web Server</h1></body></html>");

							// The HTTP response ends with another blank line
							client.println();

							// Break out of the while loop
							break;
						}
						else
						{
							// if you got a newline, then clear currentLine
							currentLine = "";
						}
					}
					else if (c != '\r')
					{
						// if you got anything else but a carriage return character,
						// add it to the end of the currentLine
						currentLine += c;
					}
				}
			}

			// Close the connection
			client.stop();
			Serial.println("Client disconnected.");
			Serial.println("");
		}
	}
}
