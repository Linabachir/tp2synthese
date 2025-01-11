#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// TFTP Client: Downloads a file from a TFTP server
int main(int argc, char ** argv) {
    printf("TFTP Client \n");
 // Check mmand-line arguments
    if (argc != 4){
        printf("Wrong command \n");
        exit(EXIT_FAILURE);
    }

    int fd=open(argv[3],O_CREAT|O_WRONLY,S_IRWXG|S_IRWXU|S_IRWXO);
// Resolve the server address
    struct addrinfo hints;
    struct addrinfo * result;
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;

    int status = getaddrinfo(argv[1],argv[2],&hints,&result);

    char ip_string[128]={0};
    char port_string[128]={0};
   // Print the resolved server IP and port
    getnameinfo(result->ai_addr,result->ai_addrlen,
                ip_string,128,port_string,128,
                NI_NUMERICHOST|NI_NUMERICSERV);

    printf("%s is resolved at : %s:%s\n",argv[1],ip_string,port_string);
// Create a UDP socket
    int sd = socket(result->ai_family,result->ai_socktype,
                    result->ai_protocol);
   // Build and send the RRQ (Read Request)
    char rrq[128]={0};
    rrq[1]=1;
    sprintf(rrq+2,"%s",argv[3]);
    sprintf(rrq+3+strlen(argv[3]),"octet");

    sendto(sd,rrq,strlen(argv[3])+9,0,
           result->ai_addr,result->ai_addrlen);

    int bytes;
    do{
        // Receive data packets from the server
        char buffer[516]={0};

        struct sockaddr data_connexion;
        socklen_t data_connexion_length;
        bytes=recvfrom(sd,buffer,516,0,&data_connexion,&data_connexion_length);

        if(buffer[1]==5){
            printf("Error during transmission on block %d : %s\n",buffer[3],buffer+4);
            exit(EXIT_FAILURE);
        }
// Write received data to the file
        write(fd,buffer+4,bytes-4);
  // Send acknowledgment (ACK) to the server
        char ack[4]={0};
        ack[1]=4;
        ack[2]=buffer[2];
        ack[3]=buffer[3];

        sendto(sd,ack,4,0,&data_connexion,data_connexion_length);
   
        printf("Received %d bytes \n",bytes);
    }while(bytes ==516);

    freeaddrinfo(result);
    close(fd);

    return 0;
}
