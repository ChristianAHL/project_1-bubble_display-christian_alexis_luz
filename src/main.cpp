#include <Arduino.h> //Include the standard Arduino framwork library.

//General pin assignments.
#define RESET_BUTTON_PIN 11
#define START_STOP_BUTTON_PIN 10

//Bubble display common cathode pin assignments.
#define CC1 15
#define CC2 13
#define CC3 14
#define CC4 12

//Bubble display anode segment pin assignments.
#define ASA 23
#define ASB 22
#define ASC 21
#define ASD 20
#define ASE 19
#define ASF 18
#define ASG 17
#define ASDP 16

//Global variable declarations.
volatile bool stopped_state_flag = false;   //Volatile prevents optimization by the compiler, flag for start/stop button press event.
volatile bool reset_requested_flag = false; //Volatile prevents optimization by the compiler, flag for reset button press event.

//Digit anode segment display flag declarations.
bool asa_flag = LOW;
bool asb_flag = LOW;
bool asc_flag = LOW;
bool asd_flag = LOW;
bool ase_flag = LOW;
bool asf_flag = LOW;
bool asg_flag = LOW;
bool asdp_flag = LOW;

//Function prototypes.
void bubble_print(uint16_t number_to_print); //Prints a 4 digit number to a bubble display.
void ISR_start_stop_press();                 //Starts or stops the stop watch.
void ISR_reset_press();                      //Resets the stop watch to 0 seconds.

//Configuration constants.
unsigned long DEBOUNCE_DELAY_MS = 200;      //Time window in milliseconds where button inputs are not entertained, for debounce purposes.
unsigned long DIGIT_DISPLAY_DELAY_US = 250; //Time allocated in microseconds for each single digit to be displayed on bubble display in turn. Should be a value that reduces apparent flicker.

