/*
 * sensor.c
 *
 *  Created on: Nov 16, 2019
 *      Author: User
 */

#include "sensor.h"
#include "msp.h"
#include <stdio.h>

void readTempSensor(float * result) {
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 |  // SMCLK
            TIMER_A_CTL_MC_2 |      // CONTINUOUS mode
            TIMER_A_CTL_CLR;       // Clear TAR

    P4->SEL0 &= ~BIT1;
    P4->SEL1 &= ~BIT1;
    P4->DIR &= ~BIT1;
    P4->REN |= BIT1;
    P4->OUT |= BIT1;
    __delay_cycles(3000);

    P1->REN &= ~BIT7;
    P1->DIR |= BIT7;
    P1->OUT &= ~BIT7;
    __delay_cycles(3300);

    P1->DIR &= ~BIT7;
    P1->REN |= BIT7;
    P1->OUT |= BIT7;
    __delay_cycles(165);


    while ((P1->IN & BIT7) != 0);

    while ((P1->IN & BIT7) == 0);

    int cycles[80];
    int i, start;

    while ((P1->IN & BIT7) != 0);

    for (i = 0; i < 80; i += 2) {
        TIMER_A0->CTL |= TIMER_A_CTL_CLR;
        while ((P1->IN & BIT7) == 0);
        cycles[i] = TIMER_A0->R;

        TIMER_A0->CTL |= TIMER_A_CTL_CLR;
        while ((P1->IN & BIT7) != 0);
        cycles[i + 1] = TIMER_A0->R;
    }

    unsigned char data[5];
    for (i = 0; i < 40; ++i) {
        uint32_t lowCycles = cycles[2 * i];
        uint32_t highCycles = cycles[2 * i + 1];

        data[i / 8] <<= 1;

        if (highCycles > lowCycles) {
            data[i / 8] |= 1;
        }
    }

    if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        result[0] = parseCelcius(data);
        result[1] = parseHumidity(data);

        if((result[0] > 29 ) & (result[1] > 70)){
            printf("\nTemp and humidity HIGH");
        }
        return result;
    }

    return 0;
}

float parseCelcius(unsigned char * data) {
    float f = ((short)(data[2] & 0x7F)) << 8 | data[3];
    f *= 0.1;
    if (data[2] & 0x80) {
        f *= -1;
    }
    return f;
}

float parseHumidity(unsigned char * data) {
    float f =((short)data[0]) << 8 | data[1];
    f *= 0.1;
    return f;
}