
c:\users\tungbt\.platformio\packages\tool-avrdude\avrdude.exe -v -patmega328p -cstk500v1 -PCOM8 -b19200 -e   -u -F -U flash:w:hw-firmware.hex:i


rem -Uhfuse:w:0xde:m -Ulfuse:w:0xff:m -Uefuse:w:0x05:m 