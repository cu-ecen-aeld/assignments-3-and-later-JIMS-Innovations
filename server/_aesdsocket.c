 /*
* @author Jesutofunmi Kupoluyi
* @brief: Native socket server
* @date: 19 June, 2023
*/

/* Definitions */
#define BUF_SIZE 1024


/* Including required libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <syslog.h>

static int exit_signal = 0;

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        exit_signal = 1;
    }
    else if (sig == SIGTERM)
    {
        exit_signal = 1;
    }
}

/* main */
int main(int argc, char *argv[])
{
	if (argc == 2)
    {
//        if (strlen(argv[2]) && argv[2][1] == 'd')
        {
            //make damon
            int pid = fork();
            if (pid != 0)
            {
                exit(0);
            }
            setsid();
            chdir("/");
        }
    }

	/* Setup signal actions */
	struct sigaction new_action;
    memset(&new_action, 0, sizeof(struct sigaction));
    new_action.sa_handler=signal_handler;
    sigaction(SIGTERM, &new_action, NULL);
    sigaction(SIGINT, &new_action, NULL);

	/* Create socket variable */
	int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		perror("socket");
		return -1;
	}

	/* Get socket address */
	int status;
	struct addrinfo hints = {0};
	struct addrinfo *servinfo;	

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	status = getaddrinfo(NULL, "9000", &hints, &servinfo);
	if(status != 0)
	{
		perror("getaddrinfo");
		return -1;
	}

	
	/* Bind socket to server */
	status = bind(socket_fd, servinfo->ai_addr, servinfo->ai_addrlen );
	if(status != 0)
      {   
          perror("bind");
          return -1;
      }

	/* Listen on the port */
	status = listen(socket_fd, 0);
	if(status != 0)
      {   
          perror("listen");
          return -1;
      }
	printf("Listening for connection\n");

	while (exit_signal == 0)
	{
		/* Accept connection */
		struct sockaddr client_info = {0};
		socklen_t client_info_len = sizeof(client_info);
 		int client_fd = accept(socket_fd, &client_info, &client_info_len );
		if(client_fd < 0)
		{
			perror("accept");
			return -1;
		}
		else 
		{	
		/* Getting the client's IP address */
		char client_addr[32];
		inet_ntop(AF_INET, (struct sockaddr_in *)&client_info, client_addr, sizeof(client_addr));
	
		/* syslog */
		openlog(NULL, 0, LOG_USER);
		syslog(LOG_INFO, "Accepted connection from %s", client_addr);
		/* end of syslog */

		printf("Accepted connection from %s\n", client_addr);	
		
		while(1)
		{
			/* Receive data */
			char buffer[BUF_SIZE];
			ssize_t recvd_data = recv(socket_fd, &buffer, BUF_SIZE, 0);

			/* Open file for storing received data */
        	FILE *fp;
        	fp = fopen("/var/tmp/aesdsocketdata", "a+");

			if(recvd_data == 0)
			{
				break;
			}
			else if (recvd_data < 0)
			{
				perror("recv");
			}	
			else
			{
				fwrite(buffer, 1, recvd_data, fp);
				if(buffer[recvd_data-1] == '\n')
					break;
			}
			rewind(fp);
            char* line = NULL;
            size_t len = 0;
            ssize_t read = 0;
            while((read = getline(&line, &len, fp)) != -1)
            {
                send(client_fd, line, read, 0);
            }
            free(line);
            fclose(fp);
            close(client_fd);
			syslog(LOG_INFO, "Closed connection from %s", client_addr);
            printf("Closed connection from %s\n", client_addr);


		}
	}
}



	/* close connection and  free socket address info */
	close(socket_fd);
	remove("/var/tmp/aesdsocketdata");
    shutdown(socket_fd, SHUT_RDWR);
	syslog(LOG_INFO, "Goodbye");
    fprintf(stdout, "Goodbye\n");
	freeaddrinfo(servinfo);	

	return 0;
}
