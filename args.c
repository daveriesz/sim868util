
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "args_local.h"

static int test_whole_number_arg(const char *want, const char *arg, const char *value, int *assign_to, int *errorinc, int exit_on_fail)
{
  int ii;
  if(strcmp(want, arg)) { return 0; } /* not the argument we want */
  for(ii=0 ; ii<strlen(value) ; ii++)
  {
    if(!isdigit(value[ii]))
    {
      fprintf(stderr, "%s requires a whole number: \"%s\" is invalid\n", arg, value);
      if(exit_on_fail != 0) { exit(1); }
      else { (*errorinc)++; }
    }
    else
    {
      *(assign_to) = atol(value);
    }
  }
  return 1;
}

static int test_fcn_arg(const char *want, const char *arg, void(*fcn)())
{
  if(strcmp(want, arg)) { return 0; } /* not the argument we want */
  fcn();
  return 1;
}

static int test_command_arg(const char *want, const char *arg, const char *tx, const char *rx, struct run_parameters *params, int *errorinc, int exit_on_fail)
{
  struct tx_rx_pair **ppTRPair;
  if(strcmp(want, arg)) { return 0; } /* not the argument we want */
  for(ppTRPair=(&(params->command_pairs)) ; ppTRPair && (*ppTRPair) ; ppTRPair = &((*ppTRPair)->next));
  (*ppTRPair) = (struct tx_rx_pair *)malloc(sizeof(struct tx_rx_pair));
  (*ppTRPair)->tx   = strdup(tx);
  (*ppTRPair)->rx   = strdup(rx);
  (*ppTRPair)->next = NULL;
  return 1;
}

void parse_args(int argc, char **argv, struct run_parameters *params)
{
  int ii, jj;
  int errors = 0;
  if(argc == 1) { usage(); }
  for(ii=1 ; ii<argc ; ii++)
  {
    if(test_fcn_arg         ("-h", argv[ii], usage                                       )) {        continue; }
    if(test_whole_number_arg("-b", argv[ii], argv[ii+1], &(params->data_rate), &errors, 0)) { ii+=1; continue; }
    if(test_whole_number_arg("-t", argv[ii], argv[ii+1], &(params->timeout  ), &errors, 0)) { ii+=1; continue; }
    if(test_command_arg     ("-c", argv[ii], argv[ii+1], argv[ii+2], params,   &errors, 0)) { ii+=2; continue; }
    else
    {
      if(params->tty)
      {
        fprintf(stderr, "argument error: >>%s<<\nserial device is already set to >>%s<<\n",
          argv[ii], params->tty);
        errors++;
      }
      else { params->tty = strdup(argv[ii]); }
    }
  }
  if(errors != 0) { exit(1); }
}

