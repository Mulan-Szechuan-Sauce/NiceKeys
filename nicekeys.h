#pragma once

const struct option long_options[] =
  {
   {"key"     , required_argument, NULL, 'k'},
   {"size"    , required_argument, NULL, 's'},
   {"prefix"  , required_argument, NULL, 'p'},
   {"threads" , required_argument, NULL, 't'},
   {"help"    , no_argument      , NULL, 'h'}
  };

struct key_settings {
  char   *prefix;
  size_t bit_size;
  int    threads;
};

enum key_types { 
    DEFAULT,
    k_RSA,
    k_SHA256
};

char *etos(enum key_types k);
void printUsage(FILE* f);

