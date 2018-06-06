
PROGRAMS = sim868init

CSOURCES = main.c serial.c
COBJECTS = $(CSOURCES:.c=.o)
CFLAGS   = $(COPT) $(CDEF) $(CINC)
COPT     = 
CDEF     = 
CINC     = 
CC       = gcc

LDFLAGS  = $(LDOPT) $(LDDIR) $(LDLIB)
LDOPT    = 
LDDIR    = 
LDLIB    = 

all: $(PROGRAMS)

sim868init: main.o serial.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)



