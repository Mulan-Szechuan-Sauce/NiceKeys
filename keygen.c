#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "keygen.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printUsage(stderr);
    exit(EXIT_FAILURE);
  }
  int c, options;
  enum key_types type;
  char *prefix;
  int size;
  while((c = getopt_long(argc, argv, "k:s:p:t:h:", long_options, NULL)) != EOF) {
    switch(c) {
    case 'k':
      if (strcmp(optarg, "rsa") == 0)
        type = k_RSA;
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
      printf("threads: %s\n", optarg);
      break;
    case 'h':
      printf("help: %s\n", optarg);
      break;
    default:
      printUsage(stderr);
      exit(EXIT_FAILURE);
    }
  }

  if(options != 7) {
    printUsage(stderr);
    exit(EXIT_FAILURE);
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

void printUsage(FILE* outputStream) {
  fprintf(outputStream, "NiceKeys USAGE:\n");
  fprintf(outputStream, "\t-k --key: Type of key to generate \n");
  fprintf(outputStream, "\t-s --size: The bit size of the key\n");
  fprintf(outputStream, "\t-p --prefix: The prefix of the public key\n");
  fprintf(outputStream, "\t-t --threads: Number of threads to use\n");
  fprintf(outputStream, "\t-h --help: Display this message\n");
}
