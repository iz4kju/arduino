#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


      int analogInput = 0;     //analog pin A0
      float VoltageOut = 0.0;
      float VoltageIn = 0.0;
      int refresh = 50;        //refresh rate
      int i = 0;               //variable used for clearing our byte 'graph'
      int value = 0;           //variable to store value
      byte graph[8] =
        {
          B11111,
          B11111,
          B11111,
          B11111,
          B11111,
          B11111,
          B11111,
          B11111,
        };
     
    void setup()
    {
      pinMode(analogInput, INPUT);  //setting analog pin mode to input
     
      lcd.begin(16, 2);             //setting up the LCD screens rows and colums
      lcd.print("V=");        
    }
     
    void loop(){
      value = analogRead(analogInput);  //reading the value on A1
     
      //VoltageOut = (value * 5.0) / 1024.0;
      VoltageIn = (value * 5.0) / 1024.0;
      //VoltageOut / (R2/(R1+R2));  
     
      lcd.setCursor(3, 0);               //printing the result to the LCD display
      lcd.print(VoltageIn);
      lcd.print("  IZ4KJU");
      delay(refresh);                    //refreshing the screen
     
      voltmetergraph();                  //calling my function voltmetergraph
    }
     
    void voltmetergraph()
      {
        if (VoltageIn >= 0.3125)         //setting up the bar graph
        {
        lcd.createChar(0, graph);
        lcd.setCursor(0, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(0);}  
       
       if (VoltageIn >= 0.625)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(1, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(1);}  
       
        if (VoltageIn >= .9375)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(2, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(2);}
       
        if (VoltageIn >= 1.25){
        lcd.createChar(0, graph);
        lcd.setCursor(3, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(3);}
       
       if (VoltageIn >= 1.5625)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(4, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(4);}
       
       if (VoltageIn >= 1.875)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(5, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(5);}
       
       if (VoltageIn >= 2.1875)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(6, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(6);}
       
        if (VoltageIn >= 2.5)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(7, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(7);}
       
        if (VoltageIn >= 2.8125)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(8, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(8);}
       
       if (VoltageIn >= 3.125)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(9, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(9);}
       
       if (VoltageIn >= 3.4375)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(10, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(10);}
       
       if (VoltageIn >= 3.75)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(11, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(11);}
       
       if (VoltageIn >= 4.0625)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(12, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(12);}
       
       if (VoltageIn >= 4.375)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(13, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(13);}
       
        if (VoltageIn >= 4.6875)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(14, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(14);}
       
        if (VoltageIn >= 4.99)
        {
        lcd.createChar(0, graph);
        lcd.setCursor(15, 2);
        lcd.write(byte(0));}
        else {LcdClearByte(15);}
      }
     
     void LcdClearByte(int c)        //clearbyte function
    {
      lcd.setCursor(c,1);
      for (i = 0; i < 16; i = i + 1) {
        lcd.print(" ");
      }
    }


