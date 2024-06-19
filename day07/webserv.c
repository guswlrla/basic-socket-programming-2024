#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

char webpage[] = "НТTP/1.1 200 OK\r\n"
							"Server:Linux Web Server\r\n"
							"Content-Type: text/html; charset=UTF-8\r\n\r\n"
							"<!DOCTYPE html> \r\n"
							"<html><head><title> My Web Page </title>\r\n"
							"‹style>body {background-color: #FFFF00}</style></head›\r\n"
							"<body><center><h1>Hello world!!</h1><br>\r\n"
							"<img src=\"game.jpg\"></center></body></html>\r\n";

int main(int argc, char argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr
}
