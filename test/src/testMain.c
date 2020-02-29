#include <CUnit/Basic.h>
#include <stdlib.h>
#include <time_structure.h>
#include <sensor_structure.h>
#include <validate_sensor.h>
#include <unique_time.h>
#include <input_output_csv.h>
#include <support_degree_matrix.h>
#include <eigen.h>
#include <principal_component.h>
#include <contribution_rate_k_component.h>
#include <contribution_rate_m_component.h>
#include <eliminate_incorrect_data.h>
#include <weight_coefficient_sensor.h>
#include <integrated_support_score.h>
#include <sensor_fusion_algorithm.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

void test_run_validate(void);
void test_run_unique_time(void);
void test_run_support_degree_matrix(void);
void test_run_stuck_sensor(void){}
void test_run_sensor_fusion(void);
void test_run_input_output(void);
void test_run_eigen(void);
void test_run_principal_component(void);
void test_run_contribution_rate_k_component(void);
void test_run_contribution_rate_m_component(void);
void test_run_integrated_support_score(void);
void test_run_eliminate_incorrect_data(void);
void test_run_weight_coefficient_sensor(void);
void test_run_sensor_fusion_algorithm(void);

int init_suite(void) {
    return 0;
}
int clean_suite(void) {
    return 0;
}
/*
 * Brief : The test_run_input_output function is used to check the proper working of read_csv and write_output_file function of input_output_csv.c file.
 * see  : input_output_csv.h input_output_csv.c for passing arguments of function.
 */
void test_run_input_output(void){
    FILE *p_fptr;

    sensor_t *p_sensor;
    char line[1024];
    /*
     * The parameters of fopen function can be changed.The return value of the read_csv could be 1 or -1 according to the
     * existence of actual file.
      */
    p_fptr = fopen("data/sample.csv", "r");
    int line_counter=0;
    while (fgets(line, 1024, p_fptr)) {
        line_counter++;
    }
    /*
     * The number of sensors can be changed to perform different test cases and accordingly the data of the sensors have to be
     * provided to perform test case.
     */
    int no_sensor=1;

    p_sensor = (sensor_t *) malloc(line_counter * sizeof(sensor_t));
    double fusedOutput=54.3;
    CU_ASSERT_EQUAL(1,read_csv(p_fptr, p_sensor));
    CU_ASSERT_EQUAL(1,write_output_file(p_fptr,p_sensor,no_sensor,fusedOutput));

    p_fptr = fopen("data/samfsple.csv", "r");
    CU_ASSERT_EQUAL(-1,read_csv(p_fptr, p_sensor));
    CU_ASSERT_EQUAL(-1,write_output_file(p_fptr,p_sensor,no_sensor,fusedOutput));
    free(p_fptr);
    free(p_sensor);
}
/*
 * Brief:The test_run_validate function is used to check the working of compare_sensor_range function of validate_sensor.c file.The function
 * returns the number of new sensors which are in the range of defined maximum and minimum range.
 * See : validate_sensor.h validate_sensor.c for passing arguments of the function.
 */
void test_run_validate(void){
    sensor_t *p_sensor,*v_sensor;
    /*
     * The number of sensors can be changed to perform different test cases and accordingly the data of the sensors have to be
     * provided to perform test case.
     */
    int no_sensor=1;
    p_sensor = (sensor_t *) malloc(no_sensor* sizeof(sensor_t));
    v_sensor = (sensor_t *) malloc(no_sensor* sizeof(sensor_t));
    /*
     * Repeat this three steps for n number of sensors.In addition, the function perform validation according to the time
     * which would be provided by user and has to be same for every sensor.
     */
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53;
    /*
     * The line counter should be same as number of sensors.
     */
    int line_counter=1;
    /*
     * The time should be same as provided in the data of sensors .
     */
    time_tt time;
    time.tm_hour=1;
    time.tm_min=20;

    CU_ASSERT_EQUAL(1, compare_sensor_range(p_sensor,50,55,line_counter,time,v_sensor));
    CU_ASSERT_EQUAL(0, compare_sensor_range(p_sensor,20,30,line_counter,time,v_sensor));
    free(p_sensor);
    free(v_sensor);
}
/*
 * Brief:The test_run_unique_time is used to check the working of three different functions of unique_time.c file.
 * See : unique_time.h unique_time.c for passing arguments of the functions.
 */
