/*
 * Blink 2 LEDs from the MSP430 board when you press
 * S1 or S2. Each LED corresponds to the switch - S1 -> LED1
 */


#include <msp430.h> 


#define S1 BIT1
#define S2 BIT2
#define LED1 BIT0
#define LED2 BIT7


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 = 0xFFFE;           // to enable inputs and outputs

    P1REN |= S1;            //enable pull-up/pull-down resistor for S1
    P1OUT |= S1;            //set S1 using pull-up resistor
    P1REN |= S2;            //enable pull-up/pull-down resistor for S2
    P1OUT |= S2;            //set S2 using pull-up resistor
    P1DIR |= LED1;          //set P1.0 to output
    P1OUT &= ~LED1;         //set LED1 to off
    P9DIR |= LED2;          //set P9.7 to output
    P9OUT &= ~LED2;         //set LED2 to off

    for (;;) {                  //loop forever
        if ((P1IN & S1) == 0) { //Is S1 pressed?
            P1OUT |= LED1;      //yes, turn on LED1
        }
        else {
            P1OUT &= ~LED1;      //No, turn off LED1
        }

        if ((P1IN & S2) == 0) { //Is S2 pressed?
            P9OUT |= LED2;      //yes, turn on LED2
        } else {
            P9OUT &= ~LED2;     //No, turn off LED2
        }
    }
}
