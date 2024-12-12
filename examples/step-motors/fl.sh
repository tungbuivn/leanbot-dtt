#!/bin/bash
avrdude -Pusb -v -p atmega328p -C /home/tungbt/.platformio/packages/tool-avrdude/avrdude.conf -c arduino -b 115200 -D -P /dev/ttyUSB0 -U flash:w:.pio/build/nanoatmega328/firmware.hex:i -F