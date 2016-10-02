byte displaymap[2][16]=
{
  {
    0b10111101,
    0b10111100,
    0b10011101,
    0b10011100,
    
    0b11101101,
    0b11101100,
    0b11001101,
    0b11001100, 
    
    0b11111001,
    0b11111000,
    0b11011001,
    0b11011000,

    0b11110101,
    0b11110100,
    0b11010101,
    0b11010100
  },
  {
    0b00111111,
    0b00111110,
    0b00011111,
    0b00011110,
    
    0b01101111,
    0b01101110,
    0b01001111,
    0b01001110, 
    
    0b01111011,
    0b01111010,
    0b01011011,
    0b01011010,

    0b01110111,
    0b01110110,
    0b01010111,
    0b01010110
  }
};

void writeChar(int x, int y,int chr)
{
  uint8_t output=8;
  uint8_t address=displaymap[y][x];
  shift.batchWriteBegin();
  for ( uint8_t bitMask = 1 ; bitMask <= 128; bitMask <<=   1) {
    if (address&bitMask){
      shift.writeBit(output,HIGH);
      //digitalWrite(output,HIGH);
    } else {
      //digitalWrite(output,LOW);
      shift.writeBit(output,LOW);
    }
    output++;
  }
  shift.batchWriteEnd();
  
  //shiftOut(0,2,LSBFIRST,displaymap[y][x]);
  /*for (uint8_t i = 0; i<8 ; i++){
    digitalWrite(output++,displaymap[y][x][i]);
  }
  */
  //digitalWrite(14,HIGH);
  //delay(1);
  //digitalWrite(14,LOW);
  //delay(1);
  shift.batchWriteBegin();
  
  output = 0;
  for ( uint8_t bitMask = 1 ; bitMask <= 64; bitMask <<=   1) {
    if ( chr & bitMask ) {
      //Serial.print('1');
      shift.writeBit(output,HIGH);
    } else {
      //Serial.print('0');
      shift.writeBit(output,LOW);
    }
    output++;
  }
  shift.batchWriteEnd();
  delay(5);
  shift.writeBit(7,LOW);
  delay(1);
  shift.writeBit(7,HIGH);
  
  
  /*digitalWrite(9,LOW);
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
  */
}

void writeString(uint8_t x, uint8_t y, const char string[], uint8_t len)
{
  for (uint8_t i= 0; x <16&&i <len; i++)
  {
    writeChar(x++,y,*(string++));
  }
}

