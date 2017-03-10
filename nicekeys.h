#pragma once
#include <stdio.h>
#include <getopt.h>

void printUsage(FILE* f);

int threads = 1;

const struct option long_options[] =
  {
   {"key"     , required_argument, NULL, 'k'},
   {"size"    , required_argument, NULL, 's'},
   {"prefix"  , required_argument, NULL, 'p'},
   {"threads" , required_argument, NULL, 't'},
   {"help"    , no_argument      , NULL, 'h'}
  };

struct key_settings = {
  char* settings;
  char* prefix;
  int   bit_size;
}

const enum key_types { k_RSA };
