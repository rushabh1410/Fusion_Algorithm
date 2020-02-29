/**
 * @file validate_sensor.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <time_structure.h>
#include <sensor_structure.h>
#include <unique_time.h>
#include <string.h>
/**
 * <p>This function computes the number of sensors at a particular time and filter the data of out of range sensors.</p>
 * @param[in] p_sensor
 * @param[in] min
 * @param[in] max
 * @param[in] line_counter
 * @param[in] curr_time
 * @param[out] v_sensor
 * @return It will return the no of sensors which are within the specified range.
 * @brief This function finds the sensors which are out of range. The range is specified by user from command line.
 * It will return the no of sensors which are within the specified range and also stores the data of valid sensor into v_sensor.
 * This new no of sensors and v_sensor are passed into fusion algorithm.
 */
int compare_sensor_range(sensor_t *p_sensor,double min ,double max,int line_counter,time_tt curr_time,sensor_t *v_sensor){

    int length=0;
    for(int i=0; i < line_counter; i++) {
        time_tt time;
        time=time_parse((p_sensor + i)->time,time);
        if((time.tm_hour == curr_time.tm_hour) && (time.tm_min == curr_time.tm_min)) {

            if (min <= ((p_sensor + i)->data) && ((p_sensor + i)->data) <= max) {
                strcpy((v_sensor + length)->time, (p_sensor + i)->time);
                strcpy((v_sensor + length)->name, (p_sensor + i)->name);
                (v_sensor + length)->data = (p_sensor + i)->data;
                length++;
            } else {
                if (!(p_sensor + i)->time) {
                    break;
                } else
                    continue;
            }
        }
    }
    return length;
}