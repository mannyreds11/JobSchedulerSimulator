
CC= g++
CPP=  -p
CFLAGS= -O4 -Wno-deprecated
LDFLAGS=
PROFFLAG= 

OBJS = events.o jobs.o random.o main.o stats.o Simulation.o

.cc.o:
	$(CC) $(CFLAGS) $(PROFFLAG) -c $<

a.out: $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) $(LDFLAGS) $(PROFFLAG)


clean:
	rm TAGS $(OBJS) a.out core sim mon.out


strip:
	strip a.out
	mcs -d a.out

