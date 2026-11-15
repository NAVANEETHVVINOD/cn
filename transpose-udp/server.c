#include "net.h"

#define PORT 9107

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
    int rows, columns;
    if (!next_integer(&request, &rows) || !next_integer(&request, &columns) ||
        rows < 1 || rows > 10 || columns < 1 || columns > 10) {
        snprintf(reply, capacity, "ERROR: dimensions must be between 1 and 10");
        return;
    }

    int matrix[10][10];
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            if (!next_integer(&request, &matrix[row][column])) {
                snprintf(reply, capacity, "ERROR: expected %d integer values", rows * columns);
                return;
            }
        }
    }
    while (isspace((unsigned char)*request))
        request++;
    if (*request) {
        snprintf(reply, capacity, "ERROR: too many matrix values");
        return;
    }

    size_t used = (size_t)snprintf(reply, capacity, "Transpose (%d x %d): ", columns, rows);
    for (int column = 0; column < columns; column++) {
        for (int row = 0; row < rows; row++) {
            const char *separator = row + 1 < rows ? " " : column + 1 < columns ? " | " : "";
            used += (size_t)snprintf(reply + used, capacity - used,
                                     "%d%s", matrix[row][column], separator);
        }
    }
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
