/**
 * @file eigen.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This files conatins the declaration of function used for computing the eigen value and eigen vector for symmetric matrix.
 */
#ifndef FUSIONALGORITHM_EIGEN_H
#define FUSIONALGORITHM_EIGEN_H

int compute_eigen(double **pp_D_array,int no_sensor, double *p_eigen_val,double **pp_eigen_vec);

#endif //FUSIONALGORITHM_EIGEN_H
