#ifndef NHGETOPT_H
#define NHGETOPT_H

typedef struct {
  char* optarg;
  int optind;
  int opterr;
  int optopt;
} nhgetopt_context_t;

void nhgetopt_init_context(nhgetopt_context_t* context);

int nhgetopt(nhgetopt_context_t* context, int argc, char* const argv[], const char* optstring);

#endif

#if 1
//#ifdef NHGETOPT_IMPLEMENTATION

void nhgetopt_init_context(nhgetopt_context_t* context) {

  context->optarg = 0;
  context->optind = 1;
  context->opterr = 0;
  context->optopt = 0;

}

int nhgetopt(nhgetopt_context_t* context, int argc, char* const argv[], const char* optstring) {

  if (argv[context->optind])

}

#endif