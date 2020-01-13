# cosmos

This software implements in AVR Atmega328 microcontroller a driver for monocrome 16*x8 display with horizontal animation, 
for 0-1 and A-Z characters.

The display is based on shift registers, that trigger transistors and power up desired LEDs. 

In any moment, the content for display can be sent by the user over an Serial communication and it is saved in EEPROM memory (non volatile).

After this, the display automatically generate the wished content characters and scroll it horizontally.

