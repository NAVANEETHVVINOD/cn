#include "net.h"

#define PORT 9101

#include <ctype.h>
#include <limits.h>

static int next_integer(const char **cursor, int *value)
{
    char *end;
    errno = 0;
    long number = strtol(*cursor, &end, 10);
    if (end == *cursor || errno == ERANGE || number < INT_MIN || number > INT_MAX ||
        (*end && !isspace((unsigned char)*end)))
        return 0;
    *cursor = end;
    *value = (int)number;
    return 1;
}

static void answer(const char *request, char *reply, size_t capacity)
{
    int order;
    if (!next_integer(&request, &order) || order < 1 || order > 10) {
        snprintf(reply, capacity, "ERROR: matrix order must be between 1 and 10");
        return;
    }

    int upper = 1, lower = 1;
    for (int row = 0; row < order; row++) {
        for (int column = 0; column < order; column++) {
            int value;
            if (!next_integer(&request, &value)) {
                snprintf(reply, capacity, "ERROR: expected %d integer values", order * order);
                return;
            }
            if (row > column && value)
                upper = 0;
            if (row < column && value)
                lower = 0;
        }
    }
    while (isspace((unsigned char)*request))
        request++;
    if (*request) {
        snprintf(reply, capacity, "ERROR: too many matrix values");
        return;
    }

    const char *type = "Ordinary";
    if (upper && lower)
        type = "Diagonal";
    else if (upper)
        type = "Upper triangular";
    else if (lower)
        type = "Lower triangular";
    snprintf(reply, capacity, "Matrix type: %s", type);
}

int main(void)
{
    Socket server = open_socket(SOCK_DGRAM, PORT, 1);
    for (;;) {
        struct sockaddr_in client;
        AddressLength client_size = sizeof(client);
        char request[2049];
        char reply[8192];

        int length = (int)recvfrom(server, request, sizeof(request), 0,
                                  (struct sockaddr *)&client, &client_size);
        if (length < 0) {
#ifdef _WIN32
            if (WSAGetLastError() == WSAEMSGSIZE)
                continue;
#endif
            fail("recvfrom");
        }
        if ((size_t)length == sizeof(request) || memchr(request, '\0', length)) {
            strcpy(reply, "ERROR: invalid request datagram");
        } else {
            request[length] = '\0';
            answer(request, reply, sizeof(reply));
        }

        if (sendto(server, reply, (int)strlen(reply), 0,
                   (struct sockaddr *)&client, client_size) < 0)
            fputs("Could not send the reply.\n", stderr);
    }
}
