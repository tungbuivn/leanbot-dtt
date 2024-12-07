
#include <Arduino.h>

#define readPort Serial

void setup()
{
 
  readPort.begin(115200);
  readPort.println("test hello");
}

void loop()
{
  while (readPort.available())
  { // While there is more to be read, keep reading.
    readPort.print((char)readPort.read());
  }
}