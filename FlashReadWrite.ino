#include <SPIFlash.h>

unsigned int data[] = {8975,440,700,4650};
unsigned int data1[100]={};
char input = 0;

#define FLASH_SS 8

SPIFlash flash(FLASH_SS, 0xEF30);

void setup() {
  Serial.begin(9600);
  Serial.println("Start...");

  if(flash.initialize())
    Serial.println("Init OK!");
  else
    Serial.println("Init FAIL!");

  delay(1000);

  Serial.print("DataSize: ");
  Serial.println(sizeof(data));

  Serial.println("Input:");
  Serial.println("d: to dump all values from 0 to 4100 bytes");
  Serial.println("e: to erase the whole flash");
  Serial.println("b: to erase 1 block 4096 bytes:");
  Serial.println("1: to save values into flash");
  Serial.println("2: to read values from flash and dump them to serial");
}

void loop() {
  if(Serial.available() > 0){
    input = Serial.read();
    int counter = 0;
    switch(input){
      case 'd': Serial.println("Flash Content: ");
                while(counter<=4100){
                  Serial.print(counter);
                  Serial.print(": ");
                  Serial.println(flash.readByte(counter++), DEC);
                  }
                  break;
       case 'e': Serial.print("Erasing Flash Chip....");
                 flash.chipErase();
                 while(flash.busy());
                 Serial.println("DONE");
                 break;
       case 'b': Serial.println("Erasing 4k from position 1");
                 flash.blockErase4K(1);
                 break;
       case '1': Serial.println("Saving...");
                 flash.writeBytes(1, &data, sizeof(data));
                 break;
       case '2': Serial.println("Reading....");
                 flash.readBytes(1, data1, sizeof(data));
                 for(int i=0; i<sizeof(data); i++){
                  Serial.print(i)
                  Serial.print(": ");
                  Serial.println(data1[i]);
                 }
                 Serial.println("Done");
                 break;
      }
    }
}
