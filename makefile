$(shell mkdir -p bin)
$(shell mkdir -p build)
CC =gcc
CFLAGS =-g -Wall
INCLUDES=-I"include" -I/usr/local/include
LFLAGS=-L/usr/local/lib
LIBS=-lgsl -lgslcblas -lm -lcunit
TARGET=FusedOutput

default :$(TARGET) TestFusedOutput

$(TARGET): main.o eigen.o contribution_rate_k_component.o contribution_rate_m_component.o eliminate_incorrect_data.o input_output_csv.o integrated_support_score.o unique_time.o principal_component.o sensor_fusion_algorithm.o support_degree_matrix.o weight_coefficient_sensor.o validate_sensor.o stuck_sensor.o
	$(CC) $(CFLAGS) $(LFLAGS) -o bin/$(TARGET) build/main.o build/eigen.o build/contribution_rate_k_component.o build/unique_time.o build/contribution_rate_m_component.o build/eliminate_incorrect_data.o build/input_output_csv.o build/integrated_support_score.o build/principal_component.o build/sensor_fusion_algorithm.o build/support_degree_matrix.o build/weight_coefficient_sensor.o build/validate_sensor.o build/stuck_sensor.o $(LIBS)

TestFusedOutput : testMain.o eigen.o contribution_rate_k_component.o contribution_rate_m_component.o eliminate_incorrect_data.o input_output_csv.o integrated_support_score.o unique_time.o principal_component.o sensor_fusion_algorithm.o support_degree_matrix.o weight_coefficient_sensor.o validate_sensor.o stuck_sensor.o
	$(CC) $(CFLAGS) $(LFLAGS) -o bin/TestFusedOutput build/testMain.o build/eigen.o build/contribution_rate_k_component.o build/unique_time.o build/contribution_rate_m_component.o build/eliminate_incorrect_data.o build/input_output_csv.o build/integrated_support_score.o build/principal_component.o build/sensor_fusion_algorithm.o build/support_degree_matrix.o build/weight_coefficient_sensor.o build/validate_sensor.o build/stuck_sensor.o $(LIBS)

testMain.o : test/src/testMain.c
	$(CC) -c $(CFLAGS) $(INCLUDES) test/src/testMain.c -o build/testMain.o

main.o :src/main.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/main.c -o build/main.o

eigen.o : src/eigen.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/eigen.c -o build/eigen.o

contribution_rate_k_component.o : src/contribution_rate_k_component.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/contribution_rate_k_component.c -o build/contribution_rate_k_component.o

contribution_rate_m_component.o : src/contribution_rate_m_component.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/contribution_rate_m_component.c -o build/contribution_rate_m_component.o

eliminate_incorrect_data.o : src/eliminate_incorrect_data.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/eliminate_incorrect_data.c -o build/eliminate_incorrect_data.o

input_output_csv.o : src/input_output_csv.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/input_output_csv.c -o build/input_output_csv.o

unique_time.o : src/unique_time.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/unique_time.c -o build/unique_time.o

integrated_support_score.o : src/integrated_support_score.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/integrated_support_score.c -o build/integrated_support_score.o

principal_component.o : src/principal_component.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/principal_component.c -o build/principal_component.o

sensor_fusion_algorithm.o : src/sensor_fusion_algorithm.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/sensor_fusion_algorithm.c -o build/sensor_fusion_algorithm.o

support_degree_matrix.o : src/support_degree_matrix.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/support_degree_matrix.c -o build/support_degree_matrix.o

weight_coefficient_sensor.o : src/weight_coefficient_sensor.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/weight_coefficient_sensor.c -o build/weight_coefficient_sensor.o

validate_sensor.o : src/validate_sensor.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/validate_sensor.c -o build/validate_sensor.o

stuck_sensor.o : src/stuck_sensor.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/stuck_sensor.c -o build/stuck_sensor.o

#CLEAN COMMANDS
clean:
	rm -f bin/* build/*