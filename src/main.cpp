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
uint16_t digit_display_time_delay_us = 250;

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
void bubble_print(uint16_t number_to_print);

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
  //Local variable declarations
  uint32_t elapsed_time_ms = 0;

  elapsed_time_ms = millis() / 10; //Save elapsed time (divided by 10 for 10 ms resolution requirement) to elapsed_time_ms

  bubble_print(elapsed_time_ms);
}

void bubble_print(uint16_t number_to_print) //Print a 4 digit number to the bubble display, minimum 16 bits to reach at least 9999 max display number
{
  //Local variable declarations
  uint8_t digit_to_print = 0;            //Single digit to print
  uint8_t number_to_print_4th_digit = 0; //4th or least significant digit
  uint8_t number_to_print_3rd_digit = 0; //3rd digit
  uint8_t number_to_print_2nd_digit = 0; //2nd digit
  uint8_t number_to_print_1st_digit = 0; //1st or most significant digit

  //Decompose 4 digit number into 4 individual digits
  number_to_print_4th_digit = (number_to_print / 1) % 10;
  number_to_print_3rd_digit = (number_to_print / 10) % 10;
  number_to_print_2nd_digit = (number_to_print / 100) % 10;
  number_to_print_1st_digit = (number_to_print / 1000) % 10;

  //Cycle through the four digits, printing the correct number for each
  for (uint8_t i = 4; i >= 1; i--)
  {

    switch (i)
    {
    case 1:
      digitalWrite(CC1, HIGH);
      digitalWrite(CC2, LOW);
      digitalWrite(CC3, LOW);
      digitalWrite(CC4, LOW);
      asdp_flag = LOW;
      digit_to_print = number_to_print_1st_digit;
      break;

    case 2:
      digitalWrite(CC1, LOW);
      digitalWrite(CC2, HIGH);
      digitalWrite(CC3, LOW);
      digitalWrite(CC4, LOW);
      asdp_flag = HIGH;
      digit_to_print = number_to_print_2nd_digit;
      break;

    case 3:
      digitalWrite(CC1, LOW);
      digitalWrite(CC2, LOW);
      digitalWrite(CC3, HIGH);
      digitalWrite(CC4, LOW);
      asdp_flag = LOW;
      digit_to_print = number_to_print_3rd_digit;
      break;

    case 4:
      digitalWrite(CC1, LOW);
      digitalWrite(CC2, LOW);
      digitalWrite(CC3, LOW);
      digitalWrite(CC4, HIGH);
      asdp_flag = LOW;
      digit_to_print = number_to_print_4th_digit;
      break;
    }

    //Print a single digit
    switch (digit_to_print)
    {
    case 0:
      asa_flag = HIGH;
      asb_flag = HIGH;
      asc_flag = HIGH;
      asd_flag = HIGH;
      ase_flag = HIGH;
      asf_flag = HIGH;
      asg_flag = LOW;
      break;

    case 1:
      asa_flag = LOW;
      asb_flag = HIGH;
      asc_flag = HIGH;
      asd_flag = LOW;
      ase_flag = LOW;
      asf_flag = LOW;
      asg_flag = LOW;
      break;

    case 2:

      asa_flag = HIGH;
      asb_flag = HIGH;
      asc_flag = LOW;
      asd_flag = HIGH;
      ase_flag = HIGH;
      asf_flag = LOW;
      asg_flag = HIGH;

      break;

    case 3:
      asa_flag = HIGH;
      asb_flag = HIGH;
      asc_flag = HIGH;
      asd_flag = HIGH;
      ase_flag = LOW;
      asf_flag = LOW;
      asg_flag = HIGH;

      break;

    case 4:
      asa_flag = LOW;
      asb_flag = HIGH;
      asc_flag = HIGH;
      asd_flag = LOW;
      ase_flag = LOW;
      asf_flag = HIGH;
      asg_flag = HIGH;

      break;

    case 5:
      asa_flag = HIGH;
      asb_flag = LOW;
      asc_flag = HIGH;
      asd_flag = HIGH;
      ase_flag = LOW;
      asf_flag = HIGH;
      asg_flag = HIGH;

      break;

    case 6:
      asa_flag = HIGH;
      asb_flag = LOW;
      asc_flag = HIGH;
      asd_flag = HIGH;
      ase_flag = HIGH;
      asf_flag = HIGH;
      asg_flag = HIGH;

      break;

    case 7:
      asa_flag = HIGH;
      asb_flag = HIGH;
      asc_flag = HIGH;
      asd_flag = LOW;
      ase_flag = LOW;
      asf_flag = LOW;
      asg_flag = LOW;

      break;

    case 8:
      asa_flag = HIGH;
      asb_flag = HIGH;
      asc_flag = HIGH;
      asd_flag = HIGH;
      ase_flag = HIGH;
      asf_flag = HIGH;
      asg_flag = HIGH;

      break;

    case 9:
      asa_flag = HIGH;
      asb_flag = HIGH;
      asc_flag = HIGH;
      asd_flag = LOW;
      ase_flag = LOW;
      asf_flag = HIGH;
      asg_flag = HIGH;

      break;

    default:
      asa_flag = LOW;
      asb_flag = LOW;
      asc_flag = LOW;
      asd_flag = LOW;
      ase_flag = LOW;
      asf_flag = LOW;
      asg_flag = LOW;

      break;
    }

    digitalWrite(ASA, asa_flag);
    digitalWrite(ASB, asb_flag);
    digitalWrite(ASC, asc_flag);
    digitalWrite(ASD, asd_flag);
    digitalWrite(ASE, ase_flag);
    digitalWrite(ASF, asf_flag);
    digitalWrite(ASG, asg_flag);
    digitalWrite(ASDP, asdp_flag);

    while (micros() % digit_display_time_delay_us > 0) //Delay prior to displaying the next digit
    {
    }
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