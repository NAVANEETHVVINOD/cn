#include "net.h"

#define PORT 9101

int main(void)
{
    char request[2048];
    printf("Enter request: ");
    fflush(stdout);
    if (!read_input(request, sizeof(request))) {
        fputs("Could not read the request, or the line is too long.\n", stderr);
        return EXIT_FAILURE;
    }
    Socket sock = open_socket(SOCK_DGRAM, PORT, 0);
    char reply[8192];
    size_t length = strlen(request);
    if (send(sock, request, (int)length, 0) != (int)length) {
        fputs("Could not send the request.\n", stderr);
        close_socket(sock);
        return EXIT_FAILURE;
    }
    int received = (int)recv(sock, reply, sizeof(reply), 0);
    if (received < 0 || (size_t)received == sizeof(reply)) {
        fputs("Could not read a complete reply.\n", stderr);
        close_socket(sock);
        return EXIT_FAILURE;
    }
    reply[received] = '\0';
    close_socket(sock);
    puts(reply);
    return strncmp(reply, "ERROR:", 6) == 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