void test_run_unique_time(void){

    time_tt time1,time2;
    /*
     * the value of time 1 can be changed according to the test case.
     */
    time1.tm_hour=1;
    time1.tm_min=30;
    /*
     * the value of time has to be same as time1 but in the string type.
     */
    char *time="1:30";
    /*
     * the time_parse function returns the time in time structure.
     */
    time2=time_parse(time,time1);

    CU_ASSERT(time2.tm_hour==time1.tm_hour && time2.tm_min==time1.tm_min);

    sensor_t *p_sensor;
    /*
     * the value of no_sensor can be changed to perform different test cases.
     */
    int no_sensor=1;
    p_sensor = (sensor_t *) malloc(no_sensor* sizeof(sensor_t));
    /*
     * The line counter should be same as number of sensors.
     */
    int line_counter=1;
    /*
     * the time_parse function returns the time in time structure.
     */
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53;
    /*
     * the get_uniquetime_length function is used to check the number of unique values of time from the sensor data.
     * It returns the integer value.
     */
    int length=get_uniquetime_length(p_sensor,line_counter);

    CU_ASSERT_EQUAL(1,length);
    /*
     * The length_time_list can be changed to perform various tests on the function get_time_list.
     */
    int length_time_list=1;
    time_tt *time3,*time4;
    time4=(time_tt *)malloc(sizeof(time_tt) * length_time_list);
    time4[0].tm_hour=1;
    time4[0].tm_min=20;

    /*
     * The get_time_list function return the list of time which can be zero or more.
     */
    time3=get_time_list(p_sensor,line_counter,length_time_list);
    for(int i=0;i<length_time_list;i++)
    {
        CU_ASSERT(time4[i].tm_hour== time3[i].tm_hour && time4[i].tm_min==time3[i].tm_min);
    }
    free(time3);
    free(time4);
    free(p_sensor);
}
/*
 * Brief:The test_run_support_degree_matrix is used to check the working of compute_support_degree_matrix
 * function of support_degree_matrix.c file.
 * See: support_degree_matrix.c and support_degree_matrix.h for passing arguments of function and logical steps.
 */
void test_run_support_degree_matrix(void)
{
    sensor_t *p_sensor;
    /*
     * The no_sensors can be changed according to test case.
     */
    int no_sensor=2;
    p_sensor = (sensor_t *) malloc(no_sensor* sizeof(sensor_t));
    /*
     * Repeat the following step according to number of sensors.for instance,the no_sensors for the given step is two
     * so it is repeated two times.
     */
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53.6;
    p_sensor++;
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor2");
    p_sensor->data=52.7;


    for(int i=0;i<(no_sensor-1);i++)
    {
        p_sensor --;
    }
    /*
     * The pp_D_array_a is actual 2 dimensional array while the pp_D_array_e would be the output of the function
     * compute_support_degree_matrix .
     */

    double **pp_D_array_a,**pp_D_array_e;

    pp_D_array_a=(double **)malloc(sizeof(double *) * no_sensor);

    for(int rows=0;rows<no_sensor;rows++){
        pp_D_array_a[rows]= (double *)malloc(sizeof(double) * no_sensor);
    }
    /*
     * The assignment of the values of pp_D_array_a is done according to number of sensors.Therefore, the n X n matrix has
     * to be declared.
     */
    pp_D_array_a[0][0]=1.000000;
    pp_D_array_a[0][1]=0.406570;
    pp_D_array_a[1][0]=0.406570;
    pp_D_array_a[1][1]=1.000000;

    pp_D_array_e = compute_support_degree_matrix(p_sensor,no_sensor);
    for(int rows=0;rows<2;rows++){
        for(int cols=0;cols<2;cols++){
            /*
             * Here the fabs function is used for the comparision of expected and actual value of
             * the data of double type and the difference must be less than the 0.001.
             */
            CU_ASSERT(fabs(pp_D_array_a[rows][cols]-pp_D_array_e[rows][cols])<0.001);
        }

    }
    free(p_sensor);
    free(pp_D_array_a);
    free(pp_D_array_e);

}
/*
 * Brief:The test_run_eigen is used to check the working of compute_eigen
 * function of eigen.c file.
 * See: eigen.c and eigen.h for passing arguments of function and logical steps.
 */
