Clone existing board code
```powershell
&"${env:HOMEDRIVE}${env:HOMEPATH}\.platformio\packages\tool-avrdude\avrdude.exe" -p atmega328p -c arduino -P com8 -U flash:r:board.hex:i
```

flast hex file
```powershell   
&"${env:HOMEDRIVE}${env:HOMEPATH}\.platformio\packages\tool-avrdude\avrdude.exe" -p atmega328p -c arduino -P com8 -U flash:w:board.hex:i
```


## reading fuse values
avrdude.exe -v -patmega328p -cstk500v1 -PCOM8 -b19200 -U lfuse:r:low_fuse_val.txt:h -U hfuse:r:high_fuse_val.txt:h -U efuse:r:ext_fuse_val.txt:h -u -F

## flash bootloader in Arduino as ISP

## nano board

avrdude "-C${env:HOMEDRIVE}${env:HOMEPATH}\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf" -v -patmega328p -cstk500v1 -PCOM8 -b19200 -e  -u -F -U flash:w:ATmegaBOOT_168_atmega328.hex:i


## nano new board



steppers pin: 

D4 : right dir
D5 : right step
D6 : left step
D7 : left dir