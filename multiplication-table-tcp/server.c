#include "net.h"

#define PORT 9110

#include <ctype.h>

static void answer(const char *request, char *reply, size_t capacity)
{
    char *end;
    errno = 0;
    long number = strtol(request, &end, 10);
    if (end == request || errno == ERANGE || number < -1000000 || number > 1000000) {
        snprintf(reply, capacity, "ERROR: enter an integer from -1000000 to 1000000");
        return;
    }
    while (isspace((unsigned char)*end))
        end++;
    if (*end) {
        snprintf(reply, capacity, "ERROR: enter one integer");
        return;
    }

    size_t used = 0;
    for (int factor = 1; factor <= 10; factor++) {
        used += (size_t)snprintf(reply + used, capacity - used, "%ld x %d = %ld%s",
                                 number, factor, number * factor, factor == 10 ? "" : " | ");
    }
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
