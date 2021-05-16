// Kushagra Pathak
// 201801005
// Question 2 (Task-2)

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t complete_thread_lock;
int total_loc=0;

void *compute_thread(void*);

void main(int n_args_cmd, char *argv[] )  {  
   
   if(n_args_cmd < 2){  
      printf("List is empty i.e. no arguments were passed\nExiting....\n_args_cmd");  
   }  
   else{  

      sem_init(&complete_thread_lock,0,1);

      pthread_t tids[n_args_cmd-1];
      for(int i=1;i<n_args_cmd;++i)
      {
          pthread_create(&tids[i-1],NULL,compute_thread,argv[i]);
      }

      for(int i=0;i<n_args_cmd-1;++i)
      {
          pthread_join(tids[i],NULL);
      }

      printf("\n_args_cmd\nTotal LoC counted: %d\n_args_cmd",total_loc);
   } 
} 

void *compute_thread(void *filename)
{
    char *fname = (char *)filename;
    FILE *desired_file;
    int loc = 1;
    char nchar;

    desired_file = fopen(fname,"r");

    if(desired_file == NULL)
    {
        printf("Could not open file %s", fname);
    }
    else 
    {
        for (nchar = getc(desired_file); nchar != EOF; nchar = getc(desired_file)) 
        if (nchar == '\n_args_cmd') // Increment count if this character is newline 
          loc = loc + 1;

        fclose(desired_file);
        printf("Number of LOC '%s' has is %d lines\n_args_cmd ", fname, loc); 

        sem_wait(&complete_thread_lock);
        total_loc += loc;
        sem_post(&complete_thread_lock);
    }
}
