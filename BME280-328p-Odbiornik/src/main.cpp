#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <time.h>

Adafruit_INA219 ina219;
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

int reading, reading_avg;
float mA_IOT,mA_100,mA_avg;
float current_time, last_time;

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

    // Initialize the INA219.
    // By default the initialization will use the largest range (32V, 2A).  However
    // you can call a setCalibration function to change this range (see comments).
    ina219.begin();
    
    // To use a slightly lower 32V, 1A range (higher precision on amps):
    //ina219.setCalibration_32V_1A();
    // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
    ina219.setCalibration_16V_400mA();
}
void pomiar_mA()
{
  mA_IOT += ina219.getCurrent_mA();
  reading++;

  if(reading >= 100)
  {
    reading_avg++;

    mA_100 = mA_IOT/100;

    mA_avg += mA_100;
    float tmp;
    tmp = mA_avg/reading_avg;

    Serial.print("Current / 100 : "); Serial.println(mA_100);
    Serial.print("Current / avg : "); Serial.println(tmp); Serial.println();
    mA_100 = mA_IOT = 0;
    reading = 0;
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
    delay(5);
    Serial.print("Message: ");
    Serial.println((char*)buf);
    digitalWrite(13,LOW);
  }

  delay(10);
  pomiar_mA();

  //current_mA = ina219.getCurrent_mA();

  //Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  //Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  //Serial.println("");
  
}