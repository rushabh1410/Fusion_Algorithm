/**
 * @file sensor_fusion_algorithm.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <sensor_fusion_algorithm.h>
#include <stdlib.h>
/**
 * @param p_sensor Pointer to struct sensot_t
 * @param no_sensor Stores the no of sensor
 * @return It will return the fused output
 * @brief This function calls all the other function required to compute the fused output.
 * @see sensor_structure.h
 * @see support_degree_matrix.h
 * @see eigen.h
 * @see principal_component.h
 * @see contribution_rate_k_component.c
 * @see contribution_rate_m_component.c
 * @see integrated_support_score.h
 * @see eliminate_incorrect_data.h
 * @see weight_coefficient_sensor.h
 */
double sensor_fusion(sensor_t *p_sensor,int no_sensor){

    int m;
    double **pp_D_array;
    /*
    *Call Step1 of Algorithm
    */
     pp_D_array=compute_support_degree_matrix(p_sensor,no_sensor);

    /*
    *Call Step2 of Algorithm
    */
    double *p_eigen_val;
    double **pp_eigen_vector;

    p_eigen_val=(double *)malloc(sizeof(double) * no_sensor);

    pp_eigen_vector=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_eigen_vector[i]=(double *) malloc(sizeof(double) * no_sensor);
    }

    compute_eigen(pp_D_array,no_sensor,p_eigen_val,pp_eigen_vector);

    /*
     * Call the step 3 of Algorithm
     */
    double **pp_y_principal_component;
    pp_y_principal_component=compute_principal_component(pp_eigen_vector,pp_D_array,no_sensor);

    /*
     * Call the step4 of Algorithm
     */
    double * p_alpha;
    p_alpha=compute_contribution_K_rate(p_eigen_val,no_sensor);

    /*
     *Call step5 of algorithm
     */
    m=compute_contribution_M_rate(p_alpha,no_sensor,0.85);

    /*
     * Call step 6 of algorithm
     */
    double *p_Z;
    p_Z=compute_integrated_score(p_alpha,pp_y_principal_component,no_sensor,m);

    /*
     * Call Step7(1) of an algorithm
     */
    int *p_discard_index=eliminate_data(p_Z,0.7,no_sensor);

    /*
     * Call Step7(2) of an algorithm
     */
    double fused_output=weight_coefficient(p_sensor,p_Z,p_discard_index,no_sensor);

    /*
     * Free the acquired memory
     */
    free(pp_D_array);
    free(p_eigen_val);
    free(pp_eigen_vector);
    free(pp_y_principal_component);
    free(p_alpha);
    free(p_Z);
    free(p_discard_index);
    return fused_output;
}