/* 

   assignment3Implementation.cpp - Simulation of Queueing Behaviour at Traffic Lights
   ============================================================================

   This program is for Assignment No. 2, Course 04-630 Data Structures and Algorithms for Engineers. 

   Please refer to the application file - assignment2Application.cpp - for details of the functionality of this program

      
   File organization
   -----------------

   assignment3.h                  interface file:      
                              contains the declarations required to use the functions that implement the solution to this problem
                              typically, these will include the definitions of the abstract data types used in the implementation

   assignment3Implementation.cpp  implementation file: 
                              contains the definitions of the functions that implement the algorithms used in the implementation
 
   assignment3Application.cpp     application file:    
                              contains the code that instantiates the abstract data types and calls the associated functions
                              in order to effect the required functionality for this application
                                                    
   Author
   ------

   Isaac Coffie, Carnegie Mellon University Africa
  March 3, 2020

*/

 
//include the header file 
#include "linkedList.h"
#include "assignment3.h"

void prompt_and_exit(int status) {
   printf("Press any key to continue and close terminal\n");
   getchar();
   exit(status);
}

//this function simply prints a message to file with no complex formatting
void print_message_to_file(FILE *fp, char message[]) {
 
   fprintf(fp,"The message is: %s\n", message);
}


/* A function to add an element of type location to the array
@param loc_array pointer to the location array
@param loc_new a location struct object
@param num_elements a pointer to the number of elements in the array
@returns nothing since it's void
*/
void add_record_to_array(struct key_value_array *keypair_array, struct key_value_array new_val, int index){

	//dereference the num_elements pointer and insert the new location record into the array index
	keypair_array[index] = new_val;
	//*num_elements +=1; //we then increment the number of elements in the array for successive insertion
}

/* A function to print the content of an array
@param loc_array pointer to the location array
@param size the size or number of elements in the array
@param fp a pointer to the file output stream
@returns nothing since it's void
*/
void print_sorted_records(FILE *fp, struct location *loc_array, int size){

	for(int i=0; i < size; i++){

		//finally print this new unique location to the output file
		float t = loc_array[i].time;
		int x = loc_array[i].x_pos;
		int y = loc_array[i].y_pos;
		fprintf(fp, "%6.3f %4d %4d \n", t, x, y);
	}
}

//The Algorithm for Sampling a Poisson Distribution from Prof David Vernon

int samplePoisson(double lambda) {
	/* Generate a random sample from a Poisson distribution with a given mean, lambda */
	/* Use the function rand to generate a random number */
	static bool first_call = true;
	int count;
	double product;
	double zero_probability;
	/* Seed the random-number generator with current time so */
	/* that the numbers will be different every time we run */
	if (first_call) {
	srand( (unsigned)time( NULL ));
	first_call = false;
	}
	count = 0;
	product = (double) rand() / (double) RAND_MAX;
	zero_probability = exp(-lambda);
	while (product > zero_probability) {
	count++;
	product = product * ((double) rand() / (double) RAND_MAX);
	}
	return(count);
}

