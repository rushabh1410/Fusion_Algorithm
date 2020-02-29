# About
The user performs the measurement with a set of sensors, but there will be error associated with the measurment.
So, the user is interested in generating more accuarate outcome.Thus, we have implemented a fusion algorithm using the principal component analysis.
This fusion algorithm takes the input from .csv file and generate the fused output.Before, performing fusion algorithm it checks the validity of sensors.
The user provides the minimum and maximum range of sensor to validate the sensors. Only the validated sensor data is passed to fusion algorithm.
It also finds the sensor which are stuck. The sensors are said to be stuck if its value doesn't change after given time interval.

Below is the paper which describes the steps and results of fusion algorithm.<br>
G. Hongyan, “A simple multi-sensor data fusion algorithm based on principal component analysis,” in 2009 ISECS International Colloquium on Computing, Communication, Control, and Management, Sanya, China, 2009, pp. 423–426.

# Author
> - Shah Jinaliben <jinalibenhiteshbhais@cmail.carleton.ca> -Univeristy of Ottawa
> - Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca> -Univeristy of Ottawa
> - Patel Jay <jpate122@uottawa.ca> -Univeristy of Ottawa

# Project Folder Structure
Our Project will follow the conventional C file structure.<br>
SensorFusion<br>
│&nbsp;&nbsp;&nbsp;&nbsp;  README.md<br>
│&nbsp;&nbsp;&nbsp;&nbsp;   INSTALL.md<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   .gitignore<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   makefile<br>
|<br>
└─src<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   contribution_rate_k_component.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   contribution_rate_m_component.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   eigen.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   eliminate_incorrect_data.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   input_output_csv.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   integrated_support_score.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;	main.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	principal_component.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	sensor_fusion_algorithm.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	stuck_sensor.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	support_degree_matrix.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	unique_time.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	validate_sensor.c<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	weight_coefficient_sensor.c<br>
|<br>
└─include<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   contribution_rate_k_component.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   contribution_rate_m_component.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   eigen.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   eliminate_incorrect_data.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   input_output_csv.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   integrated_support_score.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	principal_component.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	sensor_fusion_algorithm.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	sesnor_structure.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	stuck_sensor.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	support_degree_matrix.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	time_structure.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	unique_time.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	validate_sensor.h<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	weight_coefficient_sensor.h<br>
|<br>
└─data<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   sample.csv<br>
|<br>
└─test<br>
|	└─src<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	testMain.c<br>
|<br>
└─doc<br>
│&nbsp;&nbsp;&nbsp;&nbsp;   └─html<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;	index.html<br>
|&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;   |&nbsp;&nbsp;&nbsp;&nbsp;	user_guide.md<br>
|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;	...<br>


# Install
To install the dependencies and run this software , refer to INSTALL.md file

# Documentations
To see the user level documentation ,refer to doc/user_guide.md folder

# Aknowledgement
> -Dr. Cristina Ruiz Martin for providing advice on how to develop the software.

# Support
If you face any problem while installing the libraries, compiling and running the program.
Please feel free to contact on the email address specified in author section.