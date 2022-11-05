# AVR LED Display

This software implements in AVR Atmega328 microcontroller a driver for monocrome 8xN display for ASCII characteres, with horizontal animation.


## Electronical Configuration
The display is based on shift registers, that trigger transistors and power up desired LEDs.<br> 
The Data, Shift and Query pins is defined in **definitions.h** file, and can be customized.<br>
You can check the Proteus simulation archive with all components and wiring configuration of this project in the **proteus_simulation** folder.

## Setting the text message
In any moment, the content for display can be sent by the user over an Serial communication and it is saved in EEPROM memory (non volatile).

After this, the display automatically generate the wished content characters and scroll it horizontally.

## DEMO
<p align='center'><image src='assets/demo.gif'/></p>


