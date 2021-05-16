// minishell.c
// Kushagra Pathak
// ID : 201801005
// OS lab 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  while( 1 )
  {
/* ==== DO NOT MODIFY ANY OF THESE DECLARATIONS ============ */
    char cmdline[1024];  // the entire minishell command line
    int  num_tokens = 0; // number of tokens on the minishell command line
    char tokens[3][256]; // an array of the tokens
    int i = 0;           // just a counter
    char *p;             // pointer for stepping thru tokens
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

    /* (4) Print the minishell prompt: */
    printf("IE411> ");

/* ==== DO NOT MODIFY THIS NEXT SECTION OF CODE ============ */
    /* This reads an entire line from stdin: */
    if( fgets( cmdline, 1024, stdin ) == NULL ) { printf("\n"); break; }

    // This replaces the newline at the end of the string with a NULL
    *strrchr( cmdline, '\n') = '\0';

    // extract the individual tokens from the minishell command line
    p = cmdline;
    while( 1 == sscanf( p, " %s", tokens[i] ) )
    {
      p = strstr( p, tokens[i] ) + strlen( tokens[i] );
      ++i;
    }
    num_tokens = i;
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

    /* (5) Handle the case where there were no tokens on the
     * minishell command line, i.e., maybe the user just
     * hit the ENTER key:
     */
    
    if (num_tokens == 0) continue;

    /* (6) Handle the case where something OTHER than "mmame" */
    /*     was entered on the minishell command line:         */

    if(strcmp(tokens[0],"mmame")!=0)
    {
    	printf("minishell : %s: command not found\n",cmdline);
    	continue;
    }

    /* (7) Something valid entered on the command line, gotta fork */

    int pid = fork();

    /* (8) Handle the case where the fork failed: */
    if( pid == -1 )
    {
      exit( 1 );
    } 

    /* (9) Code that the parent executes: */ 
    if( pid !=  0 )
    {
      int status;
      wait(&pid);
    }

    /* (10) Code that the child executes: */
    else
    {
      /* (11) The child must handle these cases: */
      /*      Part 1: mmame                      */
    	if(num_tokens == 1) 
		{
			char *args[]={"./mmame",NULL}; 
			execv(args[0],args);
		}
    	else
    	{
	    	if(num_tokens==2)
	    	{
      /*      Part 2: mmame   filename           */
	    		char *args[]={"./mmame",tokens[1],(char*)0};
	    		execv(args[0],args);
	    	}
	    	else if (tokens[1][0] == '<')
	    	{
      /*      Part 3: mmame < filename           */
		    	int fd = open(tokens[2], O_WRONLY | O_CREAT, 0666);
				close(0);
				dup(fd);
				char *args[] = {"./mmame", tokens[2], NULL};
				execv(args[0], args);
	    	}
	    	else
	    	{
      /*      Part 4: mmame > filename           */
	    		int fd = open(tokens[2], O_WRONLY | O_CREAT, 0666);
				close(1);
				dup(fd);
				char* args[] = {"./mmame", tokens[2], NULL};
				execv(args[0], args);
	    	}
    		
    	}
    }
  }
  return 0;
}
