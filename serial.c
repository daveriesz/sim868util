
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "main.h"
#include "serial_local.h"

static int set_baud_rate(int data_rate)
{
  unsigned int ti_rate = 0;
  switch(data_rate)
  {
    case      50: ti_rate =      B50; break;
    case      75: ti_rate =      B75; break;
    case     110: ti_rate =     B110; break;
    case     134: ti_rate =     B134; break;
    case     150: ti_rate =     B150; break;
    case     200: ti_rate =     B200; break;
    case     300: ti_rate =     B300; break;
    case     600: ti_rate =     B600; break;
    case    1200: ti_rate =    B1200; break;
    case    1800: ti_rate =    B1800; break;
    case    2400: ti_rate =    B2400; break;
    case    4800: ti_rate =    B4800; break;
    case    9600: ti_rate =    B9600; break;
    case   19200: ti_rate =   B19200; break;
    case   38400: ti_rate =   B38400; break;
    case   57600: ti_rate =   B57600; break;
    case  115200: ti_rate =  B115200; break;
    case  230400: ti_rate =  B230400; break;
    case  460800: ti_rate =  B460800; break;
    case  500000: ti_rate =  B500000; break;
    case  576000: ti_rate =  B576000; break;
    case  921600: ti_rate =  B921600; break;
    case 1000000: ti_rate = B1000000; break;
    case 1152000: ti_rate = B1152000; break;
    case 1500000: ti_rate = B1500000; break;
    case 2000000: ti_rate = B2000000; break;
    case 2500000: ti_rate = B2500000; break;
    case 3000000: ti_rate = B3000000; break;
    case 3500000: ti_rate = B3500000; break;
    case 4000000: ti_rate = B4000000; break;
    default:
      fprintf(stderr, "unsupported rate: %d\n", data_rate);
      fprintf(stderr, "valid rates are: 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800 2400,\n");
      fprintf(stderr, "                 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800,\n");
      fprintf(stderr, "                 500000, 576000, 921600, 1000000, 1152000, 1500000,\n");
      fprintf(stderr, "                 2000000, 2500000, 3000000, 3500000, and 4000000.\n");
      exit(1);
  }
  return ti_rate;
}

static int open_serial_device(struct run_parameters *params)
{
  params->fd = open(params->tty, O_RDWR|O_NOCTTY|O_NDELAY);
  if(params->fd < 0)
  {
    fprintf(stderr, "failed to open device >>%s<<: %s\n", params->tty, strerror(errno));
    exit(1);
  }
  else
  {
    fcntl(params->fd, F_SETFL, 0); /* blocking */
//    fcntl(params->fd, SETFL, FNDELAY); /* non-blocking */
  }
  return params->fd;
}

static int configure_serial_device(struct run_parameters *params)
{
  struct termios options;

  tcgetattr(params->fd, &options);

  cfsetispeed(&options, params->baud_rate);
  cfsetospeed(&options, params->baud_rate);

  options.c_cflag |= (CLOCAL | CREAD);

  if(1) /* set 8n1 */
  {
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE ;
    options.c_cflag |= ~CS8;
  }

  tcsetattr(params->fd, TCSANOW, &options);
  
  return 0;
}

static int read_write_operations(struct run_parameters *params)
{
  struct tx_rx_pair *trp;
  char *txstr;
  int len;

  for(trp=params->command_pairs ; trp ; trp=trp->next)
  {
    printf("running tx=%s rx=%s\n", trp->tx, trp->rx);
    len = strlen(trp->tx) + 2;
    txstr = (char *)malloc(len);
    memset(txstr, 0, len);
    sprintf(txstr, "%s\r", trp->tx);
    write(params->fd, txstr, len-1);
  }
}

int run_serial_commands(struct run_parameters *params)
{
  int fd;
  unsigned int baud_rate;
  params->baud_rate = set_baud_rate(params->data_rate);
  
  open_serial_device(params);
  configure_serial_device(params);
  read_write_operations(params);

  return 0;
}

