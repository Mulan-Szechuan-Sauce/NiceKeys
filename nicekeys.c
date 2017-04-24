#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <getopt.h>
#include "nicekeys.h"

void generate_RSA(struct key_settings *settings) {
    RSA *myrsa;
    unsigned long e = RSA_3;
    BIO *out = NULL;
    myrsa = RSA_generate_key(settings->bit_size, e, NULL, NULL);

    out = BIO_new(BIO_s_file());

    if(myrsa == NULL){
        printf("error in generating keypair..");
        exit(1);
    }

    out = BIO_new_fp(stdout, BIO_CLOSE);
    RSA_print(out,myrsa,0);
}

void generate_SHA256(struct key_settings *settings) {
    SHA256_CTX ctx;
    uint8_t results[SHA256_DIGEST_LENGTH];
    char *buf;
    int n;

    buf = "H";//argv[1];
    n = strlen(buf);
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, (uint8_t *)buf, n);
    SHA256_Final(results, &ctx);

    for (n = 0; n < SHA256_DIGEST_LENGTH; n++)
        printf("%02x", results[n]);
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printUsage(stderr);
        exit(EXIT_FAILURE);
    }
    int c;
    /* These will be set to reasonable value after argument parsing */
    int options = -1, size = -1, threads = -1;
    char *prefix = NULL;
    enum key_types type = DEFAULT;

    options = 0;
    while((c = getopt_long(argc, argv, "k:s:p:t:h", long_options, NULL)) != EOF) {
        switch(c) {
            case 'k':
                if (strcmp(optarg, "rsa") == 0 || strcmp(optarg, "RSA") == 0) {
                    type = k_RSA;
                }
                else if (strcmp(optarg, "sha256") == 0 || strcmp(optarg, "SHA256") == 0) {
                    type = k_SHA256;
                } else {
                    fprintf(stderr, "Unknown encryption type\n");
                    exit(EXIT_FAILURE);
                }
                options |= 0b1;      
                break;
            case 's':
                if ((size = atoi(optarg)) == 0) {
                    fprintf(stderr, "Size must be an integer greater then 0\n");
                    exit(EXIT_FAILURE);
                }
                options |= 0b10;
                break;
            case 'p':
                prefix = optarg;
                options |= 0b100;
                break;
            case 't':
                if ((threads = atoi(optarg)) == 0) {
                    fprintf(stderr, "Threads must be an integer greater then 0\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                printUsage(stdout);
                exit(EXIT_SUCCESS);
            default:
                printUsage(stderr);
                exit(EXIT_FAILURE);
        }
    }

    if (options != 7) {
        printUsage(stderr);
        exit(EXIT_FAILURE);
    }

    struct key_settings *settings = malloc(sizeof(struct key_settings));
    settings->prefix = prefix;
    settings->bit_size = size;
    settings->threads = threads;

    if (type == k_RSA) {
        generate_RSA(settings);
    }

    return 0;
}

void printUsage(FILE* outputStream) {
    fprintf(outputStream, "NiceKeys USAGE:\n");
    fprintf(outputStream, "\t-k --key: Type of key to generate \n");
    fprintf(outputStream, "\t-s --size: The bit size of the key\n");
    fprintf(outputStream, "\t-p --prefix: The prefix of the public key\n");
    fprintf(outputStream, "\t-t --threads: Number of threads to use\n");
    fprintf(outputStream, "\t-h --help: Display this message\n");
}

char *etos(enum key_types k) {
    switch (k) {
        case k_RSA:    return "RSA";
        case k_SHA256: return "SHA256";
        case DEFAULT:  return "DEFAULT";
    }
    
    /* For an invalid enum */
    return NULL;
}
