# TronCMD
In programming lessons at university we where writing a game for an ATMega32 using a gamepad on the controller port and a serial console as display. I continued work at home and since I don't have an ATMega32 laying around I tested the developed concepts in terminal before we are implementing them in Atmel Studio.
Therefore the need for a bit-map, cause microcontroller space is really limited...

The game currently only works in Unix terminals supporting [VT100](http://www.termsys.demon.co.uk/vtansi.htm) escape sequences (Windows and [WSL](https://docs.microsoft.com/de-de/windows/wsl/faq) definitley don't work...).