void test_run_eigen(void)
{

    double **pp_D_array;
    /*
    * The no_sensors can be changed according to test case.
    */
    int no_sensor=2;
    pp_D_array=(double **)malloc(sizeof(double *) * no_sensor);

    for(int rows=0;rows<no_sensor;rows++){
        pp_D_array[rows]= (double *)malloc(sizeof(double) * no_sensor);
    }
    /*
     * The assignment of the values of pp_D_array is done according to number of sensors.Therefore, the n X n matrix has
     * to be declared.
     */
    pp_D_array[0][0]=1.000000;
    pp_D_array[0][1]=0.406570;
    pp_D_array[1][0]=0.406570;
    pp_D_array[1][1]=1.000000;

    double *p_eigen_val;
    double **pp_eigen_vector;

    p_eigen_val=(double *)malloc(sizeof(double) * no_sensor);

    pp_eigen_vector=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_eigen_vector[i]=(double *) malloc(sizeof(double) * no_sensor);
    }
    /*
     * The function compute_eigen returns 1 on successful execution.
     */
    CU_ASSERT_EQUAL(1,compute_eigen(pp_D_array,no_sensor,p_eigen_val,pp_eigen_vector));
    free(pp_eigen_vector);
    free(pp_D_array);
    free(p_eigen_val);
}
/*
 * Brief:The test_run_principal_component is used to check the working of compute_principal_component
 * function of principal_component.c file.
 * See: principal_component.c and principal_component.h for passing arguments of function and logical steps.
 */
void test_run_principal_component(void)
{
    double **pp_eigen_vector,**pp_D_array;
    /*
     * The no_sensors can be changed according to test case.
     */
    int no_sensor = 2;

    pp_eigen_vector=(double **)malloc(sizeof(double *) * no_sensor);
    pp_D_array=(double **)malloc(sizeof(double *) * no_sensor);
    double **pp_principal_component_a,**pp_principal_component_e;
    pp_principal_component_a=(double **)malloc(sizeof(double *) *no_sensor);
    for(int i=0;i<no_sensor;i++) {
        pp_eigen_vector[i] = (double *) malloc(sizeof(double) * no_sensor);
        pp_D_array[i] = (double *) malloc(sizeof(double) * no_sensor);
        pp_principal_component_a[i] = (double *) malloc(sizeof(double) * no_sensor);
    }
    /*
     * All the values are declared for all three two dimension array according to the number of sensors.
     * In the given example, there are only two sensor data available so 2 X 2 matrix is used.
     */
    pp_D_array[0][0]=1.000000;
    pp_D_array[0][1]=0.406570;
    pp_D_array[1][0]=0.406570;
    pp_D_array[1][1]=1.000000;
    pp_eigen_vector[0][0]=1.000000;
    pp_eigen_vector[0][1]=2.000000;
    pp_eigen_vector[1][0]=1.000000;
    pp_eigen_vector[1][1]=2.000000;
    pp_principal_component_a[0][0]=1.813140;
    pp_principal_component_a[0][1]=2.406570;
    pp_principal_component_a[1][0]=1.813140;
    pp_principal_component_a[1][1]=2.406570;
    /*
     * The compute function returns n X n array which is pp_principal_component_e.
     */
    pp_principal_component_e=compute_principal_component(pp_eigen_vector,pp_D_array,no_sensor);

    for(int i=0;i<no_sensor;i++) {
        for(int j=0;j<no_sensor;j++) {
            /*
             * Here the fabs function is used for the comparision of expected and actual value of
             * the data of double type and the difference must be less than the 0.001.
             */
            CU_ASSERT(fabs(pp_principal_component_e[i][j]-pp_principal_component_a[i][j])<0.01);
        }
    }

}
/*
 * Brief:The test_run_contribution_rate_k_component is used to check the working of compute_contribution_K_rate
 * function of contribution_rate_k_component.c file.
 * See: contribution_rate_k_component.c and contribution_rate_k_component.h for passing arguments of function and logical steps.
 */
void test_run_contribution_rate_k_component(void)
{
    /*
     * The no_sensors can be changed according to test case.
     */
    int no_sensor = 3;

    double *p_alpha_a,*p_alpha_e,*p_eigen_val;
    p_eigen_val=(double *)malloc(sizeof(double) * no_sensor);
    p_alpha_a=(double *)malloc(sizeof(double) * no_sensor);
    /*
     * The p_eigen_val and p_alpha_a ,both are one dimensional array and
     * the length of both the arrays are equal to total number of sensors.
     */
    p_eigen_val[0]=1.0;
    p_eigen_val[1]=2.0;
    p_eigen_val[2]=3.0;
    p_alpha_a[0]=0.166667;
    p_alpha_a[1]=0.333334;
    p_alpha_a[2]=0.500000;
    p_alpha_e=compute_contribution_K_rate(p_eigen_val,no_sensor);
    for(int i=0;i<no_sensor;i++){
        /*
          * Here the fabs function is used for the comparision of expected and actual value of
          * the data of double type and the difference must be less than the 0.001.
         */
        CU_ASSERT(fabs(p_alpha_a[i]-p_alpha_e[i])<0.001);
    }
    free(p_alpha_a);
    free(p_alpha_e);
    free(p_eigen_val);

}
/*
 * Brief:The test_run_contribution_rate_m_component is used to check the working of compute_contribution_M_rate
 * function of contribution_rate_m_component.c file.
 * See: contribution_rate_M_component.c and contribution_rate_M_component.h for passing arguments of function and logical steps.
 */
