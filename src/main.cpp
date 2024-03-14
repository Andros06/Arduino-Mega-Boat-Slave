#include <Arduino.h>
#include <Wire.h>

const int numValues = 3;
int values[numValues];

// Klassifiserer en funksjon for meldings event
void receiveEvent(int byteCount);


void setup() {
  // Starter I2C Bus som Slave på address 9
  Wire.begin(9); 

  // Starter Seriel med pc
  Serial.begin(9600);

  // Kopler meldings event ilag med wire.onreceive
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int byteCount) {
  if (byteCount == sizeof(int) * numValues){
    for (int i = 0; i < numValues; i++){
      Wire.readBytes((uint8_t*)&values[i], sizeof(int));
    }
  }
}


void loop() {
  Serial.print("Switch state = ");
  Serial.print(values[0]);
  Serial.print("  ");
  Serial.print("Throttle value = ");
  Serial.print(values[1]);
  Serial.print("  ");
  Serial.print("Steering value = ");
  Serial.println(values[2]);
  
  delay(200);
}