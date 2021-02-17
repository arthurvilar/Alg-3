EXEC := run

CC := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic -g

.PHONY: all clean purge

all : $(EXEC)

$(EXEC) : hash.o

clean:
	rm -f $(EXEC)

purge : clean
	rm -f hash.o
