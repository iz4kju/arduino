#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
//inizializzazione display con shield DFROBOT
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

String callsign = "iz4kju";  // <-- parametro da modificare
// MAC Address della scheda ethernet
byte mac[] = {
  0xDE, 0xAA, 0xFF, 0xAF, 0xFE, 0xED
};
// ip della scheda
IPAddress ip(192, 168, 1, 49); // <-- parametro da modificare
// ip del server con i cluster
IPAddress server(144, 76, 158, 174);
// dati della rete locale
IPAddress gateway(192, 168, 1, 254); // <-- parametro da modificare
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);

int passo = 0;
int timeout = 0;
int login = 0;
int caratteri = 0;
int lettere = 0;
EthernetClient client;

void setup() {
  // calcolo delle lettere nel nominativo
  lettere = callsign.length();
  // definizione del display
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.print("IZ4KJU");
  lcd.setCursor(1, 1);
  lcd.print("DX Spot Client");
  // inizializzazione scheda ethernet
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  // inizializazione porta seriale
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // attendo che la scheda ethernet sia pronta
  delay(10000);
  Serial.println("connecting...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connessione...");
  
  // connessione al server DXFUN con porta 8000
  if (client.connect(server, 8000)) {
    lcd.clear();
    Serial.println("connected");
    lcd.print("Connesso");
    delay(1000);
    lcd.clear();

  } else {
    Serial.println("connection failed");
    lcd.clear();
    lcd.print("Errore");
  }
  lcd.noAutoscroll();
}

void loop() {
  // ricevi tutti i dati provenienti dalla porta seriale
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
    // azzero il timer di timeout ogni volta che ricevo un carattere (mi serve per autenticarmi)
    timeout = 0;
    // se il carattere è un invio allora riporta a capo il cursore
    if (c == char(13) || c == char(10)) {
      lcd.setCursor(0, 0);
      caratteri = 0;
    } else if (caratteri < 32) {
    // altrimenti se ho scritto meno caratteri della dimensione massima del display scrivi ciò che arriva
      if (caratteri == 16) {
      // se ho finito la prima riga passa alla seconda
        lcd.setCursor(0, 1);
      }
      // scrivi il carattere ricevuto
      lcd.print(c);
      // incrementa il contatore dei caratteri ricevuti
      caratteri = caratteri + 1;
    }
  }

  if (timeout <= 200) {
    // attendo la richiesta di login
    timeout = timeout + 1;
  }  else if (login == 0) {
     //se non mi sono ancora loggato allora invio il mio nominativo
      client.println(String(callsign));
      login = 1;
  }


  // se il server si disconnette allora chiudi la connessione
  if (!client.connected()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Disconnesso");
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing:
    while (true);
  }
  delay(10);
}



