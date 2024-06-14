#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid = fork();

	if(pid == 0) // 자식
	{
		return 3;
	}
	else // 부모
	{
		printf("Child PID : %d \n", pid);
		pid = fork(); // 또 다른 프로세스 생성(자식생성)
		if(pid == 0)
		{
			exit(7);
		}
		else
		{
			printf("Child PID : %d \n", pid);
			wait(&status);
			if(WIFEXITED(status))// 자식프로세스가 정상 종료되면
				printf("Child send one : %d \n", WEXITSTATUS(status)); // 전달된 값 출력

			wait(&status);
			if(WIFEXITED(status))
				printf("Child send two : %d \n", WEXITSTATUS(status));
			sleep(30);
		}
	}
	return 0;
}
