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

        for(int i = 0; i<n;i++){
            printf("%02x ", buffer[i]);
        }

        printf("\n");
    }  
    
    close(sock);

    return 0;
}

