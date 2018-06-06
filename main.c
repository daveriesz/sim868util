
/*******************************************************************************
 *                                                                             *
 * sim868init                                                                  *
 *                                                                             *
 * usage: sim868init <serial_device> [options]                                 *
 *                                                                             *
 * optsions:                                                                   *
 *     -b <data_rate>             - data/baud rate                             *
 *     -t <seconds>               - wait timeout (secs.) (0 for indefinite)    *
 *     -c <tx_string> <rx_string> - command to send and expected response      *
 *                                  Multiple commands can be specified and are *
 *                                  executed in the order they are listed.     *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "args_local.h"
#include "serial_local.h"

int main(int argc, char **argv)
{
  struct run_parameters params = { NULL, -1, -1, NULL, -1, 0 };
  parse_args(argc, argv, &params);

  if(1)
  {
    struct tx_rx_pair *trp;
    printf("serial_device = >>%s<<\n", params.tty);
    printf("data_rate     = %d\n", params.data_rate);
    printf("timeout       = %d\n", params.timeout);
    for(trp = params.command_pairs ; trp ; trp=trp->next)
    {
      printf("cmd tx = >>%s<<\n    rx = >>%s<<\n", trp->tx, trp->rx);
    }
  }
  if(params.tty == NULL)
  {
    fprintf(stderr, "Serial device not set.\n");
    exit(1);
  }
  
  return run_serial_commands(&params);
  
}

void usage()
{
  const char *usage_str =
    "usage: sim868init <serial_device> [options]\n"
    "\n"
    "optsions:\n"
    "    -b <data_rate>             - data/baud rate\n"
    "    -t <seconds>               - wait timeout (0 for indefinite)\n"
    "    -c <tx_string> <rx_string> - command to send and expected response\n"
    "                                 Multiple commands can be specified and are\n"
    "                                 executed in the order they are listed.\n"
    ;
  fprintf(stderr, "%s", usage_str);
  exit(1);
}

