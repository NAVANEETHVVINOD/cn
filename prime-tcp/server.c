#include "net.h"

#define PORT 9102

#include <ctype.h>
#include <limits.h>

static void answer(const char *request, char *reply, size_t capacity)
{
    char *end;
    errno = 0;
    long number = strtol(request, &end, 10);
    if (end == request || errno == ERANGE || number < INT_MIN || number > INT_MAX) {
        snprintf(reply, capacity, "ERROR: enter one signed 32-bit integer");
        return;
    }
    while (isspace((unsigned char)*end))
        end++;
    if (*end) {
        snprintf(reply, capacity, "ERROR: enter one signed 32-bit integer");
        return;
    }

    int prime = number >= 2;
    for (long divisor = 2; prime && divisor <= number / divisor; divisor++) {
        if (number % divisor == 0)
            prime = 0;
    }
    snprintf(reply, capacity, "%ld is %sprime.", number, prime ? "" : "not ");
}

int main(void)
{
    Socket server = open_socket(SOCK_STREAM, PORT, 1);
    for (;;) {
        Socket client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET)
            fail("accept");
        set_timeout(client);

        char request[2048];
        char reply[8192];
        if (receive_line(client, request, sizeof(request)))
            answer(request, reply, sizeof(reply));
        else
            strcpy(reply, "ERROR: expected a complete request line");

        if (!send_all(client, reply, (int)strlen(reply)) ||
            !send_all(client, "\n", 1))
            fputs("Could not send the reply.\n", stderr);
        close_socket(client);
    }
}
