#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main(int argc, char **argv) {

    if (argc < 2 || argc > 2) {
        fprintf(stderr, "usage: %s prefix\n", argv[0]);
        exit(1);
    }

    SHA256_CTX ctx;
    uint8_t results[SHA256_DIGEST_LENGTH];
    char *buf;
    int n;

    buf = argv[1];
    n = strlen(buf);
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, (uint8_t *)buf, n);
    SHA256_Final(results, &ctx);

    for (n = 0; n < SHA256_DIGEST_LENGTH; n++)
        printf("%02x", results[n]);
    printf("\n");

    return 0;
}
