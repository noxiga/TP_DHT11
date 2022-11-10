#ifndef DHT11__
#define DHT11__
#include <DHT.h>
//#include <PString.h>
class DHT11_: public DHT { // Héritage de la class DHT
 private :
 float temperature ;
 float humidite ;
  public:
 DHT11_(int dhtPin,int DHTTYPE) ;
 float lireTemperature() ;
 float lireHumidite() ;

};
#endif