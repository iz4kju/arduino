

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define backLight     13

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define DS1307_I2C_ADDRESS 0x68




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
//void setDateDs1307(byte second, // 0-59
//byte minute, // 0-59
//byte hour, // 1-23
//byte dayOfWeek, // 1-7
//byte dayOfMonth, // 1-28/29/30/31
//byte month, // 1-12
//byte year) // 0-99
//{
  //Wire.beginTransmission(DS1307_I2C_ADDRESS);
  //Wire.write(0);
  //Wire.write(decToBcd(second)); // 0 to bit 7 avvia l'orologio
  //Wire.write(decToBcd(minute));
  //Wire.write(decToBcd(hour));
  //Wire.write(decToBcd(dayOfWeek));
  //Wire.write(decToBcd(dayOfMonth));
  //Wire.write(decToBcd(month));
  //Wire.write(decToBcd(year));
  //Wire.write(0x10); // invia 0x10 (hex) 00010000 (binario) al registro di controllo - si attiva ad onda quadra
  //Wire.endTransmission();
//}
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

