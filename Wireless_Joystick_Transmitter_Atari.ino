
//#define SerialPort Serial // Arduino Uno, Pro Mini, Nano...
#define SerialPort Serial1 // Arduino Pro Micro, Leonardo...

//DB9 (8=GND, 7=VCC):               1   2   3   4   5   6   7   8   9
const uint8_t inputPinsPort1[] =  { 5,  6,  7,  8,  0,  4,  0,  0,  0};
//const uint8_t inputPinsPort2[] =  {10, 16, 14, 15,  0,  3,  0,  0,  0};

// Connect transmitter to pin 0 (TX)

//#define DEBUG //don't use if your SerialPort is Serial

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

  SerialPort.begin(9600, SERIAL_6E2);

}

uint8_t data1;
uint8_t frame = 0;

void loop() {

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

  uint8_t output;
  uint8_t dummy = 0;
  dummy = bitSet(dummy, frame & B11111);
  output = data1^B10101;
  SerialPort.write(dummy | B100000);
  SerialPort.write(output);
  SerialPort.flush();

  frame++;
}
