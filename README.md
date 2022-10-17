# REBEC2A: Plateforme automobile Open Source

## Descriptif

**R**adio Controlled
**E**lectric
**B**ased
**E**xpermientation
**C**hassis for
**A**utomotive
**A**pplications

Le but de ce porjet est de convecoir d'abord, une plateforme minimale fonctionnelle de *modélisme* (donc la voiture, son châssis, son électronique, son firmware), ainsi que la commande à distance.


Le coeur du projet serait un microcontrôleur *ARM Cortex M7* assez puissant type *Teensy 4.1* ou *STM32F7*, afin de pouvoir connecter quelques capteurs; faire tourner des modèles de machine learning entraînés au préalable; implémenter de la vidéo FPV, de la conduite autonome, de l'évitement d'obstacles voire pourquoi pas s'amuser à faire un mode de dérapage autonome (inspiré de la MARTY, la [Delorean électrique](https://ddl.stanford.edu/marty/overview) autonome du Dynamic Design Lab de Stanford)

Un autre aspect intéressant est l'utilisation de matériel de *simulation de conduite* (que nous avons à disposition dans notre groupe), comme un pédalier et un volant pour une expérience de conduite plus ludique; où l'interface entre notre commande et ce matériel serait l'API du constructeur (Logitech ou Thrustmaster) par exemple.


Enfin, parce que nous apportons une importance particulière à redonner à la communauté qui nous a tant appris; nous trouvons important de fournir nos fichiers (notre code source, nos schémas electroniques et fichiers de CAD) [sous licence GPLv3](https://www.gnu.org/licenses/quick-guide-gplv3.fr.html).


Le tout pour aboutir au rêve du passionné du modélisme, d'électronique, de mécanique et de bricolage: une plateforme abordable, peu onéreuse, performante, facilement réplicable et abordable par des débutants et bien sur, facilement améliorable par les plus chevronnés, le tout dans un écosystème libre et ouvert.

## ROM COST BOM

|Nom     |Quantité|Prix|Commentaires|
|--------|--------|----|------------|
|BMS     |       1| 10€|A acheter   |
|Chargeur|       1| 50€|A acheter   | 
|Chassis |       1|  0€|Possédé     |
|ESC     |       1|  0€|Possédé     |
|ESP01   |       1| 10€|A acheter   |
|FPV VTX |       1| 20€|A acheter   |
|Joystick|       1|  0€|Possédé     |
|Batterie|       1| 25€|A racheter  |
|G920    |       1|  0€|Possédé     |
|MG996   |       1|  0€|Possédé     |
|Moni ATV|       1| 30€|A acheter   |
|MPU6050 |       1|  0€|Possédé     |
|NEO6M   |       1|  0€|Possédé     |
|nRF24l01|       2|  0€|Possédé     |
|Roues   |       4|  0€|Possédé     |
|Teensy4 |       1| 40€|A acheter   |
|Arduino |       1|  0€|Possédé     |
|Total   |--------|185€|            |
