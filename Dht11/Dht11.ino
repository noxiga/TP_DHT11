#include "Wifi.h"
#include "Lcd.h"
#include "DHT11.h"
#include "myHttpClient.h"

#ifndef STASSID
#define STASSID "######"" // nom du réseau
#define STAPSK "#######" // mot de passe du réseau
#endif

using namespace std;

const char* ssid = STASSID ;
const char* password = STAPSK ;
const char* url = "http://127.0.0.1:5500/DHT11/PHP/register.php" ; // url du script php sur la station de travail

// les constantes
#define DHT11_PIN 2 // 2 avec ESP8266
#define DHTTYPE DHT11 // DHT 11
#define cristalAddress 0x27

// les variables GLOBALES et pointeurs
DHT11_ *dht ; // pointeur sur un objet DHT11_
LCD *lcd ; // pointeur sur un objet LCD
myHttpClient *http ; // pointeur sur un objet myHttpClient 

float temperature;
float humidite;

void setup()
{
  Serial.begin(115200);
  Serial.println("Debut du programme");
  // ****************************************
  // We start by connecting to a WiFi network
  // ****************************************
  Serial.print("Connecting to ") ;
  Serial.println(ssid) ;
  Wifi *wifi = new Wifi(ssid,password) ;

  dht = new DHT11_(DHT11_PIN, DHTTYPE);
  lcd = new LCD(cristalAddress, 2, 16);
  lcd -> allumeEcran() ;
  lcd -> activeRetroEclairage();

  http = new myHttpClient("http://########/DHT11/PHP/register.php"); // adresse IP du PC qui contient les fichiers à la place de #######
}

void loop()
{
  float t= dht -> lireTemperature(); 
  float h= dht -> lireHumidite(); 
  lcd -> afficheOneLine((String) t + " Celsius", 0);
  lcd -> afficheOneLine((String) h + " %", 1);
  http ->post("Temperature="+String(t)+"&Humidite="+String(h)) ;
  Serial.println(http ->getPayload());
  delay(30000);    
  
}
