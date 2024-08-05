CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -g
LDFLAGS = `pkg-config --libs gtk+-3.0` -lm

SRCS = table.c wheel.c bets.c
OBJS = $(SRCS:.c=.o)
EXEC = roulette_game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)