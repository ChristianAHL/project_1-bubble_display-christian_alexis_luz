#include <Arduino.h> //Include the standard Arduino framwork library

//General Pin Assignments
#define LED_PIN 11
#define BUTTON_PIN 6

//Bubble Display Common Cathode Pin Assignments
#define CC1 15
#define CC2 13
#define CC3 14
#define CC4 12

//Bubble Display Anode Segment Pin Assignments
#define ASA 23
#define ASB 22
#define ASC 21
#define ASD 20
#define ASE 19
#define ASF 18
#define ASG 17
#define ASDP 16

//Global variable declarations
//uint8_t number_to_print = 1;

//Function prototypes
void bubble_print(uint8_t number_to_print);

void setup() //Setup of pin modes, serial, and interrupt
{
  Serial.begin(9600); //Set baud rate

  //General Pin Setup
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  //Anode Segment Pin Setup
  pinMode(ASA, OUTPUT);
  pinMode(ASB, OUTPUT);
  pinMode(ASC, OUTPUT);
  pinMode(ASD, OUTPUT);
  pinMode(ASE, OUTPUT);
  pinMode(ASF, OUTPUT);
  pinMode(ASG, OUTPUT);
  pinMode(ASDP, OUTPUT);

  //Common Cathode Pin Setup
  pinMode(CC1, OUTPUT);
  pinMode(CC2, OUTPUT);
  pinMode(CC3, OUTPUT);
  pinMode(CC4, OUTPUT);
}

void loop() //Main program body
{
  
  
  digitalWrite(CC3, HIGH);

  bubble_print(1);
  delay(500);
  bubble_print(2);
  delay(500);
  bubble_print(3);
  delay(500);
  bubble_print(4);
  delay(500);
  bubble_print(5);
  delay(500);
  bubble_print(6);
  delay(500);
  bubble_print(7);
  delay(500);
  bubble_print(8);
  delay(500);
  bubble_print(9);
  delay(500);
  bubble_print(10);
  delay(500);
 
}

void bubble_print(uint8_t number_to_print){
switch (number_to_print)
{
case 1:
  digitalWrite(ASA, LOW);
  digitalWrite(ASB, HIGH);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, LOW);
  digitalWrite(ASE, LOW);
  digitalWrite(ASF, LOW);
  digitalWrite(ASG, LOW);
  digitalWrite(ASDP, LOW);
  break;

case 2:
  digitalWrite(ASA, HIGH);
  digitalWrite(ASB, HIGH);
  digitalWrite(ASC, LOW);
  digitalWrite(ASD, HIGH);
  digitalWrite(ASE, HIGH);
  digitalWrite(ASF, LOW);
  digitalWrite(ASG, HIGH);
  digitalWrite(ASDP, LOW);
  break;

case 3:
  digitalWrite(ASA, HIGH);
  digitalWrite(ASB, HIGH);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, HIGH);
  digitalWrite(ASE, LOW);
  digitalWrite(ASF, LOW);
  digitalWrite(ASG, HIGH);
  digitalWrite(ASDP, LOW);
  break;

case 4:
  digitalWrite(ASA, LOW);
  digitalWrite(ASB, HIGH);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, LOW);
  digitalWrite(ASE, LOW);
  digitalWrite(ASF, HIGH);
  digitalWrite(ASG, HIGH);
  digitalWrite(ASDP, LOW);
  break;

case 5:
  digitalWrite(ASA, HIGH);
  digitalWrite(ASB, LOW);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, HIGH);
  digitalWrite(ASE, LOW);
  digitalWrite(ASF, HIGH);
  digitalWrite(ASG, HIGH);
  digitalWrite(ASDP, LOW);
  break;

case 6:
  digitalWrite(ASA, HIGH);
  digitalWrite(ASB, LOW);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, HIGH);
  digitalWrite(ASE, HIGH);
  digitalWrite(ASF, HIGH);
  digitalWrite(ASG, HIGH);
  digitalWrite(ASDP, LOW);
  break;

case 7:
  digitalWrite(ASA, HIGH);
  digitalWrite(ASB, HIGH);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, LOW);
  digitalWrite(ASE, LOW);
  digitalWrite(ASF, LOW);
  digitalWrite(ASG, LOW);
  digitalWrite(ASDP, LOW);
  break;

case 8:
  digitalWrite(ASA, HIGH);
  digitalWrite(ASB, HIGH);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, HIGH);
  digitalWrite(ASE, HIGH);
  digitalWrite(ASF, HIGH);
  digitalWrite(ASG, HIGH);
  digitalWrite(ASDP, LOW);
  break;

case 9:
  digitalWrite(ASA, HIGH);
  digitalWrite(ASB, HIGH);
  digitalWrite(ASC, HIGH);
  digitalWrite(ASD, LOW);
  digitalWrite(ASE, LOW);
  digitalWrite(ASF, HIGH);
  digitalWrite(ASG, HIGH);
  digitalWrite(ASDP, LOW);
  break;

default:
  digitalWrite(ASA, LOW);
  digitalWrite(ASB, LOW);
  digitalWrite(ASC, LOW);
  digitalWrite(ASD, LOW);
  digitalWrite(ASE, LOW);
  digitalWrite(ASF, LOW);
  digitalWrite(ASG, LOW);
  digitalWrite(ASDP, LOW);
  break;
}

}

/*
void ISR_button_press() //Interrupt service routine that handles print frequency request one the push button is pressed
{

  noInterrupts(); //Prevent other interrupts

  //Local variable declarations
  static uint32_t previous_press_time_ms = 0; //Previous time noted for debouncing
  uint32_t current_press_time_ms = millis();  //Current time noted for debouncing

  if ((current_press_time_ms - previous_press_time_ms) > DEBOUNCE_DELAY_MS) //Code segment that handles noting of frequency print request, with button debounce
  {
    frequency_requested_flag = true;                //Set flag to true to indicate a frequency print request at the main loop
    previous_press_time_ms = current_press_time_ms; //Updates previous time to facilitate correct debounce timing
  }
  interrupts(); //Re-enable other interrupts
}
*/