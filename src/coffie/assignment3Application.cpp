/* 

   assignment3Application.cpp -  Simulation of Queueing Behaviour at Traffic Lights
   ============================================================================================

   Author
   ===========================================================================================

   Isaac Coffie, MSIT Carnegie Mellon University Africa
   March 03rd 2020


   The functionality of the program is defined as follows.
   ============================================================================================

   The purpose of this assignment is simulate the behaviour of cars at a traffic light station. 
   
   This data for this simulation is stored in an input file (input.txt) with a number of test cases in the range  0 > N < 1000. 
   For each test case, we simulate the queueing behaviour of cars for the predetermined runtime.
   The resulting solution, which is essentially summary statisitcs is saved unto a text file (output.txt)
   
   Also, both the output and input files are located in the ./data/ directory of my project
  

  Format of the input and output file are defined below
  =============================================================================================

   Input file
   ----------
   The input file has several lines of ant location data
   The first line denotes the number of test cases available
   The remaining lines of records contain the parameters for the queueing simulation


   Output file
   ------
   The output file is formatted in the following way:

   first line is my Andrew ID
   The remaining line containts the summary statistics of the queueing behaviour, with each test case delimeted by an empty or blank line

	coffie
	Arrival rate:	X cars per min
	Departure rate:	X s per car
	Runtime:	X min
	Time increment:	X ms
	Light sequence:	Green X s; Amber X s; Red X s
	Average length:	X cars
	Median length:	X cars
	Maximum length:	X cars
	Average wait:	X s
	Maximum wait:	X s


   Solution Strategy / Summary of the Algorithm
   =================================================================================
   The focus of this assignment is to get the summary statistics on the queues at the traffic light. To do this, I abstracted my logic in the implementation file
   I declared all the variables required. However, the variable to pay particular attention to, is the key_values_array variable. 
   This array maps the index of the keyword list to its corresponding value.
   I implemented a method to enqueue and dequeue from a list
   Since we have no information about the size of the queue, I used a LinkedList implementation approach of the LIST ADT
   I also implemented few helper methods get_queue_length_statistics() and get_extended_wait_time_statistics() to return the summary statistics 

   summary of the algorithm is as follows:

   set row index = 1

   WHILE the input data has some content:
		
		read the content of the row (key-value) pair and ADD it to the ARRAY
		convert the key string into lower case
		Build the key_values_array by comparing the key just read in and add the value to the index of the key in the array
		increment value for row index

		IF row_index == 7 
			Reinitialize row index = 1
			CALL the process_simulation and pass key_value_list, fp_out as arguement

  END WHILE
   

   ########## Definition of process_simulation function ####################

   initialize relevant variables and do the necessary conversions from s or min into ms

   WHILE simulation counter < runtime:
	
	Call PoissonSample() to return the number of cars that have arrived within the lamda rate

	Call Enqueu() to queue all the cars into the list

	SWITCH(current color):
		
		CASE GREEN:
			
			Attempt dequeing a car 

			GET time spent in car
			ADD this time to a waiting time list

			update 



		CASE YELLOW:
			
			update current color

		CASE RED:

			update current color

	
	GET current SIZE of queue
	ADD this SIZE to queue length list


	update counte variables
   END WHILE

   CALL helper functions to write the summary statistics unto the file



   Test Strategy
   =================================================================================

   This program has been tested with variety of test data sets that reflect all valid conditions, including boundary conditions:

	#TEST 1: input file with zero test cases
			
			INPUT:

			
			EXPECTED OUTPUT:
			no content in the output file other than my AndrewID

	#TEST 2: input file with 1 test case
			
			INPUT:
				1
				Arrival 10
				Departure 5
				Runtime 5
				Increment 10
				Green 10
				Amber 1
				Red 30

			EXPECTED OUTPUT:
				
					coffie
					Arrival rate:	10 cars per min
					Departure rate:	5 s per car
					Runtime:	5 min
					Time increment:	10 ms
					Light sequence:	Green 10 s; Amber 1 s; Red 30 s
					Average length:	12 cars
					Median length:	7 cars
					Maximum length:	32 cars
					Average wait:	83 s
					Maximum wait:	152 s

	#TEST 3: input file with more than 1 test case
			
			INPUT:
				2
				Arrival 10
				Departure 5
				Runtime 5
				Increment 10
				Green 10
				Amber 1
				Red 30
				Runtime 5
				Arrival 20
				Departure 2
				Increment 100
				Red 15
				Green 5
				Amber 1

			EXPECTED OUTPUT:
				
					coffie
					Arrival rate:	10 cars per min
					Departure rate:	5 s per car
					Runtime:	5 min
					Time increment:	10 ms
					Light sequence:	Green 10 s; Amber 1 s; Red 30 s
					Average length:	12 cars
					Median length:	7 cars
					Maximum length:	32 cars
					Average wait:	83 s
					Maximum wait:	152 s

					Arrival rate:	20 cars per min
					Departure rate:	2 s per car
					Runtime:	5 min
					Time increment:	100 ms
					Light sequence:	Green 5 s; Amber 1 s; Red 15 s
					Average length:	32 cars
					Median length:	30 cars
					Maximum length:	74 cars
					Average wait:	99 s
					Maximum wait:	203 s


	#TEST 4: - input file with boundary cases, zero values for simulation parameters

		INPUT:
			1
			Runtime 0
			Arrival 0
			Departure 0
			Increment 0
			Red 0
			Green 0
			Amber 0


		EXPECTED OUTPUT:

			coffie
			Arrival rate:	0 cars per min
			Departure rate:	0 s per car
			Runtime:	0 min
			Time increment:	0 ms
			Light sequence:	Green 5 s; Amber 1 s; Red 0 s
			Average length:	0 cars
			Median length:	0 cars
			Maximum length:	0 cars
			Average wait:	0 s
			Maximum wait:	0 s

	#TEST 5: increasing the departure time so we see how the length of the queue grows
		
		INPUT:
			1
			Arrival 1
			Departure 5000
			Runtime 5
			Increment 10
			Green 10
			Amber 1
			Red 30

		EXPECTED OUTPUT: 
		coffie
		Arrival rate:	1 cars per min
		Departure rate:	5000 s per car
		Runtime:	5 min
		Time increment:	10 ms
		Light sequence:	Green 10 s; Amber 1 s; Red 30 s
		Average length:	2 cars
		Median length:	3 cars
		Maximum length:	6 cars
		Average wait:	55 s
		Maximum wait:	267 s


	#TEST 6: Zero runtime value
		
		INPUT:
			1
			Arrival 1
			Departure 5000
			Runtime 0
			Increment 10
			Green 10
			Amber 1
			Red 30

		EXPECTED OUTPUT: 
		coffie
		Arrival rate:	1 cars per min
		Departure rate:	5 s per car
		Runtime:	0 min
		Time increment:	10 ms
		Light sequence:	Green 10 s; Amber 1 s; Red 30 s
		Average length:	0 cars
		Median length:	0 cars
		Maximum length:	0 cars
		Average wait:	0 s
		Maximum wait:	0 s



    Time Complexity = g(n) = O(N^2)
   =================================================================================
   The order of complexity of this program is a quadractic function of order N = 2
   This is because the outer loop iterates through the number of elements in the input file, which is equal to O(N)
   we first do some comparison in a FOR LOOP which has a runtime of O(N)
   Within the loop, we also call the process_simulation() function which has a worst case scenario of O(N^2). Here's why

   We loop through the counter from  0 to runtime which is O(N)
   Withint this loop, we Enqueue all cars returned by the Poison Sample function, rutime is O(N)
   We perform some constant operations in this loop such as if statements, incrementing counter, adding record to array) which is K
   We also call the INSERTION SORT function to sort the list, which has a runtime of O(N^2)

   So, Overall, our time complexity ~ K(N) + K(N^2) + K
   Therefore the overall worst case time complexity is O(N^2)


   File organization -    This segement of comment is adopted from Prof David Vernon
   -----------------

   assignment3.h                  interface file:      
                              contains the declarations required to use the functions that implement the solution to this problem
                              typically, these will include the definitions of the abstract data types used in the implementation
	
  linkedList.h				LinkedList implementation file header

   assignment3Implementation.cpp  implementation file: 
                              contains the definitions of the functions that implement the algorithms used in the implementation

    linkedListImplementation.cpp  implementation file: 
                              contains the definitions of the functions that implements the Linked List
 
   assignment3Application.cpp     application file:    
                              contains the code that instantiates the abstract data types and calls the associated functions
                              in order to effect the required functionality for this application


   Audit Trail
   -----------

   - Added prompt_and_exit() to allow users to read the terminal messages before it is closed.  David Vernon, 06/01/2019.

*/
 
