#pragma once
#include <stdio.h>
#include <getopt.h>

void printUsage(FILE* f);

const struct option long_options[] =
  {
   {"key"     , required_argument, NULL, 'k'},
   {"size"    , required_argument, NULL, 's'},
   {"prefix"  , required_argument, NULL, 'p'},
   {"threads" , required_argument, NULL, 't'},
   {"help"    , required_argument, NULL, 'h'}
  };

const enum key_types { k_RSA };
