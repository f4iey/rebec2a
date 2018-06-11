/*Arduino Uno TX FPV
 * on 433MHz or 2.4GHz
 * 433: long range, FM mode but more interferences because only one channel
 * 2.4: Smaller antenna, multichannel so less interferences
 */
#include <VirtualWire.h>

const int tx = 6;
const int xPin = 3;
const int yPin = 4;
const int swPin = 5;
int x0, y0, sw0, x, y, sw;

void setup() {
  //conditions initiales joystick
  
  x0 = analogRead(xPin);
  y0 = analogRead(yPin);
  sw0 = analogRead(swPin);
  //paramètres du TX
  
  vw_set_tx_pin(tx)
  
}

void loop() {
  //récupération données joystick

  x = analogRead(xPin) - x0;
  y = analogRead(yPin) - y0;
  sw = analogRead(swPin) - sw0;
  angleX = map(x, -1023, 1023, -30, 30); //en degrés
  angleY = map(y, -1023, 1023, -30, 30);
  //codage
  vw_send((byte*) &angleY, sizeof(angleY));
  vw_wait_tx();
  delay(5);
  vw_send((byte*) &angleX, sizeof(angleX));
  vw_wait_tx();
    
}

