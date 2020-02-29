/**
 * @file contribution_rate_m_component.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <stdlib.h>

/**
 * @param[in] p_alpha_value Pointer to alpha value
 * @param[in] no_sensor Stores the no of sensor
 * @param[in] p Value specified by user
 * @return It will return the first m principal component
 * @brief This function computes the step5 of algorithm .It computes the contribution rate based on alpha value
 * @see contribution_rate_k_component.h
 */
int compute_contribution_M_rate(double *p_alpha_value,int no_sensor,double p){

    int m;
    double *p_m_rate;
    p_m_rate=(double *)malloc(sizeof(double) * no_sensor);

    /*
     * Compute all p_m_rate value
     */
    for(int i=0;i<no_sensor;i++){
        double sum=0.0;
        for(int j=0;j<=i;j++){
            sum=sum+p_alpha_value[j];
        }
        p_m_rate[i]=sum;
    }

    /*
     * Return only first p_m_rate value such p_m_rate > p
     * where p is the parameter of algorithm specified by user or if not specified by user it will take default value of 0.85
    */
     for(int i=0;i<no_sensor;i++){
        if(p_m_rate[i] > p){
            m=i+1;
            break;
        }
    }
     /*
      * Free the memory
      */
    free(p_m_rate);
    return m;
}
