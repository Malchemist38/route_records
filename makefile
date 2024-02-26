CC = gcc
CFLAGS = -std=c99

SRCS = main.c route-records.c
OBJS = $(SRCS:.c=.o)

TARGET = airline_records

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c route-records.h
route-records.o: route-records.c route-records.h

clean:
	rm -f $(OBJS) $(TARGET)
