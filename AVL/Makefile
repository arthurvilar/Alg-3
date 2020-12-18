EXEC   := myavl

CC	   := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic -g

.PHONY : all clean

all : $(EXEC)

$(EXEC) : libavl.o teste.o
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(EXEC)

purge : clean
	rm -f *.o
