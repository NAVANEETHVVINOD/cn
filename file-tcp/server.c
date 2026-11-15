#include "net.h"

#define PORT 9109

static void serve_file(Socket client, FILE *file, const char *name)
{
    char request[256];
    if (!receive_line(client, request, sizeof(request)) || strcmp(request, name) != 0) {
        const char error[] = "ERROR: requested file is not available\n";
        send_all(client, error, sizeof(error) - 1);
        return;
    }

    long size;
    if (fseek(file, 0, SEEK_END) != 0 || (size = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        const char error[] = "ERROR: could not read file size\n";
        send_all(client, error, sizeof(error) - 1);
        return;
    }

    char header[64];
    int length = snprintf(header, sizeof(header), "OK %ld\n", size);
    if (!send_all(client, header, length))
        return;

    char buffer[4096];
    while (size > 0) {
        size_t chunk = size < (long)sizeof(buffer) ? (size_t)size : sizeof(buffer);
        size_t count = fread(buffer, 1, chunk, file);
        if (count != chunk || !send_all(client, buffer, (int)count)) {
            fputs("File transfer ended early.\n", stderr);
            return;
        }
        size -= (long)count;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s FILE_TO_SERVE\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *name = strrchr(argv[1], '/');
    name = name ? name + 1 : argv[1];
#ifdef _WIN32
    const char *backslash = strrchr(name, '\\');
    if (backslash)
        name = backslash + 1;
#endif
    if (!*name || strlen(name) > 255 || strchr(name, '\n')) {
        fputs("The filename must be 1 to 255 bytes on a single line.\n", stderr);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    printf("Serving: %s\n", name);
    Socket server = open_socket(SOCK_STREAM, PORT, 1);
    for (;;) {
        Socket client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET)
            fail("accept");
        set_timeout(client);
        serve_file(client, file, name);
        close_socket(client);
    }
}
