

// Attention à bien mettre à jour à chaque changement
/* Comme je ne sais pas comment on met une issue, je marque ça là : Attention,
problème avec les associations montée/descente des ailevons aninsi que l'inutilté 
de la variable rotY
*/



/* Arduino Uno RX FPV
 *  to control motors & servos
 *  compatible with AtTiny85
 */
#include <SoftwareServo.h> //Servo.h en timer2
#include <VirtualWire.h>

SoftwareServo leftWing; //on déclare l'aileron gauche
SoftwareServo rightWing; //et le droit
const int rx = 8;
int rotX = 0;
int rotY = 0;

void setup() {
  leftWing.attach(9);
  rightWing.attach(10);
  vw_set_rx_pin(rx);
  vw_setup(2000); //on initialise à 2000 bauds
  vw_rx_start(); //on commence le décodage

}

void loop() {
  int angleX;
  int angleY;
  byte taille_message = sizeof(int);
  vw_wait_rx();
  if(vw_get_message((byte*) &angleY, &taille_message)) {
     if(angleY < 0) {
      //on descend
      while(rotY > angleY)
        leftWing.write(rotY);
        rightWing.write(rotY);
        delayMicroseconds(10);
        rotY--;
     }
     else {
     //sinon, on monte
      while(rotY < angleY)
        leftWing.write(rotY);
        rightWing.write(rotY);
        delayMicroseconds(10);
        rotY++;
     }
  }

     vw_wait_rx();
     if(vw_get_message((byte*) &angleX, &taille_message)) {
     if(angleX < 0) {
      //on vire à gauche
      while(rotX > angleX)
        leftWing.write(rotX); //on leve l'aileron gauche
        rightWing.write(-rotX); //et on baisse le droit
        delayMicroseconds(10);
        rotX--;
     }
     else {
     //sinon, on vire à droite
      while(rotX < angleX)
        leftWing.write(-rotX); //on baisse l'aileron gauche
        rightWing.write(rotX); // et on lève le droit
        delayMicroseconds(10);
        rot++;
     }
  }
        

}
