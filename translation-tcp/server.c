#include "net.h"

#define PORT 9103

#include <ctype.h>

static void answer(const char *request, char *reply, size_t capacity)
{
    static const struct { const char *short_form, *full_form; } dictionary[] = {
        {"tbh", "to be honest"}, {"ig", "I guess"}, {"tbf", "to be fair"},
        {"atm", "at the moment"}, {"irl", "in real life"}, {"lol", "laughing out loud"},
        {"asap", "as soon as possible"}, {"omg", "oh my God"}, {"ttyl", "talk to you later"},
        {"idk", "I don't know"}, {"nvm", "never mind"}, {"idc", "I don't care"}
    };

    memcpy(reply, "OK ", 3);
    size_t used = 3;
    while (*request) {
        const char *start = request++;
        if (isalnum((unsigned char)*start)) {
            while (isalnum((unsigned char)*request))
                request++;
        }
        const char *word = start;
        size_t length = (size_t)(request - start);
        for (size_t i = 0; i < sizeof(dictionary) / sizeof(dictionary[0]); i++) {
            if (strlen(dictionary[i].short_form) != length)
                continue;
            size_t j = 0;
            while (j < length && tolower((unsigned char)start[j]) == dictionary[i].short_form[j])
                j++;
            if (j == length) {
                word = dictionary[i].full_form;
                length = strlen(word);
                break;
            }
        }
        if (length >= capacity - used) {
            snprintf(reply, capacity, "ERROR: translated text is too long");
            return;
        }
        memcpy(reply + used, word, length);
        used += length;
    }
    reply[used] = '\0';
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
