#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8000
#define remote_port 8001
int main()
{
  int fd;
  char datagram[512], fileName[100], afileName[100], vfileName[100], file_buffer[100], c, caufile[7000], aufile[7000000], vfile[1000000];
  char Bye[4] = "Bye";
  struct sockaddr_in servaddr;
  struct sockaddr_in remote_add;
  int remote_len, z, x, remote_sock;
  // Creating socket
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Error!! Socket was not Created....Exiting");
    exit(EXIT_FAILURE);
  }
  printf("\n\n\t\t\t      UDP FILE TRANSFER SYSTEM");
  printf("\n\n\t\t\t      WELCOME TO THE MAIN MENU");
  printf("\n\n\t\t\t      THIS IS CLIENT SIDE");

  memset(&servaddr, 0, sizeof(servaddr));
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;
  int len = sizeof(servaddr);
  int choice;
Loop:
  while (choice != 5)
  {
    printf("\n\n ENTER \n 1.TEXT \n 2.AUDIO \n 3.VIDEO\n 4.Chat\n 5.EXIT\n Enter Your Choice: ");
    scanf("%d", &choice);
    char num = choice;

    sendto(fd, &num, sizeof(num), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));

    switch (choice)
    {
    case 1:
      printf(" Enter text file name to send: \n");
      scanf("%s", fileName);
      sendto(fd, fileName, strlen(fileName), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));

      FILE *fp;
      fp = fopen(fileName, "r");

      if (fp)
      {
        printf(" Reading file contents...\n");
        fseek(fp, 0, SEEK_END);
        size_t file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        if (fread(file_buffer, file_size, 1, fp) <= 0)
        {
          printf(" Error!! Empty File or Error reading the File...\n");
          exit(1);
        }
      }
      else
      {
        printf(" Error!! Cannot open the file\n");
        exit(0);
      }
      printf(" FILE CONTENTS to Send :\n%s\n", file_buffer);
      if (sendto(fd, file_buffer, strlen(file_buffer), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0)
      {
        printf("Error!! File wad not Sent\n");
      }
      else
      {
        printf("File Sent Sucessfully\n");
        z = recvfrom(fd, datagram, 512, 0, (struct sockaddr *)&servaddr, &len);
        printf("Acknowledgement from server: %s", datagram);
      }
      fclose(fp);
      break;

    case 2:
      printf("Enter audio file name to send : \n");
      scanf("%s", afileName);
      sendto(fd, afileName, strlen(afileName), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
      FILE *afp;
      afp = fopen(afileName, "r");
      fseek(afp, 0, SEEK_END);
      size_t afsize = ftell(afp);
      fseek(afp, 0, SEEK_SET);

      if (afp)
      {
        printf("Reading file contents.\n");
        if (fread(aufile, afsize, 1, afp) <= 0)
        {
          printf("Error!! Empty file or Error reading the File\n");
          exit(1);
        }
      }
      else
      {
        printf("Could not read audio file.\n");
        exit(0);
      }

      if (sendto(fd, aufile, afsize, 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0)
      {
        printf("Error!! Unable to send the file\n");
      }
      else
      {
        printf(" File Sent Sucessfully\n");
        z = recvfrom(fd, datagram, 512, 0, (struct sockaddr *)&servaddr, &len);
        printf("Acknowledgement from server: %s", datagram);
      }
      fclose(afp);
      break;

    case 3:
      printf("Enter video file name to send : \n");
      scanf("%s", vfileName);
      sendto(fd, vfileName, strlen(vfileName), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
      FILE *vfp;
      vfp = fopen(vfileName, "r");
      fseek(vfp, 0, SEEK_END);
      size_t vfsize = ftell(vfp);
      fseek(vfp, 0, SEEK_SET);
      if (vfp)
      {
        if (fread(vfile, 1, vfsize, vfp) <= 0)
          printf("Error!! Empty file or Error reading the File\n");
      }
      else
      {
        printf("Could not read audio file.\n");
        exit(0);
      }
      if (sendto(fd, vfile, vfsize, 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0)
        printf("Error!! File was not sent\n");
      else
      {
        printf("File Sent Sucessfully \n");
        z = recvfrom(fd, datagram, 512, 0, (struct sockaddr *)&servaddr, &len);
        printf("Acknowledgement from server: %s", datagram);
      }
      fclose(vfp);
      break;

    case 5:
      close(fd);
      break;
    case 4:
      printf("Client Initiated Chat ...\nType 'Bye' to exit from chat");
      fflush(stdin);
      fgets(datagram, 512, stdin);
      while (1)
      {
        printf("\nYou(Send A message): ");
        bzero(datagram, 512);
        fgets(datagram, 512, stdin);
        x = sendto(fd, datagram, strlen(datagram), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
        if (x != -1)
        {
          printf("Message sent. ");
        }
        if (strcmp(datagram, Bye) == 0)
        {
          printf("Closing chat..\n");
          break;
        }
        printf("Waiting for response.........\n");
        bzero(datagram, 512);
        // z = recvfrom(fd, datagram, 512, 0, (struct sockaddr *)&remote_add, &remote_len);
        z = recvfrom(fd, datagram, 512, 0, (struct sockaddr *)&servaddr, &len);
        datagram[z] = 0;
        printf("\nServer: %s", datagram);
        if (strcmp(datagram, Bye) == 0)
        {
          printf("Closing chat..\n");
          break;
        }
      }
      break;
    default:
      printf("Wrong Input... Try Again...\n\n");
      break;
    }
  }
}
