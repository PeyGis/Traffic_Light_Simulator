/************************************************************************/
/*                                                                      */
/* Implementation file for linked-list implementation of a LIST ADT     */
/*                                                                      */
/* The list element type is a structure comprising an integer & string  */
/* The list itself is implemented as a singly linked list of elements   */
/* The ADT list operations are implemented as a series of functions:    */
/*                                                                      */
/* Refer to lecture notes for details.                                  */
/*                                                                      */
/* David Vernon                                                         */
/*                                                                      */
/************************************************************************/

#include "linkedList.h"
 

/*** initialize the list pointer to make sure all subsequent checks on its value are valid ***/

void initialize_list(LIST_TYPE *list) {
  *list = NULL;
}


/*** position following last element in a list ***/

WINDOW_TYPE end(LIST_TYPE *list) {

   WINDOW_TYPE q;
   
   q = *list;

   if (q == NULL) {
      error("non-existent list");
   }
   else {
      while (q->next != NULL) {
         q = q->next;
      }
   }
   return(q);
}


/*** empty a list ***/

WINDOW_TYPE empty(LIST_TYPE *list) {

   WINDOW_TYPE p, q;
   
   if (*list != NULL) {

      /* list exists: delete all nodes including the header */

      q = *list;

      while (q->next != NULL) {
         p = q;
         q = q->next;
         free(p);
      }
   }
 
   /* now,  create a new empty one with a header node */
      
   if ((q = (NODE_TYPE) malloc(sizeof(NODE))) == NULL) 
      error("function empty: unable to allocate memory");
   else {
      q->next = NULL;
      *list = q;
   }
   return(end(list));
}


/*** test to see if a list is empty  ***/

int is_empty(LIST_TYPE *list) {

   WINDOW_TYPE q;
   
   q = *list;

   if (q == NULL) {
      error("non-existent list");
   }
   else {
      if (q->next == NULL) 
         return(TRUE);
      else
         return(FALSE);
   }
}


/*** position at first element in a list ***/

WINDOW_TYPE first(LIST_TYPE *list) {

   if (is_empty(list) == FALSE)
      return(*list);
   else
      return(end(list));
}


/*** position at last element in a list ***/

WINDOW_TYPE last(LIST_TYPE *list) {

   WINDOW_TYPE p, q;
   
   if (*list == NULL) {
      error("last: non-existent list");
   }
   else {

      /* list exists: find last node */

      if (is_empty(list)) {
         p = end(list);
      }
      else {
         p = *list;
         q = p->next;

         while (q->next != NULL) {
            p = q;
            q = q->next; 
         }
      }
      return(p);
   }
 }


/*** position at next element in a list ***/

WINDOW_TYPE next (WINDOW_TYPE w, LIST_TYPE *list) {

   if (w == last(list)) {
      return(end(list));
   }
   else if (w == end(list)) {
      error("can't find next after end of list");
   }
   else {
      return(w->next);
   }
}


/*** position at previous element in a list ***/

WINDOW_TYPE previous(WINDOW_TYPE w, LIST_TYPE *list) {

   WINDOW_TYPE p;

   if (w != first(list)) {

      p = first(list);
      while (p->next != w) {
         p = p->next;
         if (p == NULL) break;  /* trap this to ensure we don't dereference */
                                /* a null pointer in the while condition    */
      }

      if (p != NULL)
        return(p);
      else {
        error("can't find previous to a non-existent node ");
        return (w);
      }
   }
   else {
      error("can't find previous before first element in list");
      return(w);
   }
}


/*** insert an element in a list ***/

LIST_TYPE *insert(ELEMENT_TYPE e,  WINDOW_TYPE w, LIST_TYPE *list ) {

   WINDOW_TYPE temp;

   if (*list == NULL) {
      error("cannot insert in a non-existent list");
   }
   else {

      /* insert it after w */

      temp = w->next;
      if ((w->next = (NODE_TYPE) malloc(sizeof(NODE))) == NULL) 
         error("function insert: unable to allocate memory");
      else {
         w->next->element = e;
         w->next->next = temp;
      }
      return(list);
   }
}


/*** delete an element in a list ***/

LIST_TYPE *delete_element (WINDOW_TYPE w, LIST_TYPE *list) {

   WINDOW_TYPE p;

   if (*list == NULL) {
      printf("cannot delete from a non-existent list");
   }
   else {

      p = w->next; /* node to be deleted */

      w->next = w->next->next; /* rearrage the links */

      free(p); /* delete the node */

      return(list);
   }
}


/*** retrieve an element in a list ***/

ELEMENT_TYPE retrieve(WINDOW_TYPE w, LIST_TYPE *list) {

   if (*list == NULL) {
      printf("cannot retrieve from a non-existent list");
   }
   else {
      return(w->next->element);
   }
}


/*** print all elements in a list ***/

int print(LIST_TYPE *list) {

   WINDOW_TYPE w;
   ELEMENT_TYPE e;

   printf("Contents of list: \n");

   w = first(list);

   while (w != end(list)) {

      e = retrieve(w, list);
      
      printf("%d\n", e.waiting_time);

      w = next(w, list);
   }

   printf("--- \n");

   return(0);
}

/*** returns the size of the list ***/

int list_size(LIST_TYPE *list){

	WINDOW_TYPE w;
   int num_size=0;

   w = first(list);

   while (w != end(list)) {

      num_size+=1;
      w = next(w, list);
   }

   return num_size;

}

/*** error handler: print message passed as argument and take appropriate action ***/

void error(char *s) {
   printf("Error: %s\n",s);
   exit(0);
}

/*** assign values to an element ***/

