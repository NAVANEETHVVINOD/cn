#include "net.h"

#define PORT 9104

#include <ctype.h>

static void answer(const char *request, char *reply, size_t capacity)
{
    int letters = 0, digits = 0, special = 0;
    for (; *request; request++) {
        unsigned char character = (unsigned char)*request;
        if (isalpha(character))
            letters++;
        else if (isdigit(character))
            digits++;
        else
            special++;
    }
    snprintf(reply, capacity, "Alphabets: %d, digits: %d, special characters: %d",
             letters, digits, special);
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
