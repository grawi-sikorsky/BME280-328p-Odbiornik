#include <VirtualWire.h>

const int receive_pin = 12;
char temperatureChar[10];
char humidityChar[10];
struct package
{
  float temperature = 0.0;
  float humidity = 0.0;
};
typedef struct package Package;
Package data;
void setup()
{
    delay(1000);
    // Initialise the IO and ISR
    vw_set_rx_pin(receive_pin);
    vw_setup(500);   // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
}
void loop()
{
    uint8_t buf[sizeof(data)];
    uint8_t buflen = sizeof(data);
if (vw_have_message())  // Is there a packet for us? 
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    vw_get_message(buf, &buflen);
    memcpy(&data,&buf,buflen);
    Serial.print("\nPackage:");
    Serial.print(data.temperature);
    Serial.print("\n");
    Serial.println(data.humidity);
  }
}