void test_run_contribution_rate_m_component(void)
{
    /*
     * The no_sensors can be changed according to test case.
     */
    int no_sensor=3;

    double *p_alpha;
    p_alpha=(double *)malloc(sizeof(double) * no_sensor);
    /*
     * The p_alpha is one dimensional array and the length of the array should be changed according to the
     * number of sensors.The thresold can be changed to perform different test cases.
     */
    p_alpha[0]=0.166667;
    p_alpha[1]=0.333334;
    p_alpha[2]=0.500000;
    double thresold=0.5;
    int new_no_sensor_a = 2;
    /*
     * The function compute_contribution_M_rate returns the new number of sensors which passed through thresold.
     */
    int new_no_sensor_e = compute_contribution_M_rate(p_alpha,no_sensor,thresold);
    CU_ASSERT_EQUAL(new_no_sensor_a,new_no_sensor_e);

}
/*
 * Brief:The test_run_integrated_support_score is used to check the working of compute_integrated_score
 * function of integrated_support_data.c file.
 * See: integrated_support_data.c and integrated_support_data.h for passing arguments of function and logical steps.
 */
void test_run_integrated_support_score(void)
{
    /*
     * The no_sensors can be changed according to test case.
     */
    int no_sensor=3;
    int new_no_sensor=2;
    double *p_alpha;
    double **pp_y_value;
    p_alpha=(double *)malloc(sizeof(double) * no_sensor);
    pp_y_value=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_y_value[i]=(double *) malloc(sizeof(double) * no_sensor);
    }
    /*
     * The p_alpha is one dimensional array and the length of the array should be changed according to the
     * number of sensors.The pp_y_value is two dimensional array and the length of rows and columns is depend
     * upon number of sensors.
     * Change it according to number of sensors
     */
    p_alpha[0]=1;
    p_alpha[1]=2;
    p_alpha[2]=3;
    pp_y_value[0][0]=1;
    pp_y_value[0][1]=2;
    pp_y_value[0][2]=3;
    pp_y_value[1][0]=4;
    pp_y_value[1][1]=5;
    pp_y_value[1][2]=6;
    pp_y_value[2][0]=7;
    pp_y_value[2][1]=8;
    pp_y_value[2][2]=9;
    double *p_Z_e,*p_Z_a;
    p_Z_e=(double *)malloc(sizeof(double) * no_sensor);
    p_Z_e[0]=9.000000;
    p_Z_e[1]=12.000000;
    p_Z_e[2]=15.000000;
    /*
      *The output of the compute_integrated_score is one dimensional array.
      * and the values are given to p_Z_a to compare it with p_Z_e.
      */
    p_Z_a = compute_integrated_score(p_alpha,pp_y_value ,no_sensor,new_no_sensor);
    for(int i=0;i<no_sensor;i++){
        CU_ASSERT(fabs(p_Z_e[i]-p_Z_a[i])<0.001);
    }

}
/*
 * Brief:The test_eliminate_incorrect_data is used to check the working of eliminate_incorrect
 * function of eliminate_incorrect_data.c file.
 * See: eliminate_incorrect_data.c and eliminate_incorrect_data.h for passing arguments of function and logical steps.
 */

