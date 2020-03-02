Requirements
============

## Behavioural Requirements Overview

### Phase 1 (Core Functionality)

* Display main character image and main scrolling message.
* Temporarily display character information when requested: name, species, social media handle. Once finished displaying this information, fall back to displaying the main image and message.
* Display battery status at all times.
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

## Hardware Requirements

1.  ESP32 board - exact model TBD, depends on eventual requirements. Will require LiPoly battery connector + charging capability.
2.  Battery - for example, https://www.amazon.co.uk/gp/product/B07CYMYMS9. mAh is TBD, depending on power requirements.
3. Waveshare 1.5inch RGB OLED Display Module (128x128) - https://www.amazon.co.uk/Waveshare-1-5inch-RGB-OLED-Module/dp/B07DB5YFGW
4.  2x push buttons - main and secondary, which could have different coloured caps to distinguish them. For example, buttons similar to https://coolcomponents.co.uk/collections/component-buttons/products/tactile-buttons-x4.
5.  NFC reader - TBD
6.  RFID to be read by other badges - TBD
7.  Piezo buzzer - TBD
