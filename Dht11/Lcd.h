#ifndef _LCD
#define _LCD
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
class LCD : public LiquidCrystal_I2C { // un héritage de la class arduino : LiquidCrystal_I2C
 private:
 String message ; // ne sert à rien ici
 public:
 LCD(int address, int lineNumber,int digitNumber) ;
 void activeRetroEclairage() ;
 void deactiveRetroEclairage() ;
 void afficheSansTroncature(String message) ;
 void afficheOneLine(String,int line=0) ;
 void eteintEcran() ;
 void allumeEcran() ;
 void effaceEcran() ;
};
#endif