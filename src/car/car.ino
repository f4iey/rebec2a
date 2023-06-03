/*  côté voiture
 *  to control motors & servos
 */
#include <SPI.h>
#include <RF24.h> 
#include <Servo.h>
RF24 rx (7, 8);
byte adresses[][6] = {"0"}; //meme code couleur que pour le tx
Servo axle; //on déclare l'aileron gauche
Servo ESC;

struct Package{
  int gazVal; //moteur
  //char aprs[60]; //trame APRSIS à envoyer
  int steerVal; //servo
  uint8_t acc; //acessory trigger
};
struct Package rc;
int ackData[3] = {rc.gazVal, rc.steerVal, rc.acc};

/* ATTENTION:
 * la valeur gazVal doit bien être entre 0 et 1023!
 */

void setup() {
  pinMode(3, OUTPUT);
  axle.attach(9);
  axle.write(40);
  ESC.attach(6);
  //réglages radio
  Serial.begin(9600);
  SPI.begin;
  rx.begin();
  rx.setChannel(69); //meme canal que rx
  rx.setPALevel(RF24_PA_MAX); //puissance max
  rx.setDataRate(RF24_250KBPS); //vitesse lente
  rx.openReadingPipe(1, adresses[0]); //on lui donne le code couleur à utiliser
  rx.enableAckPayload();
  //rx.openWritingPipe(adresses[0]); //on lui permet d'ecrire
  //rx.startListening(); //c'est parti
  ESC.write(0); //on arme le brushless (procédure de démarrage)
  delay(15);
}

void loop() {
    //on met la LED en constant si on en a une
    rx.startListening();
    //rx.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data
    
   if(rx.available()) {
    while(rx.available()) {
      rx.read(&rc, sizeof(rc)); //on utilise les données recues pour les ailerons
      vitesseBrushless(rc.gazVal); //contrôleur
      axle.write(rc.steerVal);
      Serial.println(rc.steerVal);
      setAcc(rc.acc); //activation des acessoires
      delay(15); //attend que le servo se mettent en place
      // on acquitte avec les valeurs des capteurs
      ackData[0] = rc.gazVal; //TBD RPM
      ackData[1] = axle.read(); //a calibrer
      rx.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data
      
      
    }
    //perte de connexion: on fait clignoter la LED à éclats
   }   
    //pas de télécommande à proximité: on fait clignoter la LED à occultations
   /* rx.stopListening();
    rx.write(&rc, sizeof(rc)); //on envoie un paquet test toutes les 750ms
    delay(750);
    //rx.startListening();*/
}

void vitesseBrushless(int gaz) {
    int commandeEsc = map(gaz, 0, 1023, 1000, 1450);
    ESC.writeMicroseconds(commandeEsc);
    Serial.println(commandeEsc);
}
void setAcc(uint8_t mode){
  switch(mode){
    case 1:
      //klaxon
      digitalWrite(3, HIGH);
    break;
    case 2:
      //phares
    break;
   default:
    digitalWrite(3, LOW);
   break;
  }
}