#include "assignment3.h"
#include "linkedList.h"
 
int main() {

	//Declare and initialize variables
   int debug = TRUE;
   int number_of_test_cases;
   typedef char keyword[MAX_BUFFER_SIZE];
   keyword key;
   int value;
   int num_elements = 0;
   int row_counter = 1;
   FILE *fp_in, *fp_out;

   int key_values_array[NUMBER_OF_KEYS];
   struct key_value_array key_value_list[NUMBER_OF_KEYS];

   //define list of all possible keys
   keyword keylist[NUMBER_OF_KEYS] = {
	"arrival",
	"departure",
	"runtime",
	"increment",
	"red",
	"amber",
	"green"
	};

	/*Poisson Distribution Variables*/
	double arrival_rate = 0; // the arrival rate in cars per millisecond
	int count = 0; // the number of cars that arrive in any given
	double lambda = 0; // the mean number of cars that arrive in any one


	//####################################################################
	//declare list variables here
	WINDOW_TYPE w;
	ELEMENT_TYPE e;
	LIST_TYPE list;
	LIST_TYPE wait_time_list;
	LIST_TYPE queue_length_list;


   //attempt reading in the input data
   if ((fp_in = fopen("../data/input.txt","r")) == 0) {
	  printf("Error can't open input input.txt\n");
     prompt_and_exit(1);
   }
   // attempt reading in the output data
   if ((fp_out = fopen("../data/output.txt","w")) == 0) {
	  printf("Error can't open output output.txt\n");
     prompt_and_exit(1);
   }

   //Read number of test cases
	fscanf(fp_in, "%d", &number_of_test_cases);
	printf("Number of Test Cases %d\n", number_of_test_cases);
	printf("Program is still executing please hold on for few moments\n");

	fprintf(fp_out, "coffie\n");


	/*Read Traffic Light Simulation Data Until End of File*/
	
		while(fscanf(fp_in, "%s %d", &key, &value) != EOF){

			
			//################ KEEPING BUILDING KEY-VALUE PAIR ARRAY ##################

			/* convert the key to lower case to be safe */
			for (int j=0; j < (int) strlen(key); j++)
				key[j] = tolower(key[j]);

			/*Store the value read into the correct position in the value*/
			for(int j=0; j < NUMBER_OF_KEYS; j++){
				if(strcmp(key, keylist[j]) == 0){

					//can convert value to milliseconds for standardization
					key_values_array[j] = value;
					struct key_value_array key_pair;
					key_pair.data = value;
					add_record_to_array(key_value_list, key_pair, j);
					break;
				}
			}

			if(row_counter == 7){
				row_counter = 1;
				process_simulation(key_value_list, fp_out);
			}
		row_counter+=1; //keep track of number of lines or records read from the file
	}


    fclose(fp_in);
    fclose(fp_out);

   //prompt_and_exit(0);
}
