/*	____________
 	 UDP SERVER
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

int main(int argc, char *argv[])
{
	int sockfd;		//describes socket to be binded
	char buffer[BUFFSIZE];	//buffer	
	struct sockaddr_in  servaddr, clientaddr;	//server and client address
	int dataserv, len;
	char *link = "pong";
	int cn = 10;

	// Creating socket file descriptor
        if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1 ) {
                perror("socket creation failed");
                exit(EXIT_FAILURE);
        }


	servaddr.sin_family = PF_INET;          //match socket call
        servaddr.sin_addr.s_addr = INADDR_ANY;  //bind ti any local address
	servaddr.sin_port = htons(PORT);        //specify port to listen on
	
	if((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))<0)
	{
		perror("cannot bind\n");
		exit(EXIT_FAILURE);
	}
	
	len = sizeof(clientaddr);
	while(cn--)
	{
		if((dataserv = recvfrom(sockfd, buffer, BUFFSIZE, 0, (struct sockaddr *)&clientaddr, &len)) < 0)
		{
			perror("cannot recieve\n");
			exit(EXIT_FAILURE);
		}
		buffer[dataserv] = '\0';
		printf("Message from CLIENT : %s\n", buffer);
	}

//	buffer[dataserv] = '\0';
//	printf("data from CLIENT : %s\n", buffer);
	
	sendto(sockfd, (const char *)link, strlen(link), 0, (const struct sockaddr *) &clientaddr, len);

        return 0;
}
