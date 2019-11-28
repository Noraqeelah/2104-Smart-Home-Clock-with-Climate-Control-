#include "sensor.h"
#include "msp.h"
#include <stdio.h>

float result[2];
int i;
void main(void){

    for(;;){
    readTempSensor(result);
    printf("\nTemp: %fC \t Humidity: %f %", result[0], result[1]);
    for(i=0; i<600000; i++);
    }
}
