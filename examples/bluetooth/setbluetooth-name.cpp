
#include <Arduino.h>

#include "SoftwareSerial.h"


//  readPort.println("$$$");

//   // set leabot name
//   readPort.print("\r\nAT+NAMELB741885-Y\r\n");
//   // //  readPort.setDebug(true);
//   readPort.flush();
char buffer[100];
int bufferIndex = 0;
int countLine = 0;
SoftwareSerial bluetooth(PIND2, PIND3); // rx,tx
#define readPort bluetooth

String fromPC = "";
void setup()
{
  Serial.begin(115200);
  readPort.begin(115200);
  delay(1000);

}

void loop()
{
  if (readPort.available())
  {
    // while (bluetooth.available())
    { // While there is more to be read, keep reading.
      Serial.print((char)readPort.read());
    }
  }

  // Read from PC
  if (Serial.available())
  {
    delay(10); //
    fromPC = (char)Serial.read();

    readPort.print(fromPC); // show the HC-06 responce
    Serial.print(fromPC);    // echo it back to the PC
  }
  //   PT_SCHEDULE(buttonThread(&ptButton));
}