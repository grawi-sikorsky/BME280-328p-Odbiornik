#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <avr/power.h>

RH_ASK rf_receiver(2000,11,12,3,true);

void setup()
{
  //clock_prescale_set(clock_div_1);
  pinMode(13,OUTPUT);
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
    uint8_t buf[2];
    uint8_t buflen = sizeof(buf);
    if (rf_receiver.recv(buf, &buflen)) // Non-blocking
    {
      // Message with a good checksum received, dump it.
      digitalWrite(13,HIGH);
      delay(50);
      Serial.print("Message: ");
      Serial.println((char*)buf);
      digitalWrite(13,LOW);
    }
}