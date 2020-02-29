/**
 * @file weight_coefficient_sensor.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This file contains the declaration of function used to compute fused output
 */
#ifndef FUSIONALGORITHM_WEIGHT_COEFFICIENT_SENSOR_H
#define FUSIONALGORITHM_WEIGHT_COEFFICIENT_SENSOR_H
#include <stdio.h>
#include <sensor_structure.h>

double weight_coefficient(sensor_t *p_sensor, double *p_Z ,int *p_discard_index,int no_sensor);

#endif //FUSIONALGORITHM_WEIGHT_COEFFICIENT_SENSOR_H