void process_simulation(struct key_value_array *my_arr, FILE *fp_out){

	//declare list variables here
	WINDOW_TYPE w;
	ELEMENT_TYPE e;
	LIST_TYPE list;
	LIST_TYPE wait_time_list;
	LIST_TYPE queue_length_list;


	/*Poisson Distribution Variables*/
	double arrival_rate = 0; // the arrival rate in cars per millisecond
	int count = 0; // the number of cars that arrive in any given
	double lambda = 0; // the mean number of cars that arrive in any one


	arrival_rate = ((float) my_arr[0].data) / (60 * 1000);

	/* the Poisson distribution mean, lambda, is the arrival rate of cars during the simulation interval */
	lambda = arrival_rate * my_arr[3].data;


	//################################## BEGIN SIMULATION ####################################################

	int simulation_counter = 0;
	long int runtime_period = my_arr[2].data * 60000;
	long int increment = my_arr[3].data; // the period of each simulation interval in milliseconds

	//initialize list
	initialize_list(&list);
	initialize_list(&wait_time_list);
	initialize_list(&queue_length_list);

	empty(&list);
	empty(&wait_time_list);
	empty(&queue_length_list);

	int total_cars_per_runtime = 0;
	int departure_timer_elapsed = 0;
	long int departure_period = my_arr[1].data * 1000;
	int enter_departure_loop_counter = 1;

	long int green_light_duration = my_arr[6].data * 1000;
	long int amber_light_duration = my_arr[5].data * 1000;
	long int red_light_duration = my_arr[4].data * 1000;
	int lights_timer=0;
	int current_color = 3; // 1=Green, 2=Amber, 3=Red

	int average_waiting_time = 0;
	int max_waiting_time = 0;
	int max_queue_length = 0;
	int average_queue_length = 0;
	int interval_counter=1;


	int time_spent_in_queue = 0;
	int queue_size = 0;

	/*Start the Traffic Simulation*/

	while(simulation_counter < runtime_period){

		/* Compute the number of cars that have arrived in the current simulation interval */
		count = samplePoisson(lambda);

		//for each count, enqueue all cars in the queue for this interval
		for(int i=0; i < count; i++)
			enqueue(simulation_counter, &list);

		//printf("Poissoin distribution %d at time %d\n", count, simulation_counter);

		/*Simulate traffic light behaviour*/

		switch(current_color){

			//LIGHT IS GREEN
		case 1:

			/*find out if a car can leave, if so let's dequeue*/
			if(departure_timer_elapsed >= departure_period){

				//we can now dequeue a car
				ELEMENT_TYPE time_enqueued = dequeue(&list);

				//aggressive checking for null pointer
				if(time_enqueued.waiting_time >=0){
					departure_timer_elapsed = 0; //reset departure timer
					
					/*Get the number of milliseconds that this car waited since the last car departure*/
					time_spent_in_queue = simulation_counter - time_enqueued.waiting_time;
					//printf("Time spent in queue %d started at %d\n", time_spent_in_queue, time_enqueued.waiting_time);
					enqueue(time_spent_in_queue, &wait_time_list);

					average_waiting_time = (average_waiting_time + time_spent_in_queue) / enter_departure_loop_counter;
					enter_departure_loop_counter+=1; //increment loop counter
				} 
		
			} //end check for departure

			//Change colour to amber when green light duration has elapsed. Also reset light timer
			if(lights_timer > green_light_duration){
				current_color = 2;
				lights_timer = 0; 
			}
			//do
			break;

			//LIGHT IS AMBER
		case 2:
			//Change colour to red when amber light duration has elapsed. Also reset light timer
			if(lights_timer > amber_light_duration){
				current_color = 3;
				lights_timer = 0; 
			}
			//do
			break;

			//LIGHT IS RED
		case 3:
			//do
			//Change colour to green when red light duration has elapsed. Also reset light timer
			if(lights_timer > red_light_duration){
				current_color = 1;
				lights_timer = 0; 
				departure_timer_elapsed = 0;
			}
			break;

			//FALLBACK LIGHT
		default:
			//do nothing
			break;
		}


		/*get queue information*/
		queue_size = list_size(&list);  //get size of queue
		enqueue(queue_size, &queue_length_list); //keep this size in a list

		//increment the simulation start variable
		simulation_counter += increment;
		departure_timer_elapsed += increment; //update departure timer
		total_cars_per_runtime += count;
		interval_counter+=1;
		lights_timer += increment;
	}

	/*Write all summary statistics to file*/

	/*Get Queue statistics*/
	QUEUE_LENGTH_STATS queue_info = get_queue_length_statistics(&queue_length_list);

	/*Get waiting time statistics*/
	WAIT_TIME_STATS wait_time_stats_standard = get_normal_wait_time_statistics(&wait_time_list);

	//add remaining cars in queue details to the runing total
	WAIT_TIME_STATS wait_time_stats = get_extended_wait_time_statistics(&list, wait_time_stats_standard.avg_wait, wait_time_stats_standard.max_wait, simulation_counter);

	fprintf(fp_out, "Arrival rate:	%d cars per min\n", my_arr[0].data);
	fprintf(fp_out, "Departure rate:	%d s per car\n", my_arr[1].data);
	fprintf(fp_out, "Runtime:	%d min\n", my_arr[2].data);
	fprintf(fp_out, "Time increment:	%d ms\n", my_arr[3].data);
	fprintf(fp_out, "Light sequence:	Green %d s; Amber %d s; Red %d s\n", my_arr[6].data, my_arr[5].data, my_arr[4].data);
	fprintf(fp_out, "Average length:	%d cars\n", queue_info.avg_length);
	fprintf(fp_out, "Median length:	%d cars\n", queue_info.median_length);
	fprintf(fp_out, "Maximum length:	%d cars\n", queue_info.max_length);
	fprintf(fp_out, "Average wait:	%d s\n", wait_time_stats.avg_wait);
	fprintf(fp_out, "Maximum wait:	%d s\n", wait_time_stats.max_wait);
	fprintf(fp_out, "\n");
}
