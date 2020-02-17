#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK rf_receiver;

void setup()
{
    Serial.begin(9600);	// Debugging only
    if (!rf_receiver.init())
    {
      Serial.println("init failed");
    }
    else
    {
      Serial.println("init ok");
    }
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (rf_receiver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);         
    }
}