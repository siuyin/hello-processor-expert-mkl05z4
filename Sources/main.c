/* ###################################################################
 **     Filename    : main.c
 **     Project     : junk
 **     Processor   : MKL05Z32VFM4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-07-19, 13:22, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PTB.h"
#include "SysTick.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "GPIO_PDD.h"
#include <stdbool.h>

extern volatile unsigned int tick;

enum button_msg_t {
	bReleased, bPushed
};
static enum button_msg_t button_msg;
enum button_state_t {
	sReleased, sMaybeReleased, sPushed
};
bool buttonPushed(void) {
	if (GPIO_PDD_GetPortDataInput(GPIOB_BASE_PTR) & GPIO_PDD_PIN_0) { // button is active low
		return false;
	}
	return true;
}
void toggleButtonMessage(void){
	if (button_msg == bPushed){
		button_msg = bReleased;
		return;
	}
	button_msg = bPushed;
}
void check_button_task(void) {
	static unsigned int nrt;	// next run tick
	if (tick != nrt) {
		return;
	}

	nrt += 25;	// next run in x ticks

	static enum button_state_t state;
	switch (state) {
	case sReleased:
		if (buttonPushed()) {
			state = sPushed;
			toggleButtonMessage();
		} else {
			state = sReleased;
		}
		break;
	case sPushed:
		if (buttonPushed()) {
			state = sPushed;
		} else {
			state = sMaybeReleased;
		}
		break;
	case sMaybeReleased:
		if (buttonPushed()) {
			state = sPushed;
		} else {
			state = sReleased;
		}
		break;
	}

}

enum led_state_t {
	B, R, G
};
void turnOffLEDs(void) {
	GPIO_PDD_SetPortDataOutputMask(GPIOB_BASE_PTR,
			GPIO_PDD_PIN_8+GPIO_PDD_PIN_9+GPIO_PDD_PIN_10);	// Set: LEDs are inverted logic. PDD stands for Physical Device Drivers
}
void turnOnLED(enum led_state_t led) {
	turnOffLEDs();
	switch (led) {
	case R:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_8);
		break;
	case G:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_9);
		break;
	case B:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_10);
		break;
	}
}
void toggle_LED_task(void) {
	static unsigned int nrt;	// next run tick
	static enum led_state_t state = B;// so that the next state is R and starts from R.

	if (tick != nrt) {
		return;
	}

	if (button_msg == bPushed) {
		nrt += 125;	// schedule the next task run in x ticks
	} else {
		nrt += 500;
	}

	switch (state) {
	case R:
		state = G;
		turnOnLED(G);
		break;
	case G:
		state = B;
		turnOnLED(B);
		break;
	case B:
		state = R;
		turnOnLED(R);
		break;
		void turnOnGreenLED(void) {
			turnOffLEDs();
			GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_9);
		}
		void turnOnBlueLED(void) {
			turnOffLEDs();
			GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_10);
		}
		void turnOnRedLED(void) {
			turnOffLEDs();
			GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_8);
		}
	}

}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	while (1) {
		check_button_task();
		toggle_LED_task();
	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
