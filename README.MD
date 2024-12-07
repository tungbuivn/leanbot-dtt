Dump boot loader
```powershell
&"${env:HOMEDRIVE}${env:HOMEPATH}\.platformio\packages\tool-avrdude\avrdude.exe" -p atmega328p -c arduino -P com8 -U flash:r:board.hex:i
```

&"${env:HOMEDRIVE}${env:HOMEPATH}\.platformio\packages\tool-avrdude\avrdude.exe" -p atmega328p -c arduino -P com8 -U flash:w:ATmegaBOOT_168_atmega328.hex:i


## reading fuse values
avrdude.exe -v -patmega328p -cstk500v1 -PCOM8 -b19200 -U lfuse:r:low_fuse_val.txt:h -U hfuse:r:high_fuse_val.txt:h -U efuse:r:ext_fuse_val.txt:h -u -F

avrdude "-CC:\Users\tungbt\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf" -v -patmega328p -cstk500v1 -PCOM8 -b19200 -e -Ulock:w:0x3F:m -Uefuse:w:0x80:m -Uhfuse:w:0xDE:m -Ulfuse:w:0xFF:m  -u -F

usbasp


steppers pin: 

D4 : right dir
D5 : right step
D6 : left step
D7 : left dir