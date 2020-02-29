/**
 * @file main.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <stdio.h>
#include <stdlib.h>
#include <input_output_csv.h>
#include <sensor_fusion_algorithm.h>
#include <stuck_sensor.h>
#include <time_structure.h>
#include <unique_time.h>
#include <validate_sensor.h>
#include <ctype.h>

void str_error();
/**
 * @param argc Holds the total no of arguments given from command line
 * @param argv Pointer to command line argument
 * @return It will return 0 on success
 * @brief This is the main function and function for validate sensor, fusion algorithm and stuck sensor are called inside this function
 * @see input_output_csv.h
 * @see sensor_fusion_algorithm.h
 * @see stuck_sensor.h
 * @see validate_sensor.h
 * @see time_structure.h
 * @see sensor_structure.h
 * @see unique_time.h
 */
/*
 * argc holds the no of arguments passed.By default, the argument length == 1 which contains the name of the program
 * Thus argv[0] holds the program name.
 * Order of Arguments to be passed are "name of .csv file, sensor min range,sensor max range,
 * time interval,parameter p of algorithm, parameter q of algorithm".
 * Argument time interval, parameter p and parameter q are optional.If not provided ,then it will take the default value.
 */
int main(int argc,char *argv[]) {

    /*
     * Stores the name and path of file
     */
    char *name_file;
    /*s
     * Stores the minimum and maximum range of sensor
     */
    int sensor_min_range;
    int sensor_max_range;
    /*
     * Default value of time interval 0:10,If not specified by user
     */
    time_tt interval;
    interval.tm_hour=0;
    interval.tm_min=10;
    /*
     * Default value of fault tolerance and parameter p of algorithm ,If not specified by user
     */
    double q_fault=0.7;
    double p=0.85;

    /*
     * Pointer to input file
     */
    FILE *p_fptr;

    /*
     * Pointer to Output File
     */
    FILE *p_fptr_write;
    char line[1024];
    int loop_counter=0;

    /*
     * Stores the value 0 or 1 ,If 1 then input file is read successfully else result is 0
     */
    int result;

    /*
     * Pointer to structure sensor_t which stores sensor name, time and data
     */
    sensor_t *p_sensor;

    if(argc >=1 && argc < 4){
        str_error();
        return -1;
    } else{
        /*
        Assuming the argv[1] is the path and name of file
        */
        name_file=argv[1];

        /*
        Assuming the argv[2] is min range and argv[3] is max range
        */
        sensor_min_range=atoi(argv[2]);
        sensor_max_range=atoi(argv[3]);

        /*
        argv[4] , argv[5] and argv[6] is optional ,so If user doesn't specify then it will take the default value.
        */
        if(argc == 5) {
            interval = time_parse(argv[4], interval);
        }
        else if (argc == 6) {
            interval = time_parse(argv[4], interval);
            q_fault = atof(argv[5]);
        }
        else if (argc == 7) {
            interval = time_parse(argv[4], interval);
            q_fault = atof(argv[5]);
            p = atof(argv[6]);
        }
    }

    /*
    * Initialize input File Pointer
    */
    p_fptr = fopen(name_file, "r");

    /*
     * Initialize Pointer to output file
     */
    p_fptr_write=fopen("../data/output.txt","w");

    if (p_fptr == NULL) {
        printf("FILE POINTER IS NOT INITIALIZE");
        return -1;
    }

    /*
    * This loop is used to read the number of lines of file.So it can be further used to initialize the dynamic
     * array of sensor_t *p_sensor
    */
    while (fgets(line, 1024, p_fptr)) {
        loop_counter++;
    }
    const int line_counter=loop_counter;

    /*
     * Set the cursor at the beginning of file
     */
    fseek(p_fptr, 0, 0);

    /*
     *Initialize the dynamic array of sensor_t and it's length is equal to no of line read from file i.e. line_counters
     */
    p_sensor = (sensor_t *) malloc(line_counter * sizeof(sensor_t));

    result = read_csv(p_fptr, p_sensor);
    /*
     * If function returns 1 then the file is parse successfully.
     */
    if(result != 1){
        printf("Error in parsing the file");
        return -1;
    }
    /*
     * Get the length of unique time
     */
    int length_unique_time=get_uniquetime_length(p_sensor,line_counter);

    /*
     Call get_time_list
     */
    time_tt *p_time_list =  get_time_list(p_sensor,line_counter,length_unique_time);

    /*
     * Call the validate sensor and fusion algorithm for each time period
     */
    sensor_t *p_v_sensor;
    for(int i=0;i<length_unique_time;i++){

        p_v_sensor=(sensor_t *)malloc(sizeof(sensor_t) * (line_counter/length_unique_time));
        int sensor_len=compare_sensor_range(p_sensor,sensor_min_range,sensor_max_range,line_counter,p_time_list[i],p_v_sensor);

        /*
         * All the sensors are out of range
         */
        if(sensor_len == 0){
            fprintf(p_fptr_write,"===================AT TIME %d:%d====================\n",p_time_list[i].tm_hour,p_time_list[i].tm_min);
            fputs("ALL THE SENSORS ARE OUT OF RANGE\nNO FUSED OUTPUT\n\n",p_fptr_write);
        } else if(sensor_len == 1){
            write_output_file(p_fptr_write,p_v_sensor,sensor_len,(p_v_sensor+0)->data);
        } else{
            write_output_file(p_fptr_write,p_v_sensor,sensor_len,sensor_fusion(p_v_sensor,sensor_len));
        }
        free(p_v_sensor);
    }

    /*
     * Call the stuck sensor algorithm
     */
    compute_stuck_sensor(p_sensor,p_time_list,interval,length_unique_time,line_counter);

    /*
     * Free the Memory
     */
    free(p_fptr);
    free(p_sensor);
    free(p_time_list);
    printf("\nSEE THE data/stuck_sensor.txt file\n");
    printf("SEE THE data/output.txt file\n");

    return 0;
}
/**
 * @brief Prints the error message ; if no of arguments are less than 4.
 */
void str_error(){
    printf("Insufficient no of arguments\n");
    printf("Provide the arguments in this format");
    printf("Order of Arguments to be passed are :name of .csv file,no of sensor in each grp, sensor min range,sensor max range,\n"
           "time interval,parameter p of algorithm, parameter q of algorithm");
}