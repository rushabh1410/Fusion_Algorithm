/**
 * @file support_degree_matrix.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <sensor_structure.h>
#include <math.h>
#include <stdlib.h>

/**
 * @param[in] p_sensor Pointer to sensor data
 * @param[in] no_sensor It contains the no of sensor at particular time
 * @return It returns 2D array
 * @brief
 * This is the first step of sensor fusion algorithm, where user pass the raw data of sensor.<br>
 * The output of this function is symmetric matrix which is further passed to compute_eigen function.
 * @see eigen.h
 */
double **compute_support_degree_matrix(sensor_t *p_sensor,int no_sensor){

    /*
    Declare dynamic 2D array
    */
    double **pp_D_array;

    /*
    Allocating memory for rows=no_sensor
    */
     pp_D_array=(double **)malloc(sizeof(double *) * no_sensor);

    /*
    Allocating memory for columns in each row
    */
     for(int rows=0;rows<no_sensor;rows++){
        pp_D_array[rows]= (double *)malloc(sizeof(double) * no_sensor);
    }

    /*
     Compute matrix D
     1.Compute temp_data
     2.Compute absolute of temp_data using fabs() function
     3.Compute exponential using exp()
     */
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++){
            double temp_data=((p_sensor+rows)->data)-((p_sensor+cols)->data);
            pp_D_array[rows][cols]=exp(-fabs(temp_data));
        }
    }
    return pp_D_array;
}
