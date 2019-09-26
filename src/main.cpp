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
//Digit segment display flag declarations
bool asa_flag = LOW;
bool asb_flag = LOW;
bool asc_flag = LOW;
bool asd_flag = LOW;
bool ase_flag = LOW;
bool asf_flag = LOW;
bool asg_flag = LOW;
bool asdp_flag = LOW;

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

  digitalWrite(ASA, asa_flag);
  digitalWrite(ASB, asb_flag);
  digitalWrite(ASC, asc_flag);
  digitalWrite(ASD, asd_flag);
  digitalWrite(ASE, ase_flag);
  digitalWrite(ASF, asf_flag);
  digitalWrite(ASG, asg_flag);
  digitalWrite(ASDP, asdp_flag);
}

void bubble_print(uint8_t number_to_print)
{

  switch (number_to_print)
  {
  case 1:
    asa_flag = LOW;
    asb_flag = HIGH;
    asc_flag = HIGH;
    asd_flag = LOW;
    ase_flag = LOW;
    asf_flag = LOW;
    asg_flag = LOW;
    asdp_flag = LOW;
    break;

  case 2:

    asa_flag = HIGH;
    asb_flag = HIGH;
    asc_flag = LOW;
    asd_flag = HIGH;
    ase_flag = HIGH;
    asf_flag = LOW;
    asg_flag = HIGH;
    asdp_flag = LOW;

    break;

  case 3:
    asa_flag = HIGH;
    asb_flag = HIGH;
    asc_flag = HIGH;
    asd_flag = HIGH;
    ase_flag = LOW;
    asf_flag = LOW;
    asg_flag = HIGH;
    asdp_flag = LOW;

    break;

  case 4:
    asa_flag = LOW;
    asb_flag = HIGH;
    asc_flag = HIGH;
    asd_flag = LOW;
    ase_flag = LOW;
    asf_flag = HIGH;
    asg_flag = HIGH;
    asdp_flag = LOW;

    break;

  case 5:
    asa_flag = HIGH;
    asb_flag = LOW;
    asc_flag = HIGH;
    asd_flag = HIGH;
    ase_flag = LOW;
    asf_flag = HIGH;
    asg_flag = HIGH;
    asdp_flag = LOW;

    break;

  case 6:
    asa_flag = HIGH;
    asb_flag = LOW;
    asc_flag = HIGH;
    asd_flag = HIGH;
    ase_flag = HIGH;
    asf_flag = HIGH;
    asg_flag = HIGH;
    asdp_flag = LOW;

    break;

  case 7:
    asa_flag = HIGH;
    asb_flag = HIGH;
    asc_flag = HIGH;
    asd_flag = LOW;
    ase_flag = LOW;
    asf_flag = LOW;
    asg_flag = LOW;
    asdp_flag = LOW;

    break;

  case 8:
    asa_flag = HIGH;
    asb_flag = HIGH;
    asc_flag = HIGH;
    asd_flag = HIGH;
    ase_flag = HIGH;
    asf_flag = HIGH;
    asg_flag = HIGH;
    asdp_flag = LOW;

    break;

  case 9:
    asa_flag = HIGH;
    asb_flag = HIGH;
    asc_flag = HIGH;
    asd_flag = LOW;
    ase_flag = LOW;
    asf_flag = HIGH;
    asg_flag = HIGH;
    asdp_flag = LOW;

    break;

  default:
    asa_flag = LOW;
    asb_flag = LOW;
    asc_flag = LOW;
    asd_flag = LOW;
    ase_flag = LOW;
    asf_flag = LOW;
    asg_flag = LOW;
    asdp_flag = LOW;
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