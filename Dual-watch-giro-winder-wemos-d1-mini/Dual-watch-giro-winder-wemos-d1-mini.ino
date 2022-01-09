//**************************************************************
//Stepper motor driver 4 wires - Commande de moteur pas-à-pas unipolaire 4 fils
//tiptopboards.com 05/12/2013
// Driver ULN2003 and motor with 1:64 reduction - Driver ULN2003 et moteur réducté au 1:64
//
//**************************************************************
//Include the stepper.h library - Inclure la librairie stepper.h
#include <Stepper.h>
#define STEPS 100

const int button_1_pin = D0;     // Push button 1 PIN - Numéro de la broche à laquelle est connecté le bouton poussoir 1
const int button_2_pin = TX;     // Push button 2 PIN - Numéro de la broche à laquelle est connecté le bouton poussoir 2
const int LED = D4;              // Status LED PIN - Numéro de la broche à laquelle est connecté la DEL
const int MOTOR_SPEED = 300;    // Max speed is 300, reduce for slower operation - Vitesse de 300 (max) réduire ce chiffre pour un mouvement plus lent
// 100 allow for more torque, play with that to avoid vibration (>300) - 100 permet d'avoir un couple élevé >300 le moteur vibre sans tourner
const int NUMBER_OF_STEPS = 4096; // A complete rotation is 2048 steps (about 4.5sec) - Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
// To reverse rotation by 6x 1/30 of a turn, multiply NUMBER_OF_STEPS by 6/30 et add a - sign to reverse the direction
// Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier NUMBER_OF_STEPS par 6/30 et mettre un moins pour inverser le sens
// Example : -6*2048/30;

// Variable declaration - Déclaration des variables :
int button_1_state = 0;       // variable used to save button 1 state - variable qui sera utilisée pour stocker l'état du bouton 1
int button_2_state = 0;       // variable used to save button 2 state - variable qui sera utilisée pour stocker l'état du bouton 2

//2 instances of Stepper - Créer une instance de la classe stepper
//The motors (wire 1 2 3 4) are connected to ouput RX D1 D2 D3 and D5 D6 D7 D8 of the Arduino (and to GND, +V)
//Les moteurs (fils 1 2 3 4) sont branché sur les sorties RX D1 D2 D3 et D5 D6 D7 D8 de l'Arduino (et sur GND, +V)
Stepper stepper1(STEPS, D3, D1, D2, RX);  // Clockwise rotation - Sens horaire
Stepper stepper2(STEPS, D8,  D6,  D7,  D5);  // Clockwise rotation - Sens horaire

//Use the following if you prefer an anti-clockwise rotation - Sens anti-horaire en inversant 9 et 12 / 5 et 8 (si on préfère)
//Stepper stepper1(STEPS, D3, D2, D1, RX);
//Stepper stepper2(STEPS,  D8,  D7,  D6,  D5);

//************************************************************
// For a motor of this type: - Pour un moteur de ce type : http://tiptopboards.com/151-moteur-pas-%C3%A0-pas-r%C3%A9duct%C3%A9-de-5v-4-fils-driver-.html
// 64 steps per turn, 4 phases, 5.625° - 64 pas par tour, 4 phases, angle de 5.625° selon les spécifications du moteur
// 1:64 demultiplication for this mechanically reduced motor - Démultiplication 1:64 pour ce moteur réducté mécaniquement
//   360° / 5.625° * 64 = 4096 angles with demultiplication - angles avec la démultiplication
//   360° / 5.625° * 64  * 4 phases / 2 bipolare = 2048s step / turn

int counter;
void setup()
{
  pinMode(LED, OUTPUT); // Use pin LED as output - Declare le Pin LED comme sortie

  // set both buttons pins as input - indique que les broches bouton sont des entrées:
  pinMode(button_1_pin, INPUT);
  pinMode(button_2_pin, INPUT);
  pinMode(RX, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
}

void loop()
{
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
  digitalWrite(LED, HIGH);
  delay(1000);


  delay(100);
  // read the state of the 2 button and save it in button_1_state and button_2_state - lit l'état des boutons et stocke le résultat dans button_1_state/button_2_state
  button_1_state = digitalRead(button_1_pin);
  button_2_state = digitalRead(button_2_pin);

  stepper1.setSpeed(MOTOR_SPEED);
  stepper2.setSpeed(MOTOR_SPEED);


  if (counter <= 30) {
    //If the 3 position switch is in the middle position, both motor will run, otherwise, only the selected side will run.
    if (button_1_state == LOW) {
      stepper1.step(-NUMBER_OF_STEPS);  //Turning anticlockwise - Ca tourne
    }
    if (button_2_state == LOW) {
      stepper2.step(-NUMBER_OF_STEPS);  //Turning anticlockwise - Ca tourne
    }
    delay(2000);  //pause

    if (button_1_state == LOW) {
      stepper1.step(NUMBER_OF_STEPS);  //Turning clockwise - Ca tourne
    }
    if (button_2_state == LOW) {
      stepper2.step(NUMBER_OF_STEPS);  //Turning clockwise - Ca tourne
    }

    delay(2000);  //pause
    // Blink the LED - Clignotement de la LED
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    delay(100);
    counter++; //Add one to the counter - Ajoute 1 au counter
  }

  if (button_1_state == HIGH && button_2_state == HIGH) {
    //BUG INTER - Both input buttons are high, something is wrong, check connection or pull down resistors
    for (int i = 0; i <= 10; i++) {
      //Blink led fast to inform of the error
      digitalWrite(LED, LOW);
      delay(200);
      digitalWrite(LED, HIGH);
      delay(200);
    }
    counter++; //Ajoute 1 au counter
  }


  if (counter > 30 && counter < 180) {
    digitalWrite(LED, LOW);
    delay(1000);
    digitalWrite(LED, HIGH);
    delay(1000);
    counter++; //Ajoute 1 au counter
  }
  if (counter == 180) {
    counter = 0; //Reset the counter - Réinitialise le counter
  }
}
