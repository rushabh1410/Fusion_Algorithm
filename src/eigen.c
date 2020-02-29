/**
 * @file eigen.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>
/**
 *
 * @param[in] pp_D_aaray[in] Pointer to 2D array obtained from step1 of algorithm
 * @param[in] no_sensor[in] It contains the no of sensor at particular time
 * @param[out] p_eigen_val[inout] Pointer to eigen value
 * @param[out] pp_eigen_vec[inout] Pointer to eigen vector
 * @return It will return 1 on success
 * @brief
 * <p>This function computes the eigen value and eigen vector of symmetric matrix obtained from step1 of algorithm.
 * It will arrange the eigen value in descending order.<br>
 * GSL library is used for computing the eigen value and eigen vector.
 * In order to install the GSL ; see the INSTALL file</p>
 * @see support_degree_matrix.h
 */
int compute_eigen(double **pp_D_aaray,int no_sensor, double *p_eigen_val,double **pp_eigen_vec){

    /*
    Convert the 2D matrix pp_D_array into gsl matrix with dimensions equal to no_sensor
    Allocate the memory
    */
    gsl_matrix *p_matrix=gsl_matrix_alloc(no_sensor,no_sensor);

    /*
    Assign the value to gsl_matrix
    */
    for (int rows = 0; rows < no_sensor; rows++){
        for (int cols = 0; cols < no_sensor; cols++){
            gsl_matrix_set(p_matrix, rows, cols, pp_D_aaray[rows][cols]);
        }
    }

    /*
    Allocate the temporary memory to eigen value equal to no_sensor
     */
    gsl_vector *p_eval = gsl_vector_alloc (no_sensor);

    /*
    Allocate the temporary memory to eigen vector equal to no_sensor
     */
    gsl_matrix *p_evec = gsl_matrix_alloc (no_sensor, no_sensor);

    /*
    Create the temporary eigen computation workspace
    */
    gsl_eigen_symmv_workspace * p_w = gsl_eigen_symmv_alloc (no_sensor);

    /*
    Compute the eigen value and vector
    */
    gsl_eigen_symmv (p_matrix, p_eval, p_evec, p_w);

    /*
    Free the memory of workspace
    */
    gsl_eigen_symmv_free (p_w);

    /*
    Arrange it in ascending order
    */
    gsl_eigen_symmv_sort (p_eval, p_evec,GSL_EIGEN_SORT_VAL_DESC);

    /*
    Assign the compute eval and evec to p_eigen_val,p_eigen_vec
     */
    for (int rows = 0; rows < no_sensor; rows++){
        p_eigen_val[rows]= gsl_vector_get (p_eval, rows);
        /*
         For getting the eigen vector and arrange it in row form instead of column form which Transpose the eigen vector
        */
        for(int cols=0;cols<no_sensor;cols++){
            pp_eigen_vec[rows][cols]=gsl_matrix_get(p_evec, cols, rows);
        }
    }
    /*
    Free the eigen value and eigen vector
    */
    gsl_vector_free (p_eval);
    gsl_matrix_free (p_evec);
    /*
     Return 1 on success
     */
    return 1;
}
