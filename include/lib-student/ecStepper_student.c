#include "stm32f4xx.h"
#include "ecStepper_student.h"

//State number 
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7


// Stepper Motor function
uint32_t direction = 1; 
uint32_t step_delay = 100; 
uint32_t step_per_rev = 64*32;
	 

// Stepper Motor variable
volatile Stepper_t myStepper; 


//FULL stepping sequence  - FSM
typedef struct {
	uint8_t out;
  uint32_t next[2];
} State_full_t;

State_full_t FSM_full[4] = {  
 {0b1001,{S1,S2}},
 // YOUR CODE
 // YOUR CODE
 // YOUR CODE
};

//HALF stepping sequence
typedef struct {
	uint8_t out;
  uint32_t next[2];
} State_half_t;

State_half_t FSM_half[8] = { 
 {0b1001,{S1,S2}},
 // YOUR CODE
 // YOUR CODE
 // YOUR CODE
 // YOUR CODE
 // YOUR CODE
 // YOUR CODE
 // YOUR CODE
};



void Stepper_init(GPIO_TypeDef* port1, int pin1, GPIO_TypeDef* port2, int pin2, GPIO_TypeDef* port3, int pin3, GPIO_TypeDef* port4, int pin4){
	 
//  GPIO Digital Out Initiation
	 myStepper.port1 = port1;
   myStepper.pin1  = pin1;
	 // Repeat for port2,pin2~port4,pin4 
		// YOUR CODE 
		// YOUR CODE 
		// YOUR CODE 
		// YOUR CODE 
	
	
	
//  GPIO Digital Out Initiation
		// No pull-up Pull-down , Push-Pull, Fast	
		// Port1,Pin1 ~ Port4,Pin4
		// YOUR CODE 
		// YOUR CODE 
		// YOUR CODE 
		// YOUR CODE 

	
}

void Stepper_pinOut (uint32_t state, int mode){
	
	   if (mode == FULL){         // FULL mode
			GPIO_write(myStepper.port1, myStepper.pin1, 		// YOUR CODE_____);
  		 // Repeat for port2,pin2~port4,pin4 
				// YOUR CODE 
				// YOUR CODE 
				// YOUR CODE 

			}	 
		 else if (mode == HALF){    // HALF mode
			 	// YOUR CODE 
				// YOUR CODE 
				// YOUR CODE 
				// YOUR CODE 
			}
}


void Stepper_setSpeed (long whatSpeed){      // rppm
		step_delay = 	_________//YOUR CODE   // Convert rpm to milli sec
}


void Stepper_step(int steps, int direction, int mode){
	 uint32_t state = 0;
	 myStepper._step_num = steps;

	 for(; myStepper._step_num > 0; myStepper._step_num--){ // run for step size
				// YOUR CODE                                  		// delay (step_delay); 
					 
		    if (mode == FULL) 		 												
						state = ___________// YOUR CODE       // state = next state
				else if (mode == HALF) 
						state = ___________// YOUR CODE       // state = next state
				
				Stepper_pinOut(state, mode);
   }
}


void Stepper_stop (void){ 
     
    	myStepper._step_num = 0;    
			// All pins(Port1~4, Pin1~4) set as DigitalOut '0'
			 	// YOUR CODE 
				// YOUR CODE 
				// YOUR CODE 
				// YOUR CODE 
}

