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
#include <sys/time.h>

#define PORT 8080
#define BUFFSIZE 1024
#define SERVERIP "127.0.0.1"

int main(int argc, char *argv[])
{
	int sockfd;		//describes socket to be binded
	char buffer[BUFFSIZE];	//buffer	
	struct sockaddr_in  servaddr, clientaddr;	//server and client address
	int dataserv, len;
	char *link = argv[1];

	// Creating socket file descriptor
        if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1 ) {
                perror("socket creation failed");
                exit(1);
        }

	memset(&servaddr, 0, sizeof(servaddr));
        memset(&clientaddr, 0, sizeof(clientaddr));

	servaddr.sin_family = PF_INET;          //match socket call
        servaddr.sin_addr.s_addr = INADDR_ANY;  //bind ti any local address
	servaddr.sin_port = htons(PORT);        //specify port to listen on
	
	if((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))<0)
	{
		perror("bind failed\n");
		exit(1);
	}
	
	len = sizeof(clientaddr);

	//recieving data from client
	if((dataserv = recvfrom(sockfd, buffer, BUFFSIZE, 0, (struct sockaddr *)&clientaddr, &len)) < 0)
	{
		perror("recieve failed\n");
		exit(1);
	}
	
	//sending data to client
	if((sendto(sockfd, (char *)link, strlen(link), 0, (const struct sockaddr *) &clientaddr, len))<0)
	{
		perror("sending failed\n");
		exit(1);
	}
	buffer[dataserv] = '\0';
	printf("Message from CLIENT : %s\n", buffer);

        return 0;
}

