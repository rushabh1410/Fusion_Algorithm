/**
 * @file contribution_rate_k_component.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <stdlib.h>

/**
 * @param[in] p_eigen_value Pointer to eigen value
 * @param[in] no_sensor Stores the no of sensor
 * @return It return pointers(1-D array) to Alpha value
 * @brief This function computes the contribution rate of Kth component (Step4 of sensor fusion Algorithm).
 * @see eigen.h
 */
double *compute_contribution_K_rate(double *p_eigen_value,int no_sensor){
        double *p_alpha;
        /*
         * Allocate the memory equal to no of sensor
         */
        p_alpha=(double *)malloc(sizeof(double) * no_sensor);

        /*
         * Step1 Compute the sum of eigen value
         */
        double sum_eigen_value =0.0;
        for(int i=0;i<no_sensor;i++){
            sum_eigen_value=sum_eigen_value+p_eigen_value[i];
        }
        /*
         * Step2 Compute alpha value for each sensor
         */
        for(int i=0;i<no_sensor;i++){
            p_alpha[i]=p_eigen_value[i] / sum_eigen_value;
        }

        return p_alpha;
}