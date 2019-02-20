#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>

void monitorar_ucp(int pid)
{
	char bash_cmd[256];
	sprintf(bash_cmd, "ps u %d | awk '{print $3}' | grep -v CPU", pid);
	char buffer[1000];
	FILE *pipe;
	int len; 
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) {
		perror("pipe");
		exit(1);
	} 
	
	char* cpu_usage = fgets(buffer, sizeof(buffer), pipe);
	len = strlen(bash_cmd);
	bash_cmd[len-1] = '\0'; 
	pclose(pipe);

	printf("cpu_usage == %s", cpu_usage);
	//ADAPTED teacher code to monitor UCP;
}


void monitorar_mem(int pid)
{
	char bash_cmd[256];
	sprintf(bash_cmd, "ps u %d | awk '{print $5}' | grep -v VSZ", pid);
	char buffer[1000];
	FILE *pipe;
	int len; 
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) {
		perror("pipe");
		exit(1);
	} 
	
	char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
	len = strlen(bash_cmd);
	bash_cmd[len-1] = '\0'; 
	pclose(pipe);

	printf("mem_usage == %s\n", mem_usage);
	// ADAPTED teacher code to monitor MEMORY;
}




void matar_meu_filho(int pid)
{
	char bash_cmd[256] = "kill -TERM 0";
	sprintf(bash_cmd, "kill -TERM %d",pid);
	char buffer[1000];
	FILE *pipe;
	int len; 
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) {
		perror("pipe");
		exit(1);
	} 
	
	char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
	len = strlen(bash_cmd);
	bash_cmd[len-1] = '\0'; 
	pclose(pipe);
	// teacher code ADAPTED to kill the child;


}


int main(int argc, char **argv)
{
	//first I see if the user put the arguments at the time of executing the program;
	if (argc<2)
	{
		printf("Por favor use ucp ou ucp-mem\n");
	}
	else 
	{
		int pid;
		pid=fork();

		if (pid<0)
		{
			//this part is executed if the fork gives error;
			printf("Erro\n");
			exit(-1);
		}
		else if (pid==0)
		{
			
			if (strcmp(argv[1], "ucp")==0)
			{
				//in this conditional if the argument that he used is UCP we loop infinitely to demand enough of the UCP;
				for (;;){}
			}
			else if (strcmp(argv[1], "ucp-mem")==0){
				for(;;)
				{
					//here we check if it has put UCP-mem and we make intense use of UCP and memory;
					usleep(1);
					malloc(sizeof(10000));
				}
			}
			
		}
		else 
		{
			// we do the same in the father;
			if (strcmp(argv[1], "ucp")==0)
			{

				for (int i = 0; i < 10; ++i)
				{
					//if it is only UCP, he monitors how much from the UCP the child uses every 1 second for 5 times;
					sleep(1);
					monitorar_ucp(pid);
				}
			}
			else if(strcmp(argv[1], "ucp-mem")==0)
			{
				for (int i = 0; i < 10; ++i)
				{
					//if it is UCP-MEM, he monitors how much from the UCP and the MEMORY the child uses every 1 second for 5 times;
					sleep(1);
					monitorar_ucp(pid);
					monitorar_mem(pid);
				}
			}
			//after all, we broke up with our son;
			matar_meu_filho(pid);
		}
	}
}

