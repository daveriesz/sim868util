
/*******************************************************************************
 *                                                                             *
 * sim868init                                                                  *
 *                                                                             *
 * usage: sim868init <serial_device> [options]                                 *
 *                                                                             *
 * optsions:                                                                   *
 *     -b <data_rate>             - data/baud rate                             *
 *     -w                         - wait for response                          *
 *     -t                         - wait timeout (secs.) (0 for indefinite)    *
 *     -1 <tx_string> <rx_string> - command to send and expected response      *
 *     -2 ... -n                  - same as -1, executed in numerical order    *
 *                                                                             *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>


const char *usage()
{
  const char *usage_str[] = {
    "sim868init",
    "",
    "usage: sim868init <serial_device> [options]",
    "",
    "optsions:",
    "    -b <data_rate>             - data/baud rate",
    "    -w                         - wait for response",
    "    -t                         - wait timeout (secs.) (0 for indefinite)",
    "    -1 <tx_string> <rx_string> - command to send and expected response",
    "    -2 ... -n                  - same as -1, executed in numerical order",
  };
}


int main(int argc, char **argv)
{

}

