#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void runFilters(int *pipes, int forkNum, int length, char *arguments[]) 
{
	if(forkNum <= (length / 2) + 1) 
	{
		if(fork() == 0) 
		{
			char *currArgs[] = {arguments[0], arguments[(forkNum * 5) - 4], arguments[(forkNum * 5) - 3], arguments[(forkNum * 5) - 2], 
			arguments[(forkNum * 5) - 1], arguments[forkNum * 5], (char *)NULL}; //store the current 5 arguments
			
			//pipeline the current fork with standard I/O		
			if(forkNum == 1)  //replace stdout of first fork with write end of first pipe
				dup2(pipes[1], 1);		
			else if(forkNum == (length / 2) + 1)  //replace stdin of last fork with input read from last pipe
				dup2(pipes[0], 0);
			else
			{     
				dup2(pipes[0], 0);  //replace stdin of the current fork with read end of previous pipe
				dup2(pipes[1], 1);  //replace stdout of the current fork with write end of current pipe
			}
			for(int i = 0; i < length; i++)  //close pipes
				close(pipes[i]);
			
			execvp("./biquad", currArgs);  //run biquad filter with the current arguments
		} 
		else
			runFilters(pipes, forkNum + 1, length, arguments);  //recur with next fork if we are not in child process
	}
}

int main(int argc, char *argv[]) 
{   
	int n = (argc - 1) / 5;  //number of filters to run
    int status = 0;
    int pipes[(n - 1) * 2];
	
    for(int i = 0; i < (n - 1) * 2; i = i + 2)
        pipe(pipes + i);
    
	runFilters(pipes, 1, (n - 1) * 2, argv); //run the cascade filter
    
    for(int i = 0; i < (n - 1) * 2; i++) //close pipes
        close(pipes[i]);
    
    for (int i = 0; i < n; i++) 
        wait(&status);
}