/*	Author: kma023
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define A0 (PINA & 0x01)

enum states {start, releaseA, pressedA, releaseB, pressedB} state;

void sm() {
	switch(state) {
		case start:
			state = releaseA;
			break;
		case releaseA:
			if(A0) {
				state = pressedB;
			}
			else if(!A0) {
				state = releaseA;
			}
			break;
		case pressedB:
			if(A0) {
				state = pressedB;
			}
			else if(!A0) {
				state = releaseB;
			}
			break;
		case releaseB:
			if(A0) {
				state = pressedA;
			}
			else if(!A0) {
				state = releaseB;
			}
			break;
		case pressedA:
			if(A0) {
				state = pressedA;
			}
			else if(!A0) {
				state = releaseA;
			}
			break;
		default:
			state = start;
			break;
	}
	switch(state) {
		case releaseA:
			PORTB = 0x01;
			break;
		case pressedB:
			PORTB = 0x02;
			break;
		case releaseB:
			PORTB = 0x02;
			break;
		case pressedA:
			PORTB = 0x01;
			break;
		default:
			break;
	}
}
int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = start;
	while(1) {
		sm();
	}
	
    	return 1;
}
