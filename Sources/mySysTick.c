/*
 * mySysTick.c
 *
 *  Created on: 20 Jul, 2020
 *      Author: siuyin
 */

volatile unsigned int tick;
void mySysTick(void) {
	tick++;
}