void setup() //Setup of pin modes and interrupts.
{

  //General pin setup.
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
  pinMode(START_STOP_BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(START_STOP_BUTTON_PIN, ISR_start_stop_press, RISING); //Attach interrupt for start/stop button. Set to rising for timing precision purposes.
  attachInterrupt(RESET_BUTTON_PIN, ISR_reset_press, FALLING);          //Attach interrupt for reset button. Not set to rising as it is less critical for timing precision.

  //Anode segment pin setup.
  pinMode(ASA, OUTPUT);
  pinMode(ASB, OUTPUT);
  pinMode(ASC, OUTPUT);
  pinMode(ASD, OUTPUT);
  pinMode(ASE, OUTPUT);
  pinMode(ASF, OUTPUT);
  pinMode(ASG, OUTPUT);
  pinMode(ASDP, OUTPUT);

  //Common cathode pin setup.
  pinMode(CC1, OUTPUT);
  pinMode(CC2, OUTPUT);
  pinMode(CC3, OUTPUT);
  pinMode(CC4, OUTPUT);
}

void loop() //Main program body.
{
  //Local variable declarations.
  static unsigned long elapsed_time_ms = 0;              //Time elapsed in milliseconds.
  static unsigned long time_restart_compensation_ms = 0; //Time subtracted from millis() to ensure time is restarted at the correct time upon restarting from a stop state.
  static unsigned long time_reset_compensation_ms = 0;   //Time subtracted from millis() to ensure time starts at 0 seconds upon stop watch reset.
  static unsigned long elapsed_time_at_stop_ms = 0;      //Saves the current time when stop watch is stopped.

  //If-Then block handling time reset functionality.
  if (reset_requested_flag == false)
  {

    elapsed_time_ms = (millis() / 10) - time_restart_compensation_ms - time_reset_compensation_ms;
  }

  else if (reset_requested_flag == true)
  {

    time_reset_compensation_ms = millis() / 10;
    time_restart_compensation_ms = 0;
    elapsed_time_at_stop_ms = 0;
    reset_requested_flag = false;
  }

  //If-Then block handling start/stop functionality.
  if (stopped_state_flag == false)
  {

    bubble_print(elapsed_time_ms);
    elapsed_time_at_stop_ms = elapsed_time_ms;
  }

  else if (stopped_state_flag == true)
  {

    time_restart_compensation_ms = (millis() / 10) - elapsed_time_at_stop_ms - time_reset_compensation_ms;
    bubble_print(elapsed_time_at_stop_ms);
  }
}

void bubble_print(uint16_t number_to_print) //Print a 4 digit number to the bubble display, minimum 16 bits to reach at least 9999 max display number.
{
  //Local variable declarations.
  uint8_t digit_to_print = 0;            //Single digit to print.
  uint8_t number_to_print_4th_digit = 0; //4th or least significant digit. Increments of 10 ms as required.
  uint8_t number_to_print_3rd_digit = 0; //3rd digit.
  uint8_t number_to_print_2nd_digit = 0; //2nd digit.
  uint8_t number_to_print_1st_digit = 0; //1st or most significant digit.

  //Decompose received 4 digit number into 4 individual digits.
  number_to_print_4th_digit = (number_to_print / 1) % 10;
  number_to_print_3rd_digit = (number_to_print / 10) % 10;
  number_to_print_2nd_digit = (number_to_print / 100) % 10;
  number_to_print_1st_digit = (number_to_print / 1000) % 10;

  //Cycle through the 4 digit slots on the bubble display by manipulating common cathode state flags, printing the correct number for each.
  for (uint8_t digit_slot_number = 4; digit_slot_number >= 1; digit_slot_number--) // Start with the 4th least significant digit as it changes the fastest.
  {

    switch (digit_slot_number)
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
      asdp_flag = HIGH; //Place the decimal point after the 2nd digit, for a maximum display time of 99.99 seconds.
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

    //Print a single digit by manipulating anode segment state flags.
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

    //Activate anode segments accordingly based on anode flag states.
    digitalWrite(ASA, asa_flag);
    digitalWrite(ASB, asb_flag);
    digitalWrite(ASC, asc_flag);
    digitalWrite(ASD, asd_flag);
    digitalWrite(ASE, ase_flag);
    digitalWrite(ASF, asf_flag);
    digitalWrite(ASG, asg_flag);
    digitalWrite(ASDP, asdp_flag);

    while (micros() % DIGIT_DISPLAY_DELAY_US > 0) //Delay prior to displaying the next digit.
    {
    }
  }
}

void ISR_start_stop_press() //Interrupt service routine that handles stopping or starting of stop watch.
{

  noInterrupts(); //Prevent other interrupts.

  //Local variable declarations.
  static uint32_t previous_press_time_ms = 0; //Previous time noted for debouncing.
  uint32_t current_press_time_ms = millis();  //Current time noted for debouncing.

  if ((current_press_time_ms - previous_press_time_ms) > DEBOUNCE_DELAY_MS) //Code segment that handles a start/stop timer request, with button debounce.
  {
    if (stopped_state_flag == false)
    {
      stopped_state_flag = true; //Set flag to true to indicate a stop stop watch request.
    }
    else if (stopped_state_flag == true)
    {
      stopped_state_flag = false; //Set flag to false to indicate a start stop watch request.
    }
    previous_press_time_ms = current_press_time_ms; //Updates previous time to facilitate correct debounce timing.
  }
  interrupts(); //Re-enable other interrupts.
}

void ISR_reset_press() //Interrupt service routine that handles resetting of stop watch to 0 seconds.
{

  noInterrupts(); //Prevent other interrupts.

  //Local variable declarations.
  static uint32_t previous_press_time_ms = 0; //Previous time noted for debouncing.
  uint32_t current_press_time_ms = millis();  //Current time noted for debouncing.

  if ((current_press_time_ms - previous_press_time_ms) > DEBOUNCE_DELAY_MS) //Code segment that handles a reset timer request, with button debounce.
  {

    reset_requested_flag = true;
    previous_press_time_ms = current_press_time_ms; //Updates previous time to facilitate correct debounce timing.
  }
  interrupts(); //Re-enable other interrupts.
}
