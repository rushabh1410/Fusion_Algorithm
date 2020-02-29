/**
 * @file sensor_fusion_algorithm.h
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 * @brief This file contains the declaration of function used to get fused output.Include this header file in application code to use  sensor fusion algorithm
 */
#ifndef FUSIONALGORITHM_SENSOR_FUSION_ALGORITHM_H
#define FUSIONALGORITHM_SENSOR_FUSION_ALGORITHM_H
#include <support_degree_matrix.h>
#include <eigen.h>
#include <principal_component.h>
#include <contribution_rate_k_component.h>
#include <contribution_rate_m_component.h>
#include <integrated_support_score.h>
#include <eliminate_incorrect_data.h>
#include <weight_coefficient_sensor.h>
#include <sensor_structure.h>

double sensor_fusion(sensor_t *p_sensor,int no_sensors);

#endif //FUSIONALGORITHM_SENSOR_FUSION_ALGORITHM_H
