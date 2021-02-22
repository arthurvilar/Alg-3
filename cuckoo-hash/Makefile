CFLAGS := -Wall -Werror -Wextra -pedantic -g

# regra default 
all : myht

# regras de ligação
myht : main.o hash.o
	gcc $(CFLAGS) main.o hash.o -o myht -lm

# regras de compilação
main.o : main.c hash.h
	gcc $(CFLAGS) -c main.c

hash.o : hash.c hash.h
	gcc $(CFLAGS) -c hash.c

# remove arquivos temporários
clean:
	-rm -f *~ *.o

# remove tudo que não é o código-fonte original
purge : clean
	-rm -f myht