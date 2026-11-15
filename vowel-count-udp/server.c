#include "net.h"

#define PORT 9108

#include <ctype.h>

static void answer(const char *request, char *reply, size_t capacity)
{
    int vowels = 0, consonants = 0;
    for (; *request; request++) {
        unsigned char character = (unsigned char)*request;
        if (isalpha(character)) {
            if (strchr("aeiou", tolower(character)))
                vowels++;
            else
                consonants++;
        }
    }
    snprintf(reply, capacity, "Vowels: %d, consonants: %d", vowels, consonants);
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
