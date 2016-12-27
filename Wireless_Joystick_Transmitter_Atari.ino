


//DB9 (8=GND, 7=VCC):               1   2   3   4   5   6   7   8   9
const uint8_t inputPinsPort1[] =  { 5,  6,  7,  8,  0,  4,  0,  0,  0};
//const uint8_t inputPinsPort2[] =  {10, 16, 14, 15,  0,  3,  0,  0,  0};


//#define DEBUG

uint8_t data1;




void setup() {
  for (uint8_t i = 0; i < 9; i++) {
    if (inputPinsPort1[i] != 0)
      pinMode(inputPinsPort1[i], INPUT_PULLUP);
    /*if (inputPinsPort2[i] != 0)
      pinMode(inputPinsPort2[i], INPUT_PULLUP);*/
  }
  
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  //Serial1.begin(300);
  //Serial1.begin(9600);
  Serial1.begin(9600, SERIAL_6E2);

}

uint8_t frame = 0;

void loop() {

  //data1 = 0xff;
  data1 = 0;

  for (uint8_t i = 0; i < 4; i++) {
    bitWrite(data1, i, digitalRead(inputPinsPort1[i])); //AXES1
  }
  bitWrite(data1, 4, digitalRead(inputPinsPort1[5])); //fire

  #ifdef DEBUG
  Serial.print(" data: "); Serial.print(data1, BIN);
  Serial.println();
  Serial.flush();
  #endif

  //uint8_t output = data1^B01010101;
  uint8_t output;
  //if (frame) output = data1^B101010; else output = data1^B010101; 
  //uint8_t output = data1;
  //Serial1.write(0xff);
  //Serial1.write(B010101);
  //Serial1.write(B010101);
  //uint8_t dummy = 0xff;
  //dummy = bitClear(dummy, frame & B11111);
  uint8_t dummy = 0;
  dummy = bitSet(dummy, frame & B11111);
  output = data1^B10101;
  //Serial1.write((frame & B11111) | B100000);
  Serial1.write(dummy | B100000);
  Serial1.write(output);

  Serial.flush();

  //delayMicroseconds(100);
  //frame ^= 1;
  frame++;


}
