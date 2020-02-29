/**
 * @file integrated_support_score.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */

#include <stdlib.h>
/**
 * @param[in] p_alpha Pointer to alpha value
 * @param[in] pp_y_value Pointer to principal component
 * @param[in] no_sensor Stores the no of sensor
 * @param[in] m Stores the first m value to be consider for principal component and alpha value
 * @return The pointer to Integrated Score(Z)
 * @brief This function computes the integrated support degree score of all sensors .
 */
double *compute_integrated_score(double *p_alpha,double **pp_y_value,int no_sensor,int m){

    double *p_Z;
    /*
     * Allocate the memory to pointer p_Z
     */
    p_Z=(double *)malloc(sizeof(double) * no_sensor);

    /*
     * Compute *p_Z which is equal to  (*p_alpha) * (**pp_y_value) and iterate it to take first m elements
     */
    for(int i=0;i<no_sensor;i++){
        p_Z[i]=0;
        for(int j=0;j<m;j++){
                p_Z[i]=p_Z[i]+(p_alpha[j] * pp_y_value[j][i]);
        }
    }
    return p_Z;
}