void test_run_eliminate_incorrect_data(void)
{
    double *p_Z;
    /*
     * The no_sensors can be changed according to test case.
     */
    int no_sensor=3;
    p_Z=(double *)malloc(sizeof(double) * no_sensor);
    double fault_value=0.7;
    /*
     *The p_z is one dimensional array and the length is changed according to number of sensors.
     */
    p_Z[0]=5.0;
    p_Z[1]=10.0;
    p_Z[2]=15.0;
    /*
     *The p_discard_index_a  and p_discard_index_e ,both are one dimensional array and the length is changed according to number of sensors.
     * The eliminate_data function computes the p_discard_index_e which is compared with actual value for testing.
     */
    int *p_discard_index_a,*p_discard_index_e;

    p_discard_index_a=(int*)malloc(sizeof(int) * no_sensor);
    p_discard_index_a[0]=1;
    p_discard_index_a[1]=0;
    p_discard_index_a[2]=0;
    p_discard_index_e=eliminate_data(p_Z,fault_value,no_sensor);
    for(int i=0;i<no_sensor;i++){
        CU_ASSERT_EQUAL(p_discard_index_a[i],p_discard_index_e[i]);
    }

}
void test_run_weight_coefficient_sensor(void)
{
    sensor_t *p_sensor;
    double *p_Z ;
    int *p_discard_index;
    /*
     * The no_sensors can be changed according to test case.
     */
    int no_sensor=3;
    p_sensor = (sensor_t *) malloc(no_sensor* sizeof(sensor_t));
    /*
    * Repeat the following step according to number of sensors.for instance,the no_sensors for the given step is two
    * so it is repeated two times.
    */
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53.6;
    p_sensor++;
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor2");
    p_sensor->data=52.7;
    p_sensor++;
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor3");
    p_sensor->data=54.7;

    for(int i =0;i<(no_sensor-1);i++){
        p_sensor--;
    }
    /*
      *The p_Z is one dimensional array and the length is changed according to number of sensors and
      *The p_discard_index is one dimensional array and length is changed according to number of sensors.
      */
    p_Z=(double *)malloc(sizeof(double) * no_sensor);
    p_Z[0]=5.0;
    p_Z[1]=10.0;
    p_Z[2]=15.0;
    p_discard_index=(int*)malloc(sizeof(int) * no_sensor);
    p_discard_index[0]=1;
    p_discard_index[1]=1;
    p_discard_index[2]=0;
    /*
     * The fused_output_a is actual fused_value while the fused_output_e is expected fused_value.
     */
    double fused_output_a=54.70000,fused_output_e;

    fused_output_e=weight_coefficient(p_sensor, p_Z ,p_discard_index,no_sensor);
    CU_ASSERT(fabs(fused_output_a-fused_output_e)<0.0001);

}
void test_run_sensor_fusion_algorithm(void)
{
    sensor_t *p_sensor;
    int no_sensor=3;
    /*
      * The no_sensors can be changed according to test case.
      */

    p_sensor = (sensor_t *) malloc(no_sensor* sizeof(sensor_t));
    /*
    * Repeat the following step according to number of sensors.for instance,the no_sensors for the given step is two
    * so it is repeated two times.
    */
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53.6;
    p_sensor++;
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor2");
    p_sensor->data=52.7;
    p_sensor++;
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor3");
    p_sensor->data=54.7;
    for(int i =0;i<(no_sensor-1);i++){
        p_sensor--;
    }
    /*
    * The fused_output_a is actual fused_value while the fused_output_e is expected fused_value.
    */
    double fused_output_e,fused_output_a=54.133241;
    fused_output_e=sensor_fusion(p_sensor,no_sensor);
    CU_ASSERT(fabs(fused_output_e-fused_output_a)<0.001);
}

int main (void)// Main function
{
    CU_pSuite pSuite = NULL;

    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add suite1 to registry
    pSuite = CU_add_suite("Main_Test_Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // add test1 to suite1
    if ((NULL == CU_add_test(pSuite, "test_input_output", test_run_input_output))
        ||(NULL == CU_add_test(pSuite, "test_unique_time", test_run_unique_time))
        ||(NULL == CU_add_test(pSuite, "test_validate_sensor", test_run_validate))
        ||(NULL == CU_add_test(pSuite, "test_Support_Degree", test_run_support_degree_matrix))
        || (NULL == CU_add_test(pSuite, "test_contribution_rate_k_component", test_run_contribution_rate_k_component))
        || (NULL == CU_add_test(pSuite, "test_contribution_rate_m_component", test_run_contribution_rate_m_component))
        || (NULL == CU_add_test(pSuite, "test_eliminate_incorrect_data", test_run_eliminate_incorrect_data))
        || (NULL == CU_add_test(pSuite, "test_eigen", test_run_eigen))
        || (NULL == CU_add_test(pSuite, "test_principal_component", test_run_principal_component))
        || (NULL == CU_add_test(pSuite, "test_integrated_support_score", test_run_integrated_support_score))
        ||(NULL == CU_add_test(pSuite, "test_weight_coefficient_sensor", test_run_weight_coefficient_sensor))
        ||(NULL == CU_add_test(pSuite, "test_sensor_fusion",test_run_sensor_fusion_algorithm))
        ||(NULL == CU_add_test(pSuite, "test_stuck_sensor",test_run_stuck_sensor)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();// OUTPUT to the screen
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    CU_cleanup_registry();//Cleaning the Registry
    return CU_get_error();
}