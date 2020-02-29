/**
 * @file validate_sensor.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This file contains the declaration of function used for finding the sensors out of range.
 */

#ifndef FUSIONALGORITHM_VALIDATE_SENSOR_H
#define FUSIONALGORITHM_VALIDATE_SENSOR_H
#include <stdio.h>
#include <sensor_structure.h>
#include <time_structure.h>

int compare_sensor_range(sensor_t *p_sensor,double min ,double max,int line_counter,time_tt curr_time,sensor_t *v_sensor);
#endif //FUSIONALGORITHM_VALIDATE_SENSOR_H
