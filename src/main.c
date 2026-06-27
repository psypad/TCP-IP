#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if_ether.h>

int main(void){
    printf("Value returned by socket:\n");

    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if(sock < 0){
        perror("Error opening socket");
        return 1;
    }
    
    printf("Raw socket fd: %d\n",sock);

    unsigned char buffer[2048];

    while (1) {
        ssize_t n = recv(sock, buffer, sizeof(buffer), 0);

        printf("Received %ld bytes\n", n);

        

        printf("Destination MAC: ");
        for(int k =0; k<6;k++){
            printf("%02x ", buffer[k]);
        }
        printf("\n");

        printf("Source MAC: ");
        for(int k =6; k<12;k++){
            printf(" %02x ", buffer[k]);
        }
        printf("\n");

        printf("EtherType: ");
        for(int k =12; k<14;k++){
            printf("%02x ", buffer[k]);
        }
        printf("\n");
    

        printf("\n");
    }  
    
    close(sock);

    return 0;
}

