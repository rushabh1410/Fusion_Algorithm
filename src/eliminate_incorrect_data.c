/**
 * @file eliminate_incorrect_data.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <stdlib.h>
#include <math.h>
/**
 * @param[in] p_Z Pointer to integrated score obtained in step6
 * @param[in] fault_value It contain the fault tolerance value
 * @param[in] no_sensor Stores the no of sensor used in fusion algorithm
 * @return It return pointer to int array of discard_index.
 * @brief This function eliminates the incorrect data based on the fault tolerance theory specified by argument q.The argument <br>
 * q can be specified by user otherwise it will take the default value 0.7 .This function return the pointer to int array of<br>
 * discard_index which is set to 1 ; if particular sensor is invalid.
 * @see integrated_support_score.h
 */
int *eliminate_data(double *p_Z,double fault_value,int no_sensor){

    /*
     * Eliminate the incorrect data
     * Find the index of sensor which doesn't satisfy the given equation in paper with fault tolerance specified by the user
     */
    double Z_sum=0;
    /*
     * Initialize the the array of discarded index with 0 .
     */
    int *p_discard_index;
    p_discard_index=(int *)calloc(no_sensor, sizeof(int));

    /*
     * Compute Z_sum
     */
    for(int i=0;i<no_sensor;i++){
        Z_sum=Z_sum+p_Z[i];
    }

    double comparable_value= fabs(Z_sum/no_sensor) * fault_value;
    /*
     * Find the sensor to be eliminated.If the particular sensor is eliminated then set the corresponding discarded_index to 1.
     * Error If p_Z is satisfied then that sensor should be discarded
     * To be discarded is set to 1
     */
    for(int i=0;i<no_sensor;i++){
        if(fabs(p_Z[i]) < comparable_value){
            p_discard_index[i] =1;
        }
    }
    return p_discard_index;
}
