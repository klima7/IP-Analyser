OBJS	= main.o ipaddr.o ipmask.o ipcompaddr.o ipdata.o
SOURCE	= main.cpp ipaddr.cpp ipmask.cpp ipcompaddr.cpp ipdata.cpp
HEADER	= ipaddr.h ipmask.h ipcompaddr.h ipdata.h ipexcept.h main.h
OUT	= IPAnalyser
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

ipaddr.o: ipaddr.cpp
	$(CC) $(FLAGS) ipaddr.cpp 

ipmask.o: ipmask.cpp
	$(CC) $(FLAGS) ipmask.cpp 

ipcompaddr.o: ipcompaddr.cpp
	$(CC) $(FLAGS) ipcompaddr.cpp 

ipdata.o: ipdata.cpp
	$(CC) $(FLAGS) ipdata.cpp 


clean:
	rm -f $(OBJS) $(OUT)
