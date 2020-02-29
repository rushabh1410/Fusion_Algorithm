/**
 * @file unique_time.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */

#include <stdlib.h>
#include <string.h>
#include <unique_time.h>

int strcontain(char *time,char **unique_time,int length_unique_time);
/**
 * @param p_sensor Pointer to struct sensor_t
 * @param line_counter Holds the total no of lines in .csv file
 * @param length_time_list Stores the length of unique time list
 * @return It will return pointer to struct time_tt
 * @brief This functions computes the unique time and return the pointer to struct time_tt.
 * @see sensor_structure.h
 */
time_tt* get_time_list(sensor_t *p_sensor,int line_counter,int length_time_list){

    /*
    Compute the no of sensors
    */
    int no_sensor_grp=line_counter/length_time_list;

    time_tt *p_time_list;
    /*
    Allocate the memory to pointer of type time_tt which is equal to no of unique time in csv file
    */
    p_time_list=(time_tt *)malloc(sizeof(time_tt) * length_time_list);

    char sensor_time[6];
    int time_counter=0;
    /*
     *Compute the unique time and parse the time in format of structure time_tt
     */
    for(int i=0;i<line_counter;i+=no_sensor_grp){
        strcpy(sensor_time,(p_sensor+i)->time);
        p_time_list[time_counter]=time_parse(sensor_time,p_time_list[time_counter]);
        time_counter++;
    }
    return p_time_list;
}

/**
 * @param[in] time Array of character for holding time from sensor structure
 * @param[out] time1
 * @return It will return the time in form of time_tt
 * @brief This function parses the string of type "1:20" and assign it to type time_tt struct in form of hour and min.
 * @see time_structure.h
 */

time_tt time_parse(char time[6],time_tt time1){
    char *token;
    char time_arr[6];
    int token_counter=1;

    strcpy(time_arr,time);
    token=strtok(time_arr,":");
    while(token != NULL){
        if(token_counter == 1)
        {
            time1.tm_hour=atoi(token);
        }else if(token_counter == 2)
        {
            time1.tm_min=atoi(token);
        }
        token = strtok(NULL, ":");
        token_counter++;
    }
    free(token);
    return time1;
}
/**
 * @param[in] p_sensor Pointer to sensor data
 * @param[in] line_counter Stores the total no of lines of csv file
 * @return It will return the total no of unique time
 * @brief This function computes the length of unique time
 */
int get_uniquetime_length(sensor_t *p_sensor,int line_counter){

    /*
    *Declare the variable to store the length of 2D unique_time array
    * Declare the 2D array unique_time to store multiple unique strings
    */
    char **unique_time;
    unique_time=(char **)malloc(sizeof(char *) *line_counter);
    for(int i=0;i<line_counter;i++){
        unique_time[i]=(char *)malloc(sizeof(char) * 6);
    }

    /*
     * It is initialize to 1 because there will be at least one unique value and it increases as we find the another unique value
     */
    int length_unique_time=1;

    /*
    There will at least one unique string so 1st string is copied .
    */
     strcpy(unique_time[0],(p_sensor+0)->time);

    /*
     * The line_counter is declare as extern variable so ,
     * it is declare and defined in main.c as global variable but it's reference is used here
     * The loop will iterate till the end of .csv file to get the unique value of time
     * It internally calls strcontain() function which takes two argument i.e. current value of time from chosen line and array of unique_time
     * The strcontain() function return 1 if time value is present in unique_time
     * It return 0 if time value is not present in unique_time (which also means that time value is unique so add it in unique_time array)
     */
    for(int i=0;i<line_counter;i++){
        int result=strcontain((p_sensor+i)->time,unique_time,length_unique_time);
        //1 means true and 0 means false
        if(result == 0){
            strcpy(unique_time[length_unique_time],(p_sensor+i)->time);
            length_unique_time++;
        }
    }
    free(unique_time);
    return length_unique_time;
}
/**
 * @param[in] time Pointer to current time
 * @param[in] unique_time Pointer to array of unique time list
 * @param[in] length_unique_time Stores the length of unique time
 * @return It will return 0 or 1.
 * @brief This function strontain() return 1 if time value is present in unique_time 2D array else return 0.
 */
int strcontain(char *time,char **unique_time,int length_unique_time){
    int result;
    for(int j=0;j<length_unique_time;j++){
        result=strcmp(time,unique_time[j]);
        if(result == 0){
            return 1;
        }
    }
    return 0;
}