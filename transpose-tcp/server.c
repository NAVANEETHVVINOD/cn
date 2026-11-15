#include "net.h"

#define PORT 9106

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
