#include "DHT11.h"

DHT11_::DHT11_(int dhtPin, int DHTTYPE) :DHT(dhtPin, DHTTYPE)
{
  begin();
}
float DHT11_::lireTemperature()
{
temperature = readTemperature();
return temperature;
}
float DHT11_::lireHumidite()
{
humidite = readHumidity();
return humidite;
}