int assign_element_values(ELEMENT_TYPE *e, int w_time) {

   e->waiting_time = w_time;
   
   return(0);
}

/*** enqueues an element into a list ***/

LIST_TYPE enqueue(int w_time, LIST_TYPE *list ) {

	ELEMENT_TYPE e;
	WINDOW_TYPE w;
	assign_element_values(&e, w_time);
	w = end(list);
	insert(e, w, list);
}


/*** dequeues an element into a list ***/

ELEMENT_TYPE dequeue(LIST_TYPE *list ) {

	ELEMENT_TYPE e;
	WINDOW_TYPE w;
	w = first(list);
	if(list_size(list) > 0) {
		e = retrieve(w, list);
		delete_element(w, list);
	} else{
		assign_element_values(&e, -1);
	}
	return (e);
}

/*This function returns the queue length statisitics*/
QUEUE_LENGTH_STATS get_queue_length_statistics(LIST_TYPE *list) {

	//declare variables
   WINDOW_TYPE w;
   ELEMENT_TYPE e;
   QUEUE_LENGTH_STATS queue_stats;

   int queue_size = list_size(list);
   int max_length = 0;
   int sum_length=0;
   int med_length = 0;


   //Generate the Average and Maximum wait time values
   w = first(list);

   while (w != end(list)) {

      e = retrieve(w, list);

	  sum_length +=e.waiting_time;

	  if(e.waiting_time > max_length){
		max_length = e.waiting_time;
	  }
      w = next(w, list);
   }

	int avg_length;
	if(queue_size == 0) avg_length = 0;
	else {avg_length = sum_length / queue_size;} //average queue length

	//store the max and avg queue length values in this struct
   queue_stats.max_length = max_length;
   queue_stats.avg_length = avg_length;

   // ############### get median queue length info #####################
   if(queue_size > 0) {

	   //create an array and transfer all the values frm the linked list into this array
	   int *arr = new int[queue_size];
	   int index=0;

	   WINDOW_TYPE w_med;
	   ELEMENT_TYPE e_med;

		w_med = first(list);

		//copy data from linked list to array
	   while (w_med != end(list)) {
		   e_med = retrieve(w_med, list);
		   arr[index]= e_med.waiting_time;
		   index++;
		  w_med = next(w_med, list);
	   }

	   //do insertion sorting here

	   //loop through all elements in the array
			for(int i=1; i < queue_size; i++){

				//declare local variables to store temp values
				int cur_obj = arr[i];

				//update the inner while loop counter
				int j = i-1;

				while(j >=0 && arr[j] > cur_obj){
					
						arr[j+1] = arr[j];
						j--;
					}
			
				//we can now insert the cur obj at its correct index
				arr[j+1] = cur_obj;
			}

			//Compute the median length

			 if((queue_size % 2) == 0){
				   int median_pos = queue_size / 2;
				   med_length =  arr[median_pos];
			   } else{
					int first_md = (int) queue_size / 2;
					int second_md = first_md+1;
					int median = (arr[first_md]+ arr[second_md]) / 2 ;
					med_length =  median;
			   }
	}

   //add median length value to the struct
   queue_stats.median_length = med_length;

   return(queue_stats);
}

/*This function returns the waiting time statisitics*/
/*It also get the previous avg wait time and dequeue all remaining element from the cars queue, while computing the new average*/
WAIT_TIME_STATS get_extended_wait_time_statistics(LIST_TYPE *list, int prev_avg_wait_time, int max_wait, int simulation_counter) {

   WINDOW_TYPE w;
   ELEMENT_TYPE e;
   WAIT_TIME_STATS wait_time_stats;

   int queue_size = list_size(list);
   int max_wait_time = max_wait;
   int sum_wait_time=0;

   w = first(list);

   while (w != end(list)) {

      e = retrieve(w, list);

	  int wait_time_diff = simulation_counter - e.waiting_time;
	  sum_wait_time +=wait_time_diff;

	  if(wait_time_diff > max_wait_time){
		max_wait_time = wait_time_diff;
	  }
      w = next(w, list);
   }//end iterating through the list


   int curr_avg_wait_time;
   if(queue_size == 0) curr_avg_wait_time = 0;
   else {curr_avg_wait_time = sum_wait_time / queue_size;}

   int total_avg_wait_time = (curr_avg_wait_time + prev_avg_wait_time) / 2;

   // add statisitcs to struct
   wait_time_stats.max_wait = max_wait_time / 1000;
   wait_time_stats.avg_wait = total_avg_wait_time / 1000;

   return(wait_time_stats);
}

/*This function returns the waiting time statisitics from a list*/
WAIT_TIME_STATS get_normal_wait_time_statistics(LIST_TYPE *list) {

	//declare and initialize variables
   WINDOW_TYPE w;
   ELEMENT_TYPE e;
   WAIT_TIME_STATS wait_time_stats;

   int queue_size = list_size(list);
   int max_wait_time = 0;
   int sum_wait_time=0;

   w = first(list);

   while (w != end(list)) {

      e = retrieve(w, list);

	  sum_wait_time +=e.waiting_time;

	  if(e.waiting_time > max_wait_time){
		max_wait_time = e.waiting_time;
	  }
      w = next(w, list);
   }//end iterating through the list


   // compute average wait time
   int avg_wait_time;
   if(queue_size == 0) avg_wait_time = 0;
   else {avg_wait_time = sum_wait_time / queue_size;}

   // store values in a struct
   wait_time_stats.max_wait = max_wait_time;
   wait_time_stats.avg_wait = avg_wait_time;

   return(wait_time_stats);
}