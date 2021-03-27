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
#include <sys/time.h>

#define PORT 8080
#define BUFFSIZE 1024
#define SERVERIP "127.0.0.1"

int main(int argc, char *argv[])
{
	int sockfd;		//describes socket to be binded
	char buffer[BUFFSIZE]="this is a message from client";	//buffer
	struct sockaddr_in  servaddr;	//server address
	struct timeval start, end;	//time for rtt
	int dataserv = 20;
	int dataclie, len;
	char *link = "ping";
	double t1, t2;
	int cn=10;

	// Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
                perror("socket creation failed");
                exit(1);
        }
	
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = PF_INET;          //match socket call
        servaddr.sin_addr.s_addr = INADDR_ANY;  //bind ti any local address
	servaddr.sin_port = htons(PORT);        //specify port to listen on

	len = sizeof(servaddr);
	t1 = 0.0;
	t2 = 0.0;
	while(cn--)
	{	
		//beginning time 
		if(gettimeofday(&start,NULL)) {
			printf("time failed\n");
			exit(1);
		}

		//sending data to server
		if((sendto(sockfd, (const char *)link, strlen(link), 0, (const struct sockaddr *)&servaddr, len)) < 0)
		{
			perror("sending failed\n");
			exit(1);
		}
		sleep(1);
		
		//recieving data from client
		if((dataclie = recvfrom(sockfd, (char *)buffer, BUFFSIZE, 0, (struct sockaddr *)&servaddr, &len)) < 0)
                {
                        perror("recieve failed, maybe lost\n");
                        continue;
                }
		
		//ending time
		if (gettimeofday (&end, NULL))
		{
			printf ("time failed\n");
			exit (1);
		}
		
		t1+=start.tv_sec+(start.tv_usec/1000000.0);
		t2+=end.tv_sec+(end.tv_usec/1000000.0);
		buffer[dataclie]='\0';
	        printf("Message from SERVER : %s. RTT = %g s\n", buffer, (t2-t1)/100);

		t1 = 0.0;
		t2 = 0.0;
	}

	close(sockfd);

        return 0;
}
