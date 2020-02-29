/**
 * @file weight_coefficient_sensor.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <stdlib.h>
#include <sensor_structure.h>

/**
 * @param[in] p_sensor Pointer to sensor
 * @param[in] p_Z Pointer to integrated score Z
 * @param[in] p_discard_index Pointer to discard_index which specifies which sensor are valid and invalid
 * @param[in] no_sensor Stores the no_sensor
 * @return It will return the fused output
 * @brief This function computes the weight coefficient factor for all the valid sensors and then computes the fused output
 */
double weight_coefficient(sensor_t *p_sensor, double *p_Z ,int *p_discard_index,int no_sensor){

    /*
    Calculate the Z_sum for value with p_discard_index = 0
    */
    double Z_sum=0;

    /*
    *Compute the sum of Z  such that discard_index = 0
    * Variable to count no of 0's, because i != j
    */
    int index_counter=0;
    for(int i=0;i<no_sensor;i++){
        if(p_discard_index[i] == 0){
            Z_sum=Z_sum+p_Z[i];
            index_counter++;
        }
    }
    /*
     * Calculate the weight coefficient factor for value with p_discard_index =0 ,
     * If p_discard_index =1 , then that sensor is invalid and cannot be used for latter computation
     */
    double *p_weight_coefficient=(double *)malloc(sizeof(double) * index_counter);
    int internal_counter=0;

    for(int i=0;i<no_sensor;i++){
        if(p_discard_index[i] == 0){
            p_weight_coefficient[internal_counter]=p_Z[i] /Z_sum;
            internal_counter++;
        }
    }

    internal_counter=0;
    /*
     * Create the dynamic array p_sensor__value for p_discard_index == 0
     */
    double *p_sensor_value=(double *)malloc(sizeof(double) * index_counter);
    for(int i=0;i<no_sensor;i++){
        if(p_discard_index[i] == 0){
            p_sensor_value[internal_counter]=(p_sensor+i)->data;
            internal_counter++;
        }
    }

    /*
     * Compute the fused output
     */
    double fused_output=0;
    for(int i=0;i<index_counter;i++){
        fused_output=fused_output+(p_sensor_value[i] * p_weight_coefficient[i]);
    }

    /*
    * free the memory
    */
    free(p_sensor_value);
    free(p_weight_coefficient);
    return fused_output;
}