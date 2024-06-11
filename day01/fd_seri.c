#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void)
{
	int fd1, fd2, fd3;
	fd1 = socket(PF_INET, SOCK_STREAM, 0);
	fd2 = open("test.dat", O_CREAT|O_WRONLY|O_TRUNC);
	fd3 = socket(PF_INET, SOCK_DGRAM, 0);

	printf("file descriptor 1 : %d\n", fd1);
	printf("file descriptor 2 : %d\n", fd2);
	printf("file descriptor 3 : %d\n", fd3);

	close(fd1); close(fd2); close(fd3);
	return 0;
}

// 파일 디스크립터 0, 1, 2는 운영체제에서 사용하고 있음
// 0 : 표준입력, 1 : 표준출력, 2 : 표준에러
