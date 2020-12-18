EXEC   := myavl

CC	   := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic -g

.PHONY : all clean teste

all : $(EXEC)

$(EXEC) : libavl.o main.o
	$(CC) $(CFLAGS) -o $@ $^

teste : libavl.o teste.o
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(EXEC) teste

purge : clean
	rm -f *.o
