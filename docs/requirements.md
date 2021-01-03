Requirements
============

## Behavioural Requirements (OLED)

### Phase 1 (Core Functionality)

* Display main character image and main scrolling message.
* Temporarily display character information when requested: name, species, social media handle. Once finished displaying this information, fall back to displaying the main image and message.
* Display battery status at all times. (Note that this requires Rev B/C of the Olimex board!)
* Support different languages in UI.

### Phase 2 (Dynamic Data, Emotes)

* Allow main character image, main scrolling message, and character information to be set by the user via a companion app on a connected phone. The information should be stored persistently on the badge.
* Display connectivity status with regards to the connected phone at all times.
* Allow at least two "emotes" to be set by the user via the companion app, and stored persistently on the badge. An "emote" is comprised of a character image and scrolling message that are displayed, and a beep sequence that is played audibly.
* Temporarily display emote when invoked from companion phone app. Once finished displaying emote, fall back to displaying the main image and message.

### Phase 3 (Inter-Badge Connections)

* Allow a "connection greeting" to be set by the user via the companion app, and stored persistently on the badge. A "connection greeting" is comprised of a character image and scrolling message that are displayed, and a beep sequence that is played audibly.
* Allow badges to connect to one another wirelessly in pairs.
* When two badges are connected, temporarily display each badge's connection greeting on the other badge. Once finished displaying the greeting, fall back to displaying the main image and message.
* Log the character name, species, social media handle and greeting message from each connection performed by a badge, and store these persistently on the badge.
* Allow the user to enable or disable a badge's ability to connect to other badges.
* Allow the user to view the previous connection logs stored on the badge.
* Allow the user to clear connection logs stored on the badge.

## Behavioural Requirements (E-Ink)

### Phase 1 (Core Functionality)

* Display placeholder image with instructions on how to set badge image (eg. "Press and hold button to enable Bluetooth").
* Display instructions in appropriate language.
* Display battery status at all times. (Note that this requires Rev B/C of the Olimex board!)

### Phase 2 (Dynamic Data)

* Allow the badge to be connected to a phone via Bluetooth. The badge should be made discoverable by pressing and holding button D for two seconds, and should display this state (along with any pairing code) on the screen.
* Allow main image to be set by the user via a companion app on a connected phone. The image should be streamed directly to the display, as there will likely not be enough memory to store it on the badge.
* Allow an optional message to be specified and positioned on the image before sending from the phone.
* Allow an optional QR code to be specified and positioned on the image before sending from the phone.

### Phase 3 (Slideshow)

* Allow the image on the badge to be periodically updated from the connected phone, as long as it remains connected via Bluetooth. At least 4 different images should be available to set.
* Allow images to be cycled sequentially or randomly.
* Allow images to be cycled every 30s, 1m, 2m, 5m, 10m or 30m.

## Hardware Requirements (OLED)

1.  ESP32 board with LiPoly battery connector and charging capability: https://www.olimex.com/Products/IoT/ESP32/ESP32-DevKit-LiPo/open-source-hardware
2.  Battery - for example, https://www.olimex.com/Products/Power/BATTERY-LIPO1400mAh/. mAh is TBD, depending on power requirements. For reference:
    * The battery socket on the board is described as `SMD Header with top entry and 2mm step, with 2P positions`.
    * The battery socket part number used is `CI0102M1VT0-LF` - data sheet is available at https://store.comet.bg/download-file.php?id=4895
    * A connector that would fit into the socket has part number `CI0102S0000` - data sheet is available at https://store.comet.bg/download-file.php?id=2143
    * An RS Components connector that could work is https://uk.rs-online.com/web/p/wire-housings-plugs/8201466/
3.  Waveshare 1.5inch RGB OLED Display Module (128x128) - https://www.amazon.co.uk/Waveshare-1-5inch-RGB-OLED-Module/dp/B07DB5YFGW
    * One other option could be https://shop.pimoroni.com/products/inky-impression - currently under evaluation.
4.  2x push buttons - main and secondary, which could have different coloured caps to distinguish them. For example, buttons similar to https://coolcomponents.co.uk/collections/component-buttons/products/tactile-buttons-x4.
5.  NFC reader - TBD
6.  RFID to be read by other badges - TBD
7.  Piezo buzzer - TBD

## Hardware Requirements (E-Ink)

1.  ESP32 board with LiPoly battery connector and charging capability: https://www.olimex.com/Products/IoT/ESP32/ESP32-DevKit-LiPo/open-source-hardware
2.  Battery - for example, https://www.olimex.com/Products/Power/BATTERY-LIPO1400mAh/. mAh is TBD, depending on power requirements. For reference:
    * The battery socket on the board is described as `SMD Header with top entry and 2mm step, with 2P positions`.
    * The battery socket part number used is `CI0102M1VT0-LF` - data sheet is available at https://store.comet.bg/download-file.php?id=4895
    * A connector that would fit into the socket has part number `CI0102S0000` - data sheet is available at https://store.comet.bg/download-file.php?id=2143
    * An RS Components connector that could work is https://uk.rs-online.com/web/p/wire-housings-plugs/8201466/
3.  Pimoroni Inky Impression 7-colour e-ink display: https://shop.pimoroni.com/products/inky-impression
    * Note that this requires 5v for operation! **LiPo batteries may not be able to supply this!** We need to investigate some more.

We could include a slot on the back of the shell for credit or room cards.

## Other Considerations

Other ESP32 boards with batteries:

* [TT-GO T-DISPLAY ESP32 LCD DIY Enthusiast Development Board](https://www.aliexpress.com/item/4000296985840.html?spm=a2g0o.productlist.0.0.5a486445uI9mbz&algo_pvid=e92254e3-2add-4353-8763-6905f6204d17&algo_expid=e92254e3-2add-4353-8763-6905f6204d17-8&btsid=2100bdec16096037741002720e4db9&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_) ($10.02)
* [ESP32_Bat_Pro Battery Charging Breakout and Development Board](https://www.ezsbc.com/product/esp32_bat-battery-charging-pro/) ($13.95)

Other displays:

* [3.5 inch resistive touch screen](https://electropeak.com/3-5-inch-full-color-touch-tft-lcd-for-arduino) ($14.09)
* [2.8 inch TFT LCD](https://shop.pimoroni.com/products/2-8-tft-lcd-with-touchscreen-breakout-board-w-microsd-socket) (£28.20)
* [4 inch LCD](https://shop.pimoroni.com/products/hyperpixel-4-square?variant=30138251477075) (£60 with touch, £54 without)
