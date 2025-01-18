
Conversation opened. 1 unread message.

Skip to content
Using University of Southern California Mail with screen readers
Enable desktop notifications for University of Southern California Mail.   OK  No thanks
1 of 739
server
Inbox
Tim Lu <hlu67994@usc.edu>
	
Attachments2:58 PM (0 minutes ago)
	
to me

 One attachment  •  Scanned by Gmail
	

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <signal.h>
#include <string.h>
void error(char *msg)
{
    perror(msg);
    exit(1);
}
/*void dostuff(int newsockfd)
{
	 char buffer[256];
	 bzero(buffer,256);
     int n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
	 return;
}
*/
int main(int argc, char *argv[])
{
	// kill zombie process
	signal(SIGCHLD,SIG_IGN);
     int sockfd, newsockfd, portno, clilen;
     char buffer[1024];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_DGRAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     //listen(sockfd,5);
     socklen_t fromlen=sizeof(struct sockaddr_in);
	 while (1){
	 	bzero(buffer,1024);
		n = recvfrom(sockfd,buffer,1024,0,(struct sockaddr* )&cli_addr,&fromlen);
		if(n<0)error("recvfrom");
		printf("The message is %s\n",buffer); 
		bzero(buffer,1024);
		fgets(buffer,1023,stdin);
		n = sendto(sockfd,buffer,strlen(buffer), 0,(struct sockaddr *) &cli_addr,sizeof(cli_addr));
		if (n < 0)
		error("sendto"); 
	 }

	 
	

     
     return 0; 
}
