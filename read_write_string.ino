#include<SPIMemory.h>

uint32_t strAddr;

#define BAUD_RATE 115200
#define RANDPIN 10


//SPIFlash flash(SS1, &SPI1);       //Use this constructor if using an SPI bus other than the default SPI. Only works with chips with more than one hardware SPI bus
SPIFlash flash;

bool readSerialStr(String &inputStr);

void setup() {
  Serial.begin(BAUD_RATE);
  flash.begin();
}

void loop() {
  randomSeed(analogRead(RANDPIN));
  strAddr = random(0, flash.getCapacity());
  
  String inputString = "";
  while(!Serial.available()){}
  readSerialStr(inputString);
  flash.writeStr(strAddr, inputString);
  Serial.print(F("Written string: "));
  Serial.println(inputString);
  Serial.print(F("To address: "));
  Serial.println(strAddr);
  String outputString = "";
  if (flash.readStr(strAddr, outputString)) {
    Serial.print(F("Read string: "));
    Serial.println(outputString);
    Serial.print(F("From address: "));
    Serial.println(strAddr);
  }
  while (!flash.eraseSector(strAddr));
}

//Reads a string from Serial
bool readSerialStr(String &inputStr) {
  if (!Serial)
    Serial.begin(115200);
  while (Serial.available()) {
    inputStr = Serial.readStringUntil('\n');
    Serial.println(inputStr);
    return true;
  }
  return false;
}
