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

/*
void thatmath(char const *buffer)
{
	char digit[2][10];
        int i, j=0, c=0;
        double a, b, result;
        char op = buffer[0];

        for(i=2; buffer[i]!='\0'; i++)
        {
                if(buffer[i]==':')
                {
                        j=0;
                        c++;
                }
                else
                {
                        digit[c][j] = buffer[i];
                        j++;
                }
        }
        a=atof(digit[0]);
	b=atof(digit[1]);

	result = ((op=='+')?(a+b):
			((op=='-')?(a-b):
			 ((op=='*')?(a*b):
			  ((op=='/')?(a/b):0))));
	
	printf("Output: %.2f %c %.2f = %.2f\n", a, op, b, result);
}*/


int main (int argc, char *argv[])
{
	int sockfd;		//describes socket to be binded
	char buffer[BUFFSIZE]="this is a message from client";	//buffer
	struct sockaddr_in  servaddr;	//server address
	struct timeval start, end;	//time for rtt
	int dataserv = 20;
	int dataclie, len;
	char *link = "ping";
	double t1, t2;

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

	//beginning time 
	if(gettimeofday(&start,NULL)) {
		printf("time failed\n");
		exit(1);
	}

	//sending data to server
	if((sendto(sockfd, (char *)link, strlen(link), 0, (const struct sockaddr *)&servaddr, len)) < 0)
	{
		perror("sending failed\n");
		exit(1);
	}
	sleep(1);
	
	//recieving data from client
	if((dataclie = recvfrom(sockfd, (char *)buffer, BUFFSIZE, 0, (struct sockaddr *)&servaddr, &len)) < 0)
	{
        	perror("recieve failed\n");
                exit(1);
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

	//math
//	thatmath(buffer);

	char digit[2][3];
        int i, j=0, c=0;
        double a, b, result;
        char op = buffer[0];
	for(i=2; buffer[i]!='\0'; i++)
        {
                if(buffer[i]==':')
                {
                        j=0;
                        c++;
                }
                else
                {
                        digit[c][j] = buffer[i];
                        j++;
                }
        }
        a=atof(digit[0]);
        b=atof(digit[1]);

        result = ((op=='+')?(a+b):
                        ((op=='-')?(a-b):
                         ((op=='*')?(a*b):
                          ((op=='/')?(a/b):0))));

        printf("Output: %.2f %c %.2f = %.2f\n", a, op, b, result);

        printf("RTT = %g s\n", (t2-t1)/100);

	close(sockfd);

        return 0;
}
