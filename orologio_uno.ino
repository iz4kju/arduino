/*
 orologio_uno.ino
 Il programma mostra il funzionamento del modulo
 Modulo Real Time Clock DS1307 della SparkFun
 mostrando ora e data sul modulo LCD KeyPad della Homotix.
 Attenzione: verificare la corrispondenza dei pin del vostro modulo display
 
 Vengono utilizzati i seguenti pin
 Pin +5V         -> +5V (LCD e DS1307)
 Pin GND         -> GND (LCD e DS1307)
 Pin Vin         -> +9V Batteria
 Pin Digital 13  -> Bus D4 dati LCD
 Pin Digital 12  -> Bus D5 dati LCD
 Pin Digital 11  -> Bus D6 dati LCD
 Pin Digital 10  -> Bus D7 dati LCD
 Pin Digital 7   -> terminale RS display LCD
 Pin Digital 8   -> terminale EN display LCD
 Pin Digital 9   -> attivazione retroilluminazione
 
 Pin Analogic 4  -> SDA DS1307 Sparkfun
 Pin Analogic 5  -> SCL DS1307 Sparkfun
 
 Creato il 07/07/2012
 Modificato il 31/3/2015
 da Adriano Gandolfo <http://www.adrirobot.it>
 This example code is in the public domain.
 */

#include <Wire.h>          // Per gestione comunicazione I2C
#include <LiquidCrystal.h> // Per gestione modulo LCD
#define DS1307_I2C_ADDRESS 0x68


// Selezione dei pin utilizzati dal display LCD
// Sintassi LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(7, 8, 13, 12, 11, 10);

int backLight = 9; // per controllo retroilluminazione LCD

// Conversione normali numeri decimali in binario decimale
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
// Conversione decimale binario a normali numeri decimali
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}
/* 
 1) Imposta la data e l'ora del DS1307
 2) Avvia l'orologio
 3) Imposta la modalità di ora in orologio a 24 ore
 */
void setDateDs1307(byte second, // 0-59
byte minute, // 0-59
byte hour, // 1-23
byte dayOfWeek, // 1-7
byte dayOfMonth, // 1-28/29/30/31
byte month, // 1-12
byte year) // 0-99
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second)); // 0 to bit 7 avvia l'orologio
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(0x10); // invia 0x10 (hex) 00010000 (binario) al registro di controllo - si attiva ad onda quadra
  Wire.endTransmission();
}
// Ottiene la data e l'ora dal DS1307
void getDateDs1307(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  // Ripristina il puntatore del registro
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  // Alcuni di questi sono necessari, perché le maschere di alcuni bit sono bit di controllo
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f); // Occorre modificare questo se 12 ore am/pm
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void setup()
{
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // attiva la retroilluminazione

  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  Wire.begin();
  Serial.begin(9600);
 /*
 Modificare i successivi valori se si desidera impostare l'orologio.
 Occorre attivare la linea setDateDs1307 una volta quindi rimuovere
 la chiamata.
 */
  second = 0;
  minute = 56;
  hour = 11;
  dayOfWeek = 7;
  dayOfMonth = 21;
  month = 03;
  year = 15;

//  setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
  
  lcd.begin(16, 2); // Imposta le dimensioni dell'LCD

}
void loop()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  lcd.clear(); // Pulisce lo schermo LCD
  lcd.setCursor(0,0);
  lcd.print(" ");
  lcd.print(hour, DEC);
  lcd.print(":");
  if (minute<10)
  {
    lcd.print("0");
  }
  lcd.print(minute, DEC);
  lcd.print(":");
  if (second<10)
  {
    lcd.print("0");
  }
  lcd.print(second, DEC);
  lcd.setCursor(0,1);
  lcd.print(" ");
  switch(dayOfWeek){
  case 1:
    lcd.print("Dom");
    break;
  case 2:
    lcd.print("Lun");
    break;
  case 3:
    lcd.print("Mar");
    break;
  case 4:
    lcd.print("Mer");
    break;
  case 5:
    lcd.print("Gio");
    break;
  case 6:
    lcd.print("Ven");
    break;
  case 7:
    lcd.print("Sab");
    break;
  }
  lcd.print(" ");
  lcd.print(dayOfMonth, DEC);
  lcd.print("/");
  lcd.print(month, DEC);
  lcd.print("/20");
  lcd.print(year, DEC);
  delay(1000);
} 

