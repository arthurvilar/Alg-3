EXEC := myht

CC := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic -g

.PHONY: all clean purge

all : $(EXEC)

$(EXEC) : hash.o main.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f $(EXEC)

purge : clean
	rm -f *.o
