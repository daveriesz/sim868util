
#ifndef __MAIN_H__
#define __MAIN_H__

struct tx_rx_pair
{
  char *tx;
  char *rx;
  struct tx_rx_pair *next;
};

struct run_parameters
{
  char *tty;
  int data_rate;
  int timeout;
  struct tx_rx_pair *command_pairs;
  int fd;
  unsigned int baud_rate;
};

void usage();

#endif /* __MAIN_H__ */

