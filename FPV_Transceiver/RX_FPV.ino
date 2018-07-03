/* Arduino Uno RX FPV
 *  to control motors & servos
 *  compatible with AtTiny85
 */
#include <SoftwareServo.h> //on utilise une bibliothèque  différente de Servo.h car VirtualWire et Servo utilisent le même timer
#include <VirtualWire.h>
SoftwareServo leftWing; //on déclare l'aileron gauche
SoftwareServo rightWing; //et le droit
const int rx = 8;
int angleX;
int angleY;
byte taille_message = sizeof(int);

void setup() {
  leftWing.attach(9);
  rightWing.attach(10);
  vw_set_rx_pin(rx);
  vw_setup(2000); //on initialise à 2000 bauds
  vw_rx_start(); //on commence le décodage

}

void loop() {
  vw_wait_rx();
  if(vw_get_message((byte*) &angleY, &taille_message)) {
    //pitch
    leftWing.write(-angleY); //inversion des commandes elevons
    rightWing.write(-angleY); //sur les deux
    delay(15);
    SoftwareServo::refresh();
     
  }

     vw_wait_rx();
     if((vw_get_message((byte*) &angleX, &taille_message)) &&(angleY == 0)) {
      //roll
      leftWing.write(1*angleX); //on leve l'aileron gauche
      rightWing.write(-1*angleX); //et on baisse le droit
      delay(15);
      SoftwareServo::refresh();
  }
    else if((vw_get_message((byte*) &angleX, &taille_message)) &&(angleY != 0)) {
        if(angleX > 0) {
            //si on vire a droite
            leftWing.write(0); //on ne touche pas
            rightWing.write(-1*angleY); //ceci ne change pas
            SoftwareServo::refresh();
        }
        
        else {
            //dans le cas inverse gauche
            rightWing.write(0); //on ne touche pas
            leftWing.write(-1*angleY); //ceci ne change pas
            SoftwareServo::refresh();
        }
    }
        

}
