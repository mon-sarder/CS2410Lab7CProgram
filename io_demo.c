#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SZ 256

// Reads a line of text safely from stdin into dst (newline stripped).
void read_line(char *dst, size_t cap) {
    if (!fgets(dst, (int)cap, stdin)) {
        // Input error/EOF — make it empty string.
        dst[0] = '\0';
        return;
    }
    // Strip trailing newline, if present.
    size_t n = strlen(dst);
    if (n && dst[n-1] == '\n') dst[n-1] = '\0';
}

// Writes text to a file path (overwrites). Returns 0 on success.
int write_to_file(const char *path, const char *text) {
    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    if (fputs(text, fp) == EOF) {
        perror("fputs");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}

int main(void) {
    char name[BUF_SZ];
    char message[BUF_SZ];

    // Several primitive types for Task 2 (GDB):
    int age = 19;
    float gpa = 3.75f;
    double pi = 3.141592653589793;
    long big = 1234567890L;
    unsigned int flags = 0xA5u;
    char grade = 'A';

    printf("Enter your name: ");
    read_line(name, sizeof(name));

    printf("Enter a short message: ");
    read_line(message, sizeof(message));

    // Compose an output record
    char out[BUF_SZ * 2];
    snprintf(out, sizeof(out),
             "Name: %s\nMessage: %s\n(age=%d, gpa=%.2f, pi=%.15f, big=%ld, flags=0x%X, grade=%c)\n",
             name, message, age, gpa, pi, big, flags, grade);

    // Write to file
    const char *path = "output.txt";
    if (write_to_file(path, out) == 0) {
        printf("Wrote your input to %s\n", path);
    } else {
        fprintf(stderr, "Failed to write to %s\n", path);
        return 1;
    }
    return 0;
}
