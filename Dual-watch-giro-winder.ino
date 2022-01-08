//**************************************************************
//Stepper motor driver 4 wires - Commande de moteur pas-à-pas unipolaire 4 fils
//tiptopboards.com 05/12/2013
// Driver ULN2003 and motor with 1:64 reduction - Driver ULN2003 et moteur réducté au 1:64
//
//**************************************************************
//Include the stepper.h library - Inclure la librairie stepper.h
#include <Stepper.h>
#define STEPS 100

const int button_1_pin = 2;     // Push button 1 PIN - Numéro de la broche à laquelle est connecté le bouton poussoir 1
const int button_2_pin = 3;     // Push button 2 PIN - Numéro de la broche à laquelle est connecté le bouton poussoir 2
const int LED = 4;              // Status LED PIN - Numéro de la broche à laquelle est connecté la DEL

// Variable declaration - Déclaration des variables :
int button_1_state = 0;       // variable used to save button 1 state - variable qui sera utilisée pour stocker l'état du bouton 1
int button_2_state = 0;       // variable used to save button 2 state - variable qui sera utilisée pour stocker l'état du bouton 2

//2 instances of Stepper - Créer une instance de la classe stepper
//The motors (wire 1 2 3 4) are connected to ouput 9 10 11 12 and 5 7 6 8 of the Arduino (and to GND, +V)
//Les moteurs (fils 1 2 3 4) sont branché sur les sorties 9 10 11 12 et 5 7 6 8 de l'Arduino (et sur GND, +V)
Stepper small_stepper1(STEPS, 9, 11, 10, 12);  // Clockwise rotation - Sens horaire
Stepper small_stepper2(STEPS, 5,  7,  6,  8);  // Clockwise rotation - Sens horaire

//Use the following if you prefer an anti-clockwise rotation - Sens anti-horaire en inversant 9 et 12 / 5 et 8(si on préfère)
//Stepper small_stepper1(STEPS, 12, 11, 10, 9);
//Stepper small_stepper2(STEPS,  8,  7,  6, 5);

int  Steps2Take = 0;  //Number of rotation steps the motor had to perform - Nombre de pas de rotation demandé au moteur
long temps = 0;       //Duration of one rotation - Durée de rotation pour un tour
//************************************************************
// For a motor of this type: - Pour un moteur de ce type : http://tiptopboards.com/151-moteur-pas-%C3%A0-pas-r%C3%A9duct%C3%A9-de-5v-4-fils-driver-.html
// 64 steps per turn, 4 phases, 5.625° - 64 pas par tour, 4 phases, angle de 5.625° selon les spécifications du moteur
// 1:64 demultiplication for this mechanically reduced motor - Démultiplication 1:64 pour ce moteur réducté mécaniquement
//   360° / 5.625° * 64 = 4096 angles with demultiplication - angles avec la démultiplication
//   360° / 5.625° * 64  * 4 phases / 2 bipolare = 2048s step / turn

int counter;
void setup()
{
  Serial.begin(9600);     // 9600 bps
  Serial.println("Stepper motor test - Test de moteur pas a pas");
  pinMode(LED, OUTPUT); // Use pin 4 as indicator LED - Declare le Pin 5 comme sortie pour la LED
  // set both buttons pins as input - indique que les broches bouton sont des entrées:
  pinMode(button_1_pin, INPUT);
  pinMode(button_2_pin, INPUT);
}

