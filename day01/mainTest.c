#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("전달하는 인자개수 : %d\n", argc);
	printf("실행파일 : %s\n", argv[0]);

	for(int i = 0; i < argc; i++)
	{
		printf("전달인자 : %s\n", argv[i]);
	}
	
	return 0;
}
