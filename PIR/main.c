#include "msp.h"
#include "stdio.h"


/**
 * main.c
 */

void setup(){
    P6SEL0 = 0;
    P6SEL1 = 0;
    P1SEL0 = 0;
    P1SEL1 = 0;
    P6DIR &= ~BIT0;
    P1DIR |= BIT0;
}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	setup();
	while(1){

	    if(P6IN & BIT0){
	        printf("Object Detected!\n");
	        P1OUT |= BIT0;
	        __delay_cycles(100);
	    }
	    else{
	        printf("No object detected!\n");
	        P1OUT &= ~BIT0;
	        __delay_cycles(100);
	    }
	}
}
