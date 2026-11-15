#ifndef LAB_NET_H
#define LAB_NET_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET Socket;
typedef int AddressLength;
#define close_socket closesocket
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
typedef int Socket;
typedef socklen_t AddressLength;
#define INVALID_SOCKET (-1)
#define close_socket close
#endif

static inline void fail(const char *operation)
{
#ifdef _WIN32
    fprintf(stderr, "%s failed (socket error %d)\n", operation, WSAGetLastError());
#else
    perror(operation);
#endif
    exit(EXIT_FAILURE);
}

static inline void init_sockets(void)
{
#ifdef _WIN32
    WSADATA data;
    int status = WSAStartup(MAKEWORD(2, 2), &data);
    if (status != 0) {
        fprintf(stderr, "WSAStartup failed (%d)\n", status);
        exit(EXIT_FAILURE);
    }
#else
    signal(SIGPIPE, SIG_IGN);
#endif
}

static inline void set_timeout(Socket sock)
{
#ifdef _WIN32
    DWORD timeout = 5000;
#else
    struct timeval timeout = {5, 0};
#endif
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout,
                   sizeof(timeout)) < 0 ||
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout,
                   sizeof(timeout)) < 0)
        fail("setsockopt");
}

static inline Socket open_socket(int type, unsigned short port, int server)
{
    init_sockets();
    Socket sock = socket(AF_INET, type, 0);
    if (sock == INVALID_SOCKET)
        fail("socket");

    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (server) {
#ifndef _WIN32
        int reuse = 1;
        if (type == SOCK_STREAM &&
            setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
            fail("setsockopt");
#endif
        if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
            fail("bind");
        if (type == SOCK_STREAM && listen(sock, 8) < 0)
            fail("listen");
        printf("Listening on 127.0.0.1:%hu\n", port);
        fflush(stdout);
    } else {
        set_timeout(sock);
        if (connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
            fail("connect");
    }
    return sock;
}

static inline int send_all(Socket sock, const char *data, int length)
{
    while (length > 0) {
        int sent = (int)send(sock, data, length, 0);
        if (sent <= 0)
            return 0;
        data += sent;
        length -= sent;
    }
    return 1;
}

/* TCP lines end in LF. The caller chooses the buffer size. */
static inline int receive_line(Socket sock, char *line, size_t capacity)
{
    for (size_t i = 0; i < capacity; i++) {
        char ch;
        if (recv(sock, &ch, 1, 0) != 1)
            return 0;
        if (ch == '\n') {
            line[i] = '\0';
            return 1;
        }
        if (ch == '\0' || i + 1 == capacity)
            return 0;
        line[i] = ch;
    }
    return 0;
}

static inline int read_input(char *line, int capacity)
{
    if (!fgets(line, capacity, stdin))
        return 0;
    size_t length = strlen(line);
    if (length && line[length - 1] == '\n')
        line[--length] = '\0';
    else if (!feof(stdin))
        return 0;
    if (length && line[length - 1] == '\r')
        line[length - 1] = '\0';
    return 1;
}

#endif
