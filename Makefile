
PROGRAMS = sim868init

CSOURCES = main.c args.c serial.c
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

STRLONG  = 10

all: $(PROGRAMS)

sim868init: $(COBJECTS)
	@printf " + LD %$(STRLONG)s <== %$(STRLONG)s\n" "$@" "..."
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@printf " + CC %$(STRLONG)s <== %$(STRLONG)s\n" "$@" "$<"
	@$(CC) -o $@ -c $< $(CFLAGS)

main.o  : main.c   main.h args_local.h serial_local.h
args.o  : args.c   main.h args_local.h serial_local.h
serial.o: serial.c main.h args_local.h serial_local.h

run: $(PROGRAMS)
	./$< -b 115200 -t 3 -c at OK /dev/ttyUSB0

clean: objclean execlean
objclean:
	$(RM) $(COBJECTS)
execlean:
	$(RM) $(PROGRAMS)
        
