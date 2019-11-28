/*
 * sensor.h
 *
 *  Created on: Nov 16, 2019
 *      Author: User
 */

#ifndef SENSOR_H_
#define SENSOR_H_

void readTempSensor(float * result);
float parseCelcius(unsigned char * data);
float parseHumidity(unsigned char * data);



#endif /* SENSOR_H_ */
