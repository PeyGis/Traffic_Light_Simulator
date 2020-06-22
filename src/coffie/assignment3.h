/* 

   assignment3.h - interface file for Simulation of Queueing Behaviour at Traffic Lights
   ======================================================

   This program is for Assignment No. 3, Course 04-630 Data Structures and Algorithms for Engineers. 

   Please refer to the application file - assignment3Application.cpp - for details of the functionality of this program

      
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

 
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>
#include <time.h>
#include <math.h>


#define TRUE 1
#define FALSE 0
#define MAX_MESSAGE_LENGTH 81
#define MAX_BUFFER_SIZE 1024
#define UPPER_BOUND_TEST_RECORDS 27000
#define NUMBER_OF_KEYS 7


/* function prototypes go here */

/*A structure to store location details*/
struct location {float time; int x_pos; int y_pos;};

struct key_value_array {int data; };

void prompt_and_exit(int status);
void print_message_to_file(FILE *fp, char message[]);

/*A function to hide the implementation of adding a record to the list*/
void add_record_to_array(struct key_value_array *keypair_array, struct key_value_array new_val, int index);

/*This function prints the contents of elements in the array*/
void print_sorted_records(FILE *fp, struct location *loc_array, int size);

/*Poisson Distribution Sampling*/
int samplePoisson(double lambda);

/*The core functionality of this program, It simulates the queueing behavior at the traffic light*/
void process_simulation(struct key_value_array *my_arr, FILE *fp_out);

