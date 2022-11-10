#include "myHttpClient.h"
myHttpClient::myHttpClient(String url ) {
 this->url = url ; //on mémorise l'url du script à appeler
}
int myHttpClient::post(String postData){
 begin(client,url) ;//the url location
 addHeader("Content-Type", "application/x-www-form-urlencoded");
 httpCode = POST(postData) ;
 return httpCode ;
}
String myHttpClient::getPayload() {
 payload = getString() ;
 return payload ;
}
String myHttpClient::error() {
 return (errorToString(httpCode)) ;
}
void myHttpClient::fin() {
 end() ;
}
