#include <SPI.h>
#include <Wire.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_BMP280.h>



Adafruit_BMP280 bmp; // I2C




//RF24 radio(12, 14, 26, 25, 27);
RF24 radio(4, 5);
const uint64_t address = 0xF0F0F0F0E1LL;
int counter = 0; 

 
String data = "reza!!!!!!!!";
 
void setup() 
{
Serial.begin(115200);

while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
   
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
                  



radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter 
}
 
void loop()
{
   
  Serial.println();
  
  radio.write(&data, sizeof(16));
  
  Serial.println("Data Packet Sent");
  Serial.println("");
  
  counter++;
  data = String(bmp.readTemperature());



  Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
  

  
 

 
  delay(500);

}
