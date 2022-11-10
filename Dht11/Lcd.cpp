#include "Lcd.h"
LCD::LCD(int address, int lineNumber,int digitNumber): LiquidCrystal_I2C(address, digitNumber,
lineNumber){
 init();
}
void LCD::activeRetroEclairage() {
 backlight() ;
}
void LCD::deactiveRetroEclairage() {
 noBacklight() ;
}
void LCD::afficheOneLine(String message,int lineNumber) {
 // si la ligne se termine par un espace,
 message.trim() ; //on le supprime car inutile
 int length = message.length() ;
 if(lineNumber ==0)
 clear() ;
 //cas du message de longueur <= 16 (cas normal)
 if(length<=16){
 backlight() ;
 setCursor(0,lineNumber) ;
 print(message.c_str()) ;
 }
 else{
 clear() ;
 setCursor(0,0) ;
 afficheOneLine("Message trop") ;
 afficheOneLine("long !!",1) ;
 }
}
void LCD::afficheSansTroncature(String message) {
 String Words[16] ; // attention à ne pas vouloir réserver trop d'espace (limité sur arduino!)
 int length = message.length() ;

 // ***********************************************
 // Si le message fait moins de 16 caractères
 // ***********************************************
 if(length<=16 ) // Le message tient sur une seule ligne
 afficheOneLine(message.c_str()) ;

 // ***********************************************
 // Le message peut peut-être tenir sur deux lignes
 // ***********************************************
 else {
 // ***********************************************
 // Décomposons le message en mots.
 // tous les mots seront rangés dans le tableau de String Words
 // ***********************************************
 char *pWord ;
 int nbWords = 0 ;
 pWord = strtok((char*)message.c_str()," ,:;/-") ;
 while(pWord!=NULL)
 {
 Words[nbWords] = String(pWord) ;
 nbWords++ ;
 pWord = strtok(NULL," ,:;/-") ;
 }
 // ***********************************************
 // recherche des mots qui vont composer la première ligne
 // il y en aura "nbFirstLineWords"
 // ***********************************************
 length = 0 ;
 int nbFirstLineWords =0 ;
 do {
 // Serial.println(Words[nbFirstLineWords]);
 length+= Words[nbFirstLineWords].length()+1 ;// espace entre les mots
 if(length <=17) // 17 car l'espace à la suite du dernier mot sera supprimé
 nbFirstLineWords++ ;
 } while (length<=17 && (nbFirstLineWords<nbWords) ) ;
 // ***********************************************
 // affichage des mots de la première ligne
 // ***********************************************
 String firstLineMessage = "" ;
 for(int i=0 ; i<nbFirstLineWords ; i++)
 firstLineMessage+= Words[i]+ " " ;
 afficheOneLine(firstLineMessage,0) ;

 // ***********************************************
 // recherche des mots qui vont composer la seconde ligne
 // mais avant tout, vérifions quand même qu'il reste des mots à afficher
 // car après avoir enlevé les espaces et autres caractères de ponctuation,
 // il se peut que le message tienne sur une seule ligne
 // ***********************************************
 if(nbFirstLineWords<nbWords) {
 length = 0 ;
 int nbSecondLineWords=nbFirstLineWords ;
 while ( (length<=17) && (nbSecondLineWords<nbWords) ) {
 length+= Words[nbSecondLineWords].length()+1 ;
 if(length <=17)
 nbSecondLineWords++ ;
 }
 // ***********************************************
 // Mais il se peut également que le message ne puissent pas s'afficher complètement
 // à l'aide de la seconde ligne de l'afficheur
 // ***********************************************
 if(nbSecondLineWords<nbWords) // si l'on n'arrive pas à placer tous les mots sur l'afficheur
 {
 afficheOneLine ("Message trop long") ; // affichera "Message trop long"
 }
 else{
 // affichage des mots de la seconde ligne
 String secondLineMessage = "" ;
 for(int i=nbFirstLineWords ; i<nbSecondLineWords ; i++)
 secondLineMessage+= Words[i]+ " " ;
 afficheOneLine(secondLineMessage,1) ;
 }
 }
 }
}
void LCD::eteintEcran() {
 noDisplay() ;
}
void LCD::allumeEcran() {
 display() ;
}
void LCD::effaceEcran() {
 clear() ;
}