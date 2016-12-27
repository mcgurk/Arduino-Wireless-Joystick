//#define DEBUG

//DB9 (8=GND, 7=VCC):                1   2   3   4   5   6   7   8   9
const uint8_t outputPinsPort1[] =  {15, 14,  A1,  A0,  0,  9,  0,  0,  0};
//const uint8_t outputPinsPort2[] =  {10, 16, 14, 15,  0,  3,  0,  0,  0};

#define RECEIVER_VCC_PIN 2

void setup() {
  for (uint8_t i = 0; i < 9; i++) {
    if (outputPinsPort1[i] != 0) {
      pinMode(outputPinsPort1[i], OUTPUT);
      digitalWrite(outputPinsPort1[i], HIGH);
    }
    /*if (outputPinsPort2[i] != 0)
      pinMode(outputPinsPort2[i], INPUT_PULLUP);*/
  }

  pinMode(RECEIVER_VCC_PIN, OUTPUT);
  digitalWrite(RECEIVER_VCC_PIN, HIGH);


  #ifdef DEBUG
  Serial.begin(115200);
  #endif

  Serial1.begin(9600, SERIAL_6E2);
}

uint8_t input;
uint8_t data1;

void loop() {
  input = Serial1.read();
  if (!bitRead(input, 5)) data1 = input ^ B10101; else data1 = 0;

  if (data1) {
    for (uint8_t i = 0; i < 4; i++) {
      digitalWrite(outputPinsPort1[i], bitRead(data1, i)); //AXES1
    }
    digitalWrite(outputPinsPort1[5], bitRead(data1, 4)); //fire
  }
  
  #ifdef DEBUG
  if (data1) {
    Serial.print(data1, BIN);
    Serial.println();
    Serial.flush();
  }
  #endif
}
