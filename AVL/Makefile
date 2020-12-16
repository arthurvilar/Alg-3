EXEC   := myavl

CC	   := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic -g

.PHONY : all run clean

all : $(EXEC)

$(EXEC) : libavl.o main.o
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(EXEC)

purge : clean
	rm -f *.o
