/*	____________
 	 UDP CLIENT
	____________
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFSIZE 1024
#define SERVERIP "127.0.0.1"

int main(int argc, char *argv[])
{
	int sockfd;		//describes socket to be binded
	char buffer[BUFFSIZE]="this is a message from client";	//buffer
	struct sockaddr_in  servaddr;	//server address
	int dataserv = 20;
	int dataclie, len;
	char *link = "ping";

	int cn = 10;

	// Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
                perror("socket creation failed");
                exit(EXIT_FAILURE);
        }

	servaddr.sin_family = PF_INET;          //match socket call
        servaddr.sin_addr.s_addr = INADDR_ANY;  //bind ti any local address
	servaddr.sin_port = htons(PORT);        //specify port to listen on

	len = sizeof(servaddr);

	while(cn--)
	{
		sendto(sockfd, (const char *)link, strlen(link), 0, (const struct sockaddr *)&servaddr, len);
		sleep(1);
		printf("data sent to server\n");
	}


	dataclie = recvfrom(sockfd, (char *)buffer, BUFFSIZE, 0, (struct sockaddr *)&servaddr, &len);
		
	
	buffer[dataclie]='\0';
	printf("Message from SERVER : %s\n", buffer);

	close(sockfd);

        return 0;
}
