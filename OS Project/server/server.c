#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8000
#define maxlen 70000
#define mlen 100000
#define remote_port 8001
int main()
{
	printf("\n\n\t\t\t      UDP FILE TRANSFER SYSTEM");
	printf("\n\n\t\t\t      WELCOME TO THE MAIN MENU");
	printf("\n\n\t\t\t      THIS IS THE SERVER SIDE");
	char fileName[100];
	char filebuffer[2000], caufile[maxlen];
	char *vfilep;
	int aufile[700000], vfile[mlen];
	int sd, connfd, len, remote_sock, x, z, remote_len;
	char datagram[512];
	char Bye[4] = "Bye";
	for (int i = 0; i <= 100; i++)
	{
		fileName[i] = '\0';
	}
	struct sockaddr_in servaddr, cliaddr;
	struct sockaddr_in remote_add;
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1)
	{
		printf("\n\n socket not created in server\n");
		exit(0);
	}
	else
		printf("\n\nsocket created in  server\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	memset(&(servaddr.sin_zero), '\0', 8);
	if (bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
		printf(" \nNot binded\n");
	else
		printf(" \nBinded...Ready to Recieve Files...\n");
	len = sizeof(cliaddr);
	int choice = 1;

Recreated:
	while (1)
	{
		char num;
		recvfrom(sd, &num, sizeof(num), 0, (struct sockaddr *)&cliaddr, &len);
		choice = num;
		switch (choice)
		{
		case 1:
			recvfrom(sd, fileName, 1024, 0, (struct sockaddr *)&cliaddr, &len);
			printf(" NAME OF TEXT FILE RECEIVED: %s\n", fileName);
			FILE *fp;
			printf(" Contents in the RECIEVED TEXT file: \n");
			recvfrom(sd, filebuffer, 1024, 0, (struct sockaddr *)&cliaddr, &len);
			printf("%s\n", filebuffer);
			int fsize = strlen(filebuffer);
			fp = fopen(fileName, "w");
			if (fp)
			{
				fwrite(filebuffer, fsize, 1, fp);
				printf(" File received successfully\n");
				strcpy(datagram, "Got Your Message\n");
				x = sendto(sd, datagram, strlen(datagram), 0, (struct sockaddr *)&cliaddr, sizeof(struct sockaddr));
				if (x != -1)
				{
					puts("Message sent...\n");
				}
			}
			else
				printf(" Error!! Unable to Create Output File\n");
			memset(fileName, '\0', sizeof(fileName));
			fclose(fp);
			break;
		case 2:
			recvfrom(sd, fileName, 1024, 0, (struct sockaddr *)&cliaddr, &len);
			printf(" NAME OF AUDIO FILE RECEIVED: %s\n", fileName);
			FILE *afp;
			int numbytes;
			afp = fopen(fileName, "w");
			size_t afsize;
			afsize = recvfrom(sd, aufile, 700000, 0, (struct sockaddr *)&cliaddr, &len);
			if (afp)
			{
				fwrite(aufile, afsize, 1, afp);
				printf(" File received successfully\n");
				strcpy(datagram, "Got Your Audio File\n");
				x = sendto(sd, datagram, strlen(datagram), 0, (struct sockaddr *)&cliaddr, sizeof(struct sockaddr));
				if (x != -1)
				{
					puts("Message sent...\n");
				}
			}
			else
				printf(" Error!! Unable to Open Output File\n");
			memset(fileName, '\0', sizeof(fileName));
			fclose(afp);
			break;
		case 3:
			recvfrom(sd, fileName, 1024, 0, (struct sockaddr *)&cliaddr, &len);
			printf(" VIDEO FILE NAME RECEIVED: %s\n", fileName);
			FILE *vfp;
			vfp = fopen(fileName, "w");
			size_t vfsize;
			vfsize = recvfrom(sd, vfile, 100000, 0, (struct sockaddr *)&cliaddr, &len);
			if (vfp)
			{
				fwrite(vfile, vfsize, 1, vfp);
				printf(" File received successfully\n");
				strcpy(datagram, "Got Your Video File\n");
				x = sendto(sd, datagram, strlen(datagram), 0, (struct sockaddr *)&cliaddr, sizeof(struct sockaddr));
				if (x != -1)
				{
					puts("Message sent...\n");
				}
			}
			else
				printf(" Error!! Unable to Open Output File\n");
			fclose(vfp);
			break;
		case 4:

			while (1)
			{
				bzero(datagram, 512);
				/* Here we are waiting for recieving a message from remote machine */
				printf("Waiting for response.........\n");
				z = recvfrom(sd, datagram, 512, 0, (struct sockaddr *)&cliaddr, &len);
				datagram[z] = 0;
				if (strcmp(datagram, Bye) == 0)
				{
					printf("Client: Bye\nClosing chat...\n");
					printf("Bye\n");
					goto Recreated;
				}
				printf("Client: %s", datagram);
				printf("\nYou(Send A message): ");
				bzero(datagram, 512);
				fgets(datagram, 512, stdin);

				x = sendto(sd, datagram, strlen(datagram), 0, (struct sockaddr *)&cliaddr, sizeof(struct sockaddr));
				if (x != -1)
				{
					puts("Message sent...\n");
				}
				if (strcmp(datagram, Bye) == 0)
				{
					printf("Closing Chat....\n");
					goto Recreated;
				}
			}
		case 5:
			close(sd);
			break;
		}
	}
	return (0);
}
