#include "net.h"

#define PORT 9104

int main(void)
{
    char request[2048];
    printf("Enter request: ");
    fflush(stdout);
    if (!read_input(request, sizeof(request))) {
        fputs("Could not read the request, or the line is too long.\n", stderr);
        return EXIT_FAILURE;
    }
    Socket sock = open_socket(SOCK_STREAM, PORT, 0);
    char reply[8192];
    if (!send_all(sock, request, (int)strlen(request)) || !send_all(sock, "\n", 1)) {
        fputs("Could not send the request.\n", stderr);
        close_socket(sock);
        return EXIT_FAILURE;
    }
    if (!receive_line(sock, reply, sizeof(reply))) {
        fputs("Could not read a complete reply.\n", stderr);
        close_socket(sock);
        return EXIT_FAILURE;
    }
    close_socket(sock);
    puts(reply);
    return strncmp(reply, "ERROR:", 6) == 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
