// Posiziona un SERVO RC, nello step da 0 a 180.
// Pinout servo: Rosso +, Grigio(nero) GND, giallo SEGNALE.
//
// by De Luigi Matteo
// matteo75fe@tiscali.it
//
// Questo codice sorgente è di pubblico dominio.


#include <Servo.h> 
 
Servo myservo;  // Crea l'oggetto per controllare il servo
                 

int pos = 80;    // Variabile che definisce la posizione del SERVO RC 
                 // valore da 0 a 180.
void setup() 
{ 
  myservo.attach(9);  // Collegare al pin 9 (DGT PWM out), 
                      // il segnale del SERVO RC
} 
 
 
void loop() 
{ 
  
  {                                   
    myservo.write(pos);              // Posiziona allo step "pos" il SERVO
    delay(20);                       // Aspetta 20millisecondi per il posizionamento.
  } 
  
  
} 
// Alla variabile "pos" può essere assegnato un valore compreso 
// da 0 a 180, magari acquisito dal pin A0, come conversione 
// AD di una posizione, temperatura, o altra grandezza fisica.
