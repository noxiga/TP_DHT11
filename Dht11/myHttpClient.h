#ifndef HttpCLIENT
#define HttpCLIENT
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
class myHttpClient : public HTTPClient // un héritage de la class HTTPClient
{
 private :
 WiFiClient client ;
 int httpCode ;
 String payload ;
 String url ;
 public :
 myHttpClient(String url ) ;
 int post(String data) ;
 String getPayload() ;
 String error() ;
 void fin() ;
};
#endif