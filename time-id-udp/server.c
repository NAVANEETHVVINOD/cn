#include "net.h"

#define PORT 9105

#include <time.h>

#define SERVER_ID "CN-TIME-01"

static void answer(const char *request, char *reply, size_t capacity)
{
    if (strcmp(request, "TIME") != 0) {
        snprintf(reply, capacity, "ERROR: expected TIME");
        return;
    }

    time_t now = time(NULL);
    struct tm *local = now == (time_t)-1 ? NULL : localtime(&now);
    char timestamp[64];
    if (!local || !strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local)) {
        snprintf(reply, capacity, "ERROR: server time is unavailable");
        return;
    }
    snprintf(reply, capacity, "server_id=%s | Local time: %s", SERVER_ID, timestamp);
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
