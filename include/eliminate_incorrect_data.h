/**
 * @file eliminate_incorrect_data.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This file contains the declaration of function used for computing step7 of Algorithm(Eliminate the incorrect data)
 */
#ifndef FUSIONALGORITHM_ELIMINATE_INCORRECT_DATA_H
#define FUSIONALGORITHM_ELIMINATE_INCORRECT_DATA_H

#include <sensor_structure.h>

int *eliminate_data(double *p_Z,double fault_value,int no_sensor);
#endif //FUSIONALGORITHM_ELIMINATE_INCORRECT_DATA_H
