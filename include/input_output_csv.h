/**
 * @file input_output_csv.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This file contains the declaration of functions that parses the .csv file and write the fused output along with
 * validated sensor to file
 */
#ifndef FUSIONALGORITHM_INPUT_OUTPUT_CSV_H
#define FUSIONALGORITHM_INPUT_OUTPUT_CSV_H
#include <sensor_structure.h>

int read_csv(FILE *p_fptr, sensor_t *p_sensor);
int write_output_file(FILE *p_fptr,sensor_t *p_sensor,int no_sensor, double fusedOutput);

#endif //FUSIONALGORITHM_INPUT_OUTPUT_CSV_H
