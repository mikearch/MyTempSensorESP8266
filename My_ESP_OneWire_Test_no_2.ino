.

#include <OneWire.h>
#include <DallasTemperature.h>






#define ONE_WIRE_BUS D4


OneWire oneWire(ONE_WIRE_BUS);

 
DallasTemperature sensors(&oneWire);

DeviceAddress insideThermometer = {0x28, 0xFF, 0xA8, 0xE9, 0x80, 0x14, 0x02, 0x96  };;
 

void setup(void)
{
  
  Serial.begin(9600); 

  Serial.println("Dallas Temperature IC Control Library Demo");
  
 
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  
  sensors.setResolution(insideThermometer, 9);
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
  Serial.println();
}
    void printTemperature(DeviceAddress deviceAddress)
{
    float tempC = sensors.getTempC(deviceAddress);
    Serial.print("Temp C: ");
    Serial.print(tempC);
    Serial.print(" Temp F: ");
    delay (1000);
    Serial.println(DallasTemperature::toFahrenheit(tempC)); 
  }
  
    void loop(void)
  { 

    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); 
    Serial.println("DONE");
    
    
    printTemperature(insideThermometer); 
    delay (1000);
  }
  
  // function to print a device address
     void printAddress(DeviceAddress deviceAddress)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
   
    }
  }

