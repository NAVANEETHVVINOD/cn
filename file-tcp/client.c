#include "net.h"

#define PORT 9109

static int download(Socket sock, long remaining, const char *destination)
{
    FILE *file = fopen(destination, "wbx");
    if (!file) {
        perror(destination);
        return 0;
    }

    char buffer[4096];
    while (remaining > 0) {
        int chunk = remaining < (long)sizeof(buffer) ? (int)remaining : (int)sizeof(buffer);
        int received = (int)recv(sock, buffer, chunk, 0);
        if (received <= 0 || fwrite(buffer, 1, (size_t)received, file) != (size_t)received)
            break;
        remaining -= received;
    }
    int closed = fclose(file);
    if (remaining || closed != 0) {
        fputs("Download incomplete.\n", stderr);
        if (remove(destination) != 0)
            perror(destination);
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 3 || !*argv[1] || strlen(argv[1]) > 255 || strchr(argv[1], '\n')) {
        fprintf(stderr, "Usage: %s REMOTE_FILENAME NEW_LOCAL_FILE\n", argv[0]);
        return EXIT_FAILURE;
    }

    Socket sock = open_socket(SOCK_STREAM, PORT, 0);
    char header[128];
    if (!send_all(sock, argv[1], (int)strlen(argv[1])) ||
        !send_all(sock, "\n", 1) || !receive_line(sock, header, sizeof(header))) {
        fputs("Could not read the file transfer status.\n", stderr);
        close_socket(sock);
        return EXIT_FAILURE;
    }
    if (strncmp(header, "OK ", 3) != 0) {
        fprintf(stderr, "%s\n", header);
        close_socket(sock);
        return EXIT_FAILURE;
    }

    char *end;
    const char *length = header + 3;
    errno = 0;
    long size = strtol(length, &end, 10);
    if (length == end || *end || errno == ERANGE || size < 0) {
        fputs("Invalid file size.\n", stderr);
        close_socket(sock);
        return EXIT_FAILURE;
    }

    int success = download(sock, size, argv[2]);
    close_socket(sock);
    if (!success)
        return EXIT_FAILURE;
    printf("Saved %ld bytes to %s\n", size, argv[2]);
    return EXIT_SUCCESS;
}
