#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MIN_LENGTH 3

void strings(FILE *file) {
    int c;
    int count = 0;
    char buffer[1024];

    while ((c = fgetc(file)) != EOF) {
        if (isprint(c)) {
            buffer[count++] = c;
            if (count >= sizeof(buffer) - 1) {
                break;
            }
        } else {
            if (count >= MIN_LENGTH) {
                buffer[count] = '\0';
                printf("%s\n", buffer);
            }
            count = 0;
        }
    }
    if (count >= MIN_LENGTH) {
        buffer[count] = '\0';
        printf("%s\n", buffer);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            perror("error opening file");
            continue;
        }
        printf( argv[i]);
        strings(file);
        fclose(file);
    }
    return EXIT_SUCCESS;
}
