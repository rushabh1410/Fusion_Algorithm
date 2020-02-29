/**
 * @file stuck_sensor.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <sensor_structure.h>
#include <time_structure.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * @brief The function declaration for calculating the time difference
 */
time_tt time_diff(time_tt curr_time,time_tt next_time);

/**
 * @param p_sensor Pointer to structure sensor_t which contains sensor time,name and data
 * @param p_time_list Pointer to structure time_tt and it stores the unique time value
 * @param interval Stores the time interval at which stuck sensor is computed
 * @param time_list_length Stores the length of unique time
 * @param line_counter Stores the no of line of input .csv file
 * @brief This function computes the sensor that are stuck at interval specified by user.If not specified by user,<br>
 *         it will take the default value = 0:10
 * @see sensor_structure.h
 * @see time_structure.h
 */
void compute_stuck_sensor(sensor_t *p_sensor,time_tt *p_time_list,time_tt interval,int time_list_length,int line_counter){

    /*
     * It is assumed that input .csv file is sorted and time is in increasing order and even next day is not considered
     * So, number of sensor in each group is computed
     */
    int no_sensor_grp=line_counter/time_list_length;
    FILE *fptr;
    /*
     Open the file in write mode
     The file is generated in data/stuck_sensor.txt
     */
    fptr=fopen("../data/stuck_sensor.txt","w");
    if(fptr == NULL){
        printf("Error in creating the file stuck sensor.txt");
    }

    int sensor_counter=0;

    for(int i=1;i<time_list_length;i++) {
        /*
         * Get the current time data
         */
        time_tt curr_time=p_time_list[i-1];
        /*
         *Get the next time data
         */
        time_tt next_time=p_time_list[i];
        /*
         * Calculate the difference of time interval between current time and nexts time
         */
        time_tt diff=time_diff(curr_time,next_time);

        fputs("Time =\t",fptr);
        fprintf(fptr, "%d : %d\t", curr_time.tm_hour,curr_time.tm_min);
        fputs("Interval =\t",fptr);
        fprintf(fptr, "%d : %d\n", interval.tm_hour,interval.tm_min);
        fputs("===================================================\n",fptr);
        /*
         * If interval given by user and interval computed in previous step is same then,
         * it checks the sensor data with corresponding sensor name and if sensor data is same then,
         * the sensor is stuck
         */
        if((diff.tm_hour == interval.tm_hour) && (diff.tm_min == interval.tm_min)){

            for(int j=sensor_counter;j<sensor_counter+no_sensor_grp;j++){
                if((p_sensor+j) ->data == (p_sensor+(j+no_sensor_grp)) ->data){
                    fprintf(fptr," %s %s\n",(p_sensor+j)->name,"stuck");
                }
                else{
                    fprintf(fptr," %s %s\n",(p_sensor+j)->name,"Not stuck");
                }
            }
        }
        else{
            fputs("No sensor stuck\n",fptr);
        }
        sensor_counter=sensor_counter+no_sensor_grp;
        /*
        This condition is for the last time value
        Since it is last time value ,it will never get stuck
        */
        if(i == time_list_length -1){
            fputs("Time =\t",fptr);
            fprintf(fptr, "%d : %d\t", next_time.tm_hour,next_time.tm_min);
            fputs("Interval =\t",fptr);
            fprintf(fptr, "%d : %d\n", interval.tm_hour,interval.tm_min);
            fputs("===================================================\n",fptr);
            fputs("No sensor stuck\n",fptr);
        }
    }
}
/**
 * @param curr_time Pointer to structure time_tt which holds current time
 * @param next_time Pointer to structure time_tt which holds next time
 * @return It will return the time difference
 * @brief This function calculates the time difference between the current time and next time
 * @see stuck_sensor.h
 */
time_tt time_diff(time_tt curr_time,time_tt next_time){

    int diff_min;
    time_tt diff;
    /*
     * Calculate the difference of time interval between the current time and next time
     * Does not consider the next day
     */
    diff_min=abs((next_time.tm_hour * 60+next_time.tm_min) - (curr_time.tm_hour * 60 +curr_time.tm_min));
    diff.tm_hour=diff_min / 60;
    diff.tm_min=diff_min % 60;
    return diff;
}

