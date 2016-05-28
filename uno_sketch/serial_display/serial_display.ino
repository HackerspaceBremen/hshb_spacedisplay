
#include <Wire.h>
uint8_t displaymap[2][16][8] = {
  {
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0},
    
    {1, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 1, 1, 0, 0}, 
    
    {1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 0, 0, 0},

    {1, 1, 1, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 1, 0, 0},
    {1, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 0, 1, 0, 1, 0, 0}
  },
  {
    {0, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 0},
    
    {0, 1, 1, 0, 1, 1, 1, 1},
    {0, 1, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 1, 1, 1, 1},
    {0, 1, 0, 0, 1, 1, 1, 0}, 
    
    {0, 1, 1, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 1, 1},
    {0, 1, 0, 1, 1, 0, 1, 0},

    {0, 1, 1, 1, 0, 1, 1, 1},
    {0, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 0, 1, 0, 1, 1, 1},
    {0, 1, 0, 1, 0, 1, 1, 0}
  }
};
char teststring[16]={'O','f','f','e','n','e',' ','m','i','k','r','o','-',0x7f,0x7f,0x7f};

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(64);
  
  int i=0;
  for (i=2;i<=8;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  digitalWrite(7,HIGH);
  for (i=9;i<=13;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  
  pinMode(A0,OUTPUT);
  digitalWrite(A0,HIGH);
  pinMode(A1,OUTPUT);
  digitalWrite(A1,HIGH);
  pinMode(A2,OUTPUT);
  digitalWrite(A2,HIGH);
  pinMode(A3,OUTPUT);
  digitalWrite(A3,HIGH);
  //pinMode(A5,OUTPUT);
  //digitalWrite(A5,HIGH);
  //digitalWrite(A5,LOW);
  delay(20);
  clear();
  /*for (uint8_t i= 0; i <16; i++){
      writeChar(i,0,teststring[i]);
  }
  */
}

void loop()
{
  
  //serialEvent();
  /*for (uint8_t i=0;i<4;i++){
    writeChar(0,0,teststring[i]);
    delay(1);
  }*/
  /*
  char buf[128];
  char *xpos, *ypos, *p, *payload;
  uint8_t x, y;
  
  inputString.toCharArray(buf,inputString.length());
  if (stringComplete) {
    if(inputString.charAt(0)=='W'){
      strtok_r(buf,"\t",&p);
      xpos = strtok_r(NULL,"\t",&p);
      x = atoi(xpos);
      ypos = strtok_r(NULL,"\t",&p);
      y = atoi(ypos);
      payload =strtok_r(NULL,"\t",&p);
      writeString(x,y,payload,strlen(payload));
    }else if(inputString.charAt(0)=='C'){
      strtok_r(buf,"\t",&p);
      xpos = strtok_r(NULL,"\t",&p);
      x = atoi(xpos);
      ypos = strtok_r(NULL,"\t",&p);
      y = atoi(ypos);
      writeChar(x,y,' ');
    }
    
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  */
  delay(50);
}

void writeChar(int x, int y,int chr)
{
  uint8_t output=10;
  for (uint8_t i = 0; i<8 ; i++){
    digitalWrite(output++,displaymap[y][x][i]);
  }
  delay(1);
  digitalWrite(9,LOW);
  output = 2;
  for ( uint8_t bitMask = 64 ; bitMask != 0; bitMask = bitMask >> 1) {
    if ( chr & bitMask ) {
      //Serial.print('1');
      digitalWrite(output,HIGH);
    } else {
      //Serial.print('0');
      digitalWrite(output,LOW);
    }
    output++;
  }
  delay(1);
  digitalWrite(9,HIGH);
  delay(1);
}

void writeString(uint8_t x, uint8_t y, char string[], uint8_t len)
{
  for (uint8_t i= 0; x <16&&i <len; i++)
  {
    writeChar(x++,y,string[i]);
  }
}


void clear()
{
  //datenbits setzen
  int i=0;
  for (i=2;i<=8;i++){
    digitalWrite(i,LOW);
  }
  digitalWrite(7,HIGH);

  //alle NAND-Eingaenge aktivieren
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(13,LOW);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  //Write-Enable setzen
  digitalWrite(9,LOW);
  delay(1);
  //mux-ausgang 1
  digitalWrite(A3,HIGH);
  digitalWrite(12,HIGH);
  delay(1);
  //mux-ausgang 2
  digitalWrite(A3,LOW);
  digitalWrite(12,HIGH);
  delay(1);
  //mux-ausgang 3
  digitalWrite(A3,HIGH);
  digitalWrite(12,LOW);
  delay(1);
  //mux-ausgang 4
  digitalWrite(A3,LOW);
  digitalWrite(12,LOW);
  delay(1);

  //alles rücksetzen
  digitalWrite(9,HIGH); //write-enable aus

  //mux-addresspins
  digitalWrite(A3,HIGH);
  digitalWrite(12,HIGH);

  //NAND-Eingaenge loeschen
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);

  digitalWrite(7,LOW); //datenbit loeschen
}





/*
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      //Serial.print(inputString);
      //Serial.println();
    }
    
  }
}
*/
void receiveEvent(int howMany) {
  uint8_t cmd=(uint8_t)Wire.read();
  uint8_t inChar, i, addr;
  switch (cmd){
    case 0x01:
      clear();
      Serial.println("Display cleared!");
    break;
    case 0x02:
      uint8_t x, y;
      i=0;
      x=0;
      y=0;
      inputString = "";
      if (Wire.available()==32){
        while (Wire.available()) {
          inChar = (uint8_t)Wire.read();
          /*
          x= i % 16;
          y= i / 16;
          writeChar(x,y,inChar);
          */
          writeChar((i % 16),(i / 16),inChar);
          if(i==16){
            inputString += "\n";
          }
            inputString += inChar;
          i++;
        }
        Serial.println("Display contents:");
        Serial.println(inputString);
        Serial.println("--End of Display--");
      }
    break;
    
    case 0x03:
      addr=(uint8_t)Wire.read();
      inChar = (uint8_t)Wire.read();
      writeChar((addr % 16),(addr / 16),inChar);
      Serial.println("Character changed :");
      Serial.print("  Row: ");
      Serial.println((addr / 16));
      Serial.print("  Column: ");
      Serial.println((addr % 16));
      Serial.print("  New char: ");
      Serial.println(inChar);
    break;

    case 0x10:
      if (Wire.available()==16){
        inputString = "";
        i=0;
        while (Wire.available()) {
          inChar = (uint8_t)Wire.read();
          /*
          x= i % 16;
          y= i / 16;
          writeChar(x,y,inChar);
          */
          writeChar(i,0,inChar);
          inputString += inChar;
          i++;
        }
        Serial.println("Display line 0 contents:");
        Serial.println(inputString);
        Serial.println("--End of Display--");
      }
    break;
    case 0x11:
      if (Wire.available()==16){
        inputString = "";
        i=0;
        while (Wire.available()) {
          inChar = (uint8_t)Wire.read();
          /*
          x= i % 16;
          y= i / 16;
          writeChar(x,y,inChar);
          */
          writeChar(i,1,inChar);
          inputString += inChar;
          i++;
        }
        Serial.println("Display line 1 contents:");
        Serial.println(inputString);
        Serial.println("--End of Display--");
      }
    break;
  }
  /*
  while (Wire.available()) {
    // get the new byte:
    char inChar = (char)Wire.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
  }
  stringComplete = true;
  Serial.print("Received ");
  Serial.print(howMany);
  Serial.println(" bytes.");
  Serial.print("Contents: ");
  Serial.println(inputString);
  */
}
