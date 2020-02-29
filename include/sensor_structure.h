/**
 * @file sensor_structure.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This file contains the declaration of sensor structure to hold the sensor time,name and data
 */
#ifndef FUSIONALGORITHM_SENSOR_STRUCTURE_H
#define FUSIONALGORITHM_SENSOR_STRUCTURE_H
typedef struct{
    char time[6];
    char name[10];
    double data;
}sensor_t;

#endif //FUSIONALGORITHM_SENSOR_STRUCTURE_H
