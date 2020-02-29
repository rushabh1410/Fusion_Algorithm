/**
 * @file stuck_sensor.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This file contains the declaration of function used to compute the stuck sensor
 */
#ifndef FUSIONALGORITHM_STUCK_SENSOR_H
#define FUSIONALGORITHM_STUCK_SENSOR_H
#include <sensor_structure.h>
#include <time_structure.h>

void compute_stuck_sensor(sensor_t *p_sensor,time_tt *p_time_list,time_tt interval,int time_list_length,int line_counter);

#endif //FUSIONALGORITHM_STUCK_SENSOR_H