void loop()
{
  digitalWrite(4, HIGH); // Turn on the led.
  delay(100);
  // read the state of the 2 button and save it in button_1_state and button_2_state - lit l'état des boutons et stocke le résultat dans button_1_state/button_2_state
  button_1_state = digitalRead(button_1_pin);
  button_2_state = digitalRead(button_2_pin);
  Serial.println("Motors ON - Moteurs en marche");
  small_stepper1.setSpeed(300); //Max speed is 300, reduce for slower operation - Vitesse de 300 (max) réduire ce chiffre pour un mouvement plus lent
  small_stepper2.setSpeed(300); //Max speed is 300, reduce for slower operation - Vitesse de 300 (max) réduire ce chiffre pour un mouvement plus lent
  //100 allow for more torque, play with that to avoid vibration (>300) - 100 permet d'avoir un couple élevé >300 le moteur vibre sans tourner

  if (counter <= 30 && button_1_state == HIGH && button_2_state == LOW) {
    Serial.println("LOOP1 - Mode 1 selected - Running 30 times stepper 1");

    Steps2Take  = -4096;  // A complete rotation with 2048 steps (about 4.5sec) - Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
    //To reverse rotation by 6x 1/30 of a turn, multiply Step2Take by 6/30 et add a - sign to reverse the direction
    //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
    // Example  Steps2Take  = -6*2048/30;
    //temps = millis();
    small_stepper1.step(Steps2Take);  //Turning - Ca tourne
    //temps =  millis()- temps ;  //Time a complete turn, 6.236s per turn at speed 200 - Chronomètre un tour complet  6.236 sec par tour à vitesse 200
    //Serial.println(temps);      //Print the time in ms for a complete turn - Affiche le temps (en ms) pour un tour complet
    delay(2000);  //pause

    Steps2Take  = 4096;  // A complete rotation with 2048 steps (about 4.5sec) - Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
    //To reverse rotation by 6x 1/30 of a turn, multiply Step2Take by 6/30 et add a - sign to reverse the direction
    //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
    // Example  Steps2Take  = -6*2048/30;
    //temps = millis();
    small_stepper1.step(Steps2Take);  //Turning - Ca tourne
    //temps =  millis()- temps ;  //Time a complete turn, 6.236s per turn at speed 200 - Chronomètre un tour complet  6.236 sec par tour à vitesse 200
    //Serial.println(temps);      //Print the time in ms for a complete turn - Affiche le temps (en ms) pour un tour complet
    delay(2000);  //pause

    // Blink the LED - Clignotement de la LED
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    delay(100);
    counter++; //Add one to the counter - Ajoute 1 au counter
  }
  else if (counter <= 30 && button_1_state == LOW && button_2_state == HIGH) {
    Serial.println("LOOP2 - Mode 2 selected - Running 30 times stepper 2");
    Steps2Take  = -4096;  // A complete rotation with 2048 steps (about 4.5sec) - Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
    //To reverse rotation by 6x 1/30 of a turn, multiply Step2Take by 6/30 et add a - sign to reverse the direction
    //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
    // Example  Steps2Take  = -6*2048/30;
    //temps = millis();
    small_stepper2.step(Steps2Take);  //Turning - Ca tourne
    //temps =  millis()- temps ;  //Time a complete turn, 6.236s per turn at speed 200 - Chronomètre un tour complet  6.236 sec par tour à vitesse 200
    //Serial.println(temps);      //Print the time in ms for a complete turn - Affiche le temps (en ms) pour un tour complet
    delay(2000);  //pause

    Steps2Take  = 4096;  // A complete rotation with 2048 steps (about 4.5sec) - Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
    //To reverse rotation by 6x 1/30 of a turn, multiply Step2Take by 6/30 et add a - sign to reverse the direction
    //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
    // Example  Steps2Take  = -6*2048/30;
    //temps = millis();
    small_stepper2.step(Steps2Take);  //Turning - Ca tourne
    //temps =  millis()- temps ;  //Time a complete turn, 6.236s per turn at speed 200 - Chronomètre un tour complet  6.236 sec par tour à vitesse 200
    //Serial.println(temps);      //Print the time in ms for a complete turn - Affiche le temps (en ms) pour un tour complet
    delay(2000);  //pause

    // Blink the LED - Clignotement de la LED
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    delay(100);
    counter++; //Add 1 to the counter - Ajoute 1 au counter
  }
  else if (counter <= 30 && button_1_state == LOW && button_2_state == LOW) {
    Serial.println("LOOP1&2 - Mode 3 selected - Running 30 times both steppers");
    Steps2Take  = -4096;  // A complete rotation with 2048 steps (about 4.5sec) - Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
    //To reverse rotation by 6x 1/30 of a turn, multiply Step2Take by 6/30 et add a - sign to reverse the direction
    //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
    // Example  Steps2Take  = -6*2048/30;
    //temps = millis();
    small_stepper1.step(Steps2Take);  //Ca tourne
    small_stepper2.step(Steps2Take);  //Ca tourne
    //temps =  millis()- temps ;  //Time a complete turn, 6.236s per turn at speed 200 - Chronomètre un tour complet  6.236 sec par tour à vitesse 200
    //Serial.println(temps);      //Print the time in ms for a complete turn - Affiche le temps (en ms) pour un tour complet
    delay(0);  //pause

    Steps2Take  = 4096;  // A complete rotation with 2048 steps (about 4.5sec) - Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
    //To reverse rotation by 6x 1/30 of a turn, multiply Step2Take by 6/30 et add a - sign to reverse the direction
    //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
    // Example  Steps2Take  = -6*2048/30;
    //temps = millis();
    small_stepper1.step(Steps2Take);  //Ca tourne
    small_stepper2.step(Steps2Take);  //Ca tourne
    //temps =  millis()- temps ;  //Time a complete turn, 6.236s per turn at speed 200 - Chronomètre un tour complet  6.236 sec par tour à vitesse 200
    //Serial.println(temps);      //Print the time in ms for a complete turn - Affiche le temps (en ms) pour un tour complet
    delay(0);  //pause

    // Blink the LED - Clignotement de la LED
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    delay(100);
    counter++; //Add 1 to the counter - Ajoute 1 au counter
  }

  else if (counter <= 30 && button_1_state == HIGH && button_2_state == HIGH) {
    Serial.println("BUG INTER - Both input buttons are high, something is wrong, check connection or pull down resistors");
    counter++; //Ajoute 1 au counter
  }

  else if (counter <= 180) {
    Serial.println("PAUSE - Motor runned already 30 times, pausing until 180 loops have been reached.");
    digitalWrite(LED, LOW);
    delay(1000);
    digitalWrite(LED, HIGH);
    delay(1000);
    // 10 sec went by - 10 sec Ecoulé
    counter++; //Ajoute 1 au counter
  }
  else {
    counter = 0; //Reset the counter - Réinitialise le counter
  }
}
