
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char *message, server_reply[2000];
    int message_len, recv_size;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }

    // Set server details
    server.sin_addr.s_addr = inet_addr("192.168.1.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    printf("Connected\n");

    // Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    message_len = strlen(message);

    if (send(sock, message, message_len, 0) < 0) {
        puts("Send failed");
        return 1;
    }

    printf("Data Sent\n");

    // Receive a reply from the server
    if ((recv_size = recv(sock, server_reply, 2000, 0)) < 0) {
        puts("recv failed");
    }

    printf("Reply received\n");

    // Add a NULL terminating character to the end of the data
    server_reply[recv_size] = '\0';
    printf("%s\n", server_reply);

    close(sock);
    return 0;
}
