CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11
TARGET = password_analyzer

SRCS = main.c analyzer.c entropy.c ui.